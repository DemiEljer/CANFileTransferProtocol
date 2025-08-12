#ifndef CANFTP_SESSIONSTATUS_H_
#define CANFTP_SESSIONSTATUS_H_

/*
    Статус состояния сессии
*/
typedef enum _CanFTP_SessionStatus
{
    /*
        Нормальное состояние сессии
    */
    CANFTP_SESSIONSTATUS_OK = 0,
    /*
        Ошибка. Логика работы устройства не была заблокирована
    */
    CANFTP_SESSIONSTATUS_ERROR_LOGICISNOTLOCKED = 1,
    /*
        Ошибка. Сессия была преждевременно выключена
    */
    CANFTP_SESSIONSTATUS_ERROR_ALRAMTERMINATED = 2,
    /*
        Ошибка. Нарущена последовательность протокола
    */
    CANFTP_SESSIONSTATUS_ERROR_WRONGSEQUENCE = 3,
    /*
        Ошибка. Потеряна связь
    */
    CANFTP_SESSIONSTATUS_ERROR_LOSTCONNECTION = 4,
    /*
        Ошибка. Превышено количество итераций ответа серверу
    */
    CANFTP_SESSIONSTATUS_ERROR_ACKCOUNTOVERCOME = 5,
    /*
        Ошибка. Невозможно сконфигурировать сессию
    */
    CANFTP_SESSIONSTATUS_ERROR_CONFIGURATIONFAILED = 6,
    /*
        Ошибка. Нарушена последовательность блоков
    */
    CANFTP_SESSIONSTATUS_ERROR_BLOCKSEQUENCEFAILED = 7,
    /*
        Ошибка. Не была завершена обработка блока
    */
    CANFTP_SESSIONSTATUS_ERROR_BLOCKUNFINISHED = 8,
    /*
        Ошибка. Не был передан весь файл
    */
    CANFTP_SESSIONSTATUS_ERROR_FILEUNFINISHED = 9,
    /*
        Ошибка. Не осталось ни одного клиента
    */
    CANFTP_SESSIONSTATUS_ERROR_NOCLIENTSLEFT = 10,
    /*
        Ошибка. Превышено количество отправляемых запросов
    */
    CANFTP_SESSIONSTATUS_ERROR_REQUESTSSENDINGOVERCONE = 11,
    /*
        Ошибка. Превышено количество отправляемых запросов
    */
    CANFTP_SESSIONSTATUS_ERROR_REGISTRATIONFAIL = 12,

} CanFTP_SessionStatus_t;

#endif // CANFTP_SESSIONSTATUS_H_
