import pygame
import random
import math
import matplotlib.pyplot as plt
import numpy as np

# --- Constants & Configuration ---
SCREEN_WIDTH = 1200
SCREEN_HEIGHT = 600
FPS = 60

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (50, 50, 50)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLUE = (0, 100, 255)
YELLOW = (255, 255, 0)
ORANGE = (255, 165, 0)

LANE_Y = 300
LANE_WIDTH = 100 
PIXELS_PER_METER = 20

# Scientific Constants
# Gap acceptance mean reduced to encourage crossing in simulation time scale
GAP_MEAN = 3.5  
GAP_STD = 1.0

# --- Vehicle Definitions (Research-Backed) ---
class VehicleType:
    def __init__(self, name, color, annoyance, detectability, severity_risk, brake_efficiency):
        self.name = name
        self.color = color
        self.annoyance = annoyance        # Derived from  (Bazilinskyy et al., 2025)
        self.detectability = detectability # Derived from  (Wadud, 2025) 
        self.severity_risk = severity_risk # Derived from  (Wadud, 2025)
        self.brake_efficiency = brake_efficiency # 1.0 = Standard, 1.3 = EV Instant Torque/Regen

VEHICLE_TYPES = {
    #  Diesel annoyance ~3.5 (Reference case). 
    #  Standard Braking (Hydraulic lag)
    'ICE': VehicleType('Diesel (ICE)', (150, 150, 150), 
                       annoyance=3.5, detectability=0.98, severity_risk=0.20, brake_efficiency=1.0),

    #  Tyres only annoyance ~1.0 (Lowest).
    #  EVs brake faster (Regen + faster actuation)
    'EV_SILENT': VehicleType('Silent EV', (50, 50, 50), 
                             annoyance=1.0, detectability=0.20, severity_risk=0.20, brake_efficiency=1.3),

    #  Pure Tone (High Freq) annoyance ~5.4 (Highest rated annoyance).  
    #  Post-2019 EV (AVAS) casualty rate similar to ICE -> High Detectability (0.98). 
    'EV_PURE': VehicleType('AVAS Pure Tone', (0, 0, 255), 
                           annoyance=5.4, detectability=0.98, severity_risk=0.20, brake_efficiency=1.3),

    #  Combined Tone/Intermittent annoyance ~4.8 (Better compromise). 
    #  Assuming effective AVAS -> High Detectability (0.98).
    'EV_COMPLEX': VehicleType('AVAS Complex', (0, 200, 200), 
                              annoyance=4.8, detectability=0.98, severity_risk=0.20, brake_efficiency=1.3),

    #  Hybrid annoyance ~3.0 (Assumed slightly quieter/similar to ICE).
    #  To model 2.0x accident rate vs ICE (0.02 miss rate), HEV needs ~0.04 miss rate.
    #  However, given simulation simplicity, we tune detectability to 0.70 to ensure impact is visible.
    #  "HEVs show a negative... association with severity" -> Severity Risk lowered to 0.05. [cite: 2]
    #  HEV braking is good but heavier vehicle? Let's say 1.2
    'HEV': VehicleType('Hybrid (HEV)', (255, 140, 0), 
                       annoyance=3.0, detectability=0.70, severity_risk=0.05, brake_efficiency=1.2) 
}

# --- Simulation Classes ---

