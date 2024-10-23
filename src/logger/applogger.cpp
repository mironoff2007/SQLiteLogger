// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#include "applogger.h"
#include <QDateTime>
#include <QDebug>

namespace
{
    const auto formatDateTimeFileRecord = QStringLiteral("yyyy-MM-dd HH:mm:ss.zzz");

    auto currentDateTimeFileRecord()
    {
        return QDateTime::currentDateTime().toString(formatDateTimeFileRecord);
    }
}

static void msgOutErr(QtMsgType type, const QMessageLogContext &context, const QString &msg);

AppLogger &AppLogger::instance()
{
    static AppLogger logger;
    return logger;
}

void AppLogger::init()
{
    qInstallMessageHandler(msgOutErr);
}

AppLogger::AppLogger(QObject *parent)
    : QObject(parent)
    , m_buffer(new QByteArray)
{

}

bool AppLogger::sendState() const
{
    return m_sendState;
}

void AppLogger::setSendState(bool state)
{
    if (state == m_sendState)
        return;

    m_sendState = state;
}

void AppLogger::addToBuffer(const QString &str)
{
    m_buffer->append(str);
    if (sendState())
        emit sendData(QString::fromUtf8(m_buffer->data()));
}

void AppLogger::clearBuffer()
{
    m_buffer->clear();
}

QString AppLogger::getData() const
{
    return QString::fromUtf8(m_buffer->data());
}

void msgOutErr(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const auto createLine = [&](const QString &msgType) {
        return QString("[LOG](%1) %2: %3 : Locate(%4:%5) in fn: %6\n")
                .arg(msgType, currentDateTimeFileRecord(), msg)
                .arg(context.file)
                .arg(context.line)
                .arg(context.function);
    };

    QString line;
    switch (type) {
    case QtDebugMsg:
        line = createLine("DD");
        qDebug() << line;
        break;
    case QtInfoMsg:
        line = createLine("II");
        qInfo() << line;
        break;
    case QtWarningMsg:
        line = createLine("WW");
        qWarning() << line;
        break;
    case QtCriticalMsg:
        line = createLine("CC");
        qCritical() << line;
        break;
    case QtFatalMsg:
        abort();
    }

    AppLogger::instance().addToBuffer(line);
}
