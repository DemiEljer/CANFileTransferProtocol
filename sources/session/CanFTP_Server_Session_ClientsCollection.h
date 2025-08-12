#ifndef CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_
#define CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_

#include "CanFTP_Server_Session_Client.h"

/*
    Структура коллекции клиентов сессии на стороне сервера
*/
typedef struct _CanFTP_Server_Session_ClientsCollection
{
    // Количество клиентов сессии
    CanFTP_DeviceCode_t clientsCount;
    // Массив клиентов сесси
    CanFTP_Server_Session_Client_t* clients;

} CanFTP_Server_Session_ClientsCollection_t;

/*
    Инициализация колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Init(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Удаление колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Dispose(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Инициализация клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_InitClients(CanFTP_Server_Session_ClientsCollection_t* collection
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Количество клиентов
    , CanFTP_DeviceCode_t clientsCount
    // Массив указателей на клиентов сессии
    , CanFTP_Server_Client_t** serverClients);
/*
    Получить клиента по индексу
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_GetCount(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Получить клиента по индексу
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_ClientsCollection_GetClientByIndex(CanFTP_Server_Session_ClientsCollection_t* collection, CanFTP_DeviceCode_t index);
/*
    Подготовить клиентов перед запуском сессии
*/
void CanFTP_Server_Session_ClientsCollection_Prepare(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Обновить параметры отпавки сообщений
*/
void CanFTP_Server_Session_ClientsCollection_UpdateSendingParams(CanFTP_Server_Session_ClientsCollection_t *collection
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount);
/*
    Проверить клиентов на предмет выполнения условия нахождения в сессии
*/
void CanFTP_Server_Session_ClientsCollection_Check(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что остались не удаленные клиенты
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckIsNotDisposedLeft(CanFTP_Server_Session_ClientsCollection_t* collection);
/*
    Проврить, что все клиенты были зарегистрированы
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsRegistration(CanFTP_Server_Session_ClientsCollection_t* collection);

#endif // CANFTP_SERVER_SESSION_CLIENTSCOLLECTION_H_
