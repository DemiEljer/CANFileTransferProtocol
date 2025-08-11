#include "CanFTP_Server_Session_Configuration.h"

/*
    Сбросить конфигурацию
*/
void CanFTP_Server_Session_Configuration_Reset(CanFTP_Server_Session_Configuration_t* configuration)
{
    configuration->registrationInterval = 100;
    configuration->registrationRepeateCount = 10;
    configuration->sessionControlInterval = 100;
    configuration->sessionControlRepeateCount = 10;
    configuration->repeateBlockCount = 10;
    configuration->blockControlInterval = 50;
    configuration->blockControlRepeateCount = 10;
    configuration->frameSendingInterval = 1;
    configuration->repeateAckInterval = 100;
    configuration->repeateAckCount = 10;
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
    to->repeateAckInterval = from->repeateAckInterval;
    to->repeateAckCount = from->repeateAckCount;
}
