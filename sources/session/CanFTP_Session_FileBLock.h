#ifndef CANFTP_SESSION_FILEBLOCK_H_
#define CANFTP_SESSION_FILEBLOCK_H_

#include "CanFTP_Session_FileBLock_Defines.h"

/*
    Сброс блока файла
*/
void CanFTP_Session_FileBlock_Reset(CanFTP_Session_FileBlock_t* block);
/*
    Сконфигурировать блок
*/
void CanFTP_Session_FileBlock_Configure(CanFTP_Session_FileBlock_t* block
    , CanFTP_BloclIndex_t index
    , CanFTP_BlockLength_t length);
/*
    Проинициализовать данные
*/
void CanFTP_Session_FileBlock_InitData(CanFTP_Session_FileBlock_t* block
    , CanFTP_BloclIndex_t index
    , CanFTP_BlockLength_t length
    , uint8_t* data);
/*
    Получить фрейм блока файла
*/
void CanFTP_Session_FileBlock_GetFrame(CanFTP_Session_FileBlock_t* block
    , CanFTP_FrameIndex_t frameIndex
    , uint8_t* data);
/*
    Записаь данных в блок файла
*/
void CanFTP_Session_FileBlock_SetFrame(CanFTP_Session_FileBlock_t* block
    , CanFTP_FrameIndex_t frameIndex
    , uint8_t* data);
/*
    Объединить флаги обработки кадров блока файла
*/
void CanFTP_Session_FileBlock_MergeFramesFlags(CanFTP_Session_FileBlock_t* block
    , CanFTP_Logical_t* framesFlags);
/*
    Верификация, что весь блок файла был обработан
*/
CanFTP_Logical_t CanFTP_Session_FileBlock_VerifySubblocks(CanFTP_Session_FileBlock_t* block);
/*
    Расчет контрольной суммы блока файла
*/
void CanFTP_Session_FileBlock_CalculateCRC(CanFTP_Session_FileBlock_t* block, uint8_t* crcArray);
/*
    Получить количество кадров блока файла
*/
CanFTP_FrameIndex_t CanFTP_Session_FileBlock_GetFramesCount(CanFTP_Session_FileBlock_t* block);
/*
    Получить количество субблоков блока файла
*/
CanFTP_FrameIndex_t CanFTP_Session_FileBlock_GetSubblockesCount(CanFTP_Session_FileBlock_t* block);

#endif // CANFTP_SESSION_FILEBLOCK_H_
