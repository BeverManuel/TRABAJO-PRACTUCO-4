#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;								// primero creo un puntero de linked y lo igualo a NULL
    this =(LinkedList*)malloc(sizeof(LinkedList));		// luego le asigno un pedaso de memoria con maloc al punterior de linker
    if(this!=NULL)										// pregunto si el puntero no es nulo, luego de asignarlo con maloc
    {
        this->size=0;									// si no es nulo le cargo un valor en size
        this->pFirstNode=NULL;							// y pongo en nulo el firtnode
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)					// primero verifico que el punterio de linked no sea NULO asi poder luego obtener la cantidad de elementos
    {
        returnAux=this->size;		// si el punterio no fue nulo guardo en reuntoaux la cantidad de elelentos de la lista linked
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    int indice;													// inicialo mi indice
    Node* auxNodo=NULL;										// primero creo un puntero de la estructura nodo y lo coloco nulo

    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))// luego pregunto que el puntero de Linked no sea nulo, tambien pregunto que el nodoIndex sea menor que-
    {														//- la cantidad de la lista de linked, y pregunto que el nodo sea mayor o igual a 0
    	auxNodo=this->pFirstNode;							// guardo en primer nodo-registro
    	indice = 0;											// coloco en indice en 0
    	do
    	{
    		if(indice == nodeIndex)							// ahora pregunto, si el indice que estamos parados es el mismo que el que buscamos
    		{
    			break;										// si lo es salimos del do-while y lo retorno
    		}
    		else											// si el indice en donde estoy no es el mismo que el nodo que busco pasamos a al siguiente nodo
    		{
    			auxNodo=auxNodo->pNextNode;					// pasamos al siguiente nodo y lo guardamos en el aux
    			indice++;									// y incremento el indice a buscar para saber si es el que se esta buscando
    		}
    	}while(auxNodo != NULL);
    }
    return auxNodo;											// Retorno el indice que voy a usar
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* pNode;
    Node* auxNode;

    if(this!=NULL&&nodeIndex<=ll_len(this)&&nodeIndex>=0)
    {
        pNode=(Node*)malloc(sizeof(Node));			 	// creo espacion en memoria para el nodo que voy a usar y entonces asi puede usarlo para cargarlo
        pNode->pElement=pElement;						// al nodo le cargo el elemento que estoy utilizando

        if(nodeIndex==0)								// si el indice es el 0 cargamos los datos a utilizar
        {
            returnAux=0;
            pNode->pNextNode=this->pFirstNode;
            this->pFirstNode=pNode;
            this->size++;
        }else											// si no es el indice 0  llamo al get y le indico cual es el ultimo elemento de la lista y lo guardo en el
        {												// nodo
            auxNode=getNode(this, nodeIndex-1);			// busco la posicion del nodo anterior(-1) y guardo el dato obtenedio en el auxiliar como next
            if(auxNode!=NULL)
            {
                returnAux=0;
                pNode->pNextNode=auxNode->pNextNode;
                auxNode->pNextNode=pNode;
                this->size++;
            }
        }
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	    if(this!=NULL)								// pregunto que el puntero de linkd sea distinto de NULL
	    {
	        if(ll_len(this)==0)						// pregunto el tamaño de linkd es igual a 0 si lo es lo incialo como la primer casilla en addnode
	        {
	            addNode(this,0,pElement);
	        }
	        else									// si no era 0 en le cargo el tamaño del linkd - posicion - y lo cargo
	        {
	            addNode(this,ll_len(this),pElement);
	        }
	         returnAux=0;
	    }
	    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* aux = NULL;

    if(this!=NULL && index>=0 && index < ll_len(this))	// consulto si el elemento link THIS que ingresa es distinto a null y si el indice es mayor o igul a 0
    {													// y menor al tamaño de la lista
            aux=getNode(this,index);					// busco el nodo - posicion de la lista del indice a obtener y lo guardamos en el aux
            returnAux=aux->pElement;					// lo encontrado que se guardo en aux lo retornamos
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* setNode=NULL;
    if(this!=NULL && index>=0 && index<ll_len(this))	// consulto si el elemento link THIS que ingresa es distinto a null y si el indice es mayor o igul a 0
    {													// y menor al tamaño de la lista
        setNode=getNode(this,index);					// busco y obtengo el nodo a modificar y una vez encontrado lo guardo en setnode
        setNode->pElement=pElement;						// el elemento que se va a modificar lo guardo en setnode modificandolo
        returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* deleteNode=NULL;
    Node* aux=NULL;
    Node* siguienteNodo=NULL;
    if(this!=NULL && index>=0 && index<ll_len(this))	// consulto si el elemento link THIS que ingresa es distinto a null y si el indice es mayor o igul a 0
    {													// y menor al tamaño de la lista
    	deleteNode=getNode(this,index);					// busco y obtengo el nodo a eliminar y una vez encontrado lo guardo en deleteNode
        siguienteNodo=deleteNode->pNextNode;			// backapeo el siguiente nodo - direccion de memoria - en siguientenodo

        if(index==0)
        {
           this->pFirstNode=siguienteNodo;				//si el indice a eliminar es el 0 lo del backup que es el siguiente nodo lo reemplazo por el del primer
        }												//lugar en la lista (hago un errosque)
        else
        {												//si el elemento a eliminar no es el primero (0) paso a buscar el indice a buscar
            aux=getNode(this,index-1);					//busco la posicion del nodo anterior(-1) y guardo el dato obtenedio en el auxiliar como aux
            aux->pNextNode=siguienteNodo;				//en la siguiente direccion (nextnode) guardo el backup del siguiente nodo cargado previamente
            free(deleteNode);							//libero - saco de la memoria el elemento a borrar
        }
        this->size--;									//decremento la lista
        returnAux=0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int indice;
    if(this!=NULL)									//primero pregunto si this de linked es distinto a null
	{
    	for(indice=0;indice<=ll_len(this);indice++)  //luego hago un for QUE NO DEBERIA HACERSE - SEGUN LA PROFE - donde busco el indice a ir eliminando dentro de la lista
    	{										    //el cual saco el limite de la fila con la funcion len
    		ll_remove(this,0);					//llamo a remove y le doy los datos this y el indice que se ira borrando
    	}
    	returnAux = 0 ;
	}
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
	{
    	free(this);
    	returnAux = 0;
	}
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	Node* aux=NULL;
	Node* contenedor=NULL;
	int indice=0;

	aux=(Node*)malloc(sizeof(Node));					//primero incializo el auxiliar del puntero a nodo
	if(aux!=NULL)										//pregunto que no sea nulo
	{
		aux->pElement=pElement;							//al auxiliar le cargo el elemento a buscar
		aux->pNextNode=NULL;
	}

	if(this!=NULL)										//pregunto si this de linked es distinto a null
	{
		for(indice=0;indice<ll_len(this);indice++)		//realizo el for del limite de la lista
		{
			contenedor=getNode(this,indice);			//cargo en el "contenedor" el nodo que se encuentra en el indice que
														//estay parado
			if(aux->pElement==contenedor->pElement)		//comparo el elemento buscado con el del "contenedor"
			{
				returnAux=indice;						//si lo encontro retorno el indice en el que estoy parado
				break;
			}
		}
	}
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)				// pregunto si this es nulo
    {
    	if(ll_len(this)==0)		//obtengo el tamaño de la lista
        {
            returnAux=1;		// si entra y vale 0 retorno 1 que indica que esta vacia
        }
        else
        {
            returnAux=0;		// si entra y tiene algun dato retorno 0 y significa que tiene un valor
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    int validacion;											//creo variable para validar el indice agregado
    if(this!=NULL && index>=0 && index<= ll_len(this))	//pregunto si this es nulo y index sea mayor a o igual a 0
    {													//y que el index no supere al tamaño de la lista
    	validacion= addNode(this,index,pElement);		//agrego el dato en la lista y en el indice dado
    	if(validacion==0)								//guardo lo devuelto en addnote en validacion y lo valido
    	{												//el cual si me devolvio 0 - OK retono 0 indicando que se efectuo bien
    		returnAux=0;
    	}
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))	//pregunto si this es nulo y index sea mayor a o igual a 0
        {												//y que el index no supere al tamaño de la lista
            returnAux=ll_get(this,index);				//guardo en returno el elemento del nodo que se encuentre en el puntero
            											//linked THIS en el indice indicado
            ll_remove(this,index);
        }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this!=NULL)								//PREGUNTO SI THIS ES DISNTO DE NULL (DE SERLO DAMOS UN ERROR
	{
		if(ll_indexOf(this,pElement)!=-1)		//ahora busco el elemento solicitado si esta en la lista
		{
			returnAux=1;						//si esta renotorno uno
		}
		else
		{
			returnAux=0;						//si no esta en la lista (pero this existe) retorno 0
		}
	}
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int indice;
    int flag = 1;
    if(this!= NULL && this2!= NULL)							//PREGUNTO SI THIS ES DISNTO DE NULL (DE SERLO DAMOS UN ERROR
    {
    	for(indice=0; indice<ll_len(this2) ;indice++)		//HAGO UN FOR EL CUAL PASA HASTA EL LIMITE DE LA SEGUNDA LISTA
    	{
    		if(ll_contains(this,ll_get(this2, indice))==0)	//AHORA CONSULTA EL INDICE DE LA LISTA 2 NO COINDICE CON EL DE LA 1
    		{
    			returnAux=0;								//ROTORNO 0 AL NO HABER HABIDO UN VALIR IGUAL
    			flag=0;										//PONGO FLAG EN 0 ENTONCES AL NO ESTAR EL ELEMTNO EN LA LISTA
    			break;
    		}
    	}
    	if(flag==1)											//SI FLAG NO SE CAMBIO EN EL FOR ANTERIOR ENTONCES QUIERE DECIR
    	{													//QUE LOS ELEMENTOS ESTAN EN LA LISTA2
    		returnAux=1;
    	}
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int indice;
    if(this!=NULL && from>=0 && from<=ll_len(this) && to>from && to<=ll_len(this)) //pregunto que this no sea nulo a su vez
    {									//que from sea mayor o igual a 0 y no superior al tamño de la lista, lo mismo con to
    	cloneArray= ll_newLinkedList();								//a clonearray lo incializo
    	if(cloneArray!=NULL)										//pregunto que no sea nulo lo entregado
    	{
    		for(indice=from; indice<to ;indice++)					//en indice le cargo el punto incial desde donde arracar el
    		{											// cual es FROM y tiene que ir leyendo creando/retornando hasta el TO que es el maximo
    			ll_add(cloneArray,ll_get(this,indice));	//empiezo a cargar los elementos en la nueva lista
    		}
    	}
    }

    return cloneArray;					//retorno la lista una vez realizada la carga
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this!=NULL)									//pregunto si this no es nulo
	{
		cloneArray=ll_subList(this,0,ll_len(this)); //en clone le devuelvo la lista clonada gradas al sublist donde le cargo
	}										//this luego que el primer indice es 0 y que lea hasta el final del tamaño de la lista
    return cloneArray;						//lo que devuelvo es el clone con la lista copiada en el
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */

int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int i,j;
    void* aux=NULL;
    if(this!=NULL && pFunc!=NULL && order>=0 && order<=1)
    {
        for(i=0; i< ll_len(this)-1; i++)
        {
            for(j=i+1; j< ll_len(this); j++)
            {
                if(pFunc(ll_get(this,i), ll_get(this,j))<0 && !order)
                {
                    aux=ll_get(this,i);
                    ll_set(this,i,ll_get(this,j));
                    ll_set(this,j,aux);
                }
                else if(pFunc(ll_get(this,i), ll_get(this,j))>0 && order)
                {
                    aux=ll_get(this,i);
                    ll_set(this,i,ll_get(this,j));
                    ll_set(this,j,aux);
                }
            }
        }
        returnAux=0;

    }
    return returnAux;

}
