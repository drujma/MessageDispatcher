#ifndef IMESSAGESENDER_H
#define IMESSAGESENDER_H

struct IMessage;

class IMessageSender
{
public:
    virtual void send(const IMessage& message) = 0;
    virtual void send(unsigned destination, const IMessage& message) = 0;
};

#endif // IMESSAGESENDER_H
