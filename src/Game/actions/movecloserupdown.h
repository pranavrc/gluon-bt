#ifndef MOVECLOSERUPDOWN_H
#define MOVECLOSERUPDOWN_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveCloserUpDown : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserUpDown();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERUPDOWN_H
