import pygame
import random
import math
import os
import matplotlib.pyplot as plt
from dataclasses import dataclass
from typing import List, Optional, Tuple

# ============================================================================
# CONFIGURATION CONSTANTS
# ============================================================================

# Display Settings
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
FRAMES_PER_SECOND = 60

# Color Palette
BG_COLOR = (25, 25, 35)
HERBIVORE_COLOR = (50, 200, 100)
CARNIVORE_COLOR = (220, 50, 50)
NUTRIENT_COLOR = (255, 200, 0)
BARRIER_COLOR = (100, 100, 120)
UI_TEXT_COLOR = (220, 220, 220)

# Starting Population
STARTING_HERBIVORES = 45
STARTING_CARNIVORES = 4
STARTING_NUTRIENTS = 25
STARTING_BARRIERS = 6

# Movement Parameters
HERBIVORE_BASE_VELOCITY = 1.8
CARNIVORE_BASE_VELOCITY = 2.4
HERBIVORE_DETECTION_RANGE = 55
CARNIVORE_DETECTION_RANGE = 95
BARRIER_SIZE = 32
NUTRIENT_SIZE = 4

# Vitality System
VITALITY_CAP = 100.0
VITALITY_DECAY_PER_FRAME = 0.067  # Decay rate
NUTRIENT_VITALITY_BOOST = 32.0
CARNIVORE_HUNT_VITALITY_BOOST = 55.0
HUNGER_LEVEL = 35.0  # When herbivores actively seek food

# Breeding System
BREEDING_VITALITY_REQUIREMENT = 75.0
BREEDING_REST_PERIOD = 180
COURTSHIP_TIME = 50
COURTSHIP_PROXIMITY = 18.0

# Group Behavior (Boids Algorithm)
GROUP_BEHAVIOR_ACTIVE = True
NEIGHBORHOOD_RADIUS = 55
STEER_ALIGNMENT = 0.4
STEER_COHESION = 0.35
STEER_SEPARATION = 0.75
GROUP_VELOCITY_BONUS = 0.04

# Nutrient Generation
NUTRIENT_SPAWN_PROBABILITY = 0.04

# ============================================================================
# PYGAME SETUP
# ============================================================================

pygame.init()
display = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Ecosystem Dynamics Simulator")
timer = pygame.time.Clock()
text_renderer = pygame.font.SysFont('Arial', 22)

# ============================================================================
# DATA STRUCTURES
# ============================================================================

@dataclass
class Vector2D:
    """Custom 2D vector for position and velocity"""
    x: float
    y: float
    
    def __add__(self, other):
        return Vector2D(self.x + other.x, self.y + other.y)
    
    def __sub__(self, other):
        return Vector2D(self.x - other.x, self.y - other.y)
    
    def __mul__(self, scalar):
        return Vector2D(self.x * scalar, self.y * scalar)
    
    def __truediv__(self, scalar):
        return Vector2D(self.x / scalar, self.y / scalar)
    
    def magnitude(self):
        return math.sqrt(self.x * self.x + self.y * self.y)
    
    def normalize(self):
        mag = self.magnitude()
        if mag > 0:
            return Vector2D(self.x / mag, self.y / mag)
        return Vector2D(0, 0)
    
    def distance_to(self, other):
        dx = self.x - other.x
        dy = self.y - other.y
        return math.sqrt(dx * dx + dy * dy)
    
    def to_tuple(self):
        return (int(self.x), int(self.y))

class Nutrient:
    """Food resource that herbivores consume"""
    def __init__(self, pos: Optional[Vector2D] = None):
        self.pos = pos if pos else Vector2D(
            random.uniform(0, SCREEN_WIDTH),
            random.uniform(0, SCREEN_HEIGHT)
        )
        self.size = NUTRIENT_SIZE
    
    def render(self):
        pygame.draw.circle(display, NUTRIENT_COLOR, self.pos.to_tuple(), self.size)

class Barrier:
    """Static obstacles in the environment"""
    def __init__(self, pos: Optional[Vector2D] = None):
        self.pos = pos if pos else Vector2D(
            random.uniform(0, SCREEN_WIDTH),
            random.uniform(0, SCREEN_HEIGHT)
        )
        self.size = BARRIER_SIZE
    
    def render(self):
        pygame.draw.circle(display, BARRIER_COLOR, self.pos.to_tuple(), self.size)

