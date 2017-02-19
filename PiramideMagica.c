/*
 * Desenvolvido inteiramente por
 * Victor Cordeiro Costa
 * contato: victorcorcos@gmail.com
 */


// OpenGL Utility Toolkit
#include <GLUT/glut.h>
#include <stdio.h>

#define VELOCIDADE 10

int fullscreen=0, treme=-1, zcamera=0;

// Valor da Rotacao das Minipiramides
int fator_rotac_topo_A=0, fator_rotac_esquerda_A=0, fator_rotac_direita_A=0, fator_rotac_tras_A=0;

// Valor da Rotacao das Bases das Minipiramides
int fator_rotac_topo_B=0, fator_rotac_esquerda_B=0, fator_rotac_direita_B=0, fator_rotac_tras_B=0;

// Controla a interação com o teclado
void Keyboard (unsigned char key, int x, int y);

/*
 void Reshape(GLint largura, GLint altura)
 {
 glViewport(0, 0, (GLsizei)largura, (GLsizei)altura); // Set our viewport to the size of our window
 glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
 glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
 gluPerspective(60, (GLfloat)largura / (GLfloat)altura, -10.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
 glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
 }
 */

// Piramide base3. Desenha os elementos na tela
void Piramide();
void MiniPiramideTopo();
void BasePiramideTopo();
void MiniPiramideEsquerda();
void BasePiramideEsquerda();
void MiniPiramideDireita();
void BasePiramideDireita();
void MiniPiramideTras();
void BasePiramideTras();

// Piramide base4. (somente para testes)
void Piramide4Base();

// Mostra coordenadas (somente para testes)
void MostraCoordenadas();

// Rotacoes
void RotacaoTopo_A();      // Para a Piramide do topo
void RotacaoTopo_B();      // Para a Base da Piramide do topo
void RotacaoEsquerda_A();  // Para a Piramide da lateral esquerda
void RotacaoEsquerda_B();  // Para a Base da Piramide da lateral esquerda
void RotacaoDireita_A();   // Para a Piramide da lateral direita
void RotacaoDireita_B();   // Para a Base da Piramide da lateral direita
void RotacaoTras_A();      // Para a Piramide de tras
void RotacaoTras_B();      // Para a Base da Piramide da tras

// Atualizar tela
void ReshapeTeste();

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    // Cria uma janela GLUT que permite a execução de comandos OpenGL
    glutCreateWindow("Pyramix");
    
    // Define a função responsável por redesenhar a janela OpenGL sempre que necessário
    glutDisplayFunc(Desenha);
    
    // Serve para atualizar a tela sempre que possivel
    //   glutReshapeFunc (Reshape);
    
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
    
    ReshapeTeste();
    
    switch (key)
    {
        case '1':
            fator_rotac_topo_A += VELOCIDADE;
            break;
        case '2':
            fator_rotac_topo_A -= VELOCIDADE;
            break;
        case '3':
            fator_rotac_esquerda_A += VELOCIDADE;
            break;
        case '4':
            fator_rotac_esquerda_A -= VELOCIDADE;
            break;
        case '5':
            fator_rotac_direita_A += VELOCIDADE;
            break;
        case '6':
            fator_rotac_direita_A -= VELOCIDADE;
            break;
        case '7':
            fator_rotac_tras_A += VELOCIDADE;
            break;
        case '8':
            fator_rotac_tras_A -= VELOCIDADE;
            break;
        case 'q':
            fator_rotac_topo_B += VELOCIDADE;
            break;
        case 'w':
            fator_rotac_topo_B -= VELOCIDADE;
            break;
        case 'e':
            fator_rotac_esquerda_B += VELOCIDADE;
            break;
        case 'r':
            fator_rotac_esquerda_B -= VELOCIDADE;
            break;
        case 't':
            fator_rotac_direita_B += VELOCIDADE;
            break;
        case 'y':
            fator_rotac_direita_B -= VELOCIDADE;
            break;
        case 'u':
            fator_rotac_tras_B += VELOCIDADE;
            break;
        case 'i':
            fator_rotac_tras_B -= VELOCIDADE;
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

void ReshapeTeste(){
    if (treme==-1)
        treme=1;
    else
        treme=-1;
    glutReshapeWindow(600+treme, 600);
    glutPositionWindow(300, 150);
}

void Piramide4Base(){
    
    glBegin(GL_TRIANGLES);
    // Frente
    glColor3f(1.0f, 0.0f, 0.0f);     // Vermelho
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    
    // Direita
    glColor3f(0.0f, 1.0f, 0.0f);     // Verde
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    
    // Atras
    glColor3f(0.0f, 0.0f, 1.0f);     // Azul
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    
    // Esquerda
    glColor3f(1.0f, 0.0f, 1.0f);     // Rosa
    glVertex3f( 0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glEnd();
    
    // Base
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);     // Preto (Base)
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, -1.0f);
    glEnd();
    
    glutSwapBuffers();
    
}

