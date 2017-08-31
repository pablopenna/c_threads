#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define n_coches 8



	
	void string_generator(char * string,int str_len)
	/*arg= string's lenght*/
	{
		//[A-Z] in ASCII=[65-90]
		int j;

		for(j=0;j<str_len;j++)
		{
			string[j]=(rand()%25)+65;//random=random int from 65 to 90
		}
		string[str_len]='\0';
	}
	



// Array para los identificadores de los hilos
	pthread_t tabla_hilos [n_coches];

// Tipo de datos hilos_param
	typedef struct {
		int id ;
		char* cadena;
	} hilos_param;

// Array de datos de tipo hilos_param	
	hilos_param parametros [n_coches];

//Total del tiempo esperado

	int suma=0;
	pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;//Crear semáforo


// Funcion ejecutada por los hilos
	void * funcion_coches (void * arg)
	{
		hilos_param *p;
		p=(hilos_param *) arg;
		
		int aleatorio ;
		printf("Salida >%s >%d \n",p->cadena, p->id);
		fflush(stdout);
		aleatorio=rand();
		sleep(1 +( aleatorio%4));
		printf("Llegada >%s >%d \n",p->cadena, p->id);
		/* CODE 2 */
		pthread_mutex_lock(&mutex);
		suma+=1+aleatorio%4;
		pthread_mutex_unlock(&mutex);//Done as explained to prevent race cond.
		pthread_exit((void *)p->id);
		/*End of CODE 2*/

	}
	
	
	
	int main (void)
	{
		int i=0;
		int *res;
		srand(time(NULL));//for the numbers created with rand to be reallyrandom
		printf("Inicio del proceso de creación de los hilos...\n");
		
		
		/*CODE 4*/
		pthread_mutex_init(&mutex,NULL);//Iniciar semáforo
		/*END OF CODE 4*/


		// Se procede a crear los hilos
		for(i=0;i<n_coches;i++)
		{
			/* CODE 1 */
			parametros[i].id=i;
			parametros[i].cadena="Race Car";//string_generator(cadenaId,6);
			/*arbitrary value, length of the string*/
			pthread_create(&tabla_hilos[i],NULL,funcion_coches,(void *)
			&parametros[i]);
			/*End of CODE 1*/
		}
		
		printf("Proceso de creacion de hilos terminado\n");
		printf("SALIDA DE COCHES\n");

		for (i=0; i < n_coches ; i ++)
		{
			/* CODE 3 */
			pthread_join(tabla_hilos[i],(void *)&res);
			/*End of CODE 3*/
		}

		pthread_mutex_destroy(&mutex);
		
		printf ("Todos los coches han LLEGADO A LA META\n");
		printf("El total de tiempo esperado es: %d\n",suma);
		return 0;
	}
