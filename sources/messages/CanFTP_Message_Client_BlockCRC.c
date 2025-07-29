#include "CanFTP_Message_Client_BlockCRC.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_BlockCRC_Unpack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_BLOCKCRC, 8))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Client_BlockCRC_Pack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {

    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_BLOCKCRC, messageModel->sessionCode, messageModel->deviceCode )
        , 8
        , messageDataVector
    );
}
