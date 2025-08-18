#ifndef CANFTP_SERVER_SESSION_H_
#define CANFTP_SERVER_SESSION_H_

#include "CanFTP_Server_Session_Defines.h"

/*
    Проинициализировать сессию
*/
void CanFTP_Server_Session_Init(CanFTP_Server_Session_t *session, void* server, CanFTP_SessionCode_t sessionCode);
/*
    Удалить сессию
*/
void CanFTP_Server_Session_Dispose(CanFTP_Server_Session_t *session);
/*
    Проинициализировать клиентов, участвующих в сессии
*/
void CanFTP_Server_Session_InitClients(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t clientsCount, CanFTP_Server_Client_t** serverClients);
/*
    Проинициализировать параметры отправляемого файла
*/
void CanFTP_Server_Session_InitFileConfiguration(CanFTP_Server_Session_t *session, CanFTP_PageIndex_t pageIndex, CanFTP_FileLength_t fileLength);
/*
    Проинициализировать новую версию программного обеспечения
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
    Запрос на остановку сессии
*/
void CanFTP_Server_Session_Stop(CanFTP_Server_Session_t *session);
/*
    Запрос на удаление сессии
*/
void CanFTP_Server_Session_Delete(CanFTP_Server_Session_t *session);
/*
    Получить процент завршения работы сессии
*/
float CanFTP_Server_Session_GetCompletingPercent(CanFTP_Server_Session_t *session);
/*
    Проверить, находится ли сессия в активном состоянии
*/
CanFTP_Logical_t CanFTP_Server_Session_CheckIsActive(CanFTP_Server_Session_t *session);
/*
    Проверить, что сессия может быть удалена
*/
CanFTP_Logical_t CanFTP_Server_Session_CheckCanBeDisposed(CanFTP_Server_Session_t *session);
/*
    Получить статус сессии
*/
CanFTP_SessionStatus_t CanFTP_Server_Session_GetStatus(CanFTP_Server_Session_t *session);
/*
    Получить количество клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_GetClientsCount(CanFTP_Server_Session_t *session);
/*
    Получить количество активных клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_GetActiveClientsCount(CanFTP_Server_Session_t *session);
/*
    Получить клиента по индексу
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_GetClientByIndex(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t index);

#endif // CANFTP_SERVER_SESSION_H_
