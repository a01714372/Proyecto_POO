#include "Tablero.h" // Incluye todas las declaraciones
#include <iostream>

// Variables globales para el tablero que son accedidas por los métodos
// Nota: 'dato' almacena la información de las 100 casillas del tablero.
coord dato[101];
int yp[11]={0,2,7,12,17,22,27,32,37,42,47};
int xp[11]={0,4,13,23,31,40,49,58,67,76,85};

using namespace std;

// --- IMPLEMENTACIÓN DE FUNCIONES GLOBALES ---

/**
 * @brief Implementación de gotoxy para mover el cursor.
 * @see gotoxy en Tablero.h
 */
void gotoxy(int x,int y) {
    HANDLE hcon= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPOS;
    dwPOS.X=x;
    dwPOS.Y=y;
    SetConsoleCursorPosition(hcon,dwPOS);
}

/**
 * @brief Implementación de dibujo para pintar en el plano.
 * @see dibujo en Tablero.h
 */
void dibujo(char plano[HEIGHT/dH][WIDTH/dW+1], int A, int B, char c) {
    B=HEIGHT/dH-1-B;
    if (A<0 || B<0 || A>=WIDTH/dW || B>=HEIGHT/dH) return;
    plano[B][A]=c;
}

// --- IMPLEMENTACIÓN DE MÉTODOS DE LA CLASE TABLERO ---

/**
 * @brief Implementación para dibujar los márgenes.
 * @see Tablero::Ptablero
 */
void Tablero::Ptablero (char plano[HEIGHT/dH][WIDTH/dW+1]) {
    // ... Código Ptablero ...
    int x=1, y=1;
    for (int i=0; i<WIDTH/dW; i++) {
        for (int j=0; j<HEIGHT/dH; j++) {
            if (x==1 || x==9 || y==1 || y==5)
                dibujo(plano,i,j,'*');
            y++;
            if (y>=6)
                y=1;
        }
        x++;
        if (x>=10)
            x=1;
    }
}

/**
 * @brief Implementación para dibujar casillas y mapear coordenadas.
 * @see Tablero::pintar
 */
void Tablero::pintar (char plano[HEIGHT/dH][WIDTH/dW+1]) {
    // ... Código pintar ...
    int x=1, y=1, n1=1, D=154, f=1, c=1;
    dato[0].ocupado=true;
    for (int i=0; i<HEIGHT/dH; i++) {
        for (int j=0; j<WIDTH/dW; j++) {
            if (x==5 && y==3) {
                dibujo(plano,j+2,i+1,D);
                dato[n1].c=c;
                dato[n1].f=f;
                n1++;
                D++;
                c++;
            }
            x++;
            if (x>=10)
                x=1;
            if (c>=11)
                c=1;
        }
        y++;
        if (y>=6) {
            y=1;
            f++;
        }
    }
}

/**
 * @brief Implementación para generar valores aleatorios de serpientes/escaleras.
 * @see Tablero::valor
 */
void Tablero::valor () {
    // ... Código valor (generación de escaleras y serpientes) ...
    // Se mantiene el código de generación aleatoria como estaba.
    for (int j=0; j<9; j++) {
        while (true) {
            int x=rand()%xn[j]+xm[j];
            int y=rand()%8+1;
            int gu=0;
            int p=0;
            int r=0;
            for (int i=0;i<101;i++) {
                if (dato[i].c==x && dato[i].f==y) {
                    if (dato[i].ocupado==false) {
                        dato[i].ocupado=true;
                        dato[i].E=1;
                        dato[i].infi=2;
                        dato[i].pos=j;
                        gu=i;
                        p=1;
                    }
                }
                if (p==1 && j<6) {
                    if (dato[i].c==(x+xf[j]) && dato[i].f==y+2) {
                        if (dato[i].ocupado==false) {
                            esc[j]=dato[gu];
                            dato[i].ocupado=true;
                            dato[i].E=1;
                            dato[i].infi=1;
                            dato[i].pos=j;
                            dato[i].H=i;
                            esf[j]=dato[i];
                            r=1;
                            break;
                        }
                    }
                }
                if (p==1 && j>=6) {
                    if (dato[i].c==x-1 && dato[i].f==y+2) {
                        if (dato[i].ocupado==false) {
                            esc[j]=dato[gu];
                            dato[i].ocupado=true;
                            dato[i].E=1;
                            dato[i].infi=1;
                            dato[i].pos=j;
                            dato[i].H=i;
                            esf[j]=dato[i];
                            r=1;
                            break;
                        }
                    }
                }
            }
            if (r==1)
                break;
        }
    }
    // serpientes
    for (int j=0; j<9; j++) {
        while (true) {
            int x=rand()%8+1;
            int y=rand()%8+1;
            int gu=0;
            int p=0;
            int r=0;
            for (int i=0;i<101;i++) {
                if (dato[i].c==x && dato[i].f==y) {
                    if (dato[i].ocupado==false) {
                        dato[i].ocupado=true;
                        dato[i].S=1;
                        dato[i].infi=1;
                        dato[i].pos=j;
                        gu=i;
                        p=1;
                    }
                }
                if (p==1) {
                    if (dato[i].c==x+1 && dato[i].f==y+2) {
                        if (dato[i].ocupado==false) {
                            ser[j]=dato[gu];
                            dato[i].ocupado=true;
                            dato[i].S=1;
                            dato[i].infi=2;
                            dato[i].pos=j;
                            dato[i].H=gu;
                            sef[j]=dato[i];
                            r=1;
                            break;
                        }
                    }
                }

            }
            if (r==1)
                break;
        }
    }
}

