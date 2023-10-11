#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <strings.h>

float r=0, g=0, b=1;
float x=0,y=0,z=0;
float angulox=0, anguloy=0, anguloz=0;

void desenha(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    glColor3f(r, g, b);
    glRotatef(angulox,1,0,0);
    glRotatef(anguloy,0,1,0);
    glRotatef(anguloz,0,0,1);
    glutWireTeapot(0.2);
    glTranslatef(0.6,0,0);
    glutWireTorus(0.06, 0.12, 100, 100);
    glFlush();
}

void escolher(unsigned char key, int x, int y){
    switch (key){
        case 'X':
        case 'x':
            angulox = angulox + 1;
            break;
        case 'Y':
        case 'y':
            anguloy = anguloy + 1;
            break;
        case 'Z':
        case 'z':
            anguloz = anguloz + 1;
            break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y){
    escolher(key,x,y);
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
   glutKeyboardFunc(teclado);
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}
