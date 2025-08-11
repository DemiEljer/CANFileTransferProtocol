#include "CanFTP_Client_Session.h"

/*
    Сбросить сессию
*/
void CanFTP_Client_Session_Reset(CanFTP_Client_Session_t *session)
{
    CanFTP_Session_Configuratio_Reset(&(session->configuration));
    CanFTP_Session_FileBlock_Reset(&(session->block));
}
