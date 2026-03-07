# Bike Sharing System Simulation - Project Explanation

## 📋 Project Overview

This is **Lab 4** from the Modeling & Simulation course. The project builds an enhanced bike-sharing system simulation using **SimPy** (a discrete-event simulation library in Python). The simulation models a realistic bike-sharing system with dynamic demand patterns, maintenance, rebalancing, and customer satisfaction tracking.

---

## 🎯 Project Objectives

The main goal is to create a comprehensive simulation that demonstrates:

- **Realistic usage patterns** throughout the day
- **System maintenance** handling bike failures
- **Automatic rebalancing** to optimize bike distribution
- **Customer satisfaction** metrics
- **Data visualization** for analysis

---

## 🏗️ System Architecture

### 1. **Multiple Stations** (Requirement 1)

The simulation uses **4 stations** with different configurations:

- **Station One**: Capacity 20, Initial bikes: 10
- **Station Two**: Capacity 15, Initial bikes: 5
- **Station Three**: Capacity 25, Initial bikes: 10
- **Station Four**: Capacity 30, Initial bikes: 15

Each station is a `Station` class object containing:

- A `SimPy Container` to manage bike inventory (tracks available bikes)
- Station name and capacity limits

### 2. **Time-Dependent Trip Probabilities** (Requirement 2)

The system uses **3 time slots** that repeat daily:

#### **Morning Start** (0-240 minutes / 6:00 AM - 10:00 AM)

- Higher probabilities for trips between stations
- Example: Station One → Station Two: 40% probability per minute
- Models morning commute patterns

#### **Midday** (240-600 minutes / 10:00 AM - 4:00 PM)

- Moderate probabilities
- Example: Station One → Station Two: 20% probability per minute
- Models regular daytime usage

#### **Evening** (720-960 minutes / 6:00 PM - 10:00 PM)

- Different probability patterns
- Example: Station One → Station Two: 35% probability per minute
- Models evening commute patterns

**How it works:**

- The `get_current_prob_matrix()` function uses modulo arithmetic to map simulation time to the current time slot
- Each minute, the system checks which time slot applies
- Trip probabilities change automatically based on the time of day

### 3. **Bike Maintenance and Downtime** (Requirement 3)

**Breakdown System:**

- Each bike trip has a **1% chance** (`BREAKDOWN_PROB = 0.01`) of breaking during the journey
- When a bike breaks, it's removed from service and enters a repair process

**Repair Process:**

- Broken bikes take **30 minutes** (`REPAIR_TIME = 30`) to repair
- During repair, the bike is tracked in `bikes_under_repair` list
- After repair, the bike is returned to either:
  1. The destination station (if space available)
  2. The origin station (as fallback)
  3. Lost if both stations are full (edge case)

**Tracking:**

- The `monitor_broken_bikes()` function logs the number of bikes under repair every minute
- This data is visualized in plots

### 4. **Rebalancing Mechanism** (Requirement 4)

The system uses a **Proportional Rebalancing Strategy**:

**How it works:**

- Checks every **20 minutes** (`check_interval=20`)
- Calculates target fill ratio: **55%** of capacity (`target_fill_ratio=0.55`)
- Uses a **hysteresis band** (±10%) to prevent oscillation
- Moves bikes from stations with surplus to stations with deficit

**Algorithm:**

1. Classifies stations as "surplus" (too many bikes) or "deficit" (too few bikes)
2. Sorts stations by surplus/deficit amount
3. Greedily moves bikes from highest surplus to highest deficit
4. Maximum **8 bikes** moved per rebalancing cycle (`max_total_moves=8`)

**Why this approach:**

- Prevents stations from becoming completely empty or full
- Maintains balanced distribution across all stations
- More efficient than simple "fullest to emptiest" strategy

### 5. **Customer Satisfaction Tracking** (Requirement 5)

Tracks two types of unhappy customers:

#### **Unhappy Rent Events:**

- Occurs when a customer wants to rent a bike but the station has **0 bikes available**
- Logged in `unhappy_rent` list with timestamp
- Trip is cancelled immediately

#### **Unhappy Return Events:**

- Occurs when a customer tries to return a bike but the destination station is **full**
- Logged in `unhappy_return` list with timestamp
- System attempts fallback: returns bike to origin station (takes extra time)

**Visualization:**

- Plots show unhappy events over time
- Helps identify patterns (e.g., peak times with more issues)

### 6. **Data Collection and Visualization** (Requirement 6)

The simulation collects and visualizes:

#### **Bike Levels Over Time:**

- Tracks bike count at each station every minute
- Creates two plots:
  1. **Smoothed bike levels** (moving average with 21-minute window)
  2. **Station occupancy percentage** (bikes as % of capacity)

#### **Bikes Under Maintenance:**

- Line plot showing number of bikes being repaired over time
- Helps understand maintenance workload

#### **Customer Satisfaction:**

- Line plot showing unhappy rent and unhappy return events over time
- Different colors for different event types

---

