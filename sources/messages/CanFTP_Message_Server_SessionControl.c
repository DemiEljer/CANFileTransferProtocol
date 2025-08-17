#include "CanFTP_Message_Server_SessionControl.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Unpack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, CANFTP_MESSAGE_DLC_SERVER_SESSIONCONTROL))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Server_SessionControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {
            messageModel->configuration.pageIndex = (CanFTP_PageIndex_t)(
                  (CanFTP_PageIndex_t)((messageCan->data[0] >> 4) & 0x0F) << 0
                | (CanFTP_PageIndex_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
            messageModel->configuration.fileLength = (CanFTP_FileLength_t)(
                  (CanFTP_FileLength_t)((messageCan->data[1] >> 4) & 0x0F) << 0
                | (CanFTP_FileLength_t)((messageCan->data[2] >> 0) & 0xFF) << 4
                | (CanFTP_FileLength_t)((messageCan->data[3] >> 0) & 0xFF) << 12
                | (CanFTP_FileLength_t)((messageCan->data[4] >> 0) & 0xFF) << 20
                | (CanFTP_FileLength_t)((messageCan->data[5] >> 0) & 0x0F) << 28
            );
            messageModel->configuration.repeateAckCount = (CanFTP_SendingRepeate_t)(
                  (CanFTP_SendingRepeate_t)((messageCan->data[5] >> 4) & 0x0F) << 0
                | (CanFTP_SendingRepeate_t)((messageCan->data[6] >> 0) & 0x0F) << 4
            );
            messageModel->configuration.repeateInterval = (CanFTP_SendingRepeate_t)(
                  (CanFTP_SendingRepeate_t)((messageCan->data[6] >> 4) & 0x0F) << 0
                | (CanFTP_SendingRepeate_t)((messageCan->data[7] >> 0) & 0xFF) << 4
            );
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
        {
            messageModel->finish.sessionStatus = (CanFTP_SessionStatus_t)(
                  (CanFTP_SessionStatus_t)((messageCan->data[0] >> 4) & 0x0F) << 0
                | (CanFTP_SessionStatus_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
            messageModel->finish.newSoftVersion.lowerPart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[1] >> 4) & 0x0F) << 0
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[2] >> 0) & 0x0F) << 4
            );
            messageModel->finish.newSoftVersion.middlePart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[2] >> 4) & 0x0F) << 0
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[3] >> 0) & 0x0F) << 4
            );
            messageModel->finish.newSoftVersion.higherPart = (CanFTP_DeviceSoftwareVersionPart_t)(
                  (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[3] >> 4) & 0x0F) << 0
                | (CanFTP_DeviceSoftwareVersionPart_t)((messageCan->data[4] >> 0) & 0x0F) << 4
            );
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT)
        {
            messageModel->deleteClient.sessionStatus = (CanFTP_SessionStatus_t)(
                  (CanFTP_SessionStatus_t)((messageCan->data[0] >> 4) & 0x0F) << 0
                | (CanFTP_SessionStatus_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
            messageModel->deleteClient.deviceCode = (CanFTP_DeviceCode_t)(
                  (CanFTP_DeviceCode_t)((messageCan->data[1] >> 4) & 0x0F) << 0
                | (CanFTP_DeviceCode_t)((messageCan->data[2] >> 0) & 0x0F) << 4
            );
        }
        else
        {
            CanFTP_ThrowError();
        }
    }
}
/*
    Упаковка сообщения
*/
void CanFTP_Message_Server_SessionControl_Pack(CanFTP_Message_Server_SessionControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_CONFIGURATION)
        {
            CanFTP_SendingRepeate_t repeateAckCount = messageModel->configuration.repeateAckCount > 0xFF ? 0xFF : messageModel->configuration.repeateAckCount;
            CanFTP_SendingRepeateInterval_t repeateInterval = messageModel->configuration.repeateInterval > 0x0FFF ? 0x0FFF : messageModel->configuration.repeateInterval;

            messageDataVector[0] |= ((messageModel->configuration.pageIndex >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->configuration.pageIndex >> 4) & 0x0F) << 0) 
                                    | (((messageModel->configuration.fileLength >> 0) & 0x0F) << 4);
            messageDataVector[2] |= (((messageModel->configuration.fileLength >> 4) & 0xFF) << 0);
            messageDataVector[3] |= (((messageModel->configuration.fileLength >> 12) & 0xFF) << 0);
            messageDataVector[4] |= (((messageModel->configuration.fileLength >> 20) & 0xFF) << 0);
            messageDataVector[5] |= (((messageModel->configuration.fileLength >> 28) & 0x0F) << 0)
                                    | (((repeateAckCount >> 0) & 0x0F) << 4);
            messageDataVector[6] |= (((repeateAckCount >> 4) & 0x0F) << 0)
                                    | (((repeateInterval >> 0) & 0x0F) << 4);
            messageDataVector[7] |= (((repeateInterval >> 4) & 0xFF) << 0);
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_START)
        {
            // Ничего не делаем
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_FINISH)
        {
            messageDataVector[0] |= ((messageModel->finish.sessionStatus >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->finish.sessionStatus >> 4) & 0x0F) << 0) 
                                    | (((messageModel->finish.newSoftVersion.lowerPart >> 0) & 0x0F) << 4);
            messageDataVector[2] |= (((messageModel->finish.newSoftVersion.lowerPart >> 4) & 0x0F) << 0)
                                    | (((messageModel->finish.newSoftVersion.middlePart >> 0) & 0x0F) << 4);
            messageDataVector[3] |= (((messageModel->finish.newSoftVersion.middlePart >> 4) & 0x0F) << 0)
                                    | (((messageModel->finish.newSoftVersion.higherPart >> 0) & 0x0F) << 4);
            messageDataVector[4] |= (((messageModel->finish.newSoftVersion.higherPart >> 4) & 0x0F) << 0);
        }
        else if (messageModel->messageType == CANFTP_MESSAGE_SERVER_SESSIONCONTROL_DELETECLIENT)
        {
            messageDataVector[0] |= ((messageModel->deleteClient.sessionStatus >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->deleteClient.sessionStatus >> 4) & 0x0F) << 0) 
                                    | (((messageModel->deleteClient.deviceCode >> 0) & 0x0F) << 4);
            messageDataVector[2] |= (((messageModel->deleteClient.deviceCode >> 4) & 0x0F) << 0);
        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCode(CANFTP_MESSAGE_ID_SERVER_SESSIONCONTROL, messageModel->sessionCode)
        , CANFTP_MESSAGE_DLC_SERVER_SESSIONCONTROL
        , messageDataVector
    );
}
