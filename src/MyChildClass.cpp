#include "MyParentClass.cpp"

class MyChildClass : public MyParentClass<int>
{
    Q_OBJECT

public:
    int getValue() const override
    {
        return 42;
    }
};
