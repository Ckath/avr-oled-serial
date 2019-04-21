# see LICENSE file for copyright and license details.

# device configuration
DEV=/dev/ttyACM0
MODEL=atmega328p
BAUD=115200
PROG=arduino
F_CPU=16000000UL

NAME=oledserial
SRC= lib/font.c lib/i2c.c lib/lcd.c lib/circular_usart.c ${NAME}.c
OBJ = ${SRC:.c=.o}

options:
	@echo ${NAME} make options:
	@echo "   clean:  clean temporary files"
	@echo "   hex  :  compile source to hex binary"
	@echo "   flash:  upload hex binary to device"

.c.o: 
	@echo CC -c $< 
# -Os fucks up sscanf here
	@avr-gcc -DF_CPU=${F_CPU} -mmcu=${MODEL} -c $< -o ${<:.c=.o}

${NAME}: ${SRC} ${OBJ} 
	@echo compiling binary
	@avr-gcc -Os -DF_CPU=${F_CPU} -mmcu=${MODEL} -o ${NAME} ${OBJ}

clean:
	@echo cleaning
	@rm -f ${NAME} *.o *.hex lib/*.o

hex: ${NAME}
	@echo creating hex
	@avr-objcopy -O ihex -R .eeprom ${NAME} ${NAME}.hex

flash: hex
	@echo preparing to flash
	@avrdude -F -V -c ${PROG} -p ${MODEL} -P ${DEV} -b ${BAUD} -U flash:w:${NAME}.hex
