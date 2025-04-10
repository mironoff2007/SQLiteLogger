#include "databaseviewmodel.h"
#include <QDebug>
#include <QTimer>

DataBaseViewModel::DataBaseViewModel(QObject *parent)
    : QObject(parent)  // Remove the m_currentState initialization here
{
    m_currentState = State::Loading();  // Initialize in constructor body instead
    // Constructor implementation
    // You might want to initialize connections or data here
}

void DataBaseViewModel::generateSomeData()
{
    m_currentState = State::Loading{};

    qDebug() << "Generating some data...";

    // Simulate async operation
        QTimer::singleShot(1000, this, [this]() {
            try {
                // Generate your data
                QStringList dummyData = {"Item 1", "Item 2", "Item 3"};
                // Wrap in Success state
                m_currentState = State::State::Success(QVariant::fromValue(dummyData));
                emit successState(QVariant());

                // Also emit the original signal if needed
                emit someData(dummyData);
            } catch (const std::exception& e) {
                // Set error state
                m_currentState = State::State::Error(e.what());
            }
        });
}
