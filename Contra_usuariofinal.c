#include <stdio.h>
#include <stdlib.h>

#define honorable_usuario 	1
#define computadora 		2

// Esquema general del programa:
// Las funciones copioposiciondetabla1atabla2 e imprimeposicion son solo para comodidad.
// La función evalpos evalúa una posición. Devuelve 0 si es o bien empate o bien todavía no ha ganado nadie, 
// 			1 si ha ganado el primer jugador y 2 si ha ganado el segundo
// La función mejorjugadasiguiente es una función con dos parámetros iniciales: el jugador que quieres que gane (1 ó 2) y la posición
//			Es una función definida sobre la estructura doble, es decir, que devuelve, en el fondo, tres cosas:
// 				jugadamejor: Un número del 0-8, que define qué jugará el ordenador.
// 				resultadomejorjugada: 0, 1, 2. Si la mejor jugada resulta en un empate, devuelve 0. 
// 					Si resulta en que gane el jugador 1, devolverá 1, y si resulta en que gané el ordenador 2
// 					Nótese que si todas las jugadas son perdedoras, la mejor jugada es perdedora también.
//			¿Cómo obtiene mejorjugadasiguiente la mejor jugada siguiente?	
// 				1) Si la partida está ganada, devuelve como resultadomejorjugada el número del ganador.
//				2) Si la partida no está ganada, juega cada jugada legal por separado y se llama a sí misma, con el tablero
//						con una jugada añadida, y con el objetivo de que gane el oponente.
//						El resultado de una jugada es el resultado de la mejor respuesta que puede dar el oponente a esa jugada.
//						Computados los resultados de todas las jugadas legales, se elige el mejor
//						*La magia de la recursión*

typedef struct {
	int jugadamejor;
	int resultadomejorjugada;
	int fail;
}doble;

int evalpos(int *p){
	
	// Pensamos en el tablero de la siguiente forma:
	// 0 1 2
	// 3 4 5
	// 6 7 8
	
	// Evaluamos "filas":
	
	int ganador=0;
	
	int i;
	for(i=0;i<=6;i=i+3){ // Este for se ejecuta para i=0, i=3, i=6
		if(*(p+i)!=0 && *(p+i)==*(p+i+1) && *(p+i)==*(p+i+2) ){
			if(ganador!=0 && ganador!=*(p+i)){
				return 22; // Hay dos ganadores
			}
			else{
				ganador=*(p+i);
			}
		}
	}
	
	// Evaluamos "columnas":
	
	for(i=0;i<=2;i=i+1){ // Este for se ejecuta para i=0, i=3, i=6
		if(*(p+i)!=0 && *(p+i)==*(p+i+3) && *(p+i)==*(p+i+6) ){
			if(ganador!=0 && ganador!=*(p+i)){
				return 22; // Hay dos ganadores
			}
			else{
				ganador=*(p+i);
			}
		}
	}
	
	// Evaluamos diagonales
	// Diagonal 0 4 8
	if(*(p+0)!=0 && *(p+0)==*(p+4) && *(p+0)==*(p+8) ){
		if(ganador!=0 && ganador!=*(p+0)){
			return 22; // Hay dos ganadores
		}
		else{
			ganador=*(p+0);
		}
	}
	
	// Diagonal 2 4 6
	if(p[2]!=0 && p[2]==p[4] && p[2]==p[6] ){ 
		// Aquí lo escribimos diferente para recordar que *p == p[0]; *(p+x) == p[x]
		if(ganador!=0 && ganador!=p[2]){
			return 22; // Hay dos ganadores
		}
		else{
			ganador=p[2];
		}
	}
	
	return ganador;
}

int imprimeposicion(int *p){
	printf("\n\nLa posicion actual del tablero es:\n");
	printf("%d,%d,%d",*p,*(p+1),p[2]); // Nota, *p == p[0]; *(p+x) == p[x]
	printf("\n%d,%d,%d",p[3],p[4],p[5]);
	printf("\n%d,%d,%d\n",p[6],p[7],p[8]);
	
}

