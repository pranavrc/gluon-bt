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

#include "btperceptioninfo.h"

#include "btbrain.h"


class btPerceptionInfo::btPerceptionInfoPrivate
{
    public:
        btPerceptionInfoPrivate()
        {
            radius = 0;
        }
        ~btPerceptionInfoPrivate() {}
        
        QVector3D position;
        qreal radius;
};

btPerceptionInfo::btPerceptionInfo(btBrain * parent)
    : QObject(parent)
{
    d = new btPerceptionInfoPrivate();
	
	if(parent)
		parent->addPerceptionInfo(this);
}

btPerceptionInfo::~btPerceptionInfo()
{
    delete d;
}

QVector3D btPerceptionInfo::position() const
{
    return d->position;
}

void btPerceptionInfo::setPosition(const QVector3D& newPosition)
{
    d->position = newPosition;
}

qreal btPerceptionInfo::radius() const
{
    return d->radius;
}

void btPerceptionInfo::setRadius(const qreal& newRadius)
{
    d->radius = newRadius;
}

#include "btperceptioninfo.moc"
