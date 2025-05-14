    .include "asm/constants.inc"
    .include "asm/macros.inc"

    .syntax unified

    arm_func_start _start
_start: @ 0x030000c0
	mov r0, #PSR_IRQ_MODE
	msr cpsr_fc, r0
	ldr sp, sp_irq_ptr @ =sp_irq
	mov r0, #PSR_SYS_MODE
	msr cpsr_fc, r0
	ldr sp, sp_sys_ptr @ =sp_sys
	ldr r1, intr_vector_ptr @ =intr_vector
	add r0, pc, #0x20 @ =IntrMain
	str r0, [r1]
	ldr r1, agbmain_ptr @ =AgbMain
	mov lr, pc
	bx r1
	b _start
	.align 2, 0
sp_sys_ptr: .4byte sp_sys
sp_irq_ptr: .4byte sp_irq
intr_vector_ptr: .4byte intr_vector
agbmain_ptr: .4byte AgbMain
