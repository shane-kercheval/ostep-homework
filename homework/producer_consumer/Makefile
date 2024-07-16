BUILD_DIR := build

.PHONY: all compile setup_build_dir clean run

all: compile

# Create the build directory and run cmake
setup_build_dir:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..

# Compile the project using the generated Makefile by CMake
compile: setup_build_dir
	$(MAKE) -C $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: compile
	@$(BUILD_DIR)/producer_consumer || { echo 'Error running producer_consumer'; exit 1; }
