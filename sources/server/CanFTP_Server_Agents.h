/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_AGENTS_H_
#define CANFTP_SERVER_AGENTS_H_

#include "CanFTP_Server_Agents_Defines.h"

/*
    Сбросить контроллера процесса Ping
*/
void CanFTP_Server_Agent_PingControler_Reset(CanFTP_Server_Agent_PingControler_t* agent);

#endif // CANFTP_SERVER_AGENTS_H_
