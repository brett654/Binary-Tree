#include <iostream>

struct Node {
    int data;
    Node* leftChild;
    Node* rightChild;

    Node(int value) : data(value), leftChild(nullptr), rightChild(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        if (!root) {
             root = new Node(value);
            return;
        }
        else {
            insertRecursive(root, value);
        }
    }

    void inOrderTransversal() {
        inOrderTransversal(root);
    }

    void preOrderTransversal() {
        preOrderTransversal(root);
    }

    void postOrderTransversal() {
        postOrderTransversal(root);
    }

    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    Node* search(int value) {
        Node* current = root;

        while (current) {
            if (value == current->data) {
                return current;
            }
            else if (value < current->data) {
                current = current->leftChild;
            }
            else {
                current = current->rightChild;
            }
        }
        return nullptr;
    }

    ~BinaryTree() {
        releaseMemory(root);
    }

private:
    void insertRecursive(Node* node, int value) {
        if (value < node->data) {
            if (!node->leftChild) {
                node->leftChild = new Node(value);
            }
            else {
                insertRecursive(node->leftChild, value);
            }
        }
        else if (value > node->data) {
            if (!node->rightChild) {
                node->rightChild = new Node(value);
            }
            else {
                insertRecursive(node->rightChild, value);
            }
        }
    }

    void inOrderTransversal(Node* node) {
        if (!node) return;

        inOrderTransversal(node->leftChild);
        std::cout << node->data << std::endl;
        inOrderTransversal(node->rightChild);
    }

    void preOrderTransversal(Node* node) {
        if (!node) return;

        std::cout << node->data << std::endl;
        preOrderTransversal(node->leftChild);
        preOrderTransversal(node->rightChild);
    }

    void postOrderTransversal(Node* node) {
        if (!node) return;

        postOrderTransversal(node->leftChild);
        postOrderTransversal(node->rightChild);
        std::cout << node->data << std::endl;
    }

    void releaseMemory(Node* node) {
        if (!node) return;

        releaseMemory(node->leftChild);
        releaseMemory(node->rightChild);

        delete node;
    }

    Node* deleteNode(Node* node, int value) {
        if (!node) return node;

        if (value < node->data) {
            node->leftChild = deleteNode(node->leftChild, value);
        }
        else if (value > node->data) {
            node->rightChild = deleteNode(node->rightChild, value);
        }
        else {
            //Node found

            //Node with only 1 child or none
            if (!node->leftChild) {
                return node->rightChild;
            }
            else if (!node->rightChild) {
                return node->leftChild;
            }

            //Node with two children
            Node* successor = findMin(node->rightChild);

            node->data = successor->data;

            node->rightChild = deleteNode(node->rightChild, successor->data);
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->leftChild) {
            node = node->leftChild;
        }
        return node;
    }
};

int main() {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(1);
    tree.insert(4);

    std::cout << "In order transversal:" << std::endl;
    tree.inOrderTransversal();

    std::cout << "Pre order transversal:" << std::endl;
    tree.preOrderTransversal();

    std::cout << "Post order transversal:" << std::endl;
    tree.postOrderTransversal();

    std::cout << std::endl;

    Node* out = tree.search(5);
    std::cout << "Value searched for: " << out->data << std::endl;

    std::cout << "Node deleted" << std::endl;
    tree.deleteNode(5);
    tree.inOrderTransversal();

    std::cout << "Node added" << std::endl;
    tree.insert(5);
    tree.inOrderTransversal();
    
    return 0;
}


