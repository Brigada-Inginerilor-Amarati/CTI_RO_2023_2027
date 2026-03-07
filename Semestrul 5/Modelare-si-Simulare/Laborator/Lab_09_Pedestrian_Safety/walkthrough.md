# Lab 9: Pedestrian Safety Simulation Walkthrough

## 1. Project Overview
This simulation explores the safety and environmental challenges of the transition to Electric Vehicles (EVs).
It focuses on the "Silent Killer" hypothesis: that pedestrians are more likely to collide with silent EVs because they rely on auditory cues to cross roads.
To counter this, **AVAS (Acoustic Vehicle Alerting Systems)** are introduced, but they cause **Noise Pollution**.
This project simulates this trade-off.

## 2. Scientific Basis (External Resources)
The core logic of this model is determined by two scientific papers:

### Reference 1: Collision Statistics
*   **Paper**: *Comparing pedestrian safety between electric and internal combustion engine vehicles* (Nature Communications, 2025).
*   **Insight Used**: Hybrid vehicles (often operating silently at low speeds) show a higher collision rate than ICEs. We model this by giving "Silent" vehicles a very low **Detectability Score** (0.2 vs 0.98 for Diesel).

### Reference 2: Psychoacoustics & Noise
*   **Paper**: *Psychoacoustic assessment of synthetic sounds for electric vehicles* (Arxiv, 2025).
*   **Insight Used**: Different sound profiles have "Annoyance Scores".
    *   **Silent EV**: Score 1.0 (Pleasant, but dangerous).
    *   **Pure Tone AVAS**: Score 5.4 (Safe, but annoying).
    *   **Complex AVAS**: Score 4.8 (Balanced).

## 3. How to Run the Simulation
1.  Open the terminal in the `Lab_09_Pedestrian_Safety` folder.
2.  Run: `python safety_sim.py`
3.  A Pygame window will appear showing traffic and pedestrians.

## 4. Scenarios & Instructions
Use the number keys to switch between scenarios during runtime:

### Scenario 1: Silent Risk (Press '1')
*   **Fleet**: Mostly Silent EVs.
*   **Observation**: You will see many Blue cars. Pedestrians often fail to "hear" them and walk into the road, causing **Collisions** (Red Pedestrians).
*   **Outcome**: High Accidents, Low Noise.

### Scenario 2: Loud Future (Press '2')
*   **Fleet**: EVs with "Pure Tone" beepers.
*   **Observation**: You will see Dark Blue cars. Pedestrians detect them easily and wait.
*   **Outcome**: Low Accidents, **High Annoyance Factor** (Check the Stats on screen).

### Scenario 3: Optimized Balance (Press '3')
*   **Fleet**: EVs with "Complex" sounds.
*   **Observation**: A mix of safety and noise comfort.

## 5. Comparative Analysis (The Plot)
When you finish testing (close the window), the program generates a **Comparative Bar Chart**.
*   **Red Bars**: Total Collisions (Safety Risk).
*   **Purple Bars**: Average Annoyance (Noise Pollution).

Try running all 3 scenarios for 30 seconds each, then close the window to see the side-by-side comparison!
