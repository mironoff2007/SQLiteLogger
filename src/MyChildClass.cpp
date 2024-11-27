#include "MyParentClass.cpp"

class MyChildClass : public MyParentClass
{
    Q_OBJECT

public:
    QString getValue() const override
    {
        return "" ;
    }
};

