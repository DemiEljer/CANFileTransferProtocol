/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENT_SESSION_CONFIGURATION_H_
#define CANFTP_CLIENT_SESSION_CONFIGURATION_H_

#include "CanFTP_SoftwareVersion.h"

/*
    Структура конфигурации сессии на стороне клиента
*/
typedef struct _CanFTP_Client_Session_Configuration
{
    // Индекс первой страницы записи
    CanFTP_PageIndex_t firstPageIndex;
    // Количество страниц записи
    CanFTP_PageIndex_t pagesCount;
    // Новая версия программного обеспечения
    CanFTP_SoftwareVersion_t newSoftVersion;
    // Длина передаваемого файла
    CanFTP_FileLength_t fileLength;
    // Количество повторных отправок сообщений подтверждения при управлении сессией
    CanFTP_SendingRepeate_t sessionRepeateCount;
    // Интервал времени повторной отправки сообщений подтверждения при управлении сессией
    CanFTP_SendingRepeateInterval_t sessionRepeateInterval;
    // Количество повторных отправок сообщений подтверждения при передаче блока
    CanFTP_SendingRepeate_t blockRepeateCount;
    // Интервал времени повторной отправки сообщений подтверждения при передаче блока
    CanFTP_SendingRepeateInterval_t blockRepeateInterval;
    
} CanFTP_Client_Session_Configuration_t;

/*
    Сбросить конфигурацию сессии
*/
void CanFTP_Session_Configuratio_Reset(CanFTP_Client_Session_Configuration_t *configuration);

#endif // CANFTP_CLIENT_SESSION_CONFIGURATION_H_
