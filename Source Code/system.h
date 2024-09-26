#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>

class System : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool questionOne READ questionOne WRITE setQuestionOne NOTIFY questionOneChanged FINAL)
    Q_PROPERTY(bool questionTwo READ questionTwo WRITE setQuestionTwo NOTIFY questionTwoChanged FINAL)
    Q_PROPERTY(bool questionThree READ questionThree WRITE setQuestionThree NOTIFY questionThreeChanged FINAL)
    Q_PROPERTY(bool questionFour READ questionFour WRITE setQuestionFour NOTIFY questionFourChanged FINAL)
    Q_PROPERTY(bool questionFive READ questionFive WRITE setQuestionFive NOTIFY questionFiveChanged FINAL)
    Q_PROPERTY(bool questionSix READ questionSix WRITE setQuestionSix NOTIFY questionSixChanged FINAL)
public:
    explicit System(QObject *parent = nullptr);

    bool questionOne() const;
    void setQuestionOne(bool newQuestionOne);

    bool questionTwo() const;
    void setQuestionTwo(bool newQuestionTwo);

    bool questionThree() const;
    void setQuestionThree(bool newQuestionThree);

    bool questionFour() const;
    void setQuestionFour(bool newQuestionFour);

    bool questionFive() const;
    void setQuestionFive(bool newQuestionFive);

    bool questionSix() const;
    void setQuestionSix(bool newQuestionSix);

signals:
    void questionOneChanged();
    void questionTwoChanged();

    void questionThreeChanged();

    void questionFourChanged();

    void questionFiveChanged();

    void questionSixChanged();

private:
    bool m_questionOne;
    bool m_questionTwo;
    bool m_questionThree;
    bool m_questionFour;
    bool m_questionFive;
    bool m_questionSix;
};

#endif // SYSTEM_H
