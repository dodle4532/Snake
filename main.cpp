#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <chrono>


using namespace std;

bool delay(int j)
{
    j=j*10000000;
    for (int i = 1; i < j; i++)
    {
        if (_kbhit()) {
            return false;
        }
    }
    return true;
}

bool gameOver;
const int widht = 26;
const int height = 20;
unsigned char keyBoard;
int score;
int x,y,Fruit_x,Fruit_y;
bool isFruitEaten;

enum class GameMode : int{
    EASY = 49,
    MEDIUM,
    HARD,
    EXTREME
};
GameMode gamemode;

enum class TRAIL {
    FALSE = 0,
    FIRST,
    TRUE
};
TRAIL isTrail;
int prevX, prevY;
int firstTrailX, firstTrailY;
int lastTrailX, lastTrailY;
int Trail[widht][height];
bool isBorderCrossed;
bool flag;

enum class Letters {
    a = 97,
    s = 115,
    d = 100,
    w = 119,
    Russian_a = 228,
    Russian_s = 235,
    Russian_d = 162,
    Russian_w = 230
};

enum class Dir {
    LEFT,
    DOWN,
    RIGHT,
    UP
};

Dir* Moves;
int movesCount;

bool isBorderCrossedX (int x) {
    if (gamemode == GameMode::EASY && abs(x - prevX) > 1) {
        return true;
    }
    return false;
}


vector <int> getLastTrail (int x, int y) {
    int i = movesCount - 1;
    while (1) {
        if (Moves[i] == Dir::LEFT) {
            if (x == widht - 2) {
                x = 1;
                if (Trail[x][y] == 0) {
                    x = widht - 2;
                    break;
                }
            }
            else {
                ++x;
                if (Trail[x][y] == 0) {
                    x--;
                    break;
                }
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::UP) {
            if (y == height - 2) {
                y = 1;
                if (Trail[x][y] == 0) {
                    y = height - 2;
                    break;
                }
            }
            else {
                ++y;
                if (Trail[x][y] == 0) {
                    y--;
                    break;
                }
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::RIGHT) {
            if (x == 1) {
                x = widht - 2;
                if (Trail[x][y] == 0) {
                    x = 1;
                    break;
                }
            }
            else {
                x--;
                if (Trail[x][y] == 0) {
                    x++;
                    break;
                }
            }
            i--;
            continue;
        }
        if (Moves[i] == Dir::DOWN) {
            if (y == 1) {
                y = height - 2;
                if (Trail[x][y] == 0) {
                    y = 1;
                    break;
                }
            }
            else {
                y--;
                if (Trail[x][y] == 0) {
                    y++;
                    break;
                }
            }
            i--;
            continue;
        }
    }
    vector <int> lastTrail(2);
    lastTrail[0] = x;
    lastTrail[1] = y;
    if (x == Fruit_x && y == Fruit_y) {
        movesCount = 1;
    }
    return lastTrail;
}

void changeTrail(){ 
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
    isBorderCrossed = false;
    gameOver = false;
    keyBoard = ' ';
    x = widht / 2;
    y = height / 2;
    srand(time(NULL));
    Fruit_x = rand() % (widht - 2) + 1;
    Fruit_y = rand() % (height - 2) + 1;
    isFruitEaten = false;
    isTrail = TRAIL::FALSE;
    score = 0;
    movesCount = 0;
    for (int i = 0; i < widht; ++i) {
        for (int j = 0; j < height; ++j) {
            Trail[i][j] = 0;
        }
    }
    if (gamemode == GameMode::HARD 
        || gamemode == GameMode::EXTREME) {
        Moves = new Dir [10000];
        return;
    }
    else {
        Moves = new Dir[1000];
    }
}

void Move(unsigned char keyBoard) {
    prevX = x;
    prevY = y;
    switch (keyBoard) {
        case (unsigned char)Letters::s:
            y = y + 1;
            Moves[movesCount] = Dir::DOWN;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;
        case (unsigned char)Letters::a:
            x = x - 1;
            Moves[movesCount] = Dir::LEFT;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;
        case (unsigned char)Letters::w:
            y = y - 1;
            Moves[movesCount] = Dir::UP;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();

            }
            break;
        case (unsigned char)Letters::d:
            x = x + 1;
            Moves[movesCount] = Dir::RIGHT;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;
        case (unsigned char)Letters::Russian_s:
            y = y + 1;
            Moves[movesCount] = Dir::DOWN;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;
        case (unsigned char)Letters::Russian_a:
            x = x - 1;
            Moves[movesCount] = Dir::LEFT;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;
        case (unsigned char)Letters::Russian_w:
            y = y - 1;
            Moves[movesCount] = Dir::UP;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();

            }
            break;
        case (unsigned char)Letters::Russian_d:
            x = x + 1;
            Moves[movesCount] = Dir::RIGHT;
            movesCount++;
            if (isTrail != TRAIL::FALSE) {
                changeTrail();
            }
            break;        
    }
        
}

