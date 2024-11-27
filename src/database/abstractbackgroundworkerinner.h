#ifndef ABSTRACTBACKGROUNDWORKERINNER_H
#define ABSTRACTBACKGROUNDWORKERINNER_H

class AbstractBackGroundWorkerInner : public QObject
{
    Q_OBJECT
public:
    explicit AbstractBackGroundWorkerInner(
            AbstractBackGroundWorker* worker,
            QObject *parent = nullptr
            );

signals:
    void resultTask(const QVariant &result);

public slots:
    void runTaskOnBackGround(const QVariant &param);

public:
   AbstractBackGroundWorker *m_backgroundWorker;
};

#endif // ABSTRACTBACKGROUNDWORKERINNER_H
