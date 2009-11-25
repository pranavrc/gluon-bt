#ifndef RELATIVEFORWARD_H
#define RELATIVEFORWARD_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class relativeForward : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE relativeForward();
    bool run(btCharacter *self);
};


#endif // RELATIVEFORWARD_H
