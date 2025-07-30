#include "CanFTP_Message_Client_SessionControl.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Client_SessionControl_Unpack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL, 1))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->deviceCode = CanFTP_CanIdentifier_UnpackDeviceCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Client_SessionControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {
            messageModel->registrationAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {
            messageModel->configurationAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {
            messageModel->startSessionAck.status = (CanFTP_ClientSessionAckStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {
            messageModel->finishSessionAck.status = (CanFTP_ClientSessionFinishStatus_t)((messageCan->data[0] >> 4) & 0x0F); 
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
void CanFTP_Message_Client_SessionControl_Pack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {
            messageDataVector[0] |= ((messageModel->registrationAck.status >> 0) & 0x0F) << 4;
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {
            messageDataVector[0] |= ((messageModel->configurationAck.status >> 0) & 0x0F) << 4;
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {
            messageDataVector[0] |= ((messageModel->startSessionAck.status >> 0) & 0x0F) << 4;
        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {
            messageDataVector[0] |= ((messageModel->finishSessionAck.status >> 0) & 0x0F) << 4;
        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL, messageModel->sessionCode, messageModel->deviceCode)
        , 1
        , messageDataVector
    );
}
