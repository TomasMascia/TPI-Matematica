# 🌳 Árbol AVL — Trabajo Práctico Integrador

**Materia:** Matemática  
**Lenguaje:** C  

Implementación completa de un **Árbol Binario de Búsqueda Auto-Balanceado (AVL)** con menú interactivo desde consola.

---

## ¿Por qué un Árbol AVL?

Un árbol binario de búsqueda común tiene un problema: si insertás los números en orden (1, 2, 3, 4...), el árbol se convierte en una lista y buscar un elemento pasa de ser **O(log n)** a **O(n)**, es decir, tan lento como recorrer todo uno por uno.

El AVL resuelve esto. Después de cada inserción o eliminación, **mide su propio desbalanceo** y se corrige solo aplicando rotaciones. De esta forma garantiza que la altura del árbol siempre sea logarítmica, sin importar el orden en que se carguen los datos.

```
Árbol desbalanceado        Árbol AVL balanceado
      10                         20
        \                       /  \
         20          →        10    30
           \
            30
```

---

## ¿Cómo se balancea?

Cada nodo guarda su **altura** y calcula su **factor de balance**:

```
factor = altura(hijo izquierdo) - altura(hijo derecho)
```

Si ese valor sale de rango `{-1, 0, 1}`, el árbol aplica una rotación según el caso:

| Caso | Rotación |
|------|----------|
| Izquierda - Izquierda | Simple derecha |
| Derecha - Derecha | Simple izquierda |
| Izquierda - Derecha | Doble: primero izquierda, luego derecha |
| Derecha - Izquierda | Doble: primero derecha, luego izquierda |

---

## Funcionalidades

```
========== MENU AVL ==========
1. Insertar numero
2. Eliminar numero
3. Buscar numero
4. Imprimir Arbol (Visual)
5. Recorridos (InOrder / PreOrder / PostOrder)
6. Salir
==============================
```

- **Insertar** — Agrega un número respetando el orden y rebalancea si es necesario.
- **Eliminar** — Borra el nodo y usa el sucesor inorden para mantener la estructura, luego rebalancea.
- **Buscar** — Encuentra el número e informa en qué nivel del árbol está.
- **Imprimir** — Muestra el árbol rotado 90° con la altura de cada nodo.
- **Recorridos** — Imprime los elementos en los tres órdenes clásicos.

---

## Cómo ejecutarlo

```bash
gcc avl.c -o avl
./avl
```

## Complejidad

| Operación | Complejidad |
|-----------|-------------|
| Búsqueda  | O(log n)    |
| Inserción | O(log n)    |
| Eliminación | O(log n)  |

---

## Autores

- Nombre — [@usuario](https://github.com/TomasMascia)
