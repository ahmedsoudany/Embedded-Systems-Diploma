/* Learn_in_depth.com
   Mastering Embedded Systems online Diploma
   Eng. Ahmed Melik Alnasser */
#include "stdint.h"

void Reset_Handler ();
extern int main(void);


void Default_Handler()
{
   Reset_Handler();
}

void NMI_Hnadler(void)         __attribute__((weak,alias("Default_Handler")));;
void H_Fault_Handler(void)     __attribute__((weak,alias("Default_Handler")));;


//reserve stack size
static unsigned long Stack_top[256]; //256*4 = 1024
 

void (* const G_P_fn_Vectors[])() __attribute__((section(".vectors"))) = 
{
   (void (*)())  ((unsigned long)Stack_top + sizeof(Stack_top)),
   &Reset_Handler,
   &NMI_Hnadler,
   &H_Fault_Handler
};


extern unsigned int _S_DATA;
extern unsigned int _E_DATA;
extern unsigned int _S_BSS;
extern unsigned int _E_BSS;
extern unsigned int _E_TEXT;

void Reset_Handler (void)
{
   volatile int i;
   //copy data from ROM to RAM 
   unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA;
   unsigned char* P_src = (unsigned char*)&_E_TEXT;
   unsigned char* P_dst = (unsigned char*)&_S_DATA;
   for (i = 0 ; i < DATA_size ; i++)
   {
      *((unsigned char*)P_dst++) = *((unsigned char*)P_src++); 
   }

   unsigned int Bss_size = (unsigned char*)&_E_BSS - (unsigned char*)&_S_BSS;
   P_dst = (unsigned char*)&_S_BSS;
   for (i = 0 ; i < Bss_size ; i++)
   {
      *((unsigned char*)P_dst++) = (unsigned char)0;
   }

   //jump to main

   main(); 
}

/*
uint32_t vectors[] __attribute__((section(".vectors"))) = {
   (uint32_t) &_STACK_TOP,
   (uint32_t) &Rest_Handler,
   (uint32_t) &NMI_Hnadler,
   (uint32_t) &H_Fault_Handler,
   (uint32_t) &MM_Fault_Handler,
   (uint32_t) &Bus_Hnadler,
   (uint32_t) &Usage_Fault_Hnadler
};
*/