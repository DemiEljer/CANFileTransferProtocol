/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SESSION_FILEBLOCK_DEFINES_H_
#define CANFTP_SESSION_FILEBLOCK_DEFINES_H_

#include "CanFTP_ErrorHandlers.h"

// Максимальная длина блока файла (не больше 2048 и кратно 8)
#define CANFTP_FILEBLOCK_LENGTH 2048
// Размер фрейма блока файла
#define CANFTP_FILEBLOCK_FRAMESIZE 8
// Размер субблока (участки блока по N * FrameSize[8])
#define CANFTP_FILEBLOCK_SUBBBLOCKSIZE 4
// Максимальное количество фреймов блока файла
#define CANFTP_FILEBLOCK_FRAMESCOUNT (CANFTP_FILEBLOCK_LENGTH / CANFTP_FILEBLOCK_FRAMESIZE)
// Максимальная количество субблоков
#define CANFTP_FILEBLOCK_SUBBLOCKSCOUNT (CANFTP_FILEBLOCK_FRAMESCOUNT / CANFTP_FILEBLOCK_SUBBBLOCKSIZE)
// Размер контрольной суммы блока файла
#define CANFTP_FILEBLOCK_CRCLENGTH 8

/*
    Стркутура блока файла
*/
typedef struct _CanFTP_Session_FileBLock
{
    // Индекс блока
    CanFTP_BlockIndex_t index;
    // Длина блока
    CanFTP_BlockLength_t length;
    // Количество данных
    uint8_t data[CANFTP_FILEBLOCK_LENGTH];
    // Флаги подтверждения обработки фреймов
    CanFTP_Logical_t framesFlags[CANFTP_FILEBLOCK_FRAMESCOUNT]; 
    // Флаги подтверждения субблоков
    CanFTP_Logical_t subblocksFlags[CANFTP_FILEBLOCK_SUBBLOCKSCOUNT]; 

} CanFTP_Session_FileBlock_t;

#endif // CANFTP_SESSION_FILEBLOCK_DEFINES_H_
