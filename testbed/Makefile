TARGET		= Testbed

PRX			?= 1

CC			= psp-gcc
CXX			= psp-g++

INCDIR		= ../
SRC_DIR		= $(CURDIR)
BUILD_DIR	= build

SRCS		:= $(shell find $(SRC_DIR) -name '*.cpp')
OBJS		:= $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

LIBS		= -lgtest -lVectorMathVFPU -lm -lpspdebug -lpspctrl -lstdc++
LDFLAGS		:= -g $(LIBS) -L../bin

CFLAGS		:= -Wall
CFLAGS		+= -g -O0

CXXFLAGS	= $(CFLAGS) -std=gnu++17

.PHONY: all clean pack

all: $(BUILD_DIR)/$(TARGET) EBOOT.PBP pack

# make sure build directory exists
$(BUILD_DIR):
	@echo	"Creating build directory.."
	@mkdir	-p $@

# compile .c files to the build dir
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo	"Compiling $<.."
	$(CC)	$(CFLAGS) -c -o $@ $<

# link to executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@echo	"Linking.."
	$(CC)	$(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	@echo	"Cleaning.."
	@rm		-rf build

pack: EBOOT.PBP
	@echo	"Packing files to bin folder.."
	@rm		PARAM.SFO
	@mkdir	-p bin/$(TARGET)
	@mv		-f EBOOT.PBP bin/$(TARGET)/
	@mv		-f $(TARGET).prx bin/$(TARGET)/ 2>/dev/null || true
	@mv		-f $(TARGET).elf bin/$(TARGET)/ 2>/dev/null || true

# convert to EBOOT.PBP using build.mak
EXTRA_TARGETS	= EBOOT.PBP
PSP_EBOOT_TITLE	= Sony VectorMath VFPU Testbed
BUILD_PRX		= $(PRX)

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
