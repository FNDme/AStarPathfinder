#include <iostream>
#include "town.h"
#include "colors.h"

int main(void)
{
    town mapa;

    // Consola o ficheros
    int output_decision = 0;
    while ((output_decision != 1) && (output_decision != 2))
    {
        output_decision = 0;
        system("clear");
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        std::cout << BOLDCYAN << "\n\t¿Desea que la salida sea por consola o por ficheros?\n" << RESET;
        std::cout << BOLDCYAN << "\n\t1. Consola\n" << RESET;
        std::cout << BOLDCYAN << "\n\t2. Ficheros\n\n" << RESET;
        std::cout << GREEN << "\n\t Su elección >>\t" << RESET;
        std::cin >> output_decision;
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
    }
    
    // Tipo de funcionamiento
    int decision = 0;
    while ((decision != 1) && (decision != 2))
    {
        decision = 0;
        system("clear");
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        std::cout << BOLDCYAN << "\n\t¿Desea introducir los obstaculos de manera manual o aleatoria?\n" << RESET;
        std::cout << BOLDCYAN << "\n\t1. MANUAL\n" << RESET;
        std::cout << BOLDCYAN << "\n\t2. ALEATORIA\n\n" << RESET;
        std::cout << BOLDCYAN << "\n\tIMPORTANTE: los obstáculos, de ser establecidos manualmente, se deberán adjuntar en un fichero.\n" << RESET;
        std::cout << GREEN << "\n\t Su elección >>\t" << RESET;
        std::cin >> decision;
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
    }

    // Eleccion
    if (decision == 1)
    {
        // Ficheros
        bool ok = false;
        std::string filename;
        while (!ok)
        {
            filename = "";
            std::cout << YELLOW << "\n\t Introduzca el nombre del fichero : " << RESET;
            std::cin >> filename;
            ok = mapa.genMapFile(filename);
        }
    }
    else
    {
        // Generacion automatica
        // M x N
        int width = 0, height = 0;
        while (width <= 0 || height <= 0)
        {
            width = height = 0;
            system("clear");
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la altura y la anchura del mapa.\n" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << GREEN << "\n\t Anchura >>\t" << RESET;
            std::cin >> width;
            std::cout << GREEN << "\n\t Altura >>\t" << RESET;
            std::cin >> height;
        }
        mapa.setSize(width, height);

        // Porcentaje de obstaculos
        int percentage = -1;
        while (decision == 2 && (percentage < 0 || percentage > 100))
        {
            percentage = -1;
            std::cout << YELLOW << "\n\t Introduzca un porcentaje de obstáculos ( 0 - 100 % ) : " << RESET;
            std::cin >> percentage;
            mapa.genObstacleRand(percentage);
        }

        // Posicion inicial
        int init_pos_x = 0, init_pos_y = 0;
        bool ok = false;
        while (init_pos_x <= 0 || init_pos_y <= 0 || ok == false)
        {
            init_pos_x = init_pos_y = 0;
            system("clear");
            mapa.print();
            std::cout << YELLOW << "\n\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la posicion X e Y de inicio.\n" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << GREEN << "\n\t Pos X >>\t" << RESET;
            std::cin >> init_pos_x;
            std::cout << GREEN << "\n\t Pos Y >>\t" << RESET;
            std::cin >> init_pos_y;
            ok = mapa.setInitialPos(init_pos_x, init_pos_y);
        }

        // Posicion final
        int end_pos_x = 0, end_pos_y = 0;
        ok = false;
        while (end_pos_x <= 0 || end_pos_y <= 0 || ok == false)
        {
            end_pos_x = end_pos_y = 0;
            system("clear");
            mapa.print();
            std::cout << YELLOW << "\n\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tIntroduzca la posicion X e Y de destino.\n" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << GREEN << "\n\t Pos X >>\t" << RESET;
            std::cin >> end_pos_x;
            std::cout << GREEN << "\n\t Pos Y >>\t" << RESET;
            std::cin >> end_pos_y;
            ok = mapa.setEndPos(end_pos_x, end_pos_y);
        }
    }

    int nMovements = 0;
    while ((nMovements != 1) && (nMovements != 2))
    {
        nMovements = 0;
        system("clear");
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        std::cout << BOLDCYAN << "\n\t¿Cuantas direcciones podra realizar el vehiculo?\n" << RESET;
        std::cout << BOLDCYAN << "\n\t1. 4 Direcciones\n" << RESET;
        std::cout << BOLDCYAN << "\n\t2. 8 Direcciones\n\n" << RESET;
        std::cout << GREEN << "\n\n\t Su elección >>\t" << RESET;
        std::cin >> nMovements;
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
    }

    int formula = 0;
    while ((formula < 1) || (formula > 3))
    {
        formula = 0;
        system("clear");
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        std::cout << BOLDCYAN << "\n\t¿Que tipo de funcion heuristica desea utilizar?\n" << RESET;
        if (nMovements == 1)
        {
            std::cout << BOLDCYAN << "\n\t1. Distancia de Manhattan" << GREEN << "  (Mejor opcion)\n" << RESET;
            std::cout << BOLDCYAN << "\n\t2. Distancia Euclideana\n" << RESET;
        } else {
            std::cout << BOLDCYAN << "\n\t1. Distancia de Manhattan\n" << RESET;
            std::cout << BOLDCYAN << "\n\t2. Distancia Euclideana" << GREEN << "  (Mejor opcion)\n" << RESET;
        }
        
        std::cout << BOLDCYAN << "\n\t3. Distancia de Chevyshev\n" << RESET;
        std::cout << GREEN << "\n\t Su elección >>\t" << RESET;
        std::cin >> formula;
        std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
    }

    system("clear");
    statistics solution = mapa.solve(nMovements - 1, formula);
    if (output_decision == 1)
    {
        if(solution.solved) 
        {
            mapa.printSol();
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tTiempo: " << solution.time << "s\n" << RESET;
            std::cout << BOLDCYAN << "\n\tCantidad de nodos recorridos: " << solution.visited_nodes << "\n" << RESET;
            std::cout << BOLDCYAN << "\n\tTamaño del camino: " << solution.path_length << "\n" << RESET;
            std::cout << BOLDCYAN << "\n\tCoste de la solucion: " << solution.coste << "\n" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        }
        else 
        {
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tNo se ha podido encontrar la solucion del mapa" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        }
    }
    else
    {   if(solution.solved) 
        {
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tTiempo: " << solution.time << "s\n" << RESET;
            std::cout << BOLDCYAN << "\n\tCantidad de nodos recorridos: " << solution.visited_nodes << "\n" << RESET;
            std::cout << BOLDCYAN << "\n\tTamaño del camino: " << solution.path_length << "\n" << RESET;
            std::cout << BOLDCYAN << "\n\tCoste de la solucion: " << solution.coste << "\n" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            mapa.printSolFile("output.txt", solution);
        }
        else 
        {
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
            std::cout << BOLDCYAN << "\n\tNo se ha podido encontrar la solucion del mapa" << RESET;
            std::cout << YELLOW << "\n--------------------------------------------------------\n" << RESET;
        }
    }
    
    return 0;
}
