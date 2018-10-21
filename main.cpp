//Brian Nelson
//Basic Hash Table w/ BST Chaining

//TEST HASHBST.CPP

#include "HashBST.cpp"
#include <iostream>

int main() {

    Hash<int> *h2 = new Hash<int>(100);

    h2->insertItem(15);
    h2->insertItem(8);
    h2->insertItem(27);
    h2->insertItem(12);
    h2->insertItem(29);
    h2->insertItem(128);
    h2->insertItem(129);
    h2->insertItem(227);
    h2->insertItem(129);
    h2->insertItem(111);
    h2->insertItem(11);
    h2->insertItem(211);
    h2->insertItem(311);
    h2->displayHash();
 
    return 0;
}
