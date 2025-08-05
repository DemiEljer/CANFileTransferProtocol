#include "CanFTP_SofwareVersion.h"

/*
    Скопировать номер версии
*/
void CanFTP_SofwareVersion_Copy(CanFTP_SofwareVersion_t* to, CanFTP_SofwareVersion_t* from)
{
    to->lowerPart = from->lowerPart;
    to->middlePart = from->middlePart;
    to->higherPart = from->higherPart;
}
