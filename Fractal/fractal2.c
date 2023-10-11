#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <strings.h>
#include <math.h>

int iterations;
float r=0, g=0, b=1;
float xi=-0.01, xf=-0.32, yi=0.42, yf=-0.08;

void draw_fractal(float angulo, float dist, int interations ){
    float rad = 0.0174533 * angulo; //radianos
    float xf = xi + dist*cos(rad);
    float yf = yi + dist*sin(rad);
    if(iterations==0){
        //desenha base do fractal, que no caso é um triangulo
        //distancia entre os pontos para desenhar o trianglo equilatéro 
        glBegin(GL_TRIANGLES);                                          // início triângulo
                glVertex2f(xi,yi);                          // Topo
                glVertex2f(xf,yf);                          // Esquerda embaixo
                glVertex2f(xf+dist,yf);                          // Direita embaixo
        glEnd();                                                        // fim triângulo
    }
    else{
        iterations--;
        //dividir cada segmento em 3 parte iguais, no meio desenhar o triangulo _/\_
        //muda o angulo da linha para fazer as 4 linhas novas
        draw_fractal(angulo, dist, interations);
        angulo=angulo+60;
        draw_fractal(angulo, dist, interations);
        angulo=angulo-120;
        draw_fractal(angulo, dist, interations);
        angulo=angulo+60;
        draw_fractal(angulo, dist, interations);
    }
}

void desenha(){
    glColor3f(r, g, b);
    float distancia = sqrt((pow((xi-xf), 2)+pow((yi-yf), 2)));
    draw_fractal();
    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

    // define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

   //define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);
   glutInitWindowSize(600,600); //define largura e altura da janela
   glutCreateWindow("Fractal");
   printf("Digite o número de iterações desejada, o limite de iterações é x\n");
   scanf("%d", &iterations);
   glutDisplayFunc(desenha);//define funcao q desenhara o obj.
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}