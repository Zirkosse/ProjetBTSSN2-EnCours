#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDataStream>
#include <QString>
#include <QSettings>
#include <QAbstractSocket>
#include <QIODevice>
#include <QByteArray>
#include <iostream>
#include "stdio.h"
#include "classecheckpoints.h"
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <iostream>
#include <QDateTime>
#include <QTextStream>
#include <QDateTime>
#include "cdatabase.h"



using namespace std;
QString _dsn= "Driver={Sql Server};Server=192.168.1.21;Port=1433;Database=ClubCar;Uid=sa;Pwd=sapassword;";

cdatabase base(_dsn);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    timer = new QTimer(this);

//Creation Tableau Application

    ui->tableWidget->setRowCount(1000);
    ui->tableWidget->setColumnCount(2);
    QStringList list;
    list << "Adresse"<<"TAG";
    ui->tableWidget->setHorizontalHeaderLabels(list);


//Connexion Antenne
    socket->connectToHost("192.168.0.190", 6000,QIODevice::ReadWrite,QAbstractSocket::IPv4Protocol);
    //Accès BDD

// SLOT Utile lors des differente action de l'antenne
    connect(timer,SIGNAL(timeout()),this,SLOT(onReadyWrite()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    timer ->start(1000);

}


void MainWindow::onReadyWrite()
{
//Calcul du checksum
    char message[6]={0x04,0x10,0x01};
    ClasseCheckpoints Checksum;
    int Chaine = Checksum.clcChecksum(message,3);
    char message2[] = {0x04,0x10,0x01,0,0};
    message2[3]=(Chaine & 0x00FF);
    message2[4]=(Chaine>>8);
//Envoie du paquet au checkpoints pour analyser la zone
    QByteArray paquet = message2;
    socket->write(paquet);

}

void MainWindow::donneesRecues()
{
    int y,i =0;
    QString Tags;
    QTableWidgetItem *tag;
    QTableWidgetItem *Addr;
    tag =new QTableWidgetItem;
    Addr =new QTableWidgetItem;
    QString Tag;
    QString Vide;
    QString Date=QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");//Date systeme

    //Convertion de la réponse de l'antenne sous forme Hexadecimale.

    QByteArray Chaine=socket->readAll().toHex();
    ClasseCheckpoints Lecture;
    Tag= Lecture.DataReceive(Chaine);
    if (Tag=="")
    {
        return;
    }
    //***********************************************************
    //Ecriture des informations dans l'application
    QString Add=QString::fromUtf8(Chaine);

    QString Adresse = Add[2]+""+Add[3];
    //QString Add2=Chaine[3];
    qDebug()<< Adresse;
    tag->setText(Tag);
    Addr->setText(Adresse);
    ui->tableWidget->setItem(0,0,Addr);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0,1,tag);
    //**********************************************************
    while(Tag[i]!='\0')
    {
        if(Tag[i]!=',')
        {
            Tags[i]=Tag[i];
            i++;
        }else if(Tag[i]==',')
        {
            base.Historisation(Tags,Date,Adresse);
            i++;
            Tags="";

        }
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

