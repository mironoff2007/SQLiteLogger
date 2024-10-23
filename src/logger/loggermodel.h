// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef LOGGERMODEL_H
#define LOGGERMODEL_H

#include <QObject>
#include <QProcess>

class LoggerModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(int loggerType READ loggerType WRITE setLoggerType NOTIFY loggerTypeChanged)
public:
    enum class LoggerType
    {
        WriteLine,
        DBusMonitor,
        AppEvents
    };
    Q_ENUM(LoggerType)

public:
    explicit LoggerModel(QObject *parent = nullptr);
    ~LoggerModel() override;

    QString filePath() const;
    void setFilePath(const QString &path);
    Q_INVOKABLE void updateFileName(const QString &name);

    int loggerType() const;
    void setLoggerType(int index);

private:
    void dbusProcessStart();
    void dbusProcessFinish();

public slots:
    void writeToLog(const QString &data);

private slots:
    void onDbusProcessFinished();
    void onAppEventSendData(const QString &data);

signals:
    void filePathChanged();
    void loggerTypeChanged();

    void dbusProcessResult(const QString &txt);

    void appEventResult(const QString &txt);

private:
    QString m_filePath;
    LoggerType m_loggerType = LoggerType::WriteLine;
    QScopedPointer<QProcess> m_process;
};

#endif // LOGGERMODEL_H
