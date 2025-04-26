#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Tarea {
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; // Texto dinámico
    int Duracion;      // Entre 10 y 100
} Tarea;

typedef struct Nodo {
    Tarea T;               // La tarea que contiene el nodo
    struct Nodo *Siguiente; // Puntero al siguiente nodo
} Nodo;


Nodo * CrearListaVacia(){
    return NULL;
}

Nodo * CrearNodo(int *id){
    Nodo * Nnodo = (Nodo *)malloc(sizeof(Nodo));
    
    Nnodo->T.TareaID = id++;
    printf("el id de la tarea es:%d\n", Nnodo->T.TareaID);

    char buff[100];
    printf("ingrese la descripcion de la tarea:");
    fflush(stdin);
    gets(buff);
    Nnodo->T.Descripcion = malloc(strlen(buff) + 1); // reservamos memoria 
    strcpy(Nnodo->T.Descripcion , buff); // copiamos la cadena 

    do
    {
        printf("ingrese la duracion de la tarea de entre 10 y 100:");
        scanf("%d", &Nnodo->T.Duracion);

    } while (Nnodo->T.Duracion < 10 || Nnodo->T.Duracion > 100);
    
    Nnodo->Siguiente = NULL;

    return Nnodo;
}

void InsertarNodo(Nodo ** Start , Nodo *Nodo)
{
    Nodo->Siguiente = *Start;
    *Start = Nodo ;
}

Nodo * buscarNodo(Nodo * Start, int IdBuscado)
{
    Nodo * Aux = Start;
    while(Aux && Aux->T.TareaID != IdBuscado)
    {
    Aux = Aux->Siguiente ;
    }
    return Aux;
}

void listarTareas(Nodo *lista1 , Nodo *lista2){

    while (lista1->Siguiente != NULL)
    {
        printf("\nlista de pendientes:\n");  
        printf("Tarea id : %d\n , Descripcion %s\n , Duracion %d\n", lista1->T.TareaID, lista1->T.Descripcion , lista1->T.Duracion); 
        lista1 = lista1->Siguiente;
    }
    
    while (lista2 != NULL)
    {
        printf("\nlista de Realizadas:\n");  
        printf("Tarea id : %d\n , Descripcion %s\n , Duracion %d\n", lista2->T.TareaID, lista2->T.Descripcion , lista2->T.Duracion);
        lista2 = lista2->Siguiente;
    }
    

}



int main(){

    Nodo *pendientes = CrearListaVacia();
    Nodo *realizadas = CrearListaVacia();
    
    int num = 0;
    int id = 1000;
    int idBuscado = 0;
    int opcion = 0;
    
    do
    {
        Nodo *Tnodo = CrearNodo(&id);
        InsertarNodo(&pendientes, Tnodo);

        printf("\ndesea seguir agregando tareas? si=0 , no=1");
        scanf("%d",&num);
        
    } while (num == 0);

    do
    {
        printf("ingrese el id de la tarea para moverla de pendentes a realizadas:");
        scanf("%d", &idBuscado);

        Nodo * encontrado = buscarNodo(pendientes, idBuscado);
        InsertarNodo(&realizadas , encontrado);
        printf("desea seguir moviendo tareas a realizadas? si= 0 , no=1\n");
        scanf("%d",&opcion);
    } while (opcion == 0);
    
    
    listarTareas(pendientes, realizadas);
    
    

    return 0;
}