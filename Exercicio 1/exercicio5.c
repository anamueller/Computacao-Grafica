#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <strings.h>
#include <math.h>

float xi=0, yi=0, xf=0, yf=0.9;
float r=0, g=0, b=1;
int click=0;
int escolha;

void desenha(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r, g, b);
    if(escolha==0){
        glLineWidth(5);
        glBegin(GL_LINES);
            glVertex2f(xi,yi);
            glVertex2f(xf,yf);
    }
    else if(escolha==1){
        glBegin(GL_LINE_LOOP);
        float radius = sqrt((pow((xi-xf), 2)+pow((yi-yf), 2)));
            for (int i = 0; i <= 300; i++){
                float angulo = (2*3.142*i)/300;
                glVertex2f(xi+(radius*cos(angulo)), yi + (radius*sin(angulo)));
            }
    }
    glEnd();
    glFlush();
}

void escolher(unsigned char key, int x, int y){
    switch (key){
        case 'r':
        case 'R':
            escolha=0;
        case 'c':
        case 'C':
            xi=0, yi=0, xf=0, yf=0;
            escolha=1;
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

void MouseInt (int botao, int estado, int x, int y){
    switch (botao){
        case GLUT_LEFT_BUTTON :
            if (estado == GLUT_DOWN){
                if(click==0){
                    xi = (2*x/600.0)-1;
                    yi = ((2*y/600.0)-1)*(-1);
                    click++;
                }
                else if(click==1){
                    xf = (2*x/600.0)-1;
                    yf = ((2*y/600.0)-1)*(-1);
                    glutPostRedisplay();
                    click=0;
                }
            }
            break ;
        default :
            break ;
    }
}

int main(int argc, char *argv[]){

    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

// define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

   //define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);

   glutInitWindowSize(600,600); //define largura e altura da janela

   glutCreateWindow("Primeiro exercicio");
   glutDisplayFunc(desenha);//define funcao q/ desenhara o obj.
   glutMouseFunc(MouseInt);
   glutKeyboardFunc(mudacor);
   glutKeyboardFunc(escolher);
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}
