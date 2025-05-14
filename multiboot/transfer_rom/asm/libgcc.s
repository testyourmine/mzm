    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start __divsi3
__divsi3: @ 0x02001744
	cmp r1, #0
	beq _020017CC
	push {r4}
	adds r4, r0, #0
	eors r4, r1
	mov ip, r4
	movs r3, #1
	movs r2, #0
	cmp r1, #0
	bpl _0200175A
	rsbs r1, r1, #0
_0200175A:
	cmp r0, #0
	bpl _02001760
	rsbs r0, r0, #0
_02001760:
	cmp r0, r1
	blo _020017BE
	movs r4, #1
	lsls r4, r4, #0x1c
_02001768:
	cmp r1, r4
	bhs _02001776
	cmp r1, r0
	bhs _02001776
	lsls r1, r1, #4
	lsls r3, r3, #4
	b _02001768
_02001776:
	lsls r4, r4, #3
_02001778:
	cmp r1, r4
	bhs _02001786
	cmp r1, r0
	bhs _02001786
	lsls r1, r1, #1
	lsls r3, r3, #1
	b _02001778
_02001786:
	cmp r0, r1
	blo _0200178E
	subs r0, r0, r1
	orrs r2, r3
_0200178E:
	lsrs r4, r1, #1
	cmp r0, r4
	blo _0200179A
	subs r0, r0, r4
	lsrs r4, r3, #1
	orrs r2, r4
_0200179A:
	lsrs r4, r1, #2
	cmp r0, r4
	blo _020017A6
	subs r0, r0, r4
	lsrs r4, r3, #2
	orrs r2, r4
_020017A6:
	lsrs r4, r1, #3
	cmp r0, r4
	blo _020017B2
	subs r0, r0, r4
	lsrs r4, r3, #3
	orrs r2, r4
_020017B2:
	cmp r0, #0
	beq _020017BE
	lsrs r3, r3, #4
	beq _020017BE
	lsrs r1, r1, #4
	b _02001786
_020017BE:
	adds r0, r2, #0
	mov r4, ip
	cmp r4, #0
	bpl _020017C8
	rsbs r0, r0, #0
_020017C8:
	pop {r4}
	mov pc, lr
_020017CC:
	push {lr}
	bl __div_by_zero
	movs r0, #0
	pop {pc}
	.align 2, 0

    thumb_func_start __div_by_zero
__div_by_zero: @ 0x0808acc8
    mov pc, lr
    .align 2, 0

    thumb_func_start __udivsi3
__udivsi3: @ 0x0808ade0
    cmp r1, #0
    beq lbl_0808ae4e
    movs r3, #1
    movs r2, #0
    push {r4}
    cmp r0, r1
    blo lbl_0808ae48
    movs r4, #1
    lsls r4, r4, #0x1c
lbl_0808adf2:
    cmp r1, r4
    bhs lbl_0808ae00
    cmp r1, r0
    bhs lbl_0808ae00
    lsls r1, r1, #4
    lsls r3, r3, #4
    b lbl_0808adf2
lbl_0808ae00:
    lsls r4, r4, #3
lbl_0808ae02:
    cmp r1, r4
    bhs lbl_0808ae10
    cmp r1, r0
    bhs lbl_0808ae10
    lsls r1, r1, #1
    lsls r3, r3, #1
    b lbl_0808ae02
lbl_0808ae10:
    cmp r0, r1
    blo lbl_0808ae18
    subs r0, r0, r1
    orrs r2, r3
lbl_0808ae18:
    lsrs r4, r1, #1
    cmp r0, r4
    blo lbl_0808ae24
    subs r0, r0, r4
    lsrs r4, r3, #1
    orrs r2, r4
lbl_0808ae24:
    lsrs r4, r1, #2
    cmp r0, r4
    blo lbl_0808ae30
    subs r0, r0, r4
    lsrs r4, r3, #2
    orrs r2, r4
lbl_0808ae30:
    lsrs r4, r1, #3
    cmp r0, r4
    blo lbl_0808ae3c
    subs r0, r0, r4
    lsrs r4, r3, #3
    orrs r2, r4
lbl_0808ae3c:
    cmp r0, #0
    beq lbl_0808ae48
    lsrs r3, r3, #4
    beq lbl_0808ae48
    lsrs r1, r1, #4
    b lbl_0808ae10
lbl_0808ae48:
    adds r0, r2, #0
    pop {r4}
    mov pc, lr
lbl_0808ae4e:
    push {lr}
    bl __div_by_zero
    movs r0, #0
    pop {pc}
