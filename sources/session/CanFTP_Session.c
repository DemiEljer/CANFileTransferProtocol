#include "CanFTP_Session.h"

/*
    Сбросить сессию
*/
void CanFTP_Session_Reset(CanFTP_Session_t *session)
{
    CanFTP_Session_Configuratio_Reset(&(session->configuration));
    CanFTP_Session_FileBlock_Reset(&(session->block));
}
