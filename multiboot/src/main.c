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

/**
 * @brief 23c | 18c | Main game loop
 * 
 */
void AgbMain(void)
{
    InitializeGame();

    while (TRUE)
    {
        UpdateInput();
        APPLY_DELTA_TIME_INC(gFrameCounter8Bit);
        switch (gMainGameMode)
        {
            case GM_INIT_LINK:
                LinkResetSerial();
                gLinkFinishedDelayTimer = 0;
                gLinkTimer = 0;
                gLinkErrorFlag = 0;
                gMainGameMode++;
                break;

            case GM_HANDLE_LINK:
                APPLY_DELTA_TIME_INC(gLinkTimer);
                LinkHandleConnection();
                if (gLinkFinished & TRUE)
                {
                    APPLY_DELTA_TIME_INC(gLinkFinishedDelayTimer);
                    if (gLinkFinishedDelayTimer > CONVERT_SECONDS(.05f))
                    {
                        gUnk_70 = 0;
                        gUnk_7c = 0;
                        gUnk_6c0 = 0;
                        gMainGameMode++;
                    }
                }
                else if (gLinkErrorFlag != 0)
                {
                    gUnk_70 = 0;
                    gUnk_7c = 0;
                    gUnk_6c0 = 0;
                    gMainGameMode++;
                }
                if (gLinkTimer > CONVERT_SECONDS(1.5f))
                {
                    gLinkFinished |= TRUE;
                    gLinkErrorFlag = LINK_STAT_PARENT; // why set to parent?
                    gLinkTimer = 0;
                }
                break;

            case GM_EXIT_LINK:
                LinkDisableSerial();
                if (LoadGraphics() != 0)
                {
                    gDispCnt |= sDispRegsSettings.dispCntBg2;
                    gMainGameMode++;
                }
                else
                {
                    gMainGameMode += 2;
                }
                break;

            case GM_FADE_IN_LINK_TEXT:
                if (gBldAlpha_H != 0)
                {
                    if (gBldAlpha_H > 2)
                        gBldAlpha_H -= 2;
                    else
                        gBldAlpha_H = 0;

                    gBldAlpha_L = BLDALPHA_MAX_VALUE - gBldAlpha_H;
                    if (gBldAlpha_H == 0)
                        gMainGameMode++;
                }
                break;

            case GM_FINISHED:
        }

        VBlankIntrWait();
    }
}

/**
 * @brief 3c8 | c8 | Load the link complete or link error graphics
 * 
 * @return u32 bool, graphics loaded
 */
u32 LoadGraphics(void)
{
    u8 loadedGraphics;
    u8 graphicsOffset;

    graphicsOffset = 0x80;
    if ((u8)gLanguage <= LANGUAGE_END)
    {
        graphicsOffset = (u8)gLanguage;
    }
    else if (gZeroMissionGameCode == 1)
    {
        graphicsOffset = LANGUAGE_JAPANESE;
    }
    else if(gZeroMissionGameCode == 2 || (graphicsOffset = 0x80, gZeroMissionGameCode == 3))
    {
        graphicsOffset = LANGUAGE_ENGLISH;
    }
    
    if (graphicsOffset != 0x80)
    {
        if (gLinkErrorFlag != 0)
        {
            LZ77UncompVRAM(sLinkErrorGraphicsEntries[graphicsOffset], (sDispRegsSettings.bg3CntCharBase << BGCNT_SCREEN_SIZE_SHIFT) + VRAM_BASE + 0x5000);
            DMA_SET(3, VRAM_BASE + 0x1000, PALRAM_BASE, C_32_2_16(DMA_ENABLE, 240));
        }
        else
        {
            LZ77UncompVRAM(sLinkCompleteGraphicsEntries[graphicsOffset], (sDispRegsSettings.bg3CntCharBase << BGCNT_SCREEN_SIZE_SHIFT) + VRAM_BASE + 0x5000);
            DMA_SET(3, sPalette, PALRAM_BASE, C_32_2_16(DMA_ENABLE, ARRAY_SIZE(sPalette)));
        }
        loadedGraphics = TRUE;
    }
    else
    {
        loadedGraphics = FALSE;
    }
    return loadedGraphics;
}

