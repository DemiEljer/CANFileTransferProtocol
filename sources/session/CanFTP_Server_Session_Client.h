#ifndef CANFTP_SERVER_SESSION_CLIENT_H_
#define CANFTP_SERVER_SESSION_CLIENT_H_

#include "CanFTP_Server_Session_Client_Defines.h"

/*
    Инициализация клиента
*/
void CanFTP_Server_Session_Client_Init(CanFTP_Server_Session_Client_t *client
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Клиент на стороне сервера
    , CanFTP_Server_Client_t* serverClient
    // Код клиента
    , CanFTP_DeviceCode_t clientCode);
/*
    Удаление клиента
*/
void CanFTP_Server_Session_Client_Dispose(CanFTP_Server_Session_Client_t *client);
/*
    Проверить, что клиент активно участвует в сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_IsInSession(CanFTP_Server_Session_Client_t *client);

#endif // CANFTP_SERVER_SESSION_CLIENT_H_
