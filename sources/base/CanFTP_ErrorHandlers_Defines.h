#ifndef CANFTP_ERRORHANDLERS_DEFINES_H_
#define CANFTP_ERRORHANDLERS_DEFINES_H_

#include "CanFTP_BaseTypes_Defines.h"
#include "CanFTP_ErrorType.h"

// Сигнатура функции вызова обработчика ошибок
typedef void (*CanFTP_ErrorThrowEvent_t)(uint32_t);

/*
    Структура обработчика ошибок
*/ 
typedef struct _CanFTO_ErrorHandler
{   
    // Обработчик события возникновения ошибки
    CanFTP_ErrorThrowEvent_t enentHandler;
    
} CanFTO_ErrorHandler_t;

#endif // CANFTP_ERRORHANDLERS_DEFINES_H_