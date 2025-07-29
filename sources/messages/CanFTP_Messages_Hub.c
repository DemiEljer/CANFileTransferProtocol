#include "CanFTP_Messages_Hub.h"

/*
    Обработка логики вызова обратных связей по приему сообщений
*/
void CanFTP_Messages_Hub_RecieveMessage(CanFTP_Messages_Hub_t* hub
    , CanFTP_CanMessage_t *canMessage
    , void* invoker
)
{
    if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_PING))
    {
        if (hub->serverPingCallback != 0)
        {
            CanFTP_Message_Server_Ping_t message;
            CanFTP_Message_Server_Ping_Unpack(&(message), canMessage);
            hub->serverPingCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_PINGRESPONSE))
    {
        if (hub->serverPingResponseAckCallback != 0)
        {
            CanFTP_Message_Server_PingResponseAck_t message;
            CanFTP_Message_Server_PingResponseAck_Unpack(&(message), canMessage);
            hub->serverPingResponseAckCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_REGISTRATION))
    {
        if (hub->serverRegistrationCallback != 0)
        {
            CanFTP_Message_Server_Registration_t message;
            CanFTP_Message_Server_Registration_Unpack(&(message), canMessage);
            hub->serverRegistrationCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL))
    {
        if (hub->serverSessionControlCallback != 0)
        {
            CanFTP_Message_Server_SessionControl_t message;
            CanFTP_Message_Server_SessionControl_Unpack(&(message), canMessage);
            hub->serverSessionControlCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_BLOCKCONTROL))
    {
        if (hub->serverBlockControlCallback != 0)
        {
            CanFTP_Message_Server_BlockControl_t message;
            CanFTP_Message_Server_BlockControl_Unpack(&(message), canMessage);
            hub->serverBlockControlCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_SERVER_DATAFRAME))
    {
        if (hub->serverDataFrameCallback != 0)
        {
            CanFTP_Message_Server_DataFrame_t message;
            CanFTP_Message_Server_DataFrame_Unpack(&(message), canMessage);
            hub->serverDataFrameCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_CLIENT_PINGRESPONSE))
    {
        if (hub->clientPingResponseCallback != 0)
        {
            CanFTP_Message_Client_PingResponse_t message;
            CanFTP_Message_Client_PingResponse_Unpack(&(message), canMessage);
            hub->clientPingResponseCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_CLIENT_SESSIONCONTROL))
    {
        if (hub->clientSessionControlCallback != 0)
        {
            CanFTP_Message_Client_SessionControl_t message;
            CanFTP_Message_Client_SessionControl_Unpack(&(message), canMessage);
            hub->clientSessionControlCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_CLIENT_BLOCKCONTROL))
    {
        if (hub->clientBlockControlCallback != 0)
        {
            CanFTP_Message_Client_BlockControl_t message;
            CanFTP_Message_Client_BlockControl_Unpack(&(message), canMessage);
            hub->clientBlockControlCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_CLIENT_SUBBLOCKSSTATUSES))
    {
        if (hub->clientSubBlocksStatusesCallback != 0)
        {
            CanFTP_Message_Client_SubBlocksStatuses_t message;
            CanFTP_Message_Client_SubBlocksStatuses_Unpack(&(message), canMessage);
            hub->clientSubBlocksStatusesCallback(invoker, &(message));
        }
    }
    else if (CanFTP_CanMessage_CheckMessageCodification(canMessage, CANFTP_MESSAGE_ID_CLIENT_BLOCKCRC))
    {
        if (hub->clientBlockCRCCallback != 0)
        {
            CanFTP_Message_Client_BlockCRC_t message;
            CanFTP_Message_Client_BlockCRC_Unpack(&(message), canMessage);
            hub->clientBlockCRCCallback(invoker, &(message));
        }
    }
}
