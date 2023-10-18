/* Learn_in_depth.com
   Mastering Embedded Systems online Diploma
   Eng. Ahmed Melik Alnasser */

MEMORY
{
   flash(RX) : ORIGIN = 0X08000000, LENGTH = 128K
   sram(RWX) : ORIGIN = 0X20000000, LENGTH = 20K 
}

SECTIONS
{
   .text : 
   {
       *(.vectors*)
       *(.text*)
   } > flash
   .bss  : 
   { 
       *(.bss*) 
   } > sram
}