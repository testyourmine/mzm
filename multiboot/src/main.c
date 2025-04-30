#include "funcs.h"
#include "gba.h"
#include "io.h"
#include "macros.h"
#include "syscalls.h"
#include "types.h"
#include "variables.h"
#include "structs/structs.h"
#include "data/data.h"
#include "constants/constants.h"

void AgbMain(void)
{
    InitializeGame();

    while (TRUE)
    {
        UpdateInput();
        gFrameCounter8Bit++;
        switch (gMainGameMode)
        {
            case 0:
                LinkResetSerial();
                gUnk_290 = 0;
                gUnk_6ac = 0;
                gUnk_6bc = 0;
                gMainGameMode++;
                break;

            case 1:
                gUnk_6ac++;
                LinkHandleConnection();
                if (gUnk_88 & 1)
                {
                    gUnk_290++;
                    if (gUnk_290 > 3)
                    {
                        gUnk_70 = 0;
                        gUnk_7c = 0;
                        gUnk_6c0 = 0;
                        gMainGameMode++;
                    }
                }
                else if (gUnk_6bc != 0)
                {
                    gUnk_70 = 0;
                    gUnk_7c = 0;
                    gUnk_6c0 = 0;
                    gMainGameMode++;
                }
                if (gUnk_6ac > 90)
                {
                    gUnk_88 |= 1;
                    gUnk_6bc = 0x20;
                    gUnk_6ac = 0;
                }
                break;

            case 2:
                LinkDisableSerial();
                if (LoadGraphics() != 0)
                {
                    gUnk_24 |= (*(struct Unk_7e44*)0x02007e44).v4;
                    gMainGameMode++;
                }
                else
                {
                    gMainGameMode += 2;
                }
                break;

            case 3:
                if (gUnk_8c != 0)
                {
                    if (gUnk_8c >= 3)
                        gUnk_8c -= 2;
                    else
                        gUnk_8c = 0;

                    gUnk_78 = 0x10 - gUnk_8c;
                    if (gUnk_8c == 0)
                        gMainGameMode++;
                }
                break;

            case 4:
        }

        VBlankIntrWait();
    }
}

u32 LoadGraphics(void)
{
    u8 loadedGraphics;
    u8 graphicsOffset;

    graphicsOffset = 0x80;
    if ((u8)gUnk_6c <= 7)
    {
        graphicsOffset = (u8)gUnk_6c;
    }
    else if (gUnk_6a8 == 1)
    {
        graphicsOffset = 0;
    }
    else if(gUnk_6a8 == 2 || (graphicsOffset = 0x80, gUnk_6a8 == 3))
    {
        graphicsOffset = 2;
    }
    
    if (graphicsOffset != 0x80)
    {
        if (gUnk_6bc != 0)
        {
            LZ77UncompVRAM(PTR_ARRAY_02007fc8[graphicsOffset], (UNK_7E44.v8 << 14) + VRAM_BASE + 0x5000);
            DMA_SET(3, VRAM_BASE + 0x1000, PALRAM_BASE, C_32_2_16(DMA_ENABLE, 0xF0));
        }
        else
        {
            LZ77UncompVRAM(PTR_ARRAY_02007fac[graphicsOffset], (UNK_7E44.v8 << 14) + VRAM_BASE + 0x5000);
            DMA_SET(3, ARRAY_02001854, PALRAM_BASE, C_32_2_16(DMA_ENABLE, 0x100));
        }
        loadedGraphics = TRUE;
    }
    else
    {
        loadedGraphics = FALSE;
    }
    return loadedGraphics;
}

void InitializeGame(void)
{
    u8 tmp;
    u8 tmp2;
    u8 tmp3;
    u16 tmp4;
    
    dma_fill32(3, 0, IWRAM_BASE, IWRAM_SIZE - 0x15D);
    write16(REG_WAITCNT, WAIT_GAMEPACK_CGB | WAIT_BANK0_SUBSEQUENT_1CYCLE | WAIT_BANK0_3CYCLES);
    DMA_SET(3, InterruptTable, 0x3000030, 0x8400000e);
    DMA_SET(3, 0x2000104, 0x3000090, 0x84000080);
    gIntrCodePointer = (void*)0x3000090;
    dma_fill16(3, 0, VRAM_BASE, VRAM_SIZE);
    DMA_SET(3, ARRAY_02001854, PALRAM_OBJ, 0x80000100);
    ApplyMonochromeToPalette((u16*)ARRAY_02001854, PALRAM_BASE, 0);
    ApplyMonochromeToPalette((u16*)ARRAY_02001854, VRAM_BASE + 0x1000, -8);
    LZ77UncompVRAM(ARRAY_02001a54, ((tmp2 = UNK_7E44.v8) << 14) + VRAM_BASE);
    LZ77UncompVRAM(ARRAY_02005550, ((tmp = UNK_7E44.v9) << 11) + VRAM_BASE);
    LZ77UncompVRAM(ARRAY_02005b10, ((tmp3 = UNK_7E44.v1) << 11) + VRAM_BASE);
    dma_fill32(3, 0xA0, 0x30002a0, 0x400);
    dma_fill32(3, 0xA0, 0x7000000, 0x400);
    ValidateGameVersion();
    write16(REG_BG0CNT, UNK_7E44.v18 | UNK_7E44.v22 | (UNK_7E44.v17 << 8) | (UNK_7E44.v16 << 2));
    write16(REG_BG2CNT, UNK_7E44.v2 | UNK_7E44.v6 | (tmp3 << 8) | (UNK_7E44.v0 << 2));
    write16(REG_BG3CNT, UNK_7E44.v10 | UNK_7E44.v14 | (tmp << 8) | (tmp2 << 2));
    gSendCmd2 = 0x5500;
    gMainGameMode = 0;
    gUnk_88 = 0;
    gUnk_6c = 0xfe;
    gUnk_70 = 1;
    write16(REG_IE, 0x2001);
    write16(REG_DISPSTAT, 8);
    write16(REG_IF, 0xffff);
    write16(REG_IME, 1);
    gUnk_8c = tmp4 = 0x10;
    gUnk_78 = 0;
    gUnk_80 = 0x10;
    write16(REG_BLDY, tmp4);
    write16(REG_BLDALPHA, tmp4 << 8);
    write16(REG_BLDCNT, 0x2844);
    gUnk_24 = UNK_7E44.v12;
}

void LinkHandleConnection(void)
{
    vu32 c;
    u32* link_stat;
    
    gShouldAdvanceLinkState = gFrameCounter8Bit & 1;
    link_stat = &gErrorFlag;
    *link_stat = LinkMain(&gShouldAdvanceLinkState,&gSendCmd0,gRecvCmds);
    gLinkLocalId = *link_stat & 3;
    gLinkPlayerCount = ((*link_stat & 0x1c) >> 2);
    gLinkUnkFlag9 = ((*link_stat & 0xe00) >> 9);
    if ((*link_stat & 0x40)) {
        gUnk_6ac = 0;
        LinkBuildSendCmd(gSendCmd2);
        LinkProcessRecvCmds();
    }
    if ((*link_stat & 0x400000)) {
        gUnk_6bc = 1;
    }
    if ((*link_stat & 0x20000)) {
        gUnk_6bc = 2;
    }
    if ((*link_stat & 0x10000)) {
        gUnk_6bc = 3;
    }
    if ((*link_stat & 0x40000)) {
        gUnk_6bc = 4;
    }
    if ((*link_stat & 0x80000)) {
        gUnk_6bc = 5;
    }
    if ((*link_stat & 0x100000)) {
        gUnk_6bc = 6;
    }
    if ((*link_stat & 0x200000)) {
        gUnk_6bc = 7;
    }
}

void UpdateDisplay(void)
{
    LinkVSync();
    write16(REG_DISPCNT, gUnk_24);
    write16(REG_BLDALPHA, C_16_2_8(gUnk_8c, gUnk_78));
    gInterruptCheckFlag |= 1;
}

void unk_020007fc(void)
{
    u8 i;

    for (i = 0; i < 4; i++)
    {
        if (i < gLinkPlayerCount) {
            gUnk_2a0[i].field0 = i * 16 + 0x30;
            gUnk_2a0[i].field1_0 = 0xDC;
        }
        else {
            gUnk_2a0[i].field0 = 0xA0;
        }
    }
}

void UpdateInput(void)
{
    u16 keys;

    keys = read16(REG_KEY_INPUT) ^ KEY_MASK;
    gChangedInput = keys & ~gPreviousButtonInput;
    gPreviousButtonInput = keys;
}

void FillPalette(const u8 *src, u16 *dst, u8 palette)
{
    while (*src != 0)
    {
        *dst = (u16)*src | (palette << 0xc);
        src++;
        dst++;
    }
}

void empty_89c(void)
{
    return;
}

void LinkBuildSendCmd(u16 command)
{
    switch (command)
    {
        case 0x8800:
            gSendCmd[0] |= command;
            gSendCmd[1] = gPreviousButtonInput;
            gSendCmd[2] = gChangedInput;
            return;
        case 0x6600:
            gSendCmd[0] |= command;
            gSendCmd[1] = gUnk_20;
            break;
        case 0x5500:
            gSendCmd[0] |= command;
            gSendCmd[1] = gUnk_6c;
            break;
        case 0x3300:
            gSendCmd[0] |= command;
            gSendCmd[1] = gUnk_88;
            break;
    }
    return;
}

void LinkProcessRecvCmds(void)
{
    u8 tmp;
    if ((gErrorFlag & 0x100)) {
        return;
    }

    if (gRecvCmds[0][0] == 0x5500) {
        gUnk_6c = gRecvCmds[1][0];
        gUnk_88 = 0;
    }
    if (gRecvCmds[0][0] == 0x4400) {
        gSendCmd2 = 0x6600;
        gUnk_88 = 0;
    }
    if (gRecvCmds[0][0] == 0x2200) {
        gSendCmd2 = 0x3300;
    }
    if (gRecvCmds[0][1] == 0x3300) {
        gSendCmd2 = 0;
        tmp = gUnk_20 - 1;
        if (tmp < 3)
        {
            gUnk_88 = 1;
        }
    }
    return;
}

void ApplyMonochromeToPalette(const u16* src, u16* dst, s8 additionalValue)
{
    s32 i;
    s32 result;
    u16 r;
    u16 g;
    u16 b;

    for (i = 0; i < COLORS_IN_PAL; i++, src++, dst++)
    {
        r = RED(*src);
        g = GREEN(*src);
        b = BLUE(*src);

        // Get average
        result = (r + g + b) / 3 + additionalValue;
        CLAMP2(result, 0, COLOR_MASK);
        
        // Create grey color
        *dst = COLOR(result, result, result);
    }
}

void LinkDisableSerial(void)
{
    u32 buffer;

    // Disable Interrupts
    gLinkSavedIme = read16(REG_IME);
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) & ~(IF_TIMER3 | IF_SERIAL));
    write16(REG_IME, gLinkSavedIme);

    write16(REG_SIO, SIO_MULTI_MODE);
    write16(REG_TM3CNT_H, 0);
    write16(REG_IF, IF_TIMER3 | IF_SERIAL);

    buffer = 0;
    CpuSet(&buffer, &gLink, C_32_2_16(CPU_SET_32BIT | CPU_SET_SRC_FIXED, sizeof(gLink) / sizeof(u32)));
}

void LinkEnableSerial(void)
{
    u32 buffer;
    u32* ptr;

    // Disable Interrupts
    gLinkSavedIme = read16(REG_IME);
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) & ~(IF_TIMER3 | IF_SERIAL));
    write16(REG_IME, gLinkSavedIme);

    write16(REG_RNCT, 0);
    write16(REG_SIO, SIO_MULTI_MODE);
    write16(REG_SIO, read16(REG_SIO) | SIO_BAUD_RATE_115200 | SIO_IRQ_ENABLE);

    // Enable Interrupts
    gLinkSavedIme = read16(REG_IME);
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) | IF_SERIAL);
    write16(REG_IME, gLinkSavedIme);

    write16(REG_SIO_DATA8, 0);
    write64(REG_SIO_MULTI, 0);

    buffer = 0;
    CpuSet(&buffer, &gLink, C_32_2_16(CPU_SET_32BIT | CPU_SET_SRC_FIXED, sizeof(gLink) / sizeof(u32)));

    gNumVBlanksWithoutSerialIntr = 0;
    gSendBufferEmpty = 0;
    gHandshakePlayerCount = 0;
    gLastSendQueueCount = 0;
    gLastRecvQueueCount = 0;
    gChecksumAvailable = 0;
    gSendNonzeroCheck = 0;
    gRecvNonzeroCheck = 0;
}

void LinkResetSerial(void)
{
    LinkEnableSerial();
    LinkDisableSerial();
}

u32 LinkMain(u8* shouldAdvanceLinkState, u16 sendCmd[CMD_LENGTH], u16 recvCmds[MAX_LINK_PLAYERS][CMD_LENGTH])
{
    u32 retval;
    u32 receivedNothing;
    u32 errorFlag_1;
    u32 hardwareError;
    u32 badChecksum;
    u32 queueFull;
    u32 errorFlag_sioInternal;
    u32 val;

    switch (gLink.session.state)
    {
        case LINK_STATE_START0:
            LinkDisableSerial();
            gLink.session.state = LINK_STATE_START1;
            break;

        case LINK_STATE_START1:
            if (*shouldAdvanceLinkState == 1)
            {
                LinkEnableSerial();
                gLink.session.state = LINK_STATE_HANDSHAKE;
            }
            break;

        case LINK_STATE_HANDSHAKE:
            switch (*shouldAdvanceLinkState)
            {
                case 1:
                    if (gLink.session.isParent != 0 && gLink.session.playerCount > 1)
                        gLink.connection.handshakeAsParent = 1;
                    break;

                case 2:
                    gLink.session.state = LINK_STATE_START0;
                    write16(REG_SIO_DATA8, 0);
                    break;

                default:
                    LinkCheckParentOrChild();
                    break;
            }
            break;

        case LINK_STATE_INIT_TIMER:
            LinkInitTimer();
            gLink.session.state = LINK_STATE_CONN_ESTABLISHED;

        case LINK_STATE_CONN_ESTABLISHED:
            LinkEnqueueSendCmd(sendCmd);
            LinkDequeueRecvCmds(recvCmds);
            break;
    }

    *shouldAdvanceLinkState = 0;

    retval = gLink.session.localId | (gLink.session.playerCount << LINK_STAT_SHIFT_PLAYER_COUNT);
    if (gLink.session.isParent == LINK_PARENT)
    {
        retval |= LINK_STAT_PARENT;
    }

    receivedNothing = gLink.session.receivedNothing << LINK_STAT_SHIFT_RECEIVED_NOTHING;
    errorFlag_1 = gLink.connection.unk_11 << LINK_STAT_SHIFT_ERRORS;
    hardwareError = gLink.connection.hardwareErrorFlag << LINK_ERROR_SHIFT_HARDWARE;
    badChecksum = gLink.connection.checksumErrorFlag << LINK_ERROR_SHIFT_CHECKSUM;
    queueFull = gLink.connection.overflowErrorFlags << LINK_ERROR_SHIFT_OVERFLOW;
    errorFlag_sioInternal = gLink.connection.sioErrorFlags << LINK_ERROR_SHIFT_SIO;

    if (gLink.session.state == LINK_STATE_CONN_ESTABLISHED)
    {
        val = LINK_STAT_CONN_ESTABLISHED;
        val |= receivedNothing;
        val |= retval;
        val |= errorFlag_1;
        val |= hardwareError;
        val |= badChecksum;
        val |= queueFull;
        val |= errorFlag_sioInternal;
    }
    else
    {
        val = retval;
        val |= receivedNothing;
        val |= errorFlag_1;
        val |= hardwareError;
        val |= badChecksum;
        val |= queueFull;
        val |= errorFlag_sioInternal;
    }
    retval = val;

    if (gLink.session.localId >= MAX_LINK_PLAYERS)
        retval |= LINK_ERROR_ID_OVER;

    return retval;
}

void LinkCheckParentOrChild(void)
{
    u32 terminals;

    terminals = read32(REG_SIO) & (SIO_MULTI_CONNECTION_READY | SIO_MULTI_RECEIVE_ID);
    if (terminals == (SIO_MULTI_CONNECTION_READY | SIO_MULTI_PARENT) && gLink.session.localId == 0)
    {
        gLink.session.isParent = LINK_PARENT;
    }
    else
    {
        gLink.session.isParent = LINK_CHILD;
    }
}

void LinkInitTimer(void)
{
    if (gLink.session.isParent)
    {
        // Load -132 into timer 3 with 1/64 the normal frequency
        write16(REG_TM3CNT_L, -132);
        write16(REG_TM3CNT_H, TIMER_CONTROL_IRQ_ENABLE | 1);

        // Enable timer 3 interrupt, enable interrupts if already enabled
        gLinkSavedIme = read16(REG_IME);
        write16(REG_IME, FALSE);
        write16(REG_IE, read16(REG_IE) | IF_TIMER3);
        write16(REG_IME, gLinkSavedIme);
    }
}

void LinkEnqueueSendCmd(u16 sendCmd[CMD_LENGTH])
{
    u8 offset;
    u8 i;

    gLinkSavedIme = read16(REG_IME);
    write16(REG_IME, FALSE);

    if (gLink.sendQueue.count < QUEUE_CAPACITY)
    {
        offset = gLink.sendQueue.pos + gLink.sendQueue.count;
        if (offset >= QUEUE_CAPACITY)
        {
            offset -= QUEUE_CAPACITY;
        }

        for (i = 0; i < CMD_LENGTH; i++)
        {
            gSendNonzeroCheck |= *sendCmd;
            gLink.sendQueue.data[i][offset] = *sendCmd;
            *sendCmd++ = 0;
        }
    }
    else
    {
        gLink.connection.overflowErrorFlags |= QUEUE_FULL_SEND;
    }

    if (gSendNonzeroCheck)
    {
        gLink.sendQueue.count++;
        gSendNonzeroCheck = 0;
    }

    write16(REG_IME, gLinkSavedIme);
    gLastSendQueueCount = gLink.sendQueue.count;
}

void LinkDequeueRecvCmds(u16 recvCmds[MAX_LINK_PLAYERS][CMD_LENGTH])
{
    u8 i;
    u8 j;

    gLinkSavedIme = read16(REG_IME);
    write16(REG_IME, FALSE);

    if (gLink.recvQueue.count == 0)
    {
        for (i = 0; i < CMD_LENGTH; i++)
        {
            for (j = 0; j < gLink.session.playerCount; j++)
            {
                recvCmds[i][j] = 0;
            }
        }

        gLink.session.receivedNothing = TRUE;
    }
    else
    {
        for (i = 0; i < CMD_LENGTH; i++)
        {
            for (j = 0; j < gLink.session.playerCount; j++)
            {
                recvCmds[i][j] = gLink.recvQueue.data[j][i][gLink.recvQueue.pos];
            }
        }

        gLink.recvQueue.count--;
        gLink.recvQueue.pos++;

        if (gLink.recvQueue.pos >= QUEUE_CAPACITY)
        {
            gLink.recvQueue.pos = 0;
        }

        gLink.session.receivedNothing = FALSE;
    }

    write16(REG_IME, gLinkSavedIme);
}

void LinkVSync(void)
{
    if (gLink.session.isParent)
    {
        switch (gLink.session.state)
        {
            case LINK_STATE_CONN_ESTABLISHED:
                if (gLink.session.serialIntrCounter <= CMD_LENGTH)
                {
                    if (gLink.connection.hardwareErrorFlag == 0)
                    {
                        gLink.connection.sioErrorFlags = 1;
                    }
                    else
                    {
                        LinkStartTransfer();
                    }
                }

                else if (gLink.connection.sioErrorFlags == 0)
                {
                    gLink.session.serialIntrCounter = 0;
                    LinkStartTransfer();
                }
                break;
            
            case LINK_STATE_HANDSHAKE:
                LinkStartTransfer();
                break;
        }
    }
    
    else if (gLink.session.state == LINK_STATE_CONN_ESTABLISHED || gLink.session.state == LINK_STATE_HANDSHAKE)
    {
        gNumVBlanksWithoutSerialIntr++;
        if (gNumVBlanksWithoutSerialIntr > 10)
        {
            if (gLink.session.state == LINK_STATE_CONN_ESTABLISHED)
            {
                gLink.connection.sioErrorFlags = LAG_CHILD;
            }
            
            if (gLink.session.state == LINK_STATE_HANDSHAKE)
            {
                gLink.session.localId = 0;
                gLink.session.playerCount = 0;
                gLink.connection.unk_11 = 0;
            }
        }
    }
}

void LinkReloadTransfer(void)
{
    // Called when timer 3 interrupts
    LinkStopTimer();
    LinkStartTransfer();
}

void LinkCommunicate(void)
{
    u32 control;

    control = read32(REG_SIO);
    gLink.session.localId = (control << 26) >> 30; // SIO_MULTI_CONNECTION_ID_FLAG

    switch (gLink.session.state)
    {
        case LINK_STATE_CONN_ESTABLISHED:
            if (control & SIO_MULTI_ERROR)
                gLink.connection.hardwareErrorFlag = TRUE;

            LinkDoRecv();
            LinkDoSend();
            LinkSendRecvDone();
            break;

        case LINK_STATE_HANDSHAKE:
            if (LinkDoHandshake())
            {
                if (gLink.session.isParent)
                {
                    gLink.session.state = LINK_STATE_INIT_TIMER;
                    gLink.session.serialIntrCounter = CMD_LENGTH;
                }
                else
                {
                    gLink.session.state = LINK_STATE_CONN_ESTABLISHED;
                }
            }
            break;
    }

    gLink.session.serialIntrCounter++;
    gNumVBlanksWithoutSerialIntr = 0;
    if (gLink.session.serialIntrCounter == CMD_LENGTH)
    {
        gLastRecvQueueCount = gLink.recvQueue.count;
    }
}

void LinkStartTransfer(void)
{
    write16(REG_SIO, read16(REG_SIO) | SIO_START_BIT_ACTIVE);
}

u8 LinkDoHandshake(void)
{
    u16 minRecv;
    u8 i;
    u8 playerCount;

    playerCount = 0;
    minRecv = USHORT_MAX;

    if (gLink.connection.handshakeAsParent == TRUE)
    {
        write16(REG_SIO_DATA8, PARENT_HANDSHAKE);
    }
    else
    {
        write16(REG_SIO_DATA8, CHILD_HANDSHAKE);
    }
    gLink.connection.handshakeAsParent = FALSE;

    write64(gLink.session.handshakeBuffer, read64(REG_SIO_MULTI));

    for (i = 0; i < MAX_LINK_PLAYERS; i++)
    {    
        if ((gLink.session.handshakeBuffer[i] & ~3) == CHILD_HANDSHAKE || gLink.session.handshakeBuffer[i] == PARENT_HANDSHAKE)
        {
            playerCount++;
            if (minRecv > gLink.session.handshakeBuffer[i] && gLink.session.handshakeBuffer[i] != 0)
            {
                minRecv = gLink.session.handshakeBuffer[i];
            }
        }
        else if (gLink.session.handshakeBuffer[i] != USHORT_MAX)
        {
            playerCount = 0;
            break;
        }
        else if (i == gLink.session.localId)
        {
            playerCount = 0;
        }
    }

    gLink.session.playerCount = playerCount;

    if (gLink.session.playerCount > 1)
    {
        if (gLink.session.playerCount == gHandshakePlayerCount && gLink.session.handshakeBuffer[0] == PARENT_HANDSHAKE)
        {
            return TRUE;
        }
    
        if (gLink.session.playerCount > 1)
        {
            gLink.connection.unk_11 = (minRecv & 3) + 1;
        }
        else
        {
            gLink.connection.unk_11 = 0;
        }
    }
    else
    {
        gLink.connection.unk_11 = 0;
    }

    gHandshakePlayerCount = gLink.session.playerCount;

    return FALSE;
}

