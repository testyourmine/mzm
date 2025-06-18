    .include "asm/macros.inc"
    .include "asm/constants.inc"
    .include "asm/audio_internal_constants.inc"

    .syntax unified

    .text

    thumb_func_start call_soundcode_b
call_soundcode_b: @ 0x08004310
    push {r4, r5, r6, r7}
    mov r4, r8
    mov r5, sb
    mov r6, sl
    mov r7, fp
    push {r4, r5, r6, r7, lr}
    add r4, pc, #0x0
    bx r4

    arm_func_start soundcode_b
soundcode_b: @ 0x08004320
    ldr r4, lbl_080043b0 @ =gMusicInfo
    ldrb ip, [r4, #0x4]
    mov lr, #0x600
    b lbl_08004338
lbl_08004330:
    subs r3, r3, #0x1
    beq lbl_080043a0
lbl_08004338:
    ldsb r6, [r0, lr]
    ldsb r7, [r1, lr]
    ldsb r4, [r0], #0x1
    ldsb r5, [r1], #0x1
    ldsb r10, [r0, lr]
    ldsb r11, [r1, lr]
    ldsb r8, [r0], #0x1
    ldsb r9, [r1], #0x1
    add r6, r6, r4
    add r6, r6, r5
    add r6, r6, r7
    add r8, r8, r9
    add r8, r8, r10
    add r8, r8, r11
    mul r6, ip, r6
    mul r8, ip, r8
    asrs r6, r6, #0x9
    addmi r6, r6, #0x1
    asrs r8, r8, #0x9
    addmi r8, r8, #0x1
    lsl r6, r6, #0x7
    lsl r8, r8, #0x7
    mov r7, r6
    mov r9, r8
    stmia r2!, {r6, r7, r8, r9}
    b lbl_08004330
lbl_080043a0:
    mov r0, r2
    ldmia sp!, {r8, r9, r10, r11, lr}
    ldmia sp!, {r4, r5, r6, r7}
    bx lr
lbl_080043b0:
    .4byte gMusicInfo

    thumb_func_start call_soundcode_c
call_soundcode_c: @ 0x080043b4
    push {r4, r5, r6, r7}
    mov r4, r8
    mov r5, sb
    mov r6, sl
    mov r7, fp
    push {r4, r5, r6, r7, lr}
    add r4, pc, #0x0
    bx r4

    arm_func_start soundcode_c
soundcode_c: @ 0x080043c4
    mov r3, #0x600
    add r3, r0, r3
    mov ip, #0x0
    sub ip, ip, #0x1
    lsr ip, ip, #0x17
    ldr lr, lbl_08004460 @ =sArray_808cce2
    b lbl_080043e8
lbl_080043e0:
    subs r2, r2, #0x1
    beq lbl_08004450
lbl_080043e8:
    ldmia r1!, {r4, r5, r6, r7, r8, r9, r10, r11}
    and r4, ip, r4, lsr #0x7
    and r5, ip, r5, lsr #0x7
    and r6, ip, r6, lsr #0x7
    and r7, ip, r7, lsr #0x7
    and r8, ip, r8, lsr #0x7
    and r9, ip, r9, lsr #0x7
    and r10, ip, r10, lsr #0x7
    and r11, ip, r11, lsr #0x7
    ldrb r4, [lr, r4]
    ldrb r5, [lr, r5]
    ldrb r6, [lr, r6]
    ldrb r7, [lr, r7]
    ldrb r8, [lr, r8]
    ldrb r9, [lr, r9]
    ldrb r10, [lr, r10]
    ldrb r11, [lr, r11]
    orr r4, r4, r6, lsl #0x8
    orr r4, r4, r8, lsl #0x10
    orr r4, r4, r10, lsl #0x18
    str r4, [r0], #0x4
    orr r5, r5, r7, lsl #0x8
    orr r5, r5, r9, lsl #0x10
    orr r5, r5, r11, lsl #0x18
    str r5, [r3], #0x4
    b lbl_080043e0
lbl_08004450:
    mov r0, r1
    ldmia sp!, {r8, r9, r10, r11, lr}
    ldmia sp!, {r4, r5, r6, r7}
    bx lr
lbl_08004460:
    .4byte sArray_808cce2

    thumb_func_start call_soundcode_a
call_soundcode_a: @ 0x08004464
    push {r4, r5, r6, r7}
    mov r3, r8
    mov r4, sb
    mov r5, sl
    mov r6, fp
    push {r3, r4, r5, r6, lr}
    add r4, pc, #0x0
    bx r4

    arm_func_start soundcode_a
soundcode_a: @ 0x08004474
    ldr ip, [r0, #0x18]
    ldrb r11, [r0, #0x11]
    ldrb r10, [r0, #0x12]
    ldr r9, [r0, #0x24]
    ldr r3, [r0, #0x20]
    ldr r8, [r3, #0xC]
    ldrb r4, [r0, #0x1]
    cmp r4, #0x20
    beq lbl_080048c0
    cmp r4, #0x8
    beq lbl_08004794
    mov r7, #0x0
    sub r7, r7, #0x1
    lsr r7, r7, #0x12
    ldr r6, [r0, #0x1C]
    stmdb sp!, {r0}
    ldrh r0, [r3, #0x2]
    ldr lr, [r3, #0x8]
    sub lr, lr, r8
    b lbl_080044cc
lbl_080044c4:
    subs r2, r2, #0x1
    beq lbl_08004aa8
lbl_080044cc:
    add r4, ip, r6, lsl #0x2
    subs r4, r8, r4, lsr #0xE
    bgt lbl_080046d0
    mov r5, ip, lsr #0xE
    ands r0, r0, r0
    bne lbl_080045b8
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, r8
    bge lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, r12, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, r8
    bge lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, r12, lsr #0xE
    cmp r5, r8
    bge lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    b lbl_08004a98
lbl_080045b8:
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, r8
    blt lbl_08004600
    and r3, ip, r7
    add r5, r5, lr
    add ip, r3, r5, lsl #0xE
    b lbl_08004700
lbl_08004600:
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, r8
    blt lbl_08004648
    and r3, ip, r7
    add r5, r5, lr
    add ip, r3, r5, lsl #0xE
    b lbl_08004730
lbl_08004648:
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, r8
    blt lbl_08004690
    and r3, ip, r7
    add r5, r5, lr
    add ip, r3, r5, lsl #0xE
    b lbl_08004760
lbl_08004690:
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    and r3, ip, r7
    add r5, r5, lr
    add ip, r3, r5, lsl #0xE
    b lbl_080044c4
lbl_080046d0:
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
lbl_08004700:
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
lbl_08004730:
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
lbl_08004760:
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    b lbl_080044c4
lbl_08004794:
    stmdb sp!, {r0}
    ldrh r7, [r3, #0x2]
    ldr r6, [r3, #0x8]
    b lbl_080047ac
lbl_080047a4:
    subs r2, r2, #0x1
    beq lbl_08004aa8
lbl_080047ac:
    add r4, ip, #0x4
    cmp r4, r8
    blt lbl_0800486c
    ldsb r3, [r9, ip]
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, #0x1
    cmp ip, r8
    bne lbl_080047e4
    ands r7, r7, r7
    beq lbl_08004a98
    mov ip, r6
lbl_080047e4:
    ldsb r3, [r9, ip]
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, #0x1
    cmp ip, r8
    bne lbl_08004810
    ands r7, r7, r7
    beq lbl_08004a98
    mov ip, r6
lbl_08004810:
    ldsb r3, [r9, ip]
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, #0x1
    cmp ip, r8
    bne lbl_0800483c
    ands r7, r7, r7
    beq lbl_08004a98
    mov ip, r6
lbl_0800483c:
    ldsb r3, [r9, ip]
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, #0x1
    cmp ip, r8
    bne lbl_080047a4
    ands r7, r7, r7
    beq lbl_08004a98
    mov ip, r6
    b lbl_080047a4
lbl_0800486c:
    ldmia r1, {r3, r4, r5, lr}
    ldsb r0, [r9, ip]
    mla r3, r0, r11, r3
    mla r4, r0, r10, r4
    add ip, ip, #0x1
    ldsb r0, [r9, ip]
    mla r5, r0, r11, r5
    mla lr, r0, r10, lr
    add ip, ip, #0x1
    stmia r1!, {r3, r4, r5, lr}
    ldmia r1, {r3, r4, r5, lr}
    ldsb r0, [r9, ip]
    mla r3, r0, r11, r3
    mla r4, r0, r10, r4
    add ip, ip, #0x1
    ldsb r0, [r9, ip]
    mla r5, r0, r11, r5
    mla lr, r0, r10, lr
    add ip, ip, #0x1
    stmia r1!, {r3, r4, r5, lr}
    b lbl_080047a4
lbl_080048c0:
    mov r7, #0x0
    sub r7, r7, #0x1
    mov r4, r7
    mov r7, r7, lsr #0x12
    ldr r6, [r0, #0x1C]
    eor r6, r6, r4
    add r6, r6, #0x1
    stmdb sp!, {r0}
    ldrh r0, [r3, #0x2]
    b lbl_080048f0
lbl_080048e8:
    subs r2, r2, #0x1
    beq lbl_08004aa8
lbl_080048f0:
    add r4, ip, r6, lsl #0x2
    movs r4, r4, asr #0xE
    bgt lbl_080049d4
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, #0x0
    ble lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, #0x0
    ble lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    cmp r5, #0x0
    ble lbl_08004a98
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    b lbl_08004a98
lbl_080049d4:
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    mov r5, ip, lsr #0xE
    ldsb r3, [r5, r9]!
    ldsb r4, [r5, #0x1]
    sub r4, r4, r3
    and r5, ip, r7
    mul r4, r5, r4
    add r3, r3, r4, lsr #0xE
    ldmia r1, {r4, r5}
    mla r4, r3, r11, r4
    mla r5, r3, r10, r5
    stmia r1!, {r4, r5}
    add ip, ip, r6
    b lbl_080048e8
lbl_08004a98:
    ldmia sp!, {r0}
    mov r4, #0x0
    strb r4, [r0, #0x0]
    b lbl_08004ab0
lbl_08004aa8:
    ldmia sp!, {r0}
    str ip, [r0, #0x18]
lbl_08004ab0:
    ldmia sp!, {r8, r9, r10, r11, lr}
    ldmia sp!, {r4, r5, r6, r7}
    bx lr

    thumb_func_start CallGetNoteFrequency
CallGetNoteFrequency: @ 0x08004abc
    add r2, pc, #0x0 @ =GetNoteFrequency
    bx r2

    arm_func_start GetNoteFrequency
GetNoteFrequency: @ 0x08004ac0
    umull r2, r3, r0, r1
    lsr r2, r2, #0x12
    lsl r3, r3, #0xe
    add r3, r3, r2
    add r0, r3, #0
    bx lr

    thumb_func_start sub_08004ad8
sub_08004ad8: @ 0x08004ad8
    add r0, pc, #0x0 @ =sub_08004adc
    bx r0

    arm_func_start sub_08004adc
sub_08004adc: @ 0x08004adc
    ldr r0, lbl_08004b44 @ =gMusicInfo
    ldrb r1, [r0, #0x10]
    add r1, r1, #1
    ldrb r3, [r0, #0xe]
    cmp r1, r3
    bne lbl_08004b3c
    ldr r3, lbl_08004b48 @ =sDma1ControlPointer
    ldr r3, [r3]
    ldr ip, lbl_08004b4c @ =sDma1ControlValue
    ldr ip, [ip]
    str ip, [r3]
    str ip, [r3, #0xC]
    mov r0, r0
    mov ip, #0x50
    lsl ip, ip, #0x4
    strh ip, [r3, #0x2]
    strh ip, [r3, #0xE]
    mov ip, #0xB6
    lsl ip, ip, #0x8
    strh ip, [r3, #0x2]
    mov ip, #0xF6
    lsl ip, ip, #0x8
    strh ip, [r3, #0xE]
    mov r1, #0x0
lbl_08004b3c:
    strb r1, [r0, #0x10]
    bx lr
    .align 2, 0
lbl_08004b44: .4byte gMusicInfo
lbl_08004b48: .4byte sDma1ControlPointer
lbl_08004b4c: .4byte sDma1ControlValue
