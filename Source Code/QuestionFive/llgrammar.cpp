#include "llgrammar.h"

LL1Parser::LL1Parser(QObject *parent) : QObject(parent) {
    // Initialize the grammar
    initGrammar();
    // Calculate first and follow sets
    computeFirstSets();
    computeFollowSets();
    // Create the parsing table
    createParsingTable();
}

QVariantList LL1Parser::parse(const QString &input) {
    stack<string> parseStack;
    parseStack.push("$");
    parseStack.push(startSymbol);

    string inputStd = input.toStdString();
    int index = 0;
    string symbol = string(1, inputStd[index]);
    vector<string> output;

    QVariantList steps;
    steps.append("Stack\t\t\tInput\t\t\tOutput");
    printCurrentState(parseStack, inputStd, index, "", steps);

    while (!parseStack.empty()) {
        string top = parseStack.top();
        parseStack.pop();

        if (top == "$" && symbol == "$") {
            steps.append("Success: Input string is parsed successfully!");
            return steps;
        }

        if (isTerminal(top)) {
            if (top == symbol) {
                index++;
                symbol = string(1, inputStd[index]);
            } else {
                steps.append("Error: Unexpected symbol " + QString::fromStdString(symbol));
                return steps;
            }
        } else if (top == "ε") {
            continue;
        } else {
            if (parsingTable[top].count(symbol) > 0) {
                string production = parsingTable[top][symbol];
                output.push_back(top + " -> " + production);
                vector<string> symbols = split(production, ' ');

                for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
                    if (*it != "ε") {
                        parseStack.push(*it);
                    }
                }
            } else {
                steps.append("Error: No rule for " + QString::fromStdString(top) + " with symbol " + QString::fromStdString(symbol));
                return steps;
            }
        }
        printCurrentState(parseStack, inputStd, index, output.empty() ? "" : output.back(), steps);
    }

    if (symbol == "$") {
        steps.append("Success: Input string is parsed successfully!");
    } else {
        steps.append("Error: Input string is not fully parsed.");
    }
    return steps;
}

void LL1Parser::initGrammar() {
    grammar["E"] = {"T E'"};
    grammar["E'"] = {"+ T E'", "ε"};
    grammar["T"] = {"F T'"};
    grammar["T'"] = {"* F T'", "ε"};
    grammar["F"] = {"( E )", "i"};
}

void LL1Parser::computeFirstSets() {
    bool changed;
    do {
        changed = false;
        for (auto& rule : grammar) {
            string nonTerminal = rule.first;
            for (const string& production : rule.second) {
                vector<string> symbols = split(production, ' ');
                for (const string& symbol : symbols) {
                    size_t prevSize = firstSets[nonTerminal].size();
                    if (isTerminal(symbol)) {
                        firstSets[nonTerminal].insert(symbol);
                        break;
                    } else {
                        set<string> firstSet = firstSets[symbol];
                        firstSet.erase("ε");
                        firstSets[nonTerminal].insert(firstSet.begin(), firstSet.end());
                        if (firstSet.count("ε") == 0) {
                            break;
                        }
                    }
                    size_t newSize = firstSets[nonTerminal].size();
                    if (newSize > prevSize) {
                        changed = true;
                    }
                }
            }
        }
    } while (changed);
}

void LL1Parser::computeFollowSets() {
    followSets[startSymbol].insert("$");

    bool changed;
    do {
        changed = false;
        for (auto& rule : grammar) {
            string nonTerminal = rule.first;
            for (const string& production : rule.second) {
                vector<string> symbols = split(production, ' ');
                for (size_t i = 0; i < symbols.size(); ++i) {
                    if (isNonTerminal(symbols[i])) {
                        size_t prevSize = followSets[symbols[i]].size();
                        if (i + 1 < symbols.size()) {
                            string nextSymbol = symbols[i + 1];
                            if (isTerminal(nextSymbol)) {
                                followSets[symbols[i]].insert(nextSymbol);
                            } else {
                                set<string> firstSet = firstSets[nextSymbol];
                                firstSet.erase("ε");
                                followSets[symbols[i]].insert(firstSet.begin(), firstSet.end());
                                if (firstSets[nextSymbol].count("ε") > 0) {
                                    followSets[symbols[i]].insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
                                }
                            }
                        } else {
                            followSets[symbols[i]].insert(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
                        }
                        size_t newSize = followSets[symbols[i]].size();
                        if (newSize > prevSize) {
                            changed = true;
                        }
                    }
                }
            }
        }
    } while (changed);
}

void LL1Parser::createParsingTable() {
    for (auto& rule : grammar) {
        string nonTerminal = rule.first;
        for (const string& production : rule.second) {
            vector<string> symbols = split(production, ' ');
            set<string> firstSet = computeFirst(symbols);
            for (const string& terminal : firstSet) {
                if (terminal != "ε") {
                    parsingTable[nonTerminal][terminal] = production;
                }
            }
            if (firstSet.count("ε") > 0) {
                for (const string& terminal : followSets[nonTerminal]) {
                    parsingTable[nonTerminal][terminal] = production;
                }
            }
        }
    }
}

set<string> LL1Parser::computeFirst(const vector<string>& symbols) {
    set<string> result;
    for (const string& symbol : symbols) {
        if (isTerminal(symbol)) {
            result.insert(symbol);
            break;
        } else {
            set<string> firstSet = firstSets[symbol];
            result.insert(firstSet.begin(), firstSet.end());
            result.erase("ε");
            if (firstSet.count("ε") == 0) {
                break;
            }
        }
    }
    if (result.empty()) {
        result.insert("ε");
    }
    return result;
}

vector<string> LL1Parser::split(const string& str, char delimiter) {
    vector<string> result;
    string token;
    for (char c : str) {
        if (c == delimiter) {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty()) {
        result.push_back(token);
    }
    return result;
}

bool LL1Parser::isTerminal(const string& symbol) {
    return !symbol.empty() && !isupper(symbol[0]);
}

bool LL1Parser::isNonTerminal(const string& symbol) {
    return !symbol.empty() && isupper(symbol[0]);
}

set<string> LL1Parser::getTerminals() {
    set<string> terminals;
    for (const auto& rule : grammar) {
        for (const string& production : rule.second) {
            vector<string> symbols = split(production, ' ');
            for (const string& symbol : symbols) {
                if (isTerminal(symbol)) {
                    terminals.insert(symbol);
                }
            }
        }
    }
    terminals.insert("$");
    return terminals;
}

void LL1Parser::printCurrentState(stack<string> parseStack, const string& input, int index, const string& output, QVariantList &steps) {
    // Print stack
    string stackContent;
    while (!parseStack.empty()) {
        stackContent = parseStack.top() + " " + stackContent;
        parseStack.pop();
    }
    steps.append(QString::fromStdString(stackContent + "\t\t\t" + input.substr(index) + "\t\t\t" + output));
}
