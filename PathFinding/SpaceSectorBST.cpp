#include "SpaceSectorBST.h"
#include <cmath>

using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    // Free any dynamically allocated memory in this class.
    for (Sector* pointer : nodes_to_delete) {
        delete pointer;
    }

}


    

void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.

    std::ifstream myFile(filename);
    std::string line;    
    std::string number;
    vector<int> numbers;

    std::getline(myFile, line);
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {

            std:stringstream ss(line);
            while (std::getline(ss, number, ',')) {
                numbers.push_back(stoi(number));
            }

            
            temp = root;    
            insertSectorByCoordinates(numbers[0], numbers[1], numbers[2]);
            numbers.clear();
        }
    }


}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {
    // Instantiate and insert a new sector into the space sector BST map according to the 
    // coordinates-based comparison criteria.
    if (root == nullptr) {
        root = new Sector(x, y, z);
        nodes_to_delete.push_back(root);
        return;
    }

    
    if (x < temp->x) {
        checkLeft(x, y, z);
    }
    else if (x == temp->x) {
        if (y < temp->y) {
            checkLeft(x, y, z);
        }
        else if (y == temp->y) {
            if (z < temp->z) {
                checkLeft(x, y, z);
            }
            else if (z == temp->z) {
                // finish check
            }
            else {
                checkRight(x, y, z);
            }
        }
        else {
            checkRight(x, y, z);
        }
    }
    else {
        checkRight(x, y, z);
    }



}

void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
    sector_code_letters.push_back(sector_code.substr(sector_code.length() - 3, sector_code.length() - 2));
    sector_code_letters.push_back(sector_code.substr(sector_code.length() - 2, sector_code.length() - 1));
    sector_code_letters.push_back(sector_code.substr(sector_code.length() - 1));
    
    
    /*
    //deleteSectorRecursively(sector_code, root);

    Sector* node_to_remove = nullptr;
    Sector* node_to_remove_previous = nullptr;

    if (root->sector_code == sector_code) {
        node_to_remove = root;
    }


    // check you can delete
    if (!is_checking_subtree) {
        node = root;
    } 
    

    if (node->sector_code != sector_code && !is_checking_subtree && node_to_remove == nullptr) { // find node head to delete
        
        for (string letter : sector_code_letters) {
            if (letter == "S") {
                continue;
            }

            if (letter == "L" || letter == "D" || letter == "B") {
                node = root->left;
                break;
            }
            else {
                node = root->right;
                break;
            }
        }
    }
    is_checking_subtree = true;

    if (node_to_remove == nullptr) {

        if (node == nullptr) {
            return;
        }

        if (node->sector_code == sector_code) {
            node_to_remove = node;
            return; // you probably need to delete return
        }

        // find node to remove
        
        //node = node->left;
        //deleteSector(sector_code);
        //node = node->left;
        //deleteSector(sector_code);


        node_to_remove = find_node(sector_code);
    }
    

    if (node_to_remove != nullptr) {
        if (node_to_remove->sector_code == sector_code) {
            //delete

            //check
            if (node_to_remove->left == nullptr && node_to_remove->right == nullptr) {
                //delete node_to_remove;
                //node_to_remove = nullptr;
                //delete root->left->left->left;
                //root->left->left->left = nullptr;
                return;
            }

            if (node_to_remove->left != nullptr && node_to_remove->right == nullptr) {
                node = node_to_remove->left;
                delete node_to_remove;
                node_to_remove = node;
                return;
            }
            else if (node_to_remove->left == nullptr && node_to_remove->right != nullptr) {
                node = node_to_remove->right;
                delete node_to_remove;
                node_to_remove = node;
                return;
            }



            if (node_to_remove->left != nullptr && node_to_remove->right != nullptr) {
                if (!is_checking_subtree) {
                    node = node_to_remove->right;
                    previous = node;
                }
                is_checking_subtree = true;

                if (node->left != nullptr) {
                    previous = node;
                    node = node->left;
                    deleteSector(sector_code);
                }
                else {
                    if (node->right != nullptr) {
                        if (previous != node) {
                            previous->left = node->right;
                            //check if you need to delete child
                        }
                    }
                    temp = node_to_remove;
                    node_to_remove = node;
                    delete temp;
                    return;
                }

            }

        }
    }*/

}

void SpaceSectorBST::displaySectorsInOrder() {
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
    
    

    if (is_checking != true) {
        std::cout << "Space sectors inorder traversal:" << "\n";
        node = root;
        nodes.push(node);
        is_checking = true;
    }

    if (nodes.empty()) {
        return;
    }

    if (node == nullptr) {
        node = nodes.top();
        nodes.pop();
        return;
    }

    
    node = node->left;
    if (node != nullptr) {
        nodes.push(node);

    }
    displaySectorsInOrder();

    if (node != NULL) {
        std::cout << node->sector_code << "\n";
    }
    

    node = node->right;
    if (node != nullptr) {
        nodes.push(node);

    }
    displaySectorsInOrder();

}

