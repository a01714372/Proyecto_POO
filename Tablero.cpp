#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

const int WIDTH=810, HEIGHT=250; //Dimensiones de la pantalla
const int dW=9, dH=5; //Tamaño de cada pixel

struct coord {
    int c;
    int f;
    bool ocupado=false;
    int E=0; // escalera
    int S=0; // serpiente
    int infi=0; // 1=inicio  2=final
    int pos=0; // guarda en donde va a estar posicionado.
    int H=0; // Guarda el valor donde se encuentra el final.
};

struct coxy {
    int x;
    int y;
};

coord dato[101];
int yp[11]={0,2,7,12,17,22,27,32,37,42,47}; // Estas coordenadas no deben ser mayores a 50 y 90.
int xp[11]={0,4,13,23,31,40,49,58,67,76,85}; // Con estas coordenadas establecemos los puntos centrales de cada casilla.

void gotoxy(int x,int y) {
HANDLE hcon= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPOS;
    dwPOS.X=x;
    dwPOS.Y=y;
    SetConsoleCursorPosition(hcon,dwPOS);
}

void dibujo(char plano[HEIGHT/dH][WIDTH/dW+1], int A, int B, char c) {
    B=HEIGHT/dH-1-B;
    if (A<0 || B<0 || A>=WIDTH/dW || B>=HEIGHT/dH) return;
    plano[B][A]=c;
}

class Tablero {
private:
    coord esc[9]; // datos de las escaleras al inicio.
    coord esf[9]; // datos de las escaleras al final.
    coord ser[9]; // datos de las serpientes al inicio.
    coord sef[9]; // datos de las serpientes al final.
    int xn[9]={10,10,10,8,8,8,8,8,8};
    int xm[9]={1,1,1,1,1,1,3,3,3};
    coxy xys[13]={{1,0},{2,1},{3,2},{3,3},{3,4},{3,5},{4,6},{5,7},{6,8},{6,9},{7,9},{8,10},{9,10}}; // posiciones para generar el dibujo de la serpiente
    int xf[6]={0,0,0,1,1,1};

public:
    void Ptablero (char plano[HEIGHT/dH][WIDTH/dW+1]) { // dibuja los margenes del tablero
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
    void pintar (char plano[HEIGHT/dH][WIDTH/dW+1]) {
        int x=1, y=1, n1=1, D=154, f=1, c=1; // c y f son el número de filas y columnas, mientras que X y Y son el ancho y altura
        dato[0].ocupado=true;
        for (int i=0; i<HEIGHT/dH; i++) {
            for (int j=0; j<WIDTH/dW; j++) {
                if (x==5 && y==3) {// se ubica en el centro de cada recuadro
                    dibujo(plano,j+2,i+1,D); //D se usa para que en el centro se dibuje un simbolo ASC
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
    void valor () {
        for (int j=0; j<9; j++) {
            while (true) {
                int x=rand()%xn[j]+xm[j];
                int y=rand()%8+1;
                int gu=0;
                int p=0;
                int r=0;
                for (int i=0;i<101;i++) {
                    if (dato[i].c==x && dato[i].f==y) {
                        if (dato[i].ocupado==false) { // |-|   /-/   \-\ ]//
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

    void Pescaleras(char plano[HEIGHT/dH][WIDTH/dW+1]) { // esto dibuja la escalera |-|
        int r=0;
        for (int j=0; j<3; j++) { // Cambia las posiciones donde se encuentra la escalera
            for (int i=0; i<10; i++) { // Es la que hace la escalera
                dibujo (plano,xp[esc[j].c]-1,yp[esc[j].f]+i,'|');
                dibujo (plano,xp[esc[j].c],yp[esc[j].f]+i,'-');
                dibujo (plano,xp[esc[j].c]+1,yp[esc[j].f]+i,'|');
            }
        }
        for (int j=3; j<6; j++) { // Cambia las posiciones donde se encuentra la escalera
            r=0;
            for (int i=0; i<10; i++) { // Es la que hace la escalera
                dibujo (plano,(xp[esc[j].c]-1)+r,yp[esc[j].f]+i,'/');
                dibujo (plano,(xp[esc[j].c])+r,yp[esc[j].f]+i,'-');
                dibujo (plano,(xp[esc[j].c]+1)+r,yp[esc[j].f]+i,'/');
                r++;
            }
        }
        for (int j=6; j<9; j++) {
            // Cambia las posiciones donde se encuentra la escalera
            r=0;
            for (int i=0; i<10; i++) { // Es la que hace la escalera
                dibujo (plano,(xp[esc[j].c]-1)-r,yp[esc[j].f]+i,'\\');
                dibujo (plano,(xp[esc[j].c])-r,yp[esc[j].f]+i,'-');
                dibujo (plano,(xp[esc[j].c]+1)-r,yp[esc[j].f]+i,'\\');
                r++;
            }
        }
    }
    void Pserpientes (char plano[HEIGHT/dH][WIDTH/dW+1]) {
        for (int j=0; j<9; j++) {
            for (int i=0; i<13; i++) {
                dibujo (plano,(xp[ser[j].c]+xys[i].x),(yp[ser[j].f]+xys[i].y),190);
            }
        }
    }
    void personaje(char plano[HEIGHT/dH][WIDTH/dW+1],int& p, char n) {
        dibujo (plano, xp[dato[p].c],yp[dato[p].f]+1,'@');
        dibujo (plano, xp[dato[p].c]-2,yp[dato[p].f],n);
        dibujo (plano, xp[dato[p].c],yp[dato[p].f],219);
        dibujo (plano, xp[dato[p].c]-1,yp[dato[p].f],'/');
        dibujo (plano, xp[dato[p].c]+1,yp[dato[p].f],'\\');
        dibujo (plano, xp[dato[p].c]-1,yp[dato[p].f]-1,'/');
        dibujo (plano, xp[dato[p].c]+1,yp[dato[p].f]-1,'\\');
    }
    void ejecucion(int& p, int& pap, bool& act,int& D, int& con) {
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
    void vaciar() {
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
    void instructions () {
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
};

int main() {
    srand (static_cast <unsigned> (time(0))); // genera numeros aleatorios sin patron.
    char plano[HEIGHT/dH][WIDTH/dW+1];
    for (int i=0; i<HEIGHT/dH; i++) {
        plano[i][WIDTH/dW]='\n'; // Salto de linea de la matriz
    }
    plano[HEIGHT/dH+1][WIDTH/dW]='\O'; //Termina la matriz, su ultimo punto.

    Tablero juego; // Llamamos a la clase y asignamos un objeto.

    int p=1,j=1,k=1,l=1,o=1;
    int pap1=0,pap2=0,pap3=0,pap4=0,papia=0;
    bool act1=false,act2=false,act3=false,act4=false,actia=false;
    int con1=0,con2=0,con3=0,con4=0,conia=0;
    int D1=0,D2=0,D3=0,D4=0,DIA=0;
    int D=1, con=0, turno=1, nj=1;

    float fps=24.0f;
    float dt=1.0f/fps;
    float acumulador=0.0f;
    clock_t inicio=clock();

    bool game=false;
    int op, u;

    do {
        system("cls"); // limpia completamente la pantalla.
        gotoxy(10,5); cout << "--------------------------------";
        gotoxy(10,6); cout << "|    Serpientes y escaleras    |";
        gotoxy(10,7); cout << "--------------------------------";
        gotoxy(10,9); cout << "     . Start Game";
        gotoxy(10,10); cout << "        1. Player";
        gotoxy(10,11); cout << "        2. Players";
        gotoxy(10,12); cout << "        3. Players";
        gotoxy(10,13); cout << "        4. Players";
        gotoxy(10,14); cout << "    5. Instructions";
        gotoxy(10,15); cout << "    6. Exit";
        gotoxy(10,16); cout << "    Select option:";
        cin >> op;
        fflush(stdin); //limpia op
        switch (op) {
            case 1:
                nj=1;
                game=true;
                juego.Ptablero(plano);
                juego.pintar(plano);
                juego.valor();
                system("cls");
                break;
            case 2:
                nj=2;
                game=true;
                juego.Ptablero(plano);
                juego.pintar(plano);
                juego.valor();
                system("cls");
                break;
            case 3:
                nj=3;
                game=true;
                juego.Ptablero(plano);
                juego.pintar(plano);
                juego.valor();
                system("cls");
                break;
            case 4:
                nj=4;
                game=true;
                juego.Ptablero(plano);
                juego.pintar(plano);
                juego.valor();
                system("cls");
                break;
            case 5:
                juego.instructions();
                break;
            case 6:
                exit(0);
                break;
        }
        while (game) {
            clock_t final= clock();
            acumulador += float(final-inicio)/CLOCKS_PER_SEC;
            inicio=final;
            if (acumulador>=0.2f) acumulador=2.0f;
            while (acumulador >= dt) {
                if (GetKeyState(VK_UP)&0x8000 && turno==1) { //Esto sirve para detectar teclas
                    D1=D;
                    D=rand()%6+1;
                    turno=2;
                    pap1=1;
                    act1=true;
                }
                if (turno==2 && nj==1) {
                    DIA=rand()%6+1;
                    turno=1;
                    papia=1;
                    actia=true;
                }
                if (GetKeyState(VK_RIGHT)&0x8000 && turno==2 && nj>=2) {
                    D2=D;
                    D=rand()%6+1;
                    if (nj==2)
                        turno=1;
                    if (nj>2)
                        turno=3;
                    pap2=1;
                    act2=true;
                }
                if (GetKeyState(VK_DOWN)&0x8000 && turno==3 && nj>=3) {
                    D3=D;
                    D=rand()%6+1;
                    if (nj==3)
                        turno=1;
                    if (nj>3)
                        turno=4;
                    pap3=1;
                    act3=true;
                }
                if (GetKeyState(VK_LEFT)&0x8000 && turno==4 && nj>=4) {
                    D4=D;
                    D=rand()%6+1;
                    turno=1;
                    pap2=1;
                    act2=true;
                }
                if (GetKeyState(VK_ESCAPE)&0x8000) {
                    game=false;
                    juego.vaciar();
                    D=1;
                    D1=D2=D3=D3=D4=DIA;//Dado
                    p=j=k=l; //jugador
                    pap1=pap2=pap3=pap4=papia=0;
                    act1=act2=act3=act4=actia=false;
                    con1=con2=con3=con4=conia=0;
                    break;
                }
                juego.ejecucion(p,pap1,act1,D1,con1);
                if (nj==1)
                    juego.ejecucion(o,papia,actia,DIA,conia);
                if (nj>=2)
                    juego.ejecucion(j,pap2,act2,D2,con2);
                if (nj>=3)
                    juego.ejecucion(k,pap3,act3,D3,con3);
                if (nj>=4)
                    juego.ejecucion(l,pap4,act4,D4,con4);

                acumulador -= dt;
                con++;
                if (con>=3) {
                    D++;
                    con=0;
                }
                if (D==7) {
                    D=1;
                }
            }
            gotoxy (10,0); cout << "Turno: " << turno;
            gotoxy (10,5); cout << "Dado J1 " << D1;
            gotoxy (22,5); cout << "Dado J2 " << D2;
            gotoxy (34,5); cout << "Dado J3 " << D3;
            gotoxy (46,5); cout << "Dado J4 " << D4;
            gotoxy (58,5); cout << "Dado IA " << DIA;


            gotoxy(0,6);
            for (int i=0; i<HEIGHT/dH; i++) {
                for (int j=0; j<WIDTH/dW; j++) {
                    plano[i][j]=' ';
                }
            }
            juego.Ptablero(plano);
            juego.pintar(plano);
            juego.Pescaleras(plano);
            juego.Pserpientes(plano);
            juego.personaje(plano,p,49);
            if (nj==1) juego.personaje(plano,o,50);
            if (nj>=2) juego.personaje(plano,j,50);
            if (nj>=3) juego.personaje(plano,k,51);
            if (nj>=4) juego.personaje(plano,l,52);

            if (p>=100 || j>=100 || k>=100 || l>=100 || o>=100) {
                system("cls");
                if (p>=100) {
                    u=1;
                }
                if (j>=100) {
                    u=2;
                }
                if (k>=100) {
                    u=3;
                }
                if (l>=100) {
                    u=4;
                }
                if (o>=100) {
                    u=2;
                }
                system("cls");
                cout << endl;
                cout << "-----------------------------------"<< endl;
                cout << "-------------Game Over-------------"<< endl;
                cout << "------THE WINNER IS PLAYER: " << u << "------" << endl;
                cout << "-----------------------------------"<< endl;
                Sleep(4000); // Pausa para que se muestr el mensaje
                game=false;
                juego.vaciar();
                D=1;
                con=0;
                D1=D2=D3=D4=DIA=0;
                pap1=pap2=pap3=pap4=papia=0;
                act1=act2=act3=act4=actia=false;
                con1=con2=con3=con4=conia=0;
            }

            puts(plano[0]);
        }
    }while (1);
    return 0;
}