// SPDX-FileCopyrightText: 2024 Open Mobile Platform LLC <community@omp.ru>
// SPDX-License-Identifier: BSD-3-Clause

#ifndef APPLOGGER_H
#define APPLOGGER_H

#include <QObject>

class AppLogger : public QObject
{
    Q_OBJECT
public:
    static AppLogger& instance();

    void init();

    bool sendState() const;
    void setSendState(bool state);

    void addToBuffer(const QString &str);
    void clearBuffer();

    QString getData() const;

private:
    explicit AppLogger(QObject *parent = nullptr);
    ~AppLogger() override = default;

signals:
    void sendData(const QString &data);

private:
    QScopedPointer<QByteArray> m_buffer;
    bool m_sendState = false;
};

#endif // APPLOGGER_H
