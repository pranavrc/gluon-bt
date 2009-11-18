#ifndef _BTCHARACTER_H_
#define _BTCHARACTER_H_

#include <QObject>
#include "../gluon-bt-lib/btlib_export.h"

class BT_LIB_EXPORT btCharacter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName);
public:
        btCharacter();
        ~btCharacter();
        void setName(QString name){m_name = name;}
        QString name() const {return m_name;}
private:
        QString m_name;
};

#endif // _BTCHARACTER_H_
