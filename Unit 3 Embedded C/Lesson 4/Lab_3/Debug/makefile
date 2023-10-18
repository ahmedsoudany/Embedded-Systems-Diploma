#Prepared by Ahmed Melik Alnasser
CC     = arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -gdwarf-2
INCS   =-I .
LIBS   =
SRC    = $(wildcard *.c) 
OBJ    = $(SRC:.c=.o)# same as OBJS = $(patsubst %.c,%.o,$SRC)
As     = $(wildcard *.s) 
AsOBJ  = $(As:.s=.o) 
LINKER = $(wildcard *.ld)
Project_Name = Embedded_C_Lesoon_3_lab4_cortexM4

All: $(Project_Name).bin
	@echo "Build is Done"	

%.o: %.s
	$(CC)as.exe  $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) 	-c $< -o $@

$(Project_Name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T $(LINKER) $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map

$(Project_Name).bin: $(Project_Name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *elf *.bin
	@echo "Everything Clean"

clean:
	rm *.elf *.bin