void SpaceSectorBST::displaySectorsPreOrder() {
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.

    //bool is_checking;


    if (is_checking_preorder != true) {
        std::cout << "Space sectors preorder traversal:" << "\n";
        node = root;
        nodes.push(node);
        is_checking_preorder = true;
    }

    if (nodes.empty()) {
        return;
    }

    if (node == nullptr) {
        node = nodes.top();
        nodes.pop();
        return;
    }

    if (node != NULL) {
        std::cout << node->sector_code << "\n";
    }
    
    node = node->left;
    if (node != nullptr) {
        nodes.push(node);

    }
    displaySectorsPreOrder();    

    node = node->right;
    if (node != nullptr) {
        nodes.push(node);

    }
    displaySectorsPreOrder();
}

void SpaceSectorBST::displaySectorsPostOrder() { // there is a wrong printing. 43->70->45
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    std::vector<Sector*> printed;
    
    std::stack<Sector*> stack;
    std::cout << "\n";
    if (stack.empty()) {
        std::cout << "Space sectors postorder traversal:" << "\n";
        node = root;
        stack.push(node);
    }

    while (!stack.empty()) {

        //auto it = std::find(printed.begin(), printed.end(), node->left);
        if (!find_element(printed, node->left)) { //it == printed.end() 
            node = node->left;
        }
        
        if (node != nullptr && stack.top() != node) {
            stack.push(node);
        }
        else {
            if (node != stack.top()) {
                node = stack.top();
                if (node->right == nullptr) {
                    stack.pop();

                }
            }
            
            previous = node;
            //auto it = std::find(printed.begin(), printed.end(), node->right);
            if (!find_element(printed, node->right)) {//it == printed.end()
                node = node->right;
            }
            
            if (previous == node) {
                std::cout << node->sector_code << "\n";
                printed.push_back(node);
                if (!stack.empty()) {
                    if (node == stack.top()) {
                        stack.pop();
                    }
                    if (!stack.empty()) {
                        node = stack.top();
                    }
                     // check if you need to pop every time
                    //stack.pop();
                }
                
                continue;
            }


            if (node != nullptr) {
                stack.push(node);
            }
            else {
                //auto it = std::find(printed.begin(), printed.end(), previous);
                if (find_element(printed, previous)) {//it != printed.end()
                    stack.pop();
                    node = stack.top();
                    continue;
                }
                
                std::cout << previous->sector_code << "\n";
                printed.push_back(previous);
                node = stack.top();

                //it = std::find(printed.begin(), printed.end(), node->right);
                
                if (node->right != nullptr && !find_element(printed, node->right)) {//it == printed.end()
                    node = node->right;
                    stack.push(node);
                }
                //stack.pop(); // i uncommented
            }

        }


    }

    /*
    if (is_checking_postorder != true) {
        std::cout << "Space sectors postorder traversal:" << "\n";
        node = root;
        nodes.push(node);
        is_checking_postorder = true;
    }

    if (nodes.empty()) {
        return;
    }

    if (node == nullptr) {
        node = nodes.top();
        nodes.pop();
        //std::cout << node->sector_code << "\n";
        return;
    }

    auto it = std::find(printed.begin(), printed.end(), node->left);
    if (it == printed.end()) {
        node = node->left;
    }

    
    if (node != nullptr) {
        nodes.push(node);
        displaySectorsPostOrder();
    }
    else {
        node = nodes.top();
        nodes.pop();
        std::cout << node->sector_code << "\n";
        printed.push_back(node);
    }
    //displaySectorsPostOrder();    

    node = node->right;
    if (node != nullptr) {
        nodes.push(node);

    }
    else {
        node = nodes.top();
        nodes.pop();
        //std::cout << node->sector_code << "\n";
    }
    displaySectorsPostOrder();
    int x = 1; // delete
    //std::cout << node->sector_code << "\n";*/
}

std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> visited;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!
    std::cout << "\n";

    if (path.empty()) {
        node = root;
        path.push_back(node);
        visited.push_back(node);
    }

    if (root->sector_code != sector_code) {
        bool is_found = false;
        while (!is_found || !path.empty()) {

            if (path.empty()) {
                break;
            }

            if (node == nullptr) {
                node = path[path.size()-1];
                if (node->right == nullptr) {
                    path.pop_back();

                }
            }

            if (node->sector_code == sector_code) {
                is_found = true;
                break;
            }

            //auto it = std::find(visited.begin(), visited.end(), node->left);
            if (!find_element(visited, node->left)) {//it == printed.end()
                node = node->left;
                if (node != nullptr) {
                    path.push_back(node);
                    visited.push_back(node);
                    continue;
                }
            }
            else {
                //auto it = std::find(visited.begin(), visited.end(), node->right);
                if (!find_element(visited, node->right)) { // it== end()
                    node = node->right;
                    if (node != nullptr) {
                        path.push_back(node);
                        visited.push_back(node);
                        continue;
                    }
                }

                if (path.size() > 0) { // check
                    node = path[path.size() - 1];
                    //it = std::find(visited.begin(), visited.end(), node->right);
                    
                    
                    if (node->right == nullptr || find_element(visited, node->right)) {//it != visited.end()
                        path.pop_back();

                    }
                }
                
            }
            
            

            if (node == nullptr) {
                node = path[path.size() - 1];
                if (node->right == nullptr) {
                    path.pop_back();

                }
            }

            //it = std::find(visited.begin(), visited.end(), node->right);
            if (!find_element(visited, node->right)) {//it == visited.end()
                node = node->right;
                if (node != nullptr) {
                    path.push_back(node);
                    visited.push_back(node);
                    continue;
                }
            }
            else {
                if (path.size() > 0) {
                    node = path[path.size() - 1];
                    if (node->right == nullptr) {
                        //path.pop_back();

                    }
                    path.pop_back(); // check
                }
                
            }
            
            

            if (node == nullptr) {
                //continue;
            }
        }

    }
    
    std::cout << "\n";
    return path;
}

