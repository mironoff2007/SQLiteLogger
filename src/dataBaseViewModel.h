#ifndef DATABASEVIEWMODEL_H
#define DATABASEVIEWMODEL_H

#include <QAbstractListModel>
#include "state.h"

class DataBaseViewModel : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseViewModel(QObject *parent = nullptr);
    ~DataBaseViewModel() override = default;

    Q_INVOKABLE void generateSomeData();

signals:
    void someData(const QStringList &list);
    void successState(const QVariant state);  // Emit the complete state


private:
    State m_currentState;

};
#endif // DATABASEVIEWMODEL_H
