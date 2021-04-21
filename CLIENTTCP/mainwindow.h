#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QTableWidget>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QTimer *timer ;


    ~MainWindow();

private slots:
    void donneesRecues();
    void onReadyWrite();

private:
    Ui::MainWindow *ui;
    QTcpSocket  *socket;
    quint16 tailleMessage;
    QTableWidget *table;

};

#endif // MAINWINDOW_H
