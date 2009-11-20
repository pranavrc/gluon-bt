#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "../gluon-bt-lib/btlib_export.h"
#include <QDebug>

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
public:
        btCharacter();
        ~btCharacter();
        void hello(){qDebug() << "btCharacter hello";}
};

#endif // _BTCHARACTER_H_
