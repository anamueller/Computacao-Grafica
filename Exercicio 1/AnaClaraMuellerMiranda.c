#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <strings.h>

float r=1, g=0.64, b=0;
int w=5;
float xd, yd;
int bolas_restantes=0;
int maxscale;
int minscale;

typedef struct{
    float eixo_x;
    float eixo_y;
}coordenadas;

typedef struct {
    //cabeca, olho, corpo, pata 1-2-3-4, circulo de colisao
    float raios[8];
    //coordenada dos circulos, cabeca, olho, corpo, pata 1-2-3-4,
    coordenadas i_circulos[7]; 
    //linhas do gato
    coordenadas orelhas[8];
    coordenadas bigodes[6];
    coordenadas rabo[4];
    coordenadas circulo_de_colisao[1];
}gato_coord;

gato_coord gatinho;

//passa os valores para o gato
void atribui(){
    //raios
    gatinho.raios[0]=0.196695;
    gatinho.raios[1]=0.020276; 
    gatinho.raios[2]=0.235372;
    gatinho.raios[3]=0.038006; 
    gatinho.raios[4]=0.044473; 
    gatinho.raios[5]=0.041767; 
    gatinho.raios[6]=0.026034;
    gatinho.raios[7]=0.471463;

    //circulos coordenadas iniciais
    gatinho.i_circulos[0].eixo_x=-0.473333;
    gatinho.i_circulos[1].eixo_x=-0.61;
    gatinho.i_circulos[2].eixo_x=-0.06;
    gatinho.i_circulos[3].eixo_x=-0.243333;
    gatinho.i_circulos[4].eixo_x=-0.156667;
    gatinho.i_circulos[5].eixo_x=0.07;
    gatinho.i_circulos[6].eixo_x=0.123333;

    gatinho.i_circulos[0].eixo_y=0.233333;
    gatinho.i_circulos[1].eixo_y=0.283333;
    gatinho.i_circulos[2].eixo_y=0.09;
    gatinho.i_circulos[3].eixo_y=-0.08;
    gatinho.i_circulos[4].eixo_y=-0.126667;
    gatinho.i_circulos[5].eixo_y=-0.116667;
    gatinho.i_circulos[6].eixo_y=-0.063333;

    //orelhas
    gatinho.orelhas[0].eixo_x=-0.603333;
    gatinho.orelhas[1].eixo_x=-0.536667;
    gatinho.orelhas[2].eixo_x=-0.536667;
    gatinho.orelhas[3].eixo_x=-0.47;
    gatinho.orelhas[4].eixo_x=-0.476667;
    gatinho.orelhas[5].eixo_x=-0.396667;
    gatinho.orelhas[6].eixo_x=-0.396667;
    gatinho.orelhas[7].eixo_x=-0.36;

    gatinho.orelhas[0].eixo_y=0.37;
    gatinho.orelhas[1].eixo_y=0.52;
    gatinho.orelhas[2].eixo_y=0.52;
    gatinho.orelhas[3].eixo_y=0.43;
    gatinho.orelhas[4].eixo_y=0.433333;
    gatinho.orelhas[5].eixo_y=0.51;
    gatinho.orelhas[6].eixo_y=0.51;
    gatinho.orelhas[7].eixo_y=0.403333;

    //bigodes
    gatinho.bigodes[0].eixo_x=-0.66;
    gatinho.bigodes[1].eixo_x=-0.576667;
    gatinho.bigodes[2].eixo_x=-0.66;
    gatinho.bigodes[3].eixo_x=-0.576667;
    gatinho.bigodes[4].eixo_x=-0.66;
    gatinho.bigodes[5].eixo_x=-0.576667;

    gatinho.bigodes[0].eixo_y=0.17;
    gatinho.bigodes[1].eixo_y=0.226667;
    gatinho.bigodes[2].eixo_y=0.17;
    gatinho.bigodes[3].eixo_y=0.17;
    gatinho.bigodes[4].eixo_y=0.17;
    gatinho.bigodes[5].eixo_y=0.126667;

    //rabo
    gatinho.rabo[0].eixo_x=0.176667;
    gatinho.rabo[1].eixo_x=0.35;
    gatinho.rabo[2].eixo_x=0.35;
    gatinho.rabo[3].eixo_x=0.366667;

    gatinho.rabo[0].eixo_y=0.163333;
    gatinho.rabo[1].eixo_y=0.266667;
    gatinho.rabo[2].eixo_y=0.266667;
    gatinho.rabo[3].eixo_y=0.44;

    //circulo de colisa
    gatinho.circulo_de_colisao[0].eixo_x=-0.213333;
    gatinho.circulo_de_colisao[0].eixo_y=0.173333;
}

