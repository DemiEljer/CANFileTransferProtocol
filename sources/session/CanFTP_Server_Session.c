#include "CanFTP_Server_Session.h"
#include "CanFTP_Server_Session_States_Handlers.h"

/*
    Проинициализировать сессию
*/
void CanFTP_Server_Session_Init(CanFTP_Server_Session_t *session, void* server, CanFTP_SessionCode_t sessionCode)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    session->server = server;
    session->code = sessionCode;
    session->status = CANFTP_SESSIONSTATUS_OK;
    session->state = (CanFTP_SessionState_t*)&(session->fms.fms.state);
    // Инициализация обработчиков состояний
    {
        session->fms.states[CANFTP_SESSIONSTATE_CREATED].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_CREATED].handlers.enterStateHandler = CanFTP_Server_Session_State_CREATED_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_CREATED].handlers.bodyStateHandler = CanFTP_Server_Session_State_CREATED_Body;
        session->fms.states[CANFTP_SESSIONSTATE_CREATED].handlers.leaveStateHandler = CanFTP_Server_Session_State_CREATED_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_REGISTRATING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_REGISTRATING].handlers.enterStateHandler = CanFTP_Server_Session_State_REGISTRATING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_REGISTRATING].handlers.bodyStateHandler = CanFTP_Server_Session_State_REGISTRATING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_REGISTRATING].handlers.leaveStateHandler = CanFTP_Server_Session_State_REGISTRATING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_CONFIGURING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_CONFIGURING].handlers.enterStateHandler = CanFTP_Server_Session_State_CONFIGURING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_CONFIGURING].handlers.bodyStateHandler = CanFTP_Server_Session_State_CONFIGURING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_CONFIGURING].handlers.leaveStateHandler = CanFTP_Server_Session_State_CONFIGURING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_STARTING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_STARTING].handlers.enterStateHandler = CanFTP_Server_Session_State_STARTING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_STARTING].handlers.bodyStateHandler = CanFTP_Server_Session_State_STARTING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_STARTING].handlers.leaveStateHandler = CanFTP_Server_Session_State_STARTING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_FINISHING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHING].handlers.enterStateHandler = CanFTP_Server_Session_State_FINISHING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHING].handlers.bodyStateHandler = CanFTP_Server_Session_State_FINISHING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHING].handlers.leaveStateHandler = CanFTP_Server_Session_State_FINISHING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_FINISHED].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHED].handlers.enterStateHandler = CanFTP_Server_Session_State_FINISHED_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHED].handlers.bodyStateHandler = CanFTP_Server_Session_State_FINISHED_Body;
        session->fms.states[CANFTP_SESSIONSTATE_FINISHED].handlers.leaveStateHandler = CanFTP_Server_Session_State_FINISHED_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_STARTING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_STARTING].handlers.enterStateHandler = CanFTP_Server_Session_State_BLOCK_STARTING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_STARTING].handlers.bodyStateHandler = CanFTP_Server_Session_State_BLOCK_STARTING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_STARTING].handlers.leaveStateHandler = CanFTP_Server_Session_State_BLOCK_STARTING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_SENDING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_SENDING].handlers.enterStateHandler = CanFTP_Server_Session_State_BLOCK_SENDING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_SENDING].handlers.bodyStateHandler = CanFTP_Server_Session_State_BLOCK_SENDING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_SENDING].handlers.leaveStateHandler = CanFTP_Server_Session_State_BLOCK_SENDING_Leave;

        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_FINISHING].stateModel = CANFTP_NULL;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_FINISHING].handlers.enterStateHandler = CanFTP_Server_Session_State_BLOCK_FINISHING_Enter;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_FINISHING].handlers.bodyStateHandler = CanFTP_Server_Session_State_BLOCK_FINISHING_Body;
        session->fms.states[CANFTP_SESSIONSTATE_BLOCK_FINISHING].handlers.leaveStateHandler = CanFTP_Server_Session_State_BLOCK_FINISHING_Leave;

        CanFTP_FinalStateMachine_Init(&(session->fms.fms), CANFTP_SESSIONSTATES_COUNT, session->fms.states, CANFTP_SESSIONSTATE_CREATED);   
        // Инициализация обработчиков событий
        session->fms.fms.callbacks.changeStateCallback = CanFTP_Server_Session_StateChanedEventHandler;
        session->fms.fms.callbacks.iterationCallback = CanFTP_Server_Session_IterationEventHandler;
    }
    // Сброс запросов
    {
        session->requests.startRequest = CANFTP_FALSE;
        session->requests.stopRequest = CANFTP_FALSE;
        session->requests.deleteRequest = CANFTP_FALSE;
    }
    // Сброс статусов
    {
        session->statuses.canBeDisposed = CANFTP_FALSE;
        session->statuses.clientsAreInited = CANFTP_FALSE;
        session->statuses.fileIsInited = CANFTP_FALSE;
    }
    // Инициализация логики обработки сообшений
    {
        // Инициализация обратного вызова 
        session->callbacks.sendMessageCallback = CANFTP_NULL;
        session->callbacks.sessionFinishedCallback = CANFTP_NULL;
        session->callbacks.getFileBlockCallback = CANFTP_NULL;
        session->callbacks.clientReleaseCallback = CANFTP_NULL;
    }
    // Инициализация агентов
    {
        CanFTP_Server_Session_Agent_RegistrationConroller_Reset(&(session->agents.registrationConrtoller));
        CanFTP_Server_Session_Agent_SessionConroller_Reset(&(session->agents.sessionController));
        CanFTP_Server_Session_Agent_BlockConroller_Reset(&(session->agents.blockController));
    }
    // Сброс параметров клиентов
    {

    }
    CanFTP_Server_Session_Configuration_Reset(&(session->configuration));
    CanFTP_Server_Session_ClientsCollection_Init(&(session->clients));
    CanFTP_Server_Session_FileConfiguration_Reset(&(session->fileConfiguration));
}
/*
    Удалить сессию
*/
void CanFTP_Server_Session_Dispose(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    // Выставление запросов на удаление
    CanFTP_Server_Session_Delete(session);
    // Гарантированное выставление флага, что сессия может быть удалена
    session->statuses.canBeDisposed = CANFTP_TRUE;
    // Удаление клиентов
    CanFTP_Server_Session_ClientsCollection_Dispose(&(session->clients));
}
/*
    Проициализовать клиентов, участвующих в сессии
*/
void CanFTP_Server_Session_InitClients(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t clientsCount, CanFTP_Server_Client_t** serverClients)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    CanFTP_Server_Session_ClientsCollection_InitClients(&(session->clients), session->code, clientsCount, serverClients);
    CanFTP_Server_Session_ClientsCollection_GetSoftVewrsion(&(session->clients), &(session->fileConfiguration.newSoftVersion));

    session->statuses.clientsAreInited = CANFTP_TRUE;
}
/*
    Проициализовать параметры отправляемого файла
*/
void CanFTP_Server_Session_InitFileConfiguration(CanFTP_Server_Session_t *session, CanFTP_PageIndex_t pageIndex, CanFTP_FileLength_t fileLength)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    CanFTP_Server_Session_FileConfiguration_InitBaseParamns(&(session->fileConfiguration)
        , pageIndex
        , fileLength);

    session->statuses.fileIsInited = CANFTP_TRUE;
}
/*
    Проициализовать новую версию программного обеспечения
*/
void CanFTP_Server_Session_InitNewSoftVersion(CanFTP_Server_Session_t *session, CanFTP_SoftwareVersion_t* newSoftVersion)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    CanFTP_SoftwareVersion_Copy(&(session->fileConfiguration.newSoftVersion), newSoftVersion);
}
/*
    Вызов логики сессии
*/
void CanFTP_Server_Session_Invoke(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    CanFTP_FinalStateMachine_Invoke(CanFTP_FinalStateMachine_Cast(session));
}
/*
    Запрос на запуск сессии
*/
void CanFTP_Server_Session_Start(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    session->requests.startRequest = CANFTP_TRUE;
}
/*
    Запрос на остановку сессии
*/
void CanFTP_Server_Session_Stop(CanFTP_Server_Session_t *session)
{       
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    session->requests.stopRequest = CANFTP_TRUE;
}
/*
    Запрос на удаление сессии
*/
void CanFTP_Server_Session_Delete(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return;
    }

    session->requests.stopRequest = CANFTP_TRUE;
    session->requests.deleteRequest = CANFTP_TRUE;
}
/*
    Получить процент завршения работы сессии
*/
float CanFTP_Server_Session_GetCompletingPercent(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return 0.0F;
    }

    if (session->fileConfiguration.fileLength == 0)
    {
        return 1.0F;
    }
    else
    {
        float resultPercent = (float)session->agents.blockController.firstBlockByteIndex / (float)session->fileConfiguration.fileLength;

        if (resultPercent > 1.0F)
        {
            return 1.0F;
        }
        else
        {
            return resultPercent;
        }
    }
}
/*
    Проверить, находится ли сессия в активном состоянии
*/
CanFTP_Logical_t CanFTP_Server_Session_CheckIsActive(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return CANFTP_FALSE;
    }

    return CanFTP_Server_Session_IsActive(session);
}
/*
    Проверить, что сессия может быть удалена
*/
CanFTP_Logical_t CanFTP_Server_Session_CheckCanBeDisposed(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return CANFTP_FALSE;
    }

    return session->statuses.canBeDisposed;
}
/*
    Получить статус сессии
*/
CanFTP_SessionStatus_t CanFTP_Server_Session_GetStatus(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return CANFTP_SESSIONSTATUS_OK;
    }

    return session->status;
}
/*
    Получить количество клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_GetClientsCount(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return 0;
    }

    return session->clients.clientsCount;
}
/*
    Получить количество активных клиентов
*/
CanFTP_DeviceCode_t CanFTP_Server_Session_GetActiveClientsCount(CanFTP_Server_Session_t *session)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return 0;
    }

    return CanFTP_Server_Session_ClientsCollection_GetNotDisposedCount(&(session->clients));
}
/*
    Получить клиента по индексу
*/
CanFTP_Server_Session_Client_t* CanFTP_Server_Session_GetClientByIndex(CanFTP_Server_Session_t *session, CanFTP_DeviceCode_t index)
{
    if (session == CANFTP_NULL)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_SESSION_NULL);

        return CANFTP_NULL;
    }

    return CanFTP_Server_Session_ClientsCollection_GetClientByIndex(&(session->clients), index);
}
