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
        if (serverClients[clientIndex] == CANFTP_NULL)
        {
            CanFTP_ThrowError();
        }
        else
        {
            CanFTP_Server_Session_Client_Init(&(collection->clients[clientIndex])
                , sessionCode
                , serverClients[clientIndex]
                , clientIndex);
        }
    }
}
/*
    Найти обобщенную версию программного обеспечения
*/    
void CanFTP_Server_Session_ClientsCollection_GetSoftVewrsion(CanFTP_Server_Session_ClientsCollection_t* collection, CanFTP_SoftwareVersion_t *softVersion)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        CanFTP_SoftwareVersion_CopyIfBigger(softVersion, &(collection->clients[clientIndex].serverClient->configuration.softVersion));
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

        return CANFTP_NULL;
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
    Получить количество ну удаленных клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_ClientsCollection_GetNotDisposedCount(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t notDisposedCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        if (CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            notDisposedCount++;
        }
    }

    return notDisposedCount;
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
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsRegistrationAndDelete(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t registratedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isRegistrated != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_REGISTRATIONFAILED);
        }
        else
        {
            registratedClientsCount++;
        }
    }

    return registratedClientsCount > 0;
}
/*
    Проврить, что все клиенты были сконфигурированы
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsConfiguration(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t configuratedClientsCount = 0;
    CanFTP_DeviceCode_t disposedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isConfigurated == CANFTP_TRUE)
        {
            configuratedClientsCount++;
        }
        else if (!CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            disposedClientsCount++;
        }
    }

    return (configuratedClientsCount + disposedClientsCount) == collection->clientsCount
            && configuratedClientsCount > 0;
}
/*
    Удалить всех клиентов, не прошедших конфигурацию 
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnconfugured(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isConfigurated != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_CONFIGURATIONFAILED);
        }
    }
}
/*
    Проврить, что все клиенты готовы к началу сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsSessionStarted(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t startedClientsCount = 0;
    CanFTP_DeviceCode_t disposedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.sessionIsStarted == CANFTP_TRUE)
        {
            startedClientsCount++;
        }
        else if (!CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            disposedClientsCount++;
        }
    }

    return (startedClientsCount + disposedClientsCount) == collection->clientsCount
            && startedClientsCount > 0;
}
/*
    Удалить всех клиентов, не начавших сессию
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnstarted(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.sessionIsStarted != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_SESSIONSTARTINGFAILED);
        }
    }
}
/*
    Проврить, что все клиенты завершили сессию
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsSessionFinished(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t finishedClientsCount = 0;
    CanFTP_DeviceCode_t disposedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.sessionIsFinished == CANFTP_TRUE)
        {
            finishedClientsCount++;
        }
        else if (!CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            disposedClientsCount++;
        }
    }

    return (finishedClientsCount + disposedClientsCount) == collection->clientsCount
            && finishedClientsCount > 0;
}
/*
    Удалить всех клиентов, не закончившие сессию
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllUnfinished(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.sessionIsFinished != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_SESSIONFINISHINGFAILED);
        }
    }
}
/*
    Сброс флагов при переходе к следующему блоку
*/
void CanFTP_Server_Session_ClientsCollection_NextBlockReset(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        CanFTP_Server_Session_Client_NextBlockReset(&(collection->clients[clientIndex]));
    }
}
/*
    Проврить, что все клиенты начали чтение блока
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsBlockStarted(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t blockStartedClientsCount = 0;
    CanFTP_DeviceCode_t disposedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isBlockStarted == CANFTP_TRUE)
        {
            blockStartedClientsCount++;
        }
        else if (!CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            disposedClientsCount++;
        }
    }

    return (blockStartedClientsCount + disposedClientsCount) == collection->clientsCount
            && blockStartedClientsCount > 0;
}
/*
    Удалить всех клиентов, не начавших чтение блока
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnstarted(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isBlockStarted != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_BLOCKSTARTINGFAILED);
        }
    }
}
/*
    Проврить, что все клиенты окончили чтение блока
*/
CanFTP_Logical_t CanFTP_Server_Session_ClientsCollection_CheckClientsBlockFinished(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;
    CanFTP_DeviceCode_t blockFinishedClientsCount = 0;
    CanFTP_DeviceCode_t disposedClientsCount = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isBlockFinished == CANFTP_TRUE
            && collection->clients[clientIndex].statuses.isNextBlockReady == CANFTP_TRUE)
        {
            blockFinishedClientsCount++;
        }
        else if (!CanFTP_Server_Session_Client_IsInSession(&(collection->clients[clientIndex])))
        {
            disposedClientsCount++;
        }
    }

    return (blockFinishedClientsCount + disposedClientsCount) == collection->clientsCount
            && blockFinishedClientsCount > 0;
}
/*
    Удалить всех клиентов, не окончавших чтение блока
*/
void CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnfinished(CanFTP_Server_Session_ClientsCollection_t* collection)
{
    CanFTP_DeviceCode_t clientIndex = 0;

    for (clientIndex = 0; clientIndex < collection->clientsCount; clientIndex++)
    {
        // В случае не прохождения регистрации, клиент удаляется
        if (collection->clients[clientIndex].statuses.isBlockFinished != CANFTP_TRUE
            || collection->clients[clientIndex].statuses.isNextBlockReady != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(&(collection->clients[clientIndex]), CANFTP_SESSIONSTATUS_ERROR_BLOCKFINISHINFFAILED);
        }
    }
}
