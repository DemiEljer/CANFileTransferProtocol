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
