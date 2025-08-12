#ifndef CANFTP_SERVER_SESSION_AGENTS_H_
#define CANFTP_SERVER_SESSION_AGENTS_H_

#include "CanFTP_Server_Session_Agents_Defines.h"

/*
    Сбросить контроллер регистрации
*/
void CanFTP_Server_Session_Agent_RegistrationConroller_Reset(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent);
/*
    Перейти к следующему клиенту
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_MoveToNextClient(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount);
/*
    Проверить, остались ли клиенты для регистрации
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount);

#endif // CANFTP_SERVER_SESSION_AGENTS_H_
