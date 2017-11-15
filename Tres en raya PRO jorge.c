#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAT 3

void imprimir(char tablero[3][3]);
void Pmedio(char tablero[3][3], int *fila, int *columna,int *puesto);
void Pesquina(char tablero[3][3], int *fila, int *columna,int *puesto);

int main(int argc, char** argv) {

    char tablero[MAT][MAT]={{' ',' ',' ',},{' ',' ',' ',},{' ',' ',' ',}};
    int i=0,j=0,k, fila, columna, turno=0, ganar=0, fAUX, cAUX, puesto;
    imprimir(tablero);
    while(turno<9 && ganar==0){
        if ((turno%2)+1==1){//juega el humano
            do{        
                printf("\nJugador %d. \nElige fila: ", (turno%2)+1);
                scanf("%d", &fila);
                fila--;
                printf("Elige columna: ");
                scanf("%d", &columna);
                columna--;
            }while(tablero[fila][columna]!=' ');}
        
        else{//juega la máquina
            puesto=0;
            printf("\nJugada CPU: \n");
            if(tablero[1][1]==' '){
                fila=1;
                columna=1;
                puesto++;}
            if(!puesto){//intenta hacer 3 en raya
                for(j=0, i=0; !(j==3 && i==0) && !puesto;i=(i+1)%3){
                    if(tablero[j][i]==' '){
                        if((i+j)%2){
                            if((tablero[j][(i+1)%3]=='X' && tablero[j][(i+2)%3]=='X') || (tablero[(j+1)%3][i]=='X' && tablero[(j+2)%3][i]=='X')){
                                fila=j;
                                columna=i;
                                puesto++;}}
                        else{
                            if((tablero[j][(i+1)%3]=='X' && tablero[j][(i+2)%3]=='X') || (tablero[(j+1)%3][i]=='X' && tablero[(j+2)%3][i]=='X') || (tablero[1][1]=='X' && tablero[2-j][2-i]=='X')){
                                fila=j;
                                columna=i;
                                puesto++;}}
                        }
                    if(i==2)
                        j++;}
                }
            if(!puesto){//bloquea al jugador
                fAUX=2-fila;
                cAUX=2-columna;
                if(tablero[fila][columna]==tablero[1][1] && tablero[fAUX][cAUX]==' '){
                    fila=fAUX;
                    columna=cAUX;
                    puesto++;}
                else if(tablero[fila][columna]==tablero[fila][cAUX] && columna!=1 && tablero[fila][1]==' '){
                    columna=1;
                    puesto++;}
                else if(tablero[fila][columna]==tablero[fAUX][columna] && fila!=1 && tablero[1][columna]==' '){
                    fila=1;
                    puesto++;}
                else if(fila==1 && columna!=1){
                    if(tablero[1][columna]==tablero[0][columna] && tablero[2][columna]==' '){
                        fila=2;
                        puesto++;}
                    else if(tablero[1][columna]==tablero[2][columna] && tablero[0][columna]==' '){
                        fila=0;
                        puesto++;}
                }
                else if(columna==1 && fila!=1){
                    if(tablero[fila][1]==tablero[fila][0] && tablero[fila][2]==' '){
                        columna=2;
                        puesto++;}
                    else if(tablero[fila][1]==tablero[fila][2] && tablero[fila][0]==' '){
                        columna=0;
                        puesto++;}}
                if(!puesto){//no puede hacer 3 en raya ni bloquear al jugador
                    if(tablero[1][1]=='X'){//coloca en los puntos medios
                        Pmedio(tablero, &fila, &columna, &puesto);
                    }
                    else{// coloca en las esquinas
                        Pesquina(tablero, &fila, &columna, &puesto);
                    }
                    if(!puesto){
                        Pmedio(tablero, &fila, &columna, &puesto);}
                }
            }
        }
        if (tablero[fila][columna]!=' ')
            return (10);
        if((turno++)%2)  //cambias jugador   
            tablero[fila][columna]='X';
        else
            tablero[fila][columna]='O';
        imprimir(tablero);
        if(fila==columna || fila+columna==2){
            if((tablero[0][0]!=' ' && tablero[1][1]==tablero[2][2] && tablero[2][2]==tablero[0][0]) || (tablero[0][2]!=' ' && tablero[1][1]==tablero[0][2] && tablero[1][1]==tablero[2][0]))
                ganar++;
        }
        if(tablero[fila][0]==tablero[fila][2] && tablero[fila][0]==tablero[fila][1])
            ganar++;
        else if(tablero[1][columna]==tablero[0][columna] && tablero[2][columna]==tablero[0][columna])
            ganar++;        
    }
    if(ganar){
        if((++turno)%2+1==2)
            printf("\n¡Ha ganado la CPU!");
        else
            printf("\n¡Ha ganado el jugador 1!");}
    else
        printf("\nEmpate.\n");
    return (EXIT_SUCCESS);
}

void imprimir(char tablero[3][3]){
    int k, i=0, j=0;
    printf("\n---------------\n");
    for(k=0;k<9;k++){ 
            printf("| %c |", tablero[i][(j++)%3]);
            if(!(j%3)){
                printf("\n|---++---++---|\n");
                i++;}
        }
}
void Pmedio(char tablero[3][3], int *fila, int *columna, int *puesto){
        
    for((*fila)=0, (*columna)=1, (*puesto)=0; (*puesto)==0 && (*fila)<3;){
        if(tablero[*fila][*columna]==' ')
            (*puesto)++;
        else{
            if (*columna)
                (*fila)++;
            *columna=((*columna)+2)%3;}
    }}

void Pesquina(char tablero[3][3], int *fila, int *columna, int *puesto){
    for((*fila)=0, (*columna)=0, (*puesto)=0; (*puesto)==0 && (*fila)<3;){
        if(tablero[*fila][*columna]==' ')
            (*puesto)++;
        else{
            (*fila)+=(*columna);
            (*columna)=((*columna)+2)%4;}}}