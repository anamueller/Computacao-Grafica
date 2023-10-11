#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

int n;
float r=0, g=0, b=1;
float xi=-0.5, yi=0.5; 

void draw_fractal(float angulo, float dist, int interations ){
    double rad = 0.0174533 * angulo; //radianos
    float xf = xi + dist*cos(rad);
    float yf = yi + dist*sin(rad);
    if(interations==0){
        //desenha base do fractal, que no caso é um triangulo
        //distancia entre os pontos para desenhar o trianglo equilatéro 
        glVertex2f(xi,yi);
        glVertex2f(xf,yf);
        xi=xf;
        yi=yf;
    }
    else{
        interations--;
        //dividir cada segmento em 3 parte iguais, no meio desenhar o triangulo _/\_
        //muda o angulo da linha para fazer as 4 linhas novas
        draw_fractal(angulo, dist, interations);
        angulo+=60;
        draw_fractal(angulo, dist, interations);
        angulo-=120;
        draw_fractal(angulo, dist, interations);
        angulo+=60;
        draw_fractal(angulo, dist, interations);
    }
}

void desenha(){
    glColor3f(r, g, b);
    float distancia = 1 / pow(3, n);
    glBegin(GL_LINES);
        draw_fractal(0.0, distancia, n); //lado 1 do triangulo, usando circulo trigonometrico
        draw_fractal(-120.0, distancia, n); //lado 2 do triangulo
        draw_fractal(120.0, distancia, n); //lado 3 do triangulo
    glEnd();
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
   printf("Digite o número de iterações desejada, o limite de iterações é 13, demora alguns segundos para rodar\n");
   scanf("%d", &n);
   while(n>13){
    printf("ERRO, digite um número válido\n");
    scanf("%d", &n);
   }
   if(n<=13){
        glutDisplayFunc(desenha);//define funcao q desenhara o obj.
   }
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}