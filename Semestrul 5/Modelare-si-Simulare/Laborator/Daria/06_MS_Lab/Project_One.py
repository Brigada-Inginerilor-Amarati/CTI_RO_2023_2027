import pygame
import random
import math
import os
import matplotlib.pyplot as plt
from collections import deque

# ============================================================================
# SIMULATION PARAMETERS
# ============================================================================

# Screen dimensions
WIDTH, HEIGHT = 800, 600
FPS = 60

# Colors
BACKGROUND_COLOR = (30, 30, 30)
PREY_COLOR = (0, 255, 0)
PREDATOR_COLOR = (255, 0, 0)
FOOD_COLOR = (255, 255, 0)
OBSTACLE_COLOR = (128, 128, 128)
TEXT_COLOR = (200, 200, 200)

# Initial Counts
INITIAL_PREY = 50
INITIAL_PREDATORS = 2
INITIAL_FOOD = 20
INITIAL_OBSTACLES = 5

# Agent Physics
PREY_SPEED = 2.0
PREDATOR_SPEED = 2.6
PREY_VISION_RADIUS = 50
PREDATOR_VISION_RADIUS = 100
OBSTACLE_RADIUS = 30
FOOD_RADIUS = 3

# Energy System
ENERGY_LIFETIME_FRAMES = 1500  # How many frames energy lasts without food
MAX_ENERGY = 100.0
ENERGY_LOSS_RATE = MAX_ENERGY / ENERGY_LIFETIME_FRAMES
FOOD_ENERGY_GAIN = 30.0
PREDATOR_PREY_ENERGY_GAIN = 50.0
LOW_ENERGY_THRESHOLD = 40.0  # Below this, prey prioritizes food

# Reproduction System
REPRODUCTION_ENERGY_THRESHOLD = 80.0
REPRODUCTION_COOLDOWN_FRAMES = 200
MATING_DURATION_FRAMES = 60
MATING_DISTANCE = 20.0

# Flocking Behavior (Boids)
FLOCKING_ENABLED = True
FLOCKING_RADIUS = 50
ALIGNMENT_WEIGHT = 0.5
COHESION_WEIGHT = 0.3
SEPARATION_WEIGHT = 0.8
FLOCK_SPEED_BOOST = 0.05  # Speed increase per neighbor

# Food Spawning
FOOD_SPAWN_CHANCE = 0.05  # Chance per frame to spawn new food

# History Tracking
HISTORY_MAX_LEN = 1000

# ============================================================================
# INITIALIZATION
# ============================================================================

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Advanced Predator-Prey Simulation")
clock = pygame.time.Clock()
font = pygame.font.SysFont(None, 24)

# ============================================================================
# CLASSES
# ============================================================================

class Food:
    def __init__(self, x=None, y=None):
        self.position = pygame.math.Vector2(
            x if x is not None else random.uniform(0, WIDTH),
            y if y is not None else random.uniform(0, HEIGHT)
        )
        self.radius = FOOD_RADIUS

    def draw(self):
        pygame.draw.circle(screen, FOOD_COLOR, (int(self.position.x), int(self.position.y)), self.radius)

class Obstacle:
    def __init__(self, x=None, y=None):
        self.position = pygame.math.Vector2(
            x if x is not None else random.uniform(0, WIDTH),
            y if y is not None else random.uniform(0, HEIGHT)
        )
        self.radius = OBSTACLE_RADIUS

    def draw(self):
        pygame.draw.circle(screen, OBSTACLE_COLOR, (int(self.position.x), int(self.position.y)), self.radius)

