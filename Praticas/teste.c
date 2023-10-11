#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float passo = 0.0, inc = 0.02;

void desenha (){
    glClearColor(0.53, 0.61, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0.68, 0.8);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5+passo, 0.0);
    glVertex2f(0.0+passo, 0.0);
    glColor3f(1, 0, 0.33);
    glVertex2f(-0.25+passo, 0.25);
    glEnd();
    if (passo>1.01 || passo<-0.49)
    inc = -inc;
    passo = passo + inc;
    glFlush();
}

void Timer(int extra) {
glutPostRedisplay();
glutTimerFunc(30,Timer,0);
}

void keyboard (unsigned char key, int x, int y)
{
switch (key)
{
case 's' :
case 'S' :
glShadeModel(GL_SMOOTH) ;
break ;
case 'f' :
case 'F' :
glShadeModel(GL_FLAT) ;
break ;
default :
break ;
}
glutPostRedisplay();
}

void SpecialKeys (int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_LEFT :
glShadeModel(GL_SMOOTH) ;
break ;
case GLUT_KEY_RIGHT :
glShadeModel(GL_FLAT) ;
break ;
default :
break ;
}
glutPostRedisplay() ;
}

void MouseInt (int botao, int estado, int x, int y)
{
switch (botao)
{
case GLUT_LEFT_BUTTON :
if (estado == GLUT_DOWN)
glShadeModel(GL_SMOOTH) ;
break ;
case GLUT_RIGHT_BUTTON :
if (estado == GLUT_DOWN)
glShadeModel(GL_FLAT) ;
break ;
default :
break ;
}
glutPostRedisplay();
}

int main(int argc, char *argv[] ){
    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

// define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

//define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);

   glutInitWindowSize(400,300); //define largura e altura da janela

   glutCreateWindow("Primeiro programa usando OpenGL");

   glutDisplayFunc(desenha);//define funcao q/ desenhara o obj.

   glutTimerFunc(0,Timer,0);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialKeys);
   glutMouseFunc(MouseInt);

   glutMainLoop (); // Mostra tudo e espera

   return 0;
 }