typedef struct {
	float x_bola, y_bola;
    float raio;
} bola;

typedef struct celula{
    bola dado; //conteúdo da fila
    struct celula *prox; //ponteiro da fila que aponta pro próximo item da fila
} celula;

typedef struct {
    celula *frente; //apontador que aponta para frente da fila
    celula *tras; //apontador que aponta para frente da fila
    int tam;
} fila;

fila *aux; //ponteiro auxiliar para usar como variavel global

void inicia_fila(fila *f){
    f->frente = NULL; 
    f->tras = NULL;
    aux = f;
}

void fila_insere(bola dado, fila *f){
    celula *ptr = (celula*)malloc(sizeof(celula)); //alocando memória e criando o ponteiro tipo celula
    if (ptr == NULL){ //se o ponteiro não contém nada, não tem nada para adicionar
        printf("ERRO");
    }
    else{
        ptr->dado = dado; //atribuindo o valor do dado ao ponteiro criado
        ptr->prox = NULL; //o endereço do prox passa a ser o fim da fila 
        if(f->frente == NULL){ //quando a fila esta vazia
            f->frente = ptr;
            f->tam=1;
        }
        else{
            f->tras->prox = ptr;
        }
        f->tras = ptr;
    }
    f->tam++;
    bolas_restantes++;
}

fila_retira(fila *f){
    celula *ptr = f->frente;
    if(f->tras == NULL){
        printf("ERRO");
    }
    else {
        f->frente = ptr->prox;
        ptr->prox = NULL;
        free(ptr);
        if(f->frente == NULL){
            f->tras = NULL;
        }
    }
}

int colisao(bola c){
    float distance_x = c.x_bola-(gatinho.circulo_de_colisao[0].eixo_x);
    float distance_y = c.y_bola-gatinho.circulo_de_colisao[0].eixo_y;
    float radii_sum  = c.raio + gatinho.raios[7];
    if(distance_x * distance_x + distance_y * distance_y <= radii_sum * radii_sum){
        return 1; //chegou na bolinha
    }
    return 0;
}

//funcao que desenha todas as bolinhas da lista
void bolas(){
    celula *ptr = (celula*)malloc(sizeof(celula));
    ptr = aux->frente;
    if(aux->frente==NULL){
        return;
    }
    else{
       while (ptr!=NULL){    
            glBegin(GL_LINE_LOOP);
                for (int i = 0; i <= 300; i++){
                    float angulo = (2*3.142*i)/300;
                    glVertex2f(ptr->dado.x_bola+(ptr->dado.raio *cos(angulo)), ptr->dado.y_bola + (ptr->dado.raio*sin(angulo)));
                }
            glEnd();
            ptr = ptr->prox;
        } 
    }
    ptr = aux->frente;
    if(bolas_restantes!=0){
        if(translada(ptr->dado)==1){
            ptr = ptr->prox;
        }
    }
}

void desenha(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(r, g, b);
    gato();
    bolas();
    glFlush();
}

//escala o gato
void escala(int choice){
    switch (choice){
    case 1:
        for(int i=0;i<7;i++){
            gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x * 0.99;
            gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y * 0.99;
        }
        for(int i=0;i<8;i++){
            gatinho.raios[i] = gatinho.raios[i] * 0.99;
            gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x*0.99;
            gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y*0.99;
        }
        for(int i=0;i<6;i++){
            gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x*0.99;
            gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y*0.99;
        }
        for(int i=0;i<4;i++){
            gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x*0.99;
            gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y*0.99;
        }
        for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x*0.99;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y*0.99;
        }
        //escala diminui
        break;
    case 2:
        for(int i=0;i<7;i++){
            gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x *1.01;
            gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y *1.01;
        }
        for(int i=0;i<8;i++){
            gatinho.raios[i] = gatinho.raios[i] * 1.01;
            gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x*1.01;
            gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y*1.01;
        }
        for(int i=0;i<6;i++){
            gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x*1.01;
            gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y*1.01;
        }
        for(int i=0;i<4;i++){
            gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x*1.01;
            gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y*1.01;
        }
        for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x*1.01;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y*1.01;
        }
        //escala aumenta
        break;
    default:
        break;
    }
}

