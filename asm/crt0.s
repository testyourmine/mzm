    .include "asm/constants.inc"
    .include "asm/macros.inc"

    .syntax unified

    arm_func_start _start
_start: @ 0x080000c0
    mov r0, #PSR_IRQ_MODE
    msr cpsr_fc, r0
    ldr sp, gSpIrq_ptr
    mov r0, #PSR_SYS_MODE
    msr cpsr_fc, r0
    ldr sp, gSpSys_ptr
    ldr r1, gIntrVector_ptr
    add r0, pc, #0x20 @ IntrMain
    str r0, [r1]
    ldr r1, agbmain_ptr
    mov lr, pc
    bx r1
    b _start

@ pool
gSpSys_ptr: .4byte gSpSys
gSpIrq_ptr: .4byte gSpIrq
gIntrVector_ptr: .4byte gIntrVector
agbmain_ptr: .4byte agbmain
