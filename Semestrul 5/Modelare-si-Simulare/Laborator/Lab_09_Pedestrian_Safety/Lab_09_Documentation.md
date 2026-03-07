# Lab 9: Pedestrian Safety & AVAS Simulation
## Research-Backed Modeling of EV Transitions

### 1. Project Overview
This project simulates the safety and environmental implications of the transition from Internal Combustion Engine (ICE) vehicles to Electric Vehicles (EVs) in an urban environment. Specifically, it models **pedestrian road-crossing behavior** and the trade-off between **collision risk** (due to vehicle silence) and **noise pollution** (due to Artificial Vehicle Alerting Systems - AVAS).

### 2. Scientific References (External Resources)

#### Resource A: Collision Statistics
**Source**: *Comparing pedestrian safety between electric and internal combustion engine vehicles* (Nature Communications, Dec 2025).
-   **Finding**: Hybrid Electric Vehicles (HEVs) showed a significantly higher collision rate (**120.1 per billion miles**) compared to ICE/EVs (~58 per billion miles), effectively a **~2x risk**, but with observed lower injury severity.
-   **Model Parameter**:
    -   **ICE Collision Probability Factor**: 1.0 (Baseline).
    -   **HEV Collision Probability Factor**: 1.5 (Conservative model of the 2.0x risk).
    -   **EV Collision Probability Factor**: 1.0 (Aligns with finding that EVs $\approx$ ICE in general stats).
    -   **Severity**: HEV collisions have a 50% reduced chance of 'Severe' outcome (reflecting the "less severe injuries" finding).

#### Resource B: Psychoacoustics of AVAS
**Source**: *Psychoacoustic assessment of synthetic sounds for electric vehicles* (Arxiv:2510.25593, 2025).
-   **Finding**: Different vehicle sounds have quantified "Annoyance" and implied "Noticeability".
-   **Model Parameters**:
    | Vehicle Type | Sound Type | Annoyance (1-10) | Detectability (Prob) |
    | :--- | :--- | :--- | :--- |
    | **ICE (Diesel)** | Diesel Engine | 3.5 | 0.98 |
    | **EV (Silent)** | Tire Noise Only | 1.0 | 0.40 (Dangerously Low) |
    | **EV (Pure Tone)** | Pure AVAS | 5.4 | 0.95 |
    | **EV (Complex)** | Optimized AVAS | 4.8 | 0.90 |

#### Resource C: Gap Acceptance Behavior
**Source**: Standard Traffic Engineering Models (e.g., TRB, WesternITE).
-   **Finding**: Pedestrians accept gaps based on a probabilistic threshold.
-   **Model Parameter**:
    -   **Critical Gap ($\beta$)**: Follows Normal Distribution $N(\mu=5.0s, \sigma=1.2s)$.
    -   If $Gap > \beta$, pedestrian attempts to cross.

### 3. Simulation Model Logic

#### Traffic Generation
-   Vehicles arrive following a **Poisson Process** ($\lambda$ vehicles/minute).
-   Vehicle type is assigned based on the active Scenario probability distribution.

#### Pedestrian Behavior
-   Pedestrians arrive at the curb.
-   **Detection Step**: For each approaching vehicle, the pedestrian attempts to hear/see it.
    -   `Success = random() < Vehicle.Detectability`.
    -   If **Failed**: The pedestrian treats the road as "Clear" and may step out into traffic (High Risk).
-   **Gap Acceptance Step**: If detected, the pedestrian estimates the time gap.
    -   Samples personal aggression ($\beta$).
    -   If $Gap > \beta$, crosses.

#### Collision Logic
-   If `Pedestrian.Rect` overlaps `Vehicle.Rect`: Collision recorded.
-   **Severity Roll**: Based on Vehicle Type (Ref A).

### 4. Scenarios

#### Scenario 1: The "Silent Risk" (Early Adoption)
-   **Fleet**: 50% ICE, 50% Silent EVs (No AVAS).
-   **Hypothesis**: Low Noise Pollution, but High Collision Rate due to detection failures.

#### Scenario 2: The "Loud Future" (Bad Regulation)
-   **Fleet**: 20% ICE, 80% EV with "Pure Tone" AVAS.
-   **Hypothesis**: High Noise Pollution (Annoying), Low Collision Rate.

#### Scenario 3: "Optimized Balance"
-   **Fleet**: 20% ICE, 80% EV with "Complex" AVAS.
-   **Hypothesis**: Manageable Noise, Good Safety.