/**
 * @brief 490 | 22c | Initialize game
 * 
 */
void InitializeGame(void)
{
    u8 tmp;
    u8 tmp2;
    u8 tmp3;
    
    dma_fill32(3, 0, IWRAM_BASE, IWRAM_SIZE - 0x15D);
    write16(REG_WAITCNT, WAIT_GAMEPACK_CGB | WAIT_BANK0_SUBSEQUENT_1CYCLE | WAIT_BANK0_3CYCLES);

    DMA_SET(3, sIntrTable, gIntrTable, C_32_2_16(DMA_ENABLE | DMA_32BIT, 56 / sizeof(u32)));
    DMA_SET(3, IntrMain, gInterruptCode, C_32_2_16(DMA_ENABLE | DMA_32BIT, sizeof(gInterruptCode) / sizeof(u32)));
    gIntrCodePointer = &gInterruptCode;

    dma_fill16(3, 0, VRAM_BASE, VRAM_SIZE);
    DMA_SET(3, sPalette, PALRAM_OBJ, C_32_2_16(DMA_ENABLE, ARRAY_SIZE(sPalette)));
    ApplyMonochromeToPalette(sPalette, PALRAM_BASE, 0);
    ApplyMonochromeToPalette(sPalette, VRAM_BASE + 0x1000, -8);

    LZ77UncompVRAM(sBackgroundImageGfx, ((tmp2 = sDispRegsSettings.bg3CntCharBase) << BGCNT_SCREEN_SIZE_SHIFT) + VRAM_BASE);
    LZ77UncompVRAM(sBackgroundImageTileTable, ((tmp = sDispRegsSettings.bg3CntScreenBase) << 11) + VRAM_BASE);
    LZ77UncompVRAM(sLinkTextTileTable, ((tmp3 = sDispRegsSettings.bg2CntScreenBase) << 11) + VRAM_BASE);

    dma_fill32(3, 0xA0, gUnk_2a0, ARRAY_SIZE(gUnk_2a0));
    dma_fill32(3, 0xA0, OAM_BASE, OAM_SIZE);
    ValidateGameVersion();

    write16(REG_BG0CNT, sDispRegsSettings.bg0CntPriority | sDispRegsSettings.v22 | (sDispRegsSettings.bg0CntScreenBase << BGCNT_SCREEN_BASE_BLOCK_SHIFT) | (sDispRegsSettings.bg0CntCharBase << BGCNT_CHAR_BASE_BLOCK_SHIFT));
    write16(REG_BG2CNT, sDispRegsSettings.bg2CntPriority | sDispRegsSettings.v6 | (tmp3 << BGCNT_SCREEN_BASE_BLOCK_SHIFT) | (sDispRegsSettings.bg2CntCharBase << BGCNT_CHAR_BASE_BLOCK_SHIFT));
    write16(REG_BG3CNT, sDispRegsSettings.bg3CntPriority | sDispRegsSettings.v14 | (tmp << BGCNT_SCREEN_BASE_BLOCK_SHIFT) | (tmp2 << BGCNT_CHAR_BASE_BLOCK_SHIFT));

    gCommand = LINKCMD_5500;
    gMainGameMode = GM_INIT_LINK;
    gLinkFinished = FALSE;
    gLanguage = 0xfe;
    gUnk_70 = 1;
    write16(REG_IE, IF_GAMEPAK | IF_VBLANK);
    write16(REG_DISPSTAT, DSTAT_IF_VBLANK);
    write16(REG_IF, 0xffff);
    write16(REG_IME, 1);
    gBldAlpha_H = BLDALPHA_MAX_VALUE;
    gBldAlpha_L = 0;
    gBldY = BLDY_MAX_VALUE;
    write16(REG_BLDY, gBldY);
    write16(REG_BLDALPHA, C_16_2_8(gBldAlpha_H, gBldAlpha_L));
    write16(REG_BLDCNT, BLDCNT_BACKDROP_SECOND_TARGET_PIXEL | BLDCNT_BG3_SECOND_TARGET_PIXEL | BLDCNT_ALPHA_BLENDING_EFFECT | BLDCNT_BG2_FIRST_TARGET_PIXEL);
    gDispCnt = sDispRegsSettings.dispCntBg3;
}

/**
 * @brief 6bc | fc | Handle connection, sending/receiving commands, and errors
 * 
 */
void LinkHandleConnection(void)
{
    vu32 c;
    u32* link_stat;
    
    gShouldAdvanceLinkState = gFrameCounter8Bit & 1;
    link_stat = &gLinkStatus;
    *link_stat = LinkMain(&gShouldAdvanceLinkState,&gSendCmd0,gRecvCmds);
    gLinkLocalId = *link_stat & LINK_STAT_LOCAL_ID;
    gLinkPlayerCount = EXTRACT_PLAYER_COUNT(*link_stat);
    gLinkUnkFlag9 = EXTRACT_LINK_ERRORS(*link_stat);
    if ((*link_stat & LINK_STAT_CONN_ESTABLISHED)) {
        gLinkTimer = 0;
        LinkBuildSendCmd(gCommand);
        LinkProcessRecvCmds();
    }
    if ((*link_stat & LINK_ERROR_ID_OVER)) {
        gLinkErrorFlag = 1;
    }
    if ((*link_stat & LINK_ERROR_CHECKSUM)) {
        gLinkErrorFlag = 2;
    }
    if ((*link_stat & LINK_ERROR_HARDWARE)) {
        gLinkErrorFlag = 3;
    }
    if ((*link_stat & LINK_ERROR_SEND_OVERFLOW)) {
        gLinkErrorFlag = 4;
    }
    if ((*link_stat & LINK_ERROR_RECEIVE_OVERFLOW)) {
        gLinkErrorFlag = 5;
    }
    if ((*link_stat & LINK_ERROR_SIO_INTERNAL)) {
        gLinkErrorFlag = 6;
    }
    if ((*link_stat & LINK_ERROR_SIO_STOP)) {
        gLinkErrorFlag = 7;
    }
}

/**
 * @brief 7b8 | 44 | Update the display for v-blank
 * 
 */
void UpdateDisplay(void)
{
    LinkVSync();
    write16(REG_DISPCNT, gDispCnt);
    write16(REG_BLDALPHA, C_16_2_8(gBldAlpha_H, gBldAlpha_L));
    gInterruptCheckFlag |= 1;
}

/**
 * @brief 7fc | 4c | (Unused) To document
 * 
 */
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

/**
 * @brief 848 | 30 | Updates the input
 * 
 */
void UpdateInput(void)
{
    u16 keys;

    keys = read16(REG_KEY_INPUT) ^ KEY_MASK;
    gChangedInput = keys & ~gPreviousButtonInput;
    gPreviousButtonInput = keys;
}

/**
 * @brief 878 | 24 | (Unused) Fill the destination with the source using palette
 * 
 * @param src The pointer to the source to copy from
 * @param dst The pointer to the destination to copy to
 * @param palette The palette to use
 */
void FillPalette(const u8 *src, u16 *dst, u8 palette)
{
    while (*src != 0)
    {
        *dst = (u16)*src | (palette << 12);
        src++;
        dst++;
    }
}

/**
 * @brief 89c | 4 | Empty callback
 * 
 */
void Callback_Empty(void)
{
    return;
}

/**
 * @brief 8a0 | a0 | Input commands into the send queue
 * 
 * @param command The command to send
 */
void LinkBuildSendCmd(u16 command)
{
    switch (command)
    {
        case LINKCMD_8800:
            gSendCmd[0] |= command;
            gSendCmd[1] = gPreviousButtonInput;
            // Buffer overflow
            gSendCmd[2] = gChangedInput;
            return;
        case LINKCMD_6600:
            gSendCmd[0] |= command;
            gSendCmd[1] = gFusionGameCode;
            break;
        case LINKCMD_5500:
            gSendCmd[0] |= command;
            gSendCmd[1] = gLanguage;
            break;
        case LINKCMD_3300:
            gSendCmd[0] |= command;
            gSendCmd[1] = gLinkFinished;
            break;
    }
    return;
}

/**
 * @brief 940 | 90 | Process commands from the receive queue
 * 
 */
void LinkProcessRecvCmds(void)
{
    u8 tmp;
    if ((gLinkStatus & LINK_STAT_RECEIVED_NOTHING))
        return;

    if (gRecvCmds[0][0] == LINKCMD_5500)
    {
        gLanguage = gRecvCmds[1][0];
        gLinkFinished = FALSE;
    }

    if (gRecvCmds[0][0] == LINKCMD_4400)
    {
        gCommand = LINKCMD_6600;
        gLinkFinished = FALSE;
    }

    if (gRecvCmds[0][0] == LINKCMD_2200)
    {
        gCommand = LINKCMD_3300;
    }

    if (gRecvCmds[0][1] == LINKCMD_3300)
    {
        gCommand = 0;
        tmp = gFusionGameCode - 1;
        if (tmp < 3)
        {
            gLinkFinished = TRUE;
        }
    }
    return;
}

/**
 * @brief 9d0 | 68 | Applies a monochrome effect to a palette
 * 
 * @param src Source address
 * @param dst Destination address
 * @param additionalValue Additional color
 */
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

/**
 * @brief a38 | 68 | Disable serial transfer
 * 
 */
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

/**
 * @brief aa0 | d4 | Enable serial transfer
 * 
 */
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

/**
 * @brief b74 | 10 | Reset the state of the serial transfer
 */
void LinkResetSerial(void)
{
    LinkEnableSerial();
    LinkDisableSerial();
}

/**
 * @brief b84 | 120 | Handle connection, sending data, and checking errors
 * 
 * @param shouldAdvanceLinkState Should advance link state
 * @param sendCmd The commands to send
 * @param recvCmds A queue of received commands
 * @return u32 The state of the connection
 */
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

/**
 * @brief ca4 | 2c | Check if the current connection is parent or child
 * 
 */
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

/**
 * @brief cd0 | 50 | Load timer 3 if the GBA is the parent
 * 
 */
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

/**
 * @brief d20 | e0 | Put commands into send queue
 * 
 * @param sendCmd The commands to send
 */
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

/**
 * @brief e00 | 108 | Get commands from recieve queue
 * 
 * @param recvCmds A queue of received commands
 */
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

/**
 * @brief f08 | 70 | Keep track of VSync frames and either start a transfer or lag out if enough frames has passed
 * 
 */
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

/**
 * @brief f78 | 10 | Reload timer 3 and start serial transfer
 * 
 */
void LinkReloadTransfer(void)
{
    // Called when timer 3 interrupts
    LinkStopTimer();
    LinkStartTransfer();
}

/**
 * @brief f88 | 90 | Establish a connection and send data
 * 
 */
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

/**
 * @brief 1018 | 10 | Start a serial transfer
 * 
 */
void LinkStartTransfer(void)
{
    write16(REG_SIO, read16(REG_SIO) | SIO_START_BIT_ACTIVE);
}

/**
 * @brief 1028 | fc | Try to perform the handshake between the parent and child connections
 * 
 * @return u8 bool, handshake was successfully performed
 */
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

/**
 * @brief 1124 | 108 | Receive a command from the receive queue
 * 
 */
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

/**
 * @brief 122c | 9c | Send a command from the send queue
 * 
 */
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

/**
 * @brief 12c8 | 34 | Stops the timer for the parent
 * 
 */
void LinkStopTimer(void)
{
    if (gLink.session.isParent)
    {
        // Turn off timer 3 and load in -132
        write16(REG_TM3CNT_H, read16(REG_TM3CNT_H) & ~TIMER_CONTROL_ACTIVE);
        write16(REG_TM3CNT_L, -132);
    }
}

/**
 * @brief 12fc | 30 | Send a signal that the receive command is done
 * 
 */
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