void Logic() {
    if (isBorderCrossed == true) {
        isBorderCrossed == false;
    }
    if (gamemode != GameMode::EASY) {
        if (x == 0 || y == 0 || x == widht - 1 || y == height - 1) {
            gameOver = true;
            return;
        }
    }
    if (gamemode == GameMode::EASY) {
        if (x == 0) {
            x = widht - 2;
            isBorderCrossed = true;
        }
        else if (y == 0) {
            y = height - 2;
            isBorderCrossed = true;
        }
        else if(x == widht - 1) { 
            x = 1;
            isBorderCrossed = true;
        }
        else if (y == height - 1) {
            y = 1;
            isBorderCrossed = true;
        }
    }
    if (x == Fruit_x && y == Fruit_y) {
        isFruitEaten = true;
    }
    if (isFruitEaten == true && isTrail == TRAIL::FIRST) {
        isTrail = TRAIL::TRUE;
    }
    if (isFruitEaten == true && isTrail == TRAIL::FALSE) {
        isTrail = TRAIL::FIRST;
        firstTrailX = prevX;
        firstTrailY = prevY;
        lastTrailX = prevX;
        lastTrailY = prevY;
        Trail[prevX][prevY] = 1;
    }


    if (isFruitEaten) {
        while (1) {
            Fruit_x = rand() % (widht - 2) + 1;
            Fruit_y = rand() % (height - 2) + 1;
            if (Trail[Fruit_x][Fruit_y] == 0) {
                break;
            }
        }
        ++score;
        isFruitEaten = false;
    }
    if (Trail[x][y] == 1) {
        gameOver = true;
    }
    if (movesCount > 999) {
        gameOver = true;
    }

}

int main() {
    cout << "Choose your gamemode(just type his number)" << endl;
    cout << "1. Easy" << endl;
    cout << "2. Medium" << endl;
    cout << "3. Hard" << endl;
    cout << "4. Extreme" << endl;
    int gm;
    gm = _getch();
    if (gm < (static_cast<int>(GameMode::EASY)) ||
        gm > (static_cast<int>(GameMode::EXTREME))) {
        delete [] Moves;
        cout << "ERROR" << endl;
        getchar();
        getchar();
        return 0;
    }
    switch(gm) {
        case static_cast<int>(GameMode::EASY): {
            gamemode = GameMode::EASY;
            break;
        }
        case static_cast<int>(GameMode::MEDIUM): {
            gamemode = GameMode::MEDIUM;
            break;
        }
        case static_cast<int>(GameMode::HARD): {
            gamemode = GameMode::HARD;
            break;
        }
        case static_cast<int>(GameMode::EXTREME): {
            gamemode = GameMode::EXTREME;
            break;
        }
        
    }
    Start();
    while (!gameOver) {
        if (gamemode == GameMode::EASY
            || gamemode == GameMode::MEDIUM) {
            if (_kbhit) {
                DrawField();
                keyBoard = _getch();
                Move(keyBoard);
                Logic();
                if (score == 50) {
                    cout << "You win!!!" << endl;
                    getchar();
                    getchar();
                    return 0;
                }
            }
        }
        else if (gamemode == GameMode::HARD) {
            flag = false;
            auto start = chrono::steady_clock::now();
            DrawField();
            while (!_kbhit()) {
                auto end = chrono::steady_clock::now();
                if (chrono::duration_cast<chrono::milliseconds>(end - start).count() > 150) { 
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                keyBoard = _getch();
            }
            else {
                if (Moves[movesCount] == Dir::RIGHT) {
                    keyBoard = 'd';
                }
            }
            Move(keyBoard);
            Logic();
        }
        else {
            flag = false;
            auto start = chrono::steady_clock::now();
            DrawField();
            while (!_kbhit()) {
                auto end = chrono::steady_clock::now();
                if (chrono::duration_cast<chrono::milliseconds>(end - start).count() > 70) { 
                    flag = true;
                    break;
                }
            }
            if (flag == false) {
                keyBoard = _getch();
            }
            else {
                if (Moves[movesCount] == Dir::RIGHT) {
                    keyBoard = 'd';
                }
            }
            Move(keyBoard);
            Logic();
        }
    }
    delete [] Moves;
    cout << "GAME OVER" << endl;
    getchar();
    getchar();
    return 0;
}
