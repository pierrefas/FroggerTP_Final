
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk

# --- Conditionally apply Allegro flags based on HDMI ---
ifeq ($(HDMI_CONNECTED),yes)
    ALLEGRO_LIBS := -lallegro -lallegro_font
    @echo "Display detected. Building with Allegro support."
else
    ALLEGRO_LIBS :=
    # Optional: Pass a preprocessor flag to your C code (like -DHEADLESS)
    CFLAGS += -DHEADLESS 
endif
# --------------------------------------------------------

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \

BUILD_ARTIFACT_NAME := TP_final
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# All Target
all: main-build

# Main-build Target
main-build: TP_final

# Tool invocations
# We replaced manual "-lallegro -lallegro_font" with $(ALLEGRO_LIBS)
TP_final: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "TP_final" $(OBJS) $(USER_OBJS) $(LIBS) $(ALLEGRO_LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) TP_final
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets