#ifndef CANFTP_SERVER_SESSIONSCOLLECTION_DEFINES_H_
#define CANFTP_SERVER_SESSIONSCOLLECTION_DEFINES_H_

#include "CanFTP_Server_Params.h"
#include "CanFTP_Server_Session.h"

/*
    Структура коллекции сессий на стороне сервера
*/
typedef struct _CanFTP_Server_SessionsCollection
{
    // Массив указателей на активные сессии
    CanFTP_Server_Session_t* sessions[CANFTP_SERVER_SESSIONS_MAXCOUNT];
    // Количество активных сессий
    CanFTP_SessionCode_t activeSessionsCount;

} CanFTP_Server_SessionsCollection_t;

#endif // CANFTP_SERVER_SESSIONSCOLLECTION_DEFINES_H_