class Creature:
    """Base class for all moving agents"""
    def __init__(self, pos: Optional[Vector2D], base_velocity: float, color: Tuple[int, int, int]):
        self.pos = pos if pos else Vector2D(
            random.uniform(0, SCREEN_WIDTH),
            random.uniform(0, SCREEN_HEIGHT)
        )
        angle = random.uniform(0, 2 * math.pi)
        self.vel = Vector2D(math.cos(angle), math.sin(angle))
        self.base_velocity = base_velocity
        self.current_velocity = base_velocity
        self.color = color
        self.size = 5
        self.vitality = VITALITY_CAP
        self.movement_history = []
        self.breeding_cooldown = 0
        self.courtship_counter = 0
        self.partner = None
        self.is_alive = True
    
    def reduce_vitality(self):
        """Decrease vitality over time"""
        self.vitality -= VITALITY_DECAY_PER_FRAME
        if self.vitality <= 0:
            self.is_alive = False
    
    def enforce_boundaries(self):
        """Bounce off screen edges"""
        if self.pos.x < 0 or self.pos.x > SCREEN_WIDTH:
            self.vel.x *= -1
            self.pos.x = max(0, min(self.pos.x, SCREEN_WIDTH))
        if self.pos.y < 0 or self.pos.y > SCREEN_HEIGHT:
            self.vel.y *= -1
            self.pos.y = max(0, min(self.pos.y, SCREEN_HEIGHT))
    
    def record_position(self):
        """Track movement for visualization"""
        self.movement_history.append(Vector2D(self.pos.x, self.pos.y))
        if len(self.movement_history) > 12:
            self.movement_history.pop(0)
    
    def draw_path(self):
        """Visualize movement trail"""
        if len(self.movement_history) > 1:
            points = [p.to_tuple() for p in self.movement_history]
            pygame.draw.lines(display, self.color, False, points, 1)
    
    def evade_barriers(self, barriers: List[Barrier]):
        """Steer away from obstacles"""
        for barrier in barriers:
            dist = self.pos.distance_to(barrier.pos)
            if dist < barrier.size + 25:
                avoidance = (self.pos - barrier.pos).normalize()
                self.vel = self.vel + avoidance * 0.4

