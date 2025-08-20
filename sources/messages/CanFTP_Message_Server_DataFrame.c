#include "CanFTP_Message_Server_DataFrame.h"

/*
    Распаковка сообщения
*/
CanFTP_Logical_t CanFTP_Message_Server_DataFrame_Unpack(CanFTP_Message_Server_DataFrame_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_DATAFRAME, CANFTP_MESSAGE_DLC_SERVER_DATAFRAME))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->frameIndex = CanFTP_CanIdentifier_UnpackDataFrameIndex(messageCan->id);

        uint8_t i = 0;
        for (i = 0; i < CANFTP_DATAFRAME_BYTESCOUNT; i++)
        {
            messageModel->data[i] = messageCan->data[i];
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
void CanFTP_Message_Server_DataFrame_Pack(CanFTP_Message_Server_DataFrame_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        uint8_t i = 0;
        for (i = 0; i < CANFTP_DATAFRAME_BYTESCOUNT; i++)
        {
            messageDataVector[i] = messageModel->data[i];
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndFrameIndex(CANFTP_MESSAGE_ID_SERVER_DATAFRAME, messageModel->sessionCode, messageModel->frameIndex)
        , CANFTP_MESSAGE_DLC_SERVER_DATAFRAME
        , messageDataVector
    );
}