class Agent:
    def __init__(self, x=None, y=None, speed=2.0, color=PREY_COLOR):
        self.position = pygame.math.Vector2(
            x if x is not None else random.uniform(0, WIDTH),
            y if y is not None else random.uniform(0, HEIGHT)
        )
        angle = random.uniform(0, 2 * math.pi)
        self.velocity = pygame.math.Vector2(math.cos(angle), math.sin(angle))
        self.base_speed = speed
        self.speed = speed
        self.color = color
        self.radius = 4  # Default radius for collision
        self.energy = MAX_ENERGY
        self.trail = []
        self.reproduction_cooldown = 0
        self.mating_timer = 0
        self.mating_partner = None
        self.alive = True

    def update_energy(self):
        self.energy -= ENERGY_LOSS_RATE
        if self.energy <= 0:
            self.alive = False

    def check_bounds(self):
        if self.position.x < 0 or self.position.x > WIDTH:
            self.velocity.x *= -1
            self.position.x = max(0, min(self.position.x, WIDTH))
        if self.position.y < 0 or self.position.y > HEIGHT:
            self.velocity.y *= -1
            self.position.y = max(0, min(self.position.y, HEIGHT))

    def update_trail(self):
        self.trail.append(self.position.copy())
        if len(self.trail) > 10:
            self.trail.pop(0)

    def draw_trail(self):
        if len(self.trail) > 1:
            pygame.draw.lines(screen, self.color, False, [(int(p.x), int(p.y)) for p in self.trail], 1)

    def avoid_obstacles(self, obstacles):
        for obs in obstacles:
            dist = self.position.distance_to(obs.position)
            if dist < obs.radius + 30: # Avoidance radius
                avoid_dir = (self.position - obs.position).normalize()
                self.velocity += avoid_dir * 0.5 # Strength of avoidance

class Prey(Agent):
    def __init__(self, x=None, y=None):
        super().__init__(x, y, PREY_SPEED, PREY_COLOR)
        self.vision_radius = PREY_VISION_RADIUS

    def update(self, predators, food_list, prey_list, obstacles):
        if not self.alive: return

        self.update_energy()
        if self.reproduction_cooldown > 0:
            self.reproduction_cooldown -= 1

        # Mating State
        if self.mating_timer > 0:
            self.mating_timer -= 1
            if self.mating_timer == 0:
                # Reproduction happens in Simulation loop
                pass
            return # Stop moving while mating

        # 1. Flee from Predators (High Priority)
        nearest_predator = None
        min_dist = self.vision_radius
        for p in predators:
            d = self.position.distance_to(p.position)
            if d < min_dist:
                min_dist = d
                nearest_predator = p
        
        if nearest_predator:
            flee_dir = (self.position - nearest_predator.position).normalize()
            self.velocity += flee_dir * 0.5 # Steer away

        # 2. Seek Food (If hungry)
        elif self.energy < LOW_ENERGY_THRESHOLD:
            nearest_food = None
            min_food_dist = float('inf')
            for f in food_list:
                d = self.position.distance_to(f.position)
                if d < min_food_dist:
                    min_food_dist = d
                    nearest_food = f
            
            if nearest_food:
                seek_dir = (nearest_food.position - self.position).normalize()
                self.velocity += seek_dir * 0.3

        # 3. Seek Mate (If high energy)
        elif self.energy > REPRODUCTION_ENERGY_THRESHOLD and self.reproduction_cooldown == 0:
            nearest_mate = None
            min_mate_dist = self.vision_radius
            for mate in prey_list:
                if mate is not self and mate.energy > REPRODUCTION_ENERGY_THRESHOLD and mate.reproduction_cooldown == 0 and mate.mating_partner is None:
                    d = self.position.distance_to(mate.position)
                    if d < min_mate_dist:
                        min_mate_dist = d
                        nearest_mate = mate
            
            if nearest_mate:
                seek_dir = (nearest_mate.position - self.position).normalize()
                self.velocity += seek_dir * 0.3
                
                if self.position.distance_to(nearest_mate.position) < MATING_DISTANCE:
                    # Start Mating
                    self.mating_timer = MATING_DURATION_FRAMES
                    nearest_mate.mating_timer = MATING_DURATION_FRAMES
                    self.mating_partner = nearest_mate
                    nearest_mate.mating_partner = self

        # 4. Flocking
        if FLOCKING_ENABLED:
            self.apply_flocking(prey_list)

        # 5. Obstacle Avoidance
        self.avoid_obstacles(obstacles)

        # Normalize velocity
        if self.velocity.length() > 0:
            self.velocity = self.velocity.normalize()

        self.position += self.velocity * self.speed
        self.check_bounds()
        self.update_trail()

    def apply_flocking(self, prey_list):
        alignment = pygame.math.Vector2(0, 0)
        cohesion = pygame.math.Vector2(0, 0)
        separation = pygame.math.Vector2(0, 0)
        total = 0
        
        for other in prey_list:
            if other is not self:
                d = self.position.distance_to(other.position)
                if d < FLOCKING_RADIUS:
                    alignment += other.velocity
                    cohesion += other.position
                    diff = self.position - other.position
                    if d > 0:
                        separation += diff.normalize() / d
                    total += 1
        
        if total > 0:
            if alignment.length() > 0:
                alignment = alignment.normalize() * ALIGNMENT_WEIGHT
            
            center_mass = cohesion / total
            cohesion_vec = center_mass - self.position
            if cohesion_vec.length() > 0:
                cohesion = cohesion_vec.normalize() * COHESION_WEIGHT
            else:
                cohesion = pygame.math.Vector2(0, 0)
            
            if separation.length() > 0:
                separation = separation.normalize() * SEPARATION_WEIGHT
            
            self.velocity += alignment + cohesion + separation
            self.speed = self.base_speed + (total * FLOCK_SPEED_BOOST)
        else:
            self.speed = self.base_speed

    def draw(self):
        self.draw_trail()
        # Color fades with energy
        energy_factor = max(0.2, self.energy / MAX_ENERGY)
        color = (int(self.color[0] * energy_factor), int(self.color[1] * energy_factor), int(self.color[2] * energy_factor))
        pygame.draw.circle(screen, color, (int(self.position.x), int(self.position.y)), 4)

class Predator(Agent):
    def __init__(self, x=None, y=None):
        super().__init__(x, y, PREDATOR_SPEED, PREDATOR_COLOR)
        self.vision_radius = PREDATOR_VISION_RADIUS

    def update(self, prey_list, predator_list, obstacles):
        if not self.alive: return
        
        self.update_energy()
        if self.reproduction_cooldown > 0:
            self.reproduction_cooldown -= 1

        if self.mating_timer > 0:
            self.mating_timer -= 1
            return

        # 1. Hunt Prey
        nearest_prey = None
        min_dist = self.vision_radius
        for p in prey_list:
            d = self.position.distance_to(p.position)
            if d < min_dist:
                min_dist = d
                nearest_prey = p
        
        if nearest_prey:
            hunt_dir = (nearest_prey.position - self.position).normalize()
            self.velocity += hunt_dir * 0.4
        
        # 2. Seek Mate
        elif self.energy > REPRODUCTION_ENERGY_THRESHOLD and self.reproduction_cooldown == 0:
             nearest_mate = None
             min_mate_dist = self.vision_radius
             for mate in predator_list:
                if mate is not self and mate.energy > REPRODUCTION_ENERGY_THRESHOLD and mate.reproduction_cooldown == 0 and mate.mating_partner is None:
                    d = self.position.distance_to(mate.position)
                    if d < min_mate_dist:
                        min_mate_dist = d
                        nearest_mate = mate
            
             if nearest_mate:
                seek_dir = (nearest_mate.position - self.position).normalize()
                self.velocity += seek_dir * 0.3
                if self.position.distance_to(nearest_mate.position) < MATING_DISTANCE:
                    self.mating_timer = MATING_DURATION_FRAMES
                    nearest_mate.mating_timer = MATING_DURATION_FRAMES
                    self.mating_partner = nearest_mate
                    nearest_mate.mating_partner = self

        # 3. Obstacle Avoidance
        self.avoid_obstacles(obstacles)

        if self.velocity.length() > 0:
            self.velocity = self.velocity.normalize()
            
        self.position += self.velocity * self.speed
        self.check_bounds()
        self.update_trail()

    def draw(self):
        self.draw_trail()
        angle = self.velocity.angle_to(pygame.math.Vector2(1, 0))
        point_list = [
            pygame.math.Vector2(10, 0),
            pygame.math.Vector2(-5, -5),
            pygame.math.Vector2(-5, 5),
        ]
        rotated_points = [self.position + p.rotate(-angle) for p in point_list]
        
        energy_factor = max(0.2, self.energy / MAX_ENERGY)
        color = (int(self.color[0] * energy_factor), int(self.color[1] * energy_factor), int(self.color[2] * energy_factor))
        
        pygame.draw.polygon(screen, color, rotated_points)


# ============================================================================
# SIMULATION CLASS
# ============================================================================

