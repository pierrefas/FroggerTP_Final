
-include ../makefile.init

RM := rm -rf

# IS_PI tiene que calcularse ANTES de meter subdir.mk: ese archivo lo
# usa en su propio "ifeq ($(IS_PI),1)" para decidir si suma gameloop.o/
# disdrv.o/joydrv.o al link, y los ifeq se evaluan en el momento en que
# se lee cada archivo. Si se calcula despues (como estaba antes), subdir.mk
# siempre ve IS_PI vacio y ese bloque nunca se activa, ni en una Raspberry Pi real.
IS_PI := $(shell grep -i "raspberry pi" /proc/device-tree/model 2>/dev/null)

ifeq ($(IS_PI),)
    IS_PI = 0
else
    IS_PI = 1
endif

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk

# si hay una conexion por hdmi en el raspberry pi permito que se agreguen las librerias de allegro
ifeq ($(filter yes,$(HDMI_CONNECTED) $(FORCE_ALLEGRO)),yes)
    $(info Building with Allegro support (HDMI detected or forced).)
    ALLEGRO_LIBS := -lallegro -lallegro_font -lallegro_image -lallegro_primitives
    CFLAGS :=
else
    # paso un flag DHEADLESS para archivos como "main.c" que puede usar Allegro o no.
    CFLAGS += -DHEADLESS
endif

# gameloop.o (run_headless_game) solo se compila/linkea con IS_PI=1 (ver
# subdir.mk). HEADLESS se define en cualquier maquina sin HDMI, Pi o no;
# sin este flag aparte, main.c llamaria run_headless_game() tambien en un
# PC sin Pi y el link fallaria con "undefined reference".
ifeq ($(IS_PI),1)
    CFLAGS += -DIS_PI
endif

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

# cambie el codigo de eclipse de "-lallegro -lallegro_font" con $(ALLEGRO_LIBS)
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