#ifndef XMLNODE_HPP
#define XMLNODE_HPP

#include "String.hpp" 

class XMLNode {
public:
    String name;
    String value;
    String id;
    XMLNode** children;
    int numChildren;

    XMLNode(const char* name, const char* value = "");
    ~XMLNode();

    void addChild(XMLNode* child);
    void print(int level = 0) const;

private:
    void expandChildrenArray();
};

XMLNode::XMLNode(const char* name, const char* value)
    : name(name), value(value),id("_"), children(nullptr), numChildren(0) {}

XMLNode::~XMLNode() {
    for (int i = 0; i < numChildren; ++i) {
        delete children[i];
    }
    delete[] children;
}

void XMLNode::addChild(XMLNode* child) {
    expandChildrenArray();
    children[numChildren - 1] = child;
}

void XMLNode::expandChildrenArray() {
    XMLNode** newChildren = new XMLNode*[numChildren + 1];
    for (int i = 0; i < numChildren; ++i) {
        newChildren[i] = children[i];
    }
    delete[] children;
    children = newChildren;
    numChildren++;
}

void XMLNode::print(int level) const {
    for (int i = 0; i < level; ++i) {
        std::cout << "  ";  
    }
    std::cout << "<" << name.getData();
    
    if (id.len() > 0) {
        std::cout << " id=\"" << id.getData() << "\"";
    }
    
    std::cout << ">" << std::endl;

    if (value.len() > 0) {
        for (int i = 0; i < level + 1; ++i) {
            std::cout << "  ";  
        }
        std::cout << value.getData() << std::endl;
    }
    
    for (int i = 0; i < numChildren; ++i) {
        children[i]->print(level + 1);
    }
    
    for (int i = 0; i < level; ++i) {
        std::cout << "  ";
    }
    std::cout << "</" << name.getData() << ">" << std::endl;
}

#endif // XMLNODE_HPP
