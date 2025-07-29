#include "CanFTP_Message_Server_Ping.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_Ping_Unpack(CanFTP_Message_Server_Ping_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_PING, 8))
    {

    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_Ping_Pack(CanFTP_Message_Server_Ping_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {

    }

    CanFTP_CanMessage_Init(messageCan
        , CANFTP_MESSAGE_ID_SERVER_PING
        , 8
        , messageDataVector
    );
}
