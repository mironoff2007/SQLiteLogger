#include "databaseviewmodel.h"
#include <QDebug>
#include <QTimer>
#include "person.h"
#include "abstractviewmodel.h"
#include "selecttask.h"
#include "abstractworker/abstractbackgroundworker.h"

DataBaseViewModel::DataBaseViewModel(QObject *parent)
    : AbstractDataBaseViewModel(parent)
    , selectWorker(new AbstractWorker(new SelectTask()))
{
    // Initialize in constructor body instead
    // Constructor implementation
    // You might want to initialize connections or data here
     connect(selectWorker, &AbstractWorker::resultTask, this, &DataBaseViewModel::onResultSelectFileNames, Qt::QueuedConnection);
}

void DataBaseViewModel::onResultSelectFileNames(const QVariant &result)
{
      qDebug() << "select result" << result;
}


void DataBaseViewModel::generateSomeData()
{
    qDebug() << "Generating some data...";

    // Simulate async operation
    QTimer::singleShot(1000, this, [this]() {
        try {
            // Generate your data
            QStringList dummyData = {"Item 1", "Item 2", "Item 3"};
            // Wrap in Success state

            Person* person = new Person(this);
            person->setName("John Doe");
            person->setAge(30);

            // Convert to QVariant
            //updateSuccesState(person);
            QVariant variant = QVariant::fromValue(person);
           emit success(variant);
        } catch (const std::exception& e) {
            // Set error state
           emit error(e.what());
        }
    });
}
