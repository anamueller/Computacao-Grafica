#include <GL/glut.h>
#include <stdlib.h>

int angx = 0, angy = 0, angz = 0, shoulder1 = 0, elbow1 = 0, mao1=0;


void desenha_braco(int shoulder, int elbow, int opcao){

//todo o braco
glPushMatrix();
    glTranslatef(0.1,0.0,0.0);
    glRotatef(shoulder1,0.0,0.0,1.0);
    glTranslatef(-0.1,0.0,0.0);
  //parte de cima do braco
  glPushMatrix();
       glScalef (1.0, 0.5, 1.0);
       glutWireCube (0.2);
  glPopMatrix();

    //antebraco + mao
    glPushMatrix();
        //antebraco
        glTranslatef(-0.2,0.0,0.0);
        glTranslatef(0.1,0.0,0.0);
        glRotatef(elbow1,0.0,0.0,1.0);
        glTranslatef(-0.1,0.0,0.0);
        glPushMatrix();
            glScalef (1.0, 0.5, 1.0);
            glutWireCube (0.2);
        glPopMatrix();

        //mão
        glTranslatef(-0.14,0.0,0.0);
        glPushMatrix();
                glTranslatef(0.035,0.0,0.0);
                glRotatef(mao1,0.0,0.0,1.0);
                glTranslatef(-0.035,0.0,0.0);
                glutWireCube (0.07);
        glPopMatrix();
    glPopMatrix();

glPopMatrix();
}

void display(void){
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix();
   /* roda toda a cena */
     glRotatef(angx,1.0,0.0,0.0);
     glRotatef(angy,0.0,1.0,0.0);
     glRotatef(angz,0.0,0.0,1.0);

     // desenha o corpo
     glPushMatrix();
         glScalef(0.6,1.5,0.5);
         glutWireCube(0.4);
     glPopMatrix();

    /* desenha o braco esquerdo */
    glPushMatrix();
       //translada para acertar o braco no corpo
       glTranslatef(-0.22,0.0,0.0);
       desenha_braco(shoulder1,elbow1,1);
    glPopMatrix();


/* desenha outro braco */
     glPushMatrix();

     glPopMatrix();
  glPopMatrix();

  glutSwapBuffers();
}


void keyboard (unsigned char key, int x, int y){
  switch (key) {
/* controla rota惚es da cena */
   case 'x':
           //angx -= 5.0;
           angx = (angx-5)%360;
       break;

   case 'X':
           angx = (angx+5)%360;
       break;


   case 'y':
            angy = (angy-5)%360;
        break;

   case 'Y':
            angy = (angy+5)%360;        
       break;



   case 'z':
            angz = (angz-5)%360;
       break;


   case 'Z':
            angz = (angz+5)%360;
       break;

/* controla rota惚es do primeiro braco */
   case 's':
          // controle da rota豪o positiva do bra腔
          if(shoulder1==-80){
                break;
          }
          else{
                shoulder1 = (shoulder1 - 5);
          }
          break;
          if(shoulder1==80){
                break;
          }
          else{
                shoulder1 = (shoulder1 + 5);
          }
          break;

   case 'S':
          // controle da rota豪o negativa do bra腔
          if(shoulder1==80){
                break;
          }
          else{
                shoulder1 = (shoulder1 + 5);
          }
          break;

   case 'e':
          // adiciona o controle da rota豪o positiva da parte inferior do bra腔
          if(elbow1==-110){
                break;
          }
          else{
                elbow1 = (elbow1 - 5);
          }
          break;

   case 'E':
          // adiciona o controle da rota豪o negativa da parte inferior do bra腔
          if(elbow1==0){
                break;
          }
          else{
                elbow1 = (elbow1 + 5);
          }
          break;

    case 'm':
        if(mao1==-60){
                break;
          }
          else{
                mao1 = (mao1 - 5);
          }
          break;
    
    case 'M':
        if(mao1==60){
                break;
          }
          else{
                mao1 = (mao1 + 5);
          }
          break;
/* sai do programa */
   case 27:
            exit(0);
          break;

  }
   glutPostRedisplay();
}

void reshape(int w, int h){
    if (w >= h)
        glViewport(0, 0, (GLsizei)h, (GLsizei)h) ;
    else
        glViewport(0, 0, (GLsizei)w, (GLsizei)w) ;
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (700, 500);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Criando bracos de robo");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
