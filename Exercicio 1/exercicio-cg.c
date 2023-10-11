#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <strings.h>
#include <math.h>

float xi, yi, xf, yf;
float r=0, g=0, b=1;
int click=0;
int escolha, w=5, escolha2;
int u=600, v=600;

void desenha(){
    glColor3f(r, g, b);
    if(escolha==0){
        glLineWidth(w);
        glBegin(GL_LINES);
            glVertex2f(xi,yi);
            glVertex2f(xf,yf);
    }
    else if(escolha==1){
        glLineWidth(w);
        glBegin(GL_LINE_LOOP);
        float radius = sqrt((pow((xi-xf), 2)+pow((yi-yf), 2)));
            for (int i = 0; i <= 300; i++){
                float angulo = (2*3.142*i)/300;
                glVertex2f(xi+(radius*cos(angulo)), yi + (radius*sin(angulo)));
            }
    }
    else if(escolha==2){
        glRectf(xi, yi, xf, yf);
    }
    glEnd();
    glFlush();
}

void escolher(unsigned char key, int x, int y){
    switch (key){
        case 'r':
        case 'R':
            xi=0, yi=0, xf=0, yf=0;
            escolha=0;
            break;
        case 'c':
        case 'C':
            xi=0, yi=0, xf=0, yf=0;
            escolha=1;
            break;
        case 'k':
        case 'K':
            escolha2=0;
            break;
        case 'e':
        case 'E':
            escolha2=1;
            break;
        case 'b':
        case 'B':
            xi=0, yi=0, xf=0, yf=0;
            escolha=2;
            break;
        case 'l':
        case 'L':
            xi=0, yi=0, xf=0, yf=0;
            glClearColor(0, 0, 0, 0);
            glClear(GL_COLOR_BUFFER_BIT);
            break;
    }
    glutPostRedisplay();
}

void mudacor(unsigned char key, int x, int y){
    switch (key){
    case '0':
        r=0;
        g=1.0;
        b=0;
        break;
    case '1':
        r=1.0;
        g=0.068;
        b=0.078;
        break;
    case '2':
        r=1.0;
        g=0.745;
        b=0.043;
        break;
    case '3':
        r=1.0;
        g=0.342;
        b=0.027;
        break;
    case '4':
        r=0.555;
        g=0.237;
        b=1.0;
        break;
    case '5':
        r=1.0;
        g=0.0;
        b=0.431;
        break;
    case '6':
        r=0.227;
        g=0.525;
        b=1.0;
        break;
    case '7':
        r=0.692;
        g=1.0;
        b=0.509;
        break;
    case '8':
        r=1.0;
        g=0.377;
        b=0.388;
        break;
    case '9':
        r=0;
        g=0.751;
        b=1.0;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void mudatraco(unsigned char key, int x, int y){
      switch (key){
    case '1':
        w=1;
        break;
    case '2':
        w=2;
        break;
    case '3':
        w=3;
        break;
    case '4':
        w=4;
        break;
    case '5':
        w=5;
        break;
    case '6':
        w=6;
        break;
    case '7':
        w=7;
        break;
    case '8':
        w=8;
        break;
    case '9':
        w=9;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void MouseInt (int botao, int estado, int x, int y){
    float aux = u;
    switch (botao){
        case GLUT_LEFT_BUTTON :
            if (estado == GLUT_DOWN){
                if(click==0){
                    xi = (2*x/aux)-1;
                    yi = ((2*y/aux)-1)*(-1);
                    printf("%f %f", xi, yi);
                    click++;
                }
                else if(click==1){
                    xf = (2*x/aux)-1;
                    yf = ((2*y/aux)-1)*(-1);
                    printf("%f %f", xf, yf);
                    glutPostRedisplay();
                    click=0;
                }
            }
            break ;
        default :
            break ;
    }
}

void teclado(unsigned char key, int x, int y){
    escolher(key,x,y);
    if(escolha2==0){
        mudacor(key,x,y);
    }
    else if(escolha2==1){
        mudatraco(key,x,y);
    }
}

int main(int argc, char *argv[]){

    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

// define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

   //define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);

   glutInitWindowSize(u,v); //define largura e altura da janela
   glutCreateWindow("Primeiro exercicio");
   glutDisplayFunc(desenha);//define funcao q/ desenhara o obj.
   glutMouseFunc(MouseInt);
   glutKeyboardFunc(teclado);
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}
