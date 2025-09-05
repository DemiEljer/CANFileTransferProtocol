/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_
#define CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_SoftwareVersion.h"
#include "CanFTP_ClientSessionAckStatus.h"
#include "CanFTP_SessionStatus.h"

/*
    Тип сообщения при управлении сессией
*/
typedef enum _CanFTP_Message_Server_SessionControl_Type
{
    CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION = 0,
    CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START = 1,
    CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH = 2,
    CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT = 3,
} CanFTP_Message_Server_SessionControl_Type_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_SessionControl
{
    // Тип сообщения
    CanFTP_Message_Server_SessionControl_Type_t messageType;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    
    // CONFIGURATION
    struct
    {
        // Индекс страницы записи
        CanFTP_PageIndex_t pageIndex;
        // Длина передаваемого файла
        CanFTP_FileLength_t fileLength;
        // Количество повторных отправок сообщений подтверждения
        CanFTP_SendingRepeate_t repeateAckCount;
        // Интервал времени повторной отправки
        CanFTP_SendingRepeateInterval_t repeateInterval;

    } configuration;
    // START
    struct
    {
        // Тут ничего не упаковывается
    } start;
    // FINISH 
    struct
    {
        // Статус завершения операции
        CanFTP_SessionStatus_t sessionStatus;
        // Новая версия программного обеспечения
        CanFTP_SoftwareVersion_t newSoftVersion;

    } finish;
    // DELETECLIENT
    struct
    {
        // Статус завершения операции
        CanFTP_SessionStatus_t sessionStatus;
        // Новая версия программного обеспечения
        CanFTP_DeviceCode_t deviceCode;

    } deleteClient;

} CanFTP_Message_Server_SessionControl_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_SessionControl_Unpack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Pack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_SESSIONCONTROL_H_
