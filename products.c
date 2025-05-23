#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"
/**
 * @brief Crea un nuevo producto.
 * @param p Puntero al producto a crear.
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */

void Create_Node_Products(Products *p, int id, int codebar, float price, int stock, const char *name, const char *tag)
{
    p->id = id;
    p->codebar = codebar;
    p->price = price;
    p->stock = stock;
    strcpy(p->name, name);
    strcpy(p->tag, tag);
}

/**
 * @brief Modifica un nuevo producto.
 * @details para evitar redundancia se reutiliza la funcion create node para mayor comodidad de la API
 * @param p Puntero al producto a crear.
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Modify_Product(NodeProduct *p, int codebar, float price, int stock, const char *name, const char *tag)
{
    Create_Node_Products(p->products, p->products->id, codebar, price, stock, name, tag);
}
/**
 * @brief Crea un nuevo producto en la tienda.
 * @param nstore Puntero a la tienda donde se agregará el producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 */
void Create_Products(Store *nstore, int codebar, float price, int stock, const char *name, const char *tag)
{
    NodeProduct *n = New_Node(nstore->len, codebar, price, stock, name, tag);
    if (!n)
    {
        fprintf(stderr, "Memoria insuficiente");
        return;
    }
    if (nstore->len == 0)
    {
        nstore->first = nstore->last = n;
    }
    else
    {
        nstore->last->next = n;
        n->prev = nstore->last;
        nstore->last = n;
    }
    nstore->len++;
}
/**
 * @brief Crea un nuevo nodo de producto.
 * @details Esta funcion se cancelara en caso de no poder crear un producto
 * @param id Identificador único del producto.
 * @param codebar Código de barras del producto.
 * @param price Precio del producto.
 * @param stock Stock disponible del producto.
 * @param name Nombre del producto.
 * @param tag Etiqueta del producto.
 * @return Puntero al nuevo nodo creado.
 */
static NodeProduct *New_Node(int id, int codebar, float price, int stock, const char *name, const char *tag)
{
    NodeProduct *n = (NodeProduct *)malloc(sizeof(NodeProduct));
    if (n)
    {
        n->next = n->prev = NULL;
        n->products = (Products *)malloc(sizeof(Products));
        if (n->products)
        {
            Create_Node_Products(n->products, id, codebar, price, stock, name, tag);
        }
        else
        {
            free(n);
            n = NULL;
        }
    }
    return n;
}
/**
 * @brief Destruye un nodo de producto y libera memoria.
 * @param node Puntero al nodo a destruir.
 * @warning Debe asegurarse que "Product" sea diferente de 'NULL'
 */

void Destroy_Product(NodeProduct **node)
{
    assert(node);
    free((*node)->products);
    free(*node);
    *node = NULL;
}
