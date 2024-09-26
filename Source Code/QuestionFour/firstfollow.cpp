#include "firstfollow.h"
#include <QDebug>
#include <cctype>
#include <QSet>
#include <algorithm>

GrammarParser::GrammarParser(QObject *parent) : QObject(parent), count(0), n(0), m(0), k(0), e(0)
{
    memset(calc_first, '!', sizeof(calc_first));
    memset(calc_follow, '!', sizeof(calc_follow));
}

QString GrammarParser::firstSets() const
{
    return m_firstSets.join("\n");
}

QString GrammarParser::followSets() const
{
    return m_followSets.join("\n");
}

void GrammarParser::parseGrammar(const QString &input)
{
    m_productions.clear();
    m_firstSets.clear();
    m_followSets.clear();

    QStringList lines = input.split("\n", Qt::SkipEmptyParts);
    count = lines.size();

    for (const QString &line : lines)
    {
        m_productions.push_back(line.toStdString());
    }

    // Split productions by '|'
    std::vector<std::string> split_productions;
    for (const std::string &rule : m_productions)
    {
        size_t pos = 0;
        std::string lhs = rule.substr(0, rule.find("->"));
        std::string rhs = rule.substr(rule.find("->") + 2);  // Skip over "->"

        while ((pos = rhs.find('|')) != std::string::npos)
        {
            split_productions.push_back(lhs + "->" + rhs.substr(0, pos));
            rhs.erase(0, pos + 1);
        }
        split_productions.push_back(lhs + "->" + rhs);
    }

    m_productions = split_productions;
    count = m_productions.size();

    int kay;
    char done[count];
    int ptr = -1;
    memset(done, '\0', sizeof(done));

    int point1 = 0, point2, xxx;

    for (k = 0; k < count; k++)
    {
        char c = m_productions[k][0];
        point2 = 0;
        xxx = 0;

        for (kay = 0; kay <= ptr; kay++)
            if (c == done[kay])
                xxx = 1;

        if (xxx == 1)
            continue;

        findFirst(c, 0, 0);
        ptr += 1;
        done[ptr] = c;

        QSet<QChar> firstSet;
        for (int i = 0; i < n; i++)
        {
            firstSet.insert(first[i]);
        }

        QVector<QChar> sortedFirstSet = QVector<QChar>::fromList(firstSet.values());
        std::sort(sortedFirstSet.begin(), sortedFirstSet.end());

        QString firstSetString = QString("First(%1) = { ").arg(c);
        for (const QChar &ch : sortedFirstSet)
        {
            firstSetString.append(QString("%1, ").arg(ch));
        }
        firstSetString.chop(2); // Remove the last comma and space
        firstSetString.append(" }");
        m_firstSets.append(firstSetString);

        n = 0;
    }

    ptr = -1;
    memset(done, '\0', sizeof(done));

    for (k = 0; k < count; k++)
    {
        char c = m_productions[k][0];
        point2 = 0;
        xxx = 0;

        for (kay = 0; kay <= ptr; kay++)
            if (c == done[kay])
                xxx = 1;

        if (xxx == 1)
            continue;

        follow(c);
        ptr += 1;
        done[ptr] = c;

        QSet<QChar> followSet;
        for (int i = 0; i < m; i++)
        {
            followSet.insert(f[i]);
        }

        QVector<QChar> sortedFollowSet = QVector<QChar>::fromList(followSet.values());
        std::sort(sortedFollowSet.begin(), sortedFollowSet.end());

        QString followSetString = QString("Follow(%1) = { ").arg(c);
        for (const QChar &ch : sortedFollowSet)
        {
            followSetString.append(QString("%1, ").arg(ch));
        }
        followSetString.chop(2);
        followSetString.append(" }");
        m_followSets.append(followSetString);

        m = 0;
    }

    emit firstSetsChanged();
    emit followSetsChanged();
}

void GrammarParser::findFirst(char c, int q1, int q2)
{
    if (!isupper(c))
    {
        first[n++] = c;
        return;
    }

    for (int j = 0; j < count; j++)
    {
        if (m_productions[j][0] == c)
        {
            size_t pos = m_productions[j].find("->") + 2;

            while (pos < m_productions[j].size())
            {
                char symbol = m_productions[j][pos];
                if (symbol == '|')
                {
                    pos++;
                    continue;
                }

                if (!isupper(symbol))
                {
                    first[n++] = symbol;
                    break;
                }

                findFirst(symbol, j, pos + 1);

                bool epsilon_found = false;
                for (int x = 0; x < n; x++)
                {
                    if (first[x] == '#')
                    {
                        epsilon_found = true;
                        break;
                    }
                }

                if (!epsilon_found)
                {
                    break;
                }
                else
                {
                    pos++;
                }
            }
        }
    }
}

void GrammarParser::followFirst(char c, int c1, int c2)
{
    if (!isupper(c))
    {
        f[m++] = c;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (calc_first[i][0] == c)
            {
                for (int j = 1; calc_first[i][j] != '!'; j++)
                {
                    if (calc_first[i][j] != '#')
                    {
                        f[m++] = calc_first[i][j];
                    }
                    else
                    {
                        if (m_productions[c1][c2] == '\0')
                        {
                            follow(m_productions[c1][0]);
                        }
                        else
                        {
                            followFirst(m_productions[c1][c2], c1, c2 + 1);
                        }
                    }
                }
            }
        }
    }
}

void GrammarParser::follow(char c)
{
    if (m_productions[0][0] == c)
    {
        f[m++] = '$';
    }

    for (int i = 0; i < count; i++)
    {
        for (size_t j = 2; j < m_productions[i].length(); j++)
        {
            if (m_productions[i][j] == c)
            {
                if (m_productions[i][j + 1] != '\0')
                {
                    followFirst(m_productions[i][j + 1], i, j + 2);
                }

                if (m_productions[i][j + 1] == '\0' && c != m_productions[i][0])
                {
                    follow(m_productions[i][0]);
                }
            }
        }
    }
}
