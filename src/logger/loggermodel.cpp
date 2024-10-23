// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "loggermodel.h"

#include "auroraapp/auroraapp.h"
#include <QDateTime>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

#include "applogger.h"

namespace
{
    const auto dirLog = QStringLiteral("log");
    const auto formatDateTimeFileName = QStringLiteral("yyyy_MM_dd-HH_mm_ss_zzz");

    auto currentDateTimeFileName()
    {
        return QDateTime::currentDateTime().toString(formatDateTimeFileName);
    }

    auto createLogFile(const QString &baseName)
    {
        const auto path = QString("%1/%2").arg(Aurora::Application::filesDir(false).path(), dirLog);

        QDir dir;
        if (!dir.exists(path)) {
            if (!dir.mkpath(path)) {
                qWarning("Directory %s is not created!!!", path.toLocal8Bit().constData());
            }
        }
        dir.setPath(path);
        const auto entireFiles = dir.entryList(QStringList() << "*.log", QDir::Files, QDir::Name);
        if (entireFiles.size() >= 50) {
            if (!dir.remove(entireFiles.first())) {
                qWarning("File %s is not removed!", entireFiles.first().toLocal8Bit().constData());
            }
        }
        const auto filePath = QString("%1/%2%4").arg(path, baseName, ".log");
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << "-----\n";
            file.close();
        }
        return filePath;
    }
}

LoggerModel::LoggerModel(QObject *parent)
    : QObject(parent)
    , m_process(new QProcess)
{
    m_filePath = createLogFile(currentDateTimeFileName());

    connect(m_process.data(), &QProcess::readyRead, this, &LoggerModel::onDbusProcessFinished);
    connect(m_process.data(), &QProcess::errorOccurred, [&](QProcess::ProcessError error){
        qWarning() << "ERROR: " << error << ", " << m_process->errorString();
    });
    connect(&AppLogger::instance(), &AppLogger::sendData, this, &LoggerModel::onAppEventSendData);
}

LoggerModel::~LoggerModel()
{
    dbusProcessFinish();
}

QString LoggerModel::filePath() const
{
    return m_filePath;
}

void LoggerModel::setFilePath(const QString &path)
{
    if (m_filePath == path)
        return;

    m_filePath = path;
    emit filePathChanged();
}

void LoggerModel::updateFileName(const QString &fileName)
{
    if (fileName.isEmpty())
        return;

    const auto path = createLogFile(fileName);
    setFilePath(path);
}

int LoggerModel::loggerType() const
{
    return static_cast<int>(m_loggerType);
}

void LoggerModel::setLoggerType(int index)
{
    const auto type = static_cast<LoggerType>(index);
    if (m_loggerType == type)
        return;

    m_loggerType = type;
    if (m_loggerType == LoggerType::WriteLine) {
        dbusProcessFinish();
        AppLogger::instance().setSendState(false);
    }
    else if (m_loggerType == LoggerType::DBusMonitor) {
        dbusProcessStart();
        AppLogger::instance().setSendState(false);
    }
    else if (m_loggerType == LoggerType::AppEvents) {
        dbusProcessFinish();
        AppLogger::instance().setSendState(true);
        const auto data = AppLogger::instance().getData();
        writeToLog(data);
        emit appEventResult(data);
    }
    emit loggerTypeChanged();
}

void LoggerModel::dbusProcessStart()
{
    const QString cmd = QStringLiteral("dbus-monitor --system");
    dbusProcessFinish();

    m_process->start(cmd);
}

void LoggerModel::dbusProcessFinish()
{
    if (m_process->state() == QProcess::Running || m_process->state() == QProcess::Starting)
        m_process->close();
}

void LoggerModel::writeToLog(const QString &data)
{
    QFile file(m_filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);
        out << data;
        file.close();
    }
    else {
        qWarning() << "Error open log file: " << m_filePath;
    }
}

void LoggerModel::onDbusProcessFinished()
{
    const auto arr = m_process->readAll();
    const auto data = QString::fromLocal8Bit(arr.data());
    writeToLog(data);
    emit dbusProcessResult(data);
}

void LoggerModel::onAppEventSendData(const QString &data)
{
    writeToLog(data);
    emit appEventResult(data);
}