class Herbivore(Creature):
    """Prey species that feeds on nutrients"""
    def __init__(self, pos: Optional[Vector2D] = None):
        super().__init__(pos, HERBIVORE_BASE_VELOCITY, HERBIVORE_COLOR)
        self.detection_range = HERBIVORE_DETECTION_RANGE
    
    def update_behavior(self, carnivores: List['Carnivore'], nutrients: List[Nutrient], 
                       herbivores: List['Herbivore'], barriers: List[Barrier]):
        """Main behavior update loop"""
        if not self.is_alive:
            return
        
        self.reduce_vitality()
        if self.breeding_cooldown > 0:
            self.breeding_cooldown -= 1
        
        # Courtship state - pause movement
        if self.courtship_counter > 0:
            self.courtship_counter -= 1
            return
        
        # Priority 1: Escape from predators
        closest_carnivore = None
        min_carnivore_dist = self.detection_range
        for carn in carnivores:
            dist = self.pos.distance_to(carn.pos)
            if dist < min_carnivore_dist:
                min_carnivore_dist = dist
                closest_carnivore = carn
        
        if closest_carnivore:
            escape_direction = (self.pos - closest_carnivore.pos).normalize()
            self.vel = self.vel + escape_direction * 0.45
        
        # Priority 2: Forage when hungry
        elif self.vitality < HUNGER_LEVEL:
            closest_nutrient = None
            min_nutrient_dist = float('inf')
            for nut in nutrients:
                dist = self.pos.distance_to(nut.pos)
                if dist < min_nutrient_dist:
                    min_nutrient_dist = dist
                    closest_nutrient = nut
            
            if closest_nutrient:
                approach_direction = (closest_nutrient.pos - self.pos).normalize()
                self.vel = self.vel + approach_direction * 0.25
        
        # Priority 3: Seek mate when healthy
        elif self.vitality > BREEDING_VITALITY_REQUIREMENT and self.breeding_cooldown == 0:
            closest_mate = None
            min_mate_dist = self.detection_range
            for mate in herbivores:
                if (mate is not self and 
                    mate.vitality > BREEDING_VITALITY_REQUIREMENT and 
                    mate.breeding_cooldown == 0 and 
                    mate.partner is None):
                    dist = self.pos.distance_to(mate.pos)
                    if dist < min_mate_dist:
                        min_mate_dist = dist
                        closest_mate = mate
            
            if closest_mate:
                approach_direction = (closest_mate.pos - self.pos).normalize()
                self.vel = self.vel + approach_direction * 0.28
                
                if self.pos.distance_to(closest_mate.pos) < COURTSHIP_PROXIMITY:
                    # Begin courtship
                    self.courtship_counter = COURTSHIP_TIME
                    closest_mate.courtship_counter = COURTSHIP_TIME
                    self.partner = closest_mate
                    closest_mate.partner = self
        
        # Priority 4: Group behavior
        if GROUP_BEHAVIOR_ACTIVE:
            self.apply_group_dynamics(herbivores)
        
        # Priority 5: Barrier avoidance
        self.evade_barriers(barriers)
        
        # Normalize and apply movement
        if self.vel.magnitude() > 0:
            self.vel = self.vel.normalize()
        
        self.pos = self.pos + self.vel * self.current_velocity
        self.enforce_boundaries()
        self.record_position()
    
    def apply_group_dynamics(self, herbivores: List['Herbivore']):
        """Implement boids flocking algorithm"""
        align_force = Vector2D(0, 0)
        cohesion_force = Vector2D(0, 0)
        separation_force = Vector2D(0, 0)
        neighbor_count = 0
        
        for other in herbivores:
            if other is not self:
                dist = self.pos.distance_to(other.pos)
                if dist < NEIGHBORHOOD_RADIUS:
                    align_force = align_force + other.vel
                    cohesion_force = cohesion_force + other.pos
                    diff = self.pos - other.pos
                    if dist > 0:
                        separation_force = separation_force + (diff.normalize() / dist)
                    neighbor_count += 1
        
        if neighbor_count > 0:
            if align_force.magnitude() > 0:
                align_force = align_force.normalize() * STEER_ALIGNMENT
            
            center = cohesion_force / neighbor_count
            cohesion_vec = center - self.pos
            if cohesion_vec.magnitude() > 0:
                cohesion_force = cohesion_vec.normalize() * STEER_COHESION
            else:
                cohesion_force = Vector2D(0, 0)
            
            if separation_force.magnitude() > 0:
                separation_force = separation_force.normalize() * STEER_SEPARATION
            
            self.vel = self.vel + align_force + cohesion_force + separation_force
            self.current_velocity = self.base_velocity + (neighbor_count * GROUP_VELOCITY_BONUS)
        else:
            self.current_velocity = self.base_velocity
    
    def render(self):
        """Draw the herbivore"""
        self.draw_path()
        vitality_ratio = max(0.25, self.vitality / VITALITY_CAP)
        shade = (
            int(self.color[0] * vitality_ratio),
            int(self.color[1] * vitality_ratio),
            int(self.color[2] * vitality_ratio)
        )
        pygame.draw.circle(display, shade, self.pos.to_tuple(), self.size)

