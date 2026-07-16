
#cuando hagan un nuevo archivo metanlo en los sources, c_deps y objs
#al pedo se los digo si total lo voy a hacer yo

#me robe el makefile de eclipse

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../a_PC_display.c \
../a_sprites.c \
../a_map.c \
../checking.c \
../entityupdates.c \
../frogupdates.c \
../joystick.c \
../levelset.c \
../main.c

C_DEPS += \
./a_PC_display.d \
./a_sprites.d \
./a_map.d \
./checking.d \
./entityupdates.d \
./frogupdates.d \
./joystick.d \
./levelset.d \
./main.d

OBJS += \
./a_PC_display.o \
./a_sprites.o \
./a_map.o \
./checking.o \
./entityupdates.o \
./frogupdates.o \
./joystick.o \
./levelset.o \
./main.o

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./*.d ./*.o

.PHONY: clean--2e-

