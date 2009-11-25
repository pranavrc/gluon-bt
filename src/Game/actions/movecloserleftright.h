#ifndef MOVECLOSERLEFTRIGHT_H
#define MOVECLOSERLEFTRIGHT_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"


class moveCloserLeftRight : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE moveCloserLeftRight();
    bool run(btCharacter *self);
};


#endif // MOVECLOSERLEFTRIGHT_H
