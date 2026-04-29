#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
} Tarea; 

typedef struct Nodo{ 
    Tarea T;  
    struct Nodo *Siguiente;  
} Nodo; 

void limpiarBuffer();
Nodo * crearListaVacia();
Nodo * crearNodo(Tarea nuevaTarea);
Tarea cargarTarea(int id);
void insertarNodo(Nodo ** Start, Nodo * nuevoNodo);

int main()
{
    srand(time(NULL));
    Nodo * start = crearListaVacia();
    Tarea tareaNueva;
    
    int condicion = 0;
    int opcion = 0;
    static int id = 999;

    do
    {
        id++;
        tareaNueva = cargarTarea(id);
        insertarNodo(&start, crearNodo(tareaNueva));

        printf("\n-----Seleccione una opcion-----------\n\n");
        printf("1. Ingresar nueva tarea\n2. Finalizar carga de tarea");
        do
        {
            printf("\nSu opcion: ");
            scanf("%d",&opcion);
            limpiarBuffer();
        } while (opcion !=1 && opcion!=2);
        
        if(opcion == 1){
            condicion = 1;
        }else
            condicion = 0;

    } while (condicion == 1);
    Nodo * Aux = start;
    printf("\n\n---------------Las tareas son------------");
    while (Aux)
    {
        printf("\n\ndescripcion de tarea: %s", Aux->T.Descripcion);
        printf("\nduracion de tarea: %d horas", Aux->T.Duracion);
        printf("\nID Tarea: %d", Aux->T.TareaID);

        Aux = Aux->Siguiente;
    }
    
    
    return 0;
}

void limpiarBuffer (){
    int c;
    while((c=getchar())!= '\n' && c!=EOF){}
}

Nodo * crearListaVacia(){
    return NULL;
}

Tarea cargarTarea(int id){
    Tarea nuevaTarea;

    char buffer[100];
   
    printf("\n---------Cargar tarea--------");
    printf("\n\ningrese 'descripcion' de tarea pendiente: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")]= '\0';
    nuevaTarea.Descripcion = (char *) malloc((strlen(buffer)+1) * sizeof(char));

    if(nuevaTarea.Descripcion != NULL) {
        strcpy(nuevaTarea.Descripcion, buffer);
    }
    nuevaTarea.Duracion = 10 + rand() % 91;

    nuevaTarea.TareaID = id;

    return nuevaTarea;
}

Nodo * crearNodo(Tarea nuevaTarea){
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));//reservo memoria para un nodo
    
    nodo->T = nuevaTarea;//carga con los datos  de muevaTarea

    nodo->Siguiente = NULL;

    return nodo;
}

void insertarNodo(Nodo ** Start, Nodo * nuevoNodo){
    //el nuevoNodo apunta a lo que antes era el primer elemento de la lista
    nuevoNodo->Siguiente = *Start;
    //el puntero inicial ahora apunta al nuevoNodo
    *Start = nuevoNodo;
}
