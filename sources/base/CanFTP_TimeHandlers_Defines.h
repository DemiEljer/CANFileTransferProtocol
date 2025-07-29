#ifndef CANFTP_TIMEHANDLERS_DEFINES_H_
#define CANFTP_TIMEHANDLERS_DEFINES_H_

#include "CanFTP_ErrorHandlers.h"

// Тип метки времени
typedef uint32_t CanFTP_TimeMark_t;
// Тип времененного интервала
typedef uint32_t CanFTP_TimeInterval_t;
// Тип метода получения текущей метки времени
typedef CanFTP_TimeMark_t (*CanFTP_GetTimeMarkHandler_t)(void);

/*
    Структура триггера времени
*/
typedef struct _CanFTP_TimeTrigger
{
    // Метка времени
    CanFTP_TimeMark_t timeMark;
    // Интервал времени срабатывания триггера
    CanFTP_TimeInterval_t timeInterval;
    
} CanFTP_TimeTrigger_t;
/*
    Структура для взаимодействия с параметрами времени
*/
typedef struct _CanFTP_TimeHandler
{
    // Функция получения текущей метки времени
    CanFTP_GetTimeMarkHandler_t currentTimeGetter;

} CanFTP_TimeHandler_t;

#endif // CANFTP_TIMEHANDLERS_DEFINES_H_