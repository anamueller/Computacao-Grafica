// Ilustra o uso da projecao ortogonal e implementa as funcoes PAN e ZOOM. Permite
// que a cena seja rotacionada nos 3 eixos de coordenadas

#include <stdio.h>
#include <GL/glut.h>

float win, anglex = 0.0, angley = 0.0, anglez = 0.0, panX, panY;

void init(void) {
	// Define a cor do fundo da tela (AZUL)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    win = 10;
    panX = panY = 0.0;
}


void reshape( int w, int h ) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
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
    glBegin(GL_TRIANGLE_FAN);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(0.0,3.0,0.0);

       glColor3f(0.0,1.0,0.0);
       glVertex3f(-4.0,-3.0,0.0);

       glColor3f(0.0,0.0,1.0);
       glVertex3f(4.0,-3.0,0.0);

       glColor3f(1.0,0.0,1.0);
       glVertex3f(0.0,-3.0,-4.0);

       glColor3f(1.0,1.0,0.0);
       glVertex3f(-4.0,-3.0,0.0);
	glEnd();
}

void display( void ) {
     glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-win+panX, +win+panX, -win+panY, +win+panY,-win, win);
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
        case '-':
                win = win * 1.1;
                break;
        case '+':
                win = win * 0.9;
                break;
        case 'p':
                panX = panX + 1;
                break;
        case 'P':
                panX = panX - 1;
                break;
        case 's':
                panY = panY + 1;
                break;
        case 'S':
                panY = panY - 1;
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


int  main ( int argc, char** argv ) {
    glutInit  ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowPosition (50,50);
    glutInitWindowSize  ( 650, 500);
    glutCreateWindow    ( "Transformacoes Geometricas, Zoom e pan" );
    init ();
    glutDisplayFunc ( display );
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    glutMainLoop ( );

    return 0;
}