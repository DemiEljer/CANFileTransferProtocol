#include "CanFTP_Client_Messages_Handlers.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Ping(void* invoker, CanFTP_Message_Server_Ping_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);
    // Проверка версии протокола
    if (message->protocolVersion == CANFTP_PROTOCOL_VERSION)
    {
        if (*client->state == CANFTP_CLIENTSTATE_IDLE)
        {
            if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_NOTERMINATION)
            {

            }
            else if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_TERMINATE)
            {

            }
            else if (message->terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
            {
                
            }
            // Переход в состояние ответа на запрос Ping
            CanFTP_FinalStateMachine_ChangeState(CanFTP_FinalStateMachine_Cast(client), CANFTP_CLIENTSTATE_PING_RESPONSING);
        }
        else
        {
            // Ничего не делаем
        }
    }
}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_PingResponseAck(void* invoker, CanFTP_Message_Server_PingResponseAck_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_Registration(void* invoker, CanFTP_Message_Server_Registration_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Server_SessionControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Server_BlockControl_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageRecieve_DataFrame(void* invoker, CanFTP_Message_Server_DataFrame_t* message)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(invoker);


}
/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Client_MessageSend_PingResponse(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_PingResponse_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_PingResponse_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Client_MessageSend_SessionControl(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_SessionControl_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_SessionControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Client_MessageSend_BlockControl(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_BlockControl_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_BlockControl_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Client_MessageSend_SubBlocksStatuses(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_SubBlocksStatuses_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_SubBlocksStatuses_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Client_MessageSend_BlockCRC(CanFTP_Client_t* client)
{
    CanFTP_Message_Client_BlockCRC_t messageModel;
    // Обработка сообщения
    {

    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Client_BlockCRC_Pack(&(messageModel), &(messageCan));
        CanFTP_Client_MessageSend(client, &(messageCan));
    }
}
/*
    Отправить сообщение
*/
void CanFTP_Client_MessageSend(CanFTP_Client_t* client, CanFTP_CanMessage_t* message)
{
    if (client->callbacks.sendMessageCallback != 0)
    {
        client->callbacks.sendMessageCallback(message);
    }
}
