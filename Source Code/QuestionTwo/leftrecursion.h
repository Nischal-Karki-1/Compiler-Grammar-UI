#ifndef LEFTRECURSION_H
#define LEFTRECURSION_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

class LeftRecursion : public QObject
{
    Q_OBJECT
public:
    explicit LeftRecursion(QObject *parent = nullptr);

    Q_INVOKABLE QString removeLeftRecursion(const QString &grammar);

private:
    QStringList splitGrammar(const QString &grammar);
    QString handleLeftRecursion(const QStringList &rules);
};

#endif // LEFTRECURSION_H
