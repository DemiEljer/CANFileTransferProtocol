#include "CanFTP_Message_Client_PingResponse.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_PingResponse_Unpack(CanFTP_Message_Client_PingResponse_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_PINGRESPONSE, CANFTP_MESSAGE_DLC_CLIENT_PINGRESPONSE))
    {
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceSerialCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Client_PingResponse_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE1)
        {
            messageModel->response1.deviceSerial = (CanFTP_DeviceSerial_t)(
                  (CanFTP_DeviceSerial_t)((messageCan->data[0] >> 4) & 0x0F) 
                | (CanFTP_DeviceSerial_t)((messageCan->data[1] >> 0) & 0xFF) << 4
                | (CanFTP_DeviceSerial_t)((messageCan->data[2] >> 0) & 0xFF) << 12
                | (CanFTP_DeviceSerial_t)((messageCan->data[3] >> 0) & 0xFF) << 20
                | (CanFTP_DeviceSerial_t)((messageCan->data[4] >> 0) & 0x0F) << 28
            );
            messageModel->response1.deviceIdentifier = (CanFTP_DeviceIdentifier_t)(
                  (CanFTP_DeviceIdentifier_t)((messageCan->data[4] >> 4) & 0x0F) 
                | (CanFTP_DeviceIdentifier_t)((messageCan->data[5] >> 0) & 0x0F) << 4
            );
            messageModel->response1.deviceType = (CanFTP_DeviceType_t)(
                  (CanFTP_DeviceType_t)((messageCan->data[5] >> 4) & 0x0F) 
                | (CanFTP_DeviceType_t)((messageCan->data[6] >> 0) & 0xFF) << 4
                | (CanFTP_DeviceType_t)((messageCan->data[7] >> 0) & 0x0F) << 12
            );
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE2)
        {
            messageModel->response2.deviceSerial = (CanFTP_DeviceSerial_t)(
                  (CanFTP_DeviceSerial_t)((messageCan->data[0] >> 4) & 0x0F) 
                | (CanFTP_DeviceSerial_t)((messageCan->data[1] >> 0) & 0xFF) << 4
                | (CanFTP_DeviceSerial_t)((messageCan->data[2] >> 0) & 0xFF) << 12
                | (CanFTP_DeviceSerial_t)((messageCan->data[3] >> 0) & 0xFF) << 20
                | (CanFTP_DeviceSerial_t)((messageCan->data[4] >> 0) & 0x0F) << 28
            );
            messageModel->response2.deviceSoftVersion.lowerPart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[4] >> 4) & 0x0F) 
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[5] >> 0) & 0x0F) << 4
            );
            messageModel->response2.deviceSoftVersion.middlePart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[5] >> 4) & 0x0F) 
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[6] >> 0) & 0x0F) << 4
            );
            messageModel->response2.deviceSoftVersion.higherPart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[6] >> 4) & 0x0F) 
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[7] >> 0) & 0x0F) << 4
            );
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
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE1)
        {
            messageDataVector[0] |= ((messageModel->response1.deviceSerial >> 0) & 0x0F) << 4;
            messageDataVector[1] |= ((messageModel->response1.deviceSerial >> 4) & 0xFF) << 0;
            messageDataVector[2] |= ((messageModel->response1.deviceSerial >> 12) & 0xFF) << 0;
            messageDataVector[3] |= ((messageModel->response1.deviceSerial >> 20) & 0xFF) << 0;
            messageDataVector[4] |= (((messageModel->response1.deviceSerial >> 28) & 0x0F) << 0) 
                                    | (((messageModel->response1.deviceIdentifier >> 0) & 0x0F) << 4);
            messageDataVector[5] |= (((messageModel->response1.deviceIdentifier >> 4) & 0x0F) << 0)
                                    | (((messageModel->response1.deviceType >> 0) & 0x0F) << 4);
            messageDataVector[6] |= ((messageModel->response1.deviceType >> 4) & 0xFF) << 0;
            messageDataVector[7] |= ((messageModel->response1.deviceType >> 12) & 0x0F) << 0;                        
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_BLOCKCONTROL_RESPONSE2)
        {
            messageDataVector[0] |= ((messageModel->response2.deviceSerial >> 0) & 0x0F) << 4;
            messageDataVector[1] |= ((messageModel->response2.deviceSerial >> 4) & 0xFF) << 0;
            messageDataVector[2] |= ((messageModel->response2.deviceSerial >> 12) & 0xFF) << 0;
            messageDataVector[3] |= ((messageModel->response2.deviceSerial >> 20) & 0xFF) << 0;
            messageDataVector[4] |= (((messageModel->response2.deviceSerial >> 28) & 0x0F) << 0) 
                                    | (((messageModel->response2.deviceSoftVersion.lowerPart >> 0) & 0x0F) << 4);
            messageDataVector[5] |= (((messageModel->response2.deviceSoftVersion.lowerPart >> 4) & 0x0F) << 0)
                                    | (((messageModel->response2.deviceSoftVersion.middlePart >> 0) & 0x0F) << 4);
            messageDataVector[6] |= (((messageModel->response2.deviceSoftVersion.middlePart >> 4) & 0x0F) << 0)
                                    | (((messageModel->response2.deviceSoftVersion.higherPart >> 0) & 0x0F) << 4);
            messageDataVector[7] |= (((messageModel->response2.deviceSoftVersion.higherPart >> 4) & 0x0F) << 0);
        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSerialDeviceCode(CANFTP_MESSAGE_ID_CLIENT_PINGRESPONSE, messageModel->deviceCode)
        , CANFTP_MESSAGE_DLC_CLIENT_PINGRESPONSE
        , messageDataVector
    );
}
