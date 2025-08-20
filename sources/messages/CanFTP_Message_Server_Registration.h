#ifndef CANFTP_MESSAGE_SERVER_REGISTRATION_H_
#define CANFTP_MESSAGE_SERVER_REGISTRATION_H_

#include "CanFTP_Messages_Handlers.h"

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Server_Registration
{
    // Серийный номер устройства
    CanFTP_DeviceSerial_t deviceSerial;
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код устройства
    CanFTP_DeviceCode_t deviceCode;

} CanFTP_Message_Server_Registration_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_Registration_Unpack(CanFTP_Message_Server_Registration_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_Registration_Pack(CanFTP_Message_Server_Registration_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_SERVER_REGISTRATION_H_
