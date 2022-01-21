/**
 * @file town.h
 * @author equipo_23
 * @brief cabecera de la clase town
 */

#include <iostream>
#include <vector>
#include <list>

#include "cell.h"

struct statistics {
    bool solved;
    double time;
    int visited_nodes;
    float coste;
    int path_length;
};

class town
{
public:
    // Constructor
    town();
    // Destructor
    ~town();

    // Setters
    void setSize(int, int);
    bool setInitialPos(int, int);
    bool setEndPos(int, int);

    // Generadores del mapa
    void genObstacleRand(int);
    bool genMapFile(std::string);

    // Limpiadores
    void clearMap();
    void clearSolution();

    // Funciones de impresion
    void print();
    void printSol();
    bool printSolFile(std::string, statistics);

    // Funcion de resolución
    statistics solve(bool directions = 0, int formula = 0);

private:
    // Funciones internas
    bool solve_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, statistics &stats, bool directions = 0, int formula = 0);
    void insertNodes_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula = 0, bool directions = 0);
    void fourDirections_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula = 0);
    void eightDirections_(std::list<Cell> &open_nodes, std::list<Cell> &closed_nodes, std::list<Cell>::iterator &it, int formula = 0);
    bool isValid_(int, int);
    int isInList_(std::list<Cell> &list, Cell &node);

    // Mapa de obstaculos (0 - Camino || 1 - obstaculo)
    std::vector<std::vector<bool>> map_;
    // Mapa que contiene la solucion (0 - nada || 1 - solucion)
    std::vector<std::vector<bool>> solution;

    // Mapa para comprobar si un nodo se encuentra en la lista abierta o cerrada de forma optima
    std::vector<std::vector<bool>> openMap;
    std::vector<std::vector<bool>> closedMap;

    // Posiciones inicial y final
    std::pair<int, int> initialPos_;
    std::pair<int, int> endPos_;
    // Tamaño del mapa
    int width_;
    int height_;
};
