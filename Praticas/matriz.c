#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Ilustra o uso da projecao ortogonal e implementa as funcoes PAN e ZOOM. Permite
// que a cena seja rotacionada nos 3 eixos de coordenadas
float win, anglex = 0.0, angley = 0.0, anglez = 0.0, panX, panY;
void init(void) {
// Define a cor do fundo da tela (AZUL)
glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
win = 10;
panX = panY = 0.0;
}

void reshape( int w, int h ) {
GLfloat mprojecao[16];
mprojecao [0]=1;
mprojecao [1]= 0;
mprojecao [2]= 0;
mprojecao [3]= 0;
mprojecao [4]= 0;
mprojecao [5]= 1;
mprojecao [6]= 0;
mprojecao [7]= 0;
//cabinet
// mprojecao [8]= sqrt(2)/4;
// mprojecao [9]= sqrt(2)/4;
//cavalier
// mprojecao [8]= sqrt(2)/2;
// mprojecao [9]= sqrt(2)/2;
//isométrica
mprojecao [8]= -1;
mprojecao [9]= -1;

mprojecao [10]= 0;
mprojecao [11]= 0;
mprojecao [12]= 0;
mprojecao [13]= 0;
mprojecao [14]= 0;
mprojecao [15]= 1;

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glLoadMatrixf(mprojecao);
glViewport(0, 0, w, h);
}
void DesenhaEixos() {
glBegin(GL_LINES);
glColor3f(1,0,0);
// eixo horizontal
glVertex2f(-win,0);
glVertex2f(+win,0);
// eixo vertical
glColor3f(1,1,0);
glVertex2f(0,-win);
glVertex2f(0, +win);
glEnd();
}
void Desenha() {
glColor3f(0.2, 0.3, 0.7);
glutWireCube(0.25);
}
void display( void ) {
glClear(GL_COLOR_BUFFER_BIT);
/* glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-win, +win, -win, +win,-win, win);*/
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glLineWidth(3);
glColor3f(1,0,0);
DesenhaEixos();
glPushMatrix();
glRotatef(anglex, 1.0, 0.0, 0.0);
glRotatef(angley, 0.0, 1.0, 0.0);
glRotatef(anglez, 0.0, 0.0, 1.0);
Desenha();
glPopMatrix();
glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y ) {
switch ( key )
{
case 27:

exit ( 0 );
break;
case 'x':
anglex+=5;
break;
case 'X':
anglex-=5;
break;
case 'y':
angley+=5;
break;
case 'Y':
angley-=5;
break;
case 'z':
anglez+=5;
break;
case 'Z':
anglez-=5;
break;
}
glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y ) {
switch ( a_keys )
{
case GLUT_KEY_UP:
glutFullScreen ( );
break;
case GLUT_KEY_DOWN:
glutPositionWindow (50,50);
glutReshapeWindow ( 650, 500 );
break;
}
}

int main ( int argc, char** argv ) {
glutInit ( &argc, argv );
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB );
glutInitWindowPosition (50,50);
glutInitWindowSize ( 650, 500);
glutCreateWindow ( "Transformacoes Geometricas, Zoom e pan" );
init ();
glutDisplayFunc ( display );
glutReshapeFunc ( reshape );
glutKeyboardFunc ( keyboard );
glutSpecialFunc ( arrow_keys );
glutMainLoop ( );

return 0;
}
