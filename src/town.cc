#include <vector>
#include <list>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <climits>
#include <sys/time.h>

#include "town.h"
#include "colors.h"

#define MAX_COST 10000
#define DIAGONAL_COST 1.414213
#define ADJOINING_COST 1

// Constructor por defecto
town::town()
{
    initialPos_ = std::make_pair(-1, -1);
    endPos_ = std::make_pair(-1, -1);
}

// Destructor por defecto
town::~town()
{
    for (int i = width_ - 1; i >= 0; i--)
    {
        for (size_t j = 0; j < height_; j++)
            map_[i].pop_back();
        map_.pop_back();
    }
}

// Generacion del mapa y establecimiento de los tamaños
void town::setSize(int width, int height)
{
    width_ = width;
    height_ = height;
    std::vector<bool> aux;
    for (size_t i = 0; i < height_; i++)
        aux.push_back(0);
    for (size_t i = 0; i < width_; i++)
        map_.push_back(aux);
}

// Establecimiento de la posicion inicial
bool town::setInitialPos(int X, int Y)
{
    if (X > 0 && Y > 0 && X != endPos_.first && Y != endPos_.second && X <= width_ && Y <= height_ && !map_[X - 1][Y - 1])
    {
        initialPos_.first = X - 1;
        initialPos_.second = Y - 1;
        return true;
    }
    else
    {
        return false;
    }
}

// Establecimiento de la posicion final
bool town::setEndPos(int X, int Y)
{
    if (X > 0 && Y > 0 && X != initialPos_.first && Y != initialPos_.second && X <= width_ && Y <= height_ && !map_[X - 1][Y - 1])
    {
        endPos_.first = X - 1;
        endPos_.second = Y - 1;
        return true;
    }
    return false;
}

// Generacion de los obstaculos de forma aleatoria
void town::genObstacleRand(int perc)
{
    int sz = width_ * height_;
    int counter = 0;
    float percentage = perc * 0.01;
    sz = sz * percentage;
    int i = 0, j = 0;
    while (counter < sz)
    {
        i = rand() % width_;
        j = rand() % height_;
        if (!map_[i][j] && (i != initialPos_.first || j != initialPos_.second) && (i != endPos_.first || j != endPos_.second))
        {
            map_[i][j] = !map_[i][j];
            counter++;
        }
    }
}

// Generacion del mapa a traves de un fichero
bool town::genMapFile(std::string filename)
{
    std::ifstream File;
    File.open(filename, std::ios::in);
    if (File.is_open())
    {
        this->clearMap();
        int width, height;
        File >> width >> height;
        this->setSize(width, height);
        int input;
        for (size_t j = 0; j < height; j++)
            for (size_t i = 0; i < width_; i++)
            {
                File >> input;
                if (input == 2)
                {
                    initialPos_ = std::make_pair(i, j);
                }
                else if (input == 3)
                {
                    endPos_ = std::make_pair(i, j);
                }
                else if (input == 0 || input == 1)
                {
                    map_[i][j] = input;
                }
            }
        File.close();
        return true;
    }
    File.close();
    return false;
}

// Limpiador de obstaculos
void town::clearMap(void)
{
    if (!map_.empty())
    {
        for (int i = width_ - 1; i >= 0; i--)
        {
            for (size_t j = 0; j < height_; j++)
                map_[i].pop_back();
            map_.pop_back();
        }
        initialPos_ = std::make_pair(-1, -1);
        endPos_ = std::make_pair(-1, -1);
        width_ = 0;
        height_ = 0;
    }
}

// Limpiador de la solucion
void town::clearSolution(void)
{
    std::vector<bool> aux;
    for (size_t i = 0; i < height_; i++)
        aux.push_back(0);
    for (size_t i = 0; i < width_; i++)
        solution.push_back(aux);
}

// Impresion por consola
void town::print()
{
    std::cout << "\t\t┌";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┐\n";

    for (size_t i = 0; i < height_; i++)
    {
        std::cout << "\t\t|";
        for (size_t j = 0; j < width_; j++)
            if (initialPos_.first == j && initialPos_.second == i)
                std::cout << BG_GREEN << BLACK << "b" << RESET;
            else if (endPos_.first == j && endPos_.second == i)
                std::cout << BG_BLUE << BLACK << "e" << RESET;
            else if (map_[j][i])
                std::cout << BLACK << "█" << RESET;
            else
                std::cout << WHITE << "█" << RESET;
        std::cout << "|\n";
    }

    std::cout << "\t\t└";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┘\n";
}

