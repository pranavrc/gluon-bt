#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include "btlib.h"
#include "btlib_export.h"

#include <QtCore/QObject>
#include <QtCore/QStack>
#include <QtCore/QList>
#include <QtCore/QQueue>
#include <QtCore/QMultiHash>
#include <QtCore/QPair>
#include "btperception.h"

struct ProbNode;

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition)
    Q_PROPERTY(QVector3D orientation READ orientation WRITE setOrientation)
    
    public:
        btCharacter();
        ~btCharacter();
        
        void setBehaviorTree(btNode* behaviorTree);
        
        void think();

        /**
        * The character's position in the world
        */
        QVector3D position() const;
        void setPosition(const QVector3D& newPosition);
        
        /**
         * The character's orientation in the world.
         */
        QVector3D orientation() const;
        void setOrientation(const QVector3D& newOrientation);
    
        /**
         * Accessor for the character's perception system
         */
        btPerception* perception();
    private:
        void stopParallelExecution(btNode * currentNode, QStack<btNode*>* parentStack);
        void clearExecution();
        
        btNode* m_behaviortree;
        
        //used for scheduler exectution
        QQueue<btNode::status> m_nodesStatusQueue;
        QQueue<QPair<QStack<btNode*>*, QStack<btNode*>*> > m_currentNodeStackQueue;
        QQueue<QStack<int> > m_currentChildStackQueue;
        
        //used for probselectors
        QHash<QStack<btNode*>*, QStack<QList<ProbNode*> > > m_visitedProbChildrenHash;
        
        //used for parallels
        QMultiHash<QStack<btNode*>*, QList<btNode::status>* > m_parallelNodeStatusHash;
        
        QVector3D m_position;
        QVector3D m_orientation;
        btPerception* m_perception;
};

#endif // _BTCHARACTER_H_
