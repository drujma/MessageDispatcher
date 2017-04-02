#ifndef IMESSAGEHANDLER_H
#define IMESSAGEHANDLER_H

class QByteArray;

struct IMessageHandler
{
    virtual void handle(const QByteArray& data) = 0;
};

#endif // IMESSAGEHANDLER_H
