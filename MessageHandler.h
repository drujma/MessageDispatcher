#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "IMessageHandler.h"
#include <QDataStream>

struct Message;

template<typename T, typename MessageType>
class MessageHandler : public IMessageHandler
{
    typedef void(T::*SignalPtr)(const MessageType& msg);
    T* sender_;
    SignalPtr signalToEmit_;
public:
    MessageHandler(T* sender, SignalPtr signalToEmit) :
        sender_(sender), signalToEmit_(signalToEmit) { }

    void handle(const QByteArray& data)
    {
        QDataStream stream(data);
        MessageType message;
        message.deserialize(stream);

        (sender_->*signalToEmit_)(message);
    }
};

#endif // MESSAGEHANDLER_H
