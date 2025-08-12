#include "CanFTP_Server_Session_ClientsCollection.h"

/*
    Инициализация колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Init(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    collection->clientsCount = 0;
    collection->clients = CANFTP_NULL;
}
/*
    Удаление колекции клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_Dispose(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    if (collection->clientsCount > 0)
    {
        CanFTP_DeviceCode_t clientIndex = 0;
        // Удаление клиентов
        for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
        {
            CanFTP_Server_Session_Client_Dispose(&(collection->clients[clientIndex]));
        }

        free(collection->clients);
        // Обнуление полей
        collection->clientsCount = 0;
        collection->clients = CANFTP_NULL;
    }
}
/*
    Инициализация клиентов сессии
*/
void CanFTP_Server_Session_ClientsCollection_InitClients(CanFTP_Server_Session_ClientsCollection_t* collection
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Количество клиентов
    , CanFTP_DeviceCode_t clientsCount
    // Массив указателей на клиентов сессии
    , CanFTP_Server_Client_t** serverClients)
{
    collection->clientsCount = clientsCount;
    // Выделение памяти для клиентов
    collection->clients = malloc(sizeof(CanFTP_Server_Session_Client_t) * collection->clientsCount);

    CanFTP_DeviceCode_t clientIndex = 0;
    // Инициализация клиентов
    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        CanFTP_Server_Session_Client_Init(&(collection->clients[clientIndex])
            , sessionCode
            , serverClients[clientIndex]
            , clientIndex);
    }
}
/*
    Получить клиента по индексу
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_GetCount(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    return collection->clientsCount;
}
/*
    Получить клиента по индексу
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_ClientsCollection_GetClientByIndex(CanFTP_Server_Session_ClientsCollection_t* collection, CanFTP_DeviceCode_t index)
{
    if (index < collection->clientsCount)
    {
        return &(collection->clients[index]);
    }
    else
    {
        CanFTP_ThrowError();
    }
}
/*
    Подготовить клиентов перед запуском сессии
*/
void CanFTP_Server_Session_ClientsCollection_Prepare(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        CanFTP_Server_Session_Client_Prepare(&(collection->clients[clientIndex]));
    }
}
/*
    Обновить параметры отпавки сообщений
*/
void CanFTP_Server_Session_ClientsCollection_UpdateSendingParams(CanFTP_Server_Session_ClientsCollection_t *collection
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        CanFTP_Server_Session_Client_UpdateSendingParams(&(collection->clients[clientIndex]), interval, maxCount);
    }
}
/*
    Проверить клиентов на предмет выполнения условия нахождения в сессии
*/
void CanFTP_Server_Session_ClientsCollection_Check(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        if (!CanFTP_Server_Session_Client_Check(&(collection->clients[clientIndex])))
        {
            CanFTP_Server_Session_Client_Dispose(&(collection->clients[clientIndex]));
        }
    }
}
/*
    Проврить, что остались не удаленные клиенты
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckIsNotDisposedLeft(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        if (CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            return CANFTP_TRUE;
        }
    }

    return CANFTP_FALSE;
}
/*
    Проврить, что все клиенты были зарегистрированы
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsRegistration(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t registratedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isRegistrated != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_REGISTRATIONFAIL);
        }
        else
        {
            registratedClientsCount++;
        }
    }

    return registratedClientsCount > 0;
}
