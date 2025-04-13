#ifndef ABSTRACTVIEWMODEL_H
#define ABSTRACTVIEWMODEL_H

#include <QObject>
#include <QSharedPointer>
#include <QMutex>
#include <QMutexLocker>
#include <QVariant>
#include "clonable.h"
class AbstractDataBaseViewModel : public QObject
{
    Q_OBJECT

public:
    explicit AbstractDataBaseViewModel(QObject *parent = nullptr)
        : QObject(parent)
        , m_mutex()
    {
    }

    virtual ~AbstractDataBaseViewModel() = default;

    // Thread-safe getter
    QSharedPointer<Clonable> get() const {
        QMutexLocker locker(&m_mutex);
        return m_data;
    }

    void updateSuccesState(const Clonable* newValue) {
        QMutexLocker locker(&m_mutex);  // Use QMutexLocker for exception safety
        m_data = QSharedPointer<Clonable>(newValue->clone());
        QVariant variant = QVariant::fromValue(newValue);
        emit success(variant);
    }

signals:
    void success(const QVariant &result);
    void loading();
    void error(const QString &message);

private:
    mutable QMutex m_mutex;
    QSharedPointer<Clonable> m_data;
};

#endif // ABSTRACTVIEWMODEL_H
