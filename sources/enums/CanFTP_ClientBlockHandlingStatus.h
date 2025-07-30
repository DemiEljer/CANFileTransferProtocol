#ifndef CANFTP_CLIENTBLOCKHANDLINGSTATUS_H_
#define CANFTP_CLIENTBLOCKHANDLINGSTATUS_H_

/*
    Статусы обработки блока
*/
typedef enum _CanFTP_ClientBlockHandlingStatus
{
    // Блок принят
    CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKISRECIEVED = 0,
    // Часть субблоков не принято
    CANFTP_CLIENTBLOCKHANDLINGSTATUS_SUBBLOCKESMISSING = 1,
    // Повторная отправка блока
    CANFTP_CLIENTBLOCKHANDLINGSTATUS_BLOCKREPEAT = 2,
    // Ошибка обработки блока
    CANFTP_CLIENTBLOCKHANDLINGSTATUS_FAILED = 3

} CanFTP_ClientBlockHandlingStatus_t; 

#endif // CANFTP_CLIENTBLOCKHANDLINGSTATUS_H_
