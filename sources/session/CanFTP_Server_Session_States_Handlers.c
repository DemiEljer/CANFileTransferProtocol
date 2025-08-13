#include "CanFTP_Server_Session_States_Handlers.h"

/*
    Обработчик события изменения состояния конечным автоматом
*/
void CanFTP_Server_Session_StateChanedEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}
/*
    Обработчик события вызова итерации логики работы
*/
void CanFTP_Server_Session_IterationEventHandler(CanFTP_FinalStateMachine_t *fms)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    if (CanFTP_Server_Session_IsActive(session))
    {
        // Проверить выполнение условий клиентами
        CanFTP_Server_Session_ClientsCollection_Check(&(session->clients));
        // Проверка, что сессия не опустела
        if (!CanFTP_Server_Session_ClientsCollection_CheckIsNotDisposedLeft(&(session->clients)))
        {
            CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_NOCLIENTSLEFT);
        }
    }
}

#ifndef SERVER_SESSION_STATE_CREATED_
#define SERVER_SESSION_STATE_CREATED_
/*
    Обработка состояния CREATED
*/

void CanFTP_Server_Session_State_CREATED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}

uint32_t CanFTP_Server_Session_State_CREATED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_CREATED;
    // Обработка запроса запуска сессии
    if (session->requests.startRequest == CANFTP_TRUE)
    {
        if (session->statuses.clientsAreInited == CANFTP_TRUE
            && session->statuses.fileIsInited == CANFTP_TRUE)
        {
            // Проверка параметров конфигурации сессии
            if (CanFTP_Server_Session_ClientsCollection_GetCount(&(session->clients)) == 0
                || session->fileConfiguration.fileLength == 0
                || session->fileConfiguration.maxBlockLength == 0)
            {
                resultState = CANFTP_SESSIONSTATE_FINISHED;
            }
            // В случае, если есть кому и что передавать, то переходим к регистрации клиентов
            else
            {
                resultState = CANFTP_SESSIONSTATE_REGISTRATING;
            }
        }
        else
        {
            CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_CONFIGURATIONFAILED);
        }
    }
    else if (session->requests.stopRequest == CANFTP_TRUE)
    {
        resultState = CANFTP_SESSIONSTATE_FINISHED;
    }

    return resultState;
}

void CanFTP_Server_Session_State_CREATED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_CREATED_

/*
    Обработка состояния REGISTRATING
*/
#ifndef SERVER_SESSION_STATE_REGISTRATING_
#define SERVER_SESSION_STATE_REGISTRATING_

void CanFTP_Server_Session_State_REGISTRATING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_TimeTrigger_SetInterval(&(session->agents.registrationConrtoller.sendMessageTrigger), session->configuration.registrationInterval);
    CanFTP_IterationsHandler_SetMaxCount(&(session->agents.registrationConrtoller.sendMessageCounter), session->configuration.registrationRepeateCount);
    // Подготовка клиентов к сессии
    CanFTP_Server_Session_ClientsCollection_Prepare(&(session->clients));
    // Обновление параметров отправки сообщений
    CanFTP_Server_Session_ClientsCollection_UpdateSendingParams(&(session->clients)
        , session->configuration.registrationInterval
        , session->configuration.registrationRepeateCount);
}

uint32_t CanFTP_Server_Session_State_REGISTRATING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_REGISTRATING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Если есть кого регистрировать
    else if (CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(&(session->agents.registrationConrtoller), session->clients.clientsCount))
    {
        CanFTP_Server_Session_Client_t* currentClient = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), session->agents.registrationConrtoller.clientIndex);

        if (currentClient != CANFTP_NULL)
        {
            if (currentClient->statuses.isConfigurated
                || !CanFTP_Server_Session_Client_IsInSession(currentClient))
            {
                // В случае, если клиент зарегистрирован или вышел из сессии, переходим к другому
                CanFTP_Server_Session_Agent_RegistrationConroller_MoveToNextClient(&(session->agents.registrationConrtoller), session->clients.clientsCount);
            }
            else if (CanFTP_TimeTrigger_HasFired_Udpate(&(currentClient->repeateSendingTrigger)))
            {
                // В противном случае, производим циклическую отправку сообщений регистрации
                if (CanFTP_IterationsHandler_Handle(&(currentClient->repeateSendingCounter)))
                {
                    CanFTP_Server_Session_MessageSend_Registration(session);
                }
            }
        }
        else
        {
            CanFTP_ThrowError();
        }
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsRegistrationAndDelete(&(session->clients)))
    {
        resultState = CANFTP_SESSIONSTATE_CONFIGURING;
    }
    
    return resultState;
}

void CanFTP_Server_Session_State_REGISTRATING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);


}

#endif // SERVER_SESSION_STATE_CREATED_

/*
    Обработка состояния CONFIGURING
*/
#ifndef SERVER_SESSION_STATE_CONFIGURING_
#define SERVER_SESSION_STATE_CONFIGURING_

void CanFTP_Server_Session_State_CONFIGURING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    // Обновление параметров отправки сообщений
    CanFTP_Server_Session_Agent_SessionConroller_UpdateSendingParams(&(session->agents.sessionController)
        , session->configuration.sessionControlInterval
        , session->configuration.sessionControlRepeateCount);
}

