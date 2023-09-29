@@ Ahmed Melik Alnasser (learn-in-depth.com)
.globl reset 
reset:
        ldr sp, = stack_top
        bl main
stop:   b  stop 
