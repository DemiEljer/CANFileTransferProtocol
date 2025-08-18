#include "CanFTP_Server_SessionsCollection.h"

/*
    Проинициализировать коллекцию сессий
*/
void CanFTP_Server_SessionsCollection_Init(CanFTP_Server_SessionsCollection_t* collection)
{
    uint32_t i = 0;
    for (i = 0; i < CANFTP_SERVER_SESSIONS_MAXCOUNT; i++)
    {
        collection->sessions[i] = CANFTP_NULL;
    }
    collection->activeSessionsCount = 0;
}
/*
    Проверить количество активных сессий
*/
CanFTP_SessionCode_t CanFTP_Server_SessionsCollection_CheckActiveSessions(CanFTP_Server_SessionsCollection_t* collection)
{
    CanFTP_SessionCode_t i = 0;
    // Количество активных сессий до проверки
    CanFTP_SessionCode_t previouseActiveSessionsCount = collection->activeSessionsCount;
    // Счетчик активных проверенных сессий
    CanFTP_SessionCode_t checkedActiveSessionsCount = 0;
    // Проверка только в том случае, если есть активные сессии
    if (collection->activeSessionsCount > 0)
    {
        for (i = 0; i < CANFTP_SERVER_SESSIONS_MAXCOUNT; i++)
        {
            if (collection->sessions[i] != CANFTP_NULL)
            {
                // Удаляем сессию, если выставлен соответсвующий статус
                if (collection->sessions[i]->statuses.canBeDisposed == CANFTP_TRUE)
                {
                    CanFTP_Server_Session_Dispose(collection->sessions[i]);
                    // Удаляем сессию из памяти
                    free(collection->sessions[i]);
                    // Обнуляем указатель на сессию
                    collection->sessions[i] = CANFTP_NULL;
                    // Уменьшаем счетчик активных сессий
                    collection->activeSessionsCount--;
                }
                // Увеличиваем счетчик активных проверенных сессий
                checkedActiveSessionsCount++;
            }
            // Проверка граничных условий прекращения дальнейшей проверки
            if (checkedActiveSessionsCount == previouseActiveSessionsCount)
            {
                break;
            }
        }
    }

    return collection->activeSessionsCount;
}
/*
    Вызвать логики сессий
*/
CanFTP_SessionCode_t CanFTP_Server_SessionsCollection_InvokeSessionsOrDispose(CanFTP_Server_SessionsCollection_t* collection)
{
    CanFTP_SessionCode_t i = 0;
    // Количество активных сессий до проверки
    CanFTP_SessionCode_t previouseActiveSessionsCount = collection->activeSessionsCount;
    // Счетчик активных проверенных сессий
    CanFTP_SessionCode_t checkedActiveSessionsCount = 0;
    // Проверка только в том случае, если есть активные сессии
    if (collection->activeSessionsCount > 0)
    {
        for (i = 0; i < CANFTP_SERVER_SESSIONS_MAXCOUNT; i++)
        {
            if (collection->sessions[i] != CANFTP_NULL)
            {
                // Удаляем сессию, если выставлен соответсвующий статус
                if (collection->sessions[i]->statuses.canBeDisposed == CANFTP_TRUE)
                {
                    CanFTP_Server_Session_Dispose(collection->sessions[i]);
                    // Удаляем сессию из памяти
                    free(collection->sessions[i]);
                    // Обнуляем указатель на сессию
                    collection->sessions[i] = CANFTP_NULL;
                    // Уменьшаем счетчик активных сессий
                    collection->activeSessionsCount--;
                }
                else
                {
                    CanFTP_Server_Session_Invoke(collection->sessions[i]);
                }
                // Увеличиваем счетчик активных проверенных сессий
                checkedActiveSessionsCount++;
            }
            // Проверка граничных условий прекращения дальнейшей проверки
            if (checkedActiveSessionsCount == previouseActiveSessionsCount)
            {
                break;
            }
        }
    }

    return collection->activeSessionsCount;
}
/*
    Создать экземпляр сессии
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_CreateNewSession(CanFTP_Server_SessionsCollection_t* collection, void* server)
{
    if (collection->activeSessionsCount < CANFTP_SERVER_SESSIONS_MAXCOUNT)
    {
        CanFTP_SessionCode_t newSessionIndex = 0;
        // Поиск первого свободного индекса сессии
        for (newSessionIndex = 0; newSessionIndex < CANFTP_SERVER_SESSIONS_MAXCOUNT; newSessionIndex++)
        {
            if (collection->sessions[newSessionIndex] == CANFTP_NULL)
            {
                collection->sessions[newSessionIndex] = malloc(sizeof(CanFTP_Server_Session_t));
                CanFTP_Server_Session_Init(collection->sessions[newSessionIndex], server, newSessionIndex);

                break;
            }
        }
        // Увеличивем счетчик активных сессий
        collection->activeSessionsCount++;

        return collection->sessions[newSessionIndex];
    }
    else
    {
        return CANFTP_NULL;
    }
}
/*
    Получить указатель на сессию по ее коду
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_GetSessionByCode(CanFTP_Server_SessionsCollection_t* collection, CanFTP_SessionCode_t sessionCode)
{
    if (sessionCode >= CANFTP_SERVER_SESSIONS_MAXCOUNT)
    {
        CanFTP_ThrowError();

        return CANFTP_NULL;
    }
    else
    {
        return collection->sessions[sessionCode];
    }
}
/*
    Остановить активные сессии
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_TerminateActiveSessions(CanFTP_Server_SessionsCollection_t* collection)
{
    CanFTP_SessionCode_t i = 0;
    // Счетчик активных проверенных сессий
    CanFTP_SessionCode_t checkedActiveSessionsCount = 0;
    // Проверка только в том случае, если есть активные сессии
    if (collection->activeSessionsCount > 0)
    {
        for (i = 0; i < CANFTP_SERVER_SESSIONS_MAXCOUNT; i++)
        {
            if (collection->sessions[i] != CANFTP_NULL)
            {
                // Удаление сессии
                CanFTP_Server_Session_Delete(collection->sessions[i]);
                // Увеличиваем счетчик активных проверенных сессий
                checkedActiveSessionsCount++;
            }
            // Проверка граничных условий прекращения дальнейшей проверки
            if (checkedActiveSessionsCount == collection->activeSessionsCount)
            {
                break;
            }
        }
    }
}
/*
    Получить активную сессию по иднексу
*/
CanFTP_Server_Session_t* CanFTP_Server_SessionsCollection_GetActiveSessionByIndex(CanFTP_Server_SessionsCollection_t *collection, CanFTP_SessionCode_t index)
{
    if (index >= collection->activeSessionsCount)
    {
        CanFTP_ThrowError();

        return CANFTP_NULL;
    }
    else
    {
        CanFTP_SessionCode_t i = 0;
        // Счетчик активных проверенных сессий
        CanFTP_SessionCode_t checkedActiveSessionsCount = 0;
        // Проверка только в том случае, если есть активные сессии
        if (collection->activeSessionsCount > 0)
        {
            for (i = 0; i < CANFTP_SERVER_SESSIONS_MAXCOUNT; i++)
            {
                if (collection->sessions[i] != CANFTP_NULL)
                {
                    if (checkedActiveSessionsCount == index)
                    {
                        return collection->sessions[i];
                    }
                    // Увеличиваем счетчик активных проверенных сессий
                    checkedActiveSessionsCount++;
                }
            }
        }
    }
}
