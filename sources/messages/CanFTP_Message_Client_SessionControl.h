/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_
#define CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_ClientSessionAckStatus.h"
#include "CanFTP_SessionStatus.h"

// Количество частей конфигурации сессии
#define CANFT_MESSAGE_CLIENT_CONFIGURATIONPARTS_COUNT 2

/*
    Тип сообщения при управлении сессией
*/
typedef enum _CanFTP_Message_Client_SessionControl_Type
{
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK = 0,
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK = 1,
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK = 2,
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK = 3,

} CanFTP_Message_Client_SessionControl_Type_t;
/*
    Индекс сообщения конфинурации
*/
typedef enum _CanFTP_Message_Client_SessionControl_ConfigurationPart
{
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART0 = 0,
    CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATION_PART1 = 1,

} CanFTP_Message_Client_SessionControl_ConfigurationPart_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Client_SessionControl
{
    // Тип сообщения
    CanFTP_Message_Client_SessionControl_Type_t messageType;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код устройства
    CanFTP_DeviceCode_t deviceCode;
    // REGISTRATIONACK
    struct
    {
        // Статус завершения операции
        CanFTP_ClientSessionAckStatus_t status;
        
    } registrationAck;
    // CONFIGURATIONACK
    struct
    {
        // Статус завершения операции
        CanFTP_ClientSessionAckStatus_t status;
        // Индекс части конфигурации
        CanFTP_Message_Client_SessionControl_ConfigurationPart_t partIndex;
        // PART0
        struct 
        {

        } part0;
        // PART1
        struct 
        {
            // Максимальный размер блока
            CanFTP_BlockLength_t maxBlockLength;

        } part1;

    } configurationAck;
    // STARTSESSIONACK
    struct
    {
        // Статус завершения операции
        CanFTP_ClientSessionAckStatus_t status;

    } startSessionAck;
    // FINISHSESSIONACK
    struct
    {
        // Статус завершения операции
        CanFTP_ClientSessionAckStatus_t status;
        // Статус сессии
        CanFTP_SessionStatus_t sessionStatus;

    } finishSessionAck;

} CanFTP_Message_Client_SessionControl_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_SessionControl_Unpack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_SessionControl_Pack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_