void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.

    
    if (!path.empty()) {
        std::cout << "The stellar path to Dr. Elara: ";
    }
    else {
        std::cout << "A path to Dr. Elara could not be found.";
    }
    int i = 0;
    int path_size = path.size();
    std::vector<Sector*> x;
    for (Sector* sector : path) {
        i++;
        std::cout << sector->sector_code;
        if (i != path_size) {
            std::cout << "->";
        }
    }

    std::cout << "\n";

}

void SpaceSectorBST::checkLeft(int x, int y, int z) {
    if (temp->left == nullptr) {
        temp->left = new Sector(x, y, z);
        nodes_to_delete.push_back(temp->left);
        return;
    }
    else {
        temp = temp->left;
        insertSectorByCoordinates(x, y, z);
    }
}

void SpaceSectorBST::checkRight(int x, int y, int z) {
    if (temp->right == nullptr) {
        temp->right = new Sector(x, y, z);
        nodes_to_delete.push_back(temp->right);
        return;
    }
    else {
        temp = temp->right;
        insertSectorByCoordinates(x, y, z);
    }
}

bool SpaceSectorBST::find_element(std::vector<Sector*> vector, Sector* find_node) {
    bool is_found = false;
    for (Sector* sector_node : vector) {
        if (sector_node == find_node) {
            is_found = true;
            break;
        }
    }


    return is_found;
}

Sector* SpaceSectorBST::find_node(std::string sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> visited;
    Sector* node_found = nullptr;

    if (path.empty()) {
        node = root;
        path.push_back(node);
        visited.push_back(node);
    }

    if (root->sector_code != sector_code) {
        bool is_found = false;
        while (!is_found || !path.empty()) {

            if (node->sector_code == sector_code) {
                is_found = true;
                node_found = node;
                break;
            }

            if (path.empty()) {
                break;
            }

            if (node == nullptr) {
                node = path[path.size() - 1];
                if (node->right == nullptr) {
                    path.pop_back();

                }
            }

            

            //auto it = std::find(visited.begin(), visited.end(), node->left);
            if (!find_element(visited, node->left)) {//it == printed.end()
                node = node->left;
                if (node != nullptr) {
                    path.push_back(node);
                    visited.push_back(node);
                    continue;
                }
            }
            else {
                //auto it = std::find(visited.begin(), visited.end(), node->right);
                if (!find_element(visited, node->right)) { // it== end()
                    node = node->right;
                    if (node != nullptr) {
                        path.push_back(node);
                        visited.push_back(node);
                        continue;
                    }
                }

                if (path.size() > 0) { // check
                    node = path[path.size() - 1];
                    //it = std::find(visited.begin(), visited.end(), node->right);


                    if (node->right == nullptr || find_element(visited, node->right)) {//it != visited.end()
                        path.pop_back();

                    }
                }

            }



            if (node == nullptr) {
                node = path[path.size() - 1];
                if (node->right == nullptr) {
                    path.pop_back();

                }
            }

            //it = std::find(visited.begin(), visited.end(), node->right);
            if (!find_element(visited, node->right)) {//it == visited.end()
                node = node->right;
                if (node != nullptr) {
                    path.push_back(node);
                    visited.push_back(node);
                    continue;
                }
            }
            else {
                if (path.size() > 0) {
                    node = path[path.size() - 1];
                    if (node->right == nullptr) {
                        //path.pop_back();

                    }
                    path.pop_back(); // check
                }

            }



            if (node == nullptr) {
                //continue;
            }
        }

    }

    return node_found;
}

Sector* SpaceSectorBST::deleteSectorRecursively(const std::string& sector_code, Sector* nodeDelete) {
    Sector* tempNode;
    std::stack<Sector*> nodes;

    if (nodeDelete == nullptr) {
        return nodeDelete;
    }

    if (nodeDelete->sector_code == sector_code) { // node is found
        

    }

    nodes.push(nodeDelete);

    if (nodeDelete->left != nullptr) {
        nodeDelete->left = deleteSectorRecursively(sector_code, nodeDelete->left);
    }
    else if(nodeDelete->right != nullptr){
        nodeDelete->right = deleteSectorRecursively(sector_code, nodeDelete->right);
    }
    else {
        tempNode = nodes.top();
        nodes.pop();
        deleteSectorRecursively(sector_code, tempNode);
    }


    return nodeDelete;
}