class Carnivore(Creature):
    """Predator species that hunts herbivores"""
    def __init__(self, pos: Optional[Vector2D] = None):
        super().__init__(pos, CARNIVORE_BASE_VELOCITY, CARNIVORE_COLOR)
        self.detection_range = CARNIVORE_DETECTION_RANGE
    
    def update_behavior(self, herbivores: List[Herbivore], carnivores: List['Carnivore'], 
                       barriers: List[Barrier]):
        """Main behavior update loop"""
        if not self.is_alive:
            return
        
        self.reduce_vitality()
        if self.breeding_cooldown > 0:
            self.breeding_cooldown -= 1
        
        if self.courtship_counter > 0:
            self.courtship_counter -= 1
            return
        
        # Priority 1: Hunt herbivores
        closest_herbivore = None
        min_herbivore_dist = self.detection_range
        for herb in herbivores:
            dist = self.pos.distance_to(herb.pos)
            if dist < min_herbivore_dist:
                min_herbivore_dist = dist
                closest_herbivore = herb
        
        if closest_herbivore:
            pursuit_direction = (closest_herbivore.pos - self.pos).normalize()
            self.vel = self.vel + pursuit_direction * 0.35
        
        # Priority 2: Seek mate
        elif self.vitality > BREEDING_VITALITY_REQUIREMENT and self.breeding_cooldown == 0:
            closest_mate = None
            min_mate_dist = self.detection_range
            for mate in carnivores:
                if (mate is not self and 
                    mate.vitality > BREEDING_VITALITY_REQUIREMENT and 
                    mate.breeding_cooldown == 0 and 
                    mate.partner is None):
                    dist = self.pos.distance_to(mate.pos)
                    if dist < min_mate_dist:
                        min_mate_dist = dist
                        closest_mate = mate
            
            if closest_mate:
                approach_direction = (closest_mate.pos - self.pos).normalize()
                self.vel = self.vel + approach_direction * 0.28
                if self.pos.distance_to(closest_mate.pos) < COURTSHIP_PROXIMITY:
                    self.courtship_counter = COURTSHIP_TIME
                    closest_mate.courtship_counter = COURTSHIP_TIME
                    self.partner = closest_mate
                    closest_mate.partner = self
        
        # Priority 3: Barrier avoidance
        self.evade_barriers(barriers)
        
        if self.vel.magnitude() > 0:
            self.vel = self.vel.normalize()
        
        self.pos = self.pos + self.vel * self.current_velocity
        self.enforce_boundaries()
        self.record_position()
    
    def render(self):
        """Draw the carnivore as a triangle pointing in direction of movement"""
        self.draw_path()
        angle = math.atan2(self.vel.y, self.vel.x)
        triangle_points = [
            Vector2D(12, 0),
            Vector2D(-6, -6),
            Vector2D(-6, 6),
        ]
        rotated_points = []
        for point in triangle_points:
            rotated_x = point.x * math.cos(angle) - point.y * math.sin(angle)
            rotated_y = point.x * math.sin(angle) + point.y * math.cos(angle)
            rotated_points.append((self.pos + Vector2D(rotated_x, rotated_y)).to_tuple())
        
        vitality_ratio = max(0.25, self.vitality / VITALITY_CAP)
        shade = (
            int(self.color[0] * vitality_ratio),
            int(self.color[1] * vitality_ratio),
            int(self.color[2] * vitality_ratio)
        )
        pygame.draw.polygon(display, shade, rotated_points)

# ============================================================================
# SIMULATION MANAGER
# ============================================================================

