/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_Agents.h"

/*
    Сбросить контроллера процесса Ping
*/
void CanFTP_Server_Agent_PingControler_Reset(CanFTP_Server_Agent_PingControler_t* agent)
{
    CanFTP_TimeTrigger_SetInterval(&(agent->reapeateSendingTrigger), CANFTP_SERVER_PING_INTERVAL);
    CanFTP_TimeTrigger_Reset(&(agent->reapeateSendingTrigger));
    agent->responsingDeviceSerial = 0;
    agent->responsingMessageType = CANFTP_MESSAGE_CLIENT_PINGRESPONSE_RESPONSE1;
    agent->requsts.requestPinging = CANFTP_FALSE;
    agent->requsts.terminationRequest = CANFTP_TERMINATIONREQUEST_NOTERMINATION;
}