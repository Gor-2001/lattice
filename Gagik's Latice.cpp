#include <iostream>
#include <cstdlib>  // Include this for the rand function
using namespace std;

struct Cell
{
    int direction;
    bool existence;
};
//void ft_viruse(Cell **lattice, int lattice_size, int x, int y);
void ft_check(Cell **lattice, int lattice_size);
void ft_fill(Cell **lattice, int lattice_size);
void print_lattice(Cell **lattice, int lattice_size, bool mod);
void drop(Cell **lattice, int lattice_size);

int main()
{
    int lattice_size = 200;
    int bugs_count = 10000;  // Declare and initialize bugs_count
    Cell **lattice = new Cell *[lattice_size];
    for (int i = 0; i < lattice_size; ++i)
        lattice[i] = new Cell[lattice_size];
    ft_fill(lattice, lattice_size);
    for (int i = 0; i < bugs_count; ++i)
    drop(lattice, lattice_size);  // Corrected function name
    print_lattice(lattice, lattice_size, 0);

    return (0);
}



// Filling the lattice with random directions and remove all bugs
void ft_fill(Cell **lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            lattice[i][j].existence = 0;
            lattice[i][j].direction = (rand() % 4) + 1;
        }
    }
}

// For bug's count mod = 0 and mod = 1 otherwise.
void print_lattice(Cell **lattice, int lattice_size, bool mod)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            if (!mod)
                cout << lattice[i][j].existence;
            if (mod)
                cout << lattice[i][j].direction;
        }
        cout << endl;
    }
}


//Droping the bugs.
void drop(Cell **lattice, int lattice_size)
{
    int row = lattice_size / 2;
    int column = lattice_size / 2;

    for (; lattice[row][column].existence == 1 && 0 <= row && row < lattice_size - 1 && 0 <= column && column < lattice_size - 1;)
    {
        if (lattice[row][column].direction == 1)
        {
            lattice[row][column].direction = 2;
            ++column;
        }

        if (lattice[row][column].direction == 3)
        {
            lattice[row][column].direction = 4;
            --column;
        }

        if (lattice[row][column].direction == 2)
        {
            lattice[row][column].direction = 3;
            --row;
        }
        if (lattice[row][column].direction == 4)
        {
            lattice[row][column].direction = 1;
            ++row;
        }
    }
    lattice[row][column].existence = 1;
}

void ft_check(Cell **lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            if (!lattice[i][j].existence)
            {
                cout << "Congratulations, you find me I am in coordinates \(" << i << "," << j << ").\n";
                return ;
            }

        }
    }
    cout << "You Lose\n";
}

/*void ft_viruse(Cell **lattice, int lattice_size, int x, int y)
{
    if (x >= 0  && y >= 0 && x < lattice_size  && y < lattice_size && !lattice[x][y].existence)
      {
        ++lattice[x][y].existence;
        ft_viruse(lattice, lattice_size, x+1, y);
        ft_viruse(lattice, lattice_size, x, y+1);
        ft_viruse(lattice, lattice_size, x, y-1);
        ft_viruse(lattice, lattice_size, x-1, y);
      }
    else
        return ;
}*/