/**
 * @brief 132c | 48 | Clear the commands in the send queue
 * 
 */
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

/**
 * @brief 1374 | 5c | Clear the commands in the receive queue
 * 
 */
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

/**
 * @brief 13d0 | 24c | (Unused) Formats the number in a print statement
 * 
 * @param xPosition The x position of the text
 * @param yPosition The y position of the text
 * @param format The address of the format characters
 * @param value The value of the text to format
 * @param length The length of the text
 * @param output The address to output the formatted number text to
 */
void FormatNumber(u8 xPosition, u8 yPosition, u8 *format, u32 value, u8 length, u16* output)
{
    u8 formatted[8];
    u8 i;
    u32 powerOfTen;
    u8* caret;
    u32 truncatedValue;
    u16* outputCopy;

    caret = formatted;
    powerOfTen = 1;
    outputCopy = output;
    if (*format++ != '%')
        return;

    write64(formatted, 0);
    switch (*format)
    {
        case 'x':
        case 'X':
            for (i = 1; i <= length; i++)
                *caret++ = ((0xF << ((length - i) * 4)) & value) >> ((length - i) * 4);
            break;
    
        case 'd':
        case 'D':
            for (i = 1; i < length; i++)
                powerOfTen *= 10;

            truncatedValue = powerOfTen * 10;
            if (value >= truncatedValue)
                value -= (value / truncatedValue) * powerOfTen * 10;

            while (value != 0)
            {
                *caret = value / powerOfTen;
                value -= *caret * powerOfTen;
                caret++;
                powerOfTen /= 10;
            }
            break;
    
        case 'b':
        case 'B':
            truncatedValue = value & 0xFF;
            for (i = 1; i <= length; i++)
            {
                if ((1 << (length - i)) & truncatedValue)
                    *caret++ = 1;
                else
                    *caret++ = 0;
            }
            break;
    }

    caret = formatted;
    truncatedValue = yPosition * 32 + xPosition;
    for (i = 0; i < length; i++)
    {
        (outputCopy + truncatedValue)[i] = (*caret < 10) ? 0xF030 + *caret++ : 0xF037 + *caret++;
    }
}

/**
 * @brief 161c | 30 | Compares two strings
 * 
 * @param a The first string to compare
 * @param b The second string to compare
 * @param size The amount of characters to compare
 * @return u32 bool, strings not the same
 */
u32 CheckSameString(const char *a, const char *b, u8 size)
{
    s32 i;

    for (i = 0; i < size; i++) {
        if (b[i] != a[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief 164c | e8 | Validate the game version for Fusion and Zero Mission
 */
void ValidateGameVersion(void)
{
    gFusionGameCode = 0x50;
    if (CheckSameString(sMakerCodeMagicNumber, (u8*)0x80000b0, 3) == 0) {
        gFusionGameCode = 0x51;
        if (CheckSameString(sMetroidFusionJapaneseGameCode, (u8*)0x80000ac, 4) == 0) {
            gFusionGameCode = 1;
        }
        else if (CheckSameString(sMetroidFusionPalGameCode, (u8*)0x80000ac, 4) == 0) {
            gFusionGameCode = 2;
        }
        else if (CheckSameString(sMetroidFusionEnglishGameCode, (u8*)0x80000ac, 4) == 0) {
            gFusionGameCode = 3;
        }
    }

    gZeroMissionGameCode = 0x28;
    if (CheckSameString(sMakerCodeMagicNumber, (u8*)0x20000b0, 3) == 0) {
        gZeroMissionGameCode = 0x41;
        if (CheckSameString(sMetroidZeroMissionJapaneseGameCode, (u8*)0x20000ac, 4) == 0) {
            gZeroMissionGameCode = 1;
        }
        else if (CheckSameString(sMetroidZeroMissionPalGameCode, (u8*)0x20000ac, 4) == 0) {
            gZeroMissionGameCode = 2;
        }
        else if (CheckSameString(sMetroidZeroMissionEnglishGameCode, (u8*)0x20000ac, 4) == 0) {
            gZeroMissionGameCode = 3;
        }
    }
}
