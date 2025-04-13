#ifndef CLONABLE_H
#define CLONABLE_H
#include <QMetaType>

class Clonable {
public:
    virtual ~Clonable() = default;
    virtual Clonable* clone() const = 0;
};

Q_DECLARE_METATYPE(Clonable*)
Q_DECLARE_METATYPE(const Clonable*)

#endif // CLONABLE_H
