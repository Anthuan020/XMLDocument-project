#ifndef XMLDocument_HPP
#define XMLDocument_HPP

#include "XMLNode.hpp"

class XMLDocument {
public:
    // Modo para modificar contenido y atributos
    const int ADD = 100;    // Modo añadir
    const int OVR = 200;    // Modo sobrescribir
    const int APD = 300;    // Modo agregar
    const int DEL = 400;    // Modo eliminar

    // Posición del contenido en relación con los hijos del nodo
    const int BEG = 10;     // Contenido antes de los hijos del nodo
    const int END = 20;     // Contenido después de los hijos del nodo

    XMLDocument();
    ~XMLDocument();

    int   Root(const char* name);
    bool  Select(const char* id);
    int   Child(const char* name);
    int   Child(const char* name, const char* content);
    bool  EditAttribute(const char* key, const char* value, int mode);
    bool  EditContent(const char* content, int mode);
    bool  SwitchContentPosition();
    int   DefineTemplate(const char* name, const char* xmlContent);
    bool  EditTemplate(int templateId, const char* xmlContent);
    int   InstantiateTemplate(int templateId, const char** placeholders, const char** values, int placeholderCount);
    bool  DeleteTemplate(int templateId);
    char* TemplatesToString();
    bool  Delete();
    char* ViewTree();
    char* ViewNode();
    char* ViewXML();
    bool  Save(const char* filename);

private:
    XMLNode* root;
    XMLNode* currentNode;

    //Metodo auxiliar
    XMLNode* findNodeById(const char* id, XMLNode* startNode) const;
};

XMLDocument::XMLDocument()
    : root(nullptr), currentNode(nullptr) {}

XMLDocument::~XMLDocument() {
    delete root;
}

int XMLDocument::Root(const char* name) {
    if (root != nullptr) {
        delete root;
    }
    root = new XMLNode(name);
    currentNode = root;
    return 0;
}

bool XMLDocument::Select(const char* id) {
    if (root == nullptr) return false;
    currentNode = findNodeById(id, root);
    return currentNode != nullptr;
}

int XMLDocument::Child(const char* name) {
    if (currentNode == nullptr) return -1;
    XMLNode* child = new XMLNode(name);
    currentNode->addChild(child);
    return 0;
}

int XMLDocument::Child(const char* name, const char* content) {
    if (currentNode == nullptr) return -1;
    XMLNode* child = new XMLNode(name,content);
    currentNode->addChild(child);
    return 0;
}

bool XMLDocument::EditAttribute(const char* key, const char* value, int mode){}

XMLNode* XMLDocument::findNodeById(const char* id, XMLNode* startNode) const {
    if (startNode->id == id) return startNode;
    for (int i = 0; i < startNode->numChildren; ++i) {
        XMLNode* result = findNodeById(id, startNode->children[i]);
        if (result != nullptr) return result;
    }
    return nullptr;
}

#endif // XMLDocument_HPP
