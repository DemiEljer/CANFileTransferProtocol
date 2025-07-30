#include "CanFTP_Message_Server_Ping.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_Ping_Unpack(CanFTP_Message_Server_Ping_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_PING, 8))
    {
        messageModel->protocolVersion = (CanFTP_ProtocolVersion_t)(
              (CanFTP_ProtocolVersion_t)(messageCan->data[0]) << 0 
            | (CanFTP_ProtocolVersion_t)(messageCan->data[1]) << 8
        );
        messageModel->terminationRequest = (CanFTP_TerminationRequest_t)(messageCan->data[2] & 0x03);
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
        messageDataVector[0] |= ((messageModel->protocolVersion >> 0) & 0xFF) << 0;
        messageDataVector[1] |= ((messageModel->protocolVersion >> 8) & 0xFF) << 0;
        messageDataVector[2] |= ((messageModel->terminationRequest >> 0) & 0x03) << 0;
    }

    CanFTP_CanMessage_Init(messageCan
        , CANFTP_MESSAGE_ID_SERVER_PING
        , 8
        , messageDataVector
    );
}
