#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

typedef struct Producto {
    int ProductoID; // Numerado en ciclo iterativo
    int Cantidad;   // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
} Producto;

typedef struct Cliente {
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (aleatorio entre 1 y 5)
    Producto *Productos; // El tamaño de este arreglo depende de la variable
} Cliente;

float costoTotal(Cliente client);

int main() {
    srand(time(NULL));

    int canClientes;
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", &canClientes);

    Cliente *clientes = (Cliente *)malloc(sizeof(Cliente) * canClientes);

    for (int i = 0; i < canClientes; i++) {
        clientes[i].ClienteID = i;

        char buffer[100];
        printf("Ingrese el nombre del cliente %d: ", i + 1);
        scanf("%s", buffer);
        clientes[i].NombreCliente = (char *)malloc(strlen(buffer) + 1);
        strcpy(clientes[i].NombreCliente, buffer);

        clientes[i].CantidadProductosAPedir = rand() % 5 + 1;
        clientes[i].Productos = (Producto *)malloc(sizeof(Producto) * clientes[i].CantidadProductosAPedir);

        for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) {
            clientes[i].Productos[j].ProductoID = j;
            clientes[i].Productos[j].Cantidad = rand() % 10 + 1;
            clientes[i].Productos[j].TipoProducto = TiposProductos[rand() % 5];
            clientes[i].Productos[j].PrecioUnitario = (float)(rand() % 91 + 10);
        }
    }

    // Mostrar información
    for (int i = 0; i < canClientes; i++) {
        printf("\nCliente #%d\n", clientes[i].ClienteID);
        printf("Nombre: %s\n", clientes[i].NombreCliente);
        printf("Cantidad de productos a pedir: %d\n", clientes[i].CantidadProductosAPedir);

        for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) {
            Producto p = clientes[i].Productos[j];
            printf("  Producto #%d:\n", p.ProductoID);
            printf("    Tipo: %s\n", p.TipoProducto);
            printf("    Cantidad: %d\n", p.Cantidad);
            printf("    Precio unitario: $%.2f\n", p.PrecioUnitario);
            printf("    Precio total: $%.2f\n", p.Cantidad * p.PrecioUnitario);
        }

        float total = costoTotal(clientes[i]);
        printf(">>> Costo total del pedido: $%.2f\n", total);
    }

    // Liberar memoria
    for (int i = 0; i < canClientes; i++) {
        free(clientes[i].NombreCliente);
        free(clientes[i].Productos);
    }
    free(clientes);

    return 0;
}

float costoTotal(Cliente client) {
    float total = 0;
    for (int i = 0; i < client.CantidadProductosAPedir; i++) {
        total += client.Productos[i].Cantidad * client.Productos[i].PrecioUnitario;
    }
    return total;
}