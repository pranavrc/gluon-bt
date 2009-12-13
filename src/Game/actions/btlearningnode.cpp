#include "btlearningnode.h"
#include "statnode.h"
#include "btprobabilisticselectornode.h"

REGISTER_NODETYPE(btLearningNode)

        btLearningNode::btLearningNode()
{
}

bool btLearningNode::run(btCharacter *self)
{
    qDebug() << "learning";
    if(parentNode()->child(0)->runBehavior(self))
    {
        calculateProbability();
        return true;
    }else{
        calculateProbability();
        return false;
    }
}

void btLearningNode::calculateProbability()
{
    //tag højde for hvor mange gange en node har været prøvet (tries)
    combined_p = 0.0;
    qDebug() << "calculateProbability 1";


    foreach(StatNode* n, ((btProbSelectorNode*) parentNode()->child(0)->type())->probStats){
        qDebug() << "calculateProbability something";
        n->old_p = n->p;
        n->p = (1.0 - alpha) * (n->succes + 1.0) + alpha * (1.0/(1.0 + n->fail)) + n->old_p * gamma;
        combined_p += n->p;
    }

    // skal splittes op i de enkelte nodes
    if(combined_p > 0.0){
        foreach(StatNode* n, ((btProbSelectorNode*) parentNode()->child(0)->type())->probStats){
            n->wp = n->p / combined_p;
        }
    }

    qDebug() << "-------------------: " << tries;
    foreach(StatNode* n, ((btProbSelectorNode*) parentNode()->child(0)->type())->probStats){
        qDebug() << n->wp;
    }
   qDebug() << "-------------------";
    qDebug() << "";
}

#include "btlearningnode.moc"
