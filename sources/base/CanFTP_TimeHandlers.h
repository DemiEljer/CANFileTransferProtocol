/*
 * Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CANFTP_TIMEHANDLERS_H_
#define CANFTP_TIMEHANDLERS_H_

#include "CanFTP_TimeHandlers_Defines.h"

/*
    Проинициализировать функция получения текущей метки времени
*/
void CanFTP_TimeHandlers_InitCurrentTimeGetter(CanFTP_GetTimeMarkHandler_t timeGetter);
/*
    Получить текущее значение метки времени
*/
CanFTP_TimeMark_t CanFTP_TimeHandlers_GetCurrentTime();
/*
    Обновить метку времени
*/
void CanFTP_TimeHandlers_UpdateTimeMark(CanFTP_TimeMark_t *timeMark);
/*
    Получить количество времени прошедшего с момента записи метки времени
*/
CanFTP_TimeInterval_t CanFTP_TimeHandlers_GetDeltaTime(CanFTP_TimeMark_t *timeMark);
/*
    Проверить, что интервал времени прошел
*/
CanFTP_Logical_t CanFTP_TimeHandlers_IntervalHasPessed(CanFTP_TimeMark_t *timeMark, CanFTP_TimeInterval_t timeInterval);
/*
    Проверить, что интервал времени прошел, и обновить метку времени в данном случае
*/
CanFTP_Logical_t CanFTP_TimeHandlers_IntervalHasPassed_UpdateTimeMark(CanFTP_TimeMark_t *timeMark, CanFTP_TimeInterval_t timeInterval);
/*
    Установить значение интевала времени для триггера
*/
void CanFTP_TimeTrigger_SetInterval(CanFTP_TimeTrigger_t *trigger, CanFTP_TimeInterval_t interval);
/*
    Обновить метку времени в триггере
*/
void CanFTP_TimeTrigger_Update(CanFTP_TimeTrigger_t *trigger);
/*
    Сбросить метку времени в триггере
*/
void CanFTP_TimeTrigger_Reset(CanFTP_TimeTrigger_t *trigger);
/*
    Проверить, сработал ли триггер
*/
CanFTP_Logical_t CanFTP_TimeTrigger_HasFired(CanFTP_TimeTrigger_t *trigger);
/*
    Проверить, сработал ли триггер, и обновить его в случае срабатывания
*/
CanFTP_Logical_t CanFTP_TimeTrigger_HasFired_Udpate(CanFTP_TimeTrigger_t *trigger);

#endif // CANFTP_TIMEHANDLERS_H_