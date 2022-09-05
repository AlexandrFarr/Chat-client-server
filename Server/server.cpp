#include "server.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any,2323))
    {
        qDebug()<<"Server has started. Listening to port 2323";
    }else
    {
        qDebug()<<"Server failed to start ";
    }
}

void Server::incomingConnection(qintptr socketDecription)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDecription);

    connect(socket,&QTcpSocket::readyRead,this,&Server::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Server::sockDisc);

    //add to QVector
    sockets.push_back(socket);

    qDebug()<<"Client connected.."<<socketDecription;

    QString str = "successful connection ";
    sendToClient(str);

    qDebug()<<"send to client status - YES";

}

void Server::sockReady()
{
    //add the socket from which the request was made
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    if(in.status() == QDataStream::Ok)
    {
       qDebug()<<"read..";
       QString str;
       in>>str;
       qDebug()<<str;
       sendToClient(str);

    }else
    {
        qDebug()<<"QDataStream error..";
    }
}

void Server::sockDisc()
{
    qDebug()<<"Disconnect";
    QTcpSocket* socket = static_cast<QTcpSocket*>(QObject::sender());
    sockets.removeOne(socket);
    socket->deleteLater();

}

void Server::sendToClient(QString str)
{
   data.clear();
   QDataStream out(&data, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_5_12);
   out<<str;
   //socket->write(data);
   for(int i =0;i<sockets.size();i++)
   {
       sockets[i]->write(data);
   }
}
