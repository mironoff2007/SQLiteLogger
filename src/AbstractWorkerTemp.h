#ifndef ABSTRACTWORKERTEMP_H
#define ABSTRACTWORKERTEMP_H


#include <QObject>
#include <QThread>
#include <functional>

class AbstractWorkerTemp: public QObject
{
    Q_OBJECT
public:
    explicit AbstractWorkerTemp(QObject *parent = nullptr);
    ~AbstractWorkerTemp() override;

    void onMainMethodCall(void (*f)(int));

signals:void onMainCall();

private slots: void resultOnMain(const QStringList &list);

private:
    QScopedPointer<QThread> m_thread;
private:
    std::function<int (int)> func_obj = [&](int a) { return 1; };
};


class BackGroundWorker : public QObject
{
    Q_OBJECT
public:
    explicit BackGroundWorker(QObject *parent = nullptr);
    ~BackGroundWorker() override = default;

signals:void resultTask(const QStringList &list);

public slots:void runTaskOnBackGround();

};

#endif // ABSTRACTWORKERTEMP_H
