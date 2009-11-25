#ifndef RELATIVERIGHT_H
#define RELATIVERIGHT_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class relativeRight : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE relativeRight();
    bool run(btCharacter *self);
};


#endif // RELATIVERIGHT_H
