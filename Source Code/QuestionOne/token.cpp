#include "Token.h"
#include <cctype>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <unordered_map>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>

Tokenizer::Tokenizer(QObject *parent) : QObject(parent) {}

bool Tokenizer::isOperator(QChar c) {
    return operators.contains(c);
}

QVector<Token> Tokenizer::tokenizeLine(const QString &line) {
    QVector<Token> tokens;
    QString lineCopy = line;
    QTextStream stream(&lineCopy);
    QChar c;

    while (!stream.atEnd()) {
        stream >> c;
        if (c.isSpace()) {
            tokens.append({TokenType::WHITESPACE, QString(c)});
        } else if (c.isLetter() || c == '_') {
            QString identifier(c);
            while (!stream.atEnd()) {
                QChar nextChar;
                stream >> nextChar;
                if (nextChar.isLetterOrNumber() || nextChar == '_') {
                    identifier += nextChar;
                } else {
                    stream.seek(stream.pos() - 1);
                    break;
                }
            }
            if (keywords.find(identifier) != keywords.end()) {
                tokens.append({keywords.at(identifier), identifier});
            } else {
                tokens.append({TokenType::IDENTIFIER, identifier});
            }
        } else if (c.isDigit()) {
            QString number(c);
            while (!stream.atEnd()) {
                QChar nextChar;
                stream >> nextChar;
                if (nextChar.isDigit()) {
                    number += nextChar;
                } else {
                    stream.seek(stream.pos() - 1);
                    break;
                }
            }
            tokens.append({TokenType::NUMBER, number});
        } else if (c == '"') {
            QString str(c);
            while (!stream.atEnd()) {
                stream >> c;
                str += c;
                if (c == '"') {
                    break;
                }
            }
            tokens.append({TokenType::STRING, str});
        } else if (c == '/') {
            QChar nextChar;
            stream >> nextChar;
            if (nextChar == '/') {
                QString comment("//");
                while (!stream.atEnd()) {
                    stream >> c;
                    comment += c;
                }
                tokens.append({TokenType::COMMENT, comment});
                break;
            } else {
                stream.seek(stream.pos() - 1);
                tokens.append({TokenType::OPERATOR, QString(c)});
            }
        } else if (isOperator(c)) {
            QString op(c);
            while (!stream.atEnd()) {
                QChar nextChar;
                stream >> nextChar;
                if (isOperator(nextChar)) {
                    op += nextChar;
                } else {
                    stream.seek(stream.pos() - 1);
                    break;
                }
            }
            tokens.append({TokenType::OPERATOR, op});
        } else {
            tokens.append({TokenType::UNKNOWN, QString(c)});
        }
    }

    return tokens;
}

QVector<Token> Tokenizer::tokenizeFile(const QString &filePath) {
    QVector<Token> tokens;
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Cannot open file for reading");
        return tokens;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QVector<Token> lineTokens = tokenizeLine(line);
        tokens.append(lineTokens);
    }

    file.close();
    return tokens;
}

void Tokenizer::writeTokensToFile(const QVector<Token> &tokens, const QString &outputFile) {
    QFile file(outputFile);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Cannot open file for writing");
        return;
    }

    QTextStream out(&file);
    out << "Token Type   |    Token Value\n";
    out << "----------------------------\n";
    for (const auto &token : tokens) {
        QString type;
        switch (token.type) {
        case TokenType::KEYWORD: type = "KEYWORD"; break;
        case TokenType::IDENTIFIER: type = "IDENTIFIER"; break;
        case TokenType::OPERATOR: type = "OPERATOR"; break;
        case TokenType::NUMBER: type = "NUMBER"; break;
        case TokenType::STRING: type = "STRING"; break;
        case TokenType::COMMENT: type = "COMMENT"; break;
        case TokenType::WHITESPACE: type = "WHITESPACE"; break;
        default: type = "UNKNOWN"; break;
        }
        out << type << "         " << token.value << "\n";
    }

    file.close();
}

