#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "IMessageHandler.h"
#include <QDataStream>

struct Message;

template<typename T, typename MessageType>
class MessageHandler : public IMessageHandler
{
    typedef void(T::*FunctionPtr)(const MessageType& msg);
    T* sender_;
    FunctionPtr signalToEmit_;
public:
    MessageHandler(T* sender, FunctionPtr signalToEmit) :
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
