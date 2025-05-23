#ifndef PRODUCTS_HEADER_H
#define PRODUCTS_HEADER_H

/**
 * @file store.h
 * @brief Este archivo se encarga con la gestion de los nodos de productos
 */

/**
 * @brief Estructura para representar un producto en la tienda.
 */
typedef struct Products
{
    int id;        /**< Identificador único del producto */
    int codebar;   /**< Código de barras del producto */
    float price;   /**< Precio del producto */
    int stock;     /**< Stock disponible del producto */
    char name[50]; /**< Nombre del producto */
    char tag[30];  /**< Etiqueta del producto */
} Products;

/**
 * @brief Estructura para representar un nodo en la lista enlazada de productos.
 */
typedef struct NodeProduct
{
    struct Products *products; /**< Producto almacenado en el nodo */
    struct NodeProduct *next;  /**< Puntero al siguiente nodo */
    struct NodeProduct *prev;  /**< Puntero al nodo previo */
} NodeProduct;

void Create_Node_Products(Products *p, int id, int codebar, float price, int stock, const char *name, const char *tag);
void Destroy_Product(NodeProduct **node);
static NodeProduct *New_Node(int id, int codebar, float price, int stock, const char *name, const char *tag);
void Create_Products(Store *nstore, int codebar, float price, int stock, const char *name, const char *tag);
void Modify_Product(NodeProduct *p, int codebar, float price, int stock, const char *name, const char *tag);


#endif
/**
 * @author
 * Carro López Juan
 * Macazaga Aguilar Ricardo Fabian
 * Marín Pérez Daniela
 * Perez Casasola Lisset Adamari
 * @date 2025-05-22
 */
