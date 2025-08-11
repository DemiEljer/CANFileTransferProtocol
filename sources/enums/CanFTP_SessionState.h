#ifndef CANFTP_SESSIONSTATE_H_
#define CANFTP_SESSIONSTATE_H_

// Количество состояний конечного автомата состояния сессии
#define CANFTP_SESSIONSTATES_COUNT 9

/*
    Состояния сессии на стороне сервера
*/
typedef enum _CanFTP_SessionState 
{
    // Сессия была создана
    CANFTP_SESSIONSTATE_CREATED = 0,
    // Процесс регистрации клиентов в сессии
    CANFTP_SESSIONSTATE_REGISTRATING = 1,
    // Процесс конфигурации сессии
    CANFTP_SESSIONSTATE_CONFIGURING = 2,
    // Процесс начала сессии
    CANFTP_SESSIONSTATE_STARTING = 3,
    // Процесс завершения сессии
    CANFTP_SESSIONSTATE_FINISHING = 4,
    // Сессия завершила свою работу
    CANFTP_SESSIONSTATE_FINISHED = 5,
    // Процесс начала передачи блока
    CANFTP_SESSIONSTATE_BLOCK_STARTING = 6,
    // Процесс отправки кадров блока
    CANFTP_SESSIONSTATE_BLOCK_SENDING = 7,
    // Процесс завершения завершения передачи блока
    CANFTP_SESSIONSTATE_BLOCK_FINISHING = 8,

} CanFTP_SessionState_t;

#endif // CANFTP_SESSIONSTATE_H_
