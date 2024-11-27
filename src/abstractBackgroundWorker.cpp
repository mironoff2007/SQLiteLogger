#include <QObject>


class AbstractBackGroundWorker : public QObject
{
    Q_OBJECT


signals:
    void resultTask(const QVariant &param);

public slots:
    void runTaskOnBackGround();

};