void Piramide(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 0.0, 0.0);  // Vermelho  (frente)
    glVertex3f(0, 2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(-2, -2, 2);
    
    glColor3f(0.0, 1.0, 0.0);  // Verde     (direita)
    glVertex3f(0, 2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(2, -2, 2);
    
    glColor3f(0.0, 0.0, 1.0);  // Azul      (esquerda)
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(0, -2, -2);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto     (base)
    glVertex3f(0, -2, -2);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    
    glEnd();
    
}

void MiniPiramideTopo(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(0, 2, 0);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    
    glColor3f(0.0, 1.0, 0.0);  // Verde    (direita)
    glVertex3f(0, 2, 0);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, -1);
    
    glColor3f(0.0, 0.0, 1.0);  // Azul     (esquerda)
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, -1);
    glVertex3f(-1, 0, 1);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto    (base)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    
    glEnd();
}

void BasePiramideTopo(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (topo)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (base)
    glVertex3f(0, -2, -2);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(-1, 0, 1);
    glVertex3f(1, 0, 1);
    glVertex3f(2, -2, 2);
    glVertex3f(0, -2, 2);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);  // Verde (direita)
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, -1);
    glVertex3f(0, -2, -2);
    glVertex3f(1, -2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);  // Azul (esquerda)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, 0, 1);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, -2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(0, 0, -1);
    glEnd();
}

void MiniPiramideEsquerda(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(-1, 0, 1);
    glVertex3f(-2, -2, 2);
    glVertex3f(0, -2, 2);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto    (direita)
    glVertex3f(-1, 0, 1);
    glVertex3f(0, -2, 2);
    glVertex3f(-1, -2, 0);
    
    glColor3f(0.0, 0.0, 1.0);  // Azul     (esquerda)
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, -2, 0);
    glVertex3f(-2, -2, 2);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto    (base)
    glVertex3f(-2, -2, 2);
    glVertex3f(0, -2, 2);
    glVertex3f(-1, -2, 0);
    
    glEnd();
}

void BasePiramideEsquerda(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (topo)
    glVertex3f(-1, 0, 1);
    glVertex3f(-1, -2, 0);
    glVertex3f(0, -2, 2);
    
    glColor3f(0.0, 1.0, 0.0);  // Verde (base)
    glVertex3f(0, 2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(2, -2, 2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(-1, 0, 1);
    glVertex3f(0, -2, 2);
    glVertex3f(2, -2, 2);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(-1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);  // Azul (tras)
    glVertex3f(-1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, -1);
    glVertex3f(0, -2, -2);
    glVertex3f(-1, -2, 0);
    glVertex3f(-1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);  // Preto (baixo)
    glVertex3f(-1, -2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(1, -2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(0, -2, 2);
    glVertex3f(-1, -2, 0);
    glEnd();
}

void MiniPiramideDireita(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(1, 0, 1);
    glVertex3f(0, -2, 2);
    glVertex3f(2, -2, 2);
    
    glColor3f(0.0, 1.0, 0.0);  // Verde    (direita)
    glVertex3f(1, 0, 1);
    glVertex3f(2, -2, 2);
    glVertex3f(1, -2, 0);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto     (esquerda)
    glVertex3f(1, 0, 1);
    glVertex3f(1, -2, 0);
    glVertex3f(0, -2, 2);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto    (base)
    glVertex3f(0, -2, 2);
    glVertex3f(2, -2, 2);
    glVertex3f(1, -2, 0);
    
    glEnd();
}

void BasePiramideDireita(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (topo)
    glVertex3f(1, 0, 1);
    glVertex3f(0, -2, 2);
    glVertex3f(1, -2, 0);
    
    glColor3f(0.0, 0.0, 1.0);  // Azul (base)
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(0, -2, -2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (frente)
    glVertex3f(1, 0, 1);
    glVertex3f(0, -2, 2);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);  // Verde (tras)
    glVertex3f(1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, -1);
    glVertex3f(0, -2, -2);
    glVertex3f(1, -2, 0);
    glVertex3f(1, 0, 1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);  // Preto (baixo)
    glVertex3f(1, -2, 0);
    glVertex3f(0, -2, 2);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, -2, 0);
    glVertex3f(0, -2, -2);
    glVertex3f(1, -2, 0);
    glEnd();
}

void MiniPiramideTras(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (frente)
    glVertex3f(0, 0, -1);
    glVertex3f(1, -2, 0);
    glVertex3f(-1, -2, 0);
    
    glColor3f(0.0, 1.0, 0.0);  // Verde    (direita)
    glVertex3f(0, 0, -1);
    glVertex3f(0, -2, -2);
    glVertex3f(1, -2, 0);
    
    glColor3f(0.0, 0.0, 1.0);  // Azul     (esquerda)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, -2, 0);
    glVertex3f(0, -2, -2);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto    (base)
    glVertex3f(0, -2, -2);
    glVertex3f(-1, -2, 0);
    glVertex3f(1, -2, 0);
    
    glEnd();
}

void BasePiramideTras(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3f(0.0, 0.0, 0.0);  // Preto (topo)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, -2, 0);
    glVertex3f(1, -2, 0);
    
    glColor3f(1.0, 0.0, 0.0);  // Vermelho (base)
    glVertex3f(0, 2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(2, -2, 2);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);  // Verde (direita)
    glVertex3f(0, 0, -1);
    glVertex3f(1, -2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, -1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 1.0);  // Azul (esquerda)
    glVertex3f(0, 0, -1);
    glVertex3f(-1, -2, 0);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, 0, 1);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 0, -1);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);  // Preto (baixo)
    glVertex3f(-1, -2, 0);
    glVertex3f(1, -2, 0);
    glVertex3f(2, -2, 2);
    glVertex3f(0, -2, 2);
    glVertex3f(-2, -2, 2);
    glVertex3f(-1, -2, 0);
    glEnd();
}

