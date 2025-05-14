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
 * @brief 23c | 334 | Main game loop
 * 
 */
void AgbMain(void)
{
    u8 tmp3;
    u16 tmp;

    // Initialize Game
    write16(REG_WAITCNT, WAIT_GAMEPACK_CGB | WAIT_BANK0_SUBSEQUENT_1CYCLE | WAIT_BANK0_3CYCLES);
    DMA_SET(3, sIntrTable, gIntrTable, C_32_2_16(DMA_ENABLE | DMA_32BIT, 56 / sizeof(u32)));
    DMA_SET(3, IntrMain, gInterruptCode, C_32_2_16(DMA_ENABLE | DMA_32BIT, sizeof(gInterruptCode) / sizeof(u32)));
    gIntrCodePointer = &gInterruptCode;

    write16(PALRAM_BASE, COLOR_WHITE);
    LZ77UncompVRAM(sLinkTextTileTable, BGCNT_TO_VRAM_TILE_BASE(1));
    DMA_SET(3, sPalette, PALRAM_BASE + 15 * PAL_ROW_SIZE, C_32_2_16(DMA_ENABLE | DMA_32BIT, sizeof(sPalette) / sizeof(u32)));
    LZ77UncompVRAM(sLinkErrorEnglishGfx, BGCNT_TO_VRAM_CHAR_BASE(1));
    write16(REG_BG0CNT, CREATE_BGCNT(2, 0, BGCNT_HIGH_PRIORITY, BGCNT_SIZE_256x256));
    write16(REG_BG1CNT, CREATE_BGCNT(1, 1, BGCNT_HIGH_MID_PRIORITY, BGCNT_SIZE_256x256));

    gMainGameMode = GM_INIT_TRANSFER;
    gTransferUpdateResult = 0;
    gUnk_5020 = 0;
    gUnk_507c = 0;
    gUnk_5290 = 0;
    gScreenBreatheEffectTimer = 0;
    gScreenBreatheEffectOffset = 0;
    gScreenMode = SCREEN_MODE_FADE_IN;
    gBldY = 0;
    gUnk_508c = 0;
    tmp = gUnk_5078 = 0x10;

    write16(REG_IE, IF_GAMEPAK | IF_VBLANK);
    write16(REG_DISPSTAT, DSTAT_IF_VBLANK);
    write16(REG_IME, TRUE);
    write16(REG_BLDY, tmp = 0);
    write16(REG_BLDALPHA, tmp = BLDALPHA_MAX_VALUE);
    write16(REG_BLDCNT, BLDCNT_BRIGHTNESS_DECREASE_EFFECT | BLDCNT_BACKDROP_FIRST_TARGET_PIXEL);
    gDispCnt = DCNT_OBJ;
    write16(REG_DISPCNT, gDispCnt);
    write16(REG_RNCT, 0);
    write16(REG_SIO, SIO_MULTI_MODE);

    while (TRUE)
    {
        UpdateInput();

        switch (gMainGameMode)
        {
            case GM_INIT_TRANSFER:
                TransferInit();
                gMainGameMode++;

            case GM_HANDLE_TRANSFER:
                gTransferUpdateResult = TransferHandleTransfer(0, 0, NULL, EWRAM_BASE);
                gUnk_5020 = (u16)gTransferUpdateResult >> 8;
                tmp3 = GM_TRANSFER_FAILURE;
                if ((gTransferUpdateResult & TRANSFER_DATA_STAGE_MASK) == TRANSFER_DATA_STAGE_NONE)
                {
                    if (gTransferUpdateResult & (TRANSFER_VERIFY_SUCCESS << TRANSFER_VERIFY_SHIFT))
                    {
                        gMainGameMode = GM_TRANSFER_SUCCESS;
                        
                    }
                    else if (gTransferUpdateResult & (TRANSFER_VERIFY_FAILURE << TRANSFER_VERIFY_SHIFT))
                    {
                        gMainGameMode = GM_TRANSFER_FAILURE;
                    }
                }
                else
                {
                    if ((gTransferUpdateResult & (TRANSFER_ERROR_VERIFY_TIMEOUT << TRANSFER_ERROR_SHIFT)) == 0)
                    {
                        if ((gTransferUpdateResult & (TRANSFER_ERROR_UNK2 << TRANSFER_ERROR_SHIFT)) == 0)
                        {
                            if ((gTransferUpdateResult & (TRANSFER_ERROR_INIT_TIMEOUT << TRANSFER_ERROR_SHIFT)) == 0)
                            {
                                if ((gTransferUpdateResult & (TRANSFER_ERROR_INIT_TOO_MANY_CONNECTIONS << TRANSFER_ERROR_SHIFT)) == 0)
                                {
                                    gUnk_507c++;
                                    break;
                                }
                            }
                        }
                    }
                    gMainGameMode = tmp3;
                }
                break;

            case GM_TRANSFER_SUCCESS:
                if ((gPreviousButtonInput & (KEY_MASK & ~KEY_ALL_DIRECTIONS)) == 0)
                {
                    gScreenMode = SCREEN_MODE_FINISHED;
                    write16(REG_BLDY, gBldY = BLDY_MAX_VALUE);
                    ((Func_T)EWRAM_BASE)();
                }
                break;

            case GM_TRANSFER_FAILURE:
                gDispCnt |= DCNT_BG1;
                gScreenMode = SCREEN_MODE_FINISHED;

            case GM_FINISHED:
                gUnk_507c++;
                break;
        }

        if (gScreenBreatheEffectTimer != 0)
        {
            APPLY_DELTA_TIME_DEC(gScreenBreatheEffectTimer);
        }

        switch (gScreenMode)
        {
            case SCREEN_MODE_FADE_IN:
                gBldY += 2;
                if (gBldY >= BLDY_MAX_VALUE)
                {
                    gBldY = BLDY_MAX_VALUE;
                    gScreenBreatheEffectOffset = 0;
                    gScreenMode = SCREEN_MODE_BREATHE;
                }
                break;

            case SCREEN_MODE_BREATHE:
                if (gScreenBreatheEffectTimer == 0)
                {
                    gBldY = sScreenBreatheEffectValues[gScreenBreatheEffectOffset];
                    gScreenBreatheEffectTimer = CONVERT_SECONDS(1.f / 15);
                    gScreenBreatheEffectOffset++;
                    if (gScreenBreatheEffectOffset >= ARRAY_SIZE(sScreenBreatheEffectValues))
                    {
                        gScreenBreatheEffectOffset = 0;
                    }
                }
                break;

            case SCREEN_MODE_FINISHED:
                if (gBldY < BLDY_MAX_VALUE)
                {
                    gBldY++;
                }
                if (gBldY > BLDY_MAX_VALUE)
                {
                    gBldY = BLDY_MAX_VALUE;
                }
                break;
        }
        
        VBlankIntrWait();
    }
}

