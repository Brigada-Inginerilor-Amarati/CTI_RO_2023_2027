# folders for executables
BIN_DIR = bin
BIN_TREASURE_MANAGER = treasure_manager
BIN_TREASURE_MONITOR = treasure_monitor
BIN_TREASURE_HUB = treasure_hub
BIN_CALCULATOR = treasure_calculator

# compiler + flags
CC = gcc
CFLAGS = -Wall

# MAIN SOURCE
SRC_MANAGER = src/treasure_manager/treasure_manager.c

SRC_MONITOR= src/treasure_hub/Monitor/monitor.c

SRC_HUB = src/treasure_hub/Hub/hub.c

SRC_CALCULATOR = src/treasure_hub/Calculate_Score/calculate_score.c

# libraries
SRC_treasure_manager = $(shell find src/treasure_manager/Libraries -name "*.c")

SRC_treasure_monitor = $(shell find src/treasure_hub/Monitor/Libraries -name "*.c")

SRC_treasure_hub = $(shell find src/treasure_hub/Hub/Libraries -name "*.c")
init:
	@echo "Initializing project..."

build:
	@echo "Building project..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_TREASURE_MANAGER) $(SRC_treasure_manager) $(SRC_MANAGER)
	@echo "Build complete."

	@echo "Building treasure_hub..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_TREASURE_HUB) $(SRC_treasure_hub) $(SRC_HUB)
	@echo "Build complete."	

	@echo "Building treasure_monitor..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_TREASURE_MONITOR) $(SRC_treasure_monitor) $(SRC_MONITOR)
	@echo "Build complete."

	@echo "Building treasure_calculator..."
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(BIN_CALCULATOR) $(SRC_CALCULATOR)
	@echo "Build complete."

clean:
	@echo "Cleaning project..."
	rm -f $(BIN_DIR)/$(BIN_TREASURE_MANAGER)
	@echo "Clean complete."