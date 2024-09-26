#ifndef GRAMMARPARSER_H
#define GRAMMARPARSER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include <string>

class GrammarParser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstSets READ firstSets NOTIFY firstSetsChanged)
    Q_PROPERTY(QString followSets READ followSets NOTIFY followSetsChanged)

public:
    explicit GrammarParser(QObject *parent = nullptr);

    QString firstSets() const;
    QString followSets() const;

public slots:
    void parseGrammar(const QString &input);

signals:
    void firstSetsChanged();
    void followSetsChanged();

private:
    void findFirst(char c, int q1, int q2);
    void followFirst(char c, int c1, int c2);
    void follow(char c);

    QStringList m_firstSets;
    QStringList m_followSets;
    std::vector<std::string> m_productions;
    char calc_first[10][100];
    char calc_follow[10][100];
    char first[10];
    char f[10];
    int count;
    int n;
    int m;
    int k;
    char ck;
    int e;
};

#endif // GRAMMARPARSER_H
