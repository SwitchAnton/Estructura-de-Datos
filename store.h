#ifndef STORE_HEADER_H
#define STORE_HEADER_H

/**
 * @file store.h
 * @brief Definiciones de estructuras y funciones para gestionar una tienda.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define INFINITY 10000
#define MAX_DENOMINATIONS 10
#define MAX_CHANGE 50000
#define MIN(x, y) ((x) < (y) ? (x) : (y))
/**
 * @brief Estructura para representar una tienda.
 */
typedef struct NodeProduct NodeProduct;

typedef struct Store
{
    NodeProduct *cursor; /**< Puntero al nodo actual en la tienda */
    NodeProduct *first;  /**< Puntero al primer nodo en la tienda */
    NodeProduct *last;   /**< Puntero al último nodo en la tienda */
    int len;             /**< Longitud de la tienda (cantidad de productos) */
    char store_name[30]; /**< Nombre de la tienda */
} Store;

static void Adjust_ID(Store *store);
Store *New_Store(const char *name);
void Destroy_Store(Store **store);
void Destroy_Product(NodeProduct **node);
void Remove_Product(Store *store);
bool Move_Cursor_By_ID(Store *store, int key);
NodeProduct *Subtract_Product(Store *store);
void Sum_Product(NodeProduct *product);
NodeProduct *Get_Cursor(Store *store);
int compute_change(int i, int j, int denominations[], int table[][MAX_CHANGE]);
void reconstruct_solution(int denominations[], int table[][MAX_CHANGE], int i, int j);
int calculate_change(int change, int denominations[], int table[][MAX_CHANGE], int rows, int cols);

#endif
/**
 * @author
 * Carro López Juan Manuel  
 * Macazaga Aguilar Ricardo Fabian
 * Marín Pérez Daniela
 * Perez Casasola Lisset Adamari
 * @date 2025-05-22
 */