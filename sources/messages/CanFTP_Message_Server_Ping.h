/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_SERVER_PING_H_
#define CANFTP_MESSAGE_SERVER_PING_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_TerminationRequest.h"

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_Ping
{
    // Версия протокола
    CanFTP_ProtocolVersion_t protocolVersion;
    // Запрос на терминирование логики работы устройств
    CanFTP_TerminationRequest_t terminationRequest;

} CanFTP_Message_Server_Ping_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_Ping_Unpack(CanFTP_Message_Server_Ping_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_Ping_Pack(CanFTP_Message_Server_Ping_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_PING_H_