void LinkDoRecv(void)
{
    u16 recv[4];
    u8 i;
    u8 offset;

    write64(recv, read64(REG_SIO_MULTI));

    if (gLink.connection.sendCmdIndex == 0)
    {
        for (i = 0; i < gLink.session.playerCount; i++)
        {
            if (gLink.connection.checksum != recv[i] && gChecksumAvailable)
            {
                gLink.connection.checksumErrorFlag = TRUE;
            }
        }

        gLink.connection.checksum = 0;
        gChecksumAvailable = TRUE;
    }
    else
    {
        offset = gLink.recvQueue.pos + gLink.recvQueue.count;
        if (offset >= QUEUE_CAPACITY)
            offset -= QUEUE_CAPACITY;

        if (gLink.recvQueue.count < QUEUE_CAPACITY)
        {
            for (i = 0; i < gLink.session.playerCount; i++)
            {
                gLink.connection.checksum += recv[i];
                gRecvNonzeroCheck |= recv[i];

                gLink.recvQueue.data[i][gLink.connection.recvCmdIndex][offset] = recv[i];
            }
        }
        else
        {
            gLink.connection.overflowErrorFlags |= QUEUE_FULL_RECV;
        }

        gLink.connection.recvCmdIndex++;
        if (gLink.connection.recvCmdIndex == CMD_LENGTH && gRecvNonzeroCheck)
        {
            gLink.recvQueue.count++;
            gRecvNonzeroCheck = 0;
        }
    }
}

void LinkDoSend(void)
{
    if (gLink.connection.sendCmdIndex == CMD_LENGTH)
    {
        write16(REG_SIO_DATA8, gLink.connection.checksum);

        if (!gSendBufferEmpty)
        {
            gLink.sendQueue.count--;
            gLink.sendQueue.pos++;

            if (gLink.sendQueue.pos >= QUEUE_CAPACITY)
            {
                gLink.sendQueue.pos = 0;
            }
        }
        else
        {
            gSendBufferEmpty = FALSE;
        }
    }
    else
    {
        if (gLink.connection.sendCmdIndex == 0 && gLink.sendQueue.count == 0)
        {
            gSendBufferEmpty = TRUE;
        }
            
        if (gSendBufferEmpty)
        {
            write16(REG_SIO_DATA8, 0);
        }
        else
        {
            write16(REG_SIO_DATA8, gLink.sendQueue.data[gLink.connection.sendCmdIndex][gLink.sendQueue.pos]);
        }

        gLink.connection.sendCmdIndex++;
    }
}

void LinkStopTimer(void)
{
    if (gLink.session.isParent)
    {
        // Turn off timer 3 and load in -132
        write16(REG_TM3CNT_H, read16(REG_TM3CNT_H) & ~TIMER_CONTROL_ACTIVE);
        write16(REG_TM3CNT_L, -132);
    }
}

void LinkSendRecvDone(void)
{
    if (gLink.connection.recvCmdIndex == CMD_LENGTH)
    {
        gLink.connection.sendCmdIndex = 0;
        gLink.connection.recvCmdIndex = 0;
    }
    else if (gLink.session.isParent)
    {
        write16(REG_TM3CNT_H, read16(REG_TM3CNT_H) | TIMER_CONTROL_ACTIVE);
    }
}

void LinkResetSendBuffer(void)
{
    u8 i;
    u8 j;

    gLink.sendQueue.count = 0;
    gLink.sendQueue.pos = 0;

    for (i = 0; i < CMD_LENGTH; i++)
    {
        for (j = 0; j < QUEUE_CAPACITY; j++)
        {
            gLink.sendQueue.data[i][j] = LINKCMD_NONE;
        }
    }
}

void LinkResetRecvBuffer(void)
{
    u8 i;
    u8 j;
    u8 k;

    gLink.recvQueue.count = 0;
    gLink.recvQueue.pos = 0;

    for (i = 0; i < MAX_LINK_PLAYERS; i++)
    {
        for (j = 0; j < CMD_LENGTH; j++)
        {
            for (k = 0; k < QUEUE_CAPACITY; k++)
            {
                gLink.recvQueue.data[i][j][k] = LINKCMD_NONE;
            }
        }
    }
}
