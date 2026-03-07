import pygame
import random
import math
import os
import matplotlib.pyplot as plt
from collections import deque

# ============================================================================
# SIMULATION PARAMETERS
# ============================================================================

# Screen
WIDTH, HEIGHT = 1000, 700
FPS = 60

# Colors
BG_COLOR_DAY = (20, 20, 20)
BG_COLOR_NIGHT = (5, 5, 15)
COLOR_SUSCEPTIBLE = (50, 150, 255)  # Blue
COLOR_EXPOSED = (255, 200, 50)      # Yellow (Incubation)
COLOR_INFECTED = (255, 50, 50)      # Red
COLOR_RECOVERED = (50, 200, 50)     # Green
COLOR_DEAD = (100, 100, 100)        # Gray
COLOR_QUARANTINE = (50, 0, 0)       # Dark Red Background
COLOR_BORDER = (255, 255, 255)
COLOR_HOSPITAL = (255, 100, 255)    # Pink/Purple for UI
COLOR_MONEY = (255, 215, 0)         # Gold

# Simulation Constants
POPULATION_SIZE = 400
INITIAL_INFECTED = 5
AGENT_RADIUS = 4
AGENT_SPEED_BASE = 2.0

# Disease Parameters (SEIR)
INFECTION_RADIUS = 15
INFECTION_PROBABILITY = 0.1   # Chance per frame of contact
INCUBATION_PERIOD_FRAMES = 300 # ~5 seconds before becoming infectious
RECOVERY_TIME_FRAMES = 600    # ~10 seconds
BASE_DEATH_CHANCE = 0.001     # Normal death chance
OVERFLOW_DEATH_CHANCE = 0.01  # Death chance when hospital full

# Vaccination
VACCINATION_EFFICACY = 0.95
VACCINATION_WILLINGNESS = 0.8

# Social / Travel / Time
TRAVEL_CHANCE = 0.002
SOCIAL_WEIGHT = 0.05
DAY_LENGTH_FRAMES = 1200      # 20 seconds per day
NIGHT_START = 800             # When night begins (18:00 equivalent)

# Demographics (Age Multipliers)
# Format: (Speed Mult, Death Mult, Social Mult)
AGE_STATS = {
    'YOUNG': (1.2, 0.1, 1.5),  # Fast, Resilient, Social
    'ADULT': (1.0, 1.0, 1.0),  # Average
    'ELDERLY': (0.6, 5.0, 0.5) # Slow, Vulnerable, Isolated
}

# Intervention Defaults
QUARANTINE_ENABLED = False
SAFE_ZONE_ENABLED = False # New: Shelter for Susceptibles
QUARANTINE_DETECTION_CHANCE = 0.05
QUARANTINE_EXPOSED_DETECTION_CHANCE = 0.02
BORDERS_CLOSED = False

# Economy & Hospital
HOSPITAL_CAPACITY = 50
STARTING_MONEY = 1000         # Reduced from 2000
INCOME_PER_HEALTHY = 0.1      # Reduced from 0.15
COST_QUARANTINE = 10
COST_SAFE_ZONE = 10
COST_BORDERS = 15
COST_VACCINE = 20

# ============================================================================
# INITIALIZATION
# ============================================================================

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Epidemic Simulation: SEIR, Age & Day/Night")
clock = pygame.time.Clock()
font = pygame.font.SysFont(None, 24)
big_font = pygame.font.SysFont(None, 48)

# ============================================================================
# CLASSES
# ============================================================================

class Country:
    def __init__(self, name, rect, color):
        self.name = name
        self.rect = rect
        self.color = color
        # Work/School (Gathering Spot)
        self.gathering_spot = pygame.math.Vector2(
            rect.centerx + random.uniform(-50, 50),
            rect.centery + random.uniform(-50, 50)
        )

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, self.rect, 1)
        name_surf = font.render(self.name, True, self.color)
        surface.blit(name_surf, (self.rect.x + 10, self.rect.y + 10))
        pygame.draw.circle(surface, (150, 150, 150), (int(self.gathering_spot.x), int(self.gathering_spot.y)), 15)
        label = font.render("Work", True, (150, 150, 150))
        surface.blit(label, (self.gathering_spot.x - 15, self.gathering_spot.y - 30))

