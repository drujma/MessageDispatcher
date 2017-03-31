#ifndef MNGCOMMCONTROLLER_H
#define MNGCOMMCONTROLLER_H

#include <QDataStream>
#include <QMap>
#include <QObject>
#include <QDebug>

enum MessageIdentifier
{
    MESSAGE_ID_CONCRETE_MESSAGE = 0,
};

struct IMessage
{
    MessageIdentifier id_;
    virtual void serialize(QDataStream&) const = 0;
    virtual void deserialize(QDataStream&) = 0;
};

template<MessageIdentifier messageId>
struct AbstractMessage : public IMessage
{
    AbstractMessage()
    {
        id_ = messageId;
    }
};

struct ConcreteMessage : public AbstractMessage<MESSAGE_ID_CONCRETE_MESSAGE>
{
    virtual void serialize(QDataStream& stream) const
    {
        qDebug() << Q_FUNC_INFO;
    }

    virtual void deserialize(QDataStream&)
    {
        qDebug() << Q_FUNC_INFO;
    }
};

inline QDataStream& operator<<(QDataStream& in, const ConcreteMessage& msg)
{
    return in;
}

class IMessageHandler
{
public:
    virtual void operator()(const QByteArray&) = 0;
};

class MngCommController : public QObject
{
    Q_OBJECT
public:
    explicit MngCommController(QObject *parent = 0);
    void send(IMessage* msg);
signals:
    void messageNotify(const IMessage& msg);
private:
    QMap<MessageIdentifier, IMessageHandler*> messageToHandler_;
};

#endif // MNGCOMMCONTROLLER_H
