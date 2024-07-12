#include <iostream>
#include <queue>

struct BstNode{
    int data;
    BstNode* left;
    BstNode* right;
};

BstNode* GetNewNode(int data){
    BstNode* newNode = new BstNode;
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

BstNode* Insert(BstNode* root, int data){
    if(root == nullptr){
        root = GetNewNode(data);
    }
    else if(data <= root->data){
        root->left = Insert(root->left, data);
    }
    else{
        root->right = Insert(root->right, data);
    }
    return root;

}

bool Search(BstNode* root, int data){
    if(root == nullptr) return false;
    else if(root->data == data) return true;
    else if (data <= root->data) return Search(root->left, data);
    else return Search(root->right, data);
}

int FindMin(BstNode* root){
    if(root == nullptr){
        std::cout << "Error: Tree is empty" << std::endl;
        return -1;
    }
    while(root->left != nullptr){
        root = root->left;
    }
    return root->data;
}

int FindMinRecursive(BstNode* root){
    if(root == nullptr){
        std::cout << "Error: Tree is empty" << std::endl;
        return -1;
    }
    else if(root->left == nullptr){
        return root->data;
    }
    return FindMinRecursive(root->left);
}

int FindHeight(BstNode* root){
    if(root == nullptr){
        return -1;
    }
    return std::max(FindHeight(root->left),FindHeight(root->right)) + 1;
}

void LevelOrder(BstNode* root){
    if(root == nullptr) return;
    std::queue<BstNode*> Q;
    Q.push(root);
    
    while(!Q.empty()){
        BstNode* current = Q.front();
        std::cout << current->data << " ";
        if(current->left != nullptr) Q.push(current->left);
        if(current->right != nullptr) Q.push(current->right);
        Q.pop();
        }
}

void Preorder(BstNode* root){
    if(root == nullptr) return;

    std::cout << root->data << " ";
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(BstNode* root){ //Gives sorted order
    if(root == nullptr) return;
    
    Inorder(root->left);
    std::cout << root->data << " ";
    Inorder(root->right);
}

void Postorder(BstNode* root){
    if(root == nullptr) return;
    
    Postorder(root->left);
    Postorder(root->right);
    std::cout << root->data << " ";
}

bool IsBstUtil(BstNode* root, int minValue, int maxValue){
    if(root == nullptr) return true;

    if(minValue < root->data < maxValue
    && IsBstUtil(root->left, minValue, root->data)
    && IsBstUtil(root->right, root->data, maxValue))
        return true;
    else
        return false;
}

bool IsBinarySearchTree(BstNode* root){

    return IsBstUtil(root, INT_MIN, INT_MAX);  //INT_MIN and INT_MAX are C++ constants
}

BstNode* FindMinAddress(BstNode* root){ //Find address of min of BST
    if(root == nullptr){
        std::cout << "Error: Tree is empty" << std::endl;
        return nullptr;
    }
    while(root->left != nullptr){
        root = root->left;
    }
    return root;
}

BstNode* Delete(BstNode* root, int data){
    if(root == nullptr) return root;
    else if (data < root->data){
        root->left = Delete(root->left, data);
    }
    else if (data > root->data){
        root->right = Delete(root->right, data);
    }
    else{
        // Case 1: No child
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
        //Case 2: One child
        else if(root->left == nullptr){//Left child is null
            BstNode* temp = root; //Declare temp to assign address of root to be deleted
            root = root->right; //Reassign root address
            delete temp; //Delete address of root from memory
        }
        else if(root->right == nullptr){//Right child is null
            BstNode* temp = root;
            root = root->left;
            delete temp;
        }
        //Case 3: 2 children
        else{
            BstNode* temp = FindMinAddress(root->right);
            root->data = temp->data;
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}


int main(){

    BstNode* root = nullptr;
    root = Insert(root, 15);
    Insert(root, 10);
    Insert(root, 20);
    Insert(root, 25);
    Insert(root, 8);
    Insert(root, 12);

    int number;
    std::cout << "Enter number to search" << std::endl;
    std::cin >> number;
    if(Search(root, number) == true) std::cout << "Found" << std::endl;
    else std::cout << "Not Found" << std::endl;

    int min;
    min = FindMin(root);
    std::cout << "min: " << min << std::endl;
    min = FindMinRecursive(root);
    std::cout << "Recursive min: " << min << std::endl;

    int height;
    height = FindHeight(root);
    std::cout << "Height of BST: " << height << std::endl;

    std::cout << "Level Order: ";
    LevelOrder(root);
    std::cout << std::endl;

    std::cout << "Preorder: ";
    Preorder(root);
    std::cout << std::endl;
    
    std::cout << "Inorder: ";
    Inorder(root);
    std::cout << std::endl;

    std::cout << "Postorder: ";
    Postorder(root);
    std::cout << std::endl;

    if(IsBinarySearchTree(root)== true) std::cout << "Is BinarySearchTree" << std::endl;
    else std::cout << "Not BinarySearchTree" << std::endl;

    std::cout << "Deleting 15 from BST" << std::endl;
    Delete(root, 15);
    std::cout << "New Inorder: ";
    Inorder(root);
    std::cout << std::endl;

    return 0;
}