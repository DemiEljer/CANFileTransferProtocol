/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_CLIENT_SESSION_H_
#define CANFTP_CLIENT_SESSION_H_

#include "CanFTP_Client_Session_Defines.h"
#include "CanFTP_Session_FileBlock.h"

/*
    Сбросить сессию
*/
void CanFTP_Client_Session_Reset(CanFTP_Client_Session_t *session);

#endif // CANFTP_CLIENT_SESSION_H_