doble mejorjugadasiguiente(int *p, int jugador){ 
	// Calcula la mejor jugada siguiente para el jugador "jugador", que debe ser o 1 ó 2.

	// Comprobaciones preliminares:
	doble error;
	error.jugadamejor=-1;
	error.resultadomejorjugada=-1;
	
	if(jugador!=1 && jugador!=2){
		error.fail=007;
		return error; //  No puede haber más de dos jugadores en un tres en raya.
	}
	if(evalpos(p)!=0){
		error.resultadomejorjugada=evalpos(p);
		error.fail=111;
		return error; // Si la partida ya está ganada, no hay mejor jugada siguiente.
	}
	
	// Chicha:
	int i;
	int tabla[9];
	int resultadoposicion[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1}; 
	doble output;
	output.jugadamejor=-33;
	output.fail=0;
	output.resultadomejorjugada=-1;
	int numerodehuecoslibres=0;
	
	for(i=0;i<9;i=i+1){ // i toma los valores de {0,...,8}
		
		copioposiciondetabla1atabla2(p,tabla); // p y tabla ya son punteros
		if(tabla[i]==0){
			numerodehuecoslibres = numerodehuecoslibres+1;
			
			tabla[i]=jugador;
			resultadoposicion[i]=mejorjugadasiguiente(tabla, 2-((jugador+1)%2)).resultadomejorjugada;
			//printf("\n%d,turno siguiente:%d",i,2-((jugador+1)%2));
			// 2-(jugador+1)%2 devuelve 2 si jugador =1 y 1 si jugador=2
			//printf("\nresultadoposicion[%d]= %d",i,resultadoposicion[i]);
			// prints diagnósticos
		}

	}
	
	
	
	for(i=0;i<9;i=i+1){
		if(resultadoposicion[i]==jugador){
			output.resultadomejorjugada=jugador;
			output.jugadamejor=i;
		}
		if(resultadoposicion[i]==0 && (output.resultadomejorjugada==-1 ||output.resultadomejorjugada!=jugador )){
			output.resultadomejorjugada=0;
			output.jugadamejor=i;
		}
		if(resultadoposicion[i]==(2-((jugador+1)%2))  && output.resultadomejorjugada==-1 ){ // Puede que la única jugada disponible le conceda la victoria al oponente
			output.resultadomejorjugada=2-((jugador+1)%2);
			output.jugadamejor=i;
		}
	}
	
	if(numerodehuecoslibres==0){
		output.resultadomejorjugada=evalpos(p);
	}
	return output;
}

int copioposiciondetabla1atabla2(int *tabla1, int *tabla2){ // Sé que hay 9 posiciones.
	int i;
	for(i=0;i<9;i=i+1){
		tabla2[i]=tabla1[i];
	}
}


int main(int argc, char *argv[]) {
	//int tabla[9]={0}; // inicializa todos a 0s. No funcionaría con otro número
	int tabla[9]={		0,0,0,
				0,0,0,
				0,0,0};				 
	doble movimiento; 
	int jugada_del_usuario;
	int contador =0;
	
	printf("Las posiciones del tablero son las siguientes:");
	printf("\n0 1 2\n3 4 5\n6 7 8\n");
	
	while(evalpos(tabla)==0 && contador<9){ // N.B:: Antes tenía <10, por lo que se volverá loco si se agota el tablero
	
		imprimeposicion(&tabla);

		printf("QUE JUGADA QUIERE JUGAR EL HONORABLE USUARIO? \n[UN NUMERO DEL 0-8] QUE DESIGNE A UNA CASILLA NO OCUPADA  ");
		scanf("\n%d",&jugada_del_usuario);
		
		while(jugada_del_usuario<0 || jugada_del_usuario>8 || tabla[jugada_del_usuario]!=0){
			printf("INTRODUZCA EL NOBLE USUARIO OTRA JUGADA  \n[UN NUMERO DEL 0-8] QUE DESIGNE A UNA CASILLA NO OCUPADA  ");
			scanf("\n%d",&jugada_del_usuario);			
		}
		
		tabla[jugada_del_usuario]=honorable_usuario; // honorable_usuario :=1.
				
		movimiento=mejorjugadasiguiente(&tabla, computadora);
		printf("\nLa computadora juega %d\n",movimiento.jugadamejor);
		tabla[movimiento.jugadamejor] = computadora; // computadora :=2
	
		contador=contador+1;
	}
	imprimeposicion(&tabla);
	printf("El resultado de la partida es %d",evalpos(tabla));
	
	//Para que no cierre la ventana al terminar. Añadido posteriormente.
	printf("Presiona cualquier tecla...");
	scanf("\n%c");
	
	return 0;
}
