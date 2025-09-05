/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_SERVER_PINGRESPONSEACK_H_
#define CANFTP_MESSAGE_SERVER_PINGRESPONSEACK_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_Message_Client_PingResponse.h"

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_PingResponseAck
{
    // Тип сообщения
    CanFTP_Message_Client_PingResponse_Type_t responseType;
    // Серийный номер устройства
    CanFTP_DeviceSerial_t deviceSerial;

} CanFTP_Message_Server_PingResponseAck_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_PingResponseAck_Unpack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_PingResponseAck_Pack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_PINGRESPONSEACK_H_
