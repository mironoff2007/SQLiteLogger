#ifndef STATE_H
#define STATE_H
#include <QVariant>
#include <QString>
#include <variant>

class State
{
public:
    // State variants
    struct Success {
        QVariant data;
        explicit Success(const QVariant& data) : data(data) {}
    };

    struct Loading {};
    struct Error {
        QString message;
        explicit Error(const QString& msg = "") : message(msg) {}
    };

    // Constructors for each state
    State(const Success& state) : m_state(state) {}
    State(const Loading& state) : m_state(state) {}
    State(const Error& state) : m_state(state) {}

    // Default to Loading state
    State() : m_state(Loading{}) {}

    // Check current state
    bool isSuccess() const { return std::holds_alternative<Success>(m_state); }
    bool isLoading() const { return std::holds_alternative<Loading>(m_state); }
    bool isError() const { return std::holds_alternative<Error>(m_state); }

    // Get current state data
    Success success() const { return std::get<Success>(m_state); }
    Loading loading() const { return std::get<Loading>(m_state); }
    Error error() const { return std::get<Error>(m_state); }

private:
    std::variant<Success, Loading, Error> m_state;
};
#endif // STATE_H
