#ifndef BTGLOBAL_H
#define BTGLOBAL_H

#include <QVariant>
#include "../gluon-bt-lib/btlib_export.h"

struct BT_LIB_EXPORT btChildWeights 
{
    QVariantList childWeightList;
};

Q_DECLARE_METATYPE(btChildWeights)
#endif