#include "CanFTP_Message_Client_PingResponse.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_PingResponse_Unpack(CanFTP_Message_Client_PingResponse_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_PINGRESPONSE, 8))
    {
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceSerialCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Client_PingResponse_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE1)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE2)
        {

        }
        else
        {
            CanFTP_ThrowError();
        }
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_PingResponse_Pack(CanFTP_Message_Client_PingResponse_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE1)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE2)
        {

        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSerialDeviceCode(CANFTP_MESSAGE_ID_CLIENT_PINGRESPONSE, messageModel->deviceCode)
        , 8
        , messageDataVector
    );
}
