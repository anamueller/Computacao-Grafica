#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float angx=0, angy=0, angz=0;

GLfloat ctrlpoints[4][4][3] = {
    {
        {-1.5, -1.5,  4.0}, {-0.5, -1.5,  2.0}, {0.5, -1.5, -1.0},{1.5, -1.5,  2.0}}, 
    {
        {-1.5, -0.5,  1.0}, {-0.5, -0.5,  3.0},{0.5, -0.5,  0.0}, {1.5, -0.5, -1.0}}, 
    {
        {-1.5,  0.5,  4.0},{-0.5,  0.5,  0.0}, {0.5,  0.5,  3.0}, {1.5,  0.5,  4.0}},
    {
        {-1.5,  1.5, -2.0}, {-0.5,  1.5, -2.0}, {0.5,  1.5,  0.0},{1.5,  1.5, -1.0}}
};
void init(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
}

void escolher(unsigned char key, int x, int y){
    switch (key){
        case 'x':
           angx = (angx-0.5);
       break;
        case 'X':
            angx = (angx+0.5);
        break;
        case 'y':
            angy = (angy-0.5);
        break;
        case 'Y':
            angy = (angy+0.5);        
        break;
        case 'z':
            angz = (angz-0.5);
        break;
        case 'Z':
            angz = (angz+0.5);
        break;
    }
    glutPostRedisplay();
}

void Display(void){
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(angx,1,0,0);
    glRotatef(angy,0,1,0);
    glRotatef(angz,0,0,1);
    glPushMatrix ();
         //glRotatef(85.0, 1.0, 1.0, 1.0);
         glMapGrid2f(8,0,1,8,0,1);
         glEvalMesh2(GL_FILL,0,8,0,8);

         /*for (j = 0; j <= 8; j++) {
             glBegin(GL_LINE_STRIP);
                 for (i = 0; i <= 30; i++)
                    glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
             glEnd();
             glBegin(GL_LINE_STRIP);
                for (i = 0; i <= 30; i++)
                    glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
             glEnd();
          }*/
    glPopMatrix ();
    glPointSize(5);
    glColor3f(1,0,0.6);
    glBegin(GL_POINTS);
        for(int i=0;i<16;i++){
            glVertex3f(ctrlpoints[0][i][0],ctrlpoints[0][i][1],ctrlpoints[0][i][2]);
        }
        for(int i=0;i<16;i++){
            glVertex3f(ctrlpoints[i][0][0],ctrlpoints[i][0][1],ctrlpoints[i][0][2]);
        }
    glEnd();
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
   glutKeyboardFunc(escolher);
   glutMainLoop();
   return 0;
}