## 🔄 How the Simulation Works

### **Main Processes Running in Parallel:**

1. **Trip Generation** (`generate_trips()`)

   - Runs every minute
   - Checks current time slot
   - Generates trips based on probability matrix
   - Each trip is a separate SimPy process

2. **Station Monitoring** (`monitor_stations()`)

   - Records bike levels every minute
   - Stores data for visualization

3. **Rebalancing** (`rebalance_process_proportional()`)

   - Runs every 20 minutes
   - Redistributes bikes between stations

4. **Broken Bike Monitoring** (`monitor_broken_bikes()`)
   - Logs repair status every minute
   - Tracks maintenance workload

### **Trip Lifecycle:**

```
1. Customer arrives → Check if bike available
   ├─ No bikes → Log unhappy rent event → Exit
   └─ Bike available → Take bike from station

2. Travel for 3-7 minutes (random duration)

3. Check if bike breaks during trip
   ├─ Breaks → Start repair process → Exit
   └─ No break → Continue to return

4. Try to return bike to destination
   ├─ Destination has space → Return bike → Success
   └─ Destination full → Log unhappy return → Try origin station
```

---

## 📊 Key Features and Design Decisions

### **Time Slot Implementation:**

- Uses modulo arithmetic (`current_time % 1440`) to handle multi-day simulations
- Time slots repeat daily automatically
- Default probability matrix for times outside defined slots

### **Proportional Rebalancing:**

- More sophisticated than simple "fullest to emptiest"
- Considers target fill ratio and hysteresis to prevent oscillation
- Limits moves per cycle to avoid excessive rebalancing

### **Repair System:**

- Realistic repair time (30 minutes)
- Intelligent bike return (destination first, origin fallback)
- Tracks repair status globally

### **Error Handling:**

- Handles edge cases (both stations full after repair)
- Fallback mechanisms for failed returns
- Prevents system crashes from unexpected states

---

## 🎨 Visualizations Generated

1. **Bike Levels Plot:**

   - Shows smoothed bike counts at each station over time
   - Bottom subplot shows occupancy percentage
   - Helps identify rebalancing effectiveness

2. **Bikes Under Repair Plot:**

   - Red line showing maintenance workload over time
   - Spikes indicate periods with more breakdowns

3. **Unhappy Customers Plot:**
   - Blue line: Unhappy rent events
   - Orange line: Unhappy return events
   - Helps identify peak problem times

---

## 🔍 Observations You Can Make

When running simulations, look for:

1. **Rebalancing Effectiveness:**

   - Do bike levels stabilize after rebalancing?
   - Are stations maintaining target fill ratios?

2. **Maintenance Impact:**

   - How does breakdown rate affect overall availability?
   - Are repair times sufficient?

3. **Customer Satisfaction:**

   - When do most unhappy events occur? (Probably during peak times)
   - Is rebalancing reducing unhappy events?

4. **Time Slot Patterns:**
   - Do bike levels reflect the different probability patterns?
   - Are morning/evening peaks visible in the data?

---

## 🛠️ Technical Implementation Details

### **SimPy Concepts Used:**

- **Environment**: Controls simulation time
- **Container**: Manages bike inventory (thread-safe)
- **Processes**: Parallel execution of trips, monitoring, rebalancing
- **Timeout**: Time delays for trips and repairs

### **Code Structure:**

- Classes: `Station` (manages bike inventory)
- Functions: Trip generation, rebalancing, monitoring, visualization
- Global variables: Track broken bikes, unhappy customers
- Data structures: Lists for logging, dictionaries for bike levels

---

## 📈 Simulation Parameters

Current configuration:

- **Duration**: 1 day (1440 minutes) - can be extended to 20 days
- **Breakdown probability**: 1% per trip
- **Repair time**: 30 minutes
- **Rebalancing interval**: 20 minutes
- **Target fill ratio**: 55%
- **Max moves per cycle**: 8 bikes

All parameters are easily adjustable for different experiments!

---

## 🎯 Presentation Tips

When presenting this project:

1. **Start with the big picture**: Explain what a bike-sharing system is and why simulation matters
2. **Show the architecture**: Walk through the 4 stations and their configurations
3. **Explain time slots**: Demonstrate how demand changes throughout the day
4. **Highlight smart features**: Proportional rebalancing, maintenance system
5. **Show visualizations**: Point out interesting patterns in the plots
6. **Discuss observations**: Share what you learned from running simulations
7. **Explain design choices**: Why you chose proportional rebalancing, etc.

---

## 💡 Extensions You Could Mention

- **Money earning mechanism** (optional requirement): Track revenue per rental
- **Different rebalancing strategies**: Compare performance
- **Variable repair times**: Based on bike age or damage type
- **Customer waiting**: Queue customers when bikes unavailable
- **Weather effects**: Reduce probabilities during bad weather

---

This simulation demonstrates a realistic, dynamic system with multiple interacting components, real-time adjustments, and comprehensive monitoring - all essential for understanding complex systems in the real world!
