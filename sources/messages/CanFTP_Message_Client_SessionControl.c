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

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
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
void CanFTP_Message_Client_SessionControl_Pack(CanFTP_Message_Client_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_REGISTRATIONACK)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_CONFIGURATIONACK)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_STARTSESSIONACK)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_CLIENT_SESSIONCONTROL_FINISHSESSIONACK)
        {

        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndDeviceCode(CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL, messageModel->sessionCode, messageModel->deviceCode )
        , 1
        , messageDataVector
    );
}
