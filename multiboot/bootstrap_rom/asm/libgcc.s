    .include "asm/macros.inc"

    .syntax unified

    thumb_func_start _call_via_r0
_call_via_r0:
    bx r0
    nop

    thumb_func_start _call_via_r1
_call_via_r1:
    bx r1
    nop

    thumb_func_start _call_via_r2
_call_via_r2:
    bx r2
    nop

    thumb_func_start _call_via_r3
_call_via_r3:
    bx r3
    nop

    thumb_func_start _call_via_r4
_call_via_r4:
    bx r4
    nop

    thumb_func_start _call_via_r5
_call_via_r5:
    bx r5
    nop

    thumb_func_start _call_via_r6
_call_via_r6:
    bx r6
    nop

    thumb_func_start _call_via_r7
_call_via_r7:
    bx r7
    nop

    thumb_func_start _call_via_r8
_call_via_r8:
    bx r8
    nop

    thumb_func_start _call_via_r9
_call_via_r9:
    bx r9
    nop

    thumb_func_start _call_via_sl
_call_via_sl:
    bx sl
    nop

    thumb_func_start _call_via_fp
_call_via_fp:
    bx fp
    nop

    thumb_func_start _call_via_ip
_call_via_ip:
    bx ip
    nop

    thumb_func_start _call_via_sp
_call_via_sp:
    bx sp
    nop

    thumb_func_start _call_via_lr
_call_via_lr:
    bx lr
    nop

	thumb_func_start __divsi3
__divsi3: @ 0x0300120C
	cmp r1, #0
	beq _03001294
	push {r4}
	adds r4, r0, #0
	eors r4, r1
	mov ip, r4
	movs r3, #1
	movs r2, #0
	cmp r1, #0
	bpl _03001222
	rsbs r1, r1, #0
_03001222:
	cmp r0, #0
	bpl _03001228
	rsbs r0, r0, #0
_03001228:
	cmp r0, r1
	blo _03001286
	movs r4, #1
	lsls r4, r4, #0x1c
_03001230:
	cmp r1, r4
	bhs _0300123E
	cmp r1, r0
	bhs _0300123E
	lsls r1, r1, #4
	lsls r3, r3, #4
	b _03001230
_0300123E:
	lsls r4, r4, #3
_03001240:
	cmp r1, r4
	bhs _0300124E
	cmp r1, r0
	bhs _0300124E
	lsls r1, r1, #1
	lsls r3, r3, #1
	b _03001240
_0300124E:
	cmp r0, r1
	blo _03001256
	subs r0, r0, r1
	orrs r2, r3
_03001256:
	lsrs r4, r1, #1
	cmp r0, r4
	blo _03001262
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
_03001262:
	lsrs r4, r1, #2
	cmp r0, r4
	blo _0300126E
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
_0300126E:
	lsrs r4, r1, #3
	cmp r0, r4
	blo _0300127A
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
_0300127A:
	cmp r0, #0
	beq _03001286
	lsrs r3, r3, #4
	beq _03001286
	lsrs r1, r1, #4
	b _0300124E
_03001286:
	adds r0, r2, #0
	mov r4, ip
	cmp r4, #0
	bpl _03001290
	rsbs r0, r0, #0
_03001290:
	pop {r4}
	mov pc, lr
_03001294:
	push {lr}
	bl __div_by_zero
	movs r0, #0
	pop {pc}
	.align 2, 0

	thumb_func_start __div_by_zero
__div_by_zero: @ 0x030012A0
	mov pc, lr
	.align 2, 0

	thumb_func_start __udivsi3
__udivsi3: @ 0x030012A4
	cmp r1, #0
	beq _03001312
	movs r3, #1
	movs r2, #0
	push {r4}
	cmp r0, r1
	blo _0300130C
	movs r4, #1
	lsls r4, r4, #0x1c
_030012B6:
	cmp r1, r4
	bhs _030012C4
	cmp r1, r0
	bhs _030012C4
	lsls r1, r1, #4
	lsls r3, r3, #4
	b _030012B6
_030012C4:
	lsls r4, r4, #3
_030012C6:
	cmp r1, r4
	bhs _030012D4
	cmp r1, r0
	bhs _030012D4
	lsls r1, r1, #1
	lsls r3, r3, #1
	b _030012C6
_030012D4:
	cmp r0, r1
	blo _030012DC
	subs r0, r0, r1
	orrs r2, r3
_030012DC:
	lsrs r4, r1, #1
	cmp r0, r4
	blo _030012E8
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
_030012E8:
	lsrs r4, r1, #2
	cmp r0, r4
	blo _030012F4
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
_030012F4:
	lsrs r4, r1, #3
	cmp r0, r4
	blo _03001300
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
_03001300:
	cmp r0, #0
	beq _0300130C
	lsrs r3, r3, #4
	beq _0300130C
	lsrs r1, r1, #4
	b _030012D4
_0300130C:
	adds r0, r2, #0
	pop {r4}
	mov pc, lr
_03001312:
	push {lr}
	bl __div_by_zero
	movs r0, #0
	pop {pc}
	.align 2, 0
