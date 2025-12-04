#include "Tablero.h" // Incluye la clase Tablero y sus dependencias
#include "Tablero.cpp"
#include <iostream>
#include <stdlib.h> // Para system("cls")

using namespace std;

int main() {
    // Inicialización de constantes y plano
    srand (static_cast <unsigned> (time(0)));
    char plano[HEIGHT/dH][WIDTH/dW+1];
    for (int i=0; i<HEIGHT/dH; i++) {
        plano[i][WIDTH/dW]='\n';
    }
    plano[HEIGHT/dH+1][WIDTH/dW]='\0';

    Tablero juego;

    // Variables de estado del juego (jugadores, dados, control de animación, etc.)
    int p=1,j=1,k=1,l=1,o=1;
    int pap1=0,pap2=0,pap3=0,pap4=0,papia=0;
    bool act1=false,act2=false,act3=false,act4=false,actia=false;
    int con1=0,con2=0,con3=0,con4=0,conia=0;
    int D1=0,D2=0,D3=0,D4=0,DIA=0;
    int D=1, con=0, turno=1, nj=1;

    // Variables de control de tiempo (Frame Rate)
    float fps=24.0f;
    float dt=1.0f/fps;
    float acumulador=0.0f;
    clock_t inicio=clock();

    bool game=false;
    int op, u;

    do {
        // ... (Código del menú de selección de jugadores) ...
        system("cls");
        gotoxy(10,5); cout << "--------------------------------";
        gotoxy(10,6); cout << "|    Serpientes y escaleras    |";
        gotoxy(10,7); cout << "--------------------------------";
        gotoxy(10,9); cout << "     . Start Game";
        gotoxy(10,10); cout << "        1. 1 Player (vs IA)";
        gotoxy(10,11); cout << "        2. 2 Players";
        gotoxy(10,12); cout << "        3. 3 Players";
        gotoxy(10,13); cout << "        4. 4 Players";
        gotoxy(10,14); cout << "    5. Instructions";
        gotoxy(10,15); cout << "    6. Exit";
        gotoxy(10,16); cout << "    Select option:";
        cin >> op;
        fflush(stdin);

        p=j=k=l=o=1;
        D1=D2=D3=D4=DIA=0;
        D=1; con=0; turno=1;

        switch (op) {
            case 1:
            case 2:
            case 3:
            case 4:
                nj=op;
                game=true;
                juego.Ptablero(plano);
                juego.pintar(plano);
                juego.valor(); // Genera serpientes/escaleras
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
            // ... (Código del bucle principal, gestión de tiempo y entrada de teclado) ...
            clock_t final= clock();
            acumulador += float(final-inicio)/CLOCKS_PER_SEC;
            inicio=final;
            if (acumulador>=0.2f) acumulador=2.0f;

            while (acumulador >= dt) {
                // Lógica de entrada y turnos (detectando VK_UP, VK_RIGHT, etc.)
                // ...
                if (GetKeyState(VK_UP)&0x8000 && turno==1) { // JUGADOR 1
                    D1=D;
                    D=rand()%6+1;
                    turno=(nj==1)? 2 : 2;
                    pap1=1;
                    act1=true;
                }
                if (turno==2 && nj==1) { // TURNO DE LA IA
                    DIA=rand()%6+1;
                    turno=1;
                    papia=1;
                    actia=true;
                }
                if (GetKeyState(VK_RIGHT)&0x8000 && turno==2 && nj>=2) { // JUGADOR 2
                    D2=D;
                    D=rand()%6+1;
                    turno=(nj==2)? 1 : 3;
                    pap2=1;
                    act2=true;
                }
                if (GetKeyState(VK_DOWN)&0x8000 && turno==3 && nj>=3) { // JUGADOR 3
                    D3=D;
                    D=rand()%6+1;
                    turno=(nj==3)? 1 : 4;
                    pap3=1;
                    act3=true;
                }
                if (GetKeyState(VK_LEFT)&0x8000 && turno==4 && nj>=4) { // JUGADOR 4
                    D4=D;
                    D=rand()%6+1;
                    turno=1;
                    pap4=1;
                    act4=true;
                }

                if (GetKeyState(VK_ESCAPE)&0x8000) {
                    game=false;
                    juego.vaciar();
                    D=1; D1=D2=D3=D4=DIA=0;
                    p=j=k=l=o=1;
                    pap1=pap2=pap3=pap4=papia=0;
                    act1=act2=act3=act4=actia=false;
                    con1=con2=con3=con4=conia=0;
                    break;
                }

                // Llamadas a ejecucion para mover a todos los jugadores
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

                // Animación del dado
                con++;
                if (con>=3) {
                    D++;
                    con=0;
                }
                if (D==7) {
                    D=1;
                }
            }

            // --- DRAW (Dibujo en Consola) ---
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
            // Llamadas a métodos de dibujo del Tablero
            juego.Ptablero(plano);
            juego.pintar(plano);
            juego.Pescaleras(plano);
            juego.Pserpientes(plano);
            juego.personaje(plano,p,49);
            if (nj==1) juego.personaje(plano,o,50);
            if (nj>=2) juego.personaje(plano,j,50);
            if (nj>=3) juego.personaje(plano,k,51);
            if (nj>=4) juego.personaje(plano,l,52);

            // --- Lógica de Fin de Juego ---
            if (p>=100 || j>=100 || k>=100 || l>=100 || o>=100) {
                system("cls");
                if (p>=100) u=1;
                if (j>=100) u=2;
                if (k>=100) u=3;
                if (l>=100) u=4;
                if (o>=100 && nj==1) u=2;

                system("cls");
                cout << endl;
                cout << "-----------------------------------"<< endl;
                cout << "-------------Game Over-------------"<< endl;
                cout << "------THE WINNER IS PLAYER: " << u << "------" << endl;
                cout << "-----------------------------------"<< endl;
                Sleep(4000);
                game=false;
                juego.vaciar();
                D=1;
                con=0;
                D1=D2=D3=D4=DIA=0;
                p=j=k=l=o=1;
                pap1=pap2=pap3=pap4=papia=0;
                act1=act2=act3=act4=actia=false;
                con1=con2=con3=con4=conia=0;
            }

            puts(plano[0]);
        }
    }while (1);
    return 0;
}