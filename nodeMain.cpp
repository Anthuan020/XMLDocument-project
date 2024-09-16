#include <iostream>
#include "XMLNode.hpp"

int main() {
    XMLNode* root = new XMLNode("root","_102");
    XMLNode* child1 = new XMLNode("child1","value1");
    XMLNode* child2 = new XMLNode("child2","value2");

    root->addChild(child1);
    root->addChild(child2);

    root->print();

    delete root;

    return 0;
}
