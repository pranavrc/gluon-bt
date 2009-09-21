#ifndef _BTEDITORNODETYPE_H_
#define _BTEDITORNODETYPE_H_

#include <QObject>

#include "../gluon-bt-common/btnodetype.h"

class btEditorNodeType : public btNodeType
{
    Q_OBJECT
    Q_PROPERTY(btNodeType::nodeType childTypes READ childTypes WRITE setChildTypes)
public:


    btEditorNodeType();
    
    btEditorNodeType * copy();
    btNodeType::nodeType childTypes() const;
    void setChildTypes(btNodeType::nodeType);
    
    const QString toNodeTypeXml();
    virtual const QString toDataXml();
private:
    btNodeType::nodeType m_type;
};

#endif
