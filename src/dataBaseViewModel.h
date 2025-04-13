#ifndef DATABASEVIEWMODEL_H
#define DATABASEVIEWMODEL_H

#include <QAbstractListModel>
#include "abstractviewmodel.h"
#include "abstractworker/abstractWorker.h"

class DataBaseViewModel : public  AbstractDataBaseViewModel
{
    Q_OBJECT

public:
    explicit DataBaseViewModel(QObject *parent = nullptr);
    ~DataBaseViewModel() override = default;

    Q_INVOKABLE void generateSomeData();

private slots:
    void onResultSelectFileNames(const QVariant &result);

public:
    AbstractWorker* selectWorker;
};
#endif // DATABASEVIEWMODEL_H
