#ifndef COMMUNICATIONCONTROLLER_H
#define COMMUNICATIONCONTROLLER_H

#include <QObject>
#include "IMessageSender.h"
#include "IMessageReceiver.h"
#include "MessageInterface.h"

#include "IpcManager.h"


class MessageReceiver;

class CommunicationController : public QObject, public IMessageReceiver, public IMessageSender
{
    Q_OBJECT
public:
    explicit CommunicationController(QObject *parent = 0);
    ~CommunicationController();

    // IMessageSender interface
    void send(const Message &message);

    // IMessageReceiver interface
    void handle(unsigned messageID, const QByteArray &data);
signals:
    void systemStatusReceived(const SystemStatus&);
private:
    void messageReceived(const QString& messageId, const QString& appId, const QByteArray& data);
private:
    eltipc::IpcManager* ipcManager_;
    MessageReceiver*    messageReceiver_;
};

#endif // COMMUNICATIONCONTROLLER_H
