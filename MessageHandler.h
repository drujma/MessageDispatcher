#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "IMessageHandler.h"
#include <QDataStream>

struct IMessage;

template<typename T, typename MessageType>
class MessageHandler : public IMessageHandler
{
    typedef void(T::*FunctionPtr)(const MessageType& msg);
    T* caller_;
    FunctionPtr callback_;
public:
    MessageHandler(T* caller, FunctionPtr callback) :
        caller_(caller), callback_(callback) { }

    void handle(const QByteArray& data)
    {
        QDataStream stream(data);
        MessageType message;
        //message.deserialize(stream);

        (caller_->*callback_)(message);
    }
};

#endif // MESSAGEHANDLER_H
