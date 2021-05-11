#include <iostream>
#include <vector>
using namespace std;

#define SIZE 8

class VIRT {
    virtual bool tryQueen(int a, int b) const = 0;
    virtual void setQueen(int a, vector<pair<int, int>>& vec) = 0;
};

class Board {
public:
    friend class Recurs;
    int board[8][8];
    int results_count = 0; // Количество решений.
    vector<vector<pair<int, int>>> vect; // хранение всех решений

    void set() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                board[i][j] = 0;
            }
        }
    }
};

class Iterat : public VIRT
{
    
};

class Recurs : public VIRT
{
private: 
    Board b;
public:
    
    void showBoard() const 
    {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j)
                cout << ((b.board[i][i]) ? "Q " : ". ");
            cout << '\n';
        }
    }

    bool tryQueen(int a, int j) const override
    {
        for (int i = 0; i < a; ++i)
            if (b.board[i][j])
                return false;

        for (int i = 1; i <= a && j - i >= 0; ++i)
            if (b.board[a - i][j - i])
                return false;

        for (int i = 1; i <= a && j + i < SIZE; i++)
            if (b.board[a - i][j + i])
                return false;

        return true;
    }

    // Функция setQueen() - пробует найти результаты решений.
    void setQueen(int a, vector<pair<int, int>>& vec) override // a - номер очередной строки в которую нужно поставить очередного ферзя.
    {
        if (a == SIZE) {
            //showBoard();
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (b.board[i][j] == 1) {
                        vec.push_back(make_pair(i + 1, j + 1));
                        cout << "Q(" << i + 1 << ";" << j + 1 << ")\n";
                    }
                }
            }
            b.vect.push_back(vec);
            vec.clear();
            cout << "Result #" << ++(b.results_count)<< "\n\n";
            return;
        }

        for (int i = 0; i < SIZE; ++i) {
            if (tryQueen(a, i)) {   // проверка что ферзьбудет единственным в этой строке, столбце и диагоналях.
                b.board[a][i] = 1;
                setQueen(a + 1, vec);
                b.board[a][i] = 0;
            }
        }
    }
};


