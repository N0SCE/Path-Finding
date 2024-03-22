#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>

#include "Sector.h"


class SpaceSectorBST {
  
public:
    Sector *root;
    Sector* temp;
    Sector* previous;
    Sector* node = nullptr;
    //Sector* node_to_remove = nullptr;    
    Sector* head_to_remove = nullptr;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename); 
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    Sector* deleteSectorRecursively(const std::string& sector_code, Sector* nodeDelete);

    void checkLeft(int x, int y, int z);
    void checkRight(int x, int y, int z);
    bool find_element(std::vector<Sector*> vector, Sector* find_node);
    Sector* find_node(std::string sector_code);
    bool is_checking_subtree = false;
    bool is_checking = false; 
    bool is_checking_preorder = false;
    bool is_checking_postorder = false;
    bool is_checking_path = false;
    std::vector<std::string> sector_code_letters;
    std::stack<Sector*> nodes;
    std::vector<Sector*> nodes_to_delete;
};

#endif // SPACESECTORBST_H
