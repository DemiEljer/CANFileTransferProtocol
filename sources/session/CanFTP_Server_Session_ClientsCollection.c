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
