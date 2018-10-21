//BRIAN NELSON
//Basic Hash Table w/ BST Chaining

#include <iostream>
#include <iomanip>
#include <list>


//Template for generic
template <class Te>
//Node Class
class Node{
    public:
        Te value;
        Node *left;
        Node *right;
    //@param Te Val: value that the node will store
    Node (Te val){
        this->value = val;
        this->left = NULL;
        this->right = NULL;
    }
    //@param Te val: value that the node will store
    //@param Node<Te> left: left branch of the node
    //@param Node<Te> right: right branch of the node
    Node(Te val, Node<Te> left, Node<Te> right){
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

//Template
template <class Te>
//Binary Search Tree Class
class BST{
    private:
        Node<Te> *root;
    
        //private Add function Helper. Needed for Recursion
        //@param Node<Te> *root: a pointer to the root node
        //@param Te val: value that we are looking to add to BST
        void add_Help(Node<Te> *root, Te val){
            if (val < root->value){
                if (root->left == NULL){
                    root->left = new Node<Te>(val);
                } else {
                    add_Help(root->left, val);
                }
            } else if (val > root ->value){
                if (root->right == NULL){
                    root->right = new Node<Te>(val);
                } else {
                    add_Help(root->right, val);
                }
            //if value is equal, print that it already exists
            } else {
                std::cout << "Item is already in a BST, Do not need duplicate" << std::endl;
            }
        }

        //Private remove function Helper. Needed for Recursion
        //@param Node<Te> *parent: parent node of the root, if it exists
        //@param Node<Te> *root: root node pointer
        //@param Te val: value we are deleting from BST
        int del_Help(Node<Te> *parent, Node<Te> *root, Te val){
            std::cout << root->value << std::endl;
            //if value found and
            if (root->value == val){
                //has two children
                if (root->left != NULL && root->right != NULL){
                    Node<Te> *temp_parent = root;
                    Node<Te> *temp = root->right;
                    while(temp->left){
                        temp_parent = temp;
                        temp = temp->left;
                    }
                    Te tempVal = temp->value;
                    del_Help(temp_parent,temp, tempVal);
                    root->value = tempVal;
                //has only the left child
                } else if (root -> left != NULL){
                    root->value = root->left->value;
                    root->right = root->left->right;
                    root->left = root->left->left;
                //has only the right child
                } else if (root -> right != NULL){ 
                    root->value = root->right->value;
                    root->left = root->right->left;
                    root->right = root->right->right;
                //has no children
                } else {
                    if (parent){
                        if (parent->right == root){
                            parent->right = NULL;
                        }
                        if (parent->left == root){
                            parent->left = NULL;
                        }
                    } else {
                        //if the root node is the value, and has no children, return -1
                        //The function that called the helper will take care of this
                        return -1;
                    }
                }
            } else if (val < root->value){
                // if there is no futher node to look at then
                if (root->left == NULL){
                    //return an error that the function that called this will take care of
                    return -2;
                }
                return del_Help(root, root->left, val);
            } else if (val > root->value){
                // if there is no futher node to look at then
                if (root->right == NULL){
                    //return an error that the function that called this will take care of
                    return -2;
                }
                return del_Help(root, root->right,val);
            }
            return 0;
        }

        //Private print helper function
        //@param Node<Te> *root: rote Node Pointer
        //@param int indent: indention integer used for print formating
        void print_Help(Node<Te> *root, int indent){
            if (root != NULL){
                if (root->right) print_Help(root->right,indent+4);
                if (indent){
                    std::cout << std::setw(indent) << ' ';
                }
                if (root->right) std::cout<<" /\n" << std::setw(indent) << ' ';
                std::cout << root->value << "\n";
                if (root->left){
                    std::cout << std::setw(indent) << ' ' << " \\\n";
                    print_Help(root->left,indent+4);
                } 
            }
        }

        //Private find helper function
        //@param Node<Te> *root: a pointer to the root node
        //@param Te val: value that we are looking to add to BST
        int find_Help(Node<Te> *root, Te val){
            if (root->value == val){
                return 1;
            } else if (val < root -> value ){
                if (!(root->right)){
                    return 0;
                }                
                return find_Help(root->left, val);
            } else if (val > root -> value){
                if (!(root->right)){
                    return 0;
                }
                return find_Help(root->right, val);
            }
            return 0;
        }
    public: 
        //Add function for BST
        //@param Te Val: value that we are looking to add to BST
        void add(Te val){
            //if root exists then use the helper function
            if (root){
                this->add_Help(root, val);
            } else {
                //if root != exist then create a new node for it
                root = new Node<Te>(val);
            }    
        }
        //Print function for BST
        void print(){
            print_Help(root,0);
        }
        //Delete function for BST
        //@param Te val: value we are looking to delete
        void del(Te val){
            int temp = del_Help(NULL, root, val);
            //if the root node is the only value and we are trying to delete it.
            if (temp == -1){
                root = NULL;
                delete root;
            //if the item is not found in BST
            } else if (temp == -2){
                std::cout << "Item Not Found To Delete" << std::endl;
            }
        }
        //Find functino for BST
        //@param Te Val: value we are trying to find
        int find(Te val){
            return find_Help(root, val);
        }
};


//Basic table 
template <class Te>
class Hash{
    public: 
        int num;
        BST<Te> *table;
    public:
        Hash(int num){
            this->num = num;
            table = new BST<Te>[num];
        }
        void insertItem(Te item){
            int index = hashFunction(item);
            table[index].add(item);
        }
        
        void deleteItem(Te item){
            int index = hashFunction(item);
            table[index].remove(item);
        }
        void displayHash(){
            for (int i = 0; i < num; i++){
                std::cout << "-----" << i << "-----" << std::endl;;
                table[i].print();
                std::cout << std::endl;
            }
        }
        
        int hashFunction(Te item){
            return (item % num);
        }

};


