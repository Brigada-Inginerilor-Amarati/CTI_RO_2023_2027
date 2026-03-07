# Predator-Prey Ecosystem Simulation - Complete Walkthrough

## Table of Contents
1. [Project Overview](#project-overview)
2. [Configuration Parameters](#configuration-parameters)
3. [Code Architecture](#code-architecture)
4. [Core Classes Explained](#core-classes-explained)
5. [Behavioral Systems](#behavioral-systems)
6. [Simulation Loop](#simulation-loop)
7. [Controls & Features](#controls--features)

---

## Project Overview

This is an **ecosystem dynamics simulator** that models predator-prey relationships in a 2D environment. The simulation features:

- **Herbivores** (prey) that feed on nutrients and flee from predators
- **Carnivores** (predators) that hunt herbivores
- **Group behavior** using the Boids flocking algorithm
- **Reproduction system** with courtship mechanics
- **Vitality system** that affects creature behavior and survival
- **Real-time statistics** and data visualization

The simulation uses **pygame** for rendering and **matplotlib** for statistical analysis.

---

## Configuration Parameters

All simulation parameters are defined as constants at the top of the file for easy tuning.

### Display Settings
```python
SCREEN_WIDTH = 800          # Window width in pixels
SCREEN_HEIGHT = 600         # Window height in pixels
FRAMES_PER_SECOND = 60      # Simulation update rate
```

### Color Palette
```python
BG_COLOR = (25, 25, 35)              # Dark blue-gray background
HERBIVORE_COLOR = (50, 200, 100)     # Green for herbivores
CARNIVORE_COLOR = (220, 50, 50)      # Red for carnivores
NUTRIENT_COLOR = (255, 200, 0)       # Yellow for food
BARRIER_COLOR = (100, 100, 120)      # Gray for obstacles
UI_TEXT_COLOR = (220, 220, 220)      # Light gray for UI text
```

### Starting Population
```python
STARTING_HERBIVORES = 45    # Initial number of prey
STARTING_CARNIVORES = 4     # Initial number of predators
STARTING_NUTRIENTS = 25     # Initial food resources
STARTING_BARRIERS = 6       # Initial obstacles
```

### Movement Parameters
```python
HERBIVORE_BASE_VELOCITY = 1.8        # Pixels per frame (prey speed)
CARNIVORE_BASE_VELOCITY = 2.4        # Pixels per frame (predator speed)
HERBIVORE_DETECTION_RANGE = 55       # How far herbivores can detect threats
CARNIVORE_DETECTION_RANGE = 95       # How far carnivores can detect prey
BARRIER_SIZE = 32                    # Radius of obstacles
NUTRIENT_SIZE = 4                    # Radius of food items
```

**Note:** Carnivores are faster than herbivores, creating a realistic chase dynamic.

### Vitality System
```python
VITALITY_CAP = 100.0                 # Maximum vitality (health/energy)
VITALITY_DECAY_PER_FRAME = 0.067     # Vitality lost per frame
NUTRIENT_VITALITY_BOOST = 32.0       # Vitality gained from eating
CARNIVORE_HUNT_VITALITY_BOOST = 55.0 # Vitality gained from hunting
HUNGER_LEVEL = 35.0                  # Threshold for active food seeking
```

**How it works:**
- Creatures lose vitality over time (starvation)
- Herbivores gain vitality by consuming nutrients
- Carnivores gain vitality by hunting herbivores
- When vitality reaches 0, the creature dies
- Creatures change color based on vitality (darker = lower vitality)

### Breeding System
```python
BREEDING_VITALITY_REQUIREMENT = 75.0  # Minimum vitality to breed
BREEDING_REST_PERIOD = 180            # Frames before can breed again
COURTSHIP_TIME = 50                   # Frames spent in courtship
COURTSHIP_PROXIMITY = 18.0            # Distance to start courtship
```

**Breeding Process:**
1. Two creatures with high vitality (>75) find each other
2. They approach and enter courtship when within 18 pixels
3. During courtship (50 frames), both creatures pause movement
4. After courtship, a new offspring spawns at the midpoint
5. Both parents enter a cooldown period (180 frames)

### Group Behavior (Boids Algorithm)
```python
GROUP_BEHAVIOR_ACTIVE = True          # Enable/disable flocking
NEIGHBORHOOD_RADIUS = 55              # Detection range for neighbors
STEER_ALIGNMENT = 0.4                 # Weight for velocity alignment
STEER_COHESION = 0.35                 # Weight for group cohesion
STEER_SEPARATION = 0.75               # Weight for separation (highest priority)
GROUP_VELOCITY_BONUS = 0.04           # Speed bonus per neighbor
```

**Boids Algorithm Components:**
- **Alignment:** Steer towards average velocity of neighbors
- **Cohesion:** Steer towards average position of neighbors (stay in group)
- **Separation:** Steer away from neighbors (avoid crowding)

### Nutrient Generation
```python
NUTRIENT_SPAWN_PROBABILITY = 0.04    # Probability per frame (4% chance)
```

Each frame has a 4% chance of spawning a new nutrient randomly on the screen.

---

## Code Architecture

The project is organized into several logical sections:

```
1. Configuration Constants (lines 9-63)
2. Pygame Setup (lines 64-72)
3. Data Structures (lines 74-416)
   - Vector2D (mathematical operations)
   - Nutrient (food resources)
   - Barrier (obstacles)
   - Creature (base class)
   - Herbivore (prey species)
   - Carnivore (predator species)
4. Simulation Manager (lines 417-673)
   - EcosystemSimulator (main controller)
```

---

## Core Classes Explained

### Vector2D (Lines 78-111)

A custom 2D vector class for position and velocity calculations.

**Key Methods:**
- `__add__`, `__sub__`, `__mul__`, `__truediv__`: Vector arithmetic
- `magnitude()`: Calculate vector length
- `normalize()`: Convert to unit vector (length = 1)
- `distance_to()`: Calculate distance to another vector
- `to_tuple()`: Convert to (x, y) tuple for pygame

**Why custom?** Provides clean mathematical operations for 2D physics.

### Nutrient (Lines 113-123)

Simple food resource that herbivores consume.

**Properties:**
- `pos`: Position (Vector2D)
- `size`: Visual radius (4 pixels)

**Behavior:**
- Spawns at random position
- Rendered as yellow circle
- Removed when consumed by herbivore

### Barrier (Lines 125-135)

Static obstacles that creatures avoid.

**Properties:**
- `pos`: Position (Vector2D)
- `size`: Radius (32 pixels)

**Behavior:**
- Creatures steer away when within 57 pixels (size + 25 buffer)
- Rendered as gray circle

### Creature (Lines 137-190)

Base class for all moving agents (herbivores and carnivores).

**Key Properties:**
```python
self.pos              # Current position (Vector2D)
self.vel              # Current velocity (Vector2D, normalized)
self.base_velocity    # Base speed (pixels per frame)
self.current_velocity # Current speed (can be modified)
self.vitality         # Health/energy (0-100)
self.breeding_cooldown # Frames until can breed again
self.courtship_counter # Frames remaining in courtship
self.partner          # Reference to mating partner
self.is_alive         # Life status flag
self.movement_history # Trail for visualization
```

**Key Methods:**
- `reduce_vitality()`: Decrease vitality, mark dead if <= 0
- `enforce_boundaries()`: Bounce off screen edges
- `evade_barriers()`: Steer away from obstacles
- `record_position()`: Track movement for trail visualization

### Herbivore (Lines 192-326)

Prey species that feeds on nutrients and flees from predators.

**Behavior Priority System:**
1. **Escape predators** (highest priority)
   - Detects carnivores within 55 pixels
   - Steers away with 0.45 force multiplier

2. **Forage for food** (when vitality < 35)
   - Seeks nearest nutrient
   - Steers towards with 0.25 force multiplier

3. **Seek mate** (when vitality > 75 and cooldown = 0)
   - Finds eligible partner
   - Approaches and enters courtship

4. **Group behavior** (Boids algorithm)
   - Alignment, cohesion, separation forces
   - Speed increases with group size

5. **Barrier avoidance** (always active)

**Special Features:**
- Group dynamics create flocking behavior
- Color intensity reflects vitality level
- Movement trail visualization

### Carnivore (Lines 328-415)

Predator species that hunts herbivores.

**Behavior Priority System:**
1. **Hunt herbivores** (highest priority)
   - Detects herbivores within 95 pixels
   - Pursues with 0.35 force multiplier
   - Kills herbivore on contact (< 12 pixels)

2. **Seek mate** (when vitality > 75 and cooldown = 0)
   - Same courtship system as herbivores

3. **Barrier avoidance** (always active)

**Visual Representation:**
- Rendered as triangle pointing in movement direction
- Color intensity reflects vitality
- Movement trail visualization

---

## Behavioral Systems

### 1. Vitality System

**Decay:**
```python
def reduce_vitality(self):
    self.vitality -= VITALITY_DECAY_PER_FRAME  # 0.067 per frame
    if self.vitality <= 0:
        self.is_alive = False
```

At 60 FPS, creatures lose ~4 vitality per second. This creates time pressure.

**Recovery:**
- Herbivores: +32 vitality per nutrient consumed
- Carnivores: +55 vitality per herbivore killed

**Visual Feedback:**
```python
vitality_ratio = max(0.25, self.vitality / VITALITY_CAP)
shade = (color[0] * ratio, color[1] * ratio, color[2] * ratio)
```
Creatures become darker as vitality decreases (minimum 25% brightness).

### 2. Breeding System

**Requirements:**
- Both partners must have vitality > 75
- Both must have breeding_cooldown = 0
- Both must not already have a partner

**Process:**
1. Creatures detect eligible mates within detection range
2. Approach each other (0.28 force multiplier)
3. When within 18 pixels, enter courtship
4. Courtship lasts 50 frames (both pause movement)
5. Offspring spawns at midpoint between parents
6. Both parents enter 180-frame cooldown

**Offspring:**
- Spawns with full vitality (100)
- Inherits species type
- Positioned at average of parent positions

### 3. Boids Flocking Algorithm (Herbivores Only)

The Boids algorithm creates natural-looking group behavior using three forces:

**Alignment Force:**
```python
align_force = average_velocity_of_neighbors
```
Steers creature to match direction of nearby group members.

**Cohesion Force:**
```python
cohesion_force = direction_to_average_position_of_neighbors
```
Steers creature towards center of nearby group.

**Separation Force:**
```python
separation_force = sum((position - neighbor_position) / distance²)
```
Steers creature away from nearby neighbors to avoid crowding.

**Combined Effect:**
```python
self.vel = self.vel + align_force + cohesion_force + separation_force
self.current_velocity = base_velocity + (neighbor_count * 0.04)
```

Creatures in groups move faster and more cohesively.

### 4. Collision Detection

**Herbivore-Nutrient:**
```python
if herb.pos.distance_to(nut.pos) < herb.size + nut.size:
    # Consume nutrient
```
Distance check: 5 + 4 = 9 pixels

**Carnivore-Herbivore:**
```python
if carn.pos.distance_to(herb.pos) < 12:
    # Kill herbivore
```
Hardcoded 12-pixel threshold for hunting.

**Barrier Avoidance:**
```python
if dist < barrier.size + 25:  # 32 + 25 = 57 pixels
    # Steer away
```
Creatures start avoiding barriers before contact.

---

## Simulation Loop

The main simulation loop (`run_simulation()`, lines 458-562) executes at 60 FPS:

### Frame Structure:

1. **Event Handling** (lines 467-492)
   - Process keyboard input
   - Handle window close
   - Update runtime parameters

2. **State Updates** (lines 494-497)
   - Increment time step
   - Reset birth counters

3. **Nutrient Spawning** (lines 499-501)
   - Random chance to spawn new food

4. **Herbivore Updates** (lines 503-519)
   - Update behavior (movement, decisions)
   - Remove dead herbivores
   - Check nutrient consumption
   - Handle reproduction completion

5. **Carnivore Updates** (lines 521-537)
   - Update behavior (hunting, movement)
   - Remove dead carnivores
   - Check herbivore hunting
   - Handle reproduction completion

6. **Statistics Recording** (lines 539-543)
   - Track population counts
   - Track birth events

7. **Rendering** (lines 545-557)
   - Draw barriers
   - Draw nutrients
   - Draw herbivores
   - Draw carnivores
   - Draw UI overlay
   - Draw real-time charts (if enabled)

8. **Display Update** (line 559)
   - Flip pygame display buffer

### Key Update Order:

The order matters! Updates happen in this sequence:
1. Behavior decisions (where to move)
2. Movement application
3. Collision detection (consumption, hunting)
4. Reproduction checks
5. Death removal

This ensures creatures can react to current frame state before collisions are processed.

---

## Controls & Features

### Keyboard Controls

| Key | Action |
|-----|--------|
| **H** | Add a new herbivore |
| **C** | Add a new carnivore |
| **N** | Add a new nutrient |
| **B** | Add a new barrier |
| **T** | Toggle group behavior (Boids) on/off |
| **+** or **=** | Increase nutrient spawn rate (+1%) |
| **-** | Decrease nutrient spawn rate (-1%) |
| **↑** | Increase vitality decay rate (+15%) |
| **↓** | Decrease vitality decay rate (-15%) |
| **G** | Display interactive statistics graphs |
| **O** | Toggle real-time population overlay |
| **ESC** or **Close** | Exit simulation |

### Real-Time Overlay (O key)

Displays a live population graph in the bottom-right corner:
- Shows last 600 frames of data
- Green line: Herbivore population
- Red line: Carnivore population
- Updates every frame

### Statistics System

**During Simulation:**
- Tracks population counts per frame
- Tracks birth events per frame
- Stores in lists for analysis

**On Exit:**
- Automatically saves `Statistics/Ecosystem_Statistics.png`
- Contains two graphs:
  1. Population dynamics over time
  2. Reproduction events over time

**Interactive Graphs (G key):**
- Opens matplotlib window with current statistics
- Can be viewed while simulation runs
- Updates reflect current state

---

## Code Flow Example

Let's trace what happens when a herbivore encounters a carnivore:

1. **Frame Start:** Herbivore at position (100, 200), vitality = 50

2. **Herbivore.update_behavior() called:**
   ```python
   # Priority 1: Check for predators
   for carn in carnivores:
       dist = self.pos.distance_to(carn.pos)  # Calculate distance
       if dist < 55:  # Within detection range
           closest_carnivore = carn
   
   if closest_carnivore:
       escape_direction = (self.pos - carn.pos).normalize()
       self.vel = self.vel + escape_direction * 0.45
   ```

3. **Velocity Normalized:**
   ```python
   self.vel = self.vel.normalize()  # Ensure unit vector
   ```

4. **Position Updated:**
   ```python
   self.pos = self.pos + self.vel * self.current_velocity
   # Moves 1.8 pixels in escape direction
   ```

5. **Boundary Check:**
   ```python
   self.enforce_boundaries()  # Bounce if at edge
   ```

6. **Trail Recorded:**
   ```python
   self.record_position()  # Add to movement_history
   ```

7. **Rendering:**
   ```python
   herb.render()  # Draws circle + trail with color based on vitality
   ```

---

## Parameter Tuning Guide

### To Make Simulation More Stable:
- **Increase** `NUTRIENT_SPAWN_PROBABILITY` (more food)
- **Decrease** `VITALITY_DECAY_PER_FRAME` (slower starvation)
- **Increase** `NUTRIENT_VITALITY_BOOST` (more energy from food)

### To Make Simulation More Dynamic:
- **Decrease** `BREEDING_REST_PERIOD` (faster reproduction)
- **Increase** `CARNIVORE_DETECTION_RANGE` (better hunting)
- **Decrease** `HUNGER_LEVEL` (more active foraging)

### To Observe Different Behaviors:
- **Disable** `GROUP_BEHAVIOR_ACTIVE` to see individual behavior
- **Adjust** Boids weights (`STEER_ALIGNMENT`, `STEER_COHESION`, `STEER_SEPARATION`)
- **Modify** speed ratios between herbivores and carnivores

---

## Technical Details

### Performance Considerations

- **O(n²) complexity** for neighbor detection in Boids algorithm
- For large populations (>100), consider spatial partitioning
- Movement history limited to 12 points to reduce memory

### Coordinate System

- Origin (0, 0) at top-left corner
- X increases rightward
- Y increases downward
- All positions use floating-point for smooth movement

### Random Number Generation

- Uses Python's `random` module
- No seed set, so each run is different
- To reproduce results, add `random.seed(value)` at start

---

## Extending the Simulation

### Adding New Creature Types:

1. Create new class inheriting from `Creature`
2. Override `update_behavior()` method
3. Implement species-specific logic
4. Add to `EcosystemSimulator` initialization
5. Add rendering logic

### Adding New Behaviors:

1. Add new constants for parameters
2. Implement behavior in `update_behavior()`
3. Add appropriate priority in decision tree
4. Update UI to show new parameters

### Adding New Statistics:

1. Add tracking lists in `EcosystemSimulator.__init__()`
2. Record data in main loop
3. Add visualization in `save_statistics()` or `render_realtime_charts()`

---

## Conclusion

This simulation demonstrates:
- **Agent-based modeling** with autonomous creatures
- **Emergent behavior** from simple rules (Boids algorithm)
- **Ecosystem dynamics** (predator-prey cycles)
- **Real-time visualization** and data analysis

The modular design makes it easy to experiment with different parameters and behaviors. Adjust constants, run the simulation, and observe how small changes create different ecosystem patterns!




