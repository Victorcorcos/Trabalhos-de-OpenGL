/*
 *
 * Desenvolvido inteiramente por
 * Victor Cordeiro Costa
 * contato: victorcorcos@gmail.com
 * https://www.linkedin.com/in/victor-costa-0bba7197/
 *
 */


// OpenGL Utility Toolkit
#include <GLUT/glut.h>
#include <stdio.h>

#define VELOCIDADE 5   // Natural: 5.

int fullscreen=0, treme=-1, zcamera=0;

// Valor da Rotacao do objeto inteiro
float fator_rotac_total=0;

// Valor da Rotacao das Minipiramides
float fator_rotac_frente_A=0, fator_rotac_esquerda_A=0, fator_rotac_direita_A=0, fator_rotac_cima_A=0;

// Valor da Rotacao das Bases das Minipiramides
float fator_rotac_frente_B=0, fator_rotac_esquerda_B=0, fator_rotac_direita_B=0, fator_rotac_cima_B=0;

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


// Vertices vistos de cima:
//
//            B
//            E
//          H E J
//          F A G
//        C   I   D
//

// Vertices do Tetraedro maior
GLfloat vertA[3] = {  0.0, 0.0,                1.632993161855452 };  // Centro (Frente)
GLfloat vertB[3] = {  0.0, 1.154700538379251,  0.0  };               // Cima
GLfloat vertC[3] = { -1.0, -0.577350269189626, 0.0  };               // Esquerda
GLfloat vertD[3] = {  1.0, -0.577350269189626, 0.0  };               // Cima

// Vertices dos Tetraedros internos (pontos de seccao do Tetraedro maior)
GLfloat vertE[3] = {  0,     0.577, 0.816  };
GLfloat vertF[3] = {  -0.5, -0.289, 0.816  };
GLfloat vertG[3] = {  0.5,  -0.289, 0.816  };
GLfloat vertH[3] = {  -0.5,  0.288, 0      };
GLfloat vertI[3] = {  0,    -0.578, 0      };
GLfloat vertJ[3] = {  0.5,   0.288, 0      };

// Cores das faces
GLfloat corCimaEsquerda[3] = { 1.0f, 0.0f, 0.0f };   // Vermelho
GLfloat corCimaDireita[3]  = { 0.0f, 0.0f, 1.0f };   // Azul
GLfloat corBaixo[3]        = { 0.0f, 1.0f, 0.0f };   // Verde
GLfloat corTras[3]         = { 0.0f, 0.0f, 0.0f };   // Preto

// Atualizar tela
void ReshapeTeste();

// Piramide base3. Desenha os elementos na tela
void Tetraedro();
void MiniPiramideTopo();
void BasePiramideTopo();
void MiniPiramideEsquerda();
void BasePiramideEsquerda();
void MiniPiramideDireita();
void BasePiramideDireita();
void MiniPiramideTras();
void BasePiramideTras();

// Mostra coordenadas (somente para testes)
void MostraCoordenadas();

// Rotacoes
void RotacaoTotal();       // OK. Rotaciona toda a piramide
void RotacaoFrente_A();    // OK. Para a Piramide da frente
void RotacaoFrente_B();    // OK. Para a Base da Piramide da frente
void RotacaoEsquerda_A();  // OK. Para a Piramide da lateral esquerda
void RotacaoEsquerda_B();  // OK. Para a Base da Piramide da lateral esquerda
void RotacaoDireita_A();   // OK. Para a Piramide da lateral direita
void RotacaoDireita_B();   // OK. Para a Base da Piramide da lateral direita
void RotacaoCima_A();      // OK. Para a Piramide de cima
void RotacaoCima_B();      // OK. Para a Base da Piramide de cima

