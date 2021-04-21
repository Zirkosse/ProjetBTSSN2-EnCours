#ifndef CDATABASE_H
#define CDATABASE_H
#include "QString"
class cdatabase
{
public:
    cdatabase(QString _dsn);
    QString LoadSettings();
    bool Historisation(QString Tags,QString Date,QString Add);
private:
    QString dsn;
};
#endif // CDATABASE_H
