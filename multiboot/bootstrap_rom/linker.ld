SECTIONS {
    . = 0x03000000;
    .text : ALIGN(2) {
        asm/romheader.o(.text);
        asm/crt0.o(.text);
        asm/intr_main.o(.text);
        src/main.o(.text);
        asm/syscalls.o(.text);
        asm/libgcc.o(.text);
    } =0

    .rodata : ALIGN(2) {
        src/data/data.o(.rodata);
    } =0

    . = 0x03000000;
    iwram(NOLOAD) : ALIGN(4)
    {
        . = 0x00005000; gTransferUpdateResult_Unused = .;
        . = 0x00005002; gUnk_5002 = .;
        . = 0x00005004; gTransferDataTimer = .;
        . = 0x00005006; gTransferStartupTimer = .;
        . = 0x00005007; gTransferTimeoutTimer = .;
        . = 0x00005008; gTransferGbaDetectedCount = .;
        . = 0x00005009; gTransferGbaId = .;
        . = 0x0000500a; gRegIme_Backup = .;
        . = 0x0000500c; gRegIe_Backup = .;
        . = 0x0000500e; gRegTm3Cnt_H_Backup = .;
        . = 0x00005010; gRegSiocnt_Backup = .;
        . = 0x00005012; gRegRcnt_Backup = .;
        . = 0x00005020; gUnk_5020 = .;
        . = 0x00005024; gScreenMode = .;
        . = 0x00005030; gIntrTable = .;
        . = 0x00005068; gScreenBreatheEffectOffset = .;
        . = 0x0000506c; gTransferUpdateResult = .;
        . = 0x00005070; gPreviousButtonInput = .;
        . = 0x00005078; gUnk_5078 = .;
        . = 0x0000507c; gUnk_507c = .;
        . = 0x00005080; gChangedInput = .;
        . = 0x00005084; gBldY = .;
        . = 0x00005088; gMainGameMode = .;
        . = 0x0000508c; gUnk_508c = .;
        . = 0x00005090; gInterruptCode = .;
        . = 0x00005290; gUnk_5290 = .;
        . = 0x00005294; gDispCnt = .;
        . = 0x00005298; gScreenBreatheEffectTimer = .;
        . = 0x000052a0; gTransferManager = .;

        . = 0x00007f00; sp_sys = .;
        . = 0x00007fa0; sp_irq = .;
        . = 0x00007ff8; gInterruptCheckFlag = .;
        . = 0x00007ffc; gIntrCodePointer = .;
        . = 0x00007ffc; intr_vector = .;
    }
}
