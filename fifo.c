#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define AMOUNT 5 // Amount of numbers you want <0; AMOUNT>
#define RAMS 3   // How many ram slots you
#define COLUMNS 20
#define SPEED 1 // prints per second

void printTable(int[RAMS][COLUMNS], int);
void removeFirstColumn(int[RAMS][COLUMNS]);
void addColumn(int[RAMS][COLUMNS]);
void changeSpot(int[RAMS][COLUMNS], int);
int findInRam(int[RAMS][COLUMNS], int);
int timeout(int seconds);
void moveRequestsLeft();
void printRequests();

int columnCount = 0;
int rowCount = 0;
int request = 1, lastRequest;
int requests[COLUMNS] = {};
int changes[RAMS][COLUMNS] = {};
int main()
{
    srand(time(NULL));

    int table[RAMS][COLUMNS] = {};
    while (1)
    {
        request = rand() % 6 + rand() % 5;
        if (lastRequest == request)
            continue;
        if (columnCount == COLUMNS)
        {
            removeFirstColumn(table);
            removeFirstColumn(changes);
            moveRequestsLeft();

            columnCount -= 1;
        }
        requests[columnCount] = request;
        addColumn(table);
        system("cls");

        if (!findInRam(table, request))
            changeSpot(table, request);

        printRequests();
        printTable(table, request);
        printf("Yellow - Changes\nPurple - Highlight for REQ in RAM\n");
        timeout(SPEED);
    }
}

void printTable(int table[RAMS][COLUMNS], int req)
{
    for (int i = 0; i < RAMS; i++)
    {
        printf("RAM%d", i);
        for (int j = 0; j < columnCount; j++)
        {
            if (table[i][j] == request && j == columnCount - 1)
            {
                printf("\033[0;35m");
                printf(" [%d]", table[i][j]);
                printf("\033[0m");
            }
            else if (changes[i][j] == 1)
            {
                printf("\033[0;33m");
                printf(" [%d]", table[i][j]);
                printf("\033[0m");
            }
            else
                printf(" [%d]", table[i][j]);
        }
        printf("\n");
    }
}

void removeFirstColumn(int table[RAMS][COLUMNS])
{
    for (int i = 0; i < RAMS; i++)
    {
        for (int j = 0; j < columnCount; j++)
        {
            table[i][j] = table[i][j + 1];
        }
        table[i][columnCount] = 0;
        changes[i][columnCount] = 0;
    }
}

void addColumn(int table[RAMS][COLUMNS])
{
    for (int i = 0; i < RAMS; i++)
    {
        table[i][columnCount] = table[i][columnCount - 1];
    }
    columnCount += 1;
}

void changeSpot(int table[RAMS][COLUMNS], int newValue)
{
    table[rowCount][columnCount - 1] = newValue;
    for (int i = 0; i < RAMS; i++)
    {
        changes[i][columnCount - 1] = 0;
    }
    changes[rowCount][columnCount - 1] = 1;
    rowCount++;
    if (rowCount >= RAMS)
        rowCount = 0;
}

int findInRam(int table[RAMS][COLUMNS], int what)
{
    for (int i = 0; i < RAMS; i++)
    {
        if (table[i][columnCount - 1] == what)
            return 1;
    }
    return 0;
}

int timeout(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while (clock() < endwait)
        ;

    return 1;
}

void printRequests()
{
    printf("REQ: ");
    for (int i = 0; i < columnCount; i++)
    {
        printf(" %d  ", requests[i]);
    }
    printf("\n");
}

void moveRequestsLeft()
{
    for (int i = 0; i < COLUMNS; i++)
    {
        requests[i] = requests[i + 1];
    }
}