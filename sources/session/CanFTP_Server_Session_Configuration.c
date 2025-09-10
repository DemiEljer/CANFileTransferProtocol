/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CanFTP_Server_Session_Configuration.h"

/*
    Сбросить конфигурацию
*/
void CanFTP_Server_Session_Configuration_Reset(CanFTP_Server_Session_Configuration_t* configuration)
{
    configuration->registrationInterval = CANFTP_SERVER_SESSION_REGISTRATION_INTERVAL;
    configuration->registrationRepeateCount = CANFTP_SERVER_SESSION_REGISTRATION_COUNT;
    configuration->sessionControlInterval = CANFTP_SERVER_SESSION_SESSIONCONTROL_INTERVAL;
    configuration->sessionControlRepeateCount = CANFTP_SERVER_SESSION_SESSIONCONTROL_COUNT;
    configuration->repeateBlockCount = CANFTP_SERVER_SESSION_BLOCKREPEATE_COUNT;
    configuration->blockControlInterval = CANFTP_SERVER_SESSION_BLCOCKCONTROL_INTERVAL;
    configuration->blockControlRepeateCount = CANFTP_SERVER_SESSION_BLOCKCONTROL_COUNT;
    configuration->frameSendingInterval = CANFTP_SERVER_SESSION_FRAMESENDING_INTERVAL;
    configuration->clientSessionRepeateInterval = CANFTP_SERVER_SESSION_SESSIONCONTROL_ACKREPEATE_INTERVAL;
    configuration->clientSessionRepeateCount = CANFTP_SERVER_SESSION_SESSIONCONTROL_ACKREPEATE_COUNT;
    configuration->clientBlockRepeateInterval = CANFTP_SERVER_SESSION_BLOCKCONTROL_ACKREPEATE_INTERVAL;
    configuration->clientBlockRepeateCount = CANFTP_SERVER_SESSION_BLOCKCONTROL_ACKREPEATE_COUNT;
}
/*
    Скопировать конфигурацию
*/
void CanFTP_Server_Session_Configuration_Copy(CanFTP_Server_Session_Configuration_t* to, CanFTP_Server_Session_Configuration_t* from)
{
    to->registrationInterval = from->registrationInterval;
    to->registrationRepeateCount = from->registrationRepeateCount;
    to->sessionControlInterval = from->sessionControlInterval;
    to->sessionControlRepeateCount = from->sessionControlRepeateCount;
    to->repeateBlockCount = from->repeateBlockCount;
    to->blockControlInterval = from->blockControlInterval;
    to->blockControlRepeateCount = from->blockControlRepeateCount;
    to->frameSendingInterval = from->frameSendingInterval;
    to->clientSessionRepeateInterval = from->clientSessionRepeateInterval;
    to->clientSessionRepeateCount = from->clientSessionRepeateCount;
    to->clientBlockRepeateInterval = from->clientBlockRepeateInterval;
    to->clientBlockRepeateCount = from->clientBlockRepeateCount;
}
