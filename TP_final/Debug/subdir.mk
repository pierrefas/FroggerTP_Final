
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
./main.o

# gameloop.c: orquestador para el hardware fisico (LEDs + joystick). Se
# agrega mas abajo a C_SRCS/C_DEPS/OBJS solo bajo IS_PI, junto con
# disdrv.o/joydrv.o, porque depende de esos dos objetos.


# filtro los archivos "a_" si no hay conexion por hdmi o
ifeq ($(HDMI_CONNECTED),no and $(FORCE_ALLEGRO),no)
    C_SRCS := $(filter-out ../a_%,$(C_SRCS))
    C_DEPS := $(filter-out ./a_%,$(C_DEPS))
    OBJS   := $(filter-out ./a_%,$(OBJS))
endif

ifeq ($(IS_PI),1)
	C_SRCS += \
	../joystick.c 

	C_DEPS += \
	./joystick.d 

	OBJS += \
	./disdrv.o \
	./joydrv.o \
	./joystick.o 

endif

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc $(CFLAGS) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./*.d ./*.o

.PHONY: clean--2e-

