#ifndef LEFTFACTORING_H
#define LEFTFACTORING_H

#include <QObject>
#include <QStringList>
#include <QMap>

class LeftFactoring : public QObject
{
    Q_OBJECT
public:
    explicit LeftFactoring(QObject *parent = nullptr);
    Q_INVOKABLE QStringList leftFactor(const QStringList &productions);

private:
    QMap<QString, QStringList> findCommonPrefixes(const QStringList &productions);
    bool containsNonTerminal(const QStringList &productions, const QString &nonTerminal);
    QString findLongestCommonPrefix(const QStringList &strings);
};

#endif // LEFTFACTORING_H
