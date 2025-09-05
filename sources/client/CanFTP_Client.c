/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Client.h"

#include "CanFTP_Client_States_Handlers.h"

/*
    Инициализация клиента
*/
void CanFTP_Client_Init(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    client->state = (CanFTP_ClientState_t*)&(client->fms.fms.state);
    // Инициализация обработчиков состояний
    {
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.enterStateHandler = CanFTP_Client_State_IDLE_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.bodyStateHandler = CanFTP_Client_State_IDLE_Body;
        client->fms.states[CANFTP_CLIENTSTATE_IDLE].handlers.leaveStateHandler = CanFTP_Client_State_IDLE_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.enterStateHandler = CanFTP_Client_State_PING_RESPONSING_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.bodyStateHandler = CanFTP_Client_State_PING_RESPONSING_Body;
        client->fms.states[CANFTP_CLIENTSTATE_PING_RESPONSING].handlers.leaveStateHandler = CanFTP_Client_State_PING_RESPONSING_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.enterStateHandler = CanFTP_Client_State_PING_FINISHED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.bodyStateHandler = CanFTP_Client_State_PING_FINISHED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_PING_FINISHED].handlers.leaveStateHandler = CanFTP_Client_State_PING_FINISHED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE].handlers.enterStateHandler = CanFTP_Client_State_PROTOCOL_ACTIVE_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE].handlers.bodyStateHandler = CanFTP_Client_State_PROTOCOL_ACTIVE_Body;
        client->fms.states[CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE].handlers.leaveStateHandler = CanFTP_Client_State_PROTOCOL_ACTIVE_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_SESSION_REGISTRATED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_REGISTRATED].handlers.enterStateHandler = CanFTP_Client_State_SESSION_REGISTRATED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_REGISTRATED].handlers.bodyStateHandler = CanFTP_Client_State_SESSION_REGISTRATED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_REGISTRATED].handlers.leaveStateHandler = CanFTP_Client_State_SESSION_REGISTRATED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_SESSION_CONFIGURED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_CONFIGURED].handlers.enterStateHandler = CanFTP_Client_State_SESSION_CONFIGURED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_CONFIGURED].handlers.bodyStateHandler = CanFTP_Client_State_SESSION_CONFIGURED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_CONFIGURED].handlers.leaveStateHandler = CanFTP_Client_State_SESSION_CONFIGURED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_SESSION_STARTED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_STARTED].handlers.enterStateHandler = CanFTP_Client_State_SESSION_STARTED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_STARTED].handlers.bodyStateHandler = CanFTP_Client_State_SESSION_STARTED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_STARTED].handlers.leaveStateHandler = CanFTP_Client_State_SESSION_STARTED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_SESSION_FINISHED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_FINISHED].handlers.enterStateHandler = CanFTP_Client_State_SESSION_FINISHED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_FINISHED].handlers.bodyStateHandler = CanFTP_Client_State_SESSION_FINISHED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_SESSION_FINISHED].handlers.leaveStateHandler = CanFTP_Client_State_SESSION_FINISHED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_STARTED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_STARTED].handlers.enterStateHandler = CanFTP_Client_State_BLOCK_STARTED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_STARTED].handlers.bodyStateHandler = CanFTP_Client_State_BLOCK_STARTED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_STARTED].handlers.leaveStateHandler = CanFTP_Client_State_BLOCK_STARTED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_RECIEVING].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_RECIEVING].handlers.enterStateHandler = CanFTP_Client_State_BLOCK_RECIEVING_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_RECIEVING].handlers.bodyStateHandler = CanFTP_Client_State_BLOCK_RECIEVING_Body;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_RECIEVING].handlers.leaveStateHandler = CanFTP_Client_State_BLOCK_RECIEVING_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_FINISHED].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_FINISHED].handlers.enterStateHandler = CanFTP_Client_State_BLOCK_FINISHED_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_FINISHED].handlers.bodyStateHandler = CanFTP_Client_State_BLOCK_FINISHED_Body;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_FINISHED].handlers.leaveStateHandler = CanFTP_Client_State_BLOCK_FINISHED_Leave;

        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY].stateModel = CANFTP_NULL;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY].handlers.enterStateHandler = CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Enter;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY].handlers.bodyStateHandler = CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Body;
        client->fms.states[CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY].handlers.leaveStateHandler = CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Leave;

        CanFTP_FinalStateMachine_Init(&(client->fms.fms), CANFTP_CLIENTSTATES_COUNT, client->fms.states, CANFTP_CLIENTSTATE_IDLE);   
        // Инициализация обработчиков событий
        client->fms.fms.callbacks.changeStateCallback = CanFTP_Client_StateChanedEventHandler;
        client->fms.fms.callbacks.iterationCallback = CanFTP_Client_IterationEventHandler;
    }
    // Инициализация логики обработки сообшений
    {
        // Инициализация обратного вызова 
        client->callbacks.sendMessageCallback = CANFTP_NULL;

        client->messagesHub.clientBlockControlCallback = CANFTP_NULL;
        client->messagesHub.clientBlockCRCCallback = CANFTP_NULL;
        client->messagesHub.clientPingResponseCallback = CANFTP_NULL;
        client->messagesHub.clientSessionControlCallback = CANFTP_NULL;
        client->messagesHub.clientSubBlocksStatusesCallback = CANFTP_NULL;
        client->messagesHub.serverBlockControlCallback = CanFTP_Client_MessageRecieve_BlockControl;
        client->messagesHub.serverDataFrameCallback = CanFTP_Client_MessageRecieve_DataFrame;
        client->messagesHub.serverPingCallback = CanFTP_Client_MessageRecieve_Ping;
        client->messagesHub.serverPingResponseAckCallback = CanFTP_Client_MessageRecieve_PingResponseAck;
        client->messagesHub.serverRegistrationCallback = CanFTP_Client_MessageRecieve_Registration;
        client->messagesHub.serverSessionControlCallback = CanFTP_Client_MessageRecieve_SessionControl;
    }
    // Инициализация агентов
    {
        CanFTP_Client_Agent_LogicLockController_Reset(&(client->agents.logicLockController));
        CanFTP_Client_Agent_PingControler_Reset(&(client->agents.pingController));
        CanFTP_Client_Agent_SessionController_Reset(&(client->agents.sessionController));
    }
    // Инициализация обратных вызовов
    {
        client->callbacks.lockLogicRequestCallback = CANFTP_NULL;
        client->callbacks.unlockLogicRequestCallback = CANFTP_NULL;
        client->callbacks.sessionConfigureationCallback = CANFTP_NULL;
        client->callbacks.blockRecieceCallback = CANFTP_NULL;
        client->callbacks.sessionFinishedCallback = CANFTP_NULL;
    }
    // Сброс конфигурации
    {
        CanFTP_DeviceConfig_Reset(&(client->deviceConfig));
    }
    // Сброс флагов управления
    {
        client->control.autpUpdateSoftVersion = CANFTP_FALSE;
        client->control.pingPermition = CANFTP_FALSE;
        client->control.sessionStartPermition = CANFTP_FALSE;
    }
}
/*
    Вызов логики обработки клиента
*/
void CanFTP_Client_Invoke(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_Cast(client));
}
/*
    Обработка получения сообщений
*/
void CanFTP_Client_RecieveCanMessage(CanFTP_Client_t *client, CanFTP_CanMessage_t* canMessage)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    CanFTP_Messages_Hub_RecieveMessage(&(client->messagesHub), canMessage, client);
}
/*
    Проинициализировать функцию генерации случайных значений
*/
void CanFTP_Client_InitRanmod(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    CanFTP_Random_Init(&(client->agents.random), client->deviceConfig.serialNumber);
}
/*
    Принудительно остановить сессию
*/
void CanFTP_Client_TerminateSession(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    client->agents.sessionController.requsts.requestSession = CANFTP_FALSE;
}
/*
    Заблокировать логику
*/
void CanFTP_Client_LockLogic(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_TRUE;
}
/*
    Разблокировать логику
*/
void CanFTP_Client_UnlockLogic(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return;
    }    

    client->agents.logicLockController.requsts.requestToLockLogic = CANFTP_FALSE;
}
/*
    Проверить, находится ли клиент в состоянии Ping
*/
CanFTP_Logical_t CanFTP_Client_CheckIsPinging(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return CANFTP_FALSE;
    } 

    return CanFTP_Client_IsPinging(client);
}
/*
    Проверить, находится ли клиент сотоянии активной сессии
*/
CanFTP_Logical_t CanFTP_Client_CheckIsInSession(CanFTP_Client_t *client)
{
    if (client == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_CLIENT_NULL);

        return CANFTP_FALSE;
    }

    return CanFTP_Client_IsInActiveSession(client);
}
