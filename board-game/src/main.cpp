#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

const u_int8_t BOARD_ROWS = 5;
const u_int8_t BOARD_COLS = 5;
const u_int8_t BOARD_SIZE = (BOARD_ROWS * BOARD_COLS);

const u_int8_t MAX_REWARD = 5;
const u_int8_t MAX_TURNS = 10;
const u_int16_t MAX_WINNINGS = (MAX_REWARD * MAX_REWARD) * MAX_TURNS;
const int16_t WINNING_VALUE = MAX_WINNINGS / 5;

struct Card
{
    u_int8_t reward; // 0-255; final value is always ^2
    bool isVisited{false};
};

void initBoard(Card **board)
{
    for (auto row = 0; row < BOARD_ROWS; ++row)
    {
        for (auto col = 0; col < BOARD_COLS; ++col)
        {
            board[row][col].reward = std::rand() % MAX_REWARD;
        }
    }
};

void shuffleBoard(Card **board)
{
    std::srand(unsigned(std::time(0)));
    for (auto row = 0; row < BOARD_ROWS; ++row)
    {
        for (auto col = 0; col < BOARD_COLS; ++col)
        {
            auto randomRow = std::rand() % BOARD_ROWS;
            auto randomCol = std::rand() % BOARD_COLS;

            std::swap(board[randomRow][randomCol], board[row][col]);
        }
    }
}

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

void printBoard(Card **board, int currentWinnings, u_int8_t turnsLeft, std::string message = "")
{
    clearScreen();

    if (!message.empty())
    {
        std::cout << message << "\n\n";
    }

    std::cout << "Turns Left: " << static_cast<int>(turnsLeft) << " | Current Winnings: " << currentWinnings << " | Winning Value: " << WINNING_VALUE << "\n\n";
    for (auto row = 0; row < BOARD_ROWS; ++row)
    {
        for (auto col = 0; col < BOARD_COLS; ++col)
        {
            auto card = board[row][col];
            std::cout << "[" + (card.isVisited ? std::to_string(static_cast<int>(card.reward)) : "X") + "] ";
        }
        std::cout << std::endl;
    }
};

void destroyBoard(Card **board)
{
    for (auto row = 0; row < BOARD_ROWS; ++row)
    {
        delete[] board[row];
    }
    delete[] board;
}

int main(int argc, char const *argv[])
{
    Card **board = new Card *[BOARD_ROWS];
    for (int i = 0; i < BOARD_ROWS; ++i)
    {
        board[i] = new Card[BOARD_COLS];
    }

    initBoard(board);
    shuffleBoard(board);

    u_int32_t winnings{0};
    u_int16_t turns{0};
    std::string msg{""};
    while (true)
    {
        printBoard(board, winnings, MAX_TURNS - turns, msg);
        msg = "";

        std::cout << "Coordinates to reveal (X;Y): ";
        std::string inputPoint;
        std::cin >> inputPoint;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (inputPoint.empty())
        {
            msg = "Input cannot be empty";
            continue;
        }

        if (inputPoint.size() < 3)
        {
            msg = "Invalid input; Should be at least 3 characters";
            continue;
        }

        auto delimiterIdx = inputPoint.find(';');
        if (delimiterIdx == std::string::npos)
        {
            // std::cout << "Invalid input; No delimiter found (';')" << std::endl;
            msg = "Invalid input; No delimiter found (';')";
            continue;
        }

        auto coordinates = inputPoint.find(';');
        auto x = std::stoi(inputPoint.substr(0, coordinates));
        auto y = std::stoi(inputPoint.substr(coordinates + 1));
        if (x < 0 || x >= BOARD_ROWS || y < 0 || y >= BOARD_COLS)
        {
            msg = "Invalid input; Coordinates out of bounds";
            continue;
        }

        if (board[x][y].isVisited)
        {
            msg = "Already visited";
            continue;
        }

        board[x][y].isVisited = true;
        winnings += std::pow(board[x][y].reward, 2);

        if (winnings >= WINNING_VALUE)
        {
            printBoard(board, winnings, MAX_TURNS - turns, "Game over! You won!");
            break;
        }

        if (++turns == MAX_TURNS)
        {
            printBoard(board, winnings, 0, "Game over! Max turns reached!");
            break;
        }
    }

    destroyBoard(board);

    return 0;
}
