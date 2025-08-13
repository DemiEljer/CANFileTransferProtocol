#include "CanFTP_Client_States_Handlers.h"

#include "stdio.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Client_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Client_IterationEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    // Прекращение процесса Ping в случае выставления запрета
    if (client->control.pingPermition != CANFTP_TRUE)
    {
        client->agents.pingController.requsts.requestPinging = CANFTP_FALSE;
    }
    // Запрос на блокировку логики
    if (client->agents.logicLockController.requsts.requestToLockLogic == CANFTP_TRUE
        && client->agents.logicLockController.statuses.isLocked != CANFTP_TRUE)
    {
        if (client->callbacks.lockLogicRequestCallback != CANFTP_NULL)
        {
            client->agents.logicLockController.statuses.isLocked = client->callbacks.lockLogicRequestCallback(client);
        }
        else
        {
            client->agents.logicLockController.statuses.isLocked = CANFTP_TRUE;
        }
    }
    // Запрос на снятие блокировки логики
    else if (client->agents.logicLockController.requsts.requestToLockLogic != CANFTP_TRUE
             && client->agents.logicLockController.statuses.isLocked == CANFTP_TRUE)
    {
        if (client->callbacks.unlockLogicRequestCallback != CANFTP_NULL)
        {
            client->agents.logicLockController.statuses.isLocked = !client->callbacks.unlockLogicRequestCallback(client);
        }
        else
        {
            client->agents.logicLockController.statuses.isLocked = CANFTP_FALSE;
        }
    }
    // Выключение сесси в случае выставления запрета
    if (client->control.sessionStartPermition != CANFTP_TRUE)
    {
        client->agents.sessionController.requsts.requestSession = CANFTP_FALSE;
    }
    // Обработка логики сесии
    if (CanFTP_Client_IsInActiveSession(client)
        && CanFTP_Client_GetState(client) != CANFTP_CLIENTSTATE_SESSION_FINISHED)
    {
        // В случае, если не получилось заблокировать логику, выходим из сесии
        if (client->agents.logicLockController.statuses.isLocked != CANFTP_TRUE)
        {
            CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_LOGICISNOTLOCKED);
        }
        // В случае, если превышено время ожидания ответа от сервера
        if (CanFTP_TimeTrigger_HasFired(&(client->agents.sessionController.lostConnectionTrigger)))
        {
            CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_LOSTCONNECTION);
        }
        // В случае, если превышено количество повторов ответа серверу
        if (!CanFTP_IterationsHandler_CheckCount(&(client->agents.sessionController.repeateAckCounter)))
        {
            CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ACKCOUNTOVERCOME);
        }
    }
}
/*
    Обработка состояния IDLE
*/
#ifndef CLIENT_STATE_IDLE_
#define CLIENT_STATE_IDLE_

void CanFTP_Client_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    DEBUG_CLIENT_PRINTSTATE("IDLE", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_IDLE;
    // Переход в состояние Ping
    if (client->agents.pingController.requsts.requestPinging == CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_PING_RESPONSING;
    }
    // Переход в состояние активной работы протокола
    else if (client->agents.logicLockController.statuses.isLocked == CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
    }
    else if (client->agents.sessionController.requsts.requestSession == CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
    }

    return resultState;
}

void CanFTP_Client_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

}

#endif // CLIENT_STATE_IDLE_
/*
    Обработка состояния PING_RESPONSING
*/
#ifndef CLIENT_STATE_PING_RESPONSING_
#define CLIENT_STATE_PING_RESPONSING_

