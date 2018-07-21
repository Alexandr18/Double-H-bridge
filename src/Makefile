PRG            = main
OBJ            = main.o chan.o
MCU_TARGET     = attiny2313a
DUDE_TARGET    = t2313
OPTIMIZE       = -Os

DEFS           = -DF_CPU=1000000
LIBS           = -lm

EXTRA_CLEAN_FILES = *.bin *.d

# You should not have to change anything below here.

CC             = avr-g++

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -std=c++11 -Wall -Werror -Wpedantic $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -fdata-sections -ffunction-sections
override LDFLAGS       = -Wl,-Map,$(PRG).map,--gc-sections

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
SIZE       	   = avr-size
PROG           = avrdude

##all: $(PRG).elf lst text eeprom
all: $(PRG).elf lst text eeprom size

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@printf "\n\n"

clean:
	@printf "Cleaning up ...\n"
	@rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak
	@rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)
	@printf "Cleaning complete!\n\n"

lst:  $(PRG).lst

%.lst: %.elf
	@$(OBJDUMP) -h -S $< > $@
	@printf "Dumping\n"

# Rules for building the .text rom images

text: bin

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@
	@printf "Dumping HEX\n"

%.srec: %.elf
	@$(OBJCOPY) -j .text -j .data -O srec $< $@
	@printf "Dumping SREC\n"

%.bin: %.elf
	@$(OBJCOPY) -j .text -j .data -O binary $< $@
	@printf "Dumping BIN\n"

# Rules for building the .eeprom rom images

eeprom: ebin

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@
	@printf "Dumping EEPROM\n"

%_eeprom.srec: %.elf
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@
	@printf "Dumping EEPROM SREC\n"

%_eeprom.bin: %.elf
	@$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@
	@printf "Dumping EEPROM BIN\n"

size:
	@printf "\n\n"
	@$(SIZE) -B --mcu=$(MCU_TARGET) $(PRG).elf
	@$(SIZE) -C --mcu=$(MCU_TARGET) $(PRG).elf
	@printf "\n\n"

dude: $(PRG).bin $(PRG)_eeprom.bin
	$(PROG) -i 16 -B 16 -p $(DUDE_TARGET) -c dragon_isp -P usb -U flash:w:$(PRG).bin:r #-U eeprom:w:$(PRG)_eeprom.bin:r