// Teste de Rotacoes
void TesteRotacaoFrente();
void TesteRotacaoEsquerda();
void TesteRotacaoDireita();
void TesteRotacaoCima();

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
            fator_rotac_frente_A += VELOCIDADE;
            break;
        case '2':
            fator_rotac_frente_A -= VELOCIDADE;
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
            fator_rotac_cima_A += VELOCIDADE;
            break;
        case '8':
            fator_rotac_cima_A -= VELOCIDADE;
            break;
        case 'q':
            fator_rotac_frente_B += VELOCIDADE;
            break;
        case 'w':
            fator_rotac_frente_B -= VELOCIDADE;
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
            fator_rotac_cima_B += VELOCIDADE;
            break;
        case 'i':
            fator_rotac_cima_B -= VELOCIDADE;
            break;
        case 32: // Barra de espaco
            fator_rotac_total += VELOCIDADE+5;
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
        case 27:
            exit(0);
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

void Tetraedro(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertA);
    glVertex3fv(vertB);
    glVertex3fv(vertC);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertA);
    glVertex3fv(vertC);
    glVertex3fv(vertD);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertA);
    glVertex3fv(vertD);
    glVertex3fv(vertB);
    
    glColor3fv(corTras);
    glVertex3fv(vertC);
    glVertex3fv(vertD);
    glVertex3fv(vertB);
    
    glEnd();
    
}

void MiniPiramideTopo(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertA);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertA);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertA);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    
    glColor3fv(corTras); // (base)
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    
    glEnd();
}

void BasePiramideTopo(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);  // Preto (topo)
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    
    glColor3fv(corTras);  // Preto (base)
    glVertex3fv(vertB);
    glVertex3fv(vertD);
    glVertex3fv(vertC);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertC);
    glVertex3fv(vertH);
    glVertex3fv(vertB);
    glVertex3fv(vertE);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corBaixo);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    glVertex3fv(vertD);
    glVertex3fv(vertI);
    glVertex3fv(vertC);
    glVertex3fv(vertF);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaDireita);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertB);
    glVertex3fv(vertJ);
    glVertex3fv(vertD);
    glVertex3fv(vertG);
    glEnd();
}

void MiniPiramideEsquerda(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertF);
    glVertex3fv(vertH);
    glVertex3fv(vertC);
    
    glColor3fv(corTras);
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    glVertex3fv(vertH);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertF);
    glVertex3fv(vertC);
    glVertex3fv(vertI);
    
    glColor3fv(corTras);  // Preto    (base)
    glVertex3fv(vertH);
    glVertex3fv(vertC);
    glVertex3fv(vertI);
    
    glEnd();
}

void BasePiramideEsquerda(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);  // Preto (topo)
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    glVertex3fv(vertH);
    
    glColor3fv(corCimaDireita);  // Verde (base)
    glVertex3fv(vertA);
    glVertex3fv(vertD);
    glVertex3fv(vertB);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertF);
    glVertex3fv(vertA);
    glVertex3fv(vertE);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    glVertex3fv(vertF);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corBaixo);
    glVertex3fv(vertA);
    glVertex3fv(vertG);
    glVertex3fv(vertD);
    glVertex3fv(vertI);
    glVertex3fv(vertF);
    glVertex3fv(vertA);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corTras);
    glVertex3fv(vertH);
    glVertex3fv(vertB);
    glVertex3fv(vertJ);
    glVertex3fv(vertD);
    glVertex3fv(vertI);
    glVertex3fv(vertH);
    glEnd();
}

void MiniPiramideDireita(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);  // Base
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    glVertex3fv(vertI);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertG);
    glVertex3fv(vertI);
    glVertex3fv(vertD);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertG);
    glVertex3fv(vertD);
    glVertex3fv(vertJ);
    
    glColor3fv(corTras);
    glVertex3fv(vertJ);
    glVertex3fv(vertI);
    glVertex3fv(vertD);
    
    glEnd();
}

void BasePiramideDireita(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);  // Base
    glVertex3fv(vertJ);
    glVertex3fv(vertG);
    glVertex3fv(vertI);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertB);
    glVertex3fv(vertA);
    glVertex3fv(vertC);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corTras);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    glVertex3fv(vertC);
    glVertex3fv(vertI);
    glVertex3fv(vertJ);
    glVertex3fv(vertB);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corBaixo);
    glVertex3fv(vertA);
    glVertex3fv(vertF);
    glVertex3fv(vertC);
    glVertex3fv(vertI);
    glVertex3fv(vertG);
    glVertex3fv(vertA);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaDireita);
    glVertex3fv(vertA);
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    glVertex3fv(vertB);
    glVertex3fv(vertE);
    glVertex3fv(vertA);
    glEnd();
}

