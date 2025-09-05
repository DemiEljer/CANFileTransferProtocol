/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_ITERATIONSHANDLER_H_
#define CANFTP_ITERATIONSHANDLER_H_

#include "CanFTP_BaseTypes_Defines.h"

// Тип счетчика количества повторений
typedef uint32_t CanFTP_IterationCounter_t;

/*
    Контроллер количества срабатываний
*/
typedef struct _CanFTP_IterationsHandler
{
    // Текущее количество уже отработанных итераций
    CanFTP_IterationCounter_t currentIterationsCount;
    // Максимальное количество итераций
    CanFTP_IterationCounter_t maxIterationsCount;

} CanFTP_IterationsHandler_t;

/*
    Сбросить контроллер количества повторений
*/
void CanFTP_IterationsHandler_Reset(CanFTP_IterationsHandler_t *controller);
/*
    Установить максимальное количество повторений
*/
void CanFTP_IterationsHandler_SetMaxCount(CanFTP_IterationsHandler_t *controller, CanFTP_IterationCounter_t count);
/*
    Установить максимальное количество повторений
*/
CanFTP_Logical_t CanFTP_IterationsHandler_Handle(CanFTP_IterationsHandler_t *controller);
/*
    Проверить количество пройденных итераций
*/
CanFTP_Logical_t CanFTP_IterationsHandler_CheckCount(CanFTP_IterationsHandler_t *controller);

#endif // CANFTP_ITERATIONSHANDLER_H_