/**
 * @brief 570 | 28 | Update the display for v-blank
 * 
 */
void UpdateDisplay(void)
{
    write16(REG_BLDY, gBldY);
    write16(REG_DISPCNT, gDispCnt);
    gInterruptCheckFlag = TRUE;
}

/**
 * @brief 598 | 30 | Updates the input
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
 * @brief 5c8 | 4 | Empty function
 * 
 */
void empty_5c8(void)
{
    return;
}

/**
 * @brief 5cc | 4 | Empty callback
 * 
 */
void Callback_Empty(void)
{
    return;
}

/**
 * @brief 5d0 | 84 | (Unused) Process the serial transfer
 * 
 * @param recvBuffer Pointer to buffer to put data into
 * @return u32 Result of serial transfer update, 0 is finished, otherwise failure
 */
u32 TransferProcessRecv(u32 *recvBuffer)
{
    u32 result;
    u32 buffer;
    
    TransferBackupIoRegs();

    while (TRUE)
    {
        gTransferUpdateResult_Unused = TransferHandleTransfer(0, 0, NULL, recvBuffer);

        if ((gTransferUpdateResult_Unused & 7) == 4)
        {
            result = 0;
            break;
        }
        if (gTransferUpdateResult_Unused & (TRANSFER_ERROR_UNK2 << TRANSFER_ERROR_SHIFT))
        {
            result = 1;
            break;
        }
        if (gTransferUpdateResult_Unused & (TRANSFER_ERROR_VERIFY_TIMEOUT << TRANSFER_ERROR_SHIFT))
        {
            result = 2;
            break;
        }
        if (gTransferUpdateResult_Unused & (TRANSFER_ERROR_INIT_TIMEOUT << TRANSFER_ERROR_SHIFT))
        {
            result = 3;
            break;
        }
        if (gTransferUpdateResult_Unused & (TRANSFER_ERROR_INIT_TOO_MANY_CONNECTIONS << TRANSFER_ERROR_SHIFT))
        {
            result = 4;
            break;
        }

        VBlankIntrWait();
    }

    buffer = 0;
    CpuSet(&buffer, &gTransferManager, C_32_2_16(CPU_SET_32BIT | CPU_SET_SRC_FIXED, sizeof(gTransferManager) / sizeof(u32)));

    TransferRetrieveIoRegs();

    return result;
}

