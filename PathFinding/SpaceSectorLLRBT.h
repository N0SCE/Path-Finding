#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <stack>

class SpaceSectorLLRBT {
public:
    Sector* root = nullptr;
    
    Sector* temp;
    Sector* previous;
    Sector* node = nullptr;
    Sector* node_to_remove = nullptr;
    Sector* head_to_remove = nullptr;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);

    void checkLeft(int x, int y, int z);
    void checkRight(int x, int y, int z);
    bool find_element(std::vector<Sector*> vector, Sector* find_node);
    void checkTree(Sector* node);
    Sector* find_node(std::string sector_code);
    void flipColors(Sector* node_to_flip);
    Sector* rotateLeft(Sector* node_to_rotate);
    Sector* rotateRight(Sector* node_to_rotate);
    Sector* insert(Sector* node_to_insert, int x, int y, int z);
    bool isRed(Sector* node_to_check);
    void swapColors(Sector* first_node, Sector* second_node);
    bool is_checking_subtree = false;
    bool is_checking = false;
    bool is_checking_preorder = false;
    bool is_checking_postorder = false;
    bool is_checking_path = false;
    std::vector<std::string> sector_code_letters;
    std::stack<Sector*> nodes;
    std::vector<Sector*> nodes_to_delete;
};

#endif // SPACESECTORLLRBT_H