void CanFTP_Client_State_PING_RESPONSING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    // Инициализация времени повторной отправки сообщений
    CanFTP_TimeTrigger_SetInterval(&(client->agents.pingController.reapeateSendingTrigger)
        , CanFTP_Random_GetNext_Range(&(client->agents.random)
        , CANFTP_CLIENT_PING_MININTERVAL
        , CANFTP_CLIENT_PING_MAXINTERVAL));
    CanFTP_TimeTrigger_Update(&(client->agents.pingController.reapeateSendingTrigger));

    DEBUG_CLIENT_PRINTSTATE("PING_RESPONSING", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_PING_RESPONSING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_PING_RESPONSING;

    // Обработка логики выхода из состояния Ping по истечению времени или по снятию запроса
    if (client->agents.pingController.requsts.requestPinging == CANFTP_FALSE
        || client->agents.sessionController.requsts.requestSession == CANFTP_TRUE
        || CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.coolingDownTrigger)))
    {
        CanFTP_Client_Agent_PingControler_Reset(&(client->agents.pingController));

        if (client->agents.sessionController.requsts.requestSession == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
        }
        else if (client->agents.logicLockController.statuses.isLocked == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
        }
        else
        {
            resultState = CANFTP_CLIENTSTATE_IDLE;
        }
    }
    else if (CanFTP_Client_Agent_PingControler_AllAcksAreReceived(&(client->agents.pingController)))
    {
        resultState = CANFTP_CLIENTSTATE_PING_FINISHED;
    }
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.reapeateSendingTrigger)))
    {
        client->agents.pingController.requestedMessageIndex = 0;
        // Проверка сообщений, необходимых к отправке
        {
            if (client->agents.pingController.pingResponsesAck[0] != CANFTP_TRUE)
            {
                client->agents.pingController.requestedMessageIndex = CANFT_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE1;
                CanFTP_Client_MessageSend_PingResponse(client);
            }
            if (client->agents.pingController.pingResponsesAck[1] != CANFTP_TRUE)
            {
                client->agents.pingController.requestedMessageIndex = CANFT_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE2;
                CanFTP_Client_MessageSend_PingResponse(client);
            }
        }
        // Инициализация времени повторной отправки сообщений
        CanFTP_TimeTrigger_SetInterval(&(client->agents.pingController.reapeateSendingTrigger)
            , CanFTP_Random_GetNext_Range(&(client->agents.random)
            , CANFTP_CLIENT_PING_MININTERVAL
            , CANFTP_CLIENT_PING_MAXINTERVAL));
    }

    return resultState;
}

void CanFTP_Client_State_PING_RESPONSING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

}

#endif // CLIENT_STATE_PING_RESPONSING_
/*
    Обработка состояния PING_FINISHED
*/
#ifndef CLIENT_STATE_PING_FINISHED_
#define CLIENT_STATE_PING_FINISHED_

void CanFTP_Client_State_PING_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    DEBUG_CLIENT_PRINTSTATE("PING_FINISHED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_PING_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_PING_FINISHED;
    // Обработка логики выхода из состояния Ping по истечению времени или по снятию запроса
    if (!client->agents.pingController.requsts.requestPinging
        || client->agents.sessionController.requsts.requestSession == CANFTP_TRUE
        || CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.coolingDownTrigger)))
    {
        if (client->agents.sessionController.requsts.requestSession == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
        }
        else if (client->agents.logicLockController.statuses.isLocked)
        {
            resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
        }
        else
        {
            resultState = CANFTP_CLIENTSTATE_IDLE;
        }
    }

    return resultState;
}

void CanFTP_Client_State_PING_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_PingControler_Reset(&(client->agents.pingController));
}

#endif // CLIENT_STATE_PING_FINISHED_

/*
    Обработка состояния PROTOCOL_ACTIVE
*/
#ifndef CLIENT_STATE_PROTOCOL_ACTIVE_
#define CLIENT_STATE_PROTOCOL_ACTIVE_

void CanFTP_Client_State_PROTOCOL_ACTIVE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    DEBUG_CLIENT_PRINTSTATE("PROTOCOL_ACTIVE", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_PROTOCOL_ACTIVE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;

    // Переход в состояние активной сессии в случае, если выставлен запрос
    if (client->agents.sessionController.requsts.requestSession == CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
    }
    // Переход в состояние Ping
    if (client->agents.pingController.requsts.requestPinging == CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_PING_RESPONSING;
    }
    // Переход в состояние ожидания в случае снятиия блокировки логики
    else if (client->agents.logicLockController.statuses.isLocked != CANFTP_TRUE)
    {
        resultState = CANFTP_CLIENTSTATE_IDLE;
    }

    return resultState;
}

void CanFTP_Client_State_PROTOCOL_ACTIVE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

#endif // CLIENT_STATE_PROTOCOL_ACTIVE_

/*
    Обработка состояния SESSION_REGISTRATED
*/
#ifndef CLIENT_STATE_SESSION_REGISTRATED_
#define CLIENT_STATE_SESSION_REGISTRATED_

void CanFTP_Client_State_SESSION_REGISTRATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_SoftwareVersion_Copy(&(client->agents.sessionController.newSoftVersion), &(client->devicveConfig.softVersion));

    DEBUG_CLIENT_PRINTSTATE("SESSION_REGISTRATED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_SESSION_REGISTRATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_SESSION_REGISTRATED;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        if (client->agents.sessionController.requsts.configurationRequest)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_CONFIGURED;
        }
        // Отправка подтверждения регистрации в рамках сессии
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger))
                 && client->agents.sessionController.statuses.clientHasBeenRegistrated != CANFTP_TRUE)
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_SessionControl(client);
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_SESSION_REGISTRATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_SESSION_REGISTRATED_

/*
    Обработка состояния SESSION_CONFIGURED
*/
#ifndef CLIENT_STATE_SESSION_CONFIGURED_
#define CLIENT_STATE_SESSION_CONFIGURED_

void CanFTP_Client_State_SESSION_CONFIGURED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);
    // Инициализация параметров повторов ответов
    CanFTP_TimeTrigger_SetInterval(&(client->agents.sessionController.repeateAckTrigger), client->agents.sessionController.session.configuration.repeateInterval);
    CanFTP_IterationsHandler_SetMaxCount(&(client->agents.sessionController.repeateAckCounter), client->agents.sessionController.session.configuration.repeateAckCount);
    // Вызов логики согласования с вышестоящей логикой параметров сессии
    {
        if (client->callbacks.sessionConfigureationCallback == CANFTP_NULL)
        {
            client->agents.sessionController.statuses.sessionHasBeenVerified = CANFTP_TRUE;
        }
        else
        {
            client->agents.sessionController.statuses.sessionHasBeenVerified = client->callbacks.sessionConfigureationCallback(client, &(client->agents.sessionController.session.configuration));
        }
    }

    DEBUG_CLIENT_PRINTSTATE("SESSION_CONFIGURED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_SESSION_CONFIGURED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_SESSION_CONFIGURED;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        if (client->agents.sessionController.statuses.sessionHasBeenVerified != CANFTP_TRUE)
        {
            CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_CONFIGURATIONFAILED);

            resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
        }
        else if (client->agents.sessionController.requsts.startRequest)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_STARTED;
        }
        // Отправка подтверждения регистрации сессии
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_SessionControl(client);
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_SESSION_CONFIGURED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_SESSION_CONFIGURED_

/*
    Обработка состояния SESSION_STARTED
*/
#ifndef CLIENT_STATE_SESSION_STARTED_
#define CLIENT_STATE_SESSION_STARTED_

void CanFTP_Client_State_SESSION_STARTED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    DEBUG_CLIENT_PRINTSTATE("SESSION_STARTED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_SESSION_STARTED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_SESSION_STARTED;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        // Переход в состояние окончания сессии
        if (client->agents.sessionController.requsts.stopRequest == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
        }
        // Переход в состояние чтения нового блока файла
        else if (client->agents.sessionController.requsts.startBlockRequest == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_BLOCK_STARTED;
        }
        // Отправка подтверждения начала сессии
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_SessionControl(client);
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_SESSION_STARTED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_SESSION_STARTED_

/*
    Обработка состояния SESSION_FINISHED
*/
#ifndef CLIENT_STATE_SESSION_FINISHED_
#define CLIENT_STATE_SESSION_FINISHED_

void CanFTP_Client_State_SESSION_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    // Проверка, что был передан весь файл
    if (client->agents.sessionController.statuses.resultFileLength != client->agents.sessionController.session.configuration.fileLength)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_FILEUNFINISHED);
    }

    // Корректировка параметров отправки сообщений подтверждения в случае активации вышестоящей логики  
    if (client->agents.logicLockController.requsts.requestToLockLogic != CANFTP_TRUE)
    {
        CanFTP_TimeTrigger_SetInterval(&(client->agents.sessionController.repeateAckTrigger), CANFTP_CLIENT_SEESION_TERMINATIONACK_PERIOD);
        CanFTP_IterationsHandler_SetMaxCount(&(client->agents.sessionController.repeateAckCounter), CANFTP_CLIENT_SEESION_TERMINATIONACK_COUNT);
    }

    DEBUG_CLIENT_PRINTSTATE("SESSION_FINISHED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_SESSION_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;

    // В случае, если превышено время ожидания ответа от сервера, или было отправлено требуемое количество подтверждений окончания сессии
    if (!CanFTP_TimeTrigger_HasFired(&(client->agents.sessionController.lostConnectionTrigger))
        && CanFTP_IterationsHandler_CheckCount(&(client->agents.sessionController.repeateAckCounter)))
    {
        if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_SessionControl(client);
            }
        }
    }
    else
    {
        if (client->agents.logicLockController.statuses.isLocked)
        {
            resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
        }
        else
        {
            resultState = CANFTP_CLIENTSTATE_IDLE;
        }
    }

    return resultState;
}

void CanFTP_Client_State_SESSION_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    // Обратный вызов окончания сессии
    if (client->callbacks.sessionFinishedCallback != CANFTP_NULL)
    {
        client->callbacks.sessionFinishedCallback(client, client->agents.sessionController.statuses.sessionStatus, &(client->agents.sessionController.newSoftVersion));
    }
    // Автоматическое обновление номера версии
    if (client->control.autpUpdateSoftVersion
        && client->agents.sessionController.statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK)
    {
        CanFTP_SoftwareVersion_Copy(&(client->devicveConfig.softVersion), &(client->agents.sessionController.newSoftVersion));
    }

    CanFTP_Client_Agent_SessionController_Reset(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_SESSION_FINISHED_

/*
    Обработка состояния BLOCK_STARTED
*/
#ifndef CLIENT_STATE_BLOCK_STARTED_
#define CLIENT_STATE_BLOCK_STARTED_

void CanFTP_Client_State_BLOCK_STARTED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);
    // Сбролс флагов приема фреймов блока в случае, если запрошена повторная отправка
    if (client->agents.sessionController.statuses.blockHandlingStatus == CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT)
    {
        CanFTP_Client_Agent_SessionController_NewBlockReset(&(client->agents.sessionController));
    }

    DEBUG_CLIENT_PRINTSTATE("BLOCK_STARTED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_BLOCK_STARTED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_BLOCK_RECIEVING;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        // Переход в состояние приема фреймов блока
        if (client->agents.sessionController.requsts.recievingBlockRequest == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_BLOCK_RECIEVING;
        }
        // Отправка подтверждения начала чтения блока
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_BlockControl(client);
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_BLOCK_STARTED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_BLOCK_STARTED_

/*
    Обработка состояния BLOCK_RECIEVING
*/
#ifndef CLIENT_STATE_BLOCK_RECIEVING_
#define CLIENT_STATE_BLOCK_RECIEVING_

void CanFTP_Client_State_BLOCK_RECIEVING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    DEBUG_CLIENT_PRINTSTATE("BLOCK_RECIEVING", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_BLOCK_RECIEVING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_BLOCK_RECIEVING;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        if (client->agents.sessionController.requsts.stopBlockRequest)
        {
            resultState = CANFTP_CLIENTSTATE_BLOCK_FINISHED;
        }
    }

    return resultState;
}

void CanFTP_Client_State_BLOCK_RECIEVING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_BLOCK_RECIEVING_