void MostraCoordenadas(){
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);   // Preto
    glVertex3f(-4, 0, 0);
    glVertex3f(4, 0, 0);
    glVertex3f(0, -4, 0);
    glVertex3f(0, 4, 0);
    glVertex3f(0, 0, -4);
    glVertex3f(0, 0, 4);
    glEnd();
}

void RotacaoTopo_A(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_topo_A, 0, 1, 0);
    
    // Ajeita para rotacionar ao redor do Y
    glTranslatef(0, 0, -2/3);
}

void RotacaoTopo_B(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_topo_B, 0, 1, 0);
    
    // Ajeita para rotacionar ao redor do Y
    glTranslatef(0, 0, -2/3);
}

void RotacaoEsquerda_A(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_esquerda_A, 1, 1, -1);
    
    // Ajeita para rotacionar ??
    glTranslatef(0, 0, -2/3);
}

void RotacaoEsquerda_B(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_esquerda_B, 1, 1, -1);
    
    // Ajeita para rotacionar ??
    glTranslatef(0, 0, -2/3);
}

void RotacaoDireita_A(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_direita_A, -1, 1, -1);
    
    // Ajeita para rotacionar ??
    glTranslatef(0, 0, -2/3);
}

void RotacaoDireita_B(){
    // Ajeita para o lugar anterior
    glTranslatef(0, 0, 2/3);
    
    //            Rotação
    glRotatef(-fator_rotac_direita_B, -1, 1, -1);
    
    // Ajeita para rotacionar ??
    glTranslatef(0, 0, -2/3);
}

void RotacaoTras_A(){
    // Translacao de volta
    glTranslatef(0, -2, -2);
    
    //  Rotacao de volta
    glRotatef(-116.5, 1, 0, 0);
    
    //  Rotacao ao redor do eixo Y
    glRotatef(-fator_rotac_tras_A, 0, 1, 0);
    
    
    //  Rotacao para a parte de tras ficar em pe
    glRotatef(116.5, 1, 0, 0);
    
    // Translacao para o centro
    glTranslatef(0, 2, 2);
}


void RotacaoTras_B(){
    // Translacao de volta
    glTranslatef(0, -2, -2);
    
    //  Rotacao de volta
    glRotatef(-116.5, 1, 0, 0);
    
    //  Rotacao ao redor do eixo Y
    glRotatef(-fator_rotac_tras_B, 0, 1, 0);
    
    
    //  Rotacao para a parte de tras ficar em pe
    glRotatef(116.5, 1, 0, 0);
    
    // Translacao para o centro
    glTranslatef(0, 2, 2);
}

void Inicializa(){
    
    
    // Define a janela de visualização
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Define o sistema de coordenadas
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
    
    // Define a cor de fundo da janela
    glClearColor
    (1.0, 1.0, 1.0, 1.0);
    
    
}

void Desenha(){
    
    // Local da camera
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    
    printf("Valor x: %d", fator_rotac_topo_A);
    
    // Limpa a janela de visualização com a cor
    // de fundo especificada
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    // Rotaciona
    RotacaoTopo_A();
    RotacaoTras_B();
    
    // Desenha
    BasePiramideTras();
    glLoadIdentity();
    
    
    // Rotaciona
    RotacaoTopo_A();
    RotacaoTras_A();
    
    
    // Desenha
    MiniPiramideTras();
    glLoadIdentity();
    
    // Mostra Coordenadas
    MostraCoordenadas();
    glLoadIdentity();
    
    
    
    // Executa os comandos OpenGL para renderização
    glFlush();
}
