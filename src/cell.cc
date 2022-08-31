#include <math.h>
#include "cell.h"

// Constructor por defecto
Cell::Cell()
{
    father_ = NULL;
}

// Constructor dada la posicion y el coste
Cell::Cell(std::pair<int, int> pos, float cost)
{
    pos_ = pos;
    cost_ = cost;
    father_ = NULL;
}

Cell::Cell(std::pair<int, int> pos, float cost, std::pair<int, int> destination, int whichFormula)
{
    pos_ = pos;
    cost_ = cost;
    father_ = NULL;
    fCost_ = evaluate_(destination, whichFormula);
}

// Destructor por defecto
Cell::~Cell() {}

// Devuelve la posicion de la celda
std::pair<int, int> Cell::getPos()
{
    return pos_;
}

// Devuelve la posicion X de la celda
int Cell::getX()
{
    return pos_.first;
}

// Devuelve la posicion Y de la celda
int Cell::getY()
{
    return pos_.second;
}

// Devuelve el coste para alcanzar la celda
float Cell::getCost()
{
    return cost_;
}

float Cell::getFCost()
{
    return fCost_;
}

// Devuelve un puntero a la celda padre
Cell *Cell::getFather()
{
    return father_;
}

// Establece el coste para alcanzar la celda
void Cell::setCost(float cost)
{
    cost_ = cost;
}

void Cell::setCost(float cost, std::pair<int, int> destination, int whichFormula)
{
    cost_ = cost;
    fCost_ = evaluate_(destination, whichFormula);
}

void Cell::setFCost(float f_cost)
{
    fCost_ = f_cost;
}

// Establece la posicion de la celda
void Cell::setPos(int X, int Y)
{
    pos_ = std::make_pair(X, Y);
}

// Establece la posicion de la celda
void Cell::setPos(std::pair<int, int> pos)
{
    pos_ = pos;
}

// Establece la direccion del padre de la celda
void Cell::setFather(Cell *father)
{
    father_ = father;
}

// Funcion que calcula la distancia de Manhattan
float Cell::manhattanDistance_(std::pair<int, int> point, std::pair<int, int> destination)
{
    return (abs(point.first - destination.first) + abs(point.second - destination.second));
}

// Funcion que calcula la distancia euclideana
float Cell::euclideanDistance_(std::pair<int, int> point, std::pair<int, int> destination)
{
    return sqrt(pow(abs(point.first - destination.first), 2) + pow(abs(point.second - destination.second), 2));
}

// Funcion que calcula la distancia de Chevyshev
float Cell::chevyshevDistance_(std::pair<int, int> point, std::pair<int, int> destination)
{
    return std::max(abs(point.first - destination.first), abs(point.second - destination.second));
}

float Cell::evaluate_(std::pair<int, int> destination, int whichFormula)
{
    float aux;
    switch (whichFormula)
    {
    case 0:
        aux = cost_ + manhattanDistance_(getPos(), destination);
        break;
    case 1:
        aux = cost_ + euclideanDistance_(getPos(), destination);
        break;
    case 2:
        aux = cost_ + chevyshevDistance_(getPos(), destination);
        break;
    default:
        aux = cost_ + manhattanDistance_(getPos(), destination);
        break;
    }
    return aux;
}
