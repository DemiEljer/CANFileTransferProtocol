#include "CanFTP_Server_Session_Client.h"

/*
    Инициализация клиента
*/
void CanFTP_Server_Session_Client_Init(CanFTP_Server_Session_Client_t *client
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Клиент на стороне сервера
    , CanFTP_Server_Client_t* serverClient
    // Код клиента
    , CanFTP_DeviceCode_t clientCode)
{
    client->assosiation.sessionCode = sessionCode;
    client->assosiation.deviceCode = clientCode;
    // Связывание с клиентом на стороне сервера
    if (serverClient != CANFTP_NULL)
    {
        client->serverClient = serverClient;
        client->serverClient->isInSession = CANFTP_TRUE;
    }
}
/*
    Удаление клиента
*/
void CanFTP_Server_Session_Client_Dispose(CanFTP_Server_Session_Client_t *client)
{
    if (CanFTP_Server_Session_Client_IsInSession(client))
    {
        client->serverClient->isInSession = CANFTP_FALSE;
        client->serverClient = CANFTP_NULL;
    }
}
/*
    Проверить, что клиент активно участвует в сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_IsInSession(CanFTP_Server_Session_Client_t *client)
{
    return client->serverClient != CANFTP_NULL;
}
