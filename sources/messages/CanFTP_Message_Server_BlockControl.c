#include "CanFTP_Message_Server_BlockControl.h"

/*
    Распаковка сообщения
*/
void CanFTP_Message_Server_BlockControl_Unpack(CanFTP_Message_Server_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    if (CanFTP_CanMessage_Verify(messageCan, CANFTP_MESSAGE_ID_SERVER_BLOCKCONTROL, CANFTP_MESSAGE_DLC_SERVER_BLOCKCONTROL))
    {
        messageModel->sessionCode = CanFTP_CanIdentifier_UnpackSessionCode(messageCan->id);
        messageModel->messageType = (CanFTP_Message_Server_BlockControl_Type_t)(messageCan->data[0] & 0x0F);

        if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_START)
        {
            messageModel->start.blockIndex = (CanFTP_BloclIndex_t)(
                  (CanFTP_BloclIndex_t)((messageCan->data[0] >> 4) & 0x0F) 
                | (CanFTP_BloclIndex_t)((messageCan->data[1] >> 0) & 0xFF) << 4
                | (CanFTP_BloclIndex_t)((messageCan->data[2] >> 0) & 0xFF) << 12
                | (CanFTP_BloclIndex_t)((messageCan->data[3] >> 0) & 0xFF) << 20
                | (CanFTP_BloclIndex_t)((messageCan->data[4] >> 0) & 0x0F) << 28
            );
            messageModel->start.blockLength = (CanFTP_BlockLength_t)(
                  (CanFTP_BlockLength_t)((messageCan->data[4] >> 4) & 0x0F) 
                | (CanFTP_BlockLength_t)((messageCan->data[5] >> 0) & 0x7F) << 4
            );
        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FINISH)
        {
            messageModel->start.blockIndex = (CanFTP_BloclIndex_t)(
                  (CanFTP_BloclIndex_t)((messageCan->data[0] >> 4) & 0x0F) 
                | (CanFTP_BloclIndex_t)((messageCan->data[1] >> 0) & 0xFF) << 4
                | (CanFTP_BloclIndex_t)((messageCan->data[2] >> 0) & 0xFF) << 12
                | (CanFTP_BloclIndex_t)((messageCan->data[3] >> 0) & 0xFF) << 20
                | (CanFTP_BloclIndex_t)((messageCan->data[4] >> 0) & 0x0F) << 28
            );
        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FEEDBACKACK)
        {
            messageModel->feedbackAck.deviceCode = (CanFTP_DeviceIdentifier_t)(
                  (CanFTP_DeviceIdentifier_t)((messageCan->data[0] >> 4) & 0x0F) 
                | (CanFTP_DeviceIdentifier_t)((messageCan->data[1] >> 0) & 0x0F) << 4
            );
            messageModel->feedbackAck.blockHandlingStatus = (CanFTP_ClientBlockHandlingStatus_t)((messageCan->data[1] >> 4) & 0x0F);
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
void CanFTP_Message_Server_BlockControl_Pack(CanFTP_Message_Server_BlockControl_t* messageModel, CanFTP_CanMessage_t* messageCan)
{
    uint8_t messageDataVector[8] = {0}; 
    
    // Упаковка данных
    {
        messageDataVector[0] |= messageModel->messageType & 0x0F;

        if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_START)
        {
            messageDataVector[0] |= ((messageModel->start.blockIndex >> 0) & 0x0F) << 4;
            messageDataVector[1] |= ((messageModel->start.blockIndex >> 4) & 0xFF) << 0;
            messageDataVector[2] |= ((messageModel->start.blockIndex >> 12) & 0xFF) << 0;
            messageDataVector[3] |= ((messageModel->start.blockIndex >> 20) & 0xFF) << 0;
            messageDataVector[4] |= (((messageModel->start.blockIndex >> 28) & 0x0F) << 0) 
                                    | (((messageModel->start.blockLength >> 0) & 0x0F) << 4);
            messageDataVector[5] |= (((messageModel->start.blockLength >> 4) & 0x7F) << 0);
        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FINISH)
        {
            messageDataVector[0] |= ((messageModel->finish.blockIndex >> 0) & 0x0F) << 4;
            messageDataVector[1] |= ((messageModel->finish.blockIndex >> 4) & 0xFF) << 0;
            messageDataVector[2] |= ((messageModel->finish.blockIndex >> 12) & 0xFF) << 0;
            messageDataVector[3] |= ((messageModel->finish.blockIndex >> 20) & 0xFF) << 0;
            messageDataVector[4] |= (((messageModel->finish.blockIndex >> 28) & 0x0F) << 0);
        }
        else if (messageModel->messageType == CANFT_MESSAGE_SERVER_BLOCKCONTROL_FEEDBACKACK)
        {
            messageDataVector[0] |= ((messageModel->feedbackAck.deviceCode >> 0) & 0x0F) << 4;
            messageDataVector[1] |= (((messageModel->feedbackAck.deviceCode >> 4) & 0x0F) << 0)
                                    | (((messageModel->feedbackAck.blockHandlingStatus >> 0) & 0x0F) << 4);
        }
        else
        {
            CanFTP_ThrowError();
        }
    }

    CanFTP_CanMessage_Init(messageCan
        , CanFTP_CanIdentifier_PackWithSessionCode(CANFTP_MESSAGE_ID_SERVER_BLOCKCONTROL, messageModel->sessionCode)
        , CANFTP_MESSAGE_DLC_SERVER_BLOCKCONTROL
        , messageDataVector
    );
}
