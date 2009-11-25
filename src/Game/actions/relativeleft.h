#ifndef RELATIVELEFT_H
#define RELATIVELEFT_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class relativeLeft : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE relativeLeft();
    bool run(btCharacter *self);
};


#endif // RELATIVELEFT_H
