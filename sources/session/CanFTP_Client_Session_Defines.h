/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENT_SESSION_DEFINES_H_
#define CANFTP_CLIENT_SESSION_DEFINES_H_

#include "CanFTP_Client_Session_Configuration.h"
#include "CanFTP_Session_ClientAssosiation.h"
#include "CanFTP_Session_FileBlock_Defines.h"

/*
    Структура сессии передачи файла
*/
typedef struct _CanFTP_Client_Session
{
    // Конфигурация сессии
    CanFTP_Client_Session_Configuration_t configuration;
    // Текущий блок файла
    CanFTP_Session_FileBlock_t block;

} CanFTP_Client_Session_t;

#endif // CANFTP_CLIENT_SESSION_DEFINES_H_