class Agent:
    def __init__(self, country):
        self.home_country = country
        # Home Position (Where they sleep)
        self.home_pos = pygame.math.Vector2(
            random.uniform(country.rect.left + 10, country.rect.right - 10),
            random.uniform(country.rect.top + 10, country.rect.bottom - 10)
        )
        self.position = self.home_pos.copy()
        
        # Demographics
        r = random.random()
        if r < 0.2: self.age_group = 'YOUNG'
        elif r < 0.8: self.age_group = 'ADULT'
        else: self.age_group = 'ELDERLY'
        
        self.speed_mult, self.death_mult, self.social_mult = AGE_STATS[self.age_group]
        
        angle = random.uniform(0, 2 * math.pi)
        self.velocity = pygame.math.Vector2(math.cos(angle), math.sin(angle)) * AGENT_SPEED_BASE * self.speed_mult
        
        # State (SEIR)
        self.state = "SUSCEPTIBLE" # SUSCEPTIBLE, EXPOSED, INFECTED, RECOVERED, DEAD
        self.days_exposed = 0
        self.days_infected = 0
        self.immunity = 0.0 
        self.in_quarantine = False # In Isolation (Red)
        self.in_safe_zone = False  # In Safe Zone (Blue)
        self.wants_vaccine = random.random() < VACCINATION_WILLINGNESS

    def move(self, bounds_rect, is_night):
        if self.state == "DEAD": return

        target_vector = pygame.math.Vector2(0, 0)

        if not self.in_quarantine and not self.in_safe_zone:
            if is_night:
                # Go Home
                to_home = (self.home_pos - self.position)
                if to_home.length() > 5:
                    target_vector += to_home.normalize() * 0.1 # Strong pull home
            else:
                # Go to Work (Social)
                to_spot = (self.home_country.gathering_spot - self.position)
                if to_spot.length() > 0:
                    target_vector += to_spot.normalize() * SOCIAL_WEIGHT * self.social_mult

        self.velocity += target_vector

        # Random wander noise
        if random.random() < 0.1:
            angle = random.uniform(-0.5, 0.5)
            self.velocity = self.velocity.rotate_rad(angle)
            
        # Normalize speed
        speed = AGENT_SPEED_BASE * self.speed_mult
        if self.velocity.length() > speed:
            self.velocity = self.velocity.normalize() * speed

        self.position += self.velocity

        # Bounce off bounds
        if self.position.x < bounds_rect.left + AGENT_RADIUS:
            self.position.x = bounds_rect.left + AGENT_RADIUS
            self.velocity.x *= -1
        elif self.position.x > bounds_rect.right - AGENT_RADIUS:
            self.position.x = bounds_rect.right - AGENT_RADIUS
            self.velocity.x *= -1
        
        if self.position.y < bounds_rect.top + AGENT_RADIUS:
            self.position.y = bounds_rect.top + AGENT_RADIUS
            self.velocity.y *= -1
        elif self.position.y > bounds_rect.bottom - AGENT_RADIUS:
            self.position.y = bounds_rect.bottom - AGENT_RADIUS
            self.velocity.y *= -1

    def update_health(self, hospital_overflow):
        # Exposed -> Infected
        if self.state == "EXPOSED":
            self.days_exposed += 1
            if self.days_exposed > INCUBATION_PERIOD_FRAMES:
                self.state = "INFECTED"
                self.days_exposed = 0
        
        # Infected -> Recovered/Dead
        elif self.state == "INFECTED":
            self.days_infected += 1
            
            # Death Chance (Age + Hospital)
            base_chance = OVERFLOW_DEATH_CHANCE if hospital_overflow else BASE_DEATH_CHANCE
            chance = base_chance * self.death_mult
            
            if random.random() < chance:
                self.state = "DEAD"
                return

            # Recovery
            if self.days_infected > RECOVERY_TIME_FRAMES:
                self.state = "RECOVERED"
                self.immunity = 1.0
                self.in_quarantine = False
                self.in_safe_zone = False

    def travel(self, countries):
        if self.state == "DEAD" or self.in_quarantine or self.in_safe_zone: return
        
        chance = TRAVEL_CHANCE
        if BORDERS_CLOSED:
            chance *= 0.05 # 5% of normal travel still happens (Smugglers/Leaks)

        # Chance to fly
        if random.random() < chance:
            dest = random.choice(countries)
            if dest != self.home_country:
                self.home_country = dest
                # Teleport
                self.position = pygame.math.Vector2(
                    random.uniform(dest.rect.left + 10, dest.rect.right - 10),
                    random.uniform(dest.rect.top + 10, dest.rect.bottom - 10)
                )
                # New home is temporary (hotel?) - for simplicity, they just move there

    def draw(self, surface):
        if self.state == "DEAD":
            color = COLOR_DEAD
        elif self.state == "INFECTED":
            color = COLOR_INFECTED
        elif self.state == "EXPOSED":
            color = COLOR_EXPOSED
        elif self.state == "RECOVERED":
            color = COLOR_RECOVERED
        else:
            color = COLOR_SUSCEPTIBLE
        
        # Size based on age
        radius = AGENT_RADIUS
        if self.age_group == 'YOUNG': radius = AGENT_RADIUS - 1
        elif self.age_group == 'ELDERLY': radius = AGENT_RADIUS + 1
        
        pygame.draw.circle(surface, color, (int(self.position.x), int(self.position.y)), radius)

