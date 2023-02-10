.PHONY: configure build clean flash

PROJECT_NAME ?= firmware
BUILD_DIR ?= build
BUILD_TYPE ?= Debug
FIRMWARE := $(BUILD_DIR)/$(PROJECT_NAME).elf


configure:
	cmake \
		-GNinja \
		-B$(BUILD_DIR) \
		-DPROJECT_NAME=$(PROJECT_NAME) \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DDUMP_ASM=OFF

build: configure
	cmake --build $(BUILD_DIR)

clean:
	-rm -fR $(BUILD_DIR)

flash: build
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(BUILD_DIR)/$(PROJECT_NAME).elf verify reset exit"