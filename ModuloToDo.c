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
Nodo * buscarNodo(Nodo ** Start, int ID);
void mostrarLista(Nodo * Start);
Nodo * quitarNodo(Nodo ** Start, int ID);
Nodo * eliminarNodo(Nodo * nodo);
Nodo * buscarNodoEnDosListas(Nodo ** Start);
void mostrarNodo(Nodo * nodo);
void liberarMemoriaDeLista(Nodo ** Start);

int main()
{
    srand(time(NULL));
    Nodo * start = crearListaVacia();//sera la lista de tareas a realizar
    Nodo * start2 = crearListaVacia();//sera la lista de tareas realizadas
    Tarea tareaNueva;
    
    int condicion = 0;
    int opcion = 0;
    int id = 999;
    char buffer[50];
    char * tareaBuscada;
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
        } while (opcion !=1 && opcion!=2);//funcionara hasta que se ingrese una de las 2 opciones
        
        if(opcion == 1)//cuando la opcion 1 es ingresada, condicion toma el valor 1
            condicion = 1;
        else
            condicion = 0;
       
    } while (condicion == 1);//va a iterar hasta que condicion = 1

    printf("\n\n---------------Las tareas a realizar son------------");
    mostrarLista(start);

    
    printf("\n\n-----Ingrese el ID de la tarea que desea mover a la lista de 'Tareas Realizadas'-----------\n");
    do
    {
        printf("ID: ");
        scanf("%i", &id);
        limpiarBuffer();
        Nodo * tareaBuscada = buscarNodo(&start, id);
        if(tareaBuscada != NULL){
            insertarNodo(&start2,quitarNodo(&start, id));//agregamos a la nueva lista el nodo que quitamos de la otra lista
        }else
            printf("La tarea que esta buscando no existe");

        printf("\n1. Mover otra tarea\n2. Finalizar\n");
        do
        {
            printf("\nSu opcion: ");
            scanf("%d",&opcion);
            limpiarBuffer();
        } while (opcion !=1 && opcion!=2);

        if(opcion == 1)//cuando la opcion 1 es ingresada, condicion toma el valor 1
            condicion = 1;
        else
            condicion = 0;

    } while (condicion == 1);
    
    printf("\n\n---------------Las tareas pendientes son------------");
    mostrarLista(start);
    printf("\n\n---------------Las tareas realizadas son------------");
    mostrarLista(start2);

    //buscara la tarea en la lista 1, si no la encuentra buscada en lista 2
    //si tampoco la encuentra mostrara un mensaje diciendo que no encontro la tarea.
    Nodo *nodobuscado = buscarNodoEnDosListas(&start);
    if (nodobuscado != NULL)
    {
        printf("\n\n---------------Tarea pendiente------------");
        mostrarNodo(nodobuscado);
    }else{
        nodobuscado = buscarNodoEnDosListas(&start2);
        if (nodobuscado != NULL)
        {
            printf("\n\n---------------Tarea realizada------------");
            mostrarNodo(nodobuscado);
        }else
            printf("\nNo se encontro la tarea buscada");
    }
    
    liberarMemoriaDeLista(&start);
    liberarMemoriaDeLista(&start2);

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

void mostrarNodo(Nodo * nodo){
    if (nodo != NULL)
    {
        printf("\n\nID Tarea: %d", nodo->T.TareaID);
        printf("\nDescripcion de tarea: %s", nodo->T.Descripcion);
        printf("\nDuracion de tarea: %d horas", nodo->T.Duracion);
    }
    
    
}

void mostrarLista(Nodo * Start){//no hace falta pasarle con doble puntero por que no se cambiara ningun dato
    Nodo * Aux = Start;
     while (Aux)//muestra hasta llegar a NULL
    {
        mostrarNodo(Aux);
        Aux = Aux->Siguiente;
    }
}

Nodo * buscarNodo(Nodo ** Start, int ID){
    Nodo * Aux = * Start;
    //recorrera la lista hasta que aux llegue a null, o hasta que encuentre la tarea con el id buscado
    while (Aux && Aux->T.TareaID != ID)
    {
        //aux ira hasta el siguiente elemento del auxiliar
        Aux = Aux->Siguiente;
    }
    return Aux;
}

Nodo * quitarNodo(Nodo ** Start, int ID){
    Nodo ** aux = Start;//apuntamos al puntero actual
    //vaa recorrer la lista hasta encontrar el puntero buscado
    while(*aux && (*aux)->T.TareaID != ID){
        aux = &(*aux)->Siguiente;
    }
    //si encontramos el nodo con el id buscado, lo eliminamos de la lista y lo retornamos
    if (*aux)
    {
        Nodo *temp = *aux;//guardamos el nodo que vamos a quitar en una variable temporal
        *aux = (*aux)->Siguiente;//desvinculamos el nodo buscado de la lista
        temp->Siguiente = NULL;//ponemos en NULL para asegurar no llevar vinculos fuera de la lista
        
        return temp;//retornamos el temp
    }
    return NULL;//si no se encontro el nodo buscado retornamos null.
}

Nodo * eliminarNodo(Nodo * nodo){
    free(nodo);
}

Nodo * buscarNodoEnDosListas(Nodo ** Start){
    Nodo * Aux = * Start;
    int eleccion;
    int ID=0;
    char buffer [50];
    char * descripcion;

    printf("\nFormas disponibles para buscar una tarea\n");
    printf("\n1. ID\n2. Descripcion\n");
    do
    {
        printf("\nIngrese su eleccion: ");
        scanf("%i", &eleccion);
        limpiarBuffer();
    } while (eleccion != 1 && eleccion != 2);
    
    if(eleccion == 1){
        printf("\n\nID Tarea: ");
        scanf("%d",&ID);
        limpiarBuffer();
    }else{
        printf("\n\nDescripcion Tarea: ");
        fgets(buffer, sizeof(buffer),stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        descripcion = (char *)malloc((strlen(buffer)+1)*sizeof(char));
        strcpy(descripcion, buffer);
    }

    //recorrera la lista hasta que aux llegue a null, o hasta que encuentre la tarea buscada
    while (Aux )
    {   //verifico si coincide el id
        if (Aux->T.TareaID == ID){
            free(descripcion);//libero la memoria ocupada antes de retornar
            return Aux;
        }
            
        
        //strstr devuelve NULL si no encuentra la cadena
        if (strstr(Aux->T.Descripcion, descripcion) != NULL){
            free(descripcion);
            return Aux;
        }
        //aux ira hasta el siguiente elemento del auxiliar
        Aux = Aux->Siguiente;
    }
    free(descripcion);
    return Aux;
}

void liberarMemoriaDeLista(Nodo ** Start){
    Nodo * Aux = *Start;
    Nodo * siguiente;
    while (Aux != NULL)//va a iterar mientras el nodo
    {
        siguiente = Aux->Siguiente;//guardamos la direccion del siguiente nodo antes de borrar el actual.
        //liberamos la memoria de la descripcion un char
        if (Aux->T.Descripcion != NULL)
            free(Aux->T.Descripcion);
        //ahora liberamos la memoria de la estructura nodo
        free(Aux);
        //avanzamos al siguiente
        Aux = siguiente;
    }
    *Start = NULL;
}