    .include "asm/macros.inc"
    .include "asm/constants.inc"

    .syntax unified

    thumb_func_start CpuSet
CpuSet: @ 0x08005194
    swi SYSCALL_CPUSet
    bx lr

    thumb_func_start LZ77UncompVRAM
LZ77UncompVRAM: @ 0x080051a4
    swi SYSCALL_LZ77UnCompVRAM
    bx lr

    thumb_func_start VBlankIntrWait
VBlankIntrWait: @ 0x080051cc
    movs r2, 0
    swi SYSCALL_VBlankIntrWait
    bx lr

    .align 2, 0 @ don't insert nops
