#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"

/**
 * @brief Crea una nueva tienda.
 * @param name Nombre de la tienda.
 * @return Puntero a la tienda creada.
 */
Store *New_Store(const char *name)
{
    Store *s = (Store *)malloc(sizeof(Store));
    if (s)
    {
        s->cursor = s->first = s->last = NULL;
        s->len = 0;
        strcpy(s->store_name, name);
    }
    return s;
}
/**
 * @brief Destruye una tienda y libera memoria.
 * @param store Puntero a la tienda a destruir.
 * @warning SÓLO debe usarse para salir del programa, además de asegurarse que exista una tienda que borrar
 */
void Destroy_Store(Store **store)
{
    assert(store);
    NodeProduct *current = (*store)->first;
    NodeProduct *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        Destroy_Product(&current);
        current = next_node;
    }
    free(*store);
    *store = NULL;
}

/**
 * @brief Elimina un producto de la tienda y mueve a la derecha el cursor.
 * @warning elimina donde esta ubicado el cursor
 * @param store Puntero a la tienda.
 * @param id Identificador único del producto a eliminar.
 * @warning Debe de asegurarse que el producto exista antes de ejecutar esta función, en dado caso se disparara un 'assert()'
 */
void Remove_Product(Store *store)
{
    assert(store->cursor);
    if (store->cursor == store->first)
    {

        store->first = store->cursor->next;
        if (store->first != NULL)
        {
            store->first->prev = NULL;
        }
    }
    else if (store->cursor == store->last)
    {
        store->last = store->cursor->prev;
        store->last->next = NULL;
    }
    else
    {
        store->cursor->prev->next = store->cursor->next;
        store->cursor->next->prev = store->cursor->prev;
    }
    Adjust_ID(store);
    free(store->cursor->products);
    free(store->cursor);
    store->len--;
    fprintf(stdout, "Producto eliminado del inventario.\n");
}
static void Adjust_ID(Store *store)
{
    NodeProduct *n = store->cursor;
    while (n != NULL)
    {
        n->products->id--;
        n = n->next;
    }
}
/**
 * @brief Mueve el cursor a un ID dado por el usuario
 * @param store Puntero de store
 * @param key id a buscar en "store"
 * @return bool si fue posible mover el cursor
 */
bool Move_Cursor_By_ID(Store *store, int key)
{
    for (NodeProduct *n = store->first; n != NULL; n = n->next)
    {
        if (n->products->id == key)
        {
            store->cursor = n;
            return true;
        }
    }
    return false;
}
/**
 * @brief Elimina parte del inventario del producto
 * @param store Puntero de store
 * @return NodeProduct como copia de si mismo
 * @details en caso de no poder retirar más productos retornara un valor 'NULL'
 */
NodeProduct *Subtract_Product(Store *store)
{
    assert(store->cursor);
    if (store->cursor->products->stock > 0)
    {
        --store->cursor->products->stock;
        return (Get_Cursor(store));
    }
    else
    {
        return NULL;
    }
}
/**
 * @brief Obtiene el nodo donde esta el cursor
 * @param cart Puntero de NodeProduct a modificar
 */
NodeProduct *Get_Cursor(Store *store)
{
    return (store->cursor);
}

/**
 * @brief Calcula el número mínimo de monedas necesarias para hacer un cambio dado.
 *
 * Utiliza programación dinámica para calcular el número mínimo de monedas necesarias
 * para hacer un cambio dado, considerando hasta `i` denominaciones.
 *
 * @param i Índice actual de las denominaciones que se están considerando.
 * @param j La cantidad de cambio que se debe realizar.
 * @param denominaciones Arreglo de denominaciones de monedas disponibles.
 * @param tabla Tabla de programación dinámica que almacena los resultados intermedios.
 *
 * @return El número mínimo de monedas necesarias para hacer el cambio de la cantidad `j`.
 *         Retorna `INFINITO` si no es posible hacer el cambio.
 */
int compute_change(int i, int j, int denominations[], int table[][MAX_CHANGE])
{
    if (j == 0)
        return 0;
    if (i == 0 || j < 0)
        return INFINITY;

    if (table[i][j] != -1)
    {
        return table[i][j];
    }

    if (denominations[i - 1] > j)
    {
        table[i][j] = compute_change(i - 1, j, denominations, table);
    }
    else
    {
        table[i][j] = MIN(compute_change(i - 1, j, denominations, table),
                          1 + compute_change(i, j - denominations[i - 1], denominations, table));
    }

    return table[i][j];
}
/**
 * @brief Reconstruye y muestra la solución para el problema del cambio de monedas.
 *
 * Esta función sigue los resultados en la tabla de programación dinámica para determinar
 * qué monedas se utilizaron para hacer el cambio.
 *
 * @param denominaciones Arreglo de denominaciones de monedas disponibles.
 * @param tabla Tabla de programación dinámica que almacena los resultados.
 * @param i Número de denominaciones consideradas.
 * @param j La cantidad de cambio que se debe reconstruir.
 */
void reconstruct_solution(int denominations[], int table[][MAX_CHANGE], int i, int j)
{
    int current_denomination = -1;
    int count = 0;

    while (j > 0 && i > 0)
    {
        if (table[i][j] != table[i - 1][j])
        {
            if (denominations[i - 1] == current_denomination)
            {
                count++;
            }
            else
            {
                if (count > 0)
                {
                    printf("%dX %d\n", count, current_denomination);
                }
                current_denomination = denominations[i - 1];
                count = 1;
            }
            j -= denominations[i - 1];
        }
        else
        {
            i--;
        }
    }
    if (count > 0)
    {
        printf("%dX %d\n", count, current_denomination);
    }
}
/**
 * @brief Calcula el número mínimo de monedas necesarias para hacer un cambio dado.
 *
 * Utiliza programación dinámica para calcular el número mínimo de monedas necesarias
 * para hacer un cambio dado, considerando hasta `i` denominaciones.
 *
 * @param i Índice actual de las denominaciones que se están considerando.
 * @param j La cantidad de cambio que se debe realizar.
 * @param denominaciones Arreglo de denominaciones de monedas disponibles.
 * @param tabla Tabla de programación dinámica que almacena los resultados intermedios.
 *
 * @return El número mínimo de monedas necesarias para hacer el cambio de la cantidad `j`.
 *         Retorna `INFINITO` si no es posible hacer el cambio.
 */
int calculate_change(int change, int denominations[], int table[][MAX_CHANGE], int rows, int cols)
{
    if (change < 0 || change >= cols)
    {
        return -1;
    }

    if (table[0][0] == -1)
    {
        for (size_t i = 0; i < rows; ++i)
        {
            table[i][0] = 0;
        }

        for (size_t i = 1; i < cols; ++i)
        {
            table[0][i] = INFINITY;
        }
    }

    int coins = compute_change(rows - 1, change, denominations, table);
    if (coins == INFINITY)
    {
        printf("No hay forma de dar cambio\n");
    }
    else
    {
        reconstruct_solution(denominations, table, rows - 1, change);
    }
    return coins;
}

/**
 * @brief Añade productos a un NodeProduct
 * @param cart Puntero de NodeProduct a modificar
 */
void Sum_Product(NodeProduct *product)
{
    ++product->products->stock;
}