void MiniPiramideTras(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertE);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    
    glColor3fv(corTras);   // Base
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    glVertex3fv(vertJ);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertE);
    glVertex3fv(vertJ);
    glVertex3fv(vertB);
    
    glColor3fv(corTras);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    glVertex3fv(vertJ);
    
    glEnd();
}

void BasePiramideTras(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);  // Base
    glVertex3fv(vertH);
    glVertex3fv(vertE);
    glVertex3fv(vertJ);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertC);
    glVertex3fv(vertA);
    glVertex3fv(vertD);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertA);
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    glVertex3fv(vertC);
    glVertex3fv(vertF);
    glVertex3fv(vertA);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corCimaDireita);
    glVertex3fv(vertA);
    glVertex3fv(vertE);
    glVertex3fv(vertJ);
    glVertex3fv(vertD);
    glVertex3fv(vertG);
    glVertex3fv(vertA);
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3fv(corTras);
    glVertex3fv(vertH);
    glVertex3fv(vertC);
    glVertex3fv(vertI);
    glVertex3fv(vertD);
    glVertex3fv(vertJ);
    glVertex3fv(vertH);
    glEnd();
}

void MostraCoordenadas(){
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);   // Preto
    glVertex3f(-4, 0, 0);
    glVertex3f(4, 0,  0);
    glVertex3f(0, -4, 0);
    glVertex3f(0, 4,  0);
    glVertex3f(0, 0, -4);
    glVertex3f(0, 0,  4);
    glEnd();
}

void RotacaoTotal(){
    
    //            Rotação
    glRotatef(-fator_rotac_total, 0, 1, 0);
    
}

void RotacaoFrente_A(){
    
    //            Rotação
    glRotatef(-fator_rotac_frente_A, 0, 0, 1);
    
}

void RotacaoFrente_B(){
    
    //            Rotação
    glRotatef(-fator_rotac_frente_B, 0, 0, 1);
}

void RotacaoEsquerda_A(){
    
    // Re-Rotacao inicial
    glRotatef(49.3, 1, -1, 1);
    
    // Re-Rotacao
    glRotatef(-74.0, 0, 1, 0);
    
    // Re-Translacao
    glTranslatef(0.355, 0.11, 0);
    
    // Finalmente rotacionando pelo Z
    glRotatef(fator_rotac_esquerda_A, 0, 0, 1);
    
    // Translacao para rotacionar pelo Z
    glTranslatef(-0.355, -0.11, 0);
    
    // Rotacao para rotacionar pelo Z
    glRotatef(74.0, 0, 1, 0);
    
    // Rotacao inicial para posteriormente rotacionar pelo Z
    glRotatef(-49.3, 1, -1, 1);
    
}

void RotacaoEsquerda_B(){
    
    // Re-Rotacao inicial
    glRotatef(49.3, 1, -1, 1);
    
    // Re-Rotacao
    glRotatef(-74.0, 0, 1, 0);
    
    // Re-Translacao
    glTranslatef(0.355, 0.11, 0);
    
    // Finalmente rotacionando pelo Z
    glRotatef(fator_rotac_esquerda_B, 0, 0, 1);
    
    // Translacao para rotacionar pelo Z
    glTranslatef(-0.355, -0.11, 0);
    
    // Rotacao para rotacionar pelo Z
    glRotatef(74.0, 0, 1, 0);
    
    // Rotacao inicial para posteriormente rotacionar pelo Z
    glRotatef(-49.3, 1, -1, 1);
    
}

void RotacaoDireita_A(){
    
    // Re-Rotacao inicial
    glRotatef(-49.3, -1, -1, 1);
    
    // Re-Rotacao
    glRotatef(74.0, 0, 1, 0);
    
    // Re-Translacao
    glTranslatef(-0.355, 0.11, 0);
    
    // Finalmente rotacionando pelo Z
    glRotatef(fator_rotac_direita_A, 0, 0, 1);
    
    // Translacao para rotacionar pelo Z
    glTranslatef(0.355, -0.11, 0);
    
    // Rotacao para rotacionar pelo Z
    glRotatef(-74.0, 0, 1, 0);
    
    // Rotacao inicial para posteriormente rotacionar pelo Z
    glRotatef(49.3, -1, -1, 1);
    
}

