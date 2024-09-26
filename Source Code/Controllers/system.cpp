#include "system.h"

System::System(QObject *parent)
    : QObject{parent},
    m_questionOne(true),
    m_questionTwo(false),
    m_questionThree(false),
    m_questionFour(false),
    m_questionFive(false),
    m_questionSix(false)

{

}

bool System::questionOne() const
{
    return m_questionOne;
}

void System::setQuestionOne(bool newQuestionOne)
{
    if (m_questionOne == newQuestionOne)
        return;
    m_questionOne = newQuestionOne;
    emit questionOneChanged();
}

bool System::questionTwo() const
{
    return m_questionTwo;
}

void System::setQuestionTwo(bool newQuestionTwo)
{
    if (m_questionTwo == newQuestionTwo)
        return;
    m_questionTwo = newQuestionTwo;
    emit questionTwoChanged();
}

bool System::questionThree() const
{
    return m_questionThree;
}

void System::setQuestionThree(bool newQuestionThree)
{
    if (m_questionThree == newQuestionThree)
        return;
    m_questionThree = newQuestionThree;
    emit questionThreeChanged();
}

bool System::questionFour() const
{
    return m_questionFour;
}

void System::setQuestionFour(bool newQuestionFour)
{
    if (m_questionFour == newQuestionFour)
        return;
    m_questionFour = newQuestionFour;
    emit questionFourChanged();
}

bool System::questionFive() const
{
    return m_questionFive;
}

void System::setQuestionFive(bool newQuestionFive)
{
    if (m_questionFive == newQuestionFive)
        return;
    m_questionFive = newQuestionFive;
    emit questionFiveChanged();
}

bool System::questionSix() const
{
    return m_questionSix;
}

void System::setQuestionSix(bool newQuestionSix)
{
    if (m_questionSix == newQuestionSix)
        return;
    m_questionSix = newQuestionSix;
    emit questionSixChanged();
}




