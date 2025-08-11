#include "CanFTP_Server.h"
#include "CanFTP_Server_States_Handlers.h"

/*
    Инициализация сервера
*/
void CanFTP_Server_Init(CanFTP_Server_t *server)
{
    server->state = (CanFTP_ServerState_t*)&(server->fms.fms.state);
    // Инициализация обработчиков состояний
    {
        server->fms.states[CANFTP_SERVERSTATE_IDLE].stateModel = CANFTP_NULL;
        server->fms.states[CANFTP_SERVERSTATE_IDLE].handlers.enterStateHandler = CanFTP_Server_State_IDLE_Enter;
        server->fms.states[CANFTP_SERVERSTATE_IDLE].handlers.bodyStateHandler = CanFTP_Server_State_IDLE_Body;
        server->fms.states[CANFTP_SERVERSTATE_IDLE].handlers.leaveStateHandler = CanFTP_Server_State_IDLE_Leave;

        server->fms.states[CANFTP_SERVERSTATE_PING].stateModel = CANFTP_NULL;
        server->fms.states[CANFTP_SERVERSTATE_PING].handlers.enterStateHandler = CanFTP_Server_State_PING_Enter;
        server->fms.states[CANFTP_SERVERSTATE_PING].handlers.bodyStateHandler = CanFTP_Server_State_PING_Body;
        server->fms.states[CANFTP_SERVERSTATE_PING].handlers.leaveStateHandler = CanFTP_Server_State_PING_Leave;

        server->fms.states[CANFTP_SERVERSTATE_SESSION].stateModel = CANFTP_NULL;
        server->fms.states[CANFTP_SERVERSTATE_SESSION].handlers.enterStateHandler = CanFTP_Server_State_SESSION_Enter;
        server->fms.states[CANFTP_SERVERSTATE_SESSION].handlers.bodyStateHandler = CanFTP_Server_State_SESSION_Body;
        server->fms.states[CANFTP_SERVERSTATE_SESSION].handlers.leaveStateHandler = CanFTP_Server_State_SESSION_Leave;

        CanFTP_FinalStateMachine_Init(&(server->fms.fms), CANFTP_SERVERSTATES_COUNT, server->fms.states, CANFTP_SERVERSTATE_IDLE);   
        // Инициализация обработчиков событий
        server->fms.fms.callbacks.changeStateCallback = CanFTP_Server_StateChanedEventHandler;
        server->fms.fms.callbacks.iterationCallback = CanFTP_Server_IterationEventHandler;
    }
    // Инициализация логики обработки сообшений
    {
        // Инициализация обратного вызова 
        server->callbacks.sendMessageCallback = CANFTP_NULL;

        server->messagesHub.clientBlockControlCallback = CanFTP_Server_MessageRecieve_BlockControl;
        server->messagesHub.clientBlockCRCCallback = CanFTP_Server_MessageRecieve_BlockCRC;
        server->messagesHub.clientPingResponseCallback = CanFTP_Server_MessageRecieve_PingResponse;
        server->messagesHub.clientSessionControlCallback = CanFTP_Server_MessageRecieve_SessionControl;
        server->messagesHub.clientSubBlocksStatusesCallback = CanFTP_Server_MessageRecieve_SubBlocksStatuses;
        server->messagesHub.serverBlockControlCallback = CANFTP_NULL;
        server->messagesHub.serverDataFrameCallback = CANFTP_NULL;
        server->messagesHub.serverPingCallback = CANFTP_NULL;
        server->messagesHub.serverPingResponseAckCallback = CANFTP_NULL;
        server->messagesHub.serverRegistrationCallback = CANFTP_NULL;
        server->messagesHub.serverSessionControlCallback = CANFTP_NULL;
    }
    // Инициализация агентов
    {
        CanFTP_Server_Agent_PingControler_Reset(&(server->agents.pingController));
    }
    // Инициализация обратных вызовов
    {
        server->callbacks.clientFoundCallback = CANFTP_NULL;
    }
    CanFTP_Server_Session_Configuration_Reset(&(server->defaultSessionConfiguration));

}
/*
    Вызов логики обработки клиента
*/
void CanFTP_Server_Invoke(CanFTP_Server_t *server)
{
    CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_Cast(server));
}
/*
    Обработка получения сообщений
*/
void CanFTP_Server_RecieveCanMessage(CanFTP_Server_t *server, CanFTP_CanMessage_t* canMessage)
{
    CanFTP_Messages_Hub_RecieveMessage(&(server->messagesHub), canMessage, server);
}
/*
    Запустить процесс Ping
*/
CanFTP_Logical_t CanFTP_Server_StartPing(CanFTP_Server_t *server, CanFTP_Logical_t requestLogicLocking)
{
    if (CanFTP_Server_PingPermition(server))
    {
        server->agents.pingController.requsts.requestPinging = CANFTP_TRUE;
        server->agents.pingController.requsts.terminationRequest = requestLogicLocking == CANFTP_FALSE ? CANFTP_TERMINATIONREQUEST_NOTERMINATION : CANFTP_TERMINATIONREQUEST_TERMINATE;
    }
}
/*
    Запустить процесс разблокировки логик клиентов
*/
CanFTP_Logical_t CanFTP_Server_StartRelease(CanFTP_Server_t *server)
{
    if (CanFTP_Server_PingPermition(server))
    {
        server->agents.pingController.requsts.requestPinging = CANFTP_TRUE;
        server->agents.pingController.requsts.terminationRequest = CANFTP_TERMINATIONREQUEST_RELEASE;
    }
}
/*
    Остановить процесс Ping
*/
void CanFTP_Server_StopPing(CanFTP_Server_t *server)
{
    server->agents.pingController.requsts.requestPinging = CANFTP_FALSE;
}
/*
    Создать экземпляр сессии
*/
CanFTP_Server_Session_t* CanFTP_Server_CreateNewSession(CanFTP_Server_t *server)
{
    if (CanFTP_Server_CreateSessionPermition(server))
    {
        CanFTP_Server_Session_t* newSession = CanFTP_Server_SessionsCollection_CreateNewSession(&(server->sessions), server);
        // В случае, если сессия была успешно создана
        if (newSession != CANFTP_NULL)
        {
            // Инициализация обратных связей
            {
                newSession->callbacks.sendMessageCallback = (CanFTP_Server_Session_MessageSendCallback_t)server->callbacks.sendMessageCallback;
            }
            CanFTP_Server_Session_Configuration_Copy(&(newSession->configuration), &(server->defaultSessionConfiguration));
        }

        return newSession;
    }
    else
    {
        return CANFTP_NULL;
    }
}
