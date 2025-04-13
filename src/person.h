#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include <QVariant>
#include "clonable.h"

class Person : public QObject, public Clonable
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)

public:
    explicit Person(QObject *parent = nullptr) : QObject(parent) {}

    // Copy constructor for cloning
    Person(const Person &other, QObject *parent = nullptr)
        : QObject(parent),
          m_name(other.m_name),
          m_age(other.m_age)
    {
    }

    // Clonable interface implementation
    Clonable* clone() const override {
        return new Person(*this);
    }

    QString name() const { return m_name; }
    void setName(const QString &name) {
        if (m_name != name) {
            m_name = name;
            emit nameChanged();
        }
    }

    int age() const { return m_age; }
    void setAge(int age) {
        if (m_age != age) {
            m_age = age;
            emit ageChanged();
        }
    }

signals:
    void nameChanged();
    void ageChanged();

private:
    QString m_name;
    int m_age = 0;
};

#endif // PERSON_H
