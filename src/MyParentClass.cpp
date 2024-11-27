#include <QObject>

class MyParentClass : public QObject
{
    Q_OBJECT

public:
    virtual QString getValue() const = 0;
};


