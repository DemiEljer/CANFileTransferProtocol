#ifndef CANFTP_ERRORHANDLERS_H_
#define CANFTP_ERRORHANDLERS_H_

#include "CanFTP_ErrorHandlers_Defines.h"

/*
    Вызвать обработчик ошибок
*/
void CanFTP_ThrowError();
/*
    Вызвать обработчик ошибок с конкретным кодом
*/
void CanFTP_ThrowErrorWithCode(uint8_t errorCode);
/*
    Проинициализовать обработчик ошибок
*/
void CanFTP_InitErrorHandler(CanFTP_ErrorThrowEvent_t handler);

#endif // CANFTP_ERRORHANDLERS_H_