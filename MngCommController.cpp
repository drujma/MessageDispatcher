#include "MngCommController.h"

template<typename MessageType>
class MessageHandler : public IMessageHandler
{
    typedef void(MngCommController::*SignalPtr)(const IMessage& msg);
    MngCommController* sender_;
    SignalPtr signalToEmit_;
public:
    MessageHandler(MngCommController* mngCommController, SignalPtr signalToEmit) :
        sender_(mngCommController), signalToEmit_(signalToEmit) { }

    void operator()(const QByteArray& data)
    {
        QDataStream stream(data);
        MessageType message;
        message.deserialize(stream);

        (sender_->*signalToEmit_)(message);
    }
};

MngCommController::MngCommController(QObject *parent) : QObject(parent)
{
    messageToHandler_[MESSAGE_ID_CONCRETE_MESSAGE] = new MessageHandler<ConcreteMessage>(this, &MngCommController::messageNotify);
}

void MngCommController::send(IMessage* msg)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    msg->serialize(stream);
}

