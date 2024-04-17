// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT2L 
// Names: Sharleen Ravi Mahendra | Nor Aliah Syuhaidah binti Sharuddin | Nur Farah Nabila binti Ramzairi
// IDs: 1211102087 | 1211102031 | 1221301140
// Emails: 1211102087@student.mmu.edu.my | 1211102031@student.mmu.edu.my | 1221301140@student.mmu.edu.my
// Phones: 010-8032495 | 018-7611854 | 012-6510599
// *********************************************************

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

void displayGameboard(int rows, int columns, int zombies)
{
    cout << ".: Alien vs Zombie :." << endl; // Add the title above the gameboard
    cout << endl;

    char **gameboard = new char *[rows];

    for (int i = 0; i < rows; i++)
    {
        gameboard[i] = new char[columns];
    }

    int alienRow = rows / 2;
    int alienCol = columns / 2;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == alienRow && j == alienCol)
            {
                gameboard[i][j] = 'A';
            }

            else
            {
                gameboard[i][j] = '|';
            }
        }
    }

    int zombiesPlaced = 0;
    while (zombiesPlaced < zombies)
    {
        int row = getRandomNumber(0, rows - 1);
        int col = getRandomNumber(0, columns - 1);
        if (row != alienRow || col != alienCol)
        {
            if (gameboard[row][col] == '|')
            {
                gameboard[row][col] = 'Z';
                zombiesPlaced++;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << gameboard[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < rows; i++)
    {
        delete[] gameboard[i];
    }
    delete[] gameboard;
}

struct Alien
{
    int life;
    int attack;
};

struct Zombie
{
    int life;
    int attack;
    int range;
};

void initializeAlien(Alien &alien)
{
    alien.life = rand() % 10 + 1;
    alien.attack = 0;
}

void initializeZombie(Zombie *zombie, int rows, int columns)
{
    zombie->life = rand() % 10 + 1;
    zombie->attack = rand() % 10 + 1;
    zombie->range = rand() % min(rows, columns) + 1;
}

int main()
{
    srand(time(NULL));

    int rows = 5;
    int columns = 9;
    int zombies = 1;

    char o;

    cout << "Default Game Setting";
    cout << "\n_______________________";
    cout << "\n\nBoard Rows: 5";
    cout << "\nBoard Columns: 9";
    cout << "\nZombie Count: 1";

    cout << "\n\nDo you want to change the default game settings (y/n)? : ";
    cin >> o;

    if (o == 'y' || o == 'Y') // accept 'y' or 'Y'
    {
        // Prompt user for new game settings
        cout << "\n\nBoard Settings ";
        cout << "\n_____________________" << endl; // add endl here to move to next line
        cout << "\n\nEnter number of rows (minimum 3): ";
        cin >> rows;

        // Check if input is valid
        while (rows < 3)
        {
            cout << "Invalid input. Enter number of rows (minimum 3): ";
            cin >> rows;
        }

        cout << "Enter number of columns (minimum 3): ";
        cin >> columns;

        // Check if input is valid
        while (columns < 3)
        {
            cout << "Invalid input. Enter number of columns (minimum 3): ";
            cin >> columns;
        }

        cout << "Enter number of zombies (1-9): ";
        cin >> zombies;

        if (zombies < 1 || zombies > 9)
        {
            cout << "Invalid input. Minimum zombies = 1, maximum zombies = 9." << endl;
            return 0;
        }
    }
    else if (o != 'n' && o != 'N') // if input is neither 'y' nor 'n', display error message and exit
    {
        cout << "Invalid input. Only 'y' or 'n' is accepted." << endl;
        return 1; // return 1 to indicate an error occurred
    }

    // Display game settings
    cout << "\nGame Setting";
    cout << "\n_______________________";
    cout << "\n\nBoard Rows: " << rows;
    cout << "\nBoard Columns: " << columns;
    cout << "\nZombie Count: " << zombies << endl;
    cout << endl;

    // Display gameboard
    displayGameboard(rows, columns, zombies);

    // Initialize alien and zombies
    Alien alien;
    vector<Zombie> zombiesVector;
    zombiesVector.resize(zombies);

    initializeAlien(alien);

    // Initialize zombies
    for (int i = 0; i < zombiesVector.size(); i++)
    {
        initializeZombie(&zombiesVector[i], rows, columns);
    }

    // Display alien and zombie stats
    cout << "\nAlien: " << alien.life << " life, " << alien.attack << " attack";

    for (int i = 0; i < zombiesVector.size(); i++)
    {
        cout << "\nZombie " << i + 1 << ": " << zombiesVector[i].life << " life, " << zombiesVector[i].attack << " attack, " << zombiesVector[i].range << " range";
    }

    return 0;
}