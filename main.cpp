#include <iostream>
#include <cstdlib>  // Include this for the rand function
using namespace std;

//for traveling around cell
static int rowNbr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
static int colNbr[] = { -1, 0, 1, -1, 1, -1, 0, 1 };


struct Cell
{
    int direction;
    int odometr;
    bool existence;
    bool visited;
};
//fill something 
void all_directions_same(Cell** lattice, int lattice_size, int fixed_direction);
void odometr_reset_to_zero(Cell** lattice, int lattice_size);
void random_fill_directions(Cell** lattice, int lattice_size);
void bugs_reset_to_zero(Cell** lattice, int lattice_size);

//print somthing
void print_directions(Cell** lattice, int lattice_size);
void print_existence(Cell** lattice, int lattice_size);
void print_odometr(Cell** lattice, int lattice_size);
void print_odometr_supp(Cell** lattice, int lattice_size);
//drop
void drop(Cell** lattice, int lattice_size);
void drop_and_print_every_step(Cell** lattice, int lattice_size);

//cout of islands
int countIslands(Cell** lattice, int lattice_size);
void DFS(Cell** lattice, int lattice_size, int row, int col);
bool isSafe(Cell** lattice, int lattice_size, int row, int col);

int main()
{
    int latice_small_size = 8;
    int lattice_size = 2 * latice_small_size + 1;
    int bugs_count = 100;  // Declare and initialize bugs_count

    Cell** lattice = new Cell * [lattice_size];
    for (int i = 0; i < lattice_size; ++i)
        lattice[i] = new Cell[lattice_size];


    all_directions_same(lattice, lattice_size, 1);
    odometr_reset_to_zero(lattice, lattice_size);
    random_fill_directions(lattice, lattice_size);
    bugs_reset_to_zero(lattice, lattice_size);

    //print_directions(lattice, lattice_size);
    lattice[0][1].existence = 1;
    lattice[1][0].existence = 1;
    lattice[1][1].existence = 1;

    for (int i = 0; i < bugs_count; ++i)
        //drop_and_print_every_step(lattice, lattice_size);
    {
        drop(lattice, lattice_size);// Corrected function name
        if (i % 10 == 9) {
            print_odometr_supp(lattice, lattice_size);
            cout << endl;
        }
    }
    //print_odometr(lattice, lattice_size);
    cout << endl;

    print_existence(lattice, lattice_size);
    int count_of_islands_from_zero = countIslands(lattice, lattice_size);
    cout << endl << "count of island is " << count_of_islands_from_zero;
    return (0);
}
//Droping the bugs.
void drop(Cell** lattice, int lattice_size)
{
    int row = (lattice_size - 1) / 2;
    int column = (lattice_size - 1) / 2;

    for (; lattice[row][column].existence == 1;)
    {
        if (!(0 < row && row < lattice_size - 2 && 0 < column && column < lattice_size - 2))
        {
            cout << "Not enough place" << endl;
            break;
        }
        lattice[row][column].odometr += 1;
        if (lattice[row][column].direction == 1)
        {
            lattice[row][column].direction = 2;
            ++row;
        }

        if (lattice[row][column].direction == 3)
        {
            lattice[row][column].direction = 4;
            --row;
        }

        if (lattice[row][column].direction == 2)
        {
            lattice[row][column].direction = 3;
            ++column;
        }
        if (lattice[row][column].direction == 4)
        {
            lattice[row][column].direction = 1;
            --column;
        }
    }
    lattice[row][column].existence = 1;
}

bool isSafe(Cell** lattice, int lattice_size, int row, int col)
{
    return (row >= 0) && (row < lattice_size) && (col >= 0)
        && (col < lattice_size)
        && (lattice[row][col].existence == 0 && lattice[row][col].visited == false);
}

void DFS(Cell** lattice, int lattice_size, int row, int col)
{
    lattice[row][col].visited = true;

    for (int k = 0; k < 8; ++k)
        if (isSafe(lattice, lattice_size, row + rowNbr[k], col + colNbr[k]))
            DFS(lattice, lattice_size, row + rowNbr[k], col + colNbr[k]);
}

int countIslands(Cell** lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; i++) {
        for (int j = 0; j < lattice_size; j++) {
            lattice[i][j].visited == false;
        }
    }
    int count = 0;
    for (int i = 0; i < lattice_size; ++i)
        for (int j = 0; j < lattice_size; ++j)
            if (lattice[i][j].existence == 0 && lattice[i][j].visited == false) {
                DFS(lattice, lattice_size, i, j);
                ++count;
            }

    return count;
}

void drop_and_print_every_step(Cell** lattice, int lattice_size)
{
    int row = (lattice_size - 1) / 2;
    int column = (lattice_size - 1) / 2;

    for (; lattice[row][column].existence == 1;)
    {
        if (!(0 < row && row < lattice_size - 2 && 0 < column && column < lattice_size - 2))
        {
            cout << "Not enough place" << endl;
            break;
        }
        lattice[row][column].odometr += 1;
        if (lattice[row][column].direction == 1)
        {
            lattice[row][column].direction = 2;
            ++row;
        }

        if (lattice[row][column].direction == 3)
        {
            lattice[row][column].direction = 4;
            --row;
        }

        if (lattice[row][column].direction == 2)
        {
            lattice[row][column].direction = 3;
            ++column;
        }
        if (lattice[row][column].direction == 4)
        {
            lattice[row][column].direction = 1;
            --column;
        }
    }
    lattice[row][column].existence = 1;
    print_existence(lattice, lattice_size);
    print_directions(lattice, lattice_size);
    cout << endl;
}

void random_fill_directions(Cell** lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            lattice[i][j].direction = (rand() % 4) + 1;
        }
    }
}

void odometr_reset_to_zero(Cell** lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            lattice[i][j].odometr = 0;
        }
    }
}


void bugs_reset_to_zero(Cell** lattice, int lattice_size)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            lattice[i][j].existence = 0;
        }
    }
}

void all_directions_same(Cell** lattice, int lattice_size, int fixed_direction)
{
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            lattice[i][j].direction = fixed_direction;
        }
    }
}

void print_existence(Cell** lattice, int lattice_size)
{
    cout << "existence" << endl;
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            cout << lattice[i][j].existence;
        }
        cout << endl;
    }
}

void print_directions(Cell** lattice, int lattice_size)
{
    cout << "directions" << endl;
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            cout << lattice[i][j].direction;
        }
        cout << endl;
    }
}


void print_odometr(Cell** lattice, int lattice_size)
{
    cout << "odometr" << endl;
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            cout << lattice[i][j].odometr << " ";
        }
        cout << endl;
    }
}
void print_odometr_supp(Cell** lattice, int lattice_size)
{
    cout << "odometr_supp" << endl;
    for (int i = 0; i < lattice_size; ++i)
    {
        for (int j = 0; j < lattice_size; ++j)
        {
            if (lattice[i][j].odometr == 0)
                cout << 0;
            else
                cout << 1;
        }
        cout << endl;
    }
}





/*void ft_check(Cell **lattice, int lattice_size)
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
*/