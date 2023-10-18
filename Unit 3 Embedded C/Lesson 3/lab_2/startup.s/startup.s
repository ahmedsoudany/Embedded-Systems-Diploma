/* Learn_in_depth.com
   Mastering Embedded Systems online Diploma
   Eng. Ahmed Melik Alnasser */

.section .vectors

.word  0x200010000    /*stack top address*/
.word  _reset          /* 1 Reset*/
.word  Vector_handler /* 2 NMI*/
.word  Vector_handler /* 3 Hard Fault*/
.word  Vector_handler /* 4 MM Fault*/
.word  Vector_handler /* 5 Bus Fault*/
.word  Vector_handler /* 6 Usage Fault*/
.word  Vector_handler /* 7  RESERVED*/
.word  Vector_handler /* 8  RESERVED*/
.word  Vector_handler /* 9  RESERVED*/
.word  Vector_handler /* 10 RESERVED*/
.word  Vector_handler /* 11 Sv Call*/
.word  Vector_handler /* 12 Debug reserved*/
.word  Vector_handler /* 13 RESERVED*/
.word  Vector_handler /* 14 PendSV*/
.word  Vector_handler /* 14 Systick*/
.word  Vector_handler /* 14 IRQ0*/
.word  Vector_handler /* 14 IRQ0*/
.word  Vector_handler /* 14 IRQ0*/
.word  Vector_handler /* 19 ....*/
          /* oN TO IRQ67 */

.section .text
_reset:
    bl main
    b .

.thumb_func
Vector_handler:
   b _reset
