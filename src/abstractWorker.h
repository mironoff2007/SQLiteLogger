#ifndef ABSTRACTWORKER_H
#define ABSTRACTWORKER_H

#include <QThread>
class AbstractWorker: public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorker(QObject *parent = nullptr);

public:
   virtual QVariant getResult() = 0;

    void startTask(const QVariant &param) {
        emit onMainCall(param);
    };

signals:void onMainCall(const QVariant &param);

//private slots: void resultOnMain(const QVariant &result);

private:
    QScopedPointer<QThread> m_thread;
};


class AbstractBackGroundWorker : public QObject
{
    Q_OBJECT
public:
    explicit AbstractBackGroundWorker(QObject *parent = nullptr);
    ~AbstractBackGroundWorker() override = default;

signals:void resultTask(const QVariant &list);

public slots:void runTaskOnBackGround();

};

#endif // ABSTRACTWORKER_H
