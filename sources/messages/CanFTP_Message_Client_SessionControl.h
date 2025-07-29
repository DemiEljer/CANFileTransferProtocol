#ifndef CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_
#define CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_ClientSessionAckStatus.h"
#include "CanFTP_ClientSessionFinishStatus.h"

/*
    Тип сообщения при управлении сессией
*/
typedef enum _CanFTP_Message_Client_SessionControl_Type
{
    CANFT_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK = 0,
    CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK = 1,
    CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK = 2,
    CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK = 3,
} CanFTP_Message_Client_SessionControl_Type_t;

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
        CanFTP_ClientSessionFinishStatus_t status;
    } finishSessionAck;

} CanFTP_Message_Client_SessionControl_t;

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_SessionControl_Unpack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_SessionControl_Pack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_SESSIONCONTROL_H_
