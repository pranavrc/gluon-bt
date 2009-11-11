#ifndef _BTEDITORNODETYPE_H_
#define _BTEDITORNODETYPE_H_

#include <QObject>

#include "../gluon-bt-common/btnodetype.h"

class btEditorNodeType : public btNodeType
{
    Q_OBJECT
    Q_PROPERTY(btNodeType::nodeType childType READ childType WRITE setChildType)
public:


    btEditorNodeType();
    
    btEditorNodeType * copy();
    btNodeType::nodeType childType() const;
    void setChildType(btNodeType::nodeType);
    
    const QString toNodeTypeXml();
    virtual const QString toDataXml();
private:
    btNodeType::nodeType m_type;
    btNodeType::nodeType m_childtype;
};

#endif
