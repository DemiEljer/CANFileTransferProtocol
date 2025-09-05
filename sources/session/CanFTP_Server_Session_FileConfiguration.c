/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_Session_FileConfiguration.h"

/*
    Сбросить конфигурацию файла
*/
void CanFTP_Server_Session_FileConfiguration_Reset(CanFTP_Server_Session_FileConfiguration_t* configuration)
{
    configuration->pageIndex = 0;
    configuration->fileLength = 0;
    configuration->maxBlockLength = CANFTP_FILEBLOCK_LENGTH;
    CanFTP_SoftwareVersion_Reset(&(configuration->newSoftVersion));
}
/*
    Инициализация базовых параметров конфигурации файла
*/
void CanFTP_Server_Session_FileConfiguration_InitBaseParamns(CanFTP_Server_Session_FileConfiguration_t* configuration
    , CanFTP_PageIndex_t pageIndex
    , CanFTP_FileLength_t fileLength)
{
    configuration->pageIndex = pageIndex;
    configuration->fileLength = fileLength;
}
/*
    Инициализация максимальной длины блока
*/
void CanFTP_Server_Session_FileConfiguration_InitMaxBlockLength(CanFTP_Server_Session_FileConfiguration_t* configuration, CanFTP_BlockLength_t maxBlockLength)
{
    // Назначение новой максимальной длины блока файла только в случае, если она мешньше
    // Работы по устройству с наименьшим буфером
    if (maxBlockLength < configuration->maxBlockLength)
    {
        configuration->maxBlockLength = maxBlockLength;
    }
}