/*
    Обработка состояния BLOCK_FINISHED
*/
#ifndef CLIENT_STATE_BLOCK_FINISHED_
#define CLIENT_STATE_BLOCK_FINISHED_

void CanFTP_Client_State_BLOCK_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    if (client->agents.sessionController.statuses.blockHandlingStatus != CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED)
    {
        client->agents.sessionController.statuses.allBlocksFramesWereRecieved 
            = CanFTP_Session_FileBlock_VerifySubblocks(&(client->agents.sessionController.session.block));
        // В случае, если все блоки были приняты, рассчитываем CRC-сумму
        if (client->agents.sessionController.statuses.allBlocksFramesWereRecieved)
        {
            CanFTP_Session_FileBlock_CalculateCRC(&(client->agents.sessionController.session.block)
                , client->agents.sessionController.statuses.blockCRC);
        }
    }

    DEBUG_CLIENT_PRINTSTATE("BLOCK_FINISHED", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_BLOCK_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_BLOCK_FINISHED;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        if (client->agents.sessionController.requsts.blockFinishAckRecieved)
        {
            resultState = CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY;
        }
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                if (client->agents.sessionController.statuses.allBlocksFramesWereRecieved)
                {
                    CanFTP_Client_MessageSend_BlockCRC(client);
                }
                else
                {
                    CanFTP_Client_MessageSend_SubBlocksStatuses(client);
                }
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_BLOCK_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_BLOCK_FINISHED_

/*
    Обработка состояния BLOCK_NEXTBLOCKREADY
*/
#ifndef CLIENT_STATE_BLOCK_NEXTBLOCKREADY_
#define CLIENT_STATE_BLOCK_NEXTBLOCKREADY_

void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    if (client->agents.sessionController.statuses.blockHandlingStatus == CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED
        && client->agents.sessionController.statuses.newBlockIsHandling == CANFTP_TRUE)
    {
        // Обработный вызов успешного приема блока
        if (client->callbacks.blockRecieceCallback != CANFTP_NULL)
        {
            client->callbacks.blockRecieceCallback(client
                , client->agents.sessionController.statuses.resultFileLength 
                , client->agents.sessionController.session.block.length
                , client->agents.sessionController.session.block.data);
        }
        // Увеличение длины файла
        client->agents.sessionController.statuses.resultFileLength += client->agents.sessionController.session.block.length;
        // Сброс флага обработки нового блока
        client->agents.sessionController.statuses.newBlockIsHandling = CANFTP_FALSE;
    }
    // Сброс флагов управления процессом приема блока
    CanFTP_Client_Agent_SessionController_ResetBlock(&(client->agents.sessionController));

    DEBUG_CLIENT_PRINTSTATE("BLOCK_NEXTBLOCKREADY", client->devicveConfig.serialNumber);
}

uint32_t CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY;

    // Проверка условия, что не был снят запрос на закрытие сессии
    if (client->agents.sessionController.requsts.requestSession != CANFTP_TRUE)
    {
        CanFTP_Client_Agent_SessionController_SetSessionStatus(&(client->agents.sessionController), CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
    }
    else
    {
        // Переход в состояние окончания сессии
        if (client->agents.sessionController.requsts.stopRequest == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_SESSION_FINISHED;
        }
        // Переход в состояние чтения нового блока файла
        else if (client->agents.sessionController.requsts.startBlockRequest == CANFTP_TRUE)
        {
            resultState = CANFTP_CLIENTSTATE_BLOCK_STARTED;
        }
        // Отправка подтверждения окончания обработки блока
        else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.sessionController.repeateAckTrigger)))
        {
            if (CanFTP_IterationsHandler_Handle(&(client->agents.sessionController.repeateAckCounter)))
            {
                CanFTP_Client_MessageSend_BlockControl(client);
            }
        }
    }

    return resultState;
}

void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_Client_Agent_SessionController_ResetBetweenStates(&(client->agents.sessionController));
}

#endif // CLIENT_STATE_BLOCK_NEXTBLOCKREADY
