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

    // Общая логика в случае активного состояния сессии
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
    // Вызов событией особождения клиентов
    if (session->callbacks.clientReleaseCallback != CANFTP_NULL)
    {
        CanFTP_DeviceCode_t clientIndex = 0;

        for (clientIndex = 0; clientIndex < session->clients.clientsCount; clientIndex++)
        {
            CanFTP_Server_Session_Client_t* client = CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), clientIndex);
            // Вызов события освобождения клиента
            if (client != CANFTP_NULL
                && client->isDisposeEventCalled == CANFTP_FALSE
                && !CanFTP_Server_Session_Client_IsInSession(client))
            {
                // Выставления флага подтверждения вызова события
                client->isDisposeEventCalled = CANFTP_TRUE;
                // Вызов события
                session->callbacks.clientReleaseCallback(session->server, session, client->serverClient, client->statuses.sessionStatus);
            }
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

    DEBUG_SESSION_PRINTSTATE("CREATED", session->code)
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

    DEBUG_SESSION_PRINTSTATE("REGISTRATING", session->code)
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

    DEBUG_SESSION_PRINTSTATE("CONFIGURING", session->code)
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

    DEBUG_SESSION_PRINTSTATE("STARTING", session->code)
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

    DEBUG_SESSION_PRINTSTATE("FINISHING", session->code)
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

    DEBUG_SESSION_PRINTSTATE("FINISHED", session->code)
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

    CanFTP_Server_Session_Agent_BlockConroller_UpdateSendingParams(&(session->agents.blockController)
        , session->configuration.blockControlInterval
        , session->configuration.blockControlRepeateCount
        , session->configuration.frameSendingInterval
        , session->configuration.repeateBlockCount);

    if (session->agents.blockController.statuses.newBlockIsHanling == CANFTP_TRUE)
    {
        if (session->callbacks.getFileBlockCallback != CANFTP_NULL)
        {
            // Количество запращиваемых байт
            CanFTP_FileLength_t requestingBytesCount = session->fileConfiguration.fileLength - session->agents.blockController.firstBlockByteIndex;
            if (requestingBytesCount > session->fileConfiguration.maxBlockLength)
            {
                requestingBytesCount = session->fileConfiguration.maxBlockLength;
            }
            // Инициализация блока
            CanFTP_Session_FileBlock_Configure(&(session->agents.blockController.fileBlock), session->agents.blockController.currentBlockIndex, requestingBytesCount);
            // Запрос нового блока файла
            session->callbacks.getFileBlockCallback(session->server
                , session
                , &(session->agents.blockController.fileBlock)
                , session->agents.blockController.firstBlockByteIndex
                , requestingBytesCount);
        }
        // Расчет новой CRC-суммы
        CanFTP_Session_FileBlock_CalculateCRC(&(session->agents.blockController.fileBlock), session->agents.blockController.fileBlockCRC);
        // Сброс флага обработки нового блока
        session->agents.blockController.statuses.newBlockIsHanling = CANFTP_FALSE;
    }
    // Сброс параметров перед началом отправки блока
    CanFTP_Server_Session_Agent_BlockConroller_ResetBeforeBlockStart(&(session->agents.blockController));

    DEBUG_SESSION_PRINTSTATE("BLOCK_STARTING", session->code)
}

uint32_t CanFTP_Server_Session_State_BLOCK_STARTING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsBlockStarted(&(session->clients)))
    {
        resultState = CANFTP_SESSIONSTATE_BLOCK_SENDING;
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.blockController.sendControlMessageTrigger)))
    {
        // Проверка количества уже отправленных сообщений
        if (CanFTP_IterationsHandler_Handle(&(session->agents.blockController.sendControlMessageCounter)))
        {
            CanFTP_Server_Session_MessageSend_BlockControl(session);
        }
        else
        {
            // В случае, если были пройдены все этапы конфигурации, то удаляем всех не прошедших этап клиентов
            CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnstarted(&(session->clients));
        }
    }
    
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

    CanFTP_Server_Session_Agent_BlockConroller_UpdateSendingParams(&(session->agents.blockController)
        , session->configuration.blockControlInterval
        , session->configuration.blockControlRepeateCount
        , session->configuration.frameSendingInterval
        , session->configuration.repeateBlockCount);

    DEBUG_SESSION_PRINTSTATE("BLOCK_SENDING", session->code)
}

uint32_t CanFTP_Server_Session_State_BLOCK_SENDING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_SENDING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.blockController.sendDataMessageTrigger)))
    {
        CanFTP_Server_Session_MessageSend_DataFrame(session);

        if (!CanFTP_Session_FileBlock_GetNextUnandledFrameIndex(&(session->agents.blockController.fileBlock)
            , session->agents.blockController.currentFrameIndex
            , &(session->agents.blockController.currentFrameIndex)))
        {
            resultState = CANFTP_SESSIONSTATE_BLOCK_FINISHING;
        }
    }
    
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

    CanFTP_Server_Session_Agent_BlockConroller_UpdateSendingParams(&(session->agents.blockController)
        , session->configuration.blockControlInterval
        , session->configuration.blockControlRepeateCount
        , session->configuration.frameSendingInterval
        , session->configuration.repeateBlockCount);

    DEBUG_SESSION_PRINTSTATE("BLOCK_FINISHING", session->code)
}

uint32_t CanFTP_Server_Session_State_BLOCK_FINISHING_Body(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);

    CanFTP_SessionState_t resultState = CANFTP_SESSIONSTATE_BLOCK_FINISHING;

    if (session->requests.stopRequest == CANFTP_TRUE)
    {
        CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED);

        resultState = CANFTP_SESSIONSTATE_FINISHING;
    }
    // Верификация прошедших регистрацию клиентов
    else if (CanFTP_Server_Session_ClientsCollection_CheckClientsBlockFinished(&(session->clients)))
    {
        if (CanFTP_Server_Session_Agent_BlockConroller_ResetBlockFlagsIfRequested(&(session->agents.blockController)))
        {
            CanFTP_Session_FileBlock_ResetFramesFlags(&(session->agents.blockController.fileBlock));
        }
        // Проверка, что были приняты все субблоки
        if (CanFTP_Session_FileBlock_VerifySubblocks(&(session->agents.blockController.fileBlock)))
        {
            CanFTP_IterationsHandler_Reset(&(session->agents.blockController.sendBlockCounter));
            // Если передан весь файл, то завершаем сессию
            if (CanFTP_Server_Session_Agent_BlockConroller_NextBlock(&(session->agents.blockController)) >= session->fileConfiguration.fileLength)
            {
                resultState = CANFTP_SESSIONSTATE_BLOCK_FINISHING;
            }
            else
            {
                resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;
            }
        }
        else
        {
            if (CanFTP_IterationsHandler_CheckCount(&(session->agents.blockController.sendBlockCounter)))
            {
                resultState = CANFTP_SESSIONSTATE_BLOCK_STARTING;
            }
            else
            {
                CanFTP_Server_Session_SetStatus(session, CANFTP_SESSIONSTATUS_ERROR_BLOCKSENDINGOVERCOME);
            }
        }
    }
    // Проверка триггера времени отправки сообщения
    else if (CanFTP_TimeTrigger_HasFired_Udpate(&(session->agents.blockController.sendControlMessageTrigger)))
    {
        // Проверка количества уже отправленных сообщений
        if (CanFTP_IterationsHandler_Handle(&(session->agents.blockController.sendControlMessageCounter)))
        {
            CanFTP_Server_Session_MessageSend_BlockControl(session);
        }
        else
        {
            // В случае, если были пройдены все этапы конфигурации, то удаляем всех не прошедших этап клиентов
            CanFTP_Server_Session_ClientsCollection_DeleteAllBlockUnfinished(&(session->clients));
        }
    }
    
    return resultState;
}

void CanFTP_Server_Session_State_BLOCK_FINISHING_Leave(CanFTP_FinalStateMachine_t *fms, void* stateModel)
{
    CanFTP_Server_Session_t* session = (CanFTP_Server_Session_t*)(fms);
    // Подготовка к отправке следующего блока
    CanFTP_Server_Session_ClientsCollection_NextBlockReset(&(session->clients));
}

#endif // SERVER_SESSION_STATE_BLOCK_FINISHING_
