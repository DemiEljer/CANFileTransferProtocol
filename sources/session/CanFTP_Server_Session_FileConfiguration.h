/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_FILECONFIGURATION_H_
#define CANFTP_SERVER_SESSION_FILECONFIGURATION_H_

#include "CanFTP_Session_FileBlock.h"
#include "CanFTP_SoftwareVersion.h"

/*
    Структура конфигурации файла на стороне сервера
*/
typedef struct _CanFTP_Server_Session_FileConfiguration
{
    // Индекс первой страницы записи
    CanFTP_PageIndex_t firstPageIndex;
    // Количество страниц записи
    CanFTP_PageIndex_t pagesCount;
    // Длина файла
    CanFTP_FileLength_t fileLength;
    // Максимальный длина блока
    CanFTP_BlockLength_t maxBlockLength;
    // Новая версия программного обеспечения
    CanFTP_SoftwareVersion_t newSoftVersion;
    
} CanFTP_Server_Session_FileConfiguration_t;

/*
    Сбросить конфигурацию файла
*/
void CanFTP_Server_Session_FileConfiguration_Reset(CanFTP_Server_Session_FileConfiguration_t* configuration);
/*
    Инициализация базовых параметров конфигурации файла
*/
void CanFTP_Server_Session_FileConfiguration_InitBaseParamns(CanFTP_Server_Session_FileConfiguration_t* configuration
    , CanFTP_PageIndex_t firstPageIndex
    , CanFTP_PageIndex_t pagesCount
    , CanFTP_FileLength_t fileLength);
/*
    Инициализация максимальной длины блока
*/
void CanFTP_Server_Session_FileConfiguration_InitMaxBlockLength(CanFTP_Server_Session_FileConfiguration_t* configuration, CanFTP_BlockLength_t maxBlockLength);


#endif // CANFTP_SERVER_SESSION_FILECONFIGURATION_H_
