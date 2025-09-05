/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_Session_HelpFunctions.h"

/*
    Получить состояние сессии
*/
CanFTP_SessionState_t CanFTP_Server_Session_GetState(CanFTP_Server_Session_t *session)
{
    return *(session->state);
}
/*
    Установить статус состояния сессии
*/
void CanFTP_Server_Session_SetStatus(CanFTP_Server_Session_t *session, CanFTP_SessionStatus_t status)
{
    // Изменить статус в случае, если до этого сессия находилась в рабочем состоянии
    if (session->status == CANFTP_SESSIONSTATUS_OK)
    {
        session->status = status;
    }
    // В случае возникновения ошибки, устанавливается запрос на остановку сессии
    if (session->status != CANFTP_SESSIONSTATUS_OK)
    {
        session->requests.stopRequest = CANFTP_TRUE;
    }
}
/*
    Находится ли сессия в активном состоянии
*/
CanFTP_SessionState_t CanFTP_Server_Session_IsActive(CanFTP_Server_Session_t *session)
{
    return CanFTP_Server_Session_GetState(session) != CANFTP_SESSIONSTATE_CREATED
           && CanFTP_Server_Session_GetState(session) != CANFTP_SESSIONSTATE_FINISHED;
}
/*
    Проверить, что клиент относится к данной сессии
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_CheckClientIsInSession(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t clientIndex)
{
    if (CanFTP_Server_Session_IsActive(session))
    {
        CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), clientIndex);

        if (client != CANFTP_NULL
            && CanFTP_Server_Session_Client_IsInSession(client))
        {
            // Обновление метки времени потери связи с клиентом
            CanFTP_TimeTrigger_Update(&(client->lostConnectionTrigger));

            return client;
        }
        else
        {
            return CANFTP_NULL;
        }
    }
    else 
    {
        return CANFTP_NULL;
    }
}