int translada(bola c){
    if(colisao(c)==1){
        bolas_restantes--;
        fila_retira(aux);
        return 1;
    }
    if(c.x_bola>gatinho.bigodes[0].eixo_x && c.y_bola>gatinho.bigodes[0].eixo_y){
        for(int i=0;i<7;i++){
            gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x + 0.0001;
            gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y + 0.0001;
        }
        for(int i=0;i<8;i++){
            gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x+0.0001;
            gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y+0.0001;
        }
        for(int i=0;i<6;i++){
            gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x+0.0001;
            gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y+0.0001;
        }
        for(int i=0;i<4;i++){
            gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x+0.0001;
            gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y+0.0001;
        }
        for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x+0.0001;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y+0.0001;
        }   
    }
    if(c.x_bola<gatinho.bigodes[0].eixo_x && c.y_bola>gatinho.bigodes[0].eixo_y){
        for(int i=0;i<7;i++){
            gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x - 0.0001;
            gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y + 0.0001;
        }
        for(int i=0;i<8;i++){
            gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x-0.0001;
            gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y+0.0001;
        }
        for(int i=0;i<6;i++){
            gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x-0.0001;
            gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y+0.0001;
        }
        for(int i=0;i<4;i++){
            gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x-0.0001;
            gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y+0.0001;
        }
        for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x-0.0001;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y+0.0001;
        }   
    }
    if(c.x_bola<gatinho.bigodes[0].eixo_x && c.y_bola<gatinho.bigodes[0].eixo_y){
        for(int i=0;i<7;i++){
            gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x-0.0001;
            gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y-0.0001;
        }
        for(int i=0;i<8;i++){
            gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x-0.0001;
            gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y-0.0001;
        }
        for(int i=0;i<6;i++){
            gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x-0.0001;
            gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y-0.0001;
        }
        for(int i=0;i<4;i++){
            gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x-0.0001;
            gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y-0.0001;
        } 
        for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x-0.0001;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y-0.0001;
        }   
    }
    if(c.x_bola>gatinho.bigodes[0].eixo_x && c.y_bola<gatinho.bigodes[0].eixo_y){
            for(int i=0;i<7;i++){
                gatinho.i_circulos[i].eixo_x = gatinho.i_circulos[i].eixo_x + 0.0001;
                gatinho.i_circulos[i].eixo_y = gatinho.i_circulos[i].eixo_y - 0.0001;
            }
            for(int i=0;i<8;i++){
                gatinho.orelhas[i].eixo_x = gatinho.orelhas[i].eixo_x+0.0001;
                gatinho.orelhas[i].eixo_y = gatinho.orelhas[i].eixo_y-0.0001;
            }
            for(int i=0;i<6;i++){
                gatinho.bigodes[i].eixo_x = gatinho.bigodes[i].eixo_x+0.0001;
                gatinho.bigodes[i].eixo_y = gatinho.bigodes[i].eixo_y-0.0001;
            }
            for(int i=0;i<4;i++){
                gatinho.rabo[i].eixo_x = gatinho.rabo[i].eixo_x+0.0001;
                gatinho.rabo[i].eixo_y = gatinho.rabo[i].eixo_y-0.0001;
            } 
            for(int i=0;i<1;i++){
            gatinho.circulo_de_colisao[0].eixo_x = gatinho.circulo_de_colisao[0].eixo_x+0.0001;
            gatinho.circulo_de_colisao[0].eixo_y = gatinho.circulo_de_colisao[0].eixo_y-0.0001;
        }   
        }
    //usar xd e yd
}

