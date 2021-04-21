#include "classecheckpoints.h"
#include "QString"
#include "QDebug"
#include "QByteArray"
#define PRESET_VALUE 0xFFFF
#define POLYNOMIAL  0x8408
ClasseCheckpoints::ClasseCheckpoints()
{

}

unsigned int ClasseCheckpoints::clcChecksum(char *pucY, unsigned char ucX)// méthode calculant le CRC !
{
        unsigned char ucI,ucJ;
        unsigned short int  uiCrcValue = PRESET_VALUE;

        for(ucI = 0; ucI < ucX; ucI++)
           {
               uiCrcValue = uiCrcValue ^ *(pucY + ucI);
               for(ucJ = 0; ucJ < 8; ucJ++)
              {
                if(uiCrcValue & 0x0001)
                {
                    uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
                }
                else
                {
                    uiCrcValue = (uiCrcValue >> 1);
                }
            }
        }
        //qDebug()<<uiCrcValue;
    return uiCrcValue;
}

QString ClasseCheckpoints::HexToAscii(QString String)
{
    QByteArray ByteArray1=String.toUtf8();

    const char* chArr1=ByteArray1.constData();

    QByteArray ByteArray2=QByteArray::fromHex(chArr1);

    const char* chArr2=ByteArray2.constData();

    return QString::fromUtf8(chArr2);
}


 QString ClasseCheckpoints::DataReceive(QByteArray Chaine)
{
     QString Tag;
     QString Tags;
     QString Tags1;
     QString Tags2;
     QString Message;
     int i = 0;
     int X = 2;
     ClasseCheckpoints convert;
     int NbTag  = Chaine[9]-'0';
     Tags = Chaine;
     if (NbTag==1)
     {

             Tag=QByteArray::fromHex(Chaine.mid(12,24))+',';

     }
     if (NbTag>1)
     {
                 Tags1=convert.HexToAscii(Chaine.mid(12,24));
                 if(Tags1.mid(0,3)=="EPV")
                 {
                     Tag=Tags1;
                 }
                 while(NbTag>=X)
                 {

                         Tags2=convert.HexToAscii(Chaine.mid(X*26-14,24));

                     if (Tags2.mid(0,3)=="EPV")
                     {
                         Tag=Tag+","+Tags2+',';
                     }

                     X++;
                 }

             i++;
         }
     return Tag;

}

