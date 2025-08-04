#include "CanFTP_Session_Configuration.h"

/*
    Сбросить конфигурацию сессии
*/
void CanFTP_Session_Configuratio_Reset(CanFTP_Session_Configuration_t *configuration)
{
    configuration->fileLength = 0;
    configuration->pageIndex = 0;
    configuration->repeateAckCount = 0;
    configuration->repeateBlockCount = 0;
    configuration->repeateInterval = 0;
}
