#include "btprobabilisticselectornode.h"

REGISTER_NODETYPE(btProbSelectorNode)

#include <QDebug>
#include <QDateTime>
#include <QVariant>

btProbSelectorNode::btProbSelectorNode()
{
    qsrand(QDateTime::currentDateTime().toTime_t());

}

bool btProbSelectorNode::run(btCharacter *self)
{

    float randNum;
    float intStart = 0.0;
    float scale = 1.0;
    int inc = 0;

    for(int i = 0; i < probStats.count(); i++){
        qDebug() << qrand();
        randNum = ((float)qrand()/RAND_MAX) * scale;
        qDebug() << "RandNum: " << randNum;
        foreach(StatNode *node, probStats)
        {
            if(node->visited == false){
                if(intStart < randNum && randNum <= (node->wp + intStart)){
                   qDebug() << intStart << " < " << randNum << " <= " << node->wp + intStart << " YES";
                   if(stopFlag()){  // måske kan man gøre det til en del af runBehavior ?
                       setStopFlag(false);
                       return false;
                   }
                    if(parentNode()->child(inc)->runBehavior(self)){
                        qDebug("behavior run succes");
                        node->succes += 1;
                        foreach(StatNode *node, probStats){
                            node->visited = false;
                        }
                        return true;
                    }else{
                        qDebug("behavior run fail");
                        node->fail += 1;
                        node->visited = true;
                        scale -= node->wp;
                    }
                }
                 intStart += node->wp;
            }
            inc += 1;
        }
        intStart = 0.0;
        inc = 0;
    }

    foreach(StatNode *node, probStats){
        node->visited = 0;
    }

    return false;
}

void btProbSelectorNode::appendingChild(int index)
{
    StatNode *newNode = new StatNode();
    //property(""
    probStats.insert(index,newNode);
}

void btProbSelectorNode::removingChild(int index)
{
    probStats.removeAt(index);
}

void btProbSelectorNode::childrenAdded()
{

    ///fixme skal læses fra xml
    int count = probStats.count();
    int i = 0;
    if(count > 0){

        if(property("weights").isValid()){
            QList<QVariant> probs = property("weights").toList();
            foreach(StatNode *node, probStats){
                node->p = (1.0 / count);
                node->wp = probs.at(i).toDouble(); //(1.0 / count);
                i++;
            }
        }else{
            foreach(StatNode *node, probStats){
                node->p = (1.0 / count);
                node->wp = (1.0 / count);
            }
        }
    }
}

