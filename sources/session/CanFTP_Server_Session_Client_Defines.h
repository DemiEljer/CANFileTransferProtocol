#ifndef CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_
#define CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_

#include "CanFTP_Session_ClientAssosiation.h"
#include "CanFTP_Session_FileBLock_Defines.h"
#include "CanFTP_Server_Client.h"
#include "stdlib.h"

/*
    Струкутура клиента на стороне сервера
*/
typedef struct _CanFTP_Server_Session_Client
{
    // Клиент сервера
    CanFTP_Server_Client_t* serverClient;
    // Ассоциация клиента и сессии
    CanFTP_Session_ClientAssosiation_t assosiation;

} CanFTP_Server_Session_Client_t;

#endif // CANFTP_SERVER_SESSION_CLIENT_DEFINES_H_
