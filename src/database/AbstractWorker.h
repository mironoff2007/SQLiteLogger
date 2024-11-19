#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H


#include <QObject>
#include <QThread>
class AbstractWorker : public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorker(QObject *parent = nullptr);
    ~AbstractWorker() override;

    //void onMainMethodCall();

//signals:void onMainCall();

//private slots: void onResultSelectFileNames(const QStringList &list);

private:
    QScopedPointer<QThread> m_thread;
};


class BackGroundWorker : public QObject
{
    Q_OBJECT
public:
    explicit BackGroundWorker(QObject *parent = nullptr);
    ~BackGroundWorker() override = default;

//signals:void resultSelectFileNames(const QStringList &list);

//public slots:void handleSelectFileNames();

};

#endif // ABSTRACTWORKER_H
