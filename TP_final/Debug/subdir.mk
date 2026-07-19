
#cuando hagan un nuevo archivo metanlo en los sources, c_deps y objs
#al pedo se los digo si total lo voy a hacer yo

#me robe el makefile de eclipse

# Add inputs and outputs from these tool invocations to the build variables 

HDMI1 := $(shell cat /sys/class/drm/card0-HDMI-A-1/status 2>/dev/null)
HDMI2 := $(shell cat /sys/class/drm/card0-HDMI-A-2/status 2>/dev/null)

ifeq ($(HDMI1),connected)
    HDMI_CONNECTED := yes
else ifeq ($(HDMI2),connected)
    HDMI_CONNECTED := yes
else
    HDMI_CONNECTED := no
endif

C_SRCS += \
../a_alphanum.c \
../a_PC_display.c \
../a_sprites.c \
../a_map.c \
../a_pause.c \
../checking.c \
../entityupdates.c \
../frogupdates.c \
../gamestate.c \
../levelset.c \
../scores.c \
../highscores.c \
../main.c

C_DEPS += \
./a_alphanum.d \
./a_PC_display.d \
./a_sprites.d \
./a_map.d \
./a_pause.d \
./checking.d \
./entityupdates.d \
./frogupdates.d \
./gamestate.d \
./levelset.d \
./scores.d \
./highscores.d \
./main.d

OBJS += \
./a_alphanum.o \
./a_PC_display.o \
./a_sprites.o \
./a_map.o \
./a_pause.o \
./checking.o \
./entityupdates.o \
./frogupdates.o \
./gamestate.o \
./levelset.o \
./scores.o \
./highscores.o \
./main.o


# filtro los archivos "a_" si no hay conexion por hdmi o
ifeq ($(HDMI_CONNECTED),no and $(FORCE_ALLEGRO),no)
    C_SRCS := $(filter-out ../a_%,$(C_SRCS))
    C_DEPS := $(filter-out ./a_%,$(C_DEPS))
    OBJS   := $(filter-out ./a_%,$(OBJS))
endif

ifeq ($(IS_PI),1)
	C_SRCS += \
	../joystick.c \
	../gameloop.c

	C_DEPS += \
	./joystick.d \
	./gameloop.d

	OBJS += \
	./disdrv.o \
	./joydrv.o \
	./joystick.o \
	./gameloop.o

endif

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

# disdrv.o/joydrv.o son los binarios del profesor: no hay .c del que
# regenerarlos, asi que "clean" no los borra (antes se perdian en cada
# limpieza y habia que volver a copiarlos a mano).
clean--2e-:
	-$(RM) $(filter-out ./disdrv.o ./joydrv.o,$(wildcard ./*.o))
	-$(RM) ./*.d

.PHONY: clean--2e-

