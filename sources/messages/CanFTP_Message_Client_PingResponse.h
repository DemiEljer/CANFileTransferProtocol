#ifndef CANFTP_MESSAGE_CLIENT_PINGRESPONSE_H_
#define CANFTP_MESSAGE_CLIENT_PINGRESPONSE_H_

#include "CanFTP_Messages_Handlers.h"
#include "CanFTP_SoftwareVersion.h"

// Количество сообщений ответов на запрос Ping
#define CANFT_MESSAGE_CLIENT_PINGRESPONSE_COUNT 2

/*
    Тип сообщения ответа на запрос Ping
*/
typedef enum _CanFTP_Message_Client_PingResponse_Type
{
    CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE1 = 0,
    CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE2 = 1,
} CanFTP_Message_Client_PingResponse_Type_t;

/*
    Структура сообщения BlockControl
*/
typedef struct _CanFTP_Message_Client_PingResponse
{
    // Тип сообщения
    CanFTP_Message_Client_PingResponse_Type_t messageType;
    // Код устройства, полученный из серийного номера
    CanFTP_DeviceSerialCode_t deviceCode;
    // RESPONSE1
    struct
    {
        // Серийный номер устройства
        CanFTP_DeviceSerial_t deviceSerial;
        // Идентификатор устройства
        CanFTP_DeviceIdentifier_t deviceIdentifier;
        // Тип устройства
        CanFTP_DeviceType_t deviceType;

    } response1;
    // RESPONSE2
    struct
    {
        // Серийный номер устройства
        CanFTP_DeviceSerial_t deviceSerial;
        // Версия программного обеспечения
        CanFTP_SoftwareVersion_t deviceSoftVersion;
        
    } response2;

} CanFTP_Message_Client_PingResponse_t;

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_PingResponse_Unpack(CanFTP_Message_Client_PingResponse_t* messageModel, CanFTP_CanMessage_t* messageCan);
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_PingResponse_Pack(CanFTP_Message_Client_PingResponse_t* messageModel, CanFTP_CanMessage_t* messageCan);

#endif // CANFTP_MESSAGE_CLIENT_PINGRESPONSE_H_