void RotacaoDireita_B(){
    
    // Re-Rotacao inicial
    glRotatef(-49.3, -1, -1, 1);
    
    // Re-Rotacao
    glRotatef(74.0, 0, 1, 0);
    
    // Re-Translacao
    glTranslatef(-0.355, 0.11, 0);
    
    // Finalmente rotacionando pelo Z
    glRotatef(fator_rotac_direita_B, 0, 0, 1);
    
    // Translacao para rotacionar pelo Z
    glTranslatef(0.355, -0.11, 0);
    
    // Rotacao para rotacionar pelo Z
    glRotatef(-74.0, 0, 1, 0);
    
    // Rotacao inicial para posteriormente rotacionar pelo Z
    glRotatef(49.3, -1, -1, 1);
    
}

void RotacaoCima_A(){
    
    //  Re-Rotacao
    glRotatef(-19.6, 1, 0, 0);
    
    //  Re-Translacao
    glTranslatef(0, 0, 0.4);
    
    //  Finalmente rotacionando ao redor do Y
    glRotatef(fator_rotac_cima_A, 0, 1, 0);
    
    //  Translacao para poder rotacionar ao redor do Y
    glTranslatef(0, 0, -0.4);
    
    //  Rotacao para poder rotacionar ao redor do Y
    glRotatef(19.6, 1, 0, 0);
    
}


void RotacaoCima_B(){
    
    //  Re-Rotacao
    glRotatef(-19.6, 1, 0, 0);
    
    //  Re-Translacao
    glTranslatef(0, 0, 0.4);
    
    //  Finalmente rotacionando ao redor do Y
    glRotatef(fator_rotac_cima_B, 0, 1, 0);
    
    //  Translacao para poder rotacionar ao redor do Y
    glTranslatef(0, 0, -0.4);
    
    //  Rotacao para poder rotacionar ao redor do Y
    glRotatef(19.6, 1, 0, 0);
    
}

void TesteRotacaoFrente(){
    
    // Rotaciona
    RotacaoTotal();
    RotacaoFrente_B();
    
    // Desenha base da piramide do topo
    BasePiramideTopo();
    glLoadIdentity();
    
    // Rotaciona
    RotacaoTotal();
    RotacaoFrente_A();
    
    // Desenha piramide do topo
    MiniPiramideTopo();
    glLoadIdentity();
}

void TesteRotacaoCima(){
    
    // Rotaciona
    RotacaoTotal();
    RotacaoCima_B();
    
    // Desenha base da piramide traseira
    BasePiramideTras();
    glLoadIdentity();
    
    // Rotaciona
    RotacaoTotal();
    RotacaoCima_A();
    
    // Desenha piramide traseira
    MiniPiramideTras();
    glLoadIdentity();
}

void TesteRotacaoEsquerda(){
    
    // Rotaciona
    RotacaoTotal();
    RotacaoEsquerda_B();
    
    // Desenha base da piramide esquerda
    BasePiramideEsquerda();
    glLoadIdentity();
    
    
    // Rotaciona
    RotacaoTotal();
    RotacaoEsquerda_A();
    
    // Desenha piramide esquerda
    MiniPiramideEsquerda();
    glLoadIdentity();
}

void TesteRotacaoDireita(){
    
    // Rotaciona
    RotacaoTotal();
    RotacaoDireita_B();
    
    // Desenha base da piramide direita
    BasePiramideDireita();
    glLoadIdentity();
    
    
    // Rotaciona
    RotacaoTotal();
    RotacaoDireita_A();
    
    // Desenha piramide direita
    MiniPiramideDireita();
    glLoadIdentity();
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
    
    // Limpa a janela de visualização com a cor
    // de fundo especificada
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    
    TesteRotacaoFrente();
    
    
    // Mostra as Coordenadas
    MostraCoordenadas();
    
    // Executa os comandos OpenGL para renderização
    glFlush();
}











