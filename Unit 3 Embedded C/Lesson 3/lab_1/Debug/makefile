#Prepared by Ahmed Melik Alnasser
CC     = arm-none-eabi-
CFLAGS = -mcpu=arm926ej-s -g
INCS   =-I .
LIBS   =
SRC    = $(wildcard *.c) 
OBJ    = $(SRC:.c=.o)# same as OBJS = $(patsubst %.c,%.o,$SRC)
As     = $(wildcard *.s) 
AsOBJ  = $(As:.s=.o) 
Project_Name = Ahmed-Melik-Alnasser

All: $(Project_Name).bin
	@echo "Build is Done"	

%.o: %.s
	$(CC)as.exe  $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) 	-c $< -o $@

$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *elf *.bin
	@echo "Everything Clean"

clean:
	rm *.elf *.bin