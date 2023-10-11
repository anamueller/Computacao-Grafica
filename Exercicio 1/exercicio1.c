#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float xfinal=0.0, yfinal=0.0;

void desenha(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.68, 0.8);
    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex2f(xfinal,yfinal);
    glEnd();
    glFlush();
}

void MouseInt (int botao, int estado, int x, int y){

switch (botao){
    case GLUT_LEFT_BUTTON :
        if (estado == GLUT_DOWN){
            xfinal = (2*x/300.0)-1;
            yfinal = ((2*y/300.0)-1)*(-1);
            glutPostRedisplay();
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

   glutInitWindowSize(300,300); //define largura e altura da janela

   glutCreateWindow("Primeiro exercicio");

   glutDisplayFunc(desenha);//define funcao q/ desenhara o obj.
   glutMouseFunc(MouseInt);
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}
