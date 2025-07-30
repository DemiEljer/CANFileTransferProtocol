#include "CanFTP_Message_Server_PingResponseAck.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_PingResponseAck_Unpack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_PINGRESPONSE, 8))
    {
        messageModel->responseType = (CanFTP_Message_Client_PingResponse_Type_t)(messageCan->data[0] & 0x0F);
        messageModel->deviceSerial = (CanFTP_DeviceSerial_t)(
              (CanFTP_DeviceSerial_t)((messageCan->data[0] >> 4) & 0x0F) 
            | (CanFTP_DeviceSerial_t)((messageCan->data[1] >> 0) & 0xFF) << 4
            | (CanFTP_DeviceSerial_t)((messageCan->data[2] >> 0) & 0xFF) << 12
            | (CanFTP_DeviceSerial_t)((messageCan->data[3] >> 0) & 0xFF) << 20
            | (CanFTP_DeviceSerial_t)((messageCan->data[4] >> 0) & 0x0F) << 28
        );
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_PingResponseAck_Pack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= ((messageModel->responseType & 0x0F) << 0)
                                | (((messageModel->deviceSerial >> 0) & 0x0F) << 4);
        messageDataVector[1] |= ((messageModel->deviceSerial >> 4) & 0xFF) << 0;
        messageDataVector[2] |= ((messageModel->deviceSerial >> 12) & 0xFF) << 0;
        messageDataVector[3] |= ((messageModel->deviceSerial >> 20) & 0xFF) << 0;
        messageDataVector[4] |= (((messageModel->deviceSerial >> 28) & 0x0F) << 0);
    }

    CanFTP_CanMessage_Init(messageCan
        , CANFTP_MESSAGE_ID_SERVER_PINGRESPONSE
        , 8
        , messageDataVector
    );
}
