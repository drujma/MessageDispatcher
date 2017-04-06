#ifndef ICOMMUNICATIONADAPTER_H
#define ICOMMUNICATIONADAPTER_H

#include "IMessageSender.h"

class IMessageReceiver;

class ICommunicationAdapter : public IMessageSender
{
    // IMessageSender interface
public:
    virtual void send(const IMessage& message) = 0;
    virtual void send(unsigned destination, const IMessage& message) = 0;
    virtual void setMessageEnabled(unsigned messageID, bool isEnabled) = 0;
    virtual void setMessageReceiver(IMessageReceiver* messageReceiver) = 0;
};

#endif // ICOMMUNICATIONADAPTER_H
