#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
Nodo * crearNodo(int id, int duracion, char Descripcion);
void ingresarTarea();

int main()
{
    Nodo * start = crearListaVacia();
    Tarea nuevaTarea;
    char buffer[100];
    int opcion = 0;
    int condicion = 0;
    int id = 1000;
   do
   {
        printf("\n---------Cargar tarea--------");
        printf("\n\ningrese 'descripcion' de tarea pendiente: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")]= '\0';
        nuevaTarea.Descripcion = (char *) malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(nuevaTarea.Descripcion, buffer);

        nuevaTarea.Duracion = 10 + rand() % 91;

        id++;
        nuevaTarea.TareaID = id;

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
    
    

    printf("\n\nnueva tarea es: %s", nuevaTarea.Descripcion);
    printf("\nduracion de tarea: %d horas", nuevaTarea.Duracion);
    printf("\nID Tarea: %d", nuevaTarea.TareaID);

    free(nuevaTarea.Descripcion);
    return 0;
}

void limpiarBuffer(){
    int c;
    while((c=getchar())!= '\n' && c!=EOF){}
}

Nodo * crearListaVacia(){
    return NULL;
}

Nodo * crearNodo(int id, int duracion, char Descripcion){
    Nodo * nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->T.TareaID = id;
    nodo->T.Duracion = duracion;
    nodo->T.Descripcion = Descripcion;

    return nodo;
}