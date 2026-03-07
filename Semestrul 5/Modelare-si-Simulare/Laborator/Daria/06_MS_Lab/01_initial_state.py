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
        angle = random.uniform(0, 2 * math.pi)
        self.velocity = pygame.math.Vector2(math.cos(angle), math.sin(angle))
        self.speed = 2

    def update(self):
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

    def draw(self):
        pygame.draw.circle(screen, PREY_COLOR, (int(self.position.x), int(self.position.y)), 4)
        
class Predator:
    def __init__(self):
        self.position = pygame.math.Vector2(random.uniform(0, WIDTH), random.uniform(0, HEIGHT))
        angle = random.uniform(0, 2 * math.pi)
        self.velocity = pygame.math.Vector2(math.cos(angle), math.sin(angle))
        self.speed = 3

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

    def draw(self):
        pygame.draw.circle(screen, PREDATOR_COLOR, (int(self.position.x), int(self.position.y)), 6)

# Create lists of prey and predators
prey_list = [Prey() for _ in range(50)]
predator_list = [Predator() for _ in range(3)]

running = True
while running:
    clock.tick(60)  # Limit to 60 FPS
    screen.fill(BACKGROUND_COLOR)

    # Event handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Update and draw prey
    for prey in prey_list[:]:
        prey.update()
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