#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"
/**
 * @brief Crea una nueva pila.
 * @return Puntero a la pila creada.
 */
Shopping_Cart *Create_Stack()
{
    Shopping_Cart *stack = (Shopping_Cart *)malloc(sizeof(Shopping_Cart));
    if (stack)
    {
        stack->top = NULL;
        stack->LenProducts = 0;
        stack->PriceProducts = 0;
    }
    return stack;
}

/**
 * @brief Agrega un producto a la pila (carrito de compras).
 * @param stack Puntero a la pila.
 * @param product Puntero al producto a agregar.
 */
void Stack_Push(Shopping_Cart *stack, NodeProduct *product)
{
    ++stack->LenProducts;
    stack->top = (NodeProduct *)realloc(stack->top, stack->LenProducts * sizeof(NodeProduct));
    stack->top[stack->LenProducts - 1] = *product;
    stack->PriceProducts += product->products->price;
}

/**
 * @brief Quita y devuelve el producto en la cima de la pila.
 * @param stack Puntero a la pila.
 * @return Puntero al producto en la cima de la pila.
 */

NodeProduct *Stack_Pop(Shopping_Cart *stack)
{
    assert(stack->top);
    --stack->LenProducts;
    stack->PriceProducts -= Get_Total_Amount_Cart(stack);
    return &stack->top[stack->LenProducts];
}
/**
 * @brief Destruye una pila y libera memoria.
 * @param stack Puntero a la pila a destruir.
 */
void Destroy_Stack(Shopping_Cart **stack)
{
    assert(stack);
    while ((*stack)->LenProducts != 0)
    {
        Stack_Pop(*stack);
    }
    free(*stack);
    *stack = NULL;
}

/**
 * @brief Calcula el total de los productos en el carrito de compras.
 * @param cart Puntero al carrito de compras.
 * @return Suma total de los productos en el carrito.
 */
float Get_Total_Amount_Cart(Shopping_Cart *cart)
{
    return cart->PriceProducts;
}
/**
 * @brief Devuelve la cantidad de objetos alojados en la pila (Carrito).
 * @param cart Puntero al carrito de compras.
 * @return Total de los productos
 */

int Get_Total_Cart(Shopping_Cart *cart)
{
    return cart->LenProducts;
}