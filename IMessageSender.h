#ifndef IMESSAGESENDER_H
#define IMESSAGESENDER_H

struct Message;

class IMessageSender
{
public:
    virtual void send(const Message& message) = 0;
};

#endif // IMESSAGESENDER_H
