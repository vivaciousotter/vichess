RAYLIB_LIBS := raylib GL m pthread dl rt X11 
BUILD_DIR := ./build
BUILD_TARGET := $(BUILD_DIR)/chess
CXXFLAGS := -std=c++20
SRC_DIRS := ./src
#find all .cpp files
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

#define build targets in the build directory for each file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)


LDFLAGS = $(addprefix -l,$(RAYLIB_LIBS))

# Final build 
$(BUILD_TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	rm -r $(BUILD_DIR)
