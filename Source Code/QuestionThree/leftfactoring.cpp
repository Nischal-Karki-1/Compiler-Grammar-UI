#include "LeftFactoring.h"
#include <QDebug>
#include <QSet>

LeftFactoring::LeftFactoring(QObject *parent) : QObject(parent)
{
}

QStringList LeftFactoring::leftFactor(const QStringList &productions)
{
    QStringList newProductions = productions;
    bool updated;

    do {
        updated = false;
        QMap<QString, QStringList> tempGrammar;

        qDebug() << "Current Productions:" << newProductions;

        for (const QString &prod : newProductions) {
            QStringList parts = prod.split("->");
            if (parts.size() != 2) continue;

            QString nonTerminal = parts[0].trimmed();
            QStringList prodList = parts[1].split("|", Qt::SkipEmptyParts);

            for (QString &p : prodList) {
                p = p.trimmed();
            }

            qDebug() << "Processing Non-Terminal:" << nonTerminal;
            qDebug() << "Production List:" << prodList;

            if (prodList.size() < 2 || (prodList.size() == 1 && prodList[0] == "ε")) {
                tempGrammar[nonTerminal] = prodList;
                continue;
            }


            QMap<QString, QStringList> commonPrefixes = findCommonPrefixes(prodList);

            qDebug() << "Common Prefixes:" << commonPrefixes;

            if (!commonPrefixes.isEmpty()) {
                updated = true;
                QStringList newProdList;
                QStringList untouchedProdList = prodList;

                auto it = commonPrefixes.begin();
                QString prefix = it.key();
                QStringList suffixes = it.value();

                if (suffixes.size() > 1) {
                    QString newNonTerminal = nonTerminal + "'";
                    while (tempGrammar.contains(newNonTerminal) || containsNonTerminal(newProductions, newNonTerminal)) {
                        newNonTerminal += "'";
                    }

                    QStringList newSuffixes;
                    for (const QString &suffix : suffixes) {
                        newSuffixes.append(suffix.isEmpty() ? "ε" : suffix);
                    }
                    tempGrammar[newNonTerminal] = newSuffixes;
                    newProdList.append(prefix + newNonTerminal);

                    qDebug() << "New Non-Terminal:" << newNonTerminal;
                    qDebug() << "New Suffixes:" << newSuffixes;


                    for (const QString &suffix : suffixes) {
                        untouchedProdList.removeOne(prefix + suffix);
                    }
                }

                newProdList.append(untouchedProdList);
                tempGrammar[nonTerminal] = newProdList;

                qDebug() << "New Production List for" << nonTerminal << ":" << newProdList;
            } else {
                tempGrammar[nonTerminal] = prodList;
            }
        }

        newProductions.clear();
        for (auto it = tempGrammar.begin(); it != tempGrammar.end(); ++it) {
            newProductions.append(it.key() + " -> " + it.value().join(" | "));
        }
    } while (updated);

    qDebug() << "Final Productions:" << newProductions;
    return newProductions;
}

QMap<QString, QStringList> LeftFactoring::findCommonPrefixes(const QStringList &productions)
{
    QMap<QString, QStringList> prefixes;


    QString longestCommonPrefix;
    for (int i = 0; i < productions.size(); ++i) {
        for (int j = i + 1; j < productions.size(); ++j) {
            QStringList pair;
            pair.append(productions[i]);
            pair.append(productions[j]);

            QString commonPrefix = findLongestCommonPrefix(pair);
            if (commonPrefix.length() > longestCommonPrefix.length()) {
                longestCommonPrefix = commonPrefix;
            }
        }
    }

    if (!longestCommonPrefix.isEmpty()) {
        QStringList suffixes;
        for (const QString &prod : productions) {
            if (prod.startsWith(longestCommonPrefix)) {
                suffixes.append(prod.mid(longestCommonPrefix.length()));
            }
        }
        prefixes[longestCommonPrefix] = suffixes;
    }

    return prefixes;
}

QString LeftFactoring::findLongestCommonPrefix(const QStringList &strings)
{
    if (strings.isEmpty()) {
        return "";
    }

    QString prefix = strings[0];
    for (int i = 1; i < strings.size(); ++i) {
        while (strings[i].indexOf(prefix) != 0) {
            prefix = prefix.left(prefix.length() - 1);
            if (prefix.isEmpty()) {
                return "";
            }
        }
    }
    return prefix;
}

bool LeftFactoring::containsNonTerminal(const QStringList &productions, const QString &nonTerminal)
{
    for (const QString &prod : productions) {
        if (prod.startsWith(nonTerminal + " ->")) {
            return true;
        }
    }
    return false;
}
