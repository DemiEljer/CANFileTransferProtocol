#ifndef CANFTP_CLIENTSESSIONFINISHSTATUS_H_
#define CANFTP_CLIENTSESSIONFINISHSTATUS_H_

/*
    Статусы завершения сессии передачи файла
*/
typedef enum _CanFTP_ClientSessionFinishStatus
{
    // Сессия успешно завершена
    CANFTP_CLIENTSESSIONFINISHSTATUS_SUCCESSFULLY = 0,
    // Сессия завершена с ошибкой
    CANFTP_CLIENTSESSIONFINISHSTATUS_FAILED = 1,
    // Сессия отклонена
    CANFTP_CLIENTSESSIONFINISHSTATUS_REJECTED = 2,

} CanFTP_ClientSessionFinishStatus_t; 

#endif // CANFTP_CLIENTSESSIONFINISHSTATUS_H_