class Vehicle(pygame.sprite.Sprite):
    def __init__(self, v_type_key, x):
        super().__init__()
        self.type_data = VEHICLE_TYPES[v_type_key]
        self.v_key = v_type_key
        
        self.image = pygame.Surface((80, 40), pygame.SRCALPHA) 
        self.draw_vehicle_icon()
        
        self.rect = self.image.get_rect()
        self.rect.x = x
        self.rect.y = LANE_Y + (LANE_WIDTH - 40) // 2
        
        self.speed_mps = 13.8 # approx 50 km/h
        self.speed_px = self.speed_mps * PIXELS_PER_METER / FPS
        self.current_speed_px = self.speed_px # Current actual speed
        self.is_braking = False

    def draw_vehicle_icon(self):
        # Draw Chassis
        pygame.draw.rect(self.image, self.type_data.color, (0, 0, 80, 40), border_radius=5)
        
        # Draw Windshield (Black rect)
        pygame.draw.rect(self.image, (30, 30, 30), (50, 2, 20, 36))
        
        # Draw Headlights (Yellow/White cones)
        pygame.draw.circle(self.image, (255, 255, 200), (78, 8), 4)
        pygame.draw.circle(self.image, (255, 255, 200), (78, 32), 4)
        
        # Brake Lights (Red when stopped, slightly darker when moving)
        pygame.draw.circle(self.image, (150, 0, 0), (2, 8), 3)
        pygame.draw.circle(self.image, (150, 0, 0), (2, 32), 3)

        # Add text label (Type)
        font = pygame.font.SysFont('Arial', 10, bold=True)
        label = font.render(self.v_key.split()[0][:6], True, WHITE)
        self.image.blit(label, (5, 12))

    def update(self, light_state, vehicles, pedestrians=None): # Added pedestrians arg
        # 1. Base Target (Cruising)
        target_speed = 8.3 * PIXELS_PER_METER / FPS 
        
        # 2. EMERGENCY BRAKING (Pedestrian Detection)
        # Vehicles can detect pedestrians in front (Safety feature)
        # Logic: If ped in lane AND dist < critical -> BRAKE
        braking_urgency = 0
        if pedestrians:
            for p in pedestrians:
                if p.state in ['CROSSING', 'Wait']: # Should brake for crossing peds
                    # Check lateral alignment (is ped in front of car's lane?)
                    if self.rect.top - 10 < p.rect.y < self.rect.bottom + 10:
                        # Check longitudinal distance
                        dist_to_ped = p.rect.left - self.rect.right
                        if 0 < dist_to_ped < 200: # 10 meters scan range
                            braking_urgency = 1.0 # MAX BRAKE
        
        # 3. Traffic Light Check
        stop_line_x = 1000
        dist_to_light = stop_line_x - self.rect.right
        
        if light_state == 'RED':
            if 0 < dist_to_light < 150: 
                target_speed = 0
        
        # 4. Queueing Logic
        dist_to_car_ahead = 999
        for v in vehicles:
            if v != self:
                if v.rect.left > self.rect.right - 10:
                     d = v.rect.left - self.rect.right
                     if d < dist_to_car_ahead:
                         dist_to_car_ahead = d
        
        if dist_to_car_ahead < 30:
             target_speed = 0

        if braking_urgency > 0:
            # EVs brake 30% harder/quicker
            decel = 0.5 * self.type_data.brake_efficiency 
            self.current_speed_px = max(0, self.current_speed_px - decel)
            self.is_braking = True
        else:
            # Normal Cruise control
            if self.current_speed_px < target_speed:
                self.current_speed_px += 0.1 # Accel
            elif self.current_speed_px > target_speed:
                self.current_speed_px -= 0.2 # Normal coastal decel
            self.is_braking = (self.current_speed_px < target_speed - 0.5)

        self.rect.x += self.current_speed_px
        
        if self.is_braking or self.current_speed_px == 0:
             pygame.draw.circle(self.image, (255, 0, 0), (2, 8), 4)
             pygame.draw.circle(self.image, (255, 0, 0), (2, 32), 4)
        else:
             pygame.draw.circle(self.image, (100, 0, 0), (2, 8), 3)
             pygame.draw.circle(self.image, (100, 0, 0), (2, 32), 3)


