#ifndef LRParser_H
#define LRParser_H

#include <QObject>
#include <QString>
#include <QVector>
#include <unordered_map>
#include <vector>

class LRParser : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString inputString READ inputString WRITE setInputString NOTIFY inputStringChanged)
    Q_PROPERTY(QVector<QString> stack READ stack NOTIFY stackChanged)
    Q_PROPERTY(QVector<QString> input READ input NOTIFY inputChanged)
    Q_PROPERTY(QVector<QString> action READ action NOTIFY actionChanged)

public:
    explicit LRParser(QObject *parent = nullptr);

    QString inputString() const;
    void setInputString(const QString &inputString);

    QVector<QString> stack() const;
    QVector<QString> input() const;
    QVector<QString> action() const;

    Q_INVOKABLE void parse();

signals:
    void inputStringChanged();
    void stackChanged();
    void inputChanged();
    void actionChanged();

private:
    QString m_inputString;
    QVector<QString> m_stack;
    QVector<QString> m_input;
    QVector<QString> m_action;

    std::unordered_map<int, std::pair<std::string, std::vector<std::string>>> grammar;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parsingTable;

    void setupGrammarAndTable();
    std::vector<std::string> tokenize(const std::string& inputString);
    std::string join(const std::vector<std::string>& vec, const std::string& delimiter);
};

#endif // LRParser_H
