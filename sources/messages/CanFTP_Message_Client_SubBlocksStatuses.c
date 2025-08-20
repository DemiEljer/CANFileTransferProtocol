#include "CanFTP_Message_Client_SubBlocksStatuses.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Client_SubBlocksStatuses_Unpack(CanFTP_Message_Client_SubBlocksStatuses_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_SUBBLOCKSSTATUSES, CANFTP_MESSAGE_DLC_CLIENT_SUBBLOCKSSTATUSES))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);

        uint8_t i = 0;
        for (i = 0; i < CANFTP_SUBBLOCKS_COUNT; i++)
        {
            messageModel->subblocksReciecedFlags[i] = (CanFTP_Logical_t)((messageCan->data[i / 8] >> (i % 8)) & 0x01);
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
void CanFTP_Message_Client_SubBlocksStatuses_Pack(CanFTP_Message_Client_SubBlocksStatuses_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        uint8_t i = 0;
        for (i = 0; i < CANFTP_SUBBLOCKS_COUNT; i++)
        {
            messageDataVector[i / 8] |=  (messageModel->subblocksReciecedFlags[i] & 0x01) << (i % 8);
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_SUBBLOCKSSTATUSES, messageModel->sessionCode, messageModel->deviceCode)
        , CANFTP_MESSAGE_DLC_CLIENT_SUBBLOCKSSTATUSES
        , messageDataVector
    );
}
