#include <iostream>
#include <iomanip>
#include <list>



template <class Te>
class Node{
    public:
        Te value;
        Node *left;
        Node *right;
    Node (Te val){
        this->value = val;
        this->left = NULL;
        this->right = NULL;
    }
    Node(Te val, Node<Te> left, Node<Te> right){
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

template <class Te>
class BST{
    private:
        Node<Te> *root;
        
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
            } else {
                std::cout << "Item is already in a BST, Do not need duplicate" << std::endl;
            }
        }
        int del_Help(Node<Te> *parent, Node<Te> *root, Te val){
            std::cout << root->value << std::endl;
            if (root->value == val){
                //two children
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

                } else if (root -> left != NULL){
                    root->value = root->left->value;
                    root->right = root->left->right;
                    root->left = root->left->left;
                } else if (root -> right != NULL){ 
                    root->value = root->right->value;
                    root->left = root->right->left;
                    root->right = root->right->right;
                } else {
                    if (parent){
                        if (parent->right == root){
                            parent->right = NULL;
                        }
                        if (parent->left == root){
                            parent->left = NULL;
                        }
                    } else {
                        //This is if the root node is the only value, and we are trying to delete it
                        return -1;
                    }
                }
            } else if (val < root->value){
                //IF THE VALUE DOES NOT EXIST RETURN -2
                if (root->left == NULL){
                    return -2;
                }
                return del_Help(root, root->left, val);
            } else if (val > root->value){
                //IF THE VALUE DOES NOT EXIST RETURN -2
                if (root->right == NULL){
                    return -2;
                }
                return del_Help(root, root->right,val);
            }
            return 0;
        }

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

        void add(Te val){
            if (root){
                this->add_Help(root, val);
            } else {
                root = new Node<Te>(val);
            }    
        }
        void print(){
            print_Help(root,0);
        }
        void del(Te val){
            int temp = del_Help(NULL, root, val);
            //if the root node is the only value and we are trying to delete it.
            if (temp == -1){
                root = NULL;
                delete root;
            } else if (temp == -2){
                std::cout << "Item Not Found To Delete" << std::endl;
            }
        }
        int find(Te val){
            return find_Help(root, val);
        }
};

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


