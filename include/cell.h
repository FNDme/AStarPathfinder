/**
 * @file cell.h
 * @author equipo_23
 * @brief Fichero de cabecera de la clase Cell
 */

#include <iostream>

class Cell
{
public:
    // Constructores
    Cell();
    Cell(std::pair<int, int>, float);
    Cell(std::pair<int, int>, float, std::pair<int, int>, int);
    // Destructor
    ~Cell();

    // Setters
    void setCost(float);
    void setCost(float, std::pair<int, int>, int);
    void setFCost(float);
    void setFCost(std::pair<int, int>, int);
    void setPos(int, int);
    void setPos(std::pair<int, int> pos);
    void setFather(Cell *);

    // Getters
    std::pair<int, int> getPos();
    int getX();
    int getY();
    float getCost();
    float getFCost();
    Cell *getFather();

private:
    float manhattanDistance_(std::pair<int, int>, std::pair<int, int>);
    float euclideanDistance_(std::pair<int, int>, std::pair<int, int>);
    float chevyshevDistance_(std::pair<int, int>, std::pair<int, int>);

    float evaluate_(std::pair<int, int>, int);

    // Celda padre
    Cell *father_;
    // Posicion en el mapa
    std::pair<int, int> pos_;
    // Coste para alcanzar la celda
    float cost_;

    float fCost_;
};
