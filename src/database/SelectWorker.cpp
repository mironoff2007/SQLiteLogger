#include "abstractbackgroundworker.h"

class MyChildClass : public AbstractBackgroundWorker
{
    Q_OBJECT

public:
    QString getValue() const override
    {
        return "" ;
    }
};

