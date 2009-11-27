#ifndef BTLEARNINGNODE_H
#define BTLEARNINGNODE_H

#include <QObject>

#include "../gluon-bt-lib/btlib.h"
#include "btlib_export.h"

class btLearningNode : public btNodeType
{
    Q_OBJECT
    
public:
    Q_INVOKABLE btLearningNode();
    bool run(btCharacter *self);
    void calculateProbability();
private:
    float combined_p;
    float alpha;
    float gamma;
    int tries;
};

#endif // BTLEARNINGNODE_H
