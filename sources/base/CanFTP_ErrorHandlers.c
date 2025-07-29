#include "CanFTP_ErrorHandlers.h"

// Обработчик ошибок
static CanFTO_ErrorHandler_t _errorHandler = 
{
    .enentHandler = 0
};

/*
    Вызвать обработчик ошибок
*/
void CanFTP_ThrowError()
{
    if (_errorHandler.enentHandler != 0)
    {
        _errorHandler.enentHandler(0);
    }
}
/*
    Вызвать обработчик ошибок с конкретным кодом
*/
void CanFTP_ThrowErrorWithCode(uint8_t errorCode)
{
    if (_errorHandler.enentHandler != 0)
    {
        _errorHandler.enentHandler(errorCode);
    }
}
/*
    Проинициализовать обработчик ошибок
*/
void CanFTP_InitErrorHandler(CanFTP_ErrorThrowEvent_t handler)
{
    _errorHandler.enentHandler = handler;
}
