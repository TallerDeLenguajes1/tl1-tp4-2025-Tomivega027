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

Nodo * CrearNodo(Tarea tarea){
    Nodo *Nnodo = (Nodo *)malloc(sizeof(Nodo));
    Nnodo->T = tarea;
    Nnodo->Siguiente = NULL;
    return Nnodo;
}

void InsertarNodo(Nodo **start, Nodo *NuevoNodo){

    NuevoNodo->Siguiente = *start;
    *start = NuevoNodo;
}

void MoverLista(Nodo **pendientes , Nodo **realizadas , int i){
    Nodo * actual = *pendientes;
    Nodo * anterior = NULL;

    while (actual != NULL)
    {
        if (actual->T.TareaID == i)//entra solo si actualTareaid es igual al id
        {
            if (anterior == NULL)//es el caso en donde la tarea es la primera de la lista
            {
                *pendientes = actual->Siguiente; //aqui pendientes deja de apuntar al primer nodo (lo borra)
            }else
            {
                anterior->Siguiente = actual->Siguiente; //es el caso en donde la lista esta en el medio o al final 

            }
            InsertarNodo(realizadas, actual);//insertamos la tarea en realizadas
        
        }

        anterior = actual; // aqui anterior pasa a tener el contenido de lo que tiene actual
        actual = actual->Siguiente; // aqui actual se mueve a la siguiente tarea
    }
    
}

void listarTarea(Nodo *lista){
    while (lista !=  NULL)
    {
        printf("\nId tarea:%d\n Descripcion tarea:%s\n Duracion tarea:%d\n" , lista->T.TareaID , lista->T.Descripcion, lista->T.Duracion);
        lista = lista->Siguiente;
    }
    
}

void buscarTarea(Nodo **pendientes , Nodo **realizadas ){
    Nodo *actual = *pendientes;
    Nodo *actual2 = *realizadas;

    int seleccion = 0;
    int encotrada = 0;
    printf("\nsi desea buscar tarea por id eliga 1 , y si es por clave eliga 0");
    scanf("%d" , &seleccion);

    if (seleccion == 1)
    {
        int idbuscar = 0;
        printf("ingrese el id de la tarea");
        scanf("%d" , &idbuscar);
        while (actual != NULL)
        {
            if (actual->T.TareaID == idbuscar)
            {
                puts("\n***Tarea pendiente****\n");
                printf("Id de la tarea: %d\nLa descripcion de la tarea es:%s\nLa duracion de la tarea es:%d\n", actual->T.TareaID , actual->T.Descripcion , actual->T.Duracion);
                encotrada = 1;
            }
            actual = actual->Siguiente;
        }

        while (actual2 != NULL)
        {
            if (actual2->T.TareaID == idbuscar)
            {
                puts("Tarea Realizada");
                printf("Id de la tarea: %d\nLa descripcion de la tarea es:%s\nLa duracion de la tarea es:%d\n", actual2->T.TareaID , actual2->T.Descripcion , actual2->T.Duracion);
                encotrada = 1;
            }
            actual2 = actual2->Siguiente;
        }
        
        if (encotrada == 0)
        {
            puts("no se encontro la tarea");
        }
        
        
    }else
    {
        char cadena[100];
        printf("ingrese la clave a buscar:");
        scanf("%s", &cadena);

        while (actual != NULL)
        {
            if (strstr(actual->T.Descripcion , cadena))
            {
                puts("Tarea pendiente");
                printf("Id de la tarea: %d\nLa descripcion de la tarea es:%s\nLa duracion de la tarea es:%d\n", actual->T.TareaID , actual->T.Descripcion , actual->T.Duracion);
                encotrada = 1;
            }
            actual = actual->Siguiente;
            
        }

        while (actual2 != NULL)
        {
            if (strstr(actual2->T.Descripcion , cadena))
            {
                puts("Tarea Realizada");
                printf("Id de la tarea: %d\nLa descripcion de la tarea es:%s\nLa duracion de la tarea es:%d\n", actual2->T.TareaID , actual2->T.Descripcion , actual2->T.Duracion);
                encotrada = 1;
            }
            actual2 = actual2->Siguiente;
            
        }

        if (encotrada == 0)
        {
            puts("no se encontro la tarea");
        }
        
        
        
    }
    
    
}

int main(){

    Nodo *pendientes = CrearListaVacia();
    Nodo *realizadas = CrearListaVacia();
    int id = 1000;
    int opcion = 0;
    Tarea tarea;
    
    do
    {
        printf("\ndesea ingresar una nueva tarea ? no=0 , si=1\n");
        scanf("%d",&opcion);
        if (opcion == 1)
        {
            tarea.TareaID = id++;
            char descripcionTT[100];
            fflush(stdin);
            printf("\ningrese la descripcion de la tarea:");
            fflush(stdin);
            gets(descripcionTT);
            tarea.Descripcion = (char*)malloc((strlen(descripcionTT) + 1) * sizeof(char ));
            strcpy(tarea.Descripcion, descripcionTT);

            do
            {
                printf("\ningrese la duracion de la tarea:");
                scanf("%d", &tarea.Duracion);
            } while (tarea.Duracion <10 || tarea.Duracion >100);
            
            InsertarNodo(&pendientes, CrearNodo(tarea));
            printf("\nNodo insertado\n");
            
        }        

    } while (opcion != 0);

    int cambiar = 0; 
    printf("desea pasar tareas de pendientes a realizadas? si.1 y no.0");
    scanf("%d", &cambiar);
do
{

    if (cambiar == 1)
    {
        int idmover;
        printf("ingrese el id de la tarea a mover:");
        scanf("%d",&idmover);
        MoverLista(&pendientes , &realizadas , idmover);

    }
    printf("desea pasar mas tareas de pendientes a realizadas? si.1 y no.0");
    scanf("%d", &cambiar);
} while (cambiar != 0);


    puts("Tareas pendientes");
    listarTarea(pendientes);
    puts("Tareas realizadas");
    listarTarea(realizadas);

    buscarTarea(&pendientes , &realizadas);

    return 0;
}