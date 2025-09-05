/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGES_HUB_H_
#define CANFTP_MESSAGES_HUB_H_

#include "CanFTP_Message_Client_BlockControl.h"
#include "CanFTP_Message_Client_BlockCRC.h"
#include "CanFTP_Message_Client_PingResponse.h"
#include "CanFTP_Message_Client_SessionControl.h"
#include "CanFTP_Message_Client_SubBlocksStatuses.h"
#include "CanFTP_Message_Server_BlockControl.h"
#include "CanFTP_Message_Server_DataFrame.h"
#include "CanFTP_Message_Server_Ping.h"
#include "CanFTP_Message_Server_PingResponseAck.h"
#include "CanFTP_Message_Server_Registration.h"
#include "CanFTP_Message_Server_SessionControl.h"

// Типы функций обратной связи на прием сообщений
typedef void (*CanFTP_Message_Client_BlockControl_RecieveCallback_t)(void*, CanFTP_Message_Client_BlockControl_t*);
typedef void (*CanFTP_Message_Client_BlockCRC_RecieveCallback_t)(void*, CanFTP_Message_Client_BlockCRC_t*);
typedef void (*CanFTP_Message_Client_PingResponse_RecieveCallback_t)(void*, CanFTP_Message_Client_PingResponse_t*);
typedef void (*CanFTP_Message_Client_SessionControl_RecieveCallback_t)(void*, CanFTP_Message_Client_SessionControl_t*);
typedef void (*CanFTP_Message_Client_SubBlocksStatuses_RecieveCallback_t)(void*, CanFTP_Message_Client_SubBlocksStatuses_t*);
typedef void (*CanFTP_Message_Server_BlockControl_RecieveCallback_t)(void*, CanFTP_Message_Server_BlockControl_t*);
typedef void (*CanFTP_Message_Server_DataFrame_RecieveCallback_t)(void*, CanFTP_Message_Server_DataFrame_t*);
typedef void (*CanFTP_Message_Server_Ping_RecieveCallback_t)(void*, CanFTP_Message_Server_Ping_t*);
typedef void (*CanFTP_Message_Server_PingResponseAck_RecieveCallback_t)(void*, CanFTP_Message_Server_PingResponseAck_t*);
typedef void (*CanFTP_Message_Server_Registration_RecieveCallback_t)(void*, CanFTP_Message_Server_Registration_t*);
typedef void (*CanFTP_Message_Server_SessionControl_RecieveCallback_t)(void*, CanFTP_Message_Server_SessionControl_t*);

/*
    Стрктура хаба обработки принимаемых сообщений
*/
typedef struct _CanFTP_Messages_Hub
{
    // Обратная вызов получения сообщения Client_BlockControl
    CanFTP_Message_Client_BlockControl_RecieveCallback_t clientBlockControlCallback;
    // Обратная вызов получения сообщения Client_BlockCRC
    CanFTP_Message_Client_BlockCRC_RecieveCallback_t clientBlockCRCCallback;
    // Обратная вызов получения сообщения Client_PingResponse
    CanFTP_Message_Client_PingResponse_RecieveCallback_t clientPingResponseCallback;
    // Обратная вызов получения сообщения Client_SessionControl
    CanFTP_Message_Client_SessionControl_RecieveCallback_t clientSessionControlCallback;
    // Обратная вызов получения сообщения Client_SubBlocksStatuses
    CanFTP_Message_Client_SubBlocksStatuses_RecieveCallback_t clientSubBlocksStatusesCallback;
    // Обратная вызов получения сообщения Server_BlockControl
    CanFTP_Message_Server_BlockControl_RecieveCallback_t serverBlockControlCallback;
    // Обратная вызов получения сообщения Server_DataFrame
    CanFTP_Message_Server_DataFrame_RecieveCallback_t serverDataFrameCallback;
    // Обратная вызов получения сообщения Server_Ping
    CanFTP_Message_Server_Ping_RecieveCallback_t serverPingCallback;
    // Обратная вызов получения сообщения Server_PingResponseAck
    CanFTP_Message_Server_PingResponseAck_RecieveCallback_t serverPingResponseAckCallback;
    // Обратная вызов получения сообщения Server_Registration
    CanFTP_Message_Server_Registration_RecieveCallback_t serverRegistrationCallback;
    // Обратная вызов получения сообщения Server_SessionControl
    CanFTP_Message_Server_SessionControl_RecieveCallback_t serverSessionControlCallback;

} CanFTP_Messages_Hub_t;

/*
    Обработка логики вызова обратных связей по приему сообщений
*/
void CanFTP_Messages_Hub_RecieveMessage(CanFTP_Messages_Hub_t* hub
    , CanFTP_CanMessage_t *canMessage
    , void* invoker
);

#endif // CANFTP_MESSAGES_HUB_H_
