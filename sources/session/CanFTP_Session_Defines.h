#ifndef CANFTP_SESSION_DEFINES_H_
#define CANFTP_SESSION_DEFINES_H_

#include "CanFTP_Session_Configuration.h"
#include "CanFTP_Session_ClientAssosiation.h"
#include "CanFTP_Session_FileBLock_Defines.h"

/*
    Структура сессии передачи файла
*/
typedef struct _CanFTP_Session
{
    // Конфигурация сессии
    CanFTP_Session_Configuration_t configuration;
    // Текущий блок файла
    CanFTP_Session_FileBlock_t block;

} CanFTP_Session_t;

#endif // CANFTP_SESSION_DEFINES_H_
