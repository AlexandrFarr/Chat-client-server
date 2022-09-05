#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;


public slots:
    //описывает действия в случае присоединения нового клиента,где дискриптор- уникальный номер нашего соединения
    void incomingConnection(qintptr socketDecription);
    void sockReady();
    //new
    void sockDisc();

private:
    QList<QTcpSocket*> sockets;
    //QVector<QTcpSocket*> sockets;
    QByteArray data;
    //sending data to the client
    void sendToClient(QString str);

};

#endif // SERVER_H
