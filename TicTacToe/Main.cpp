#include <iostream>
#include "SFML\Graphics.hpp"

using namespace std;
using namespace sf;

#define MAX_GRID 4
#define APP_WIDTH 316
#define APP_HEIGHT 400

int dx[] = { -1, 0, 1, 1 };
int dy[] = { -1, -1, -1, 0 };
int maps[MAX_GRID][MAX_GRID];
int tWidth, tHeight, mouseRow, mouseCol;
char turn;
Event event;
Texture cell, resetIcon;
Sprite sCell, sresetIcon;
Text uText;
Font uFont;
Vector2i mousePos;
int tempR, tempC;
int res;
bool isWin;

void Winner(int r, int c, char curTurn, int n)
{
    //int resX = 1;
    //int resO = 1;
    int nR, nC;
    for (int ii = 0; ii < 4; ii = ii + 1)
    {
        res = 1;
        for (int jj = 1; jj <= n; jj = jj + 1)
        {
            nR = r + dy[ii] * jj;
            nC = c + dx[ii] * jj;
            if (nR >= 0 && nR < n && nC >= 0 && nC < n && maps[r][c] != 0)
            {
                if (maps[nR][nC] == maps[r][c])
                {
                    res = res + 1;
                }
            }
            nR = r - dy[ii] * jj;
            nC = c - dx[ii] * jj;
            if (nR >= 0 && nR < n && nC >= 0 && nC < n && maps[r][c] != 0)
            {
                if (maps[nR][nC] == maps[r][c])
                {
                    res = res + 1;
                }
            }
            if (res == 3)
            {
                isWin = true;
                return;
            }
        }
    }
}

void Reset()
{
    for (int r = 0; r < 3; r = r + 1)
    {
        for (int c = 0; c < 3; c = c + 1)
        {
            maps[r][c] = 0;
        }
    }
    isWin = false;
}

int main()
{
    RenderWindow mainActivity(VideoMode(APP_WIDTH, APP_HEIGHT), "Tic Tac Toe Game");

    cell.loadFromFile("boards1.png");
    resetIcon.loadFromFile("reseticon.png");
    //cell.setSmooth(true);
    sCell.setTexture(cell);
    sresetIcon.setTexture(resetIcon);
    tWidth = cell.getSize().x;
    tHeight = cell.getSize().y;
    tWidth = tWidth / 3;
    //tHeight = tHeight / 3;

    //Init
    Reset();
    turn = 'X';

    uFont.loadFromFile("Roboto-Black.ttf");
    uText.setFont(uFont);
    uText.setString("Turn: ");
    uText.setFillColor(Color::Black);
    uText.setCharacterSize(25);

    while (mainActivity.isOpen())
    {
        mousePos = Mouse::getPosition(mainActivity);
        mouseRow = mousePos.x / tWidth;
        mouseCol = mousePos.y / tWidth;

        while (mainActivity.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                mainActivity.close();
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                if (mouseRow < 3 && mouseCol < 3 && maps[mouseRow][mouseCol] == 0 && event.key.code == Mouse::Left && isWin == false)
                {
                    tempR = mouseRow;
                    tempC = mouseCol;
                    switch (turn)
                    {
                    case 'X':
                    {
                        maps[mouseRow][mouseCol] = 2;
                        turn = 'O';
                        break;
                    }
                    default:
                        maps[mouseRow][mouseCol] = 1;
                        turn = 'X';
                        break;
                    }
                }
                else if (mousePos.x >= sresetIcon.getPosition().x && mousePos.x <= sresetIcon.getPosition().x + 64 && mousePos.y >= sresetIcon.getPosition().y && mousePos.y <= sresetIcon.getPosition().y + 64)
                {
                    Reset();
                }
            }
        }

        //Display board
        mainActivity.clear(Color::White);

        for (int row = 0; row < 3; row = row + 1)
        {
            for (int col = 0; col < 3; col = col + 1)
            {
                sCell.setPosition(row * tWidth, col * tHeight);
                if (maps[row][col] == 0)
                {
                    sCell.setTextureRect(IntRect(0, 0, tWidth, tHeight));
                }
                else if (maps[row][col] == 1)
                {
                    sCell.setTextureRect(IntRect(tWidth, 0, tWidth, tHeight));
                }
                else
                {
                    sCell.setTextureRect(IntRect(2 * tWidth, 0, tWidth, tHeight));
                }
                mainActivity.draw(sCell);
            }
        }
        sresetIcon.setPosition(126, 330);
        uText.setString("Turn: ");
        uText.setPosition(10, 3 * tHeight + 10);
        mainActivity.draw(uText);
        uText.setString(turn);
        uText.setPosition(80, 3 * tHeight + 10);
        mainActivity.draw(sresetIcon);
        mainActivity.draw(uText);

        //Find out and show the winner
        Winner(tempR, tempC, turn, 3);
        if (isWin == true)
        {
            //cout << turn << " Winnn!" << endl;
            //Reset();
            mainActivity.clear(Color::White);
            uText.setString("Winner: ");
            uText.setPosition(100, 150);
            mainActivity.draw(uText);
            if (turn == 'X') uText.setString('O');
            else uText.setString('X');
            uText.setPosition(190, 150);
            sresetIcon.setPosition(126, 190);
            mainActivity.draw(sresetIcon);
            mainActivity.draw(uText);
        }

        mainActivity.display();
    }
    return 0;
}