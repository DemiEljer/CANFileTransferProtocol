#include "CanFTP_Message_Server_Registration.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_Registration_Unpack(CanFTP_Message_Server_Registration_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_REGISTRATION, CANFTP_MESSAGE_DLC_SERVER_REGISTRATION))
    {
        messageModel->deviceSerial = (CanFTP_DeviceSerial_t)(
              (CanFTP_DeviceSerial_t)(messageCan->data[0]) << 0
            | (CanFTP_DeviceSerial_t)(messageCan->data[1]) << 8
            | (CanFTP_DeviceSerial_t)(messageCan->data[2]) << 16
            | (CanFTP_DeviceSerial_t)(messageCan->data[3]) << 24
        );
        messageModel->sessionCode = (CanFTP_SessionCode_t)(messageCan->data[4]);
        messageModel->deviceCode = (CanFTP_DeviceCode_t)(messageCan->data[5]);

        return CANFTP_TRUE;
    }
    else
    {
        return CANFTP_FALSE;
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_Registration_Pack(CanFTP_Message_Server_Registration_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= ((messageModel->deviceSerial >> 0) & 0xFF) << 0;
        messageDataVector[1] |= ((messageModel->deviceSerial >> 8) & 0xFF) << 0;
        messageDataVector[2] |= ((messageModel->deviceSerial >> 16) & 0xFF) << 0;
        messageDataVector[3] |= ((messageModel->deviceSerial >> 24) & 0xFF) << 0;
        messageDataVector[4] |= messageModel->sessionCode & 0xFF;
        messageDataVector[5] |= messageModel->deviceCode & 0xFF;
    }

    CanFTP_CanMessage_Init(messageCan
        , CANFTP_MESSAGE_ID_SERVER_REGISTRATION
        , CANFTP_MESSAGE_DLC_SERVER_REGISTRATION
        , messageDataVector
    );
}
