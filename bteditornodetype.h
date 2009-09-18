#ifndef _BTEDITORNODETYPE_H_
#define _BTEDITORNODETYPE_H_

#include <QObject>

#include "btnodetype.h"

class btEditorNodeType : public btNodeType
{
    Q_OBJECT
public:
    btEditorNodeType();
    
    btEditorNodeType * copy();
    
    const QString toNodeTypeXml();
    virtual const QString toDataXml();
};

#endif