class EcosystemSimulator:
    """Main simulation controller"""
    def __init__(self):
        self.herbivores = [Herbivore() for _ in range(STARTING_HERBIVORES)]
        self.carnivores = [Carnivore() for _ in range(STARTING_CARNIVORES)]
        self.nutrients = [Nutrient() for _ in range(STARTING_NUTRIENTS)]
        self.barriers = [Barrier() for _ in range(STARTING_BARRIERS)]
        self.is_running = True
        self.show_overlay = False
        
        # Statistics tracking
        self.herbivore_population_history = []
        self.carnivore_population_history = []
        self.herbivore_birth_history = []
        self.carnivore_birth_history = []
        self.time_step = 0
        self.herbivore_births_this_frame = 0
        self.carnivore_births_this_frame = 0
    
    def create_offspring(self, parent1: Creature, parent2: Creature, 
                        population: List[Creature], species_class):
        """Spawn a new creature from two parents"""
        offspring = species_class()
        offspring.pos = (parent1.pos + parent2.pos) / 2
        offspring.vitality = VITALITY_CAP
        population.append(offspring)
        
        parent1.breeding_cooldown = BREEDING_REST_PERIOD
        parent2.breeding_cooldown = BREEDING_REST_PERIOD
        parent1.partner = None
        parent2.partner = None
        
        if species_class == Herbivore:
            self.herbivore_births_this_frame += 1
        else:
            self.carnivore_births_this_frame += 1
    
    def run_simulation(self):
        """Main simulation loop"""
        global GROUP_BEHAVIOR_ACTIVE, NUTRIENT_SPAWN_PROBABILITY, VITALITY_DECAY_PER_FRAME
        
        while self.is_running:
            timer.tick(FRAMES_PER_SECOND)
            display.fill(BG_COLOR)
            
            # Handle input events
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.is_running = False
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_h:
                        self.herbivores.append(Herbivore())
                    elif event.key == pygame.K_c:
                        self.carnivores.append(Carnivore())
                    elif event.key == pygame.K_n:
                        self.nutrients.append(Nutrient())
                    elif event.key == pygame.K_b:
                        self.barriers.append(Barrier())
                    elif event.key == pygame.K_t:
                        GROUP_BEHAVIOR_ACTIVE = not GROUP_BEHAVIOR_ACTIVE
                    elif event.key == pygame.K_PLUS or event.key == pygame.K_EQUALS:
                        NUTRIENT_SPAWN_PROBABILITY = min(1.0, NUTRIENT_SPAWN_PROBABILITY + 0.01)
                    elif event.key == pygame.K_MINUS:
                        NUTRIENT_SPAWN_PROBABILITY = max(0.0, NUTRIENT_SPAWN_PROBABILITY - 0.01)
                    elif event.key == pygame.K_UP:
                        VITALITY_DECAY_PER_FRAME *= 1.15
                    elif event.key == pygame.K_DOWN:
                        VITALITY_DECAY_PER_FRAME *= 0.85
                    elif event.key == pygame.K_g:
                        self.display_statistics()
                    elif event.key == pygame.K_o:
                        self.show_overlay = not self.show_overlay
            
            # Update simulation state
            self.time_step += 1
            self.herbivore_births_this_frame = 0
            self.carnivore_births_this_frame = 0
            
            # Spawn nutrients randomly
            if random.random() < NUTRIENT_SPAWN_PROBABILITY:
                self.nutrients.append(Nutrient())
            
            # Update herbivores
            for herb in self.herbivores[:]:
                herb.update_behavior(self.carnivores, self.nutrients, self.herbivores, self.barriers)
                if not herb.is_alive:
                    self.herbivores.remove(herb)
                    continue
                
                # Consume nutrients
                for nut in self.nutrients[:]:
                    if herb.pos.distance_to(nut.pos) < herb.size + nut.size:
                        herb.vitality = min(VITALITY_CAP, herb.vitality + NUTRIENT_VITALITY_BOOST)
                        self.nutrients.remove(nut)
                
                # Check for reproduction completion
                if herb.courtship_counter == 1 and herb.partner:
                    if herb.partner in self.herbivores:
                        self.create_offspring(herb, herb.partner, self.herbivores, Herbivore)
            
            # Update carnivores
            for carn in self.carnivores[:]:
                carn.update_behavior(self.herbivores, self.carnivores, self.barriers)
                if not carn.is_alive:
                    self.carnivores.remove(carn)
                    continue
                
                # Hunt herbivores
                for herb in self.herbivores[:]:
                    if carn.pos.distance_to(herb.pos) < 12:
                        carn.vitality = min(VITALITY_CAP, carn.vitality + CARNIVORE_HUNT_VITALITY_BOOST)
                        self.herbivores.remove(herb)
                
                # Check for reproduction completion
                if carn.courtship_counter == 1 and carn.partner:
                    if carn.partner in self.carnivores:
                        self.create_offspring(carn, carn.partner, self.carnivores, Carnivore)
            
            # Record statistics
            self.herbivore_population_history.append(len(self.herbivores))
            self.carnivore_population_history.append(len(self.carnivores))
            self.herbivore_birth_history.append(self.herbivore_births_this_frame)
            self.carnivore_birth_history.append(self.carnivore_births_this_frame)
            
            # Render everything
            for barrier in self.barriers:
                barrier.render()
            for nutrient in self.nutrients:
                nutrient.render()
            for herb in self.herbivores:
                herb.render()
            for carn in self.carnivores:
                carn.render()
            
            self.render_ui()
            if self.show_overlay:
                self.render_realtime_charts()
            
            pygame.display.flip()
        
        self.save_statistics()
        pygame.quit()
    
    def render_ui(self):
        """Display on-screen information"""
        info_lines = [
            f"Herbivores: {len(self.herbivores)} | Carnivores: {len(self.carnivores)}",
            f"Nutrients: {len(self.nutrients)} | Barriers: {len(self.barriers)}",
            f"Group Behavior: {'ON' if GROUP_BEHAVIOR_ACTIVE else 'OFF'} (Toggle: T)",
            f"Nutrient Rate: {NUTRIENT_SPAWN_PROBABILITY:.2f} (+/-: +/-)",
            f"Vitality Decay: {VITALITY_DECAY_PER_FRAME:.3f} (Up/Down: Arrow Keys)",
            "Controls: H/C/N/B (Add), G (Graphs), O (Overlay)"
        ]
        for idx, line in enumerate(info_lines):
            text_surface = text_renderer.render(line, True, UI_TEXT_COLOR)
            display.blit(text_surface, (10, 10 + idx * 22))
    
    def render_realtime_charts(self):
        """Display live population graphs overlay"""
        chart_width, chart_height = 320, 160
        chart_x = SCREEN_WIDTH - chart_width - 10
        chart_y = SCREEN_HEIGHT - chart_height - 10
        
        # Semi-transparent background
        overlay = pygame.Surface((chart_width, chart_height))
        overlay.set_alpha(140)
        overlay.fill((0, 0, 0))
        display.blit(overlay, (chart_x, chart_y))
        
        # Title
        title = text_renderer.render("Live Population", True, (255, 255, 255))
        display.blit(title, (chart_x + 5, chart_y + 5))
        
        if len(self.herbivore_population_history) < 2:
            return
        
        # Normalize data
        max_pop = max(max(self.herbivore_population_history), max(self.carnivore_population_history), 1)
        
        herbivore_points = []
        carnivore_points = []
        
        # Show last 600 frames
        start_index = max(0, len(self.herbivore_population_history) - 600)
        data_length = len(self.herbivore_population_history) - start_index
        
        for i in range(data_length):
            idx = start_index + i
            x_coord = chart_x + (i / max(1, data_length - 1)) * chart_width
            
            y_herb = chart_y + chart_height - (self.herbivore_population_history[idx] / max_pop) * chart_height
            herbivore_points.append((x_coord, y_herb))
            
            y_carn = chart_y + chart_height - (self.carnivore_population_history[idx] / max_pop) * chart_height
            carnivore_points.append((x_coord, y_carn))
        
        if len(herbivore_points) > 1:
            pygame.draw.lines(display, HERBIVORE_COLOR, False, herbivore_points, 2)
        if len(carnivore_points) > 1:
            pygame.draw.lines(display, CARNIVORE_COLOR, False, carnivore_points, 2)
        
        # Border
        pygame.draw.rect(display, (255, 255, 255), (chart_x, chart_y, chart_width, chart_height), 1)
    
    def save_statistics(self):
        """Generate and save population graphs"""
        fig = plt.figure(figsize=(14, 9))
        
        plt.subplot(2, 1, 1)
        plt.plot(self.herbivore_population_history, label='Herbivores', color='green', linewidth=1.5)
        plt.plot(self.carnivore_population_history, label='Carnivores', color='red', linewidth=1.5)
        plt.title('Population Dynamics Over Time', fontsize=14, fontweight='bold')
        plt.xlabel('Time Step', fontsize=12)
        plt.ylabel('Population Count', fontsize=12)
        plt.legend(fontsize=11)
        plt.grid(True, alpha=0.3)
        
        plt.subplot(2, 1, 2)
        plt.plot(self.herbivore_birth_history, label='Herbivore Births', color='green', alpha=0.6, linewidth=1)
        plt.plot(self.carnivore_birth_history, label='Carnivore Births', color='red', alpha=0.6, linewidth=1)
        plt.title('Reproduction Events Over Time', fontsize=14, fontweight='bold')
        plt.xlabel('Time Step', fontsize=12)
        plt.ylabel('Births per Time Step', fontsize=12)
        plt.legend(fontsize=11)
        plt.grid(True, alpha=0.3)
        
        plt.tight_layout()
        os.makedirs('Statistics', exist_ok=True)
        filepath = 'Statistics/Ecosystem_Statistics.png'
        plt.savefig(filepath, dpi=150)
        print(f"Statistics saved to {filepath}")
        plt.close()
    
    def display_statistics(self):
        """Show interactive graphs"""
        fig = plt.figure(figsize=(12, 7))
        
        plt.subplot(2, 1, 1)
        plt.plot(self.herbivore_population_history, label='Herbivores', color='green')
        plt.plot(self.carnivore_population_history, label='Carnivores', color='red')
        plt.title('Population Over Time')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        plt.subplot(2, 1, 2)
        plt.plot(self.herbivore_birth_history, label='Herbivore Births', color='green', alpha=0.5)
        plt.plot(self.carnivore_birth_history, label='Carnivore Births', color='red', alpha=0.5)
        plt.title('Birth Events')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        plt.tight_layout()
        plt.show()

if __name__ == "__main__":
    EcosystemSimulator().run_simulation()

