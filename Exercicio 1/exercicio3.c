#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float x1=0.0, y1=0.0, x2=0.0, y2=0.9;
float r=0, g=0, b=1.0;
int click=0;

void desenha(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r, g, b);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2d(x2,y2);
    glEnd();
    glFlush();
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
                    x1 = (2*x/600.0)-1;
                    y1 = ((2*y/600.0)-1)*(-1);
                    click++;
                }
                else if(click==1){
                    x2 = (2*x/600.0)-1;
                    y2 = ((2*y/600.0)-1)*(-1);
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
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}