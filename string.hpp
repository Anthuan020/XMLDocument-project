/*****Datos administrativos************************
 * Nombre del archivo: String.hpp
 * Tipo de archivo: hpp
 * Proyecto: Librería String
 * Autores: Nabyell León, Derrick  Gonzalez, Johnsy López
 * Institución: Tecnológico de Costa Rica
 *****Descripción**********************************
 * Esta librería está creada para manipular strings en C++.
 * Contiene una variedad de métodos para manipular cadenas.
 *****Versión**************************************
 * ##  |   Fecha y hora 
 * 1.5   25/08/2024 15:17
 **************************************************/

#ifndef STRING_HPP
#define STRING_HPP

#include <fstream>
#include <iostream>


/*****Nombre: String *****************************************************
 * 
 *****Descripción: Librería creada para manipular strings en C++. **********************************
 * 
 *****Atributos: data (char*), length (int)************************************
 * 
 *****Métodos públicos: **************************************
    String( char* str)                          ~String()
    unsigned int len()                          const char* getData()
    int ultimoIndice(char)                      void setLength(unsigned int newLength)
    void cambiarCadena(char*)                   char operator[](int index) const            
    bool operator==(const String& other)        void addChar(char)                          
    char* Split(char)                           void concatenarEn(const char*,int)          
    void reemplazarEn(const char*,int)          void reemplazarOcurrencias(const char*, const char*)
    void concatenarCadenas(const char**)        char** frecuenciaCaracteres()               
    char** tokenizar(char , int)                bool guardarEnArchivo(char*,char*)          
    void leerArchivo( char* )

 **************************************************/


class String {
private:
    char* data;
    unsigned int length;
    int buscarDesde(int, const char*) const;
    void addChar(char);

public:
    String(const char* str);
    ~String();
    unsigned int len() const;
    const char* getData() const;
    int ultimoIndice(char);
    void setLength(unsigned int newLength);
    void cambiarCadena(const char*);
    char operator[](int index) const;
    bool operator==(const String& other)const;
    String** Split(char) const;
    void concatenarEn(const char*,int);
    int buscarSubcadena(const char*) const;
    void concatenarCadenas(const char**);
    void reemplazarEn(const char*,int);
    void reemplazarOcurrencias(const char*, const char*);
    char** frecuenciaCaracteres();
    char** tokenizar(char);
    void reverseString();
    bool guardarEnArchivo(const char*, const char*);
    bool leerArchivo(const char*);
};

String::String(const char* str) {
    if (str) {
        length = 0;
        while (str[length] != '\0') {
            ++length;
        }
        data = new char[length + 1];
        for (unsigned int i = 0; i < length; ++i) {
            data[i] = str[i];
        }
        data[length] = '\0';
    } else {
        data = nullptr;
        length = 0;
    }
}

String::~String() {
    delete[] data;
}

void String::setLength(unsigned int newLength) {
    length = newLength;
}

unsigned int String::len() const {
    int size = 0;
    int i = 0;
    while (true) {
        if (data[i] != '\0') {
           i++;
           size++;
        } else {
            const_cast<String*>(this)->setLength(size);
            return size;
        };       
    }
}

const char* String::getData() const {
    return data;
}

int String::ultimoIndice(char caracter) {
	int ultimo = -1;

	for(unsigned int i = 0; i < length; i++) {
		if (data[i] == caracter) {
			ultimo = i;
		}
	}

	return ultimo;
}

void String::cambiarCadena(const char* text) {
    delete data;
    data = (char*)text;
    length = this->len();
}

