#include "CanFTP_IterationsHandler.h"

/*
    Сбросить контроллер количества повторений
*/
void CanFTP_IterationsHandler_Reset(CanFTP_IterationsHandler_t *controller)
{
    controller->currentIterationsCount = 0;
}
/*
    Установить максимальное количество повторений
*/
void CanFTP_IterationsHandler_SetMaxCount(CanFTP_IterationsHandler_t *controller, CanFTP_IterationCounter_t count)
{
    controller->maxIterationsCount = count;
}
/*
    Установить максимальное количество повторений
*/
CanFTP_Logical_t CanFTP_IterationsHandler_Handle(CanFTP_IterationsHandler_t *controller)
{
    controller->currentIterationsCount++;

    CanFTP_IterationsHandler_CheckCount(controller);
}
/*
    Проверить количество пройденных итераций
*/
CanFTP_Logical_t CanFTP_IterationsHandler_CheckCount(CanFTP_IterationsHandler_t *controller)
{
    return controller->currentIterationsCount > controller->maxIterationsCount;
}
