#ifndef COMMUNICATIONCONTROLLER_H
#define COMMUNICATIONCONTROLLER_H

#include <QMap>

#include "IMessageSenderReceiver.h"
#include "MessageHandler.h"

class ICommunicationAdapter;

class CommunicationController : public IMessageSenderReceiver
{
public:
    explicit CommunicationController(ICommunicationAdapter* adapter);
    virtual ~CommunicationController();

    // IMessageReceiver interface
    virtual void handle(unsigned messageID, const QByteArray& data);
    virtual void handle(unsigned sender, unsigned messageID, const QByteArray& data);

    // IMessageSender interface
    virtual void send(const IMessage& message);
    virtual void send(unsigned destination, const IMessage& message);

    virtual void setMessageEnabled(unsigned messageID, bool isEnabled);

    /*!
     * M is the message type
     * T is the caller
     * F is the function to call
     */
    template<typename M, typename T, typename F>
    void registerHandler(unsigned messageID, T* caller, F callback){
        handlers_[messageID] = new MessageHandler<T, M>(caller, callback);
    }

protected:
    ICommunicationAdapter* adapter_;
    QMap<unsigned, IMessageHandler*> handlers_;
};

#endif // COMMUNICATIONCONTROLLER_H
