#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class changeColor : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE changeColor();
    bool run(btCharacter *self);
};


#endif // CHANGECOLOR_H
