#ifndef SHOPING_CART_HEADER_H
#define SHOPING_CART_HEADER_H

/**
 * @brief Estructura para representar un carrito de compras.
 */
typedef struct Shopping_Cart
{
    NodeProduct *top;    /**< Puntero al nodo superior de la pila (último elemento añadido) */
    int LenProducts;     /**< Cantidad de productos añadidos(Implementación de un carrito) */
    float PriceProducts; /**< Total del precio acomulado en la pila*/
} Shopping_Cart;

Shopping_Cart *Create_Stack();
void Stack_Push(Shopping_Cart *stack, NodeProduct *product);
NodeProduct *Stack_Pop(Shopping_Cart *stack);
void Destroy_Stack(Shopping_Cart **stack);
float Get_Total_Amount_Cart(Shopping_Cart *cart);
int Get_Total_Cart(Shopping_Cart *cart);

#endif

/**
 * @author
 * Carro López Juan Manuel
 * Macazaga Aguilar Ricardo Fabian
 * Marín Pérez Daniela
 * Perez Casasola Lisset Adamari
 * @date 2025-05-22
 */

