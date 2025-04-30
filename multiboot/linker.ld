SECTIONS {
    . = 0x02000000;
    .text : ALIGN(2) {
        asm/romheader.o(.text);
        asm/crt0.o(.text);
        asm/intr_main.o(.text);
        src/main.o(.text);
        asm/disasm.o(.text);
    } =0

    .rodata : ALIGN(2) {
        src/data/data.o(.rodata)
    } =0

    . = 0x03000000;
    iwram(NOLOAD) : ALIGN(4)
    {
        . = 0x00000010; gMainGameMode = .;
        . = 0x00000024; gUnk_24 = .;
        . = 0x0000006c; gUnk_6c = .;
        . = 0x00000070; gUnk_70 = .;
        . = 0x00000078; gUnk_78 = .;
        . = 0x0000007c; gUnk_7c = .;
        . = 0x00000080; gUnk_80 = .;
        . = 0x00000088; gUnk_88 = .;
        . = 0x0000008c; gUnk_8c = .;
        . = 0x00000290; gUnk_290 = .;
        . = 0x000006a0; gFrameCounter8Bit = .;
        . = 0x000006a8; gUnk_6a8 = .;
        . = 0x000006ac; gUnk_6ac = .;
        . = 0x000006b8; gUnk_6b8 = .;
        . = 0x000006bc; gUnk_6bc = .;
        . = 0x000006c0; gUnk_6c0 = .;

        . = 0x00007f00; sp_sys = .;
        . = 0x00007fa0; sp_irq = .;
        . = 0x00007ff8; gInterruptCheckFlag = .;
        . = 0x00007ffc; gIntrCodePointer = .;
        . = 0x00007ffc; intr_vector = .;
    }

    /DISCARD/ :
    {
        *(*);
    }
}
