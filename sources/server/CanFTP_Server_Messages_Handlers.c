#include "CanFTP_Server_Messages_Handlers.h"
#include "CanFTP_Server_Session_Messages_Handlers.h"

/*
    Обработчик приема сообщения PingResponse
*/
void CanFTP_Server_MessageRecieve_PingResponse(void* invoker, CanFTP_Message_Client_PingResponse_t* message)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(invoker);

    if (CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_PING)
    {
        if (message->messageType == CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE1)
        {
            CanFTP_Server_Client_t* client = CanFTP_Server_ClientsCollection_GetBySerial(&(server->clients), message->response1.deviceSerial);
            if (client == CANFTP_NULL)
            {
                client = CanFTP_Server_ClientsCollection_Append(&(server->clients));

                CanFTP_Server_Client_Reset(client);
            }
            // Флаг, что клиент уже был сконфигурирован
            CanFTP_Logical_t clientConfigurationIsFinished = CanFTP_Server_Client_IsConfigured(client);
            
            // Подтверждление получения сообщения конфигурации клиента
            client->configurationMessagesAck[0] = CANFTP_TRUE;
            // Заполнение конфигурируемых полей
            client->configuration.serialNumber = message->response1.deviceSerial;
            client->configuration.identifier = message->response1.deviceIdentifier;
            client->configuration.type = message->response1.deviceType;
            // Отправка сообщения подтверждения конфигурации
            {
                // Назначение параметров ответа
                server->agents.pingController.responsingDeviceSerial = message->response1.deviceSerial;
                server->agents.pingController.responsingMessageType = CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE1;

                CanFTP_Server_MessageSend_PingResponseAck(server);
            }
            // Проверка условия вызова нахождения клиента
            if (!clientConfigurationIsFinished
                && CanFTP_Server_Client_IsConfigured(client))
            {
                if (server->callbacks.clientFoundCallback != CANFTP_NULL)
                {
                    server->callbacks.clientFoundCallback(server, client);
                }
            }
        }
        else if (message->messageType == CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE2)
        {
            CanFTP_Server_Client_t* client = CanFTP_Server_ClientsCollection_GetBySerial(&(server->clients), message->response2.deviceSerial);
            if (client == CANFTP_NULL)
            {
                client = CanFTP_Server_ClientsCollection_Append(&(server->clients));

                CanFTP_Server_Client_Reset(client);
            }
            // Флаг, что клиент уже был сконфигурирован
            CanFTP_Logical_t clientConfigurationIsFinished = CanFTP_Server_Client_IsConfigured(client);

            // Подтверждление получения сообщения конфигурации клиента
            client->configurationMessagesAck[1] = CANFTP_TRUE;
            // Заполнение конфигурируемых полей
            client->configuration.serialNumber = message->response2.deviceSerial;
            CanFTP_SoftwareVersion_Copy(&(client->configuration.softVersion), &(message->response2.deviceSoftVersion));
            // Отправка сообщения подтверждения конфигурации
            {
                // Назначение параметров ответа
                server->agents.pingController.responsingDeviceSerial = message->response2.deviceSerial;
                server->agents.pingController.responsingMessageType = CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE2;

                CanFTP_Server_MessageSend_PingResponseAck(server);
            }
            // Проверка условия вызова нахождения клиента
            if (!clientConfigurationIsFinished
                && CanFTP_Server_Client_IsConfigured(client))
            {
                if (server->callbacks.clientFoundCallback != CANFTP_NULL)
                {
                    server->callbacks.clientFoundCallback(server, client);
                }
            }
        }
    }
}
/*
    Обработчик приема сообщения SessionControl
*/
void CanFTP_Server_MessageRecieve_SessionControl(void* invoker, CanFTP_Message_Client_SessionControl_t* message)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(invoker);

    if (CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_SESSION)
    {
        CanFTP_Server_Session_t* session = CanFTP_Server_SessionsCollection_GetSessionByCode(&(server->sessions), message->sessionCode);

        if (session != CANFTP_NULL)
        {
            CanFTP_Server_Session_MessageRecieve_SessionControl(session, message);
        }
    }
}
/*
    Обработчик приема сообщения BlockControl
*/
void CanFTP_Server_MessageRecieve_BlockControl(void* invoker, CanFTP_Message_Client_BlockControl_t* message)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(invoker);

    if (CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_SESSION)
    {
        CanFTP_Server_Session_t* session = CanFTP_Server_SessionsCollection_GetSessionByCode(&(server->sessions), message->sessionCode);

        if (session != CANFTP_NULL)
        {
            CanFTP_Server_Session_MessageRecieve_BlockControl(session, message);
        }
    } 
}
/*
    Обработчик приема сообщения SubBlocksStatuses
*/
void CanFTP_Server_MessageRecieve_SubBlocksStatuses(void* invoker, CanFTP_Message_Client_SubBlocksStatuses_t* message)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(invoker);

    if (CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_SESSION)
    {
        CanFTP_Server_Session_t* session = CanFTP_Server_SessionsCollection_GetSessionByCode(&(server->sessions), message->sessionCode);

        if (session != CANFTP_NULL)
        {
            CanFTP_Server_Session_MessageRecieve_SubBlocksStatuses(session, message);
        }
    }
}
/*
    Обработчик приема сообщения BlockCRC
*/
void CanFTP_Server_MessageRecieve_BlockCRC(void* invoker, CanFTP_Message_Client_BlockCRC_t* message)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(invoker);

    if (CanFTP_Server_GetState(server) == CANFTP_SERVERSTATE_SESSION)
    {
        CanFTP_Server_Session_t* session = CanFTP_Server_SessionsCollection_GetSessionByCode(&(server->sessions), message->sessionCode);

        if (session != CANFTP_NULL)
        {
            CanFTP_Server_Session_MessageRecieve_BlockCRC(session, message);
        }
    }
}

/*
    Обработчик отправки сообщения Ping
*/
void CanFTP_Server_MessageSend_Ping(CanFTP_Server_t* server)
{
    CanFTP_Message_Server_Ping_t messageModel;
    // Обработка сообщения
    {
        messageModel.protocolVersion = CANFTP_PROTOCOL_VERSION;
        messageModel.terminationRequest = server->agents.pingController.requsts.terminationRequest;
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_Ping_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_MessageSend(server, &(messageCan));
    }
}
/*
    Обработчик отправки сообщения PingResponseAck
*/
void CanFTP_Server_MessageSend_PingResponseAck(CanFTP_Server_t* server)
{
    CanFTP_Message_Server_PingResponseAck_t messageModel;
    // Обработка сообщения
    {
        messageModel.deviceSerial = server->agents.pingController.responsingDeviceSerial;
        messageModel.responseType = server->agents.pingController.responsingMessageType;
    }
    // Упаковка сообщения и отправка
    {
        CanFTP_CanMessage_t messageCan;
        CanFTP_Message_Server_PingResponseAck_Pack(&(messageModel), &(messageCan));
        CanFTP_Server_MessageSend(server, &(messageCan));
    }
}
/*
    Отправить сообщение
*/
void CanFTP_Server_MessageSend(CanFTP_Server_t* server, CanFTP_CanMessage_t* message)
{
    if (server->callbacks.sendMessageCallback != CANFTP_NULL)
    {
        server->callbacks.sendMessageCallback(server, message);
    }
}
