#include "LRParser.h"
#include <stdexcept>
#include <sstream>

LRParser::LRParser(QObject *parent) : QObject(parent) {
    setupGrammarAndTable();
}

QString LRParser::inputString() const {
    return m_inputString;
}

void LRParser::setInputString(const QString &inputString) {
    if (m_inputString != inputString) {
        m_inputString = inputString;
        emit inputStringChanged();
    }
}

QVector<QString> LRParser::stack() const {
    return m_stack;
}

QVector<QString> LRParser::input() const {
    return m_input;
}

QVector<QString> LRParser::action() const {
    return m_action;
}

void LRParser::setupGrammarAndTable() {
    // Example grammar
    grammar = {
        {1, {"E", {"E", "+", "T"}}},
        {2, {"E", {"T"}}},
        {3, {"T", {"T", "*", "F"}}},
        {4, {"T", {"F"}}},
        {5, {"F", {"(", "E", ")"}}},
        {6, {"F", {"id"}}}
    };

    // Example parsing table
    parsingTable = {
        {"0", {{"id", "s5"}, {"(", "s4"}, {"E", "1"}, {"T", "2"}, {"F", "3"}}},
        {"1", {{"+", "s6"}, {"$", "acc"}}},
        {"2", {{"+", "r2"}, {"*", "s7"}, {")", "r2"}, {"$", "r2"}}},
        {"3", {{"+", "r4"}, {"*", "r4"}, {")", "r4"}, {"$", "r4"}}},
        {"4", {{"id", "s5"}, {"(", "s4"}, {"E", "8"}, {"T", "2"}, {"F", "3"}}},
        {"5", {{"+", "r6"}, {"*", "r6"}, {")", "r6"}, {"$", "r6"}}},
        {"6", {{"id", "s5"}, {"(", "s4"}, {"T", "9"}, {"F", "3"}}},
        {"7", {{"id", "s5"}, {"(", "s4"}, {"F", "10"}}},
        {"8", {{"+", "s6"}, {")", "s11"}}},
        {"9", {{"+", "r1"}, {"*", "s7"}, {")", "r1"}, {"$", "r1"}}},
        {"10", {{"+", "r3"}, {"*", "r3"}, {")", "r3"}, {"$", "r3"}}},
        {"11", {{"+", "r5"}, {"*", "r5"}, {")", "r5"}, {"$", "r5"}}}
    };
}

std::vector<std::string> LRParser::tokenize(const std::string &inputString) {
    std::vector<std::string> tokens;
    for (size_t i = 0; i < inputString.size();) {
        if (inputString[i] == '+' || inputString[i] == '*' || inputString[i] == '(' || inputString[i] == ')') {
            tokens.push_back(std::string(1, inputString[i]));
            ++i;
        } else if (isalnum(inputString[i])) {
            tokens.push_back("id");
            while (i < inputString.size() && isalnum(inputString[i])) {
                ++i;
            }
        } else {
            ++i;
        }
    }
    return tokens;
}

std::string LRParser::join(const std::vector<std::string>& vec, const std::string& delimiter) {
    std::ostringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) ss << delimiter;
        ss << vec[i];
    }
    return ss.str();
}

void LRParser::parse() {
    std::vector<std::string> stack = {"0"};
    std::vector<std::string> input = tokenize(m_inputString.toStdString());
    input.push_back("$");
    std::vector<std::vector<std::string>> steps;
    steps.push_back({ "0", join(input, " "), "Initial step" });

    m_stack.clear();
    m_input.clear();
    m_action.clear();

    while (true) {
        std::string currentState = stack.back();
        std::string currentSymbol = input[0];
        if (parsingTable.count(currentState) == 0 || parsingTable.at(currentState).count(currentSymbol) == 0) {
            throw std::runtime_error("Invalid state or symbol");
        }
        std::string action = parsingTable.at(currentState).at(currentSymbol);

        if (action[0] == 's') {
            stack.push_back(currentSymbol);
            stack.push_back(action.substr(1));
            input.erase(input.begin());
            steps.push_back({ join(stack, " "), join(input, " "), "Shift: " + action });
        } else if (action[0] == 'r') {
            int productionIndex = std::stoi(action.substr(1));
            auto production = grammar.at(productionIndex);
            for (size_t i = 0; i < production.second.size() * 2; ++i) {
                stack.pop_back();
            }
            stack.push_back(production.first);
            std::string gotoState = parsingTable.at(stack[stack.size() - 2]).at(stack.back());
            stack.push_back(gotoState);
            steps.push_back({ join(stack, " "), join(input, " "), "Reduce: " + production.first + " -> " + join(production.second, " ") });
        } else if (action == "acc") {
            steps.push_back({ join(stack, " "), join(input, " "), "Accept: Input Accepted" });
            break;
        } else {
            throw std::runtime_error("Invalid action: " + action);
        }
    }

    for (const auto& row : steps) {
        m_stack.append(QString::fromStdString(row[0]));
        m_input.append(QString::fromStdString(row[1]));
        m_action.append(QString::fromStdString(row[2]));
    }

    emit stackChanged();
    emit inputChanged();
    emit actionChanged();
}
