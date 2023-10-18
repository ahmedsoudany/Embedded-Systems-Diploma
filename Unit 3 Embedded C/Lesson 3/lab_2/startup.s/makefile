#Prepared by Ahmed Melik Alnasser
CC     = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -gdwarf-2
INCS   =-I .
LIBS   =
SRC    = $(wildcard *.c) 
OBJ    = $(SRC:.c=.o)# same as OBJS = $(patsubst %.c,%.o,$SRC)
As     = $(wildcard *.s) 
AsOBJ  = $(As:.s=.o) 
LINKER = $(wildcard *.ld)
Project_Name = Ahmed-Melik-Alnasser_cortexM4

All: $(Project_Name).hex
	@echo "Build is Done"	

%.o: %.s
	$(CC)as.exe  $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@

$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T $(LINKER) $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map

$(Project_Name).hex: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *elf *.hex
	@echo "Everything Clean"

clean:
	rm *.elf *.hex