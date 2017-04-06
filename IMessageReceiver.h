#ifndef IMESSAGERECEIVER_H
#define IMESSAGERECEIVER_H

class QByteArray;

class IMessageReceiver
{
public:
    virtual void handle(unsigned messageID, const QByteArray& data) = 0;
    virtual void handle(unsigned sender, unsigned messageID, const QByteArray& data) = 0;
};

#endif // IMESSAGERECEIVER_H
