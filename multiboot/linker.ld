SECTIONS {
    . = 0x02000000;
    .text : ALIGN(2) {
        asm/romheader.o(.text);
        asm/crt0.o(.text);
        asm/intr_main.o(.text);
        src/main.o(.text);
        asm/syscalls.o(.text)
        asm/libgcc.o(.text)
    } =0

    .rodata : ALIGN(2) {
        src/data/data.o(.rodata)
    } =0

    . = 0x03000000;
    iwram(NOLOAD) : ALIGN(4)
    {
        . = 0x00000000; gLinkSavedIme = .;
        . = 0x00000002; gNumVBlanksWithoutSerialIntr = .;
        . = 0x00000003; gSendBufferEmpty = .;
        . = 0x00000005; gHandshakePlayerCount = .;
        . = 0x00000006; gChecksumAvailable = .;
        . = 0x00000008; gSendNonzeroCheck = .;
        . = 0x0000000a; gRecvNonzeroCheck = .;
        . = 0x00000010; gMainGameMode = .;
        . = 0x00000018; gRecvCmds = .;
        . = 0x00000020; gFusionGameCode = .;
        . = 0x00000024; gDispCnt = .;
        . = 0x00000030; gIntrTable = .;
        . = 0x00000068; gLinkLocalId = .;
        . = 0x0000006c; gLanguage = .;
        . = 0x00000070; gUnk_70 = .;
        . = 0x00000074; gChangedInput = .;
        . = 0x00000078; gBldAlpha_L = .;
        . = 0x0000007c; gUnk_7c = .;
        . = 0x00000080; gBldY = .;
        . = 0x00000084; gLinkStatus = .;
        . = 0x00000088; gLinkFinished = .;
        . = 0x0000008c; gBldAlpha_H = .;
        . = 0x00000090; gInterruptCode = .;
        . = 0x00000290; gLinkFinishedDelayTimer = .;
        . = 0x00000298; gShouldAdvanceLinkState = .;
        . = 0x0000029c; gLinkUnkFlag9 = .;
        . = 0x000002a0; gUnk_2a0 = .;
        . = 0x000006a0; gFrameCounter8Bit = .;
        . = 0x000006a4; gPreviousButtonInput = .;
        . = 0x000006a8; gZeroMissionGameCode = .;
        . = 0x000006ac; gLinkTimer = .;
        . = 0x000006b0; gLinkPlayerCount = .;
        . = 0x000006b4; gSendCmd = .;
        . = 0x000006b4; gSendCmd0 = .;
        . = 0x000006b6; gSendCmd1 = .;
        . = 0x000006b8; gCommand = .;
        . = 0x000006bc; gLinkErrorFlag = .;
        . = 0x000006c0; gUnk_6c0 = .;
        . = 0x000006d0; gLastSendQueueCount = .;
        . = 0x000006d4; gLastRecvQueueCount = .;
        . = 0x000006e0; gLink = .;

        . = 0x00007f00; sp_sys = .;
        . = 0x00007fa0; sp_irq = .;
        . = 0x00007ff8; gInterruptCheckFlag = .;
        . = 0x00007ffc; gIntrCodePointer = .;
        . = 0x00007ffc; intr_vector = .;
    }
}
