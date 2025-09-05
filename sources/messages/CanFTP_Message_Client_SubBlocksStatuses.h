/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_CLIENT_SUBBLOCKSSTATUSES_H_
#define CANFTP_MESSAGE_CLIENT_SUBBLOCKSSTATUSES_H_

#include "CanFTP_Messages_Handlers.h"

// Количество субблоков
#define CANFTP_SUBBLOCKS_COUNT  64

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Client_SubBlocksStatuses
{
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код устройства
    CanFTP_DeviceCode_t deviceCode;
    // Флаги подтверждения принятия субблоков
    CanFTP_Logical_t subblocksReciecedFlags[CANFTP_SUBBLOCKS_COUNT];

} CanFTP_Message_Client_SubBlocksStatuses_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_SubBlocksStatuses_Unpack(CanFTP_Message_Client_SubBlocksStatuses_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_SubBlocksStatuses_Pack(CanFTP_Message_Client_SubBlocksStatuses_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_SUBBLOCKSSTATUSES_H_
