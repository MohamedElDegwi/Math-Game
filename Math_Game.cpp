/*
Hello! this a Small math game.....

Project Requirements :

1- Ask the user how many question do he want to answer

2- Ask the user to enter the question level he wants (easy, mid, hard, mix)

3- Ask the user to enter the operator type (Add, Sub, Mul, Div, mix)

4- show question body like :

Question [1/5]

6
10 /

_________________

here where the user enters his answer.


5- if the user enterd the right answer turn the screen to green and print right answer :-)

6- if Wrong print Wrong Answer :-(  and turn the screen to red

7 - do the same process for all questions

8- print final result (pass, fail)

9- show the Result panel like that :

_______________________________

nunber of questions :

questions level :

operator type :

number of right answers :

number of wrong answers :

_________________________________

10- ask the user if he wants to paly again (y/n)? if yes start the game again if no end the game

*/

#include <iostream>
#include <cstdlib>

enum enQuestionLevel
{
    Easy = 1,
    Mid,
    Hard,
    Mix
};
enum enOperationType
{
    Add = 1,
    Sub,
    Mul,
    Div,
    mix
};

struct stQuestionInfo
{
    short QuestionNumber = 0;
    enQuestionLevel QuestionLevel;
    short Number1 = 0;
    enOperationType OperationType;
    short Number2 = 0;
    int UserAnswer = 0;
    int CorrectAnswer = 0;
    bool IsCorrectAnswer = false;
};

struct stGameResults
{
    short NumberofQuestions = 0;
    enQuestionLevel QuestionsLevel;
    enOperationType OpType;
    short NumberofCorrectAnswers = 0;
    short NumberofWrongAnswers = 0;
    bool PassorFail = false;
};

short GetNumOfQuestions(const std::string &Message)
{
    std::cout << Message;
    short NumOfQuestions = 0;
    std::cin >> NumOfQuestions;

    while (NumOfQuestions < 1)
    {
        std::cout << "\nInvalid Input! try again : ";
        std::cin >> NumOfQuestions;
    }

    return NumOfQuestions;
}

enQuestionLevel GetQuestionLevel()
{
    short QuestionLevel = 0;
    std::cin >> QuestionLevel;

    while (QuestionLevel > 4 || QuestionLevel < 1)
    {
        std::cout << "\nInvalid Input! Enter a number in the allowed range : ";
        std::cin >> QuestionLevel;
    }

    return (enQuestionLevel)QuestionLevel;
}

enOperationType GetOperationType()
{
    short OperationType = 0;
    std::cin >> OperationType;

    while (OperationType > 5 || OperationType < 1)
    {
        std::cout << "\nInvalid Input! Enter a number in the allowed range : ";
        std::cin >> OperationType;
    }

    return (enOperationType)OperationType;
}

int GetRandNum(short From, short To)
{
    int RandomNum = std::rand() % (To - From) + From;

    return RandomNum;
}

std::string PrintOpSymbol(enOperationType OpType)
{
    std::string Arr[] = {"+ ", "- ", "* ", "/ "};

    return Arr[OpType - 1];
}

void PrintQuestionFormat(stQuestionInfo Question, short AllQuestions)
{
    std::cout << "\n\nQuestion [ " << Question.QuestionNumber << " / " << AllQuestions << " ] \n\n";
    std::cout << "\n"
              << Question.Number1;
    std::cout << "\n\t\t" << PrintOpSymbol(Question.OperationType);
    std::cout << "\n"
              << Question.Number2;
    std::cout << "\n________________________\n";
}

std::string PrintOpName(enOperationType OpType)
{
    std::string Arr[] = {"Add", "Sub", "Mul", "Div", "Mix"};

    return Arr[OpType - 1];
}

std::string PrintQuestionLevelName(enQuestionLevel QuestionLevel)
{
    std::string Arr[] = {"Easy", "Mid", "Hard", "Mix"};

    return Arr[QuestionLevel - 1];
}

void PrintQuestionLevelMenu()
{
    std::cout << "\nEnter The Question Level [1]Easy, [2]Mid, [3]Hard, [4]Mix ? ";
}

void PrintOPerationTypeMenu()
{
    std::cout << "\nEnter Operation Type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix ? ";
}

int GetCorrectAnswer(stQuestionInfo &Question)
{
    switch (Question.OperationType)
    {
    case enOperationType::Add:

        return Question.Number1 + Question.Number2;

    case enOperationType::Sub:

        return Question.Number1 - Question.Number2;

    case enOperationType::Mul:

        return Question.Number1 * Question.Number2;

    case enOperationType::Div:

        return Question.Number1 / Question.Number2;

    default:

        return (Question.CorrectAnswer = Question.Number1 + Question.Number2);
    }
}

