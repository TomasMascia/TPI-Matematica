#include <stdio.h>
#include <stdlib.h>

// ______________________________________________________________
// ESTRUCTURAS Y CONSTANTES
// ______________________________________________________________

// Definimos una estructura porque el arbol necesita nodos para poder relacionarce entre si. En este caso es un nodo que tiene un dato y dos hijos. 
// Esta estructura es una estructura basica y sencilla para hacer un arbol. ademas tiene su altura esto es clave para el tema de balanceo
#define ESPACIO_NIVEL 10

typedef struct Nodo {
    int dato;
    struct Nodo* izq;
    struct Nodo* der;
    int altura;
} Nodo;

// ______________________________________________________________
// FUNCIONES AUXILIARES Y DE MEMORIA
// ______________________________________________________________

int altura(Nodo* raiz) {
    if(raiz == NULL) {
        return 0;
    }
    return raiz->altura;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Esta funcion lo que hace es crear un nodo el cual se agrega un valor
// dentro al apartado de int dato para poder crear el primer nodo.
// lo que verifica es que si el nodo esta vacio este mismo marca un 
// mensaje en memoria el cual demuestra que no pudo asignarle memoria
Nodo* crearNodo(int dato) {
    Nodo* nuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No pudo asignarse memoria.\n");
        exit(1);
    }
    nuevoNodo->dato = dato;
    nuevoNodo->altura = 1;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;
    
    return nuevoNodo;
}
// Esta funcion obtiene el balance que tiene el nodo
int obtenerBalance(Nodo* raiz) {
    if (raiz == NULL) {
        return 0;
    }
    return altura(raiz->izq) - altura(raiz->der);
}

// Esta funcion da el menor dato que tenga el arbol, recorre hasta encontrar el mas chico
Nodo* nodoMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

// ______________________________________________________________
// ROTACIONES Y BALANCEO
// ______________________________________________________________

// Rotacion hacia la derecha
Nodo* rotacionDerecha(Nodo* raiz) {
    Nodo* nuevaRaiz = raiz->izq;
    Nodo* hijoDer = nuevaRaiz->der;

    nuevaRaiz->der = raiz;
    raiz->izq = hijoDer;

    raiz->altura = maximo(altura(raiz->izq), altura(raiz->der)) + 1;
    nuevaRaiz->altura = maximo(altura(nuevaRaiz->izq), altura(nuevaRaiz->der)) + 1;

    return nuevaRaiz;
}

// Rotaicon hacia la izquierda
Nodo* rotacionIzquierda(Nodo* raiz) {
    Nodo* nuevaRaiz = raiz->der;
    Nodo* hijoIzq = nuevaRaiz->izq;

    nuevaRaiz->izq = raiz;
    raiz->der = hijoIzq;

    raiz->altura = maximo(altura(raiz->izq), altura(raiz->der)) + 1;
    nuevaRaiz->altura = maximo(altura(nuevaRaiz->izq), altura(nuevaRaiz->der)) + 1;

    return nuevaRaiz;
}

// ______________________________________________________________
// INSERTAR
// Esta funcion insertar hace que dandole un arbol ya existente
// y un dato poder hacer una insercion. Esto valida y organiza el arbol es decir,
// si el dato que metes es mas chico que el que esta arriba tenemos 
// que organizar el dato para que vaya a su izquierda. sino a su derecha
// esta funcion permite que el arbol sea una estructura muy buena a la hora de buscar un dato.
// ______________________________________________________________

