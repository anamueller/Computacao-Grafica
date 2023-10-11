/* TeaPot3D.c (Isabel Harb Manssour)
 Exemplo de visualizacao de objetos 3D
 Baseado nos exemplos do livro OpenGL SuperBible, 2nd Edition
 Richard S. Wright Jr.
*/
#include <stdio.h>
#include <GL/glut.h>

GLfloat angle=45.0;
GLfloat fAspect;


void RenderScene(void)	{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireTeapot(50.0f);
	glutSwapBuffers();
}


void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


void Viewing(void)	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle,fAspect,0.1,500);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
           gluLookAt(0,80,200, 0,0,0, 0,1,0);
}


void ChangeSize(GLsizei w, GLsizei h)	{
	/* Para previnir uma divisao por zero */
	if ( h == 0 )
		h = 1;
            glViewport(0, 0, w, h);

	/* Calcula a correcao de aspecto */
	fAspect = (GLfloat)w/(GLfloat)h;
	Viewing();
}


void HandleMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {    /* Zoom-in */
			if (angle >= 10)
				angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {    /* Zoom-out */

			if (angle <= 130)
				angle += 5;
		}
	Viewing();
	glutPostRedisplay();
}


int  main ( int argc, char** argv ){
            glutInit  ( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400,350);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(RenderScene);
            glutReshapeFunc(ChangeSize);
	glutMouseFunc(HandleMouse);
	SetupRC();
	glutMainLoop();
}

