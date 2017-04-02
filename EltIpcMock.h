#ifndef ELTIPCMOCK_H
#define ELTIPCMOCK_H

#include <QByteArray>
#include <QDebug>
#include <QObject>

class EltIpcMock : public QObject
{
    Q_OBJECT
public:
    EltIpcMock() { }

    void send(const QString& messageID, const QByteArray& data){
        Q_UNUSED(data)
        qInfo() << "Sending" << messageID;
    }

signals:
    void messageReceived(const QString& messageID, const QByteArray& data);
};

#endif // ELTIPCMOCK_H
