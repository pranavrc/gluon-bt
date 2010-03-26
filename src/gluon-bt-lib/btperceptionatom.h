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

#ifndef BTPERCEPTIONATOM_H
#define BTPERCEPTIONATOM_H

#include <QtCore/QObject>
#include <QtCore/QVariant>

#include "btperceptioninfo.h"

class btPerceptionAtom : public QObject
{
    Q_OBJECT
    Q_PROPERTY(btPerceptionInfo* perceptionInfo READ perceptionInfo WRITE setPerceptionInfo)
    Q_PROPERTY(QVariant knowledge READ knowledge)
    Q_PROPERTY(bool shouldUpdate READ shouldUpdate WRITE setShouldUpdate)
    
    public:
        btPerceptionAtom(QObject* parent = 0);
        ~btPerceptionAtom();
        
        btPerceptionInfo* perceptionInfo() const;
        void setPerceptionInfo(const btPerceptionInfo& newPerceptionInfo);
        
        QVariant knowledge() const;
        
        bool shouldUpdate() const;
        void setShouldUpdate(const bool& newShouldUpdate);
        
    public Q_SLOTS:
        void perceptionInfoUpdated();
        
    private:
        class btPerceptionAtomPrivate;
        btPerceptionAtomPrivate* d;
};

#endif // BTPERCEPTIONATOM_H
