#ifndef CANFTP_SERVER_SESSION_HELPFUNCTIONS_H_
#define CANFTP_SERVER_SESSION_HELPFUNCTIONS_H_

#include "CanFTP_Server_Session_Defines.h"

/*
    Получить состояние сессии
*/
CanFTP_SessionState_t CanFTP_Server_Session_GetState(CanFTP_Server_Session_t *session);
/*
    Установить статус состояния сессии
*/
void CanFTP_Server_Session_SetStatus(CanFTP_Server_Session_t *session, CanFTP_SessionStatus_t status);
/*
    Находится ли сессия в активном состоянии
*/
CanFTP_SessionState_t CanFTP_Server_Session_IsActive(CanFTP_Server_Session_t *session);

#endif // CANFTP_SERVER_SESSION_HELPFUNCTIONS_H_
