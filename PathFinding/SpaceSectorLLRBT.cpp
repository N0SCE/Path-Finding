#include "SpaceSectorLLRBT.h"

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the LLRBT sector map
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

// Remember to handle memory deallocation properly in the destructor.
SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // TODO: Free any dynamically allocated memory in this class.

    for (Sector* pointer : nodes_to_delete) {
        delete pointer;
    }
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    // TODO: Instantiate and insert a new sector into the space sector LLRBT map 
    // according to the coordinates-based comparison criteria.

    /*
    if (root == nullptr) {
        root = new Sector(x, y, z);
        root->color = BLACK;
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
    }*/

    //checkTree(temp);
    
    root = insert(root, x, y, z);
    root->color = BLACK;

}


Sector* SpaceSectorLLRBT::insert(Sector* root, int x, int y, int z) {

    if (root == nullptr) {
        Sector* new_node = new Sector(x, y, z);

        //root = new Sector(x, y, z);
        nodes_to_delete.push_back(new_node);
        return new_node;
    }

    if (x < root->x) {
        root->left = insert(root->left, x, y, z);
        root->left->parent = root;
    }
    else if (x == root->x) {
        if (y < root->y) {
            root->left = insert(root->left, x, y, z);
            root->left->parent = root;
        }
        else if (y == root->y) {
            if (z < root->z) {
                root->left = insert(root->left, x, y, z);
                root->left->parent = root;
            }
            else if (z == root->z) {
                // finish check
            }
            else {
                root->right = insert(root->right, x, y, z);
                root->right->parent = root;
            }
        }
        else {
            root->right = insert(root->right, x, y, z);
            root->right->parent = root;
        }
    }
    else {
        root->right = insert(root->right, x, y, z);
        root->right->parent = root;
    }

    // check tree

    if (isRed(root->right) && !isRed(root->left)) {
        root = rotateLeft(root);
        swapColors(root, root->left);
    }

    if (isRed(root->left) && isRed(root->left->left)) {
        root = rotateRight(root);
        swapColors(root, root->right);
    }

    if (isRed(root->left) && isRed(root->right)) {
        flipColors(root);
    }



    return root;
}


void SpaceSectorLLRBT::displaySectorsInOrder() {
    // TODO: Traverse the space sector LLRBT map in-order and print the sectors 
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

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    // TODO: Traverse the space sector LLRBT map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
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

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    // TODO: Traverse the space sector LLRBT map in post-order traversal and print 
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

}

std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    std::vector<Sector*> path2;
    std::vector<Sector*> visited;
    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!


    /*
    node = find_node("0SSS");

    if (path.empty()) {
        path.push_back(node);
        visited.push_back(node);
    }

    if (node->sector_code != sector_code) {

        bool is_found = false;
        while (!is_found || !path.empty()) {

            if (path.empty()) {
                break;
            }

        }

    }*/

    return path;
}

void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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
 

void SpaceSectorLLRBT::checkLeft(int x, int y, int z) {
    if (temp->left == nullptr) {
        temp->left = new Sector(x, y, z);
        
        return;
    }
    else {
        temp = temp->left;
        insertSectorByCoordinates(x, y, z);
    }
}

void SpaceSectorLLRBT::checkRight(int x, int y, int z) {
    if (temp->right == nullptr) {
        temp->right = new Sector(x, y, z);
        return;
    }
    else {
        temp = temp->right;
        insertSectorByCoordinates(x, y, z);
    }
}

bool SpaceSectorLLRBT::find_element(std::vector<Sector*> vector, Sector* find_node) {
    bool is_found = false;
    for (Sector* sector_node : vector) {
        if (sector_node == find_node) {
            is_found = true;
            break;
        }
    }


    return is_found;
}




void SpaceSectorLLRBT::flipColors(Sector* node_to_flip) {
    node_to_flip->color = !node_to_flip->color;

    node_to_flip->left->color = false;
    node_to_flip->right->color = false;
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector* node_to_rotate) {
    Sector* child = node_to_rotate->right;
    Sector* childLeft = child->left;

    child->left = node_to_rotate;
    node_to_rotate->right = childLeft;

    return child;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector* node_to_rotate) {
    Sector* child = node_to_rotate->left;
    Sector* childRight = child->right;

    child->right = node_to_rotate;
    node_to_rotate->left = childRight;

    return child;
}

bool SpaceSectorLLRBT::isRed(Sector* node_to_check) {

    if (node_to_check == nullptr) {
        return false;
    }

    return node_to_check->color == RED;
}

void SpaceSectorLLRBT::swapColors(Sector* first_node, Sector* second_node) {
    bool temp_first_color = first_node->color;
    first_node->color = second_node->color;
    second_node->color = temp_first_color;
}


Sector* SpaceSectorLLRBT::find_node(std::string sector_code) {
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