// Impresion de la solucion por consola
void town::printSol()
{
    std::cout << "\t\t┌";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┐\n";

    for (size_t i = 0; i < height_; i++)
    {
        std::cout << "\t\t|" << RESET;
        for (size_t j = 0; j < width_; j++)
            if (initialPos_.first == j && initialPos_.second == i)
                std::cout << BG_GREEN << BLACK << "b" << RESET;
            else if (endPos_.first == j && endPos_.second == i)
                std::cout << BG_BLUE << BLACK << "e" << RESET;
            else if (solution[j][i])
                std::cout << BG_MAGENTA << "·" << RESET;
            else if (map_[j][i])
                std::cout << BLACK << "█" << RESET;
            else
                std::cout << WHITE << "█" << RESET;
        std::cout << "|\n"
                  << RESET;
    }

    std::cout << "\t\t└";
    for (size_t i = 0; i < width_; i++)
        std::cout << "─";
    std::cout << "┘\n";
}

bool town::printSolFile(std::string filename, statistics stats)
{
    std::ofstream File;
    File.open(filename, std::ios::out);
    if (File.is_open())
    {
        File << width_ << "x" << height_ << "\n"
             << "Tiempo requerido para la resolucion del algoritmo: " << stats.time << "\n"
             << "Cantidad de nodos recorridos: " << stats.visited_nodes << "\n"
             << "Tamaño del camino: " << stats.path_length << "\n"
             << "Coste de la solucion: " << stats.coste << "\n";

        File << "\t\t┌";
        for (size_t i = 0; i < width_; i++)
            File << "─";
        File << "┐\n";

        for (size_t i = 0; i < height_; i++)
        {
            File << "\t\t|";
            for (size_t j = 0; j < width_; j++)
                if (initialPos_.first == j && initialPos_.second == i)
                    File << "b";
                else if (endPos_.first == j && endPos_.second == i)
                    File << "e";
                else if (solution[j][i])
                    File << "·";
                else if (map_[j][i])
                    File << "█";
                else
                    File << " ";
            File << "|\n";
        }

        File << "\t\t└";
        for (size_t i = 0; i < width_; i++)
            File << "─";
        File << "┘\n";

        File.close();
        return true;
    }
    File.close();
    return false;
}

// Funcion de resolucion
statistics town::solve(bool directions, int formula)
{
    statistics data;
    data.visited_nodes = 0;
    data.path_length = 0;
    std::list<Cell> open_nodes;
    std::list<Cell> closed_nodes;
    clearSolution();
    openMap = solution;
    closedMap = solution;
    open_nodes.push_back(Cell(initialPos_, 0, endPos_, formula));

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    data.solved = solve_(open_nodes, closed_nodes, data, directions, formula);

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    data.time = seconds + microseconds * 1e-6;

    return data;
}

// Funcion interna de resolucion
bool town::solve_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, statistics &data, bool directions, int formula)
{
    data.solved = false;
    Cell better_sol(std::make_pair(0, 0), MAX_COST, endPos_, formula);
    if (initialPos_ == endPos_) {
        data.solved = true;
        return true;
    }
    while (!open_nodes.empty())
    {
        std::list<Cell>::iterator it = open_nodes.begin();
        ++data.visited_nodes;
        if (it->getPos() == endPos_)
        {
            data.solved = true;
            if (it->getFCost() <= better_sol.getFCost())
                better_sol = *it;
            closed_nodes.push_back(*it);
            closedMap[it->getX()][it->getY()] = true;
            open_nodes.erase(it);
            openMap[it->getX()][it->getY()] = false;
        }
        else
        {
            closed_nodes.push_back(*it);
            closedMap[it->getX()][it->getY()] = true;
            open_nodes.erase(it);
            openMap[it->getX()][it->getY()] = false;
            std::list<Cell>::iterator iter = closed_nodes.end();
            --iter;
            insertNodes_(open_nodes, closed_nodes, iter, formula, directions);
        }
    }
    if (data.solved)
    {
        data.coste = better_sol.getCost();
        while (better_sol.getFather() != NULL)
        {
            solution[better_sol.getX()][better_sol.getY()] = true;
            better_sol = *better_sol.getFather();
            ++data.path_length;
        }
        return true;
    }
    return false;
}

