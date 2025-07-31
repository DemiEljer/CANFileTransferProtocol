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

    // Запрос на блокировку логики
    if (client->agents.logicLockController.requsts.requestToLockLogic
        && !client->agents.logicLockController.statuses.isLocked)
    {
        if (client->callbacks.lockLogicRequestCallback != 0)
        {
            client->agents.logicLockController.statuses.isLocked = client->callbacks.lockLogicRequestCallback();
        }
        else
        {
            client->agents.logicLockController.statuses.isLocked = 0x01;
        }
    }
    // Запрос на снятие блокировки логики
    else if (!client->agents.logicLockController.requsts.requestToLockLogic
             && client->agents.logicLockController.statuses.isLocked)
    {
        if (client->callbacks.lockLogicRequestCallback != 0)
        {
            client->agents.logicLockController.statuses.isLocked = !client->callbacks.unlockLogicRequestCallback();
        }
        else
        {
            client->agents.logicLockController.statuses.isLocked = 0x00;
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

}

uint32_t CanFTP_Client_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_IDLE;
    // Переход в состояние Ping
    if (client->agents.pingController.requsts.requestPinging)
    {
        resultState = CANFTP_CLIENTSTATE_PING_RESPONSING;
    }
    // Переход в состояние активной работы протокола
    else if (client->agents.logicLockController.statuses.isLocked)
    {
        resultState = CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
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
    client->agents.pingController.reapeateSendingTrigger.timeInterval = CanFTP_Random_GetNext_Range(&(client->agents.random), 10, 100);
}

uint32_t CanFTP_Client_State_PING_RESPONSING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_PING_RESPONSING;

    // Обработка логики выхода из состояния Ping по истечению времени или по снятию запроса
    if (!client->agents.pingController.requsts.requestPinging
        || CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.coolingDownTrigger)))
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
    else if (CanFTP_Client_Agent_PingControler_AllAcksAreReceived(&(client->agents.pingController)))
    {
        resultState = CANFTP_CLIENTSTATE_PING_FINISHED;
    }
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.reapeateSendingTrigger)))
    {

        client->agents.pingController.requestedMessageIndex = 0;
        // Проверка сообщений, необходимых к отправке
        {
            if (!client->agents.pingController.pingResponsesAck[0])
            {
                client->agents.pingController.requestedMessageIndex = 1;
                CanFTP_Client_MessageSend_PingResponse(client);

            }
            if (!client->agents.pingController.pingResponsesAck[1])
            {
                client->agents.pingController.requestedMessageIndex = 2;
                CanFTP_Client_MessageSend_PingResponse(client);
            }
        }

        client->agents.pingController.reapeateSendingTrigger.timeInterval = CanFTP_Random_GetNext_Range(&(client->agents.random), 10, 100);
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

}

uint32_t CanFTP_Client_State_PING_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    CanFTP_ClientState_t resultState = CANFTP_CLIENTSTATE_PING_FINISHED;
    // Обработка логики выхода из состояния Ping по истечению времени или по снятию запроса
    if (!client->agents.pingController.requsts.requestPinging
        || CanFTP_TimeTrigger_HasFired_Udpate(&(client->agents.pingController.coolingDownTrigger)))
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

    
}

uint32_t CanFTP_Client_State_PROTOCOL_ACTIVE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE;
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


}

uint32_t CanFTP_Client_State_SESSION_REGISTRATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_REGISTRATED;
}

void CanFTP_Client_State_SESSION_REGISTRATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
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

    
}

uint32_t CanFTP_Client_State_SESSION_CONFIGURED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_CONFIGURED;
}

void CanFTP_Client_State_SESSION_CONFIGURED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
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

    
}

uint32_t CanFTP_Client_State_SESSION_STARTED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_STARTED;
}

void CanFTP_Client_State_SESSION_STARTED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
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

    
}

uint32_t CanFTP_Client_State_SESSION_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_SESSION_FINISHED;
}

void CanFTP_Client_State_SESSION_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_SESSION_FINISHED_

/*
    Обработка состояния BLOCK_RECIEVING
*/
#ifndef CLIENT_STATE_BLOCK_RECIEVING_
#define CLIENT_STATE_BLOCK_RECIEVING_

void CanFTP_Client_State_BLOCK_RECIEVING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

uint32_t CanFTP_Client_State_BLOCK_RECIEVING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_RECIEVING;
}

void CanFTP_Client_State_BLOCK_RECIEVING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
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

    
}

uint32_t CanFTP_Client_State_BLOCK_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_FINISHED;
}

void CanFTP_Client_State_BLOCK_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
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

    
}

uint32_t CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY;
}

void CanFTP_Client_State_BLOCK_NEXTBLOCKREADY_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    
}

#endif // CLIENT_STATE_BLOCK_NEXTBLOCKREADY_

/*
    Обработка состояния BLOCK_NEXTBLOCKREADY
*/
#ifndef CLIENT_STATE_PROTOCOL_DISABLING_
#define CLIENT_STATE_PROTOCOL_DISABLING_

void CanFTP_Client_State_PROTOCOL_DISABLING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

uint32_t CanFTP_Client_State_PROTOCOL_DISABLING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);

    return CANFTP_CLIENTSTATE_PROTOCOL_DISABLING;
}

void CanFTP_Client_State_PROTOCOL_DISABLING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Client_t* client = (CanFTP_Client_t*)(fms);


}

#endif // CLIENT_STATE_PROTOCOL_DISABLING_

