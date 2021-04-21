#include <QCoreApplication>
#include <QSettings>
#include <iostream>
#include <QDateTime>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "cdatabase.h"
#include "QDebug"
static bool DEBUG = true;
static QString IP;
static QString Port;
static QString Name;
static QString UserID;
static QString Password;
QString sql;

using namespace std;

cdatabase::cdatabase(QString _dsn)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    dsn=_dsn;
    db.setDatabaseName(dsn);
    db.open();
    if(db.isOpen())
    {
        cout << "Connecte"<<endl;
    }
    else
    {
        cout << "Non connecte"<<endl;
}
}

QString cdatabase::LoadSettings()
{
        QSettings settings("config.ini", QSettings::IniFormat);
        QString strDB("Database.Setting/");

        IP = settings.value(strDB + "IP", "").toString();
        Port = settings.value(strDB + "Port", "").toString();
        Name = settings.value(strDB + "Name", "").toString();
        UserID = settings.value(strDB + "UserID", "").toString();
        Password = settings.value(strDB + "Password", "").toString();
    return IP+Port+Name+UserID+Password;
}


bool cdatabase::Historisation(QString Tags,QString Date,QString Add)
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    db.setDatabaseName(dsn);
    db.open();

        sql="INSERT INTO Passage (IDTags,Date,NumCheckpoints) Values ('"+Tags+"'"+","+"'"+Date+"'"+","+Add+")";
        qDebug()<<sql;
        if(db.isOpen())
        {
            QSqlQuery query(db);

            if(!query.exec(sql))
            {
                db.close();
                return false;
            }
            else
            {
                db.close();
                return true;
            }

        }
}


