#include "btprobabilisticselectornode.h"

//REGISTER_NODETYPE(btProbSelectorNode)

#include <QDebug>
#include <QDateTime>

btProbSelectorNode::btProbSelectorNode()
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}

bool btProbSelectorNode::run()
{
    float randNum;
    float intStart = 0.0;
    float scale = 1.0;
    int inc = 0;

    for(int i = 0; i < probStats.count(); i++){
        randNum = ((float)qrand()/RAND_MAX) * scale;
        foreach(StatNode node, probStats)
        {

            if(node.visited == false){
                if(intStart < randNum && randNum <= (node.wp + intStart)){
                   qDebug() << intStart << " < " << randNum << " <= " << node.wp + intStart << " YES";
                    if(parentNode()->child(inc)->runBehavior()){
                        foreach(StatNode node, probStats){
                            node.visited = false;
                        }
                        return true;
                    }else{
                        node.visited = true;
                        scale -= node.wp;
                    }
                }
               qDebug() << intStart << " < " << randNum << " <= " << node.wp + intStart << " NO";
                 intStart += node.wp;
            }
            inc += 1;
        }
        intStart = 0.0;
        inc = 0;
    }

    foreach(StatNode node, probStats){
        node.visited = 0;
    }

    return false;
}

void btProbSelectorNode::appendingChild(int index)
{
    StatNode newNode;
    probStats.insert(index,newNode);
}

void btProbSelectorNode::removingChild(int index)
{
    probStats.removeAt(index);
}

void btProbSelectorNode::childrenAdded()
{
    ///fixme skal l�ses fra xml
    int count = probStats.count();
    if(count > 0){
        foreach(StatNode node, probStats){
            node.p = (1.0 / count);
        }
    }
}


#include "btprobabilisticselectornode.moc"