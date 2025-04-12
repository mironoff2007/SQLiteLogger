#ifndef DATABASEVIEWMODEL_H
#define DATABASEVIEWMODEL_H

#include <QAbstractListModel>
#include "abstractviewmodel.h"

class DataBaseViewModel : public  AbstractDataBaseViewModel
{
    Q_OBJECT

public:
    explicit DataBaseViewModel(QObject *parent = nullptr);
    ~DataBaseViewModel() override = default;

    Q_INVOKABLE void generateSomeData();


};
#endif // DATABASEVIEWMODEL_H
