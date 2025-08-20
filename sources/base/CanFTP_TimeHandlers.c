#include "CanFTP_TimeHandlers.h"

// Структура обработчика времени
static CanFTP_TimeHandler_t _timeHandler = 
{
    .currentTimeGetter = 0
};

/*
    Проинициализировать функция получения текущей метки времени
*/
void CanFTP_TimeHandlers_InitCurrentTimeGetter(CanFTP_GetTimeMarkHandler_t timeGetter)
{
    _timeHandler.currentTimeGetter = timeGetter;
}
/*
    Получить текущее значение метки времени
*/
CanFTP_TimeMark_t CanFTP_TimeHandlers_GetCurrentTime()
{
    if (_timeHandler.currentTimeGetter == 0)
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_TIME_NOTTIMEGETTER);

        return 0;
    }
    else
    {
        return _timeHandler.currentTimeGetter();
    }
}
/*
    Обновить метку времени
*/
void CanFTP_TimeHandlers_UpdateTimeMark(CanFTP_TimeMark_t *timeMark)
{
    *(timeMark) = CanFTP_TimeHandlers_GetCurrentTime();
}
/*
    Получить количество времени прошедшего с момента записи метки времени
*/
uint32_t CanFTP_TimeHandlers_GetDeltaTime(CanFTP_TimeMark_t *timeMark)
{
    CanFTP_TimeMark_t currentTimeMark = CanFTP_TimeHandlers_GetCurrentTime();

    if (currentTimeMark < *(timeMark))
    {
        CanFTP_ThrowErrorWithCode(CANFTP_ERROR_TIME_TIMEMARK);

        return 0;
    }
    else
    {
        return currentTimeMark - *(timeMark);
    }
}
/*
    Проверить, что интервал времени прошел
*/
CanFTP_Logical_t CanFTP_TimeHandlers_IntervalHasPessed(CanFTP_TimeMark_t *timeMark, CanFTP_TimeInterval_t timeInterval)
{
    return CanFTP_TimeHandlers_GetDeltaTime(timeMark) >= timeInterval;
}
/*
    Проверить, что интервал времени прошел, и обновить метку времени в данном случае
*/
CanFTP_Logical_t CanFTP_TimeHandlers_IntervalHasPassed_UpdateTimemark(CanFTP_TimeMark_t *timeMark, CanFTP_TimeInterval_t timeInterval)
{
    uint8_t resultFlag = CanFTP_TimeHandlers_IntervalHasPessed(timeMark, timeInterval);

    if (resultFlag)
    {
        CanFTP_TimeHandlers_UpdateTimeMark(timeMark);
    }
}
/*
    Установить значение интевала времени для триггера
*/
void CanFTP_TimeTrigger_SetInterval(CanFTP_TimeTrigger_t *trigger, CanFTP_TimeInterval_t interval)
{
    trigger->timeInterval = interval;
}
/*
    Обновить метку времени в триггере
*/
void CanFTP_TimeTrigger_Update(CanFTP_TimeTrigger_t *trigger)
{
    CanFTP_TimeHandlers_UpdateTimeMark(&(trigger->timeMark));
}
/*
    Сбросить метку времени в триггере
*/
void CanFTP_TimeTrigger_Reset(CanFTP_TimeTrigger_t *trigger)
{
    trigger->timeMark = 0;
}
/*
    Проверить, сработал ли триггер
*/
CanFTP_Logical_t CanFTP_TimeTrigger_HasFired(CanFTP_TimeTrigger_t *trigger)
{
    return CanFTP_TimeHandlers_IntervalHasPessed(&(trigger->timeMark), trigger->timeInterval);
}
/*
    Проверить, сработал ли триггер, и обновить его в случае срабатывания
*/
CanFTP_Logical_t CanFTP_TimeTrigger_HasFired_Udpate(CanFTP_TimeTrigger_t *trigger)
{
    return CanFTP_TimeHandlers_IntervalHasPassed_UpdateTimemark(&(trigger->timeMark), trigger->timeInterval);
}
