/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_SESSION_CONFIGURATION_H_
#define CANFTP_SERVER_SESSION_CONFIGURATION_H_

#include "CanFTP_TimeHandlers.h"
#include "CanFTP_IterationsHandler.h"
#include "CanFTP_Server_Session_Params.h"

/*
    Структура конфигурации сессии на стороне сервера
*/
typedef struct _CanFTP_Server_Session_Configuration
{
    // Интервалы времени отправки сообщений при регистрации клиентов
    CanFTP_TimeInterval_t registrationInterval;
    // Количество повторных отправок сообщений при регистрации клиентов
    CanFTP_IterationCounter_t registrationRepeateCount;
    // Интервалы времени отправки сообщений при управлении сессией
    CanFTP_TimeInterval_t sessionControlInterval;
    // Количество повторных отправок сообщений при управлении сессей
    CanFTP_IterationCounter_t sessionControlRepeateCount;
    // Количество повторных отправок блока
    CanFTP_SendingRepeate_t repeateBlockCount;
    // Интервалы времени отправки сообщений при управлении процессом отправки блока
    CanFTP_TimeInterval_t blockControlInterval;
    // Количество повторных отправок сообщений при управлении процессом отправки блока
    CanFTP_IterationCounter_t blockControlRepeateCount;
    // Интервалы времени отправки кадров блока
    CanFTP_TimeInterval_t frameSendingInterval;
    // Количество повторных отправок сообщений подтверждения при управлении сессией (клиентом)
    CanFTP_SendingRepeate_t clientSessionRepeateCount;
    // Интервал времени повторной отправки сообщений подтверждения при управлении сессией (клиентом)
    CanFTP_SendingRepeateInterval_t clientSessionRepeateInterval;
    // Количество повторных отправок сообщений подтверждения при передаче блока (клиентом)
    CanFTP_SendingRepeate_t clientBlockRepeateCount;
    // Интервал времени повторной отправки сообщений подтверждения при передаче блока (клиентом)
    CanFTP_SendingRepeateInterval_t clientBlockRepeateInterval;

} CanFTP_Server_Session_Configuration_t;

/*
    Сбросить конфигурацию
*/
void CanFTP_Server_Session_Configuration_Reset(CanFTP_Server_Session_Configuration_t* configuration);
/*
    Скопировать конфигурацию
*/
void CanFTP_Server_Session_Configuration_Copy(CanFTP_Server_Session_Configuration_t* to, CanFTP_Server_Session_Configuration_t* from);

#endif // CANFTP_SERVER_SESSION_CONFIGURATION_H_
