import pygame
import random
import math

# Screen dimensions
WIDTH, HEIGHT = 800, 600

# Colors
BACKGROUND_COLOR = (30, 30, 30)
PREY_COLOR = (0, 255, 0)
PREDATOR_COLOR = (255, 0, 0)

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Predator-Prey Simulation")
clock = pygame.time.Clock()

class Prey:
    def __init__(self):
        self.position = pygame.math.Vector2(random.uniform(0, WIDTH), random.uniform(0, HEIGHT))
        self.velocity = pygame.math.Vector2(random.uniform(-1, 1), random.uniform(-1, 1)).normalize()
        self.speed = 2
        self.vision_radius = 50  # New attribute
        self.trail = []

    def update(self, predators):
        # Flee from predators
        nearest_predator = None
        min_distance = self.vision_radius  # Only consider predators within vision radius

        for predator in predators:
            distance = self.position.distance_to(predator.position)
            if distance < min_distance:
                min_distance = distance
                nearest_predator = predator

        if nearest_predator:
            # Flee from the nearest predator
            flee_direction = (self.position - nearest_predator.position).normalize()
            self.velocity = flee_direction

        # Move the prey
        self.position += self.velocity * self.speed

        # Bounce off the edges
        if self.position.x < 0 or self.position.x > WIDTH:
            self.velocity.x *= -1
        if self.position.y < 0 or self.position.y > HEIGHT:
            self.velocity.y *= -1

        # Keep position within bounds
        self.position.x = max(0, min(self.position.x, WIDTH))
        self.position.y = max(0, min(self.position.y, HEIGHT))

        # Update trail
        self.trail.append(self.position.copy())
        if len(self.trail) > 10:
            self.trail.pop(0)

    def draw(self):
        # Draw trail
        if len(self.trail) > 1:
            pygame.draw.lines(screen, PREY_COLOR, False, [(int(p.x), int(p.y)) for p in self.trail], 1)
        pygame.draw.circle(screen, PREY_COLOR, (int(self.position.x), int(self.position.y)), 4)

class Predator:
    def __init__(self):
        self.position = pygame.math.Vector2(random.uniform(0, WIDTH), random.uniform(0, HEIGHT))
        angle = random.uniform(0, 2 * math.pi)
        self.velocity = pygame.math.Vector2(math.cos(angle), math.sin(angle))
        self.speed = 3
        self.trail = []

    def update(self, prey_list):
        # Simple hunting behavior: move towards the nearest prey
        if prey_list:
            nearest_prey = min(prey_list, key=lambda prey: self.position.distance_to(prey.position))
            direction = (nearest_prey.position - self.position).normalize()
            self.velocity = direction
            self.position += self.velocity * self.speed
        else:
            # Random movement if no prey
            self.position += self.velocity * self.speed

        # Bounce off the edges
        if self.position.x < 0 or self.position.x > WIDTH:
            self.velocity.x *= -1
        if self.position.y < 0 or self.position.y > HEIGHT:
            self.velocity.y *= -1

        # Keep position within bounds
        self.position.x = max(0, min(self.position.x, WIDTH))
        self.position.y = max(0, min(self.position.y, HEIGHT))
        # Update trail
        self.trail.append(self.position.copy())
        if len(self.trail) > 10:
            self.trail.pop(0)

    def draw(self):
            # Calculate the angle in degrees between the velocity and the x-axis
            angle = self.velocity.angle_to(pygame.math.Vector2(1, 0))

            # Define the triangle points relative to the origin, pointing right
            point_list = [
                pygame.math.Vector2(10, 0),    # Tip of the triangle
                pygame.math.Vector2(-5, -5),   # Bottom left
                pygame.math.Vector2(-5, 5),    # Bottom right
            ]

            # Rotate the points and translate to the predator's position
            rotated_point_list = [self.position + p.rotate(-angle) for p in point_list]

            # Draw the predator as a triangle
            pygame.draw.polygon(screen, PREDATOR_COLOR, rotated_point_list)
            
            # Draw trail
            if len(self.trail) > 1:
                pygame.draw.lines(screen, PREDATOR_COLOR, False, [(int(p.x), int(p.y)) for p in self.trail], 1)

def draw_legend():
    font = pygame.font.SysFont(None, 24)
    prey_text = font.render('Prey (Green Circle) - Press P to add', True, PREY_COLOR)
    predator_text = font.render('Predator (Red Triangle) - Press O to add', True, PREDATOR_COLOR)
    screen.blit(prey_text, (10, 10))
    screen.blit(predator_text, (10, 30))
    
def draw_stats():
    font = pygame.font.SysFont(None, 24)
    prey_count_text = font.render(f'Prey Count: {len(prey_list)}', True, (200, 200, 200))
    predator_count_text = font.render(f'Predator Count: {len(predator_list)}', True, (200, 200, 200))
    screen.blit(prey_count_text, (WIDTH - 150, 10))
    screen.blit(predator_count_text, (WIDTH - 150, 30))

# Create lists of prey and predators
prey_list = [Prey() for _ in range(50)]
predator_list = [Predator() for _ in range(3)]

running = True
while running:
    clock.tick(60)  # Limit to 60 FPS
    screen.fill(BACKGROUND_COLOR)
    draw_stats()
    draw_legend()

    # Event handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
            # Add prey with 'P' key
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_p:
                prey_list.append(Prey())
            # Add predator with 'O' key
            elif event.key == pygame.K_o:
                predator_list.append(Predator())

    # Update and draw prey
    for prey in prey_list[:]:
        prey.update(predator_list)
        prey.draw()

    # Update and draw predators
    for predator in predator_list:
        predator.update(prey_list)
        predator.draw()

    # Collision detection
    for predator in predator_list:
        for prey in prey_list[:]:
            if predator.position.distance_to(prey.position) < 6:
                prey_list.remove(prey)

    # Update the display
    pygame.display.flip()
    

pygame.quit()