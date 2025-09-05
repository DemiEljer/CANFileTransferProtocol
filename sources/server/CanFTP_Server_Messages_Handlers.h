/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_SERVER_MESSAGES_HANDLERS_H_
#define CANFTP_SERVER_MESSAGES_HANDLERS_H_

#include "CanFTP_Server_HelpFunctions.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Server_MessageRecieve_PingResponse(void* invoker, CanFTP_Message_Client_PingResponse_t* message);
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Client_SessionControl_t* message);
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Client_BlockControl_t* message);
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_MessageRecieve_SubBlocksStatuses(void* invoker, CanFTP_Message_Client_SubBlocksStatuses_t* message);
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_MessageRecieve_BlockCRC(void* invoker, CanFTP_Message_Client_BlockCRC_t* message);

/*
    Обработчик отправки сообщения Ping
*/
void CanFTP_Server_MessageSend_Ping(CanFTP_Server_t* server);
/*
    Обработчик отправки сообщения PingResponseAck
*/
void CanFTP_Server_MessageSend_PingResponseAck(CanFTP_Server_t* server);
/*
    Отправить сообщение
*/
void CanFTP_Server_MessageSend(CanFTP_Server_t* server, CanFTP_CanMessage_t* message);

#endif // CANFTP_SERVER_MESSAGES_HANDLERS_H_
