#include "CommunicationController.h"
#include "ICommunicationAdapter.h"
#include <QDebug>

CommunicationController::CommunicationController(ICommunicationAdapter* adapter) :
    adapter_(adapter)
{
    adapter_->setMessageReceiver(this);
}

CommunicationController::~CommunicationController()
{
    qDeleteAll(handlers_);
}

void CommunicationController::handle(unsigned messageID, const QByteArray& data)
{
    IMessageHandler* handler  = handlers_.value(messageID, nullptr);

    if(handler){
        handler->handle(data);
    }else{
        qWarning() << "Handler not registered for messageID" << messageID;
    }
}

void CommunicationController::handle(unsigned sender, unsigned messageID, const QByteArray& data)
{
    //TODO add handle with sender
    IMessageHandler* handler  = handlers_.value(messageID, nullptr);

    if(handler){
        handler->handle(data);
    }else{
        qWarning() << "Handler not registered for messageID" << messageID;
    }
}

void CommunicationController::send(const IMessage& message)
{
    adapter_->send(message);
}

void CommunicationController::send(unsigned destination, const IMessage& message)
{
    adapter_->send(destination, message);
}

void CommunicationController::setMessageEnabled(unsigned messageID, bool isEnabled)
{
    adapter_->setMessageEnabled(messageID, isEnabled);
}
