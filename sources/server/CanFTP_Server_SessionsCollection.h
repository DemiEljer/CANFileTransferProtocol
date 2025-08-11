#ifndef CANFTP_SERVER_SESSIONSCOLLECTION_H_
#define CANFTP_SERVER_SESSIONSCOLLECTION_H_

#include "CanFTP_Server_SessionsCollection_Defines.h"

/*
    Проинициализовать коллекцию сессий
*/
void CanFTP_Server_SessionsCollection_Init(CanFTP_Server_SessionsCollection_t* collection);
/*
    Проверить количество активных сессий
*/
CanFTP_SessionCode_t CanFTP_Server_SessionsCollection_CheckActiveSessions(CanFTP_Server_SessionsCollection_t* collection);
/*
    Вызвать логики сессий
*/
CanFTP_SessionCode_t CanFTP_Server_SessionsCollection_InvokeSessionsOrDispose(CanFTP_Server_SessionsCollection_t* collection);
/*
    Создать экземпляр сессии
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_CreateNewSession(CanFTP_Server_SessionsCollection_t* collection, void* server);
/*
    Получить указатель на сессию по ее коду
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_GetSessionByCode(CanFTP_Server_SessionsCollection_t* collection, CanFTP_SessionCode_t sessionCode);

#endif // CANFTP_SERVER_SESSIONSCOLLECTION_H_
