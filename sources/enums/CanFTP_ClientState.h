#ifndef CANFTP_CLIENTSTATE_H_
#define CANFTP_CLIENTSTATE_H_

// Количество состояний конечного автомата клинета
#define CANFTP_CLIENTSTATES_COUNT 3
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
    CANFTP_CLIENTSTATE_PING_FINISHED = 2
} CanFTP_ClientState_t;

#endif // CANFTP_CLIENTSTATE_H_