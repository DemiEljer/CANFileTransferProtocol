#include "CanFTP_Server_Session_Agents.h"

/*
    Сбросить контроллер регистрации
*/
void CanFTP_Server_Session_Agent_RegistrationConroller_Reset(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent)
{
    agent->clientIndex = 0;
    CanFTP_TimeTrigger_SetInterval(&(agent->sendMessageTrigger), CANFTP_SERVER_SESSION_REGISTRATION_INTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->sendMessageTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->sendMessageCounter), CANFTP_SERVER_SESSION_REGISTRATION_COUNT);
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));
}
/*
    Перейти к следующему клиенту
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_MoveToNextClient(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount)
{
    CanFTP_IterationsHandler_Reset(&(agent->sendMessageCounter));

    agent->clientIndex++;

    return CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(agent, clientsCount);
}
/*
    Проверить, остались ли клиенты для регистрации
*/
CanFTP_Logical_t CanFTP_Server_Session_Agent_RegistrationConroller_CheckIfClientsLeft(CanFTP_Server_Session_Agent_RegistrationConroller_t* agent, CanFTP_DeviceCode_t clientsCount)
{
    return agent->clientIndex < clientsCount;
}
