/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

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
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    client->assosiation.sessionCode = sessionCode;
    client->assosiation.deviceCode = clientCode;
    // Инициализация запросов
    {
        client->requests.disposeBecauseSessionHasFinished = CANFTP_FALSE;
    } 
    // Инициализация статусов
    {
        client->statuses.isDisposed = CANFTP_FALSE;
        client->statuses.isRegistrated = CANFTP_FALSE;
        client->statuses.isConfigurated = CANFTP_FALSE;
        client->statuses.sessionIsStarted = CANFTP_FALSE;
        client->statuses.sessionIsFinished = CANFTP_FALSE;
        client->statuses.sessionStatus = CANFTP_SESSIONSTATUS_OK;
        client->statuses.isBlockStarted = CANFTP_FALSE;
        client->statuses.isBlockFinished = CANFTP_FALSE;
        client->statuses.isNextBlockReady = CANFTP_FALSE;
        client->statuses.blockStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
    }
    // Связывание с клиентом на стороне сервера
    if (serverClient != CANFTP_NULL
        && !CanFTP_Server_Client_IsInSession(serverClient))
    {
        client->serverClient = serverClient;
        client->serverClient->isInSession = CANFTP_TRUE;
    }
    else
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_ALREADYINSESSION);
        // Выставляем флаг, что он уже удален
        client->statuses.isDisposed = CANFTP_TRUE;
    }
    CanFTP_TimeTrigger_SetInterval(&(client->lostConnectionTrigger), CANFTP_SERVER_SESSION_LOSTCONNECTION_TIMEOUT);
    CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
    CanFTP_TimeTrigger_Update(&(client->repeateSendingTrigger));
    CanFTP_TimeTrigger_Update(&(client->deletingSendingTrigger));
    CanFTP_IterationsHandler_Reset(&(client->repeateSendingCounter));
    CanFTP_IterationsHandler_Reset(&(client->deletingSendingCounter));
    // Сброс полей
    {
        client->isDisposeEventCalled = CANFTP_FALSE;
    }
}
/*
    Подготовить клиента
*/
void CanFTP_Server_Session_Client_Prepare(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));
}
/*
    Удаление клиента
*/
void CanFTP_Server_Session_Client_Dispose(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    if (CanFTP_Server_Session_Client_IsInSession(client))
    {
        // Если клиент не удаляется по факту звершения сессии
        if (client->requests.disposeBecauseSessionHasFinished != CANFTP_TRUE)
        {
            CanFTP_Server_Session_Client_SetSessionStatus(client, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);
        }

        client->serverClient->isInSession = CANFTP_FALSE;
        client->statuses.isDisposed = CANFTP_TRUE;
    }
}
/*
    Установить статус сессии клиенту
*/
void CanFTP_Server_Session_Client_SetSessionStatus(CanFTP_Server_Session_Client_t *client, CanFTP_SessionStatus_t status)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    if (client->statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK)
    {
        client->statuses.sessionStatus = status;
    }
}
/*
    Получить статус сессии
*/
CanFTP_SessionStatus_t CanFTP_Server_Session_Client_GetSessionStatus(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return CANFTP_SESSIONSTATUS_OK;
    }

    return client->statuses.sessionStatus;
}
/*
    Обновить параметры отпавки сообщений управления
*/
void CanFTP_Server_Session_Client_UpdateControlSendingParams(CanFTP_Server_Session_Client_t *client
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    CanFTP_TimeTrigger_SetInterval(&(client->repeateSendingTrigger), interval);
    CanFTP_TimeTrigger_Update(&(client->repeateSendingTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(client->repeateSendingCounter), maxCount);
    CanFTP_IterationsHandler_Reset(&(client->repeateSendingCounter));
    // Инициализация интервала времени потери связи
    {
        CanFTP_TimeInterval_t newLostConnectionTimeout = interval * maxCount * maxCount;
        // Обработка сценария, когда понижается скорость работы протокола, с условием сохранения минимального интервала времени 
        if (newLostConnectionTimeout < CANFTP_SERVER_SESSION_LOSTCONNECTION_TIMEOUT)
        {
            newLostConnectionTimeout = CANFTP_SERVER_SESSION_LOSTCONNECTION_TIMEOUT;
        }

        CanFTP_TimeTrigger_SetInterval(&(client->lostConnectionTrigger), newLostConnectionTimeout);
    }
}
/*
    Обновить параметры отпавки сообщений удаления клиента из сессии
*/
void CanFTP_Server_Session_Client_UpdateDeletingSendingParams(CanFTP_Server_Session_Client_t *client
    // Интервал времени отправки
    , CanFTP_TimeInterval_t interval
    // Количество отправляемых сообщений
    , CanFTP_IterationCounter_t maxCount)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    CanFTP_TimeTrigger_SetInterval(&(client->deletingSendingTrigger), interval);
    CanFTP_TimeTrigger_Update(&(client->deletingSendingTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(client->deletingSendingCounter), maxCount);
}
/*
    Проверить, что клиент активно участвует в сессии
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_IsInSession(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return CANFTP_FALSE;
    }

    return client->statuses.isDisposed == CANFTP_FALSE;
}
/*
    Проверить клиента
*/
CanFTP_Logical_t CanFTP_Server_Session_Client_Check(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return CANFTP_FALSE;
    }

    if (CanFTP_TimeTrigger_HasFired(&(client->lostConnectionTrigger)))
    {
        CanFTP_Server_Session_Client_SetSessionStatus(client, CANFTP_SESSIONSTATUS_ERROR_LOSTCONNECTION);

        return CANFTP_FALSE;
    }
    else if (!CanFTP_IterationsHandler_CheckCount(&(client->repeateSendingCounter)))
    {
        CanFTP_Server_Session_Client_SetSessionStatus(client, CANFTP_SESSIONSTATUS_ERROR_REQUESTSSENDINGOVERCOME);

        return CANFTP_FALSE;
    }
    
    return client->statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK;
}
/*
    Сброс флагов при переходе к следующему блоку
*/
void CanFTP_Server_Session_Client_NextBlockReset(CanFTP_Server_Session_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }

    client->statuses.isBlockStarted = CANFTP_FALSE;
    client->statuses.isBlockFinished = CANFTP_FALSE;
    client->statuses.isNextBlockReady = CANFTP_FALSE;
    client->statuses.blockStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
}
