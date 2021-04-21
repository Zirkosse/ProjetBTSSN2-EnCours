#ifndef CLASSECHECKPOINTS_H
#define CLASSECHECKPOINTS_H
#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL  0x8408
#include "QString"

class ClasseCheckpoints
{
public:
    ClasseCheckpoints();
    unsigned int clcChecksum(char * pucY, unsigned char ucX);
    QString HexToAscii(QString p);
    QString DataReceive(QByteArray Chaine);

};

#endif // CLASSECHECKPOINTS_H