/**
 * @brief Implementación para dibujar escaleras.
 * @see Tablero::Pescaleras
 */
void Tablero::Pescaleras(char plano[HEIGHT/dH][WIDTH/dW+1]) {
    // ... Código Pescaleras ...
    int r=0;
    for (int j=0; j<3; j++) {
        for (int i=0; i<10; i++) {
            dibujo (plano,xp[esc[j].c]-1,yp[esc[j].f]+i,'|');
            dibujo (plano,xp[esc[j].c],yp[esc[j].f]+i,'-');
            dibujo (plano,xp[esc[j].c]+1,yp[esc[j].f]+i,'|');
        }
    }
    for (int j=3; j<6; j++) {
        r=0;
        for (int i=0; i<10; i++) {
            dibujo (plano,(xp[esc[j].c]-1)+r,yp[esc[j].f]+i,'/');
            dibujo (plano,(xp[esc[j].c])+r,yp[esc[j].f]+i,'-');
            dibujo (plano,(xp[esc[j].c]+1)+r,yp[esc[j].f]+i,'/');
            r++;
        }
    }
    for (int j=6; j<9; j++) {
        r=0;
        for (int i=0; i<10; i++) {
            dibujo (plano,(xp[esc[j].c]-1)-r,yp[esc[j].f]+i,'\\');
            dibujo (plano,(xp[esc[j].c])-r,yp[esc[j].f]+i,'-');
            dibujo (plano,(xp[esc[j].c]+1)-r,yp[esc[j].f]+i,'\\');
            r++;
        }
    }
}

/**
 * @brief Implementación para dibujar serpientes.
 * @see Tablero::Pserpientes
 */
void Tablero::Pserpientes (char plano[HEIGHT/dH][WIDTH/dW+1]) {
    // ... Código Pserpientes ...
    for (int j=0; j<9; j++) {
        for (int i=0; i<13; i++) {
            dibujo (plano,(xp[ser[j].c]+xys[i].x),(yp[ser[j].f]+xys[i].y),190);
        }
    }
}

/**
 * @brief Implementación para dibujar personaje.
 * @see Tablero::personaje
 */
void Tablero::personaje(char plano[HEIGHT/dH][WIDTH/dW+1],int& p, char n) {
    // ... Código personaje ...
    dibujo (plano, xp[dato[p].c],yp[dato[p].f]+1,'@');
    dibujo (plano, xp[dato[p].c]-2,yp[dato[p].f],n);
    dibujo (plano, xp[dato[p].c],yp[dato[p].f],219);
    dibujo (plano, xp[dato[p].c]-1,yp[dato[p].f],'/');
    dibujo (plano, xp[dato[p].c]+1,yp[dato[p].f],'\\');
    dibujo (plano, xp[dato[p].c]-1,yp[dato[p].f]-1,'/');
    dibujo (plano, xp[dato[p].c]+1,yp[dato[p].f]-1,'\\');
}

/**
 * @brief Implementación de la lógica de movimiento y casillas especiales.
 * @see Tablero::ejecucion
 */
void Tablero::ejecucion(int& p, int& pap, bool& act,int& D, int& con) {
    // ... Código ejecucion ...
    if (con>=D) {
        act=false;
        con=0;
        pap=0;
    }
    if (pap==0) {
        if (dato[p].ocupado==true) {
            if (dato[p].E==1) {
                if (dato[p].infi==1) {
                    p=esf[dato[p].pos].H;
                }
            }
            if (dato[p].S==1) {
                if (dato[p].infi==1) {
                    p=sef[dato[p].pos].H;
                }
            }
        }
    }
    if (act==true) {
        p++;
        con++;
    }
}

/**
 * @brief Implementación para vaciar estructuras de datos.
 * @see Tablero::vaciar
 */
void Tablero::vaciar() {
    // ... Código vaciar ...
    coord lim;
    for (int i=0; i<101; i++) {
        dato[i]=lim;
    }
    for (int i=0; i<9; i++) {
        esc[i]=lim;
        esf[i]=lim;
        ser[i]=lim;
        sef[i]=lim;
    }
}

/**
 * @brief Implementación para mostrar instrucciones.
 * @see Tablero::instructions
 */
void Tablero::instructions () {
    // ... Código instructions ...
    system ("cls");
    cout << "Instructions" << endl;
    cout << "----------------------"<< endl;
    cout << "Press the up arrow key to move player 1" << endl;
    cout << "Press the right arrow key to move player 2" << endl;
    cout << "Press the down arrow key to move player 3" << endl;
    cout << "Press the left arrow key to move player 4" << endl;
    cout << "Pres the ESC key to go to menu" << endl;
    cout << "Press a key to return to menu" << endl;
    getch();
}