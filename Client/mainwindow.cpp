#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);

    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket,&QTcpSocket::disconnected,this,&MainWindow::sockDisk);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotReadyRead()
{

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_12);

    if(in.status() == QDataStream::Ok)
    {
      QString str;
      in>>str;
      ui->textBrowser->append(str);


    }else
    {
        qDebug()<<"read error...";
    }
}

void MainWindow::sockDisk()
{
    socket->close();
    socket->deleteLater();

    socket = new QTcpSocket(this);
}


void MainWindow::on_pushButton_clicked()
{


    QString ip = ui->lineEdit_2->text();
    int port = ui->lineEdit_3->text().toInt();
    socket->connectToHost(ip,port);
}

void MainWindow::SentToServer(QString str)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_12);
    out<<str;
    socket->write(data);
}


void MainWindow::on_pushButton_2_clicked()
{
    SentToServer(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    SentToServer(ui->lineEdit->text());
}


void MainWindow::on_pushButton_3_clicked()
{
    sockDisk();
}

