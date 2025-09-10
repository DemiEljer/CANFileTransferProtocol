/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_H_
#define CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_ClientBlockHandlingStatus.h"

/*
    Тип сообщения управления блоком
*/
typedef enum _CanFTP_Message_Client_BlockControl_Type
{
    CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_START = 0,
    CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_FINISH = 1,
    
} CanFTP_Message_Client_BlockControl_Type_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Client_BlockControl
{
    // Тип сообщения
    CanFTP_Message_Client_BlockControl_Type_t messageType;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код устройства
    CanFTP_DeviceCode_t deviceCode;
    // START
    struct
    {
        // Тут ничего не упаковывается
    } startBlockAck;
    // FINISH
    struct
    {
        // Статус обработки блока
        CanFTP_ClientBlockHandlingStatus_t blockHandlingStatus;
        
    } finishBlockAck;

} CanFTP_Message_Client_BlockControl_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_BlockControl_Unpack(CanFTP_Message_Client_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_BlockControl_Pack(CanFTP_Message_Client_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_H_