// Funcion de insercion de los nodos en la lista abierta
void town::insertNodes_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula, bool directions)
{
    switch (directions)
    {
    case 0:
        fourDirections_(open_nodes, closed_nodes, it, formula);
        break;
    case 1:
        eightDirections_(open_nodes, closed_nodes, it, formula);
        break;
    }
}

void town::fourDirections_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula)
{
    // left
    if (isValid_(it->getX() - 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() - 1, it->getY()), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // right
    if (isValid_(it->getX() + 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() + 1, it->getY()), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // up
    if (isValid_(it->getX(), it->getY() - 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() - 1), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // down
    if (isValid_(it->getX(), it->getY() + 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() + 1), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
}

void town::eightDirections_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula)
{
    // left
    if (isValid_(it->getX() - 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() - 1, it->getY()), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // left-up
    if (isValid_(it->getX() - 1, it->getY() - 1))
    {
        Cell insert_cell(std::make_pair(it->getX() - 1, it->getY() - 1), it->getCost() + DIAGONAL_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // up
    if (isValid_(it->getX(), it->getY() - 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() - 1), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // right-up
    if (isValid_(it->getX() + 1, it->getY() - 1))
    {
        Cell insert_cell(std::make_pair(it->getX() + 1, it->getY() - 1), it->getCost() + DIAGONAL_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // right
    if (isValid_(it->getX() + 1, it->getY()))
    {
        Cell insert_cell(std::make_pair(it->getX() + 1, it->getY()), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // right-down
    if (isValid_(it->getX() + 1, it->getY() + 1))
    {
        Cell insert_cell(std::make_pair(it->getX() + 1, it->getY() + 1), it->getCost() + DIAGONAL_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // down
    if (isValid_(it->getX(), it->getY() + 1))
    {
        Cell insert_cell(std::make_pair(it->getX(), it->getY() + 1), it->getCost() + ADJOINING_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
    // left-down
    if (isValid_(it->getX() - 1, it->getY() + 1))
    {
        Cell insert_cell(std::make_pair(it->getX() - 1, it->getY() + 1), it->getCost() + DIAGONAL_COST, endPos_, formula);
        insert_cell.setFather(&*it);
        if (openMap[insert_cell.getX()][insert_cell.getY()])
        {
            int i = isInList_(open_nodes, insert_cell);
            std::list<Cell>::iterator open_nodes_pos = open_nodes.begin();
            std::advance(open_nodes_pos, i);
            if (open_nodes_pos->getFCost() > insert_cell.getFCost())
            {
                open_nodes_pos->setCost(insert_cell.getCost());
                open_nodes_pos->setFather(insert_cell.getFather());
                open_nodes_pos->setFCost(insert_cell.getFCost());
                std::list<Cell>::iterator k = open_nodes_pos;
                --k;
                while (k->getFCost() > open_nodes_pos->getFCost())
                    --k;
                open_nodes.splice(k, open_nodes, open_nodes_pos);
            }
        }
        else
        {
            if (!closedMap[insert_cell.getX()][insert_cell.getY()])
            {
                std::list<Cell>::iterator k = open_nodes.end();
                while (k->getFCost() > insert_cell.getFCost())
                    --k;
                open_nodes.insert(k, insert_cell);
                openMap[insert_cell.getX()][insert_cell.getY()] = true;
            }
        }
    }
}

// Funcion que valida o no una posicion del mapa
bool town::isValid_(int X, int Y)
{
    if (X >= 0 && Y >= 0 && X < width_ && Y < height_ && !map_[X][Y])
        return true;
    return false;
}

// Funcion que comprueba si un nodo esta en una lista y en caso afirmativo devuelve el indice
int town::isInList_(std::list<Cell> &list, Cell &node)
{
    std::list<Cell>::iterator it;
    int pos = 0;
    for (it = list.begin(); it != list.end(); ++it)
    {
        if (it->getPos() == node.getPos())
            return pos;
        ++pos;
    }
    return -1;
}
