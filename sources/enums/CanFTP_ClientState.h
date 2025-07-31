#ifndef CANFTP_CLIENTSTATE_H_
#define CANFTP_CLIENTSTATE_H_

// Количество состояний конечного автомата клинета
#define CANFTP_CLIENTSTATES_COUNT 12
/*
    Состояния конечного автомата клиента
*/
typedef enum _CanFTP_ClientState
{
    // Состояние ожидания 
    CANFTP_CLIENTSTATE_IDLE = 0,
    // Состояние отправки ответов на сообщение Ping со стороны сервера
    CANFTP_CLIENTSTATE_PING_RESPONSING = 1,
    // Состояние получения всех подтверждений на сообщения Ping со стороны сервера
    CANFTP_CLIENTSTATE_PING_FINISHED = 2,
    // Активное состояние протокола
    CANFTP_CLIENTSTATE_PROTOCOL_ACTIVE = 3,
    // Клиент зарегистрирован в сессии
    CANFTP_CLIENTSTATE_SESSION_REGISTRATED = 4,
    // Сессия сконфигурирована
    CANFTP_CLIENTSTATE_SESSION_CONFIGURED = 5,
    // Сессия перешла в активное состояние
    CANFTP_CLIENTSTATE_SESSION_STARTED = 6,
    // Сессия завершена
    CANFTP_CLIENTSTATE_SESSION_FINISHED = 7,
    // Блок принимает фрагменты блока
    CANFTP_CLIENTSTATE_BLOCK_RECIEVING = 8,
    // Передача блока была закончена
    CANFTP_CLIENTSTATE_BLOCK_FINISHED = 9,
    // Клиент готов принимать следующий блок
    CANFTP_CLIENTSTATE_BLOCK_NEXTBLOCKREADY = 10,
    // Выключение активной логики протокола
    CANFTP_CLIENTSTATE_PROTOCOL_DISABLING = 11

} CanFTP_ClientState_t;

#endif // CANFTP_CLIENTSTATE_H_