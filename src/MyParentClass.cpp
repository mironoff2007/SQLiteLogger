#include <QObject>

template <typename T>
class MyParentClass : public QObject
{
    Q_OBJECT

public:
    virtual T getValue() const = 0;
};