uint32_t CanFTP_Server_Session_State_CONFIGURING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_CONFIGURING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsConfiguration(&(session->clients)))
    {
        resultState = CANFTP_SESSIONSTATE_STARTING;
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.sessionController.sendMessageTrigger)))
    {
        // Проверка количества уже отправленных сообщений
        if (CanFTP_IterationsHandler_Handle(&(session->agents.sessionController.sendMessageCounter)))
        {
            CanFTP_Server_Session_MessageSend_SessionControl(session);
        }
        else
        {
            // В случае, если были пройдены все этапы конфигурации, то удаляем всех не прошедших этап клиентов
            CanFTP_Server_Session_ClientsCollection_DeleteAllUnconfugured(&(session->clients));
        }
    }

    return resultState;
}

void CanFTP_Server_Session_State_CONFIGURING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_CONFIGURING_

/*
    Обработка состояния STARTING
*/
#ifndef SERVER_SESSION_STATE_STARTING_
#define SERVER_SESSION_STATE_STARTING_

void CanFTP_Server_Session_State_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    // Обновление параметров отправки сообщений
    CanFTP_Server_Session_Agent_SessionConroller_UpdateSendingParams(&(session->agents.sessionController)
        , session->configuration.sessionControlInterval
        , session->configuration.sessionControlRepeateCount);
}

uint32_t CanFTP_Server_Session_State_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_STARTING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsSessionStarted(&(session->clients)))
    {
        resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.sessionController.sendMessageTrigger)))
    {
        // Проверка количества уже отправленных сообщений
        if (CanFTP_IterationsHandler_Handle(&(session->agents.sessionController.sendMessageCounter)))
        {
            CanFTP_Server_Session_MessageSend_SessionControl(session);
        }
        else
        {
            // В случае, если были пройдены все этапы конфигурации, то удаляем всех не прошедших этап клиентов
            CanFTP_Server_Session_ClientsCollection_DeleteAllUnstarted(&(session->clients));
        }
    }
    
    return resultState;
}

void CanFTP_Server_Session_State_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_STARTING_

/*
    Обработка состояния FINISHING
*/
#ifndef SERVER_SESSION_STATE_FINISHING_
#define SERVER_SESSION_STATE_FINISHING_

void CanFTP_Server_Session_State_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    // Обновление параметров отправки сообщений
    CanFTP_Server_Session_Agent_SessionConroller_UpdateSendingParams(&(session->agents.sessionController)
        , session->configuration.sessionControlInterval
        , session->configuration.sessionControlRepeateCount);
}

uint32_t CanFTP_Server_Session_State_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_FINISHING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsSessionFinished(&(session->clients)))
    {
        resultState = CANFTP_SESSIONSTATE_FINISHED;
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.sessionController.sendMessageTrigger)))
    {
        // Проверка количества уже отправленных сообщений
        if (CanFTP_IterationsHandler_Handle(&(session->agents.sessionController.sendMessageCounter)))
        {
            CanFTP_Server_Session_MessageSend_SessionControl(session);
        }
        else
        {
            // В случае, если были пройдены все этапы конфигурации, то удаляем всех не прошедших этап клиентов
            CanFTP_Server_Session_ClientsCollection_DeleteAllUnfinished(&(session->clients));
        }
    }
    
    return resultState;
}

void CanFTP_Server_Session_State_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_FINISHING_

/*
    Обработка состояния FINISHED
*/
#ifndef SERVER_SESSION_STATE_FINISHED_
#define SERVER_SESSION_STATE_FINISHED_

void CanFTP_Server_Session_State_FINISHED_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    // Обратный вызов завершения сессии
    if (session->callbacks.sessionFinishedCallback != CANFTP_NULL)
    {
        session->callbacks.sessionFinishedCallback(session->server, session, session->status);
    }
}

uint32_t CanFTP_Server_Session_State_FINISHED_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_FINISHED;

    if (session->requests.deleteRequest == CANFTP_TRUE)
    {
        session->statuses.canBeDisposed = CANFTP_TRUE;
    }
    
    return resultState;
}

void CanFTP_Server_Session_State_FINISHED_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_FINISHING_

/*
    Обработка состояния BLOCK_STARTING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_STARTING_
#define SERVER_SESSION_STATE_BLOCK_STARTING_

void CanFTP_Server_Session_State_BLOCK_STARTING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_STARTING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_STARTING_

/*
    Обработка состояния BLOCK_SENDING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_SENDING_
#define SERVER_SESSION_STATE_BLOCK_SENDING_

void CanFTP_Server_Session_State_BLOCK_SENDING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_SENDING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_SENDING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_SENDING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_SENDING_

/*
    Обработка состояния BLOCK_FINISHING
*/
#ifndef SERVER_SESSION_STATE_BLOCK_FINISHING_
#define SERVER_SESSION_STATE_BLOCK_FINISHING_

void CanFTP_Server_Session_State_BLOCK_FINISHING_Enter(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

uint32_t CanFTP_Server_Session_State_BLOCK_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_FINISHING;


    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    
}

#endif // SERVER_SESSION_STATE_BLOCK_FINISHING_
