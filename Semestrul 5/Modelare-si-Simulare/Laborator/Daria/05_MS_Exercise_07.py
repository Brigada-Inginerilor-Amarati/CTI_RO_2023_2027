import numpy as np
import pygame

# Initialize Pygame
pygame.init()

# Define simulation window dimensions
WINDOW_WIDTH, WINDOW_HEIGHT = 800, 600
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
pygame.display.set_caption('Boids Simulation - Exercise 7: Obstacle Avoidance & Keyboard Controls')

# Define colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)
GRAY = (128, 128, 128)

# Initialize font for displaying parameters
pygame.font.init()
font = pygame.font.Font(None, 24)


class Boid:
    def __init__(self, position, velocity):
        self.position = np.array(position, dtype='float64')
        self.velocity = np.array(velocity, dtype='float64')

    def update_position(self, width, height, radius=3):
        """Update position with boundary bouncing"""
        # move
        self.position += self.velocity

        # bounce on X (respect radius and clamp inside)
        if self.position[0] < radius:
            self.position[0] = radius
            self.velocity[0] *= -1
        elif self.position[0] > width - radius:
            self.position[0] = width - radius
            self.velocity[0] *= -1

        # bounce on Y (respect radius and clamp inside)
        if self.position[1] < radius:
            self.position[1] = radius
            self.velocity[1] *= -1
        elif self.position[1] > height - radius:
            self.position[1] = height - radius
            self.velocity[1] *= -1

    def separation(self, boids, separation_distance=20):
        """Calculate separation steering vector"""
        steer = np.zeros(2)
        count = 0
        for other in boids:
            distance = np.linalg.norm(self.position - other.position)
            if 0 < distance < separation_distance:
                steer += self.position - other.position
                count += 1
        if count > 0:
            steer /= count
        return steer

    def alignment(self, boids, neighbor_distance=50):
        """Calculate alignment steering vector"""
        avg_velocity = np.zeros(2)
        count = 0
        for other in boids:
            distance = np.linalg.norm(self.position - other.position)
            if 0 < distance < neighbor_distance:
                avg_velocity += other.velocity
                count += 1
        if count > 0:
            avg_velocity /= count
            return avg_velocity - self.velocity
        return np.zeros(2)

    def cohesion(self, boids, neighbor_distance=50):
        """Calculate cohesion steering vector"""
        center_of_mass = np.zeros(2)
        count = 0
        for other in boids:
            distance = np.linalg.norm(self.position - other.position)
            if 0 < distance < neighbor_distance:
                center_of_mass += other.position
                count += 1
        if count > 0:
            center_of_mass /= count
            return center_of_mass - self.position
        return np.zeros(2)

    def obstacle_avoidance(self, obstacles, avoidance_distance=50):
        """
        Calculate obstacle avoidance steering vector.
        Boids will steer away from obstacles within avoidance_distance.
        
        :param obstacles: List of Obstacle objects
        :param avoidance_distance: Distance at which boids start avoiding obstacles
        :return: Avoidance vector as a numpy array
        """
        avoid = np.zeros(2)
        for obstacle in obstacles:
            direction = self.position - obstacle.position
            distance = np.linalg.norm(direction)
            
            # If obstacle is within avoidance distance
            if distance < avoidance_distance and distance > 0:
                # Normalize direction and scale by inverse distance (closer = stronger repulsion)
                avoid += (direction / distance) * (avoidance_distance - distance) / avoidance_distance
        
        return avoid

    def apply_behaviors(self, boids, obstacles, 
                        separation_weight=1.5, 
                        alignment_weight=1.0, 
                        cohesion_weight=1.0,
                        obstacle_weight=2.0,
                        max_speed=2,
                        separation_distance=20,
                        neighbor_distance=50):
        """
        Apply all behaviors including obstacle avoidance.
        
        :param boids: List of all Boids
        :param obstacles: List of all Obstacles
        :param separation_weight: Weight for separation behavior
        :param alignment_weight: Weight for alignment behavior
        :param cohesion_weight: Weight for cohesion behavior
        :param obstacle_weight: Weight for obstacle avoidance
        :param max_speed: Maximum speed limit
        :param separation_distance: Distance for separation behavior
        :param neighbor_distance: Distance for alignment and cohesion behaviors
        """
        sep = self.separation(boids, separation_distance) * separation_weight
        ali = self.alignment(boids, neighbor_distance) * alignment_weight
        coh = self.cohesion(boids, neighbor_distance) * cohesion_weight
        obs = self.obstacle_avoidance(obstacles) * obstacle_weight
        
        self.velocity += sep + ali + coh + obs
        self.limit_speed(max_speed)

    def limit_speed(self, max_speed):
        """Limit the Boid's speed to the specified maximum"""
        speed = np.linalg.norm(self.velocity)
        if speed > max_speed:
            self.velocity = (self.velocity / speed) * max_speed

    def draw(self, surface, max_speed):
        """Draw the Boid colored by speed"""
        speed = np.linalg.norm(self.velocity)

        if speed > max_speed * 0.99:
            pygame.draw.circle(surface, RED, self.position.astype(int), 3)
        else:
            pygame.draw.circle(surface, BLUE, self.position.astype(int), 3)


class Obstacle:
    def __init__(self, position, radius=30):
        self.position = np.array(position, dtype='float64')
        self.radius = radius

    def draw(self, surface):
        """Draw the obstacle as a white circle"""
        pygame.draw.circle(surface, WHITE, self.position.astype(int), self.radius)
        # Draw a border to make it more visible
        pygame.draw.circle(surface, GRAY, self.position.astype(int), self.radius, 2)


