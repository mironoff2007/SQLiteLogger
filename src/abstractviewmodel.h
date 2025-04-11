#ifndef ABSTRACTVIEWMODEL_H
#define ABSTRACTVIEWMODEL_H

#include <QAbstractListModel>
#include <QObject>

class AbstractDataBaseViewModel : public QObject
{
    Q_OBJECT
public:
    explicit AbstractDataBaseViewModel(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~AbstractDataBaseViewModel() = default;

signals:
    void success(const QVariant &result);
    void loading();
    void error(const QString &message);

};

#endif // ABSTRACTVIEWMODEL_H
