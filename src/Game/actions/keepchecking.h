#ifndef KEEPCHECKING_H
#define KEEPCHECKING_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class keepChecking : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE keepChecking();
    bool run(btCharacter *self);
};


#endif // KEEPCHECKING_H
