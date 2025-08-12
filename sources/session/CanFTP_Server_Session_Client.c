#include "CanFTP_Server_Session_Client.h"

/*
    Инициализация клиента
*/
void CanFTP_Server_Session_Client_Init(CanFTP_Server_Session_Client_t *client
    // Код сессии
    , CanFTP_SessionCode_t sessionCode
    // Клиент на стороне сервера
    , CanFTP_Server_Client_t* serverClient
    // Код клиента
    , CanFTP_DeviceCode_t clientCode)
{
    client->assosiation.sessionCode = sessionCode;
    client->assosiation.deviceCode = clientCode;
    // Связывание с клиентом на стороне сервера
    if (serverClient != CANFTP_NULL)
    {
        client->serverClient = serverClient;
        client->serverClient->isInSession = CANFTP_TRUE;
    }
    // Инициализация статусов
    {
        client->statuses.isDisposed = CANFTP_FALSE;
        client->statuses.isRegistrated = CANFTP_FALSE;
        client->statuses.isConfigurated = CANFTP_FALSE;
        client->statuses.sessionIsStarted = CANFTP_FALSE;
        client->statuses.sessionIsFinished = CANFTP_FALSE;
        client->statuses.sessionStatus = CANFTP_SESSIONSTATUS_OK;
    }
    CanFTP_TimeTrigger_SetInterval(&(client->lostConnectionTrigger), CANFTP_SERVER_SESSION_LOSTCONNECTION_TIMEOUT);
    CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
    CanFTP_TimeTrigger_Update(&(client->repeateSendingTrigger));
    CanFTP_IterationsHandler_Reset(&(client->repeateSendingCounter));
}
/*
    Подготовить клиента
*/
void CanFTP_Server_Session_Client_Prepare(CanFTP_Server_Session_Client_t *client)
{
    CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
}
/*
    Удаление клиента
*/
void CanFTP_Server_Session_Client_Dispose(CanFTP_Server_Session_Client_t *client)
{
    if (CanFTP_Server_Session_Client_IsInSession(client))
    {
        client->serverClient->isInSession = CANFTP_FALSE;
        client->serverClient = CANFTP_NULL;
        client->statuses.isDisposed = CANFTP_TRUE;
    }
}
/*
    Установить статус сессии клиенту
*/
void CanFTP_Server_Session_Client_SetSessionStatus(CanFTP_Server_Session_Client_t *client, CanFTP_SessionStatus_t status)
{
    if (client->statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK)
    {
        client->statuses.sessionStatus = status;
    }
}
/*
    Обновить параметры отпавки сообщений
*/
void CanFTP_Server_Session_Client_UpdateSendingParams(CanFTP_Server_Session_Client_t *client
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount)
{
    CanFTP_TimeTrigger_SetInterval(&(client->repeateSendingTrigger), interval);
    CanFTP_TimeTrigger_Update(&(client->repeateSendingTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(client->repeateSendingCounter), maxCount);
    CanFTP_IterationsHandler_Reset(&(client->repeateSendingCounter));
}
/*
    Проверить, что клиент активно участвует в сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_IsInSession(CanFTP_Server_Session_Client_t *client)
{
    return client->serverClient != CANFTP_NULL
           && client->statuses.isDisposed == CANFTP_FALSE;
}
/*
    Проверить клиента
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_Check(CanFTP_Server_Session_Client_t *client)
{
    if (CanFTP_TimeTrigger_HasFired(&(client->lostConnectionTrigger)))
    {
        CanFTP_Server_Session_Client_SetSessionStatus(client, CANFTP_SESSIONSTATUS_ERROR_LOSTCONNECTION);

        return CANFTP_FALSE;
    }
    else if (!CanFTP_IterationsHandler_CheckCount(&(client->repeateSendingCounter)))
    {
        CanFTP_Server_Session_Client_SetSessionStatus(client, CANFTP_SESSIONSTATUS_ERROR_REQUESTSSENDINGOVERCONE);
    }

    
    return CANFTP_TRUE;
}
