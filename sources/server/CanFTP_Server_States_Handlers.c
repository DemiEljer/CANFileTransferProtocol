#include "CanFTP_Server_States_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Server_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);


}
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Server_IterationEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    
}

/*
    Обработка состояния IDLE
*/
#ifndef SERVER_STATE_IDLE_
#define SERVER_STATE_IDLE_

void CanFTP_Server_State_IDLE_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    DEBUG_SERVER_PRINTSTATE("IDLE")
}
uint32_t CanFTP_Server_State_IDLE_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    CanFTP_ServerState_t resultState = CANFTP_SERVERSTATE_IDLE;
    
    if (CanFTP_Server_SessionsCollection_CheckActiveSessions(&(server->sessions)) > 0)
    {
        CanFTP_Server_Agent_PingControler_Reset(&(server->agents.pingController));

        resultState = CANFTP_SERVERSTATE_SESSION;
    }
    // Переход в логику процесса Ping
    else if (server->agents.pingController.requsts.requestPinging == CANFTP_TRUE)
    {
        resultState = CANFTP_SERVERSTATE_PING;
    }

    return resultState;
}
void CanFTP_Server_State_IDLE_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    
}

#endif // SERVER_STATE_IDLE_

/*
    Обработка состояния PING
*/
#ifndef SERVER_STATE_PING_
#define SERVER_STATE_PING_

void CanFTP_Server_State_PING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);
    // Очистка списка клиентов
    CanFTP_Server_ClientsCollection_Clear(&(server->clients));

    DEBUG_SERVER_PRINTSTATE("PING")
}
uint32_t CanFTP_Server_State_PING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    CanFTP_ServerState_t resultState = CANFTP_SERVERSTATE_PING;
    // Выход из процесса Ping
    if (server->agents.pingController.requsts.requestPinging != CANFTP_TRUE)
    {
        resultState = CANFTP_SERVERSTATE_IDLE;
    }
    // Циклическая отправка сообщений запроса
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(server->agents.pingController.reapeateSendingTrigger)))
    {
        CanFTP_Server_MessageSend_Ping(server);
    }

    return resultState;
}
void CanFTP_Server_State_PING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    CanFTP_Server_Agent_PingControler_Reset(&(server->agents.pingController));
    CanFTP_Server_ClientsCollection_Verify(&(server->clients));
}

#endif // SERVER_STATE_PING_

/*
    Обработка состояния SESSION
*/
#ifndef SERVER_STATE_SESSION_
#define SERVER_STATE_SESSION_

void CanFTP_Server_State_SESSION_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    DEBUG_SERVER_PRINTSTATE("SESSION")
}
uint32_t CanFTP_Server_State_SESSION_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    CanFTP_ServerState_t resultState = CANFTP_SERVERSTATE_SESSION;

    // Вызов логики остановки у даления сессий
    if (server->agents.pingController.requsts.terminationRequest == CANFTP_TERMINATIONREQUEST_RELEASE)
    {
        CanFTP_Server_SessionsCollection_TerminateActiveSessions(&(server->sessions));
    }
    // Вызов или проверка активных сессий
    if (server->controls.doesServerInvokeSessions == CANFTP_TRUE)
    {
        // Вызлов логик созданных сессий
        if (CanFTP_Server_SessionsCollection_InvokeSessionsOrDispose(&(server->sessions)) == 0)
        {
            resultState = CANFTP_SERVERSTATE_IDLE;
        }
    }
    else
    {
        if (CanFTP_Server_SessionsCollection_CheckActiveSessions(&(server->sessions)) == 0)
        {
            resultState = CANFTP_SERVERSTATE_IDLE;
        }
    }

    return resultState;
}
void CanFTP_Server_State_SESSION_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_t* server = (CanFTP_Server_t*)(fms);

    
}

#endif // SERVER_STATE_SESSION_
