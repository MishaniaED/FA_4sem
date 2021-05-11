#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Recurtion_search(vector<string>);
bool Iteration_serch(vector<string>);


const int SIZE = 8;
int board[SIZE][SIZE];
int results_count = 0; // Количество решений.
vector<vector<pair<int, int>>> vect; // хранение всех решений

void showBoard()
{
    for (int a = 0; a < SIZE; ++a) {
        for (int b = 0; b < SIZE; ++b)
            cout << ((board[a][b]) ? "Q " : ". ");
        cout << '\n';
    }
}

// Рекурсивно
// Функция tryQueen() - проверяет нет ли уже установленных ферзей по вертикали и диагоналям.
bool tryQueen(int a, int b)
{
    for (int i = 0; i < a; ++i)
        if (board[i][b])
            return false;

    for (int i = 1; i <= a && b - i >= 0; ++i)
        if (board[a - i][b - i])
            return false;

    for (int i = 1; i <= a && b + i < SIZE; i++)
        if (board[a - i][b + i])
            return false;

    return true;
}

// Функция setQueen() - пробует найти результаты решений.
void setQueen(int a, vector<pair<int, int>> &vec) // a - номер очередной строки в которую нужно поставить очередного ферзя.
{
    if (a == SIZE) {
        showBoard();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j] == 1) {
                    vec.push_back(make_pair(i+1, j+1));
                    cout << "Q("<<i+1<<";"<<j+1<<")\n";
                }
            }
        }
        vect.push_back(vec);
        vec.clear();
        cout << "Result #" << ++results_count << "\n\n";
        return;
    }

    for (int i = 0; i < SIZE; ++i) {
        if (tryQueen(a, i)) {   // проверка что ферзьбудет единственным в этой строке, столбце и диагоналях.
            board[a][i] = 1;
            setQueen(a + 1, vec);
            board[a][i] = 0;
        }
    }
}

int main() {
	int flag;
    vector<pair<int, int>> vec;
	cout << "Рow do you want to solve the problem?\n"<<"Recurtion -- 1\n"<<"Iteration -- 2\n"<<"Your choice: ";
	cin >> flag;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }
	if (flag == 1) {
        setQueen(0, vec);
	}
    else {
        // как сделать не рекурсивно не понял(
    }

    // проверял на одинаковые расстановки
    /*sort(vect.begin(), vect.end());
    auto it = unique(vect.begin(), vect.end());
    vect.resize(distance(vect.begin(), it));
    int counter = 0;
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < SIZE; j++)
            cout <<"Q("<< vect[i][j].first << ";"<< vect[i][j].second <<")\n"; 
        cout << endl;
        counter++;
    }
    cout << counter;*/
	return 0;
}