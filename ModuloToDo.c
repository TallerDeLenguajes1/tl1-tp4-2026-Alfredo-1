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
Nodo * buscarNodo(Nodo ** Start, Tarea tarea);
void mostrarLista(Nodo * Start);

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

    mostrarLista(start);
    
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
    //reservo memoria para un char de la descripcion
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

void mostrarLista(Nodo * Start){//no hace falta pasarle con doble puntero por que no se cambiara ningun dato
    Nodo * Aux = Start;
    printf("\n\n---------------Las tareas son------------");
    while (Aux)//muestra hasta llegar a NULL
    {
        printf("\n\ndescripcion de tarea: %s", Aux->T.Descripcion);
        printf("\nduracion de tarea: %d horas", Aux->T.Duracion);
        printf("\nID Tarea: %d", Aux->T.TareaID);

        Aux = Aux->Siguiente;
    }
}

/*en esta funcion quiero que pida como parametro la direccion del puntero a Start y el numero id
de la tarea que quiero transferir a la lista de tareas finalizadas
cambiar Tarea por id que recibe como parametro
usar ese id para comparar con cada nodo de la lista hasta encontrarlo
si no lo encuentra tengo que ver que retornar*/
Nodo * buscarNodo(Nodo ** Start, Tarea tarea){
    Nodo * Aux = * Start;
    //recorrera la lista hasta que aux llegue a null, o hasta que encuentre la tarea con el id buscado
    while (Aux && Aux->T.TareaID != tarea.TareaID)
    {
        //aux ira hasta el siguiente elemento del auxiliar
        Aux = Aux->Siguiente;
    }
    return Aux;
}
