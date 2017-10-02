# Distributed under the BSD License (See accompanying file /LICENSE )
# Build : exorcism project

CMAKE_PRG ?= $(shell (command -v cmake3 || echo cmake))
CMAKE_BUILD_TYPE ?= Debug
CMAKE_FLAGS := -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

BUILD_TYPE ?= $(shell (type ninja > /dev/null 2>&1 && echo "Ninja") || \
                echo "Unix Makefiles")

ifeq (,$(BUILD_TOOL))
	ifeq (Ninja,$(BUILD_TYPE))
		ifneq ($(shell $(CMAKE_PRG) --help 2>/dev/null | grep Ninja),)
			BUILD_TOOL := ninja
		else
			# User's version of CMake doesn't support Ninja
			BUILD_TOOL = $(MAKE)
			BUILD_TYPE := Unix Makefiles
		endif
	else
		BUILD_TOOL = $(MAKE)
	endif
endif

BUILD_CMD = $(BUILD_TOOL)

all: exorcism

exorcism: build/.ran-cmake
	+$(BUILD_CMD) -C build

cmake:
	touch CMakeLists.txt
	$(MAKE) build/.ran-cmake

build/.ran-cmake:
	mkdir -p build
	cd build && $(CMAKE_PRG) -G '$(BUILD_TYPE)' $(CMAKE_FLAGS) ..
	touch $@

clean:
	+test -d build && $(BUILD_CMD) -C build clean || true

distclean: clean
	rm -rf .deps build

.PHONY: clean distclean cmake