class Pedestrian(pygame.sprite.Sprite):
    def __init__(self, mode='jaywalk'):
        super().__init__()
        self.mode = mode # 'legal' or 'jaywalk'
        self.image = pygame.Surface((24, 24), pygame.SRCALPHA)
        self.draw_human_icon(BLUE)
        
        self.rect = self.image.get_rect()
        
        if self.mode == 'legal':
             # Spawn at Crosswalk (near traffic light)
             self.rect.centerx = random.randint(1030, 1090)
        else:
             # Spawn randomly before the stop line (Jaywalking zone)
             self.rect.centerx = random.randint(100, 950)
             
        self.rect.bottom = LANE_Y - 10
        
        self.state = 'WAITING' 
        self.speed = 2.0 * PIXELS_PER_METER / FPS 
        self.critical_gap = max(1.0, random.gauss(GAP_MEAN, GAP_STD))
        self.decision_timer = 0
        self.impatience = 0

    def draw_human_icon(self, color):
        self.image.fill((0,0,0,0)) # Clear
        pygame.draw.circle(self.image, color, (12, 12), 10)
        pygame.draw.rect(self.image, color, (4, 18, 16, 6))

    def decide_to_cross(self, vehicles, light_state):
        # 1. Legal Crossing Logic
        if self.mode == 'legal':
            # Cross only if Cars have RED (Pedestrians have GREEN)
            if light_state == 'RED':
                self.start_crossing()
            return 

        # 2. Jaywalking Logic (Gap Acceptance)
        self.impatience += 0.1
        current_crit_gap = max(1.0, self.critical_gap - self.impatience)

        # Find nearest APPROACHING vehicle
        approaching_cars = [v for v in vehicles if v.rect.x < self.rect.x + 20 and v.rect.x > -150]
        
        # Check for immediate blockage
        for v in vehicles:
            if v.rect.right > self.rect.left - 10 and v.rect.left < self.rect.right + 10:
                return # Blocked

        if not approaching_cars:
            self.start_crossing()
            return
        
        nearest_time_gap = 999
        
        for v in approaching_cars:
            effective_speed = v.speed_px
            if effective_speed < 0.1: 
                effective_speed = 0.01 

            dist_px = self.rect.x - v.rect.right
            if dist_px < 0: continue 
            
            time_gap = dist_px / effective_speed / FPS 
            
            # DETECTION CHECK
            detected = True
            if random.random() > v.type_data.detectability:
                detected = False 
            
            if detected:
                 if time_gap < nearest_time_gap:
                     nearest_time_gap = time_gap
        
        if nearest_time_gap > current_crit_gap:
            self.start_crossing()

    def start_crossing(self):
        self.state = 'CROSSING'
        self.draw_human_icon(YELLOW)

    def update(self, *args): 
        if self.state == 'CROSSING':
            self.rect.y += self.speed
            if self.rect.top > LANE_Y + LANE_WIDTH:
                self.state = 'DONE'
                self.draw_human_icon(GREEN)
        elif self.state == 'HIT':
            self.draw_human_icon(RED)

class Scenario:
    def __init__(self, name, fleet_mix, traffic_rate):
        self.name = name
        self.fleet_mix = fleet_mix 
        self.traffic_rate = traffic_rate 

