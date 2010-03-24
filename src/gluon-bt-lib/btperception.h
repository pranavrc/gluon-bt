/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef BTPERCEPTION_H
#define BTPERCEPTION_H

#include <QtCore/QObject>
#include <QVector3D>

#include "btperceptionatom.h"
#include "btperceptionviewcone.h"
#include "btcharacter.h"

Q_DECLARE_METATYPE(QList<btPerceptionViewcone*>);
Q_DECLARE_METATYPE(QList<btPerceptionAtom*>);

class btPerception : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal perceptionLimit READ perceptionLimit WRITE setPerceptionLimit)
    Q_PROPERTY(QList<btPerceptionAtom*> perceptionAtoms READ perceptionAtoms WRITE setPerceptionAtoms)
    Q_PROPERTY(QList<btPerceptionViewcone*> viewCones READ viewCones WRITE setViewCones)
    
    public:
        btPerception(QObject* parent = 0);
        ~btPerception();
        
        /**
         * The limit of the character's perception. If left at 0, the limit will be the entire level.
         * Please note that this can potentially be very expensive, depending on level size.
         */
        qreal perceptionLimit() const;
        void setPerceptionLimit(const qreal& newPerceptionLimit);
        
        QList<btPerceptionAtom*> perceptionAtoms() const;
        void setPerceptionAtoms(const QList<btPerceptionAtom*>& newPerceptionAtoms);
        
        QList<btPerceptionViewcone*> viewCones() const;
        void setViewCones(const QList<btPerceptionViewcone*> newViewCones);
        
    private:
        class btPerceptionPrivate;
        btPerceptionPrivate* d;
};

#endif // BTPERCEPTION_H
