#ifndef CANFTP_MESSAGE_CLIENT_BLOCKCRC_H_
#define CANFTP_MESSAGE_CLIENT_BLOCKCRC_H_

#include "CanFTP_Messages_Handlers.h"

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Client_BlockCRC
{
    // Код сессии
    CanFTP_SessionCode_t sessionCode;
    // Код устройства
    CanFTP_DeviceCode_t deviceCode;
    // Элементы CRC-суммы
    uint8_t crcElements[8];

} CanFTP_Message_Client_BlockCRC_t;

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_BlockCRC_Unpack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_BlockCRC_Pack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_BLOCKCRC_H_
