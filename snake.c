#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
void setup(int *snakeX, int *snakeY, int *fruitX, int *fruitY, int x, int y, int flag)
{
    if (flag == 1)
    {
        *snakeX = x / 2;
        *snakeY = y / 2;
    }
    *fruitX = rand() % (x - 2) + 2;
    *fruitY = rand() % (y - 2) + 2;
}

void draw(int snakeX, int snakeY, int fruitX, int fruitY, int x, int y, int score, int snakeLenX[], int snakeLenY[], int len, int level)
{
    printf("\n");
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            if (i == 1 || i == x || j == 1 || j == y)
            {
                printf("#");
            }
            else
            {
                if (i == snakeX && j == snakeY)
                {
                    printf("@");
                }
                else if (i == fruitX && j == fruitY)
                {
                    printf("*");
                }
                else
                {
                    int printed = 0;
                    for (int k = 0; k < len; k++)
                    {
                        if (snakeLenX[k] == i && snakeLenY[k] == j && level != 1)
                        {
                            printed = 1;
                            printf("0");
                            break;
                        }
                    }
                    if (!printed)
                    {
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("Enter (w:up)/(s:down)/(a:left)/(d:right)/(x:exit): ");
    printf("\n\nScore: %d", score);
}

void update(int snakeLenX[], int snakeLenY[], int len, int snakeX, int snakeY)
{
    for (int i = len; i > 0; i--)
    {
        snakeLenX[i] = snakeLenX[i - 1];
        snakeLenY[i] = snakeLenY[i - 1];
    }
    snakeLenX[0] = snakeX;
    snakeLenY[0] = snakeY;
}

int collision(int snakeX[], int snakeY[], int len)
{
    for (int i = 1; i < len; i++)
    {
        if (snakeX[i] == snakeX[0] && snakeY[i] == snakeY[0])
            return 1;
    }
    return 0;
}

void input(char *prev_dir, char *dir, int *snakeY, int *snakeX, int level)
{
    if (_kbhit())
    {
        char ch = getch();
        switch (ch)
        {
        case 'a':
            if (level == 1)
                *dir = 'a';
            else if (*prev_dir != 'd')
                *dir = 'a';
            break;
        case 'w':
            if (level == 1)
                *dir = 'w';
            else if (*prev_dir != 's')
                *dir = 'w';
            break;
        case 'd':
            if (level == 1)
                *dir = 'd';
            else if (*prev_dir != 'a')
                *dir = 'd';
            break;
        case 's':
            if (level == 1)
                *dir = 's';
            else if (*prev_dir != 'w')
                *dir = 's';
            break;
        case 'x':
            exit(0);
        }
    }

    switch (*dir)
    {
    case 'a':
        (*snakeY)--;
        break;
    case 'w':
        (*snakeX)--;
        break;
    case 'd':
        (*snakeY)++;
        break;
    case 's':
        (*snakeX)++;
        break;
    }
}

int checkGameOver(int *snakeX, int *snakeY, int x, int y, int level, int snakeLenX[], int snakeLenY[], int len)
{
    if (level == 1)
    {
        if (*snakeX == 1)
            *snakeX = x - 1;
        else if (*snakeX == x)
            *snakeX = 2;
        if (*snakeY == 1)
            *snakeY = y - 1;
        else if (*snakeY == y)
            *snakeY = 2;

        return 0;
    }
    else if (level == 2)
    {
        if (*snakeX == 1 || *snakeX == x || *snakeY == 1 || *snakeY == y)
            return 1;
    }
    else if (level == 3)
    {
        if (*snakeX == 1 || *snakeX == x || *snakeY == 1 || *snakeY == y || collision(snakeLenX, snakeLenY, len))
            return 1;
    }
    return 0;
}

void handleGameOver(int *snakeX, int *snakeY, int *fruitX, int *fruitY, int *len, int *score, int *newTime, int *level, int x, int y, int snakeLenX[], int snakeLenY[])
{
    system("cls");
    draw(*snakeX, *snakeY, *fruitX, *fruitY, x, y, *score, snakeLenX, snakeLenY, *len, *level);
    printf("\nGame over!\n");
    printf("You want to play again:\n1.Yes\n2.No: ");
    int flag;
    scanf("%d", &flag);
    if (flag == 2)
        exit(0);
    if (flag == 1)
    {
        setup(snakeX, snakeY, fruitX, fruitY, x, y, 1);
        *len = 0;
        *score = 0;
        *newTime = 300;
        *level = 1;
    }
    else
    {
        printf("Wrong Choice!\n");
        exit(0);
    }
}

int main()
{
    int fruitX, fruitY, snakeX, snakeY, score = 0;
    int x = 20, y = 30, newsetup = 1, len = 0, newTime = 300, level = 1;
    int snakeLenX[100], snakeLenY[100];
    char dir;
    char prev_dir;
    setup(&snakeX, &snakeY, &fruitX, &fruitY, x, y, newsetup);
    while (1)
    {
        input(&prev_dir, &dir, &snakeY, &snakeX,level);
        if (snakeX == fruitX && snakeY == fruitY)
        {
            score += 10;
            len++;
            setup(&snakeX, &snakeY, &fruitX, &fruitY, x, y, newsetup = 0);
        }
        update(snakeLenX, snakeLenY, len, snakeX, snakeY);
        if (score > 50 && score <= 100)
        {
            level = 2;
            newTime = 200;
        }
        else if (score > 100)
        {
            level = 3;
            newTime = 100;
        }
        system("cls");
        draw(snakeX, snakeY, fruitX, fruitY, x, y, score, snakeLenX, snakeLenY, len, level);
        prev_dir = dir;

        if (checkGameOver(&snakeX, &snakeY, x, y, level, snakeLenX, snakeLenY, len))
        {

            handleGameOver(&snakeX, &snakeY, &fruitX, &fruitY, &len, &score, &newTime, &level, x, y, snakeLenX, snakeLenY);
        }
        Sleep(newTime+50);
    }
    return 0;
}