//escolha de escalar o gato 
void tamanho(unsigned char key, int x, int y){
      switch (key){
    case '+':
        if(maxscale<50){
            escala(2);
            maxscale++;
        }
        break;
    case '-':
    if(minscale<90){
        escala(1);
        minscale++;
    }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

//desenha o gato
void gato(){
    //cabeca 0 nos vetores
    glLineWidth(w);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[0].eixo_x+(gatinho.raios[0]*cos(angulo)), gatinho.i_circulos[0].eixo_y + (gatinho.raios[0]*sin(angulo)));
        }
    glEnd();
    //olho 1 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[1].eixo_x+(gatinho.raios[1]*cos(angulo)), gatinho.i_circulos[1].eixo_y + (gatinho.raios[1]*sin(angulo)));
        }
    glEnd();
    //orelhas
    glBegin(GL_LINES);
        glVertex2f(gatinho.orelhas[0].eixo_x, gatinho.orelhas[0].eixo_y); //0 nos vetores
        glVertex2f(gatinho.orelhas[1].eixo_x, gatinho.orelhas[1].eixo_y); //1 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.orelhas[2].eixo_x, gatinho.orelhas[2].eixo_y); //2 nos vetores
        glVertex2f(gatinho.orelhas[3].eixo_x, gatinho.orelhas[3].eixo_y); //3 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.orelhas[4].eixo_x, gatinho.orelhas[4].eixo_y); //4 nos vetores
        glVertex2f(gatinho.orelhas[5].eixo_x, gatinho.orelhas[5].eixo_y); //5 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.orelhas[6].eixo_x, gatinho.orelhas[6].eixo_y); //6 nos vetores
        glVertex2f(gatinho.orelhas[7].eixo_x, gatinho.orelhas[7].eixo_y); //7 nos vetores
    glEnd();
    //bigode
    glBegin(GL_LINES);
        glVertex2f(gatinho.bigodes[0].eixo_x, gatinho.bigodes[0].eixo_y); //0 nos vetores
        glVertex2f(gatinho.bigodes[1].eixo_x, gatinho.bigodes[1].eixo_y); //1 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.bigodes[2].eixo_x, gatinho.bigodes[2].eixo_y); //2 nos vetores 
        glVertex2f(gatinho.bigodes[3].eixo_x, gatinho.bigodes[3].eixo_y); //3 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.bigodes[4].eixo_x, gatinho.bigodes[4].eixo_y); //4 nos vetores
        glVertex2f(gatinho.bigodes[5].eixo_x, gatinho.bigodes[5].eixo_y); //5 nos vetores
    glEnd();
    //corpo 2 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[2].eixo_x+(gatinho.raios[2]*cos(angulo)), gatinho.i_circulos[2].eixo_y + (gatinho.raios[2]*sin(angulo)));
        }
    glEnd();
    //pata1 3 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[3].eixo_x+(gatinho.raios[3]*cos(angulo)), gatinho.i_circulos[3].eixo_y + (gatinho.raios[3]*sin(angulo)));
        }
    glEnd();
    //pata2 4 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[4].eixo_x+(gatinho.raios[4]*cos(angulo)), gatinho.i_circulos[4].eixo_y + (gatinho.raios[4]*sin(angulo)));
        }
    glEnd();
    //pata3 5 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[5].eixo_x+(gatinho.raios[5]*cos(angulo)), gatinho.i_circulos[5].eixo_y + (gatinho.raios[5]*sin(angulo)));
        }
    glEnd();
    //pata4 6 nos vetores
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 300; i++){
            float angulo = (2*3.142*i)/300;
            glVertex2f(gatinho.i_circulos[6].eixo_x+(gatinho.raios[6]*cos(angulo)), gatinho.i_circulos[6].eixo_y + (gatinho.raios[6]*sin(angulo)));
        }
    glEnd();
    //rabo
    glBegin(GL_LINES);
        glVertex2f(gatinho.rabo[0].eixo_x, gatinho.rabo[0].eixo_y); //0 nos vetores
        glVertex2f(gatinho.rabo[1].eixo_x, gatinho.rabo[1].eixo_y); //1 nos vetores
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(gatinho.rabo[2].eixo_x, gatinho.rabo[2].eixo_y); //2 nos vetores
        glVertex2f(gatinho.rabo[3].eixo_x, gatinho.rabo[3].eixo_y); //3 nos vetores
    glEnd();
    glutPostRedisplay();
}

bola click;

void MouseInt (int botao, int estado, int x, int y){
    switch (botao){
        case GLUT_LEFT_BUTTON :
            if (estado == GLUT_DOWN){
                //inves de mudar a variavel global adiciona na lista
                //insere na lista um novo no
                click.x_bola = (2*x/600.0)-1;
                click.y_bola = ((2*y/600.0)-1)*(-1);
                click.raio = 0.03;
                fila_insere(click, aux);
                translada(click);
            }
            break ;
        default:
            break ;
        glutPostRedisplay();
    }
}

//funcao que manipula o gato, translada, escala e rotaciona
//funcao da logica, se o gato passou da tela, se nao, se chegou na bolinha limpa a lista e atualiza qual ele 
//deve ir atras

int main(int argc, char *argv[]){
    fila *bolinhas = (fila*)malloc(sizeof(fila));
    inicia_fila(bolinhas);
    glutInit(&argc,argv); //inicializa a glut com parametros de entrada do programa.

    // define o modo do display
   glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

   //define a posicao do canto superior esquerdo da janela
   glutInitWindowPosition(50,100);
   glutInitWindowSize(600,600); //define largura e altura da janela
   atribui(); //passando os valores pra desenhar o gato
   glutCreateWindow("Gato");
   glutDisplayFunc(desenha);//define funcao q desenhara o obj.
   glutMouseFunc(MouseInt);
   glutKeyboardFunc(tamanho);
   glutMainLoop (); // Mostra tudo e espera

    return 0;
}
