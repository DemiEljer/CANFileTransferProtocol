#ifndef CANFTP_SERVER_SESSION_H_
#define CANFTP_SERVER_SESSION_H_

#include "CanFTP_Server_Session_Defines.h"

/*
    Проинициализовать сессию
*/
void CanFTP_Server_Session_Init(CanFTP_Server_Session_t *session, void* server, CanFTP_SessionCode_t sessionCode);
/*
    Удалить сессию
*/
void CanFTP_Server_Session_Dispose(CanFTP_Server_Session_t *session);
/*
    Проициализовать клиентов, участвующих в сессии
*/
void CanFTP_Server_Session_InitClients(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t clientsCount, CanFTP_Server_Client_t** serverClients);
/*
    Проициализовать параметры отправляемого файла
*/
void CanFTP_Server_Session_InitFileConfiguration(CanFTP_Server_Session_t *session, CanFTP_PageIndex_t pageIndex, CanFTP_FileLength_t fileLength);
/*
    Проициализовать новую версию программного обеспечения
*/
void CanFTP_Server_Session_InitNewSoftVersion(CanFTP_Server_Session_t *session, CanFTP_SoftwareVersion_t* newSoftVersion);
/*
    Вызов логики сессии
*/
void CanFTP_Server_Session_Invoke(CanFTP_Server_Session_t *session);
/*
    Запрос на запуск сессии
*/
void CanFTP_Server_Session_Start(CanFTP_Server_Session_t *session);
/*
    Запрос на остановка сессии
*/
void CanFTP_Server_Session_Stop(CanFTP_Server_Session_t *session);
/*
    Запрос на удаление сессии
*/
void CanFTP_Server_Session_Delete(CanFTP_Server_Session_t *session);

#endif // CANFTP_SERVER_SESSION_H_
