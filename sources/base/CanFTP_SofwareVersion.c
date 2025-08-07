#include "CanFTP_SofwareVersion.h"

/*
    Сбросить номер версии
*/
void CanFTP_SofwareVersion_Reset(CanFTP_SofwareVersion_t* version)
{
    version->lowerPart = 0;
    version->middlePart = 0;
    version->higherPart = 0;
}
/*
    Скопировать номер версии
*/
void CanFTP_SofwareVersion_Copy(CanFTP_SofwareVersion_t* to, CanFTP_SofwareVersion_t* from)
{
    to->lowerPart = from->lowerPart;
    to->middlePart = from->middlePart;
    to->higherPart = from->higherPart;
}
