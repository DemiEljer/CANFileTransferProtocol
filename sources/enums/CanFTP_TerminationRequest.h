#ifndef CANFTP_TERMINATIONREQUEST_H_
#define CANFTP_TERMINATIONREQUEST_H_

/*
    Запрос на терминирование работы логики
*/
typedef enum _CanFTP_TerminationRequest
{
    CANFTP_TERMINATIONREQUEST_NOTERMINATION = 0,
    CANFTP_TERMINATIONREQUEST_TERMINATE     = 1,
    CANFTP_TERMINATIONREQUEST_RELEASE       = 2
} CanFTP_TerminationRequest_t;

#endif // CANFTP_TERMINATIONREQUEST_H_