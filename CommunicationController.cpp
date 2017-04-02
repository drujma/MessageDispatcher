#include "CommunicationController.h"
#include "MessageInterface.h"

#include "MessageHandler.h"

class MessageReceiver : public IMessageReceiver
{
public:
    MessageReceiver(CommunicationController* controller) : controller_(controller) { }
    template<typename MessageType, typename FunctionPtr>
    void registerMessage(unsigned messageId, FunctionPtr ptr)
    {
        messageHandlers_[messageId] = new MessageHandler<CommunicationController, MessageType>(controller_, ptr);
    }

    void handle(unsigned messageID, const QByteArray &data){
        messageHandlers_[messageID]->handle(data);
    }

private:
    CommunicationController* controller_;
    QMap<unsigned, IMessageHandler*> messageHandlers_;
};

CommunicationController::CommunicationController(QObject *parent) : QObject(parent)
{
    messageReceiver_ = new MessageReceiver(this);

    messageReceiver_->registerMessage<SystemStatus>(HmiInterface::MESSAGE_ID_SYSTEM_STATUS, &CommunicationController::systemStatusReceived);

    connect(&eltIpc_, &EltIpcMock::messageReceived, this, &CommunicationController::messageReceived);
}

void CommunicationController::send(const Message &message)
{
    const QString& messageID(HmiInterface::toString(message.id));

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    message.serialize(stream);

    eltIpc_.send(messageID, data);
}

void CommunicationController::handle(unsigned messageID, const QByteArray &data)
{
    messageReceiver_->handle(messageID, data);
}

void CommunicationController::messageReceived(const QString &messageId, const QByteArray &data)
{
    unsigned id = HmiInterface::toEnum(messageId);
    handle(id, data);
}
