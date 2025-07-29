#include "CanFTP_Message_Server_PingResponseAck.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_PingResponseAck_Unpack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_PINGRESPONSE, 8))
    {

    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_PingResponseAck_Pack(CanFTP_Message_Server_PingResponseAck_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {

    }

    CanFTP_CanMessage_Init(messageCan
        , CANFTP_MESSAGE_ID_SERVER_PINGRESPONSE
        , 8
        , messageDataVector
    );
}
