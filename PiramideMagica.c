// OpenGL Utility Toolkit
#include <GLUT/glut.h>
#include <stdio.h>

#define VELOCIDADE 10

int fullscreen=0, treme=-1;
int xfactor=0, yfactor=0, zcamera=0;

// Controla a interação com o teclado
void Keyboard (unsigned char key, int x, int y);

// Desenha os triangulos na tela
void Piramide();

// Inicializações de OpenGL que devem ser executadas antes da exibição do desenho
void Inicializa();

// Função callback chamada para fazer o desenho
void Desenha();

// Programa principal
int main(int argc, char** argv){
    
    // Inicia GLUT e processa argumentos passados por linha de comandos
    glutInit(&argc, argv);
    glutInitWindowSize     (600, 600);
    glutInitWindowPosition (300, 150);
    
    // Avisa a GLUT que tipo de modo de exibição deve ser usado quando a janela é criada
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Cria uma janela GLUT que permite a execução de comandos OpenGL
    glutCreateWindow("Olá Mundo!");
    
    // Define a função responsável por redesenhar a janela OpenGL sempre que necessário
    glutDisplayFunc(Desenha);
    
    // Função responsável pela interação com o teclado é a Keyboard().
    glutKeyboardFunc(Keyboard);
    
    // Inicializações de OpenGL executadas antes da exibição do desenho
    Inicializa();
    
    // Inicia o processamento de eventos de GLUT. O controle do programa
    // passa a GLUT, que inicia o gerenciamento dos eventos
    glutMainLoop();
    
    return 0;
}

void Keyboard (unsigned char key, int x, int y){
    if (treme==-1)
        treme=1;
    else
        treme=-1;
    glutReshapeWindow(600+treme, 600);
    glutPositionWindow(300, 150);
    switch (key)
    {
        case 'd':
            xfactor += VELOCIDADE;
            break;
        case 'a':
            xfactor -= VELOCIDADE;
            break;
        case 'w':
            yfactor += VELOCIDADE;
            break;
        case 's':
            yfactor -= VELOCIDADE;
            break;
        case 27:
            exit(0);
            break;
        case 'f':
            if (fullscreen == 0)
            {
                glutFullScreen();
                fullscreen = 1;
            }
            else
            {
                glutReshapeWindow(600, 600);
                glutPositionWindow(300, 150);
                fullscreen = 0;
            }
            break;
        default:
            printf ("   Special key %c == %d\n", key, key);
    }
}

void Piramide(){
    
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(-2, -2, 2);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(2, -2, 2);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(0, -2, -2);
    glEnd();
    glColor3f(1.0, 0.0, 0.0);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(0, -2, -2);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    
}

void Inicializa(){
    
    
    // Define a janela de visualização
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Define o sistema de coordenadas
    glOrtho(-8.0, 8.0, -8.0, 8.0, -8.0, 8.0);
    
    // Define a cor de fundo da janela
    glClearColor
    (0.0, 0.0, 0.0, 1.0);
}

void Desenha(){
    // Local da camera
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    
    printf("Valor x: %d", xfactor);
    
    // Limpa a janela de visualização com a cor
    // de fundo especificada
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    //            Rotação
    glRotatef(yfactor, -1, -1, 1);
    
    //            Rotação
    glRotatef(xfactor, 0, 1, 0);
    
    // Desenha um triângulo
    Piramide();
    glLoadIdentity();
    
    
    // Executa os comandos OpenGL para renderização
    glFlush();
}
