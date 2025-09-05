/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_HELPFUNCTIONS_H_
#define CANFTP_SERVER_HELPFUNCTIONS_H_

#include "CanFTP_Server_Defines.h"

/*
    Получить состояние сервера
*/
CanFTP_ServerState_t CanFTP_Server_GetState(CanFTP_Server_t *server);
/*
    Проверить, что в данный момент разрешено начать процесс Ping
*/
CanFTP_Logical_t CanFTP_Server_PingPermition(CanFTP_Server_t *server);
/*
    Проверить, что в данный момент разрешено создать сессию
*/
CanFTP_Logical_t CanFTP_Server_CreateSessionPermition(CanFTP_Server_t *server);

#endif // CANFTP_SERVER_HELPFUNCTIONS_H_
