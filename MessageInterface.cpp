#include "MessageInterface.h"

#include <QMetaEnum>

QString HmiInterface::toString(unsigned id)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<MessageIdentifier>();
    QString idString = metaEnum.valueToKey(id);

    return idString;
}

HmiInterface::MessageIdentifier HmiInterface::toEnum(const QString &id)
{
    MessageIdentifier res(MESSAGE_ID_UNKNOWN);

    QMetaEnum metaEnum = QMetaEnum::fromType<MessageIdentifier>();
    bool okConversion = false;
    int enumValue = metaEnum.keyToValue(id.toStdString().c_str(), &okConversion);

    if(okConversion){
        res = static_cast<MessageIdentifier>(enumValue);
    }

    return res;
}
