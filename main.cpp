#include <iostream>
#include <conio.h>
#include <locale.h>
#include <time.h>
#include <vector>

using namespace std;

bool gameOver;
const int widht = 26;
const int height = 20;
char keyBoard;
int score;
int x,y,Fruit_x,Fruit_y;
bool isFruitEaten;


enum class Trail {
    FALSE,
    FIRST,
    TRUE
};
Trail isTrail;
int prevX, prevY;
int curTrailX, curTrailY;
int firstTrailX, firstTrailY;
int lastTrailX, lastTrailY;
int Trail[widht][height];

enum class Letters {
    a = 97,
    s = 115,
    d = 100,
    w = 119,
    Russian_a = 10100000,
    Russian_s = 11101011,
    Russian_d = 10100010,
    Russian_w = 11100110
};

enum class Dir {
    LEFT,
    DOWN,
    RIGHT,
    UP
};

Dir* Moves = new Dir [10000];
int movesCount;

vector <int> getLastTrail (int x, int y) {
    int i = movesCount - 1;
    while (1) {
        if (Moves[i] == Dir::LEFT) {
            ++x;
            if (Trail[x][y] == 0) {
                x--;
                break;
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::UP) {
            ++y;
            if (Trail[x][y] == 0) {
                y--;
                break;
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::RIGHT) {
            x--;
            if (Trail[x][y] == 0) {
                x++;
                break;
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::DOWN) {
            y--;
            if (Trail[x][y] == 0) {
                y++;
                break;
            }
            i--;
            continue;
        }
    }
    vector <int> lastTrail(2);
    lastTrail[0] = x;
    lastTrail[1] = y;
    return lastTrail;
}

void changeTrail(){ 
/*    if (direction == Dir::LEFT) {
        firstTrailX = prevX;
    }
    if (direction == Dir::UP) {
        firstTrailY = prevY;
    }
    if (direction == Dir::RIGHT) {
        firstTrailX = prevX;
    }
    if (direction == Dir::DOWN) {
        firstTrailY = prevY;
    }
*/
    firstTrailX = prevX;
    firstTrailY = prevY;
    Trail[firstTrailX][firstTrailY] = 1;
    if (x == Fruit_x && y == Fruit_y) {
        Trail[lastTrailX][lastTrailY] = 1;
        return;
    }
    else {
        Trail[lastTrailX][lastTrailY] = 0;
    }
    vector <int> lastTrail(2);
    lastTrail = getLastTrail(x, y);
    lastTrailX = lastTrail[0];
    lastTrailY = lastTrail[1];
/*    if (Trail[lastTrailX + 1][lastTrailY] == 1) {
        if (getTrailsAround(lastTrailX, lastTrailY) ==
            getTrailsAround(lastTrailX + 1, lastTrailY) + 1) {
            
            lastTrailX += 1;    
        }
        
    } 
    else if (Trail[lastTrailX - 1][lastTrailY] == 1) {
        if (getTrailsAround(lastTrailX, lastTrailY) ==
            getTrailsAround(lastTrailX + 1, lastTrailY) + 1) {
        
            lastTrailX -= 1;
        }
    }
    else if (Trail[lastTrailX][lastTrailY + 1] == 1) {
        if (getTrailsAround(lastTrailX, lastTrailY) ==
            getTrailsAround(lastTrailX + 1, lastTrailY) + 1) {
        
            lastTrailY += 1;
        }
    }
    else if (Trail[lastTrailX][lastTrailY - 1] == 1) {
        if (getTrailsAround(lastTrailX, lastTrailY) ==
            getTrailsAround(lastTrailX + 1, lastTrailY) + 1) {

            lastTrailY -= 1;
        }
    }
    */
//    cout << lastTrailX << lastTrailY << endl;
    return;
}

void DrawField() {
    system("cls");
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < widht; ++j) {
            if(Trail[j][i] == 1) {
                cout << "o";
                continue;
            }
            if ((x != 0 && y != 0) && (j == x && i == y)){
                cout << "O";
                continue;
            }
            if ((x != 0 && y != 0) && (j == Fruit_x && i == Fruit_y)){
                cout << "F";
                continue;
            }
            if (i == 0 || i == height - 1) {
                cout << "#";
            }
            else if ((i != 0 && i != height - 1) && (j == 0 || j == widht - 1)) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
        
    }
    cout << "SCORE: " << score;
    cout << endl;
    cout << endl;
    cout << endl;
}

void Start () {
    gameOver = false;
    keyBoard = ' ';
    x = widht / 2;
    y = height / 2;
    srand(time(NULL));
    Fruit_x = rand() % (widht - 2) + 1;
    Fruit_y = rand() % (height - 2) + 1;
    isFruitEaten = false;
    isTrail = Trail::FALSE;
    score = 0;
    movesCount = 0;
    for (int i = 0; i < widht; ++i) {
        for (int j = 0; j < height; ++j) {
            Trail[i][j] = 0;
        }
    }
}

void Move() {
    int keyBoard;
/*    if (isTrail == Trail::FALSE) {
        prevX = x;
        prevY = y;
    }
*/
    prevX = x;
    prevY = y;
    switch (keyBoard = _getch()) {
        case (int)Letters::s:
            y = y + 1;
            Moves[movesCount] = Dir::DOWN;
            movesCount++;
            if (isTrail != Trail::FALSE) {
                changeTrail();
            }
            break;
        case (int)Letters::a:
            x = x - 1;
            Moves[movesCount] = Dir::LEFT;
            movesCount++;
            if (isTrail != Trail::FALSE) {
                changeTrail();
            }
            break;
        case (int)Letters::w:
            y = y - 1;
            Moves[movesCount] = Dir::UP;
            movesCount++;
            if (isTrail != Trail::FALSE) {
                changeTrail();

            }
            break;
        case (int)Letters::d:
            x = x + 1;
            Moves[movesCount] = Dir::RIGHT;
            movesCount++;
            if (isTrail != Trail::FALSE) {
                changeTrail();
            }
            break;
/*        case (int)Letters::Russian_s:
            y = y + 1;
            break;
        case (int)Letters::Russian_a:
            x = x - 1;
            break;
        case (int)Letters::Russian_w:
            y = y - 1;
            break;
        case (int)Letters::Russian_d:
            x = x + 1;
            break;        
        }
        */
    }
}

void Logic() {
    if (x == 0 || y == 0 || x == widht - 1 || y == height - 1) {
        gameOver = true;
        return;
    }
    if (x == Fruit_x && y == Fruit_y) {
        isFruitEaten = true;
    }
    if (isFruitEaten == true && isTrail == Trail::FIRST) {
        isTrail = Trail::TRUE;
    }
    if (isFruitEaten == true && isTrail == Trail::FALSE) {
        isTrail = Trail::FIRST;
        firstTrailX = prevX;
        firstTrailY = prevY;
        lastTrailX = prevX;
        lastTrailY = prevY;
        Trail[prevX][prevY] = 1;
    }


    if (isFruitEaten) {
        Fruit_x = rand() % (widht - 2) + 1;
        Fruit_y = rand() % (height - 2) + 1;
        ++score;
        isFruitEaten = false;
    }
    if (Trail[x][y] == 1) {
        gameOver = true;
    }

}

int main() {
    setlocale(LC_ALL, "rus");
    Start();
    while (!gameOver) {
        if (_kbhit) {
            DrawField();
            Move();
            Logic();
        }
    }
    delete [] Moves;
    cout << "GAME OVER" << endl;
    getchar();
    return 0;
}