/**
 * @brief 654 | 54 | Initialize data for transfer
 * 
 */
void TransferInit(void)
{
    u32 buffer;

    gUnk_5002 = 0;
    gTransferDataTimer = 0;
    gTransferStartupTimer = 0;
    gTransferTimeoutTimer = 0;
    gTransferGbaDetectedCount = 0;
    gTransferGbaId = 0;

    buffer = 0;
    CpuSet(&buffer, &gTransferManager, C_32_2_16(CPU_SET_32BIT | CPU_SET_SRC_FIXED, sizeof(gTransferManager) / sizeof(u32)));
}

/**
 * @brief 6a8 | 40 | Stop serial transfer and timer 3
 * 
 */
void TransferCloseSerial(void)
{
    // Disable timer 3 and serial interrupt
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) & ~(IF_TIMER3 | IF_SERIAL));
    write16(REG_IME, TRUE);

    // Reset timer 3 and serial and acknowledge outstanding interrupt requests
    write16(REG_SIO, 0);
    write16(REG_TM3CNT_H, 0);
    write16(REG_IF, IF_TIMER3 | IF_SERIAL);
}

/**
 * @brief 6e8 | 58 | Set serial transfer to multi mode
 * 
 */
void TransferOpenSerialMulti(void)
{
    // Disable timer 3 and serial interrupt
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) & ~(IF_TIMER3 | IF_SERIAL));
    write16(REG_IME, TRUE);

    write16(REG_RNCT, 0);

    // Multi mode, baud rate = 115200 bits per second, request interrupt upon completion
    write16(REG_SIO, SIO_MULTI_MODE);
    write16(REG_SIO, read16(REG_SIO) | SIO_BAUD_RATE_115200 | SIO_IRQ_ENABLE);

    // Enable serial port interrupt
    write16(REG_IME, FALSE);
    write16(REG_IE, read16(REG_IE) | IF_SERIAL);
    write16(REG_IME, TRUE);
}

/**
 * @brief 740 | 24 | Set serial transfer to 32 bit transfer and set serial out to ready
 * 
 */
void TransferOpenSerial32(void)
{
    write16(REG_RNCT, 0);
    write16(REG_SIO, SIO_32BIT_MODE | SIO_IRQ_ENABLE);
    write16(REG_SIO, read16(REG_SIO) | SIO_MULTI_CONNECTION_READY);
}

/**
 * @brief 764 | 174 | Handle the serial transfer
 * 
 * @param transferMode (Unused) Transfer mode, 0 is receiving, 1 is sending
 * @param Size Data size
 * @param pData Pointer to data to transfer
 * @param recvBuffer Pointer to data to receive
 * @return u16 Bits 0-1 is dataTransferStage, bits 2-3 is verifyTransferResult, bits 4-7 is errorDuringTransfer, bits 8+ is unk_2
 */
u16 TransferHandleTransfer(u32 transferMode, u32 size, const u32* pData, u32* recvBuffer)
{
    // pData is transfer rom, size is size of transfer rom
    switch (gTransferManager.status.stage)
    {
        case TRANSFER_STAGE_INIT:
            // Clear and set up transfer
            TransferInit();
            TransferOpenSerialMulti();
            gTransferManager.status.dataTransferStage = TRANSFER_DATA_STAGE_INIT;
            gTransferManager.status.stage = TRANSFER_STAGE_SETUP_CONNECTION;
            break;

        case TRANSFER_STAGE_SETUP_CONNECTION:
            if (gTransferManager.status.errorDuringTransfer != TRANSFER_ERROR_NONE)
                gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;

            APPLY_DELTA_TIME_INC(gTransferStartupTimer);
            // If more than half a second passes, fail
            if (gTransferStartupTimer > CONVERT_SECONDS(.5f))
            {
                gTransferManager.status.errorDuringTransfer = TRANSFER_ERROR_INIT_TIMEOUT;
                gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;
            }
            break;

        case TRANSFER_STAGE_SETUP_DATA:
            // Set up transmission for size of data to transfer?
            TransferOpenSerial32();
            TransferSetUpTransferManager(size, pData, recvBuffer);
            gTransferManager.status.stage = TRANSFER_STAGE_TRANSFER_DATA;

        case TRANSFER_STAGE_TRANSFER_DATA:
            if (gTransferManager.status.isParent == FALSE)
            {
                APPLY_DELTA_TIME_INC(gTransferTimeoutTimer);
                if (gTransferTimeoutTimer > CONVERT_SECONDS(.5f))
                {
                    gTransferManager.status.errorDuringTransfer = TRANSFER_ERROR_VERIFY_TIMEOUT;
                    gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;
                }
            }
            
            if (gTransferManager.status.dataTransferStage == TRANSFER_DATA_STAGE_SENDING)
                break;

            if (gTransferManager.status.isParent)
            {
                APPLY_DELTA_TIME_INC(gTransferDataTimer);
                if (gTransferDataTimer >= CONVERT_SECONDS(1.f / 6))
                {
                    TransferStartTransfer();
                    gTransferManager.status.dataTransferStage = TRANSFER_DATA_STAGE_SENDING;
                    break;
                }
            }

            TransferStartTransfer();
            gTransferManager.status.dataTransferStage = TRANSFER_DATA_STAGE_SENDING;
            break;

        case TRANSFER_STAGE_SETUP_VERIFICATION:
            TransferOpenSerialMulti();
            gTransferManager.status.stage = TRANSFER_STAGE_VERIFY_DATA;
            break;

        case TRANSFER_STAGE_VERIFY_DATA:
            APPLY_DELTA_TIME_INC(gTransferDataTimer);
            if (gTransferDataTimer > CONVERT_SECONDS(.5f))
            {
                gTransferManager.status.errorDuringTransfer = TRANSFER_ERROR_VERIFY_TIMEOUT;
                gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;
            }
            break;

        case TRANSFER_STAGE_TERMINATE_CONNECTION:
            if (gTransferManager.status.dataTransferStage != TRANSFER_DATA_STAGE_NONE)
            {
                TransferCloseSerial();
                gTransferManager.status.dataTransferStage = TRANSFER_DATA_STAGE_NONE;
            }
            break;
    }

    gTransferManager.status.unk_2 = gTransferManager.data.cursor * 100 / gTransferManager.data.sizeInt;

    return gTransferManager.status.dataTransferStage << TRANSFER_DATA_STAGE_SHIFT | 
           gTransferManager.status.verifyTransferResult << TRANSFER_VERIFY_SHIFT | 
           gTransferManager.status.errorDuringTransfer << TRANSFER_ERROR_SHIFT | 
           gTransferManager.status.unk_2 << 8;
}

/**
 * @brief 8d8 | c | (Unused) Determine if all GBA's are ready and the GBA is the parent or child
 * 
 */
void TransferDetermineSendRecvState(void)
{
    // Original checks are removed, thus it always sets to child
    gTransferManager.status.isParent = FALSE;
}

/**
 * @brief 8e4 | 14 | Set up the data to transfer
 * 
 * @param size (Unused) Data size
 * @param pData (Unused) Pointer to data to send
 * @param recvBuffer Pointer to data to receive
 */
void TransferSetUpTransferManager(u32 size, const u32* pData, u32* recvBuffer)
{
    write16(REG_SIO, read16(REG_SIO));
    
    gTransferManager.data.pData = recvBuffer;
}

/**
 * @brief 8f8 | 1c0 | Exchange data over serial
 * 
 */
void TransferExchangeData(void)
{
    // Called when serial communication interrupts
    u16 recv[4];
    u32 control;
    u16 i;
    u16 numGbaDetected;
    u16 numGbaSendingData;
    u32 recv32;
    u32 tmp;

    control = read32(REG_SIO);

    switch (gTransferManager.status.stage)
    {
        case TRANSFER_STAGE_SETUP_CONNECTION:
            write16(REG_SIO_DATA8, TRANSFER_HANDSHAKE); // Outgoing data
            write64(recv, read64(REG_SIO_MULTI));

            i = 0;
            numGbaDetected = 0;
            numGbaSendingData = 0;

            for (; i < ARRAY_SIZE(recv); i++)
            {
                // if GBA either sent or is receiving data
                if (recv[i] == TRANSFER_HANDSHAKE)
                    numGbaDetected++;
                // if receiving some data
                else if (recv[i] != USHORT_MAX)
                    numGbaSendingData++;
            }

            gTransferGbaDetectedCount = numGbaDetected;
            gTransferGbaId = (control << 26) >> 30; // SIO_MULTI_CONNECTION_ID_FLAG

            // If 0-2 GBA's detected
            if (numGbaDetected <= 2)
            {
                // If 2 GBA's detected and not sending anymore data
                if (numGbaDetected >= 2 && numGbaSendingData == 0)
                    gTransferManager.status.stage = TRANSFER_STAGE_SETUP_DATA;
            }
            else
                gTransferManager.status.errorDuringTransfer = TRANSFER_ERROR_INIT_TOO_MANY_CONNECTIONS;
            break;

        case TRANSFER_STAGE_TRANSFER_DATA:
            recv32 = read32(REG_SIO_MULTI);

            if (gTransferManager.data.cursor == gTransferGbaId - 1)
            {
                gTransferManager.data.sizeInt = recv32 / sizeof(u32) + 1;
            }

            if (gTransferManager.data.cursor >= gTransferGbaId && gTransferManager.data.cursor < gTransferManager.data.sizeInt + gTransferGbaId)
            {
                gTransferManager.data.pData[gTransferManager.data.cursor - gTransferGbaId] = recv32;
                gTransferManager.data.checksum += recv32;
            }
            else if (gTransferManager.data.cursor == gTransferManager.data.sizeInt + gTransferGbaId)
            {
                if (gTransferManager.data.checksum == recv32)
                {
                    gTransferManager.status.verifyTransferResult = TRANSFER_VERIFY_SUCCESS;
                }
                else
                {
                    gTransferManager.status.verifyTransferResult = TRANSFER_VERIFY_FAILURE;
                }
            }

            gTransferTimeoutTimer = 0;
            gTransferManager.data.cursor++;

            if (gTransferManager.data.cursor < (gTransferManager.data.sizeInt + gTransferGbaDetectedCount))
            {
                TransferStartTransfer();
            }
            else
            {
                gTransferManager.status.stage = TRANSFER_STAGE_SETUP_VERIFICATION;
                gTransferDataTimer = 0;
            }
            break;

        case TRANSFER_STAGE_VERIFY_DATA:
            write16(REG_SIO_DATA8, gTransferManager.status.verifyTransferResult);
            write64(recv, read64(REG_SIO_MULTI));

            i = 1; // start from GBA receiving data?
            numGbaDetected = 1;

            for (i; i < gTransferGbaDetectedCount; i++)
            {
                // if child GBA 1 correctly sends 1
                if (recv[i] == 1)
                    numGbaDetected++;
                // if another child GBA sends 1 (this shouldn't happen?)
                else if (recv[i] == 2)
                {
                    gTransferManager.status.verifyTransferResult = TRANSFER_VERIFY_FAILURE;
                    gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;
                    break;
                }

                // Check if correct number of GBA's sent correct data
                if (numGbaDetected == gTransferGbaDetectedCount)
                {
                    gTransferManager.status.verifyTransferResult = TRANSFER_VERIFY_SUCCESS;
                    gTransferManager.status.stage = TRANSFER_STAGE_TERMINATE_CONNECTION;
                }
            }
            break;
    }
}

/**
 * @brief ab8 | 10 | Start a serial transfer
 * 
 */
void TransferStartTransfer(void)
{
    write16(REG_SIO, read16(REG_SIO) | SIO_START_BIT_ACTIVE);
}

/**
 * @brief ac8 | 54 | Makes a backup of the registers used for transfer
 * 
 */
void TransferBackupIoRegs(void)
{
    gRegIme_Backup = read16(REG_IME);
    gRegIe_Backup = read16(REG_IE);
    gRegTm3Cnt_H_Backup = read16(REG_TM3CNT_H);
    gRegSiocnt_Backup = read16(REG_SIO);
    gRegRcnt_Backup = read16(REG_RNCT);
}

/**
 * @brief b1c | 44 | Retrieves the registers used for transfer from the backups
 * 
 */
void TransferRetrieveIoRegs(void)
{
    write16(REG_IME, gRegIme_Backup);
    write16(REG_IE, gRegIe_Backup);
    write16(REG_TM3CNT_H, gRegTm3Cnt_H_Backup);
    write16(REG_SIO, gRegSiocnt_Backup);
    write16(REG_RNCT, gRegRcnt_Backup);
}

/**
 * @brief b60 | 244 | (Unused) Formats the number in a print statement
 * 
 * @param xPosition The x position of the text
 * @param yPosition The y position of the text
 * @param format The address of the format characters
 * @param value The value of the text to format
 * @param length The length of the text
 * @param output The address to output the formatted number text to
 * @param palette The palette of the text
 */
void FormatNumber(u8 xPosition, u8 yPosition, u8 *format, u32 value, u8 length, u16* output, u8 palette)
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
        (outputCopy + truncatedValue)[i] = (*caret <= 9 ? *caret++ + '0' : *caret++ + '7') | (palette << 12);
    }
}

/**
 * @brief da4 | 2e8 | To document
 * 
 * @param typeSize The size of the number to output (1 byte, 2 bytes, 4 bytes)
 * @param param_2 To document
 * @param param_3 To document
 * @param output The address to output to
 */
void unk_da4(u8 typeSize, u32 param_2, u16 param_3, u16 *output)
{
    u16 i;
    u16 j;
    u8 value;
    u32 value32;
    u16* outputCaret;
    u8* values8;
    u16* values16;
    u32* values32;

    outputCaret = output;

    for (i = 0; i < 8; i++)
    {
        value = ((param_2 + param_3 * 8) & (0xF << ((7 - i) * 4))) >> ((7 - i) * 4);

        *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    }

    outputCaret = output + 0x61;

    for (i = 0; i < 16; i++)
    {
        for (j = 4; j < 8; j++)
        {
            value = ((param_2 + param_3 * 8 + i * 8) & (0xF << ((7 - j) * 4))) >> ((7 - j) * 4);

            *outputCaret++ = value <= 9 ? value + '0' : value + '7';
        }

        outputCaret += 28;
    }

    outputCaret = output + 0x66;
    switch (typeSize)
    {
        case 0:
            values8 = (u8*)(param_2 + param_3 * 8);
            for (i = 0; i < 16; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    value = (*values8 & (0xF << 4)) >> 4;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values8++ & (0xF << 0)) >> 0;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
                    *outputCaret++ = 0;
                }

                outputCaret += 8;
            }
            break;

        case 1:
            values16 = (u16*)(param_2 + param_3 * 16);
            for (i = 0; i < 16; i++)
            {
                for (j = 0; j < 4; j++)
                {
                    value = (*values16 & (0xF << 12)) >> 12;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values16 & (0xF << 8)) >> 8;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values16 & (0xF << 4)) >> 4;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values16 & (0xF << 0)) >> 0;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
                    *outputCaret++ = 0;

                    values16++;
                }

                write64(outputCaret, 0);
                outputCaret += 12;
            }
            break;

        case 2:
            values32 = (u32*)(param_2 + param_3 * 32);
            for (i = 0; i < 16; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    value = (*values32 & (0xF << 28)) >> 28;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 24)) >> 24;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 20)) >> 20;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 16)) >> 16;
                    *outputCaret = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 12)) >> 12;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 8)) >> 8;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 4)) >> 4;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
    
                    value = (*values32 & (0xF << 0)) >> 0;
                    *outputCaret++ = value <= 9 ? value + '0' : value + '7';
                    *outputCaret++ = 0;

                    values32++;
                }

                write64(outputCaret, 0);
                outputCaret += 16;
            }
    }
}

/**
 * @brief 108c | 134 | (Unused) Draws a time in (hour, minute, second) format
 * 
 * @param digit The digits to draw (hours, minutes, or seconds)
 * @param xPosition The x position of the text
 * @param yPosition The y position of the text
 * @param time The time to draw
 * @param src The base address of the output
 * @param palette The palette of the timer
 */
void DrawTime(u8 digit, u8 xPosition, u8 yPosition, u32 time, u16* src, u8 palette)
{
    u8 hours;
    u8 minutes;
    u8 seconds;
    u16 *dst;
    u8 hoursTens;
    u8 minutesTens;
    u8 secondsTens;

    dst = src + xPosition + yPosition * 32;

    hours = time / (60 * 60 * 60);
    time -= hours * (60 * 60 * 60);

    minutes = time / (60 * 60);
    time -= minutes * (60 * 60);

    seconds = time / (60);

    switch (digit)
    {
        case TIMER_DRAW_HOURS:
            hoursTens = hours / 10;
            hours -= hoursTens * 10;

            *dst++ = (palette << 12) | (hoursTens + '0');
            *dst++ = (palette << 12) | (hours + '0');
            *dst++ = (palette << 12) | 'H';

        case TIMER_DRAW_MINUTES:
            minutesTens = minutes / 10;
            minutes -= minutesTens * 10;

            *dst++ = (palette << 12) | (minutesTens + '0');
            *dst++ = (palette << 12) | (minutes + '0');
            *dst++ = (palette << 12) | 'M';

        case TIMER_DRAW_SECONDS:
            secondsTens = seconds / 10;
            seconds -= secondsTens * 10;

            *dst++ = (palette << 12) | (secondsTens + '0');
            *dst++ = (palette << 12) | (seconds + '0');
            *dst++ = (palette << 12) | 'S';
    }
}
