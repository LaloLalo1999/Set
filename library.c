#include "library.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
// Arbol de busqueda binaria
// Un BST es un arbol binario donde los nodos estan ordenados de la siguiente manera:
// - Cada nodo tiene un valor
// - Todos los nodos a la izquierda del nodo tienen un valor menor que el nodo
// - Todos los nodos a la derecha del nodo tienen un valor mayor que el nodo
// - No se permiten valores duplicados
// El primer dato se guarda en la raiz del arbol
// Cada dato siguiente se guarda en un nodo hijo
// Se compara el dato a añadir con el dato de cada nodo en el camino:
// - Si el dato es menor que el dato del nodo, se va al nodo hijo izquierdo
// - Si el dato es mayor que el dato del nodo, se va al nodo hijo derecho
// - Si el dato es igual que el dato del nodo, se ignora el dato
// Si estamos trabajando con datos genericos, necesitamos una funcion de comparacion
// El contenedor, en el momento de su creacion, recibe un apuntador a la funcion de comparacion
// La funcion de comparacion recibe dos apuntadores a void y devuelve un entero
// - Si el primer apuntador es menor que el segundo, devuelve un numero negativo
// - Si el primer apuntador es mayor que el segundo, devuelve un numero positivo
// - Si el primer apuntador es igual que el segundo, devuelve 0
// ¿Qué tipo de datos necesitamos para implementar un BST?
// - Un apuntador a la raiz del arbol
// - Un apuntador a la funcion de comparacion
// - Un entero que indique el numero de elementos en el arbol
// ¿Qué estructuras requerimos para los nodos y el contenedor set?
// - Un nodo debe tener un apuntador al dato, un apuntador al nodo hijo izquierdo y un apuntador al nodo hijo derecho
// - El contenedor debe tener un apuntador a la raiz del arbol, un apuntador a la funcion de comparacion, un entero que indique el numero de elementos en el arbol y un size_t que indique el tamaño de los datos

struct Node {
    Type value;
    struct Node *left;
    struct Node *right;
};

typedef struct Node * Node;

struct Set {
    Node root;
    Compare compare;
    unsigned int size;
    size_t typeSize;
};

// Crea una instancia de un contenedor set y lo inicializa
Set createSet(Compare compare, size_t typeSize) {
    Set set = malloc(sizeof(struct Set));
    set->root = NULL;
    set->compare = compare;
    set->size = 0;
    set->typeSize = typeSize;
    return set;
}

// Devuelve el numero de elementos en el contenedor set
int sizeSet(Set set) {
    if (set != NULL) {
        return set->size;
    }
    return -1;
}

// Crea un nodo y lo inicializa
Node createNode(Type value, size_t typeSize) {
    Node node = malloc(sizeof(struct Node));
    node->value = malloc(typeSize);
    memcpy(node->value, value, typeSize);
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Agrega un dato al conjunto, sólo si no existe el dato en el conjunto
// Si se agrega el dato, devuelve true e incrementa el tamaño del conjunto
// Si no se agrega el dato, devuelve false
bool addSet(Set set, Type value) {
    Node node = createNode(value, set->typeSize);
    if (set->root == NULL) {
        set->root = node;
        set->size++;
        return true;
    }
    Node current = set->root;
    while (current != NULL) {
        int result = set->compare(&value, &current->value);
        if (result == 0) {
            free(node->value);
            free(node);
            return false;
        } else if (result < 0) {
            if (current->left == NULL) {
                current->left = node;
                set->size++;
                return true;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == NULL) {
                current->right = node;
                set->size++;
                return true;
            } else {
                current = current->right;
            }
        }
    }
    return false;
}

// Retorna true si el dato se encuentra en el conjunto, false en caso contrario
bool containSet(Set set, Type value) {
    Node current = set->root;
    while (current != NULL) {
        int result = set->compare(value, current->value);
        if (result == 0) {
            return true;
        } else if (result < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// Elimina un dato del conjunto. Retorna true si el dato se elimino, false en caso contrario
bool removeSet(Set set, Type value) {
    Node current = set->root;
    while (current != NULL) {
        int result = set->compare(value, current->value);
        if(result == 0) {
            if ((current->left == NULL) && (current->right == NULL)) {
                free(current->value);
                free(current);
                set->size--;
                return true;
            } else if ((current->left != NULL) && (current->right == NULL)){
                Node temp = current;
                current = temp->left;
                free(temp->value);
                free(temp);
                set->size--;
                return true;
            } else if ((current->left == NULL) && (current->right != NULL)){
                Node temp = current;
                current = temp->right;
                free(temp->value);
                free(temp);
                set->size--;
                return true;
            } else {
                Node temp = current->left;
                while(temp->right != NULL){
                    temp = temp->right;
                }
                current->value = temp->value;
                free(temp->value);
                Node left = temp->left;
                free(temp);
                temp = current->left;
                while(temp->right != NULL){
                    temp = temp->right;
                }
                temp->right = left;
                set->size--;
                return true;
            }
        } else if (result < 0){
            current = current->left;
        } else {
            current = current ->right;
        }
    }
    return false;
}

// Destruye el contenedor set
void destroySet(Set set) {
    Node current = set->root;
    while (current != NULL) {
        if ((current->left == NULL) && (current->right == NULL)) {
            free(current->value);
            free(current);
            current = NULL;
        } else if ((current->left != NULL) && (current->right == NULL)){
            Node temp = current;
            current = temp->left;
            free(temp->value);
            free(temp);
        } else if ((current->left == NULL) && (current->right != NULL)){
            Node temp = current;
            current = temp->right;
            free(temp->value);
            free(temp);
        } else {
            Node temp = current->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            free(temp->value);
            Node left = temp->left;
            free(temp);
            temp = current->left;
            while(temp->right != NULL){
                temp = temp->right;
            }
            temp->right = left;
        }
    }
    free(set);
}