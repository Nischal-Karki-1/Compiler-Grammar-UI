#include "LeftRecursion.h"
#include <QStringList>
#include <QMap>

LeftRecursion::LeftRecursion(QObject *parent) : QObject(parent)
{
}

QString LeftRecursion::removeLeftRecursion(const QString &grammar)
{
    QStringList rules = splitGrammar(grammar);
    return handleLeftRecursion(rules);
}

QStringList LeftRecursion::splitGrammar(const QString &grammar)
{
    return grammar.split('\n', Qt::SkipEmptyParts);
}

QString LeftRecursion::handleLeftRecursion(const QStringList &rules)
{
    QString result;
    QMap<QString, QStringList> grammarRules;
    QStringList nonTerminals;

    for (const QString &rule : rules) {
        QStringList parts = rule.split("->", Qt::SkipEmptyParts);
        if (parts.size() == 2) {
            QString nonTerminal = parts[0].trimmed();
            QStringList productions = parts[1].trimmed().split('|', Qt::SkipEmptyParts);
            grammarRules[nonTerminal].append(productions);
            nonTerminals.append(nonTerminal);
        }
    }

    // Handle left recursion
    for (const QString &nonTerminal : nonTerminals) {
        QStringList alpha, beta;
        for (const QString &production : grammarRules[nonTerminal]) {
            if (production.startsWith(nonTerminal)) {
                alpha.append(production.mid(nonTerminal.length()).trimmed());
            } else {
                beta.append(production.trimmed());
            }
        }

        if (!alpha.isEmpty()) {
            QString newNonTerminal = nonTerminal + "'";
            QStringList betaProductions;
            for (const QString &b : beta) {
                betaProductions.append(b + " " + newNonTerminal);
            }
            result += nonTerminal + " -> " + betaProductions.join(" | ") + "\n";

            QStringList alphaProductions;
            for (const QString &a : alpha) {
                alphaProductions.append(a + " " + newNonTerminal);
            }
            result += newNonTerminal + " -> " + alphaProductions.join(" | ") + " | ε\n";
        } else {
            result += nonTerminal + " -> " + grammarRules[nonTerminal].join(" | ") + "\n";
        }
    }

    return result;
}
