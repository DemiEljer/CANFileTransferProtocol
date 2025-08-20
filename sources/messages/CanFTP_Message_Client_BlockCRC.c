#include "CanFTP_Message_Client_BlockCRC.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_BlockCRC_Unpack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_BLOCKCRC, CANFTP_MESSAGE_DLC_CLIENT_BLOCKCRC))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);

        uint8_t i = 0;
        for (i = 0; i < CANFTP_CRCELEMENTS_COUNT; i++)
        {
            messageModel->crcElements[i] = messageCan->data[i];
        }

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
void CanFTP_Message_Client_BlockCRC_Pack(CanFTP_Message_Client_BlockCRC_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        uint8_t i = 0;
        for (i = 0; i < CANFTP_CRCELEMENTS_COUNT; i++)
        {
            messageDataVector[i] = messageModel->crcElements[i];
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_BLOCKCRC, messageModel->sessionCode, messageModel->deviceCode)
        , CANFTP_MESSAGE_DLC_CLIENT_BLOCKCRC
        , messageDataVector
    );
}