class Simulation:
    def __init__(self):
        self.prey_list = [Prey() for _ in range(INITIAL_PREY)]
        self.predator_list = [Predator() for _ in range(INITIAL_PREDATORS)]
        self.food_list = [Food() for _ in range(INITIAL_FOOD)]
        self.obstacles = [Obstacle() for _ in range(INITIAL_OBSTACLES)]
        self.running = True
        self.show_overlay = False
        
        # History (Unlimited)
        self.history_prey = []
        self.history_predator = []
        self.history_prey_births = []
        self.history_predator_births = []
        self.timestep = 0
        self.prey_births = 0
        self.predator_births = 0

    def spawn_child(self, parent1, parent2, agent_list, type_class):
        child = type_class()
        child.position = (parent1.position + parent2.position) / 2
        child.energy = MAX_ENERGY
        agent_list.append(child)
        
        parent1.reproduction_cooldown = REPRODUCTION_COOLDOWN_FRAMES
        parent2.reproduction_cooldown = REPRODUCTION_COOLDOWN_FRAMES
        parent1.mating_partner = None
        parent2.mating_partner = None
        
        if type_class == Prey:
            self.prey_births += 1
        else:
            self.predator_births += 1

    def run(self):
        global FLOCKING_ENABLED, FOOD_SPAWN_CHANCE, ENERGY_LOSS_RATE
        
        while self.running:
            clock.tick(FPS)
            screen.fill(BACKGROUND_COLOR)
            
            # Event Handling
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_p:
                        self.prey_list.append(Prey())
                    elif event.key == pygame.K_o:
                        self.predator_list.append(Predator())
                    elif event.key == pygame.K_f:
                        self.food_list.append(Food())
                    elif event.key == pygame.K_b:
                        self.obstacles.append(Obstacle())
                    elif event.key == pygame.K_1:
                        FLOCKING_ENABLED = not FLOCKING_ENABLED
                    elif event.key == pygame.K_2:
                        FOOD_SPAWN_CHANCE = min(1.0, FOOD_SPAWN_CHANCE + 0.01)
                    elif event.key == pygame.K_3:
                        FOOD_SPAWN_CHANCE = max(0.0, FOOD_SPAWN_CHANCE - 0.01)
                    elif event.key == pygame.K_4:
                        ENERGY_LOSS_RATE *= 1.1
                    elif event.key == pygame.K_5:
                        ENERGY_LOSS_RATE *= 0.9
                    elif event.key == pygame.K_g:
                        self.show_graphs()
                    elif event.key == pygame.K_h:
                        self.show_overlay = not self.show_overlay

            # Update Simulation
            self.timestep += 1
            self.prey_births = 0
            self.predator_births = 0

            # Spawn Food
            if random.random() < FOOD_SPAWN_CHANCE:
                self.food_list.append(Food())

            # Update Prey
            for prey in self.prey_list[:]:
                prey.update(self.predator_list, self.food_list, self.prey_list, self.obstacles)
                if not prey.alive:
                    self.prey_list.remove(prey)
                    continue
                
                # Eat Food
                for food in self.food_list[:]:
                    if prey.position.distance_to(food.position) < prey.radius + food.radius:
                        prey.energy = min(MAX_ENERGY, prey.energy + FOOD_ENERGY_GAIN)
                        self.food_list.remove(food)
                
                # Reproduction Check (End of mating)
                if prey.mating_timer == 1 and prey.mating_partner:
                     # Only one parent needs to trigger birth
                     if prey.mating_partner in self.prey_list:
                         self.spawn_child(prey, prey.mating_partner, self.prey_list, Prey)

            # Update Predators
            for predator in self.predator_list[:]:
                predator.update(self.prey_list, self.predator_list, self.obstacles)
                if not predator.alive:
                    self.predator_list.remove(predator)
                    continue

                # Eat Prey
                for prey in self.prey_list[:]:
                    if predator.position.distance_to(prey.position) < 10: # Catch distance
                        predator.energy = min(MAX_ENERGY, predator.energy + PREDATOR_PREY_ENERGY_GAIN)
                        self.prey_list.remove(prey)
                
                # Reproduction Check
                if predator.mating_timer == 1 and predator.mating_partner:
                    if predator.mating_partner in self.predator_list:
                        self.spawn_child(predator, predator.mating_partner, self.predator_list, Predator)

            # Record History
            self.history_prey.append(len(self.prey_list))
            self.history_predator.append(len(self.predator_list))
            self.history_prey_births.append(self.prey_births)
            self.history_predator_births.append(self.predator_births)

            # Draw Everything
            for obs in self.obstacles: obs.draw()
            for food in self.food_list: food.draw()
            for prey in self.prey_list: prey.draw()
            for pred in self.predator_list: pred.draw()
            
            self.draw_ui()
            if self.show_overlay:
                self.draw_realtime_graphs()
                
            pygame.display.flip()

        self.save_graphs()
        pygame.quit()

    def draw_ui(self):
        stats = [
            f"Prey: {len(self.prey_list)} | Predator: {len(self.predator_list)}",
            f"Food: {len(self.food_list)} | Obstacles: {len(self.obstacles)}",
            f"Flocking: {'ON' if FLOCKING_ENABLED else 'OFF'} (Toggle: 1)",
            f"Food Rate: {FOOD_SPAWN_CHANCE:.2f} (+/-: 2/3)",
            f"Energy Loss: {ENERGY_LOSS_RATE:.3f} (+/-: 4/5)",
            "Controls: P/O/F/B (Add), G (Graphs), H (Overlay)"
        ]
        for i, line in enumerate(stats):
            text = font.render(line, True, TEXT_COLOR)
            screen.blit(text, (10, 10 + i * 20))

    def draw_realtime_graphs(self):
        # Overlay dimensions
        graph_w, graph_h = 300, 150
        graph_x, graph_y = WIDTH - graph_w - 10, HEIGHT - graph_h - 10
        
        # Background
        s = pygame.Surface((graph_w, graph_h))
        s.set_alpha(128)
        s.fill((0, 0, 0))
        screen.blit(s, (graph_x, graph_y))
        
        # Title
        title = font.render("Real-time Population", True, (255, 255, 255))
        screen.blit(title, (graph_x + 5, graph_y + 5))
        
        # Draw lines
        if len(self.history_prey) < 2: return
        
        # Normalize data to fit graph
        max_pop = max(max(self.history_prey), max(self.history_predator), 1)
        
        points_prey = []
        points_pred = []
        
        # Show last 500 frames in overlay
        start_idx = max(0, len(self.history_prey) - 500)
        data_len = len(self.history_prey) - start_idx
        
        for i in range(data_len):
            idx = start_idx + i
            x = graph_x + (i / max(1, data_len - 1)) * graph_w
            
            y_prey = graph_y + graph_h - (self.history_prey[idx] / max_pop) * graph_h
            points_prey.append((x, y_prey))
            
            y_pred = graph_y + graph_h - (self.history_predator[idx] / max_pop) * graph_h
            points_pred.append((x, y_pred))
            
        if len(points_prey) > 1:
            pygame.draw.lines(screen, PREY_COLOR, False, points_prey, 2)
        if len(points_pred) > 1:
            pygame.draw.lines(screen, PREDATOR_COLOR, False, points_pred, 2)
            
        # Border
        pygame.draw.rect(screen, (255, 255, 255), (graph_x, graph_y, graph_w, graph_h), 1)

    def save_graphs(self):
        plt.figure(figsize=(12, 8))
        
        plt.subplot(2, 1, 1)
        plt.plot(self.history_prey, label='Prey', color='green')
        plt.plot(self.history_predator, label='Predator', color='red')
        plt.title('Population History (Full)')
        plt.xlabel('Timestep')
        plt.ylabel('Count')
        plt.legend()
        plt.grid(True)
        
        plt.subplot(2, 1, 2)
        plt.plot(self.history_prey_births, label='Prey Births', color='green', alpha=0.5)
        plt.plot(self.history_predator_births, label='Predator Births', color='red', alpha=0.5)
        plt.title('Birth Events History (Full)')
        plt.xlabel('Timestep')
        plt.ylabel('Births')
        plt.legend()
        plt.grid(True)
        
        plt.tight_layout()
        os.makedirs('Graphs_For_Project_one', exist_ok=True)
        filename = 'Graphs_For_Project_one/Simulation_graphs.png'
        plt.savefig(filename)
        print(f"Graphs saved to {filename}")
        plt.close()

    def show_graphs(self):
        plt.figure(figsize=(10, 6))
        
        plt.subplot(2, 1, 1)
        plt.plot(self.history_prey, label='Prey', color='green')
        plt.plot(self.history_predator, label='Predator', color='red')
        plt.title('Population Over Time')
        plt.legend()
        
        plt.subplot(2, 1, 2)
        plt.plot(self.history_prey_births, label='Prey Births', color='green', alpha=0.5)
        plt.plot(self.history_predator_births, label='Predator Births', color='red', alpha=0.5)
        plt.title('Birth Events')
        plt.legend()
        
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    Simulation().run()
