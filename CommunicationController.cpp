#include "CommunicationController.h"
#include "MessageInterface.h"

#include "MessageHandler.h"

#include <QCoreApplication>

class MessageReceiver : public IMessageReceiver
{
public:
    MessageReceiver(CommunicationController* controller) : controller_(controller) { }
    template<typename MessageType, typename FunctionPtr>
    void registerMessage(unsigned messageId, FunctionPtr ptr)
    {
        messageHandlers_[messageId] = new MessageHandler<CommunicationController, MessageType>(controller_, ptr);
    }

    void handle(unsigned messageID, const QByteArray &data){
        messageHandlers_[messageID]->handle(data);
    }

private:
    CommunicationController* controller_;
    QMap<unsigned, IMessageHandler*> messageHandlers_;
};

CommunicationController::CommunicationController(QObject *parent) :
    QObject(parent),
    messageReceiver_(new MessageReceiver(this)),
    ipcManager_(new eltipc::IpcManager(true))
{
    ipcManager_->setHostServer("10.180.60.104");
    ipcManager_->configure("DSP_ID_1", QCoreApplication::applicationDirPath() + "/../config.xml");
    ipcManager_->start();

    messageReceiver_->registerMessage<SystemStatus>(HmiInterface::MESSAGE_ID_SYSTEM_STATUS, &CommunicationController::systemStatusReceived);


    connect(ipcManager_, &eltipc::IpcManager::receiveMessage, this, &CommunicationController::messageReceived);
}

CommunicationController::~CommunicationController()
{
    ipcManager_->stop();

    delete messageReceiver_;
    delete ipcManager_;
}

void CommunicationController::send(const Message &message)
{
    const QString& messageID(HmiInterface::toString(message.id));

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    message.serialize(stream);

    ipcManager_->send(messageID, data);
}

void CommunicationController::handle(unsigned messageID, const QByteArray &data)
{
    messageReceiver_->handle(messageID, data);
}

void CommunicationController::messageReceived(const QString &messageId, const QString& appId, const QByteArray &data)
{
    Q_UNUSED(appId)

    unsigned id = HmiInterface::toEnum(messageId);
    handle(id, data);
}