def draw_ui(surface, params):
    """Draw the UI showing current parameters and controls"""
    y_offset = 10
    line_height = 25
    
    # Background for text
    ui_rect = pygame.Rect(10, 10, 300, 200)
    pygame.draw.rect(surface, (0, 0, 0, 180), ui_rect)
    pygame.draw.rect(surface, WHITE, ui_rect, 2)
    
    texts = [
        f"Separation: {params['separation_weight']:.2f} (Q/A)",
        f"Alignment: {params['alignment_weight']:.2f} (W/S)",
        f"Cohesion: {params['cohesion_weight']:.2f} (E/D)",
        f"Obstacle Avoid: {params['obstacle_weight']:.2f} (R/F)",
        f"Max Speed: {params['max_speed']:.2f} (T/G)",
        f"Separation Dist: {params['separation_distance']:.1f} (Y/H)",
        f"Neighbor Dist: {params['neighbor_distance']:.1f} (U/J)",
        "",
        "Mouse: Attract boids",
        "ESC: Exit"
    ]
    
    for i, text in enumerate(texts):
        if text:  # Skip empty strings
            text_surface = font.render(text, True, WHITE)
            surface.blit(text_surface, (20, y_offset + i * line_height))


# Initialize simulation parameters (adjustable via keyboard)
params = {
    'separation_weight': 1.5,
    'alignment_weight': 1.0,
    'cohesion_weight': 1.0,
    'obstacle_weight': 2.0,
    'max_speed': 2.0,
    'separation_distance': 20.0,
    'neighbor_distance': 50.0
}

# Initialize Boids
num_boids = 30
boids_pygame = [
    Boid(position=np.random.rand(2) * [WINDOW_WIDTH, WINDOW_HEIGHT],
         velocity=np.random.rand(2) * 2 - 1)
    for _ in range(num_boids)
]

# Initialize Obstacles (can add more)
obstacles = [
    Obstacle(position=np.random.rand(2) * [WINDOW_WIDTH, WINDOW_HEIGHT], radius=30),
    Obstacle(position=np.random.rand(2) * [WINDOW_WIDTH, WINDOW_HEIGHT], radius=25)
]

# Define clock to control frame rate
clock = pygame.time.Clock()
FPS = 60  # Frames per second

# Main Pygame loop
running = True
while running:
    clock.tick(FPS)

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            # Keyboard controls for adjusting parameters
            # Q/A: Separation weight
            if event.key == pygame.K_q:
                params['separation_weight'] = min(params['separation_weight'] + 0.1, 5.0)
            elif event.key == pygame.K_a:
                params['separation_weight'] = max(params['separation_weight'] - 0.1, 0.0)
            
            # W/S: Alignment weight
            elif event.key == pygame.K_w:
                params['alignment_weight'] = min(params['alignment_weight'] + 0.1, 5.0)
            elif event.key == pygame.K_s:
                params['alignment_weight'] = max(params['alignment_weight'] - 0.1, 0.0)
            
            # E/D: Cohesion weight
            elif event.key == pygame.K_e:
                params['cohesion_weight'] = min(params['cohesion_weight'] + 0.1, 5.0)
            elif event.key == pygame.K_d:
                params['cohesion_weight'] = max(params['cohesion_weight'] - 0.1, 0.0)
            
            # R/F: Obstacle avoidance weight
            elif event.key == pygame.K_r:
                params['obstacle_weight'] = min(params['obstacle_weight'] + 0.1, 5.0)
            elif event.key == pygame.K_f:
                params['obstacle_weight'] = max(params['obstacle_weight'] - 0.1, 0.0)
            
            # T/G: Max speed
            elif event.key == pygame.K_t:
                params['max_speed'] = min(params['max_speed'] + 0.2, 10.0)
            elif event.key == pygame.K_g:
                params['max_speed'] = max(params['max_speed'] - 0.2, 0.5)
            
            # Y/H: Separation distance
            elif event.key == pygame.K_y:
                params['separation_distance'] = min(params['separation_distance'] + 5, 100)
            elif event.key == pygame.K_h:
                params['separation_distance'] = max(params['separation_distance'] - 5, 5)
            
            # U/J: Neighbor distance
            elif event.key == pygame.K_u:
                params['neighbor_distance'] = min(params['neighbor_distance'] + 5, 200)
            elif event.key == pygame.K_j:
                params['neighbor_distance'] = max(params['neighbor_distance'] - 5, 20)
            
            # ESC: Exit
            elif event.key == pygame.K_ESCAPE:
                running = False

    # Get mouse position and state
    mouse_pos = np.array(pygame.mouse.get_pos(), dtype='float64')
    mouse_pressed = pygame.mouse.get_pressed()[0]  # Left button

    # Fill the background
    screen.fill(BLACK)

    # Update and draw obstacles first
    for obstacle in obstacles:
        obstacle.draw(screen)

    # Update and draw each Boid
    for boid in boids_pygame:
        # Mouse interaction: attract boids to mouse
        if mouse_pressed:
            direction = mouse_pos - boid.position
            distance = np.linalg.norm(direction)
            if distance > 0:
                boid.velocity += direction * 0.001  # Adjust strength as needed

        # Apply behaviors with current parameters
        boid.apply_behaviors(
            boids_pygame, 
            obstacles,
            separation_weight=params['separation_weight'],
            alignment_weight=params['alignment_weight'],
            cohesion_weight=params['cohesion_weight'],
            obstacle_weight=params['obstacle_weight'],
            max_speed=params['max_speed'],
            separation_distance=params['separation_distance'],
            neighbor_distance=params['neighbor_distance']
        )
        boid.update_position(WINDOW_WIDTH, WINDOW_HEIGHT)
        boid.draw(screen, max_speed=params['max_speed'])

    # Draw UI
    draw_ui(screen, params)

    # Update the display
    pygame.display.flip()

pygame.quit()

