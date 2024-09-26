#ifndef LL1_PARSER_H
#define LL1_PARSER_H

#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>
#include <QObject>
#include <QVariantList>

using namespace std;

class LL1Parser : public QObject {
    Q_OBJECT

public:
    explicit LL1Parser(QObject *parent = nullptr);
    Q_INVOKABLE QVariantList parse(const QString &input);

private:
    map<string, set<string>> firstSets;
    map<string, set<string>> followSets;
    map<string, map<string, string>> parsingTable;
    map<string, vector<string>> grammar;
    string startSymbol = "E";

    void initGrammar();
    void computeFirstSets();
    void computeFollowSets();
    void createParsingTable();
    set<string> computeFirst(const vector<string>& symbols);
    vector<string> split(const string& str, char delimiter);
    bool isTerminal(const string& symbol);
    bool isNonTerminal(const string& symbol);
    set<string> getTerminals();
    void printCurrentState(stack<string> parseStack, const string& input, int index, const string& output, QVariantList &steps);
};

#endif
