#ifndef TOKEN_H
#define TOKEN_H


#include <QObject>
#include <QString>
#include <QVector>
#include <QChar>
#include <unordered_map>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    NUMBER,
    STRING,
    COMMENT,
    WHITESPACE,
    UNKNOWN
};

class Token {
    Q_GADGET
    Q_PROPERTY(TokenType type MEMBER type)
    Q_PROPERTY(QString value MEMBER value)

public:
    TokenType type;
    QString value;
};

class Tokenizer : public QObject {
    Q_OBJECT
public:
    explicit Tokenizer(QObject *parent = nullptr);

    Q_INVOKABLE QVector<Token> tokenizeFile(const QString &filePath);
    Q_INVOKABLE void writeTokensToFile(const QVector<Token> &tokens, const QString &outputFile);

private:
    QVector<Token> tokenizeLine(const QString &line);
    const std::unordered_map<QString, TokenType> keywords = {
        {"int", TokenType::KEYWORD},
        {"return", TokenType::KEYWORD},
        {"if", TokenType::KEYWORD},
        {"else", TokenType::KEYWORD},
        {"for", TokenType::KEYWORD},
        {"while", TokenType::KEYWORD},
        {"do", TokenType::KEYWORD},
        {"break", TokenType::KEYWORD},
        {"continue", TokenType::KEYWORD},
        {"switch", TokenType::KEYWORD},
        {"case", TokenType::KEYWORD},
        {"default", TokenType::KEYWORD},
        {"void", TokenType::KEYWORD},
        {"const", TokenType::KEYWORD},
        {"static", TokenType::KEYWORD},
        {"struct", TokenType::KEYWORD},
        {"class", TokenType::KEYWORD},
        {"public", TokenType::KEYWORD},
        {"private", TokenType::KEYWORD},
        {"protected", TokenType::KEYWORD},
        {"namespace", TokenType::KEYWORD},
        {"using", TokenType::KEYWORD},
        {"new", TokenType::KEYWORD},
        {"delete", TokenType::KEYWORD},
        {"try", TokenType::KEYWORD},
        {"catch", TokenType::KEYWORD},
        {"throw", TokenType::KEYWORD}
    };
    const QString operators = "+-*/%=!<>&|^~";

    bool isOperator(QChar c);
};

#endif // TOKEN_H