class Simulation:
    def __init__(self):
        self.running = True
        self.paused = False
        self.time_of_day = 0 # 0 to DAY_LENGTH_FRAMES
        
        # Economy
        self.money = STARTING_MONEY
        
        # Define Countries
        mid_x, mid_y = WIDTH // 2, HEIGHT // 2
        self.countries = [
            Country("North West", pygame.Rect(0, 0, mid_x, mid_y), (200, 200, 255)),
            Country("North East", pygame.Rect(mid_x, 0, mid_x, mid_y), (255, 200, 200)),
            Country("South West", pygame.Rect(0, mid_y, mid_x, mid_y), (200, 255, 200)),
            Country("South East", pygame.Rect(mid_x, mid_y, mid_x, mid_y), (255, 255, 200))
        ]
        
        # Zones
        q_size = 140
        # Isolation (Red) - Right
        self.quarantine_rect = pygame.Rect(mid_x + 10, mid_y - q_size//2, q_size, q_size)
        # Safe Zone (Blue) - Left
        self.safe_zone_rect = pygame.Rect(mid_x - q_size - 10, mid_y - q_size//2, q_size, q_size)
        
        # Create Agents
        self.agents = []
        for _ in range(POPULATION_SIZE):
            country = random.choice(self.countries)
            self.agents.append(Agent(country))
            
        # Infect Initial Agents
        for _ in range(INITIAL_INFECTED):
            target = random.choice(self.agents)
            target.state = "INFECTED"

        # History
        self.history_susceptible = []
        self.history_exposed = []
        self.history_infected = []
        self.history_recovered = []
        self.history_dead = []
        self.history_new_infections = []
        self.new_infections_counter = 0
        
    def handle_input(self):
        global BORDERS_CLOSED, QUARANTINE_ENABLED, SAFE_ZONE_ENABLED, INFECTION_PROBABILITY
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    self.paused = not self.paused
                elif event.key == pygame.K_b:
                    BORDERS_CLOSED = not BORDERS_CLOSED
                elif event.key == pygame.K_q:
                    QUARANTINE_ENABLED = not QUARANTINE_ENABLED
                elif event.key == pygame.K_s:
                    SAFE_ZONE_ENABLED = not SAFE_ZONE_ENABLED
                elif event.key == pygame.K_v:
                    self.vaccinate_population()
                elif event.key == pygame.K_r:
                    self.__init__() # Reset
                elif event.key == pygame.K_UP:
                    INFECTION_PROBABILITY = min(1.0, INFECTION_PROBABILITY + 0.01)
                elif event.key == pygame.K_DOWN:
                    INFECTION_PROBABILITY = max(0.0, INFECTION_PROBABILITY - 0.01)
                elif event.key == pygame.K_1:
                    self.save_graphs("Scenario_1_Extinction")
                elif event.key == pygame.K_2:
                    self.save_graphs("Scenario_2_Survival")

    def vaccinate_population(self):
        count = 0
        cost = 0
        for agent in self.agents:
            if agent.state == "SUSCEPTIBLE":
                if random.random() < 0.1:
                    if agent.wants_vaccine:
                        cost += COST_VACCINE
                        if random.random() < VACCINATION_EFFICACY:
                            agent.immunity = 1.0
                            agent.state = "RECOVERED"
                            count += 1
        self.money -= cost
        print(f"Vaccinated {count} agents. Cost: ${cost}")

    def update(self):
        global BORDERS_CLOSED, QUARANTINE_ENABLED, SAFE_ZONE_ENABLED
        if self.paused: return
        
        # Time Cycle
        self.time_of_day = (self.time_of_day + 1) % DAY_LENGTH_FRAMES
        is_night = self.time_of_day > NIGHT_START
        
        # Counters
        s, e, i, r, d = 0, 0, 0, 0, 0
        
        infected_agents = [a for a in self.agents if a.state == "INFECTED"]
        hospital_overflow = len(infected_agents) > HOSPITAL_CAPACITY
        
        # Economy & Bankruptcy
        if self.money <= 0:
            # BANKRUPTCY: Services fail!
            if QUARANTINE_ENABLED: QUARANTINE_ENABLED = False
            if SAFE_ZONE_ENABLED: SAFE_ZONE_ENABLED = False
            if BORDERS_CLOSED: BORDERS_CLOSED = False
        
        if QUARANTINE_ENABLED: self.money -= COST_QUARANTINE
        if SAFE_ZONE_ENABLED: self.money -= COST_SAFE_ZONE
        if BORDERS_CLOSED: self.money -= COST_BORDERS
        
        for agent in self.agents:
            # Update Stats
            if agent.state == "SUSCEPTIBLE": 
                s += 1
                self.money += INCOME_PER_HEALTHY
            elif agent.state == "EXPOSED": e += 1
            elif agent.state == "INFECTED": i += 1
            elif agent.state == "RECOVERED": 
                r += 1
                self.money += INCOME_PER_HEALTHY
            elif agent.state == "DEAD": d += 1
            
            if agent.state == "DEAD": continue

            # Movement
            if agent.in_quarantine:
                agent.move(self.quarantine_rect, is_night)
            elif agent.in_safe_zone:
                agent.move(self.safe_zone_rect, is_night)
            else:
                agent.move(agent.home_country.rect, is_night)
                agent.travel(self.countries)

            # Health
            agent.update_health(hospital_overflow)
            
            # Quarantine Logic
            # Quarantine Logic (Isolation for Sick)
            if QUARANTINE_ENABLED and not agent.in_quarantine and not agent.in_safe_zone:
                # Detect Infected
                if agent.state == "INFECTED":
                    if random.random() < QUARANTINE_DETECTION_CHANCE:
                        agent.in_quarantine = True
                        agent.position = pygame.math.Vector2(
                            random.uniform(self.quarantine_rect.left + 10, self.quarantine_rect.right - 10),
                            random.uniform(self.quarantine_rect.top + 10, self.quarantine_rect.bottom - 10)
                        )
                # Detect Exposed (Contact Tracing)
                elif agent.state == "EXPOSED":
                    if random.random() < QUARANTINE_EXPOSED_DETECTION_CHANCE:
                        agent.in_quarantine = True
                        agent.position = pygame.math.Vector2(
                            random.uniform(self.quarantine_rect.left + 10, self.quarantine_rect.right - 10),
                            random.uniform(self.quarantine_rect.top + 10, self.quarantine_rect.bottom - 10)
                        )
            
            # Safe Zone Logic (Shelter for Healthy)
            if SAFE_ZONE_ENABLED and not agent.in_safe_zone and not agent.in_quarantine:
                if agent.state == "SUSCEPTIBLE":
                    if random.random() < 0.05: # Gradual evacuation
                        agent.in_safe_zone = True
                        agent.position = pygame.math.Vector2(
                            random.uniform(self.safe_zone_rect.left + 10, self.safe_zone_rect.right - 10),
                            random.uniform(self.safe_zone_rect.top + 10, self.safe_zone_rect.bottom - 10)
                        )

            # Infection Spread (Only Infected can spread, Exposed cannot)
            if agent.state == "SUSCEPTIBLE":
                for infector in infected_agents:
                    if infector.in_quarantine and not agent.in_quarantine: continue # Isolated can't spread to outside
                    if agent.in_quarantine and not infector.in_quarantine: continue # Outside can't spread to Isolated
                    if agent.in_safe_zone and not infector.in_safe_zone: continue   # Safe Zone is protected
                    if infector.in_safe_zone: continue                              # If infected gets in safe zone (oops), they spread inside!
                    
                    dist = agent.position.distance_to(infector.position)
                    if dist < INFECTION_RADIUS:
                        chance = INFECTION_PROBABILITY * (1.0 - agent.immunity)
                        if random.random() < chance:
                            agent.state = "EXPOSED" # SEIR: Becomes Exposed first
                            self.new_infections_counter += 1
                            break

        # Record History
        self.history_susceptible.append(s)
        self.history_exposed.append(e)
        self.history_infected.append(i)
        self.history_recovered.append(r)
        self.history_dead.append(d)
        self.history_new_infections.append(self.new_infections_counter)
        self.new_infections_counter = 0

    def draw(self):
        # Day/Night Background
        is_night = self.time_of_day > NIGHT_START
        bg = BG_COLOR_NIGHT if is_night else BG_COLOR_DAY
        screen.fill(bg)
        
        # Draw Countries
        for country in self.countries:
            country.draw(screen)
            
        # Draw Quarantine Zone (Isolation)
        if QUARANTINE_ENABLED:
            pygame.draw.rect(screen, COLOR_QUARANTINE, self.quarantine_rect)
            pygame.draw.rect(screen, (255, 0, 0), self.quarantine_rect, 2)
            text = font.render("ISOLATION", True, (255, 100, 100))
            screen.blit(text, (self.quarantine_rect.x + 10, self.quarantine_rect.y - 20))

        # Draw Safe Zone (Shelter)
        if SAFE_ZONE_ENABLED:
            pygame.draw.rect(screen, (0, 0, 50), self.safe_zone_rect)
            pygame.draw.rect(screen, (0, 100, 255), self.safe_zone_rect, 2)
            text = font.render("SAFE ZONE", True, (100, 200, 255))
            screen.blit(text, (self.safe_zone_rect.x + 10, self.safe_zone_rect.y - 20))

        # Draw Agents
        for agent in self.agents:
            agent.draw(screen)
            
        # Draw UI
        self.draw_ui()
        
        pygame.display.flip()

    def draw_ui(self):
        if not self.history_susceptible: return
        
        curr_i = self.history_infected[-1]
        
        # Time Display
        is_night = self.time_of_day > NIGHT_START
        time_str = "NIGHT" if is_night else "DAY"
        time_color = (100, 100, 255) if is_night else (255, 255, 100)
        time_text = big_font.render(time_str, True, time_color)
        screen.blit(time_text, (WIDTH//2 - 50, 10))
        
        # Hospital Bar
        bar_w, bar_h = 200, 20
        bar_x, bar_y = 10, 10
        pygame.draw.rect(screen, (50, 50, 50), (bar_x, bar_y, bar_w, bar_h))
        fill_pct = min(1.0, curr_i / HOSPITAL_CAPACITY)
        fill_w = int(bar_w * fill_pct)
        color = (0, 255, 0) if fill_pct < 0.8 else (255, 0, 0)
        pygame.draw.rect(screen, color, (bar_x, bar_y, fill_w, bar_h))
        pygame.draw.rect(screen, (255, 255, 255), (bar_x, bar_y, bar_w, bar_h), 1)
        
        hosp_text = font.render(f"Hospital: {curr_i}/{HOSPITAL_CAPACITY}", True, (255, 255, 255))
        screen.blit(hosp_text, (bar_x + bar_w + 10, bar_y))
        
        if curr_i > HOSPITAL_CAPACITY:
            warn = font.render("OVERFLOW! DEATH RATE HIGH!", True, (255, 0, 0))
            screen.blit(warn, (bar_x + bar_w + 150, bar_y))

        # Economy
        money_color = COLOR_MONEY if self.money > 0 else (255, 0, 0)
        money_text = big_font.render(f"${int(self.money)}", True, money_color)
        screen.blit(money_text, (WIDTH - 150, 10))
        
        if self.money <= 0:
            bankrupt_text = font.render("BANKRUPT! SERVICES STOPPED!", True, (255, 0, 0))
            screen.blit(bankrupt_text, (WIDTH - 250, 50))

        # Controls & Status Panel
        panel_x = 10
        panel_y = HEIGHT - 240
        
        # Background for panel
        s = pygame.Surface((280, 230))
        s.set_alpha(180)
        s.fill((0, 0, 0))
        screen.blit(s, (panel_x - 5, panel_y - 5))
        
        # Helper to draw text lines
        def draw_line(text, color, y_offset):
            t = font.render(text, True, color)
            screen.blit(t, (panel_x, panel_y + y_offset))

        # Stats
        draw_line(f"Susceptible: {self.history_susceptible[-1]}", COLOR_SUSCEPTIBLE, 0)
        draw_line(f"Exposed: {self.history_exposed[-1]}", COLOR_EXPOSED, 20)
        draw_line(f"Infected: {self.history_infected[-1]}", COLOR_INFECTED, 40)
        draw_line(f"Recovered: {self.history_recovered[-1]}", COLOR_RECOVERED, 60)
        draw_line(f"Dead: {self.history_dead[-1]}", COLOR_DEAD, 80)
        
        # Controls / Status
        y = 110
        draw_line("--- CONTROLS ---", (255, 255, 255), y)
        y += 25
        
        # Borders
        b_status = "CLOSED" if BORDERS_CLOSED else "OPEN"
        b_color = (255, 50, 50) if BORDERS_CLOSED else (50, 255, 50)
        draw_line(f"[B] Borders: {b_status} (-$15)", b_color, y)
        y += 20
        
        # Quarantine
        q_status = "ON" if QUARANTINE_ENABLED else "OFF"
        q_color = (255, 50, 50) if QUARANTINE_ENABLED else (50, 255, 50)
        draw_line(f"[Q] Isolation: {q_status} (-$10)", q_color, y)
        y += 20

        # Safe Zone
        s_status = "ON" if SAFE_ZONE_ENABLED else "OFF"
        s_color = (50, 150, 255) if SAFE_ZONE_ENABLED else (50, 255, 50)
        draw_line(f"[S] Safe Zone: {s_status} (-$10)", s_color, y)
        y += 20
        
        # Actions
        draw_line(f"[V] Vaccinate (-$20)", (255, 255, 200), y)
        y += 20
        draw_line(f"[SPACE] Pause / Resume", (200, 200, 200), y)
        y += 20
        draw_line(f"[R] Reset Simulation", (200, 200, 200), y)
        y += 25
        
        # Save
        draw_line(f"[1] Save Extinction Graph", (150, 150, 255), y)
        y += 20
        draw_line(f"[2] Save Survival Graph", (150, 255, 150), y)

        # Mini Graph
        self.draw_realtime_graph()

    def draw_realtime_graph(self):
        graph_w, graph_h = 300, 150
        graph_x, graph_y = WIDTH - graph_w - 10, HEIGHT - graph_h - 10
        
        s = pygame.Surface((graph_w, graph_h))
        s.set_alpha(100)
        s.fill((0,0,0))
        screen.blit(s, (graph_x, graph_y))
        
        if len(self.history_infected) < 2: return
        
        max_pop = POPULATION_SIZE
        data_len = len(self.history_infected)
        start_idx = max(0, data_len - 500)
        show_len = data_len - start_idx
        
        points_i = []
        points_e = []
        points_d = []
        
        for i in range(show_len):
            idx = start_idx + i
            x = graph_x + (i / max(1, show_len - 1)) * graph_w
            
            y_i = graph_y + graph_h - (self.history_infected[idx] / max_pop) * graph_h
            points_i.append((x, y_i))
            
            y_e = graph_y + graph_h - (self.history_exposed[idx] / max_pop) * graph_h
            points_e.append((x, y_e))
            
            y_d = graph_y + graph_h - (self.history_dead[idx] / max_pop) * graph_h
            points_d.append((x, y_d))
            
        if len(points_i) > 1:
            pygame.draw.lines(screen, COLOR_INFECTED, False, points_i, 2)
        if len(points_e) > 1:
            pygame.draw.lines(screen, COLOR_EXPOSED, False, points_e, 2)
        if len(points_d) > 1:
            pygame.draw.lines(screen, COLOR_DEAD, False, points_d, 2)
            
        pygame.draw.rect(screen, (255, 255, 255), (graph_x, graph_y, graph_w, graph_h), 1)
        title = font.render("Exp(Yel) / Inf(Red) / Dead(Gry)", True, (255, 255, 255))
        screen.blit(title, (graph_x, graph_y - 20))

    def save_graphs(self, filename_prefix="epidemic_results"):
        if not self.history_susceptible: return
        
        plt.figure(figsize=(12, 10))
        
        plt.subplot(2, 1, 1)
        plt.plot(self.history_susceptible, label='Susceptible', color='blue')
        plt.plot(self.history_exposed, label='Exposed', color='orange')
        plt.plot(self.history_infected, label='Infected', color='red')
        plt.plot(self.history_recovered, label='Recovered', color='green')
        plt.plot(self.history_dead, label='Dead', color='gray')
        plt.title(f'Epidemic Model - {filename_prefix}')
        plt.ylabel('Population')
        plt.legend()
        plt.grid(True)
        
        plt.subplot(2, 1, 2)
        smoothed = [sum(self.history_new_infections[max(0, i-10):i+1]) for i in range(len(self.history_new_infections))]
        plt.plot(smoothed, label='New Infections (Rolling 10 frames)', color='orange')
        plt.title('Infection Rate')
        plt.xlabel('Time (Frames)')
        plt.ylabel('New Cases')
        plt.legend()
        plt.grid(True)
        
        os.makedirs('Graphs_For_Project_Two', exist_ok=True)
        path = f'Graphs_For_Project_Two/{filename_prefix}.png'
        plt.savefig(path)
        plt.close()
        print(f"Saved graph to {path}")

    def run(self):
        while self.running:
            clock.tick(FPS)
            self.handle_input()
            self.update()
            self.draw()
        
        # self.save_graphs() # Disabled auto-save as per user request
        pygame.quit()

if __name__ == "__main__":
    Simulation().run()
