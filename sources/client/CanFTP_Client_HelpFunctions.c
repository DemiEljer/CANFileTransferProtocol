/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Client_HelpFunctions.h"

/*
    Проверить, находится ли клиент в состоянии активной сессии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveSession(CanFTP_Client_t* client)
{
    return CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_REGISTRATED
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_CONFIGURING
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_STARTED
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_STARTED
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_RECIEVING
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_FINISHED
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_SESSION_FINISHED;
}
/*
    Проверить условие, что конкретное сообщение относится к активной сессии клиента 
*/
CanFTP_Logical_t CanFTP_Client_CheckIfMessageCorrespondingToActiveSession(CanFTP_Client_t* client, CanFTP_SessionCode_t sessionCode)
{
    // Проверка условий обработки данного сообшения
    if (CanFTP_Client_IsInActiveSession(client)
        && client->agents.sessionController.clientAssosiation.sessionCode == sessionCode)
    {
        // Обновление метки времеи в случае получения сообщения от сервера
        CanFTP_TimeTrigger_Update(&(client->agents.sessionController.lostConnectionTrigger));
        // Обновление количество ответов на запросы только в случае, если клиент не завршеает сессию
        if (CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED)
        {
            // Сброс счетчика количества повторений подтверждений приема
            CanFTP_IterationsHandler_Reset(&(client->agents.sessionController.repeateAckCounter));
        }

        return CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        return CANFTP_FALSE;
    }
}
/*
    Проверить, находится ли клиент в состоянии Ping
*/
CanFTP_Logical_t CanFTP_Client_IsPinging(CanFTP_Client_t* client)
{
    return CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_PING_RESPONSING
            || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_PING_FINISHED;
}
/*
    Проверить, находится ли протокол в активном состоянии
*/
CanFTP_Logical_t CanFTP_Client_IsInActiveState(CanFTP_Client_t* client)
{
    return CanFTP_Client_IsInActiveSession(client)
           || CanFTP_Client_GetState(client) == CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
}
/*
    Получить состояние клиента
*/
CanFTP_ClientState_t CanFTP_Client_GetState(CanFTP_Client_t *client)
{
    return *(client->state);
}
