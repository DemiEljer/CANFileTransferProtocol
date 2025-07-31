#include "CanFTP_Client_Agents.h"

/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_Agent_PingControler_Reset(CanFTP_Client_Agent_PingControler_t *agent)
{
    agent->pingResponsesAck[0] = 0x00;
    agent->pingResponsesAck[1] = 0x00;
    agent->reapeateSendingTrigger.timeInterval = 50;
    CanFTP_TimeTrigger_Update(&(agent->reapeateSendingTrigger));
    agent->coolingDownTrigger.timeInterval = 1000;
    CanFTP_TimeTrigger_Update(&(agent->coolingDownTrigger));
    agent->requestedMessageIndex = 0x00;
    agent->requsts.requestPinging = 0x00;
}
/*
    Проверка, что были получены подтверждения на все запросы
*/
CanFTP_Logical_t CanFTP_Client_Agent_PingControler_AllAcksAreReceived(CanFTP_Client_Agent_PingControler_t *agent)
{
    return agent->pingResponsesAck[0] && agent->pingResponsesAck[1];
}
/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_LogicLockController_Reset(CanFTP_Client_LogicLockController_t *agent)
{
    agent->requsts.requestToLockLogic = 0x00;
    agent->statuses.isLocked = 0x00;
}