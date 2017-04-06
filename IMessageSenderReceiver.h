#ifndef IMESSAGESENDERRECEIVER_H
#define IMESSAGESENDERRECEIVER_H

#include "IMessageReceiver.h"
#include "IMessageSender.h"

class IMessageSenderReceiver : public IMessageSender, public IMessageReceiver
{
public:
    // IMessageReceiver interface
    virtual void handle(unsigned messageID, const QByteArray& data) = 0;
    virtual void handle(unsigned sender, unsigned messageID, const QByteArray& data) = 0;

    // IMessageSender interface
    virtual void send(const IMessage& message) = 0;
    virtual void send(unsigned destination, const IMessage& message) = 0;
};

#endif // IMESSAGESENDERRECEIVER_H
