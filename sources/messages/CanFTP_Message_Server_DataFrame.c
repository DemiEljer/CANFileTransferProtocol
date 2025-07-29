#include "CanFTP_Message_Server_DataFrame.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_DataFrame_Unpack(CanFTP_Message_Server_DataFrame_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_DATAFRAME, 8))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->frameIndex = CanFTP_CanIdentifier_UnpackDataFrameIndex(messageCan->id);
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

    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCodeAndFrameIndex(CANFTP_MESSAGE_ID_SERVER_DATAFRAME, messageModel->sessionCode, messageModel->frameIndex)
        , 8
        , messageDataVector
    );
}
