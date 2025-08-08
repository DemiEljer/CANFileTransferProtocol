#include "CanFTP_Client_Agents.h"

/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_Agent_PingControler_Reset(CanFTP_Client_Agent_PingControler_t *agent)
{
    agent->pingResponsesAck[0] = CANFTP_FALSE;
    agent->pingResponsesAck[1] = CANFTP_FALSE;
    CanFTP_TimeTrigger_SetInterval(&(agent->reapeateSendingTrigger), CANFTP_CLIENT_PING_MININTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->reapeateSendingTrigger));
    CanFTP_TimeTrigger_SetInterval(&(agent->coolingDownTrigger), CANFTP_CLIENT_PING_TIMEOUT);
    CanFTP_TimeTrigger_Reset(&(agent->coolingDownTrigger));
    agent->requestedMessageIndex = 0x00;
    agent->requsts.requestPinging = CANFTP_FALSE;
}
/*
    Проверка, что были получены подтверждения на все запросы
*/
CanFTP_Logical_t CanFTP_Client_Agent_PingControler_AllAcksAreReceived(CanFTP_Client_Agent_PingControler_t *agent)
{
    return agent->pingResponsesAck[0] == CANFTP_TRUE 
           && agent->pingResponsesAck[1] == CANFTP_TRUE;
}
/*
    Сброс контроллера процесса Ping
*/
void CanFTP_Client_LogicLockController_Reset(CanFTP_Client_LogicLockController_t *agent)
{
    agent->requsts.requestToLockLogic = CANFTP_FALSE;
    agent->statuses.isLocked = CANFTP_FALSE;
}
/*
    Сброс контроллера управления сессией
*/
void CanFTP_Client_SessionController_Reset(CanFTP_Client_SessionController_t *agent)
{
    uint8_t i = 0;

    agent->requsts.requestSession = CANFTP_FALSE;
    agent->requsts.configurationRequest = CANFTP_FALSE;
    agent->requsts.startRequest = CANFTP_FALSE;
    agent->requsts.stopRequest = CANFTP_FALSE;
    agent->requsts.startBlockRequest = CANFTP_FALSE;
    agent->requsts.recievingBlockRequest = CANFTP_FALSE;
    agent->requsts.stopBlockRequest = CANFTP_FALSE;
    agent->requsts.blockFinishAckRecieved = CANFTP_FALSE;
    agent->statuses.sessionStatus = CANFTP_SESSIONSTATUS_OK;
    agent->statuses.sessionHasBeenVerified = CANFTP_FALSE;
    agent->statuses.allBlocksFramesWereRecieved = CANFTP_FALSE;
    agent->statuses.blockHandlingStatus = CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT;
    agent->statuses.resultFileLength = 0;
    agent->statuses.newBlockIsHandling = CANFTP_TRUE;
    // Сброс CRC-суммы
    {
        for (i = 0; i < CANFTP_FILEBLOCK_CRCLENGTH; i++)
        {
            agent->statuses.blockCRC[i] = 0;
        }
    }
    agent->clientAssosiation.deviceCode = 0;
    agent->clientAssosiation.sessionCode = 0;
    CanFTP_TimeTrigger_SetInterval(&(agent->repeateAckTrigger), CANFTP_CLIENT_SEESION_REPEATEACK_INTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->repeateAckTrigger));
    CanFTP_TimeTrigger_SetInterval(&(agent->lostConnectionTrigger), CANFTP_CLIENT_SEESION_LOSTCONNECTION_TIMEOUT);
    CanFTP_TimeTrigger_Reset(&(agent->lostConnectionTrigger));
    CanFTP_IterationsHandler_SetMaxCount(&(agent->repeateAckCounter), CANFTP_CLIENT_SEESION_REPEATEACK_COUNT);
    CanFTP_IterationsHandler_Reset(&(agent->repeateAckCounter));
    CanFTP_Session_Reset(&(agent->session));
}
/*
    Сброс контроллера управления сессией
*/
void CanFTP_Client_SessionController_ResetBlock(CanFTP_Client_SessionController_t *agent)
{
    uint8_t i = 0;
    // Сброс флагов управления чтением блока
    agent->requsts.startBlockRequest = CANFTP_FALSE;
    agent->requsts.recievingBlockRequest = CANFTP_FALSE;
    agent->requsts.stopBlockRequest = CANFTP_FALSE;
    agent->requsts.blockFinishAckRecieved = CANFTP_FALSE;
    agent->statuses.allBlocksFramesWereRecieved = CANFTP_FALSE;
    // Сброс CRC-суммы
    {
        for (i = 0; i < CANFTP_FILEBLOCK_CRCLENGTH; i++)
        {
            agent->statuses.blockCRC[i] = 0;
        }
    }
}
/*
    Установить статус состояния сессии
*/
void CanFTP_Client_SessionController_SetSessionStatus(CanFTP_Client_SessionController_t *agent, CanFTP_SessionStatus_t status)
{
    // Изменить статус в случае, если до этого сессия находилась в рабочем состоянии
    if (agent->statuses.sessionStatus == CANFTP_SESSIONSTATUS_OK)
    {
        agent->statuses.sessionStatus = status;
    }
    // В случае возникновения ошибки, убирается запрос на активацию сессии
    if (agent->statuses.sessionStatus != CANFTP_SESSIONSTATUS_OK)
    {
        agent->requsts.configurationRequest = CANFTP_FALSE;
    }
}
/*
    Сброс флагов управления при переходе в другое состояние
*/
void CanFTP_Client_SessionController_ResetBetweenStates(CanFTP_Client_SessionController_t *agent)
{
    // Сброс счетчика количества повторений
    CanFTP_IterationsHandler_Reset(&(agent->repeateAckCounter));
    // Сброс метки времени генерации ответа
    CanFTP_TimeTrigger_Reset(&(agent->repeateAckTrigger));
}
