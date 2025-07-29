#include "CanFTP_Message_Server_SessionControl.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Unpack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, 8))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Server_SessionControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_START)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
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
void CanFTP_Message_Server_SessionControl_Pack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_START)
        {

        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
        {

        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCode(CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, messageModel->sessionCode)
        , 8
        , messageDataVector
    );
}
