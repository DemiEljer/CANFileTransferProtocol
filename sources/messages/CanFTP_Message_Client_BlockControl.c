#include "CanFTP_Message_Client_BlockControl.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_BlockControl_Unpack(CanFTP_Message_Client_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_BLOCKCONTROL, CANFTP_MESSAGE_DLC_CLIENT_BLOCKCONTROL))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Client_BlockControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_FINISH)
        {
            messageModel->finishBlockAck.blockHandlingStatus = (CanFTP_ClientBlockHandlingStatus_t)((messageCan->data[0] >> 4) & 0x0F);
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
void CanFTP_Message_Client_BlockControl_Pack(CanFTP_Message_Client_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_CLIENT_BLOCKCONTROL_FINISH)
        {
            messageDataVector[0] |= (messageModel->finishBlockAck.blockHandlingStatus & 0x0F) << 4;
        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_BLOCKCONTROL, messageModel->sessionCode, messageModel->deviceCode)
        , CANFTP_MESSAGE_DLC_CLIENT_BLOCKCONTROL
        , messageDataVector
    );
}
