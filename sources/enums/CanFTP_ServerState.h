/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVERSTATE_H_
#define CANFTP_SERVERSTATE_H_

// Количество состояний конечного автомата сервера
#define CANFTP_SERVERSTATES_COUNT 3

/*
    Состояние конечного автомата сервера
*/
typedef enum _CanFTP_ServerState
{
    // Сервер находится в состояние ожидания
    CANFTP_SERVERSTATE_IDLE = 0,
    // Сервер находится в состояние Ping
    CANFTP_SERVERSTATE_PING = 1,
    // Запущена хотя бы одна сессия     
    CANFTP_SERVERSTATE_SESSION = 2

} CanFTP_ServerState_t;

#endif // CANFTP_SERVERSTATE_H_