void SetQuestion(stQuestionInfo &Question)
{
    switch (Question.QuestionLevel)
    {
    case enQuestionLevel::Easy:

        Question.Number1 = GetRandNum(1, 10);
        Question.Number2 = GetRandNum(1, 10);
        break;

    case enQuestionLevel::Mid:

        Question.Number1 = GetRandNum(11, 100);
        Question.Number2 = GetRandNum(11, 100);
        break;

    case enQuestionLevel::Hard:

        Question.Number1 = GetRandNum(101, 1000);
        Question.Number2 = GetRandNum(101, 1000);
        break;

    default:
        Question.Number1 = 0;
        Question.Number2 = 0;
        break;
    }
}

void SetQuestionResult(bool IsCorrectAnswer, short Answer)
{
    if (IsCorrectAnswer)
    {
        system("color 2F");
        std::cout << "\nCorrect Answer :- )\n";
    }

    else
    {
        std::cout << "\a";
        system("color 4F");
        std::cout << "\nWrong Answer :-( \n";
        std::cout << "The Correct answer is : " << Answer << "\n";
    }
}

enOperationType GetRandomOperationType()
{
    int Op = GetRandNum(1, 4);
    return (enOperationType)Op;
}

void StartQuestion(stQuestionInfo &Question, stGameResults &GameResult)
{
    if (GameResult.QuestionsLevel == enQuestionLevel::Mix)
    {
        Question.QuestionLevel = (enQuestionLevel)GetRandNum(1, 3);
    }
    else
    {
        Question.QuestionLevel = GameResult.QuestionsLevel;
    }

    if (GameResult.OpType == enOperationType::mix)
    {
        Question.OperationType = GetRandomOperationType();
    }

    else
    {
        Question.OperationType = GameResult.OpType;
    }
    
    SetQuestion(Question);

    PrintQuestionFormat(Question, GameResult.NumberofQuestions);

    std::cin >> Question.UserAnswer;

    Question.CorrectAnswer = GetCorrectAnswer(Question);

    if (Question.UserAnswer == Question.CorrectAnswer)
    {
        Question.IsCorrectAnswer = true;
    }
    else
    {
        Question.IsCorrectAnswer = false;
    }

    SetQuestionResult(Question.IsCorrectAnswer, Question.CorrectAnswer);
}

void StartQuestionsLoop(stQuestionInfo &Question, stGameResults &GameResult)
{
    for (short i = 1; i <= GameResult.NumberofQuestions; i++)
    {
        Question.QuestionNumber = i;

        StartQuestion(Question, GameResult);

        if (Question.IsCorrectAnswer == true)
        {
            GameResult.NumberofCorrectAnswers++;
        }

        else
        {
            GameResult.NumberofWrongAnswers++;
        }
    }
}

bool PassorFail(stGameResults &GameResults)
{
    if (GameResults.NumberofCorrectAnswers > GameResults.NumberofWrongAnswers)
    {
        GameResults.PassorFail = true;

        std::cout << "\t\tPass :-)";

        return true;
    }
    else
    {
        GameResults.PassorFail = false;

        std::cout << "\t\tFail :-(";

        return false;
    }
    return false;
}

void SetGameResultScreen(stGameResults GameResults)
{
    if (GameResults.PassorFail == true)
    {
        system("color 2F");
    }

    else
    {
        system("color 4F");
        std::cout << "\a";
    }
}

void PrintGameResults(stGameResults &GameResults)
{

    SetGameResultScreen(GameResults);
    std::cout << "\n___________________________________________________________\n";

    PassorFail(GameResults);

    std::cout << "\n___________________________________________________________\n";

    std::cout << "\nNumber of Questions : " << GameResults.NumberofQuestions;
    std::cout << "\nQuestion Level : " << PrintQuestionLevelName(GameResults.QuestionsLevel);
    std::cout << "\nOperation Type : " << PrintOpName(GameResults.OpType);
    std::cout << "\nNumber Of Correct Answers : " << GameResults.NumberofCorrectAnswers;
    std::cout << "\nNumber of Wrong Answer : " << GameResults.NumberofWrongAnswers;
}

void StartGame()
{
    stQuestionInfo Question;
    stGameResults GameResult;

    GameResult.NumberofQuestions = GetNumOfQuestions("enter numer of questions you want to play : ");
    PrintQuestionLevelMenu();
    GameResult.QuestionsLevel = GetQuestionLevel();
    PrintOPerationTypeMenu();
    GameResult.OpType = GetOperationType();

    StartQuestionsLoop(Question, GameResult);

    PrintGameResults(GameResult);
}

void Start()
{
    char Play_Decision = 'N';

    do
    {
        system("cls");
        system("color 0F");
        StartGame();

        std::cout << "\nDo You Want to play again ? Y/N ? ";
        std::cin >> Play_Decision;

    } while (Play_Decision == 'Y' || Play_Decision == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    Start();

    return 0;
}