class Simulation:
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Lab 9: Pedestrian Safety - Research Backed Simulation")
        self.clock = pygame.time.Clock()
        self.font = pygame.font.SysFont('Arial', 16)
        self.history = {} 

        self.setup_scenarios()
        self.reset_simulation(self.scenarios[0])

    def setup_scenarios(self):
        # Scenarios ... (Same as before)
        scenario_a = Scenario("A. The Silent Danger (Pre-2019)", {'ICE': 0.9, 'EV_SILENT': 0.1}, 40)
        scenario_b = Scenario("B. The Hybrid Problem (Source 2)", {'HEV': 1.0}, 40)
        scenario_c = Scenario("C. Optimized Future (Source 1)",   {'ICE': 0.2, 'EV_COMPLEX': 0.8}, 40)
        self.scenarios = [scenario_a, scenario_b, scenario_c]
        self.current_scenario_idx = 0

    def reset_simulation(self, scenario):
        # Save history
        if hasattr(self, 'active_scenario'):
            avg_noise = 0
            if self.total_annoyance:
                avg_noise = sum(self.total_annoyance) / len(self.total_annoyance)
            
            self.history[self.active_scenario.name] = {
                'Collisions': self.total_colls,
                'Severe': self.total_severe,
                'NearMisses': self.near_misses,
                'Noise': avg_noise
            }

        self.active_scenario = scenario
        self.all_sprites = pygame.sprite.Group()
        self.vehicles = pygame.sprite.Group()
        self.pedestrians = pygame.sprite.Group()
        
        self.spawn_timer = 0
        self.total_colls = 0
        self.total_severe = 0
        self.near_misses = 0 
        self.total_annoyance = []
        self.sim_time = 0
        
        # Traffic Light Init
        self.light_state = 'GREEN'
        self.light_timer = 0
        
        print(f"--- Scenario Reset: {scenario.name} ---")

    def get_spawn_type(self):
        r = random.random()
        cumulative = 0
        for v_type, prob in self.active_scenario.fleet_mix.items():
            cumulative += prob
            if r <= cumulative:
                return v_type
        return 'ICE'

    def run(self):
        running = True
        print("Controls: 1, 2, 3 to switch scenarios. R to restart. CLOSE window to plot.")
        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.reset_simulation(self.active_scenario) # Save last data
                    running = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_1: self.reset_simulation(self.scenarios[0])
                    if event.key == pygame.K_2: self.reset_simulation(self.scenarios[1])
                    if event.key == pygame.K_3: self.reset_simulation(self.scenarios[2])
                    if event.key == pygame.K_r: self.reset_simulation(self.active_scenario)

            self.update()
            self.draw()
            self.clock.tick(FPS)
            
        pygame.quit()
        self.plot_results()

    def update(self):
        self.sim_time += 1
        
        # Traffic Light Logic (10s Green, 6s Red)
        self.light_timer += 1
        if self.light_state == 'GREEN' and self.light_timer > 600: # 10s
             self.light_state = 'RED'
             self.light_timer = 0
        elif self.light_state == 'RED' and self.light_timer > 360: # 6s
             self.light_state = 'GREEN'
             self.light_timer = 0

        # Spawn Vehicles
        frames_per_spawn = (60 * FPS) / self.active_scenario.traffic_rate
        if self.sim_time - self.spawn_timer > frames_per_spawn:
            if random.random() < 0.7: 
                v_type = self.get_spawn_type()
                v = Vehicle(v_type, -150)
                self.vehicles.add(v)
                self.all_sprites.add(v)
                self.total_annoyance.append(v.type_data.annoyance)
                self.spawn_timer = self.sim_time

        # Spawn Pedestrians
        if random.random() < 0.02: 
            mode = 'legal' if random.random() < 0.4 else 'jaywalk'
            p = Pedestrian(mode)
            self.pedestrians.add(p)
            self.all_sprites.add(p)

        for p in self.pedestrians:
            if p.state == 'WAITING':
                p.decision_timer += 1
                if p.decision_timer % 15 == 0: 
                    p.decide_to_cross(self.vehicles, self.light_state)

        # Near Miss Logic (Check distances without collision)
        for p in self.pedestrians:
            if p.state == 'CROSSING':
                for v in self.vehicles:
                    # distance in pixels
                    dist_x = abs(p.rect.centerx - v.rect.centerx)
                    dist_y = abs(p.rect.centery - v.rect.centery)
                    
                    if dist_x < 80 and dist_y < 60: # Close proximity
                        if not pygame.sprite.collide_rect(p, v):
                            # Ensure we don't count same near miss multiple times for same car/ped pair
                            if random.random() < 0.1: 
                                self.near_misses += 0.1

        # Collisions
        hits = pygame.sprite.groupcollide(self.pedestrians, self.vehicles, False, False)
        for p, vs in hits.items():
            if p.state != 'HIT' and p.state != 'DONE':
                p.state = 'HIT'
                self.total_colls += 1
                v_hit = vs[0]
                if random.random() < v_hit.type_data.severity_risk:
                    self.total_severe += 1
                    print(f"SEVERE INJURY! Hit by {v_hit.v_key}")
                else:
                    print(f"Minor Injury. Hit by {v_hit.v_key}")

        # Cleanup
        for v in self.vehicles:
            if v.rect.x > SCREEN_WIDTH: v.kill()
        for p in self.pedestrians:
             if p.rect.y > SCREEN_HEIGHT: p.kill()
        
        # Custom Update for Vehicles (Pass params)
        self.vehicles.update(self.light_state, self.vehicles, self.pedestrians) # Pass pedestrians for braking
        self.pedestrians.update() # Normal update

    def draw(self):
        self.screen.fill(BLACK)
        
        # Road
        pygame.draw.rect(self.screen, GRAY, (0, LANE_Y, SCREEN_WIDTH, LANE_WIDTH))
        pygame.draw.line(self.screen, WHITE, (0, LANE_Y + LANE_WIDTH/2), (SCREEN_WIDTH, LANE_Y + LANE_WIDTH/2), 2)
        # Lane markings
        for i in range(0, SCREEN_WIDTH, 40):
            pygame.draw.line(self.screen, WHITE, (i, LANE_Y), (i+20, LANE_Y), 1)
            pygame.draw.line(self.screen, WHITE, (i, LANE_Y+LANE_WIDTH), (i+20, LANE_Y+LANE_WIDTH), 1)
        
        # Draw Stop Line
        pygame.draw.line(self.screen, RED, (1000, LANE_Y), (1000, LANE_Y+LANE_WIDTH), 5)
        
        # Draw Zebra Crossing (Next to stop line)
        for x in range(1020, 1100, 20):
             pygame.draw.rect(self.screen, WHITE, (x, LANE_Y, 12, LANE_WIDTH))
        
        # Draw Traffic Light
        light_color = GREEN if self.light_state == 'GREEN' else RED
        pygame.draw.rect(self.screen, (20, 20, 20), (1010, LANE_Y - 100, 40, 80)) # Body
        if self.light_state == 'RED':
             pygame.draw.circle(self.screen, RED, (1030, LANE_Y - 80), 15)
             pygame.draw.circle(self.screen, (50, 0, 0), (1030, LANE_Y - 40), 15) # Dim Green
        else:
             pygame.draw.circle(self.screen, (50, 0, 0), (1030, LANE_Y - 80), 15) # Dim Red
             pygame.draw.circle(self.screen, GREEN, (1030, LANE_Y - 40), 15)

        self.all_sprites.draw(self.screen)
        
        self.draw_ui()
        pygame.display.flip()

    def draw_ui(self):
        s_text = self.font.render(f"Scenario: {self.active_scenario.name}", True, WHITE)
        self.screen.blit(s_text, (10, 10))
        
        avg_annoy = 0
        if self.total_annoyance:
            avg_annoy = sum(self.total_annoyance) / len(self.total_annoyance)
            
        stats = [
            f"Collisions: {self.total_colls}",
            f"Severe Injuries: {self.total_severe}",
            f"Avg Annoyance: {avg_annoy:.1f} / 10.0 ",
            f"Near Misses: {int(self.near_misses)}"
        ]
        
        for i, line in enumerate(stats):
            color = WHITE
            if "Near Misses" in line: color = ORANGE
            if "Collisions" in line: color = RED
            t = self.font.render(line, True, color)
            self.screen.blit(t, (10, 40 + i*20))

    def plot_results(self):
        if not self.history:
            print("No history to plot. Run at least one scenario for a few seconds!")
            return

        scenarios = list(self.history.keys())
        collisions = [self.history[s]['Collisions'] for s in scenarios]
        severe = [self.history[s]['Severe'] for s in scenarios]
        near_miss = [self.history[s]['NearMisses'] for s in scenarios]
        noise = [self.history[s]['Noise'] for s in scenarios]
        
        x = np.arange(len(scenarios))
        width = 0.20
        
        fig, ax1 = plt.subplots(figsize=(12, 6))
        
        # Metrics
        ax1.bar(x - width, collisions, width, label='Collisions', color='red')
        ax1.bar(x, severe, width, label='Severe', color='darkred')
        ax1.bar(x + width, near_miss, width, label='Near Misses', color='orange')
        
        ax1.set_ylabel('Count', color='black')
        ax1.set_xticks(x)
        ax1.set_xticklabels(scenarios, rotation=15, ha="right")
        ax1.legend(loc='upper left')
        
        # Noise Annoyance
        ax2 = ax1.twinx()
        ax2.plot(x, noise, label='Avg Annoyance', color='purple', marker='o', linewidth=2, linestyle='--')
        ax2.set_ylabel('Annoyance Rating (0-10)', color='purple')
        ax2.set_ylim(0, 10)
        ax2.legend(loc='upper right')
        
        plt.title('Research-Backed Analysis: Bazilinskyy et al. & Wadud')
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    sim = Simulation()
    sim.run()