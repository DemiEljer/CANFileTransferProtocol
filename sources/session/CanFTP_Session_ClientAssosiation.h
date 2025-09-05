/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SESSION_CLIENTASSOSIATION_H_
#define CANFTP_SESSION_CLIENTASSOSIATION_H_

#include "CanFTP_BaseTypes_Defines.h"

/*
    Структура ассоциации клинета и сессии
*/
typedef struct _CanFTP_Session_ClientAssosiation
{
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код клиента (устройства)
    CanFTP_DeviceCode_t deviceCode;

} CanFTP_Session_ClientAssosiation_t;

#endif // CANFTP_SESSION_CLIENTASSOSIATION_H_
