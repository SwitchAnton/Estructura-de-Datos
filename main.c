/*
	gcc -c store.c -o store.o
	gcc -c main.c -o main.o
	gcc store.o main.o -o ./programa
*/

#include "store.h"
#include "products.h"
#include "shopping_cart.h"
#include "ui.h"

int main()
{
	char store_name[30];
	Print_Title();
	printf("\n\n\n\nInserte el nombre de su tienda (30 caracteres máximo):\n");
	// fgets para poder leer el nombre de la tienda con espacios
	fgets(store_name, sizeof(store_name), stdin);
	// Elimina el carácter de nueva línea que fgets puede incluir
	store_name[strcspn(store_name, "\n")] = 0;

	Store *nstore = New_Store(store_name);
	if (!nstore)
	{
		printf("\nError de memoria");
		return 1;
	}

	Create_Products(nstore, 355, 32.5, 3, "Cereal", "Cereales");
	Create_Products(nstore, 456, 15.0, 5, "Leche", "Lácteos");
	Create_Products(nstore, 789, 10.0, 10, "Pan", "Panadería");

	Shopping_Cart *cart = Create_Stack();
	if (!cart)
	{
		printf("\nError de memoria");
		Destroy_Store(&nstore);
		return 1;
	}

	bool quit = false, id_exist = false;
	int option = 0, amount, id = 0;
	// case 2
	char name[50], tag[30];
	int codebar, stock;
	float price;
	// case 7
	int money;
	do
	{

		Print_Menu(nstore->store_name);
		Print_Cart(cart);
		scanf("%d", &option);
		switch (option)
		{
		case 1:
			Printf_Inv(nstore);
			break;
		case 2:
			printf("Ingrese el código de barras: ");
			scanf("%d", &codebar);
			printf("Ingrese el precio: ");
			scanf("%f", &price);
			printf("Ingrese la cantidad en stock: ");
			scanf("%d", &stock);
			printf("Ingrese el nombre del producto: ");
			getchar(); // Consume el salto de línea pendiente
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = 0; // Elimina el salto de línea
			printf("Ingrese la etiqueta del producto: ");
			fgets(tag, sizeof(tag), stdin);
			tag[strcspn(tag, "\n")] = 0; // Elimina el salto de línea
			Create_Products(nstore, codebar, price, stock, name, tag);
			break;
		case 3:
			id = 0;
			printf("Ingrese el ID del producto a eliminar: ");
			scanf("%d", &id);
			id_exist = Move_Cursor_By_ID(nstore, id);
			if (id_exist)
			{
				printf("Producto eleminado.\n");
				Remove_Product(nstore);
			}
			else
			{
				printf("El producto con ID %d no existe en el inventario.\n", id);
			}
			break;
		case 4:
			id = 0;
			amount = 0;
			printf("Ingrese el ID del producto que desea agregar: ");
			scanf("%d", &id);
			Move_Cursor_By_ID(nstore, id);
			printf("Ingrese la cantidad de productos a agregar: ");
			scanf("%d", &amount);
			amount = abs(amount);
			while (amount > 0)
			{
				amount--;
				Sum_Product(Get_Cursor(nstore));
			}
			break;
		case 5:
			id = 0;
			amount = 0;
			printf("Ingrese el ID del producto que desea sustraer productos: ");
			scanf("%d", &id);
			id_exist = Move_Cursor_By_ID(nstore, id);
			if (!id_exist)
			{
				printf("El producto con ID %d no existe en el inventario.\n", id);
				break;
			}
			printf("Ingrese la cantidad de productos a eliminar: ");
			scanf("%d", &amount);
			amount = abs(amount);
			while (amount > 0)
			{
				amount--;
				NodeProduct *tmp = Subtract_Product(nstore);
				if (!tmp)
				{
					break;
				}
			}
			break;
		case 6:
			id = 0;
			printf("Ingrese el ID del producto a comprar: ");
			scanf("%d", &id);
			id_exist = Move_Cursor_By_ID(nstore, id);
			if (id_exist)
			{
				NodeProduct *ProdctAdd = Subtract_Product(nstore);
				if (ProdctAdd)
				{
					Stack_Push(cart, ProdctAdd);
					printf("Producto añadido al carrito.\n");
				}
				else
				{
					printf("Producto agotado.\n");
				}
			}
			else
			{
				printf("El producto con ID %d no existe en el inventario.\n", id);
			}
			break;
		case 7:
			id = 0;
			printf("Ingrese el ID del producto que desea modificar");
			scanf("%d", &id);
			id_exist = Move_Cursor_By_ID(nstore, id);
			if (!id_exist)
			{
				printf("El producto con ID %d no existe en el inventario.\n", id);
				break;
			}
			printf("Ingrese el código de barras: ");
			scanf("%d", &codebar);
			printf("Ingrese el precio: ");
			scanf("%f", &price);
			printf("Ingrese la cantidad en stock: ");
			scanf("%d", &stock);
			printf("Ingrese el nombre del producto: ");
			getchar(); // Consume el salto de línea pendiente
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = 0; // Elimina el salto de línea
			printf("Ingrese la etiqueta del producto: ");
			fgets(tag, sizeof(tag), stdin);
			tag[strcspn(tag, "\n")] = 0; // Elimina el salto de línea
			Modify_Product(Get_Cursor(nstore), codebar, price, stock, name, tag);
			break;
		case 8:
			if (Get_Total_Cart(cart) > 0)
			{
				printf("Ingrese la cantidad de efectivo recibida:");
				scanf("%d", &money);
				if (money >= Get_Total_Amount_Cart(cart))
				{
					Print_ticket(cart, money);
				}
				else
				{
					printf("Compra no realizada, Falta efectivo\n");
				}
			}
			else
			{
				printf("Compra no realizada, carrito vacío\n");
			}
			break;
		case 9:
			while (Get_Total_Cart(cart) > 0)
			{
				Sum_Product(Stack_Pop(cart));
			}
			printf("Carrito vaciado con éxito\n");
			break;
		case 10:
			quit = true;
			break;
		default:
			printf("Opción no válida. Por favor, ingrese un número entre 1 y 5.\n");
			break;
		}

	} while (!quit);

	Destroy_Store(&nstore);
	Destroy_Stack(&cart);

	return 0;
}