bool String::operator==(const String& other) const {
    if (length != other.length) {
        return false;
    }
    for (unsigned int i = 0; i < length; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

char String::operator[](int index) const {
    if (index < 0 || static_cast<unsigned int>(index) >= length) {
        return '\0';
    }
    return data[index];
}

void String::addChar(char element) {
    char* new_data = new char[length + 2]; 

    for (unsigned int i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }

    new_data[length] = element;
    new_data[length + 1] = '\0';

    delete[] data;

    data = new_data;
    length += 1;
}

String** String::Split(char element) const {
    unsigned int count = this->len();

    unsigned int separator_count = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (data[i] == element) {
            separator_count++;
        }
    }
    
    String** resultado = new String*[separator_count+1];

    unsigned int index = 0;
    String* temp = new String("");
    for (unsigned int i = 0; i < count; i++) {
        
        if (data[i] == element) {
            resultado[index] = temp;
            
            temp = new String("");
            index++;
        } else {
            char* value = new char[1];
            value[0] = data[i];
            temp->addChar(data[i]);
        }
    }

    resultado[index] = temp;
    
    return resultado;
}

void String::concatenarEn(const char* text, int paramIndex) {

    int original_length = length;
    int text_len = 0;
    if (paramIndex < 0) {
        paramIndex = length + paramIndex;
    }

    if (paramIndex > length) {
        paramIndex = paramIndex % (length + 1);
    }

    if (paramIndex < 0) {
        paramIndex = 0;
    }
    

    while (text[text_len] != '\0') {
        text_len++;
    }

    char* resultado = new char[original_length + text_len + 1];

    int i = 0;
    for (; i < paramIndex; i++) {
        resultado[i] = data[i];
    }

    for (int j = 0; j < text_len; j++) {
        resultado[i + j] = text[j];
    }

    for (int k = paramIndex; k < original_length; k++) {
        resultado[i + text_len + (k - paramIndex)] = data[k];
    }

    resultado[original_length + text_len] = '\0';

    delete[] data;
    data = resultado;
    length = original_length + text_len;
}

int String::buscarDesde(int index, const char* subCadena) const {
    int subCadena_len = 0;
    while (subCadena[subCadena_len] != '\0') {
        subCadena_len++;
    }

    if (subCadena_len > length) {
        return -1;
    }

    for (int i = index; i <= length - subCadena_len; i++) {
        int j;
        for (j = 0; j < subCadena_len; j++) {
            if (data[i + j] != subCadena[j]) {
                break;
            }
        }

        if (j == subCadena_len) {
            return i;
        }
    }

    return -1;
}

int String::buscarSubcadena(const char* subCadena) const {
    return buscarDesde(0, subCadena);
}

void String::concatenarCadenas(const char** arregloCadenas){
    int numero_cadenas = 0;
    int totalLen = 0;
    while (arregloCadenas[numero_cadenas] != nullptr) {
        int len = 0;
        while (arregloCadenas[numero_cadenas][len]!= '\0') {
            len++;
        }
        totalLen += len;
        numero_cadenas++;
    }

    char* new_data = new char[length + totalLen + 1];

    int i = 0;
    for (int idx = 0; idx < length; idx++) {
        new_data[i++] = data[idx];
    }

    for (int j = 0; j < numero_cadenas; j++) {
        int k = 0;
        while (arregloCadenas[j][k] != '\0') {
            new_data[i++] = arregloCadenas[j][k++];
        }
    }

    new_data[i] = '\0';

    delete[] data;
    data = new_data;
    length += totalLen;
}

void String::reemplazarEn(const char* text, int paramIndex) {
    while (paramIndex < 0) {
        paramIndex = length + paramIndex;
    }

    while (paramIndex >= length) {
        paramIndex = paramIndex - length;
    }

    unsigned int text_len = 0;
    while (text[text_len] != '\0') {
        text_len++;
    }

    unsigned int nuevo_length = text_len+length;

    char* new_data = new char[nuevo_length + 1];
    int j = 0;
    for (int i = 0; i < nuevo_length; i++) {
        if (i < paramIndex) {
            new_data[i] = data[i];
        } else if (i == paramIndex) {   
            while (j < text_len) {
                new_data[i] = text[j];
                j++;
                i++;
            }     
        } else {
            new_data[i-1] = data[i-j];
        }
    }

    new_data[nuevo_length] = '\0';

    delete[] data;
    data = new_data;
    length = nuevo_length;
}


void String::reemplazarOcurrencias(const char* anterior, const char* nuevo) {

    unsigned int anterior_len = 0;
    while (anterior[anterior_len] != '\0') {
        anterior_len++;
    }

    unsigned int nuevo_len = 0;
    while (nuevo[nuevo_len] != '\0') {
        nuevo_len++;
    }

    unsigned int count = 0;

    int index = 0;
    int i = 0;
    while(i < length){
        index = buscarDesde(i, anterior);
        if (index == -1) {
            i = length+1;
        } else {
            i = index+anterior_len;
            count++;
        }
    }

    unsigned int nuevo_length = length-count+(count*(anterior_len+1));
    char* new_data = new char[nuevo_length + 1];

    int j = 0; // cadena original
    i = 0; // nueva cadena
    int proximo = 0;
    proximo = buscarSubcadena(anterior);
    while(i < nuevo_length){
        if (j == proximo) {
            for (int k = 0; k < nuevo_len; k++) {
                new_data[i] = nuevo[k];
                i++;
            }
            j += anterior_len;
            proximo = buscarDesde(j+1,anterior);

        } else {
            new_data[i] = data[j];
            j++;
            i++;
        }
    }

    new_data[nuevo_length] = '\0';

    delete[] data;
    data = new_data;
    length = nuevo_length;
}

char** String::tokenizar(char delimiter)  {
    // Contar los tokens
    int tokens = 1;
    for (int i = 0; i<length;i++){
        if (data[i] == delimiter)
            tokens++;
    };

    //arreglo de tokens
    char** tokens_array = new char*[tokens];

    //formar el arreglo de tokens
    int start = 0;
    int index = 0;
    for (int i = 0; i<=length; i++){
        if (data[i] == delimiter || data[i] == '\0'){

            int arrayIndex = i - start;    
            tokens_array[index] = new char[arrayIndex + 1];
            int token_index = 0;
            
            for (int j = start; j < i; j++){
                tokens_array[index][token_index] = data[start + token_index];
                token_index++;
                
            }
            tokens_array[index][arrayIndex] = '\0';
            index++;
            start = i + 1;
        };

    };
    return tokens_array;
}

char** String::frecuenciaCaracteres() {
    int leng = len();
    char** mapa = new char*[leng * 3];
    int index = 0;
    int cont = 0;
    for (int i = 0; i < leng; i++) {
        for(int j = 0; j < leng; j++) {
            if (data[i] == data[j]) {
                cont++;
            }

        }
        mapa[index] = new char[3];
        mapa[index][0] = data[i];
        mapa[index][1] = cont + '0'; 
        mapa[index][2] = '\0'; 

        cont = 0;
        index++;
    }
    return mapa;
}


void String::reverseString() {
    char* new_data = new char[length]; 

    for (unsigned int i = 0; i < length; ++i) {
        new_data[i] = data[length-1-i]; //se asignan los datos a los índices inversos
    }
    new_data[length] = '\0';

    delete[] data;
    data = new_data;
}

bool String::guardarEnArchivo(const char* ruta, const char* modo) {
    
    std::ofstream file;

    bool esTrunc = true;

    int i = 0;
    while (modo[i] != '\0' && "trunc"[i] != '\0') {
        if (modo[i] != "trunc"[i]) {
            esTrunc = false;
            break;
        }
        i++;
    }

    bool esAppend = true;
    i = 0;
    while (modo[i] != '\0' && "append"[i] != '\0') {
        if (modo[i] != "append"[i]) {
            esAppend = false;
            break;
        }
        i++;
    }

    
    if (esTrunc) {
        file.open(ruta, std::ios::out | std::ios::trunc);
    } else if (esAppend) {
        file.open(ruta, std::ios::out | std::ios::app);
    } else {
        //std::cout << "Error en modo de archivo" << std::endl;
        return false;
    }

    if (!file.is_open()) {
        //std::cout << "Error al abrir archivo" << std::endl;
        return false;
    }

    file << data;
    file.close();

    return true;

}

bool String::leerArchivo(const char* ruta) {
    std:: ifstream fich(ruta);
    if (fich.is_open()) {
        char c;
        delete[] data;
        char* new_data;
        cambiarCadena(""); 
        data = new char[20];
        while (fich.get(c)) {
            data[length] = c;
            length++;
            new_data = new char[length + 1];
        }

        for (int i = 0; i < length; i++) {
            new_data[i] = data[i];
        }

        delete[] data;
        
        cambiarCadena(new_data);
        data[length] = '\0';
        fich.close();
        return true;
    }
    else{
        return false;
    }

}

#endif
