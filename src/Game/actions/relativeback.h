#ifndef RELATIVEBACK_H
#define RELATIVEBACK_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class relativeBack : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE relativeBack();
    bool run(btCharacter *self);
};


#endif // RELATIVEBACK_H
