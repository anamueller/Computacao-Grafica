#include <stdio.h>
#include <GL/glut.h>

GLfloat ctrlpoints[6][3] = {
    {0.0,0.0,0,0},
    {-4.0,0.0,0.0},
    {-4.0,8.0,0.0},
    {4.0,8.0,0.0}, 
    {4.0,0.0,0.0}, 
    {0.0,0.0,0,0}};

void init(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
    glTranslated(0,0,-2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 6,&ctrlpoints[0][0]); 
    glEnable(GL_MAP1_VERTEX_3);
}

void Display(void){
   int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glColor3f(1,1,1);
    glBegin(GL_LINE_STRIP);
         for (i = 0; i <= 30; i++)
              glEvalCoord1f((GLfloat) i/30.0);
    glEnd();
    glPointSize(5);
    glColor3f(1,0,0.6);
    glBegin(GL_POINTS);
        for(int i=0;i<6;i++){
            glVertex2f(ctrlpoints[i][0],ctrlpoints[i][1]);
        }
    glEnd();
    glFlush();
    glFlush();
}

int main(int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (700, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Spline Curve");
   glutDisplayFunc(Display);
   init();
   glutMainLoop();
   return 0;
}
