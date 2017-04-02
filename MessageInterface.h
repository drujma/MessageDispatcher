#ifndef MESSAGEINTERFACE_H
#define MESSAGEINTERFACE_H

#include "Message.h"
#include <QDataStream>
#include <QObject>
#include <QVariant>

class HmiInterface
{
    Q_GADGET
public:
    enum MessageIdentifier
    {
        MESSAGE_ID_UNKNOWN = 0,
        MESSAGE_ID_SYSTEM_STATUS = 1,
    };
    Q_ENUM(MessageIdentifier)

    static QString toString(unsigned id);

    static MessageIdentifier toEnum(const QString& id);
};


struct SystemStatus : public Message
{

    unsigned state;
    unsigned status;
    unsigned configuration;

    SystemStatus()
    {
        id = HmiInterface::MESSAGE_ID_SYSTEM_STATUS;
    }

    // Message interface
    void serialize(QDataStream &stream) const
    {
        stream << state
               << status
               << configuration;
    }

    void deserialize(QDataStream &stream)
    {
        stream >> state
               >> status
               >> configuration;
    }
};


#endif // MESSAGEINTERFACE_H
