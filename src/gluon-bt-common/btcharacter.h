#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include <QObject>
#include "../gluon-bt-lib/btlib_export.h"

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
public:
        btCharacter();
        ~btCharacter();
};

#endif // _BTCHARACTER_H_
