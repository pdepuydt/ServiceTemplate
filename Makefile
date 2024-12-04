#
# Project: YourService

# Variables
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -lsystemd
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TARGET = $(BIN_DIR)/YourService
SERVICE_FILE = /etc/systemd/system/yourservice.service
BINARY = /usr/local/bin/YourService

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete: $@"

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Install target
install: all
	@sudo mkdir -p /usr/local/bin
	@sudo cp $(TARGET) $(BINARY)
	@sudo mkdir -p /etc/systemd/system
	@sudo cp config/teledatascope.service $(SERVICE_FILE)
	@echo "Installation complete. Service file and binary installed."

# Remove target
remove:
	@echo "Stopping and disabling the service..."
	@sudo systemctl stop yourservice.service || true
	@sudo systemctl disable yourservice.service || true
	@echo "Removing service file and binary..."
	@sudo rm -f $(SERVICE_FILE)
	@sudo rm -f $(BINARY)
	@echo "Reloading systemd daemon..."
	@sudo systemctl daemon-reload
	@sudo systemctl reset-failed
	@echo "Removal complete."

# Test target
test:
	$(MAKE) -C tests

# Clean target
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned up build artifacts."

# Phony targets
.PHONY: all install test clean