Nodo* insertar(Nodo* raiz, int dato) {
    if(raiz == NULL) {
        return crearNodo(dato);
    }
    
    // esta validacion se hace siempre en cualquier tipo de arbol,
    // esto es para mantener la estructura de donde va el dato,
    // si es menor va para la izquierda.
    // en caso que sea mayor iria para el lado derecho
    if (dato < raiz->dato) {
        raiz->izq = insertar(raiz->izq, dato);
    } else if (dato > raiz->dato) {
        raiz->der = insertar(raiz->der, dato);
    } else {
        return raiz;
    }
    
    // aca se actualiza la altura del nodo actual
    raiz->altura = 1 + maximo(altura(raiz->izq), altura(raiz->der));
    
    // luego obtenemos el factor balance para verificar si contiene o no desbalanceo el arbol
    int balance = obtenerBalance(raiz);

    // Si el arbol se desbalancea, es decir tiene un baalance mayor a 1
    // existen 4 casos en los que se puede rotar el arbol

    // caso 1: izquierda - izquierda (rotacion simple DERECHA)
    if (balance > 1 && dato < raiz->izq->dato)
        return rotacionDerecha(raiz);
    
    // caso 2: derecha - derecha (rotacion simple IZQUIERDA)
    if (balance < -1 && dato > raiz->der->dato)
        return rotacionIzquierda(raiz);
    
    // caso 3: izquierda - derecha (rotacion doble: primero izquierda y luego derecha)
    if (balance > 1 && dato > raiz->izq->dato) {
        raiz->izq = rotacionIzquierda(raiz->izq);
        return rotacionDerecha(raiz);
    }

    // caso 4: derecha - izquierda (rotacion doble: primero derecha y luego izquierda)
    if (balance < -1 && dato < raiz->der->dato) {
        raiz->der = rotacionDerecha(raiz->der);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// ______________________________________________________________
// ELIMINAR
// Esta funcion lo que hace es eliminar un nodo y el dato.
// primero lo busca hasta encontrarlo, lo eliminar y lo balancea denuevo
// es decir esta funcion ademas de elimar rebalance el arbol
// para que no quede desbalanceado
// ______________________________________________________________
Nodo* eliminar(Nodo* raiz, int dato) {
    if (raiz == NULL) {
        return raiz;
    }

    if (dato < raiz->dato) {
        raiz->izq = eliminar(raiz->izq, dato);
    } else if (dato > raiz->dato) {
        raiz->der = eliminar(raiz->der, dato);
    } else {
        if ((raiz->izq == NULL) || (raiz->der == NULL)) {
            Nodo* temp = raiz->izq ? raiz->izq : raiz->der;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp; 
            }
            free(temp);
        } else {
            Nodo* temp = nodoMinimo(raiz->der);
            raiz->dato = temp->dato;
            raiz->der = eliminar(raiz->der, temp->dato);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->altura = 1 + maximo(altura(raiz->izq), altura(raiz->der));
    int balance = obtenerBalance(raiz);

    if (balance > 1 && obtenerBalance(raiz->izq) >= 0)
        return rotacionDerecha(raiz);

    if (balance > 1 && obtenerBalance(raiz->izq) < 0) {
        raiz->izq = rotacionIzquierda(raiz->izq);
        return rotacionDerecha(raiz);
    }

    if (balance < -1 && obtenerBalance(raiz->der) <= 0)
        return rotacionIzquierda(raiz);

    if (balance < -1 && obtenerBalance(raiz->der) > 0) {
        raiz->der = rotacionDerecha(raiz->der);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// ______________________________________________________________
// BUSCAR
// Esta funcion lo que hace es buscar un dato en el arbol
// primero hace la condicion de siempre que es ir buscando si es menor o mayor
// y hace recursivamente eso hasta encontrar el dato.
// ademas de eso da tambien el nivel del dato encontrado
// ______________________________________________________________
void buscar(Nodo* raiz, int dato, int nivel) {
    if (raiz == NULL) {
        printf("El numero %d no se encuentra en el arbol.\n", dato);
        return;
    }
    
    if (dato == raiz->dato) {
        printf("Numero %d fue encontrado en el nivel %d.\n", dato, nivel);
        return;
    }
    
    if (dato < raiz->dato) {
        buscar(raiz->izq, dato, nivel + 1);
    } else {
        buscar(raiz->der, dato, nivel + 1);
    }
}

// ______________________________________________________________
// RECORRIDOS
// Estas son 3 funciones las cuales son las mas importantes y principales
// a la hora de recorrer un arbol.
// (cada una con su explicacion)
// ______________________________________________________________

void inOrder(Nodo* raiz) {
    if(raiz != NULL) {
        inOrder(raiz->izq);
        printf("%d ", raiz->dato);
        inOrder(raiz->der);
    }
}

void preOrder(Nodo* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dato);
        preOrder(raiz->izq);
        preOrder(raiz->der);
    }
}

void postOrder(Nodo* raiz) {
    if (raiz != NULL) {
        postOrder(raiz->izq);
        postOrder(raiz->der);
        printf("%d ", raiz->dato);
    }
}

// funcion para que imprima los tres recorridos juntos
void imprimirRecorridos(Nodo* raiz) {
    printf("____________ RECORRIDOS ____________\n");
    printf("InOrder: ");
    inOrder(raiz);
    printf("\nPreOrder: ");
    preOrder(raiz);
    printf("\nPostOrder: ");
    postOrder(raiz);
    printf("____________________________________\n");
}

// ______________________________________________________________
void imprimirArbolRecursivo(Nodo *raiz, int espacio) {
    if (raiz == NULL)
        return;

    espacio += ESPACIO_NIVEL;

    imprimirArbolRecursivo(raiz->der, espacio);

    printf("\n");
    for (int i = ESPACIO_NIVEL; i < espacio; i++)
        printf(" ");
    
    printf("%d(h:%d)\n", raiz->dato, raiz->altura);

    imprimirArbolRecursivo(raiz->izq, espacio);
}

void imprimirArbol(Nodo* raiz) {
    printf("--- ESTRUCTURA DEL ARBOL ---\n");
    imprimirArbolRecursivo(raiz, 0);
    printf("-----------------------------------------------\n");
}

// esta funcion libera el espacio en memoria del malloc usado anteriormente
// va recorriendo y a medida que va agarrando el nodo le aplica free
// esta funcion free lo que hace es que la memoria guardada para el nodo que 
// le dio el malloc la libera para que no quede con ese dato
void liberarArbol(Nodo* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izq);
        liberarArbol(raiz->der);
        free(raiz);
    }
}

// ______________________________________________________________
// MENU INTERACTIVO
// ______________________________________________________________
int main() {
    Nodo* raiz = NULL;
    int opcion = 0;
    int dato;

    raiz = insertar(raiz, 10);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 60);
    raiz = insertar(raiz, 70);
    raiz = insertar(raiz, 80);

    while (opcion != 6) {
        printf("_____________________Menu arbol AVL______________________\n");
        printf("1. Insertar numero\n");
        printf("2. Eliminar numero\n");
        printf("3. Buscar numero\n");
        printf("4. Imprimir Arbol (Visual)\n");
        printf("5. Recorridos (InOrder / PreOrder / PostOrder)\n");
        printf("6. Salir\n");
        printf("_________________________________________________________\n");
        printf("Seleccione una opcion: ");
        
        if(scanf("%d", &opcion) != 1) {
            printf("Entrada invalida\n");
            break;
        }

        switch (opcion) {
            case 1:
                printf("Ingrese el numero a insertar: ");
                if(scanf("%d", &dato) == 1) {
                    raiz = insertar(raiz, dato);
                    printf("Numero %d insertado correctamente\n", dato);
                }
                break;

            case 2:
                if (raiz == NULL) {
                    printf("[-] El arbol esta vacio.\n");
                } else {
                    printf("Ingrese el numero a eliminar: ");
                    if(scanf("%d", &dato) == 1) {
                        raiz = eliminar(raiz, dato);
                        printf("Numero %d eliminado correctamente\n", dato);
                    }
                }
                break;

            case 3:
                if (raiz == NULL) {
                    printf("El arbol esta vacio\n");
                } else {
                    printf("Ingrese el numero a buscar: ");
                    if(scanf("%d", &dato) == 1) {
                        buscar(raiz, dato, 1);
                    }
                }
                break;

            case 4:
                if (raiz == NULL) {
                    printf("El arbol esta vacio\n");
                } else {
                    imprimirArbol(raiz);
                }
                break;

            case 5:
                if (raiz == NULL) {
                    printf("El arbol esta vacio\n");
                } else {
                    imprimirRecorridos(raiz);
                }
                break;

            case 6:
                printf("Libero memoria y salgo del programa, gracias por usar nuestro algoritmo\n");
                liberarArbol(raiz);
                break;

            default:
                printf("Opcion no valida. Ingrese un numero del 1 al 6.\n");
                while(getchar() != '\n');
                break;
        }
    }

    return 0;
}
