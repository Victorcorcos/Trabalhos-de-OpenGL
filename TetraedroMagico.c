/*
 *
 * Desenvolvido inteiramente por
 * Victor Cordeiro Costa
 * contato: victorcorcos@gmail.com
 * https://www.linkedin.com/in/victor-costa-0bba7197/
 *
 */


/*          Comandos do jogo
 *
 *  Barra
 *   de     =>   Rotaciona o Pyraminx inteiro.
 *  Espaço
 *
 *    W     =>   Rotaciona as minipiramides.
 *  A S D        Se a letra for maiuscula, rotaciona em outro sentido.
 *
 *    T     =>   Rotaciona as bases das minipiramides.
 *  F G H        Se a letra for maiúscula, rotaciona em outro sentido.
 *
 *   ESC    =>   Fecha o jogo
 *
 */


// OpenGL Utility Toolkit
#include <GLUT/glut.h>
#include <stdio.h>

#define VELOCIDADE 15          // Natural: 15
#define CONFIG_INICIAL 120     // Rotacoes iniciais. Possiveis escolhas: 0, 120 ou 240.

// Valor da Rotacao do objeto inteiro
float fator_rotac_total=0;

// Angulo da Rotacao das Minipiramides
int fator_rotac_frente_A=CONFIG_INICIAL, fator_rotac_cima_A=CONFIG_INICIAL, fator_rotac_direita_A=CONFIG_INICIAL, fator_rotac_esquerda_A=CONFIG_INICIAL;

// Angulo da Rotacao das Bases das Minipiramides
int fator_rotac_frente_B=0, fator_rotac_cima_B=0, fator_rotac_direita_B=0, fator_rotac_esquerda_B=0;

// Guarda a tecla que o usuario digitou no teclado para descobrir o caso da rotacao.
char caso=' ';

// Controla a interação com o teclado
void Keyboard (unsigned char key, int x, int y);


//    Vertices vistos de cima:
//
//               B
//             H E J
//             F A G
//           C   I   D
//

// Vertices do Tetraedro maior.
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

// Cores iniciais das faces do Tetraedro
GLfloat corCimaEsquerda[3] = { 1.0f, 0.0f, 0.0f };   // Vermelho
GLfloat corCimaDireita[3]  = { 0.0f, 0.0f, 1.0f };   // Azul
GLfloat corBaixo[3]        = { 0.0f, 1.0f, 0.0f };   // Verde
GLfloat corTras[3]         = { 1.0f, 1.0f, 0.0f };   // Amarelo
GLfloat corInterna[3]      = { 0.0f, 0.0f, 0.0f };   // Preto

// Cores de cada triangulo equilatero (Inicializados na funçao apropriada)
GLfloat corT1[3];
GLfloat corT2[3];
GLfloat corT3[3];
GLfloat corT4[3];
GLfloat corT5[3];
GLfloat corT6[3];
GLfloat corT7[3];
GLfloat corT8[3];
GLfloat corT9[3];
GLfloat corT10[3];
GLfloat corT11[3];
GLfloat corT12[3];
GLfloat corT13[3];
GLfloat corT14[3];
GLfloat corT15[3];
GLfloat corT16[3];
GLfloat corTEsq[3];
GLfloat corTDir[3];
GLfloat corTCima[3];
GLfloat corTFrente[3];

// Funções de desenho de cada triangulo equilatero externo
void T1();
void T2();
void T3();
void T4();
void T5();
void T6();
void T7();
void T8();
void T9();
void T10();
void T11();
void T12();
void T13();
void T14();
void T15();
void T16();

// Funções de desenho de cada triangulo equilatero interno
void TEsq();
void TDir();
void TCima();
void TFrente();

// Funções de desenho dos Tetraedros, formados pelos triangulos equilateros.
void Pyraminx();
void PyraFrente();
void PyraEsq();
void PyraDir();
void PyraCima();
void RestoCentro();  // A figura formada no centro é um Octaedro

// Rotações
void RotacaoTotal();       // Rotaciona toda a piramide
void RotacaoFrente_A();    // Para a Piramide da frente
void RotacaoFrente_B();    // Para a Base da Piramide da frente
void RotacaoEsquerda_A();  // Para a Piramide da lateral esquerda
void RotacaoEsquerda_B();  // Para a Base da Piramide da lateral esquerda
void RotacaoDireita_A();   // Para a Piramide da lateral direita
void RotacaoDireita_B();   // Para a Base da Piramide da lateral direita
void RotacaoCima_A();      // Para a Piramide de cima
void RotacaoCima_B();      // Para a Base da Piramide de cima

// Funções para atualizar o Pyraminx após realizar cada rotação
void AtualizaPyraminx_s();
void AtualizaPyraminx_w();
void AtualizaPyraminx_a();
void AtualizaPyraminx_d();
void AtualizaPyraminx_g();
void AtualizaPyraminx_t();
void AtualizaPyraminx_f();
void AtualizaPyraminx_h();

// Função que atualiza o Pyraminx para todas as rotações
void AtualizaPyraminx();

// Funções que determinam se partes do Pyraminx pode ser rotacionado.
// As partes só devem rotacionar se o resto está devidamente encaixado.
// 1 -> Pode rotacionar. 0 -> Não pode rotacionar.
int pode_rotacionar_s();
int pode_rotacionar_w();
int pode_rotacionar_a();
int pode_rotacionar_d();
int pode_rotacionar_g();
int pode_rotacionar_t();
int pode_rotacionar_f();
int pode_rotacionar_h();

// Mostra coordenadas
void MostraCoordenadas();

// Inicializa cores de cada triangulo que forma o Pyraminx
void InicializaCoresTriangulos();

// vetor1 = vetor2
void CopiaVetor(GLfloat* vetor1, GLfloat* vetor2);

// vetor1 = vetor2. vetor2 = vetor3. vetor3 = vetor1
void CopiaVetores(GLfloat* vetor1, GLfloat* vetor2, GLfloat* vetor3);

// Copia uma sequencia de vetores
void CopiaSequenciaVetores(GLfloat* vetor1, GLfloat* vetor2, GLfloat* vetor3, GLfloat* vetor4, GLfloat* vetor5, GLfloat* vetor6, GLfloat* vetor7, GLfloat* vetor8, GLfloat* vetor9, GLfloat* vetor10, GLfloat* vetor11, GLfloat* vetor12);

// Inicializações de OpenGL que devem ser executadas antes da exibição do desenho
void Inicializa();

// Função callback chamada para fazer o desenho
void Desenha();

// Programa principal
int main(int argc, char** argv){
    
    // Inicia GLUT e processa argumentos passados por linha de comandos
    glutInit(&argc, argv);
    
    // Avisa a GLUT que tipo de modo de exibição deve ser usado quando a janela é criada
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize     (650, 650);
    glutInitWindowPosition (300, 300);
    
    // Cria uma janela GLUT que permite a execução de comandos OpenGL
    glutCreateWindow("Pyraminx Magico");
    
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
    
    switch (key)
    {
        case 's':
            if (pode_rotacionar_s())
            {
                fator_rotac_frente_A = (fator_rotac_frente_A + VELOCIDADE) % 360;
                caso = 's';
                glutPostRedisplay();
            }
            break;
        case 'S':
            if (pode_rotacionar_s())
            {
                fator_rotac_frente_A = (360+(fator_rotac_frente_A - VELOCIDADE)) % 360;
                caso = 'S';
                glutPostRedisplay();
            }
            break;
        case 'a':
            if (pode_rotacionar_a())
            {
                fator_rotac_esquerda_A = (fator_rotac_esquerda_A + VELOCIDADE) % 360;
                caso = 'a';
                glutPostRedisplay();
            }
            break;
        case 'A':
            if (pode_rotacionar_a())
            {
                fator_rotac_esquerda_A = (360+(fator_rotac_esquerda_A - VELOCIDADE)) % 360;
                caso = 'A';
                glutPostRedisplay();
            }
            break;
        case 'd':
            if (pode_rotacionar_d())
            {
                fator_rotac_direita_A = (fator_rotac_direita_A + VELOCIDADE) % 360;
                caso = 'd';
                glutPostRedisplay();
            }
            break;
        case 'D':
            if (pode_rotacionar_d())
            {
                fator_rotac_direita_A = (360+(fator_rotac_direita_A - VELOCIDADE)) % 360;
                caso = 'D';
                glutPostRedisplay();
            }
            break;
        case 'w':
            if (pode_rotacionar_w())
            {
                fator_rotac_cima_A = (fator_rotac_cima_A + VELOCIDADE) % 360;
                caso = 'w';
                glutPostRedisplay();
            }
            break;
        case 'W':
            if (pode_rotacionar_w())
            {
                fator_rotac_cima_A = (360+(fator_rotac_cima_A - VELOCIDADE)) % 360;
                caso = 'W';
                glutPostRedisplay();
            }
            break;
        case 'g':
            if (pode_rotacionar_g())
            {
                fator_rotac_frente_B = (fator_rotac_frente_B + VELOCIDADE) % 360;
                caso = 'g';
                glutPostRedisplay();
            }
            break;
        case 'G':
            if (pode_rotacionar_g())
            {
                fator_rotac_frente_B = (360+(fator_rotac_frente_B - VELOCIDADE)) % 360;
                caso = 'G';
                glutPostRedisplay();
            }
            break;
        case 'f':
            if (pode_rotacionar_f())
            {
                fator_rotac_esquerda_B = (fator_rotac_esquerda_B + VELOCIDADE) % 360;
                caso = 'f';
                glutPostRedisplay();
            }
            break;
        case 'F':
            if (pode_rotacionar_f())
            {
                fator_rotac_esquerda_B = (360+(fator_rotac_esquerda_B - VELOCIDADE)) % 360;
                caso = 'F';
                glutPostRedisplay();
            }
            break;
        case 'h':
            if (pode_rotacionar_h())
            {
                fator_rotac_direita_B = (fator_rotac_direita_B + VELOCIDADE) % 360;
                caso = 'h';
                glutPostRedisplay();
            }
            break;
        case 'H':
            if (pode_rotacionar_h())
            {
                fator_rotac_direita_B = (360+(fator_rotac_direita_B - VELOCIDADE)) % 360;
                caso = 'H';
                glutPostRedisplay();
            }
            break;
        case 't':
            if (pode_rotacionar_t())
            {
                fator_rotac_cima_B = (fator_rotac_cima_B + VELOCIDADE) % 360;
                caso = 't';
                glutPostRedisplay();
            }
            break;
        case 'T':
            if (pode_rotacionar_t())
            {
                fator_rotac_cima_B = (360+(fator_rotac_cima_B - VELOCIDADE)) % 360;
                caso = 'T';
                glutPostRedisplay();
            }
            break;
        case 32: // Barra de espaco
            fator_rotac_total += VELOCIDADE+5;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            printf ("   Special key %c == %d\n", key, key);
    }
}

int pode_rotacionar_s(){
    if((fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_w(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_a(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_d(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_g(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240))
        return 1;
    return 0;
}

int pode_rotacionar_t(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_f(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_direita_B==0  || fator_rotac_direita_B==120  || fator_rotac_direita_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

int pode_rotacionar_h(){
    if((fator_rotac_frente_A==0   || fator_rotac_frente_A==120   || fator_rotac_frente_A==240) &&
       (fator_rotac_esquerda_A==0 || fator_rotac_esquerda_A==120 || fator_rotac_esquerda_A==240) &&
       (fator_rotac_direita_A==0  || fator_rotac_direita_A==120  || fator_rotac_direita_A==240) &&
       (fator_rotac_cima_A==0     || fator_rotac_cima_A==120     || fator_rotac_cima_A==240) &&
       (fator_rotac_esquerda_B==0 || fator_rotac_esquerda_B==120 || fator_rotac_esquerda_B==240) &&
       (fator_rotac_cima_B==0     || fator_rotac_cima_B==120     || fator_rotac_cima_B==240) &&
       (fator_rotac_frente_B==0   || fator_rotac_frente_B==120   || fator_rotac_frente_B==240 ))
        return 1;
    return 0;
}

void T1(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT1);
    glVertex3fv(vertB);
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void T2(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT2);
    glVertex3fv(vertH);
    glVertex3fv(vertF);
    glVertex3fv(vertC);
    
    glEnd();
    
}

void T3(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT3);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void T4(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT4);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T5(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT5);
    glVertex3fv(vertC);
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T6(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT6);
    glVertex3fv(vertI);
    glVertex3fv(vertG);
    glVertex3fv(vertD);
    
    glEnd();
    
}

void T7(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT7);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T8(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT8);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T9(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT9);
    glVertex3fv(vertD);
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T10(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT10);
    glVertex3fv(vertJ);
    glVertex3fv(vertE);
    glVertex3fv(vertB);
    
    glEnd();
    
}

void T11(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT11);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T12(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT12);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T13(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT13);
    glVertex3fv(vertC);
    glVertex3fv(vertH);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T14(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT14);
    glVertex3fv(vertI);
    glVertex3fv(vertJ);
    glVertex3fv(vertD);
    
    glEnd();
    
}

void T15(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT15);
    glVertex3fv(vertH);
    glVertex3fv(vertI);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T16(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corT16);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void TEsq(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTEsq);
    glVertex3fv(vertH);
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void TDir(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTDir);
    glVertex3fv(vertI);
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void TCima(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTCima);
    glVertex3fv(vertJ);
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void TFrente(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTFrente);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    
    glEnd();
    
}

void Pyraminx(){
    
    PyraFrente();
    PyraCima();
    PyraEsq();
    PyraDir();
    RestoCentro();
    
}

void PyraFrente(){
    
    T4();
    T8();
    T12();
    TFrente();
    
}

void PyraEsq(){
    
    T2();
    T5();
    T13();
    TEsq();
    
}

void PyraDir(){
    
    T6();
    T9();
    T14();
    TDir();
    
}

void PyraCima(){
    
    T1();
    T10();
    T16();
    TCima();
    
}

void RestoCentro(){
    
    T3();
    T7();
    T11();
    T15();
    
    TFrente();
    TEsq();
    TDir();
    TCima();
    
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

void CopiaVetor(GLfloat* vetor1, GLfloat* vetor2){
    
    int i=0;
    
    for(i=0; i<3; i++)
        vetor1[i] = vetor2[i];
    
}

void InicializaCoresTriangulos(){
    
    CopiaVetor(corT1, corCimaEsquerda);
    CopiaVetor(corT2, corCimaEsquerda);
    CopiaVetor(corT3, corCimaEsquerda);
    CopiaVetor(corT4, corCimaEsquerda);
    CopiaVetor(corT5, corBaixo);
    CopiaVetor(corT6, corBaixo);
    CopiaVetor(corT7, corBaixo);
    CopiaVetor(corT8, corBaixo);
    CopiaVetor(corT9, corCimaDireita);
    CopiaVetor(corT10, corCimaDireita);
    CopiaVetor(corT11, corCimaDireita);
    CopiaVetor(corT12, corCimaDireita);
    CopiaVetor(corT13, corTras);
    CopiaVetor(corT14, corTras);
    CopiaVetor(corT15, corTras);
    CopiaVetor(corT16, corTras);
    CopiaVetor(corTFrente, corInterna);
    CopiaVetor(corTCima, corInterna);
    CopiaVetor(corTEsq, corInterna);
    CopiaVetor(corTDir, corInterna);
    
}

void CopiaVetores(GLfloat* vetor1, GLfloat* vetor2, GLfloat* vetor3){
    
    GLfloat vetoraux[3];
    
    CopiaVetor(vetoraux, vetor1);
    CopiaVetor(vetor1, vetor2);
    CopiaVetor(vetor2, vetor3);
    CopiaVetor(vetor3, vetoraux);
    
}

void CopiaSequenciaVetores(GLfloat* vetor1, GLfloat* vetor2, GLfloat* vetor3, GLfloat* vetor4, GLfloat* vetor5, GLfloat* vetor6, GLfloat* vetor7, GLfloat* vetor8, GLfloat* vetor9, GLfloat* vetor10, GLfloat* vetor11, GLfloat* vetor12){
    
    GLfloat vetoraux1[3];
    GLfloat vetoraux2[3];
    GLfloat vetoraux3[3];
    
    CopiaVetor(vetoraux1, vetor1);
    CopiaVetor(vetoraux2, vetor2);
    CopiaVetor(vetoraux3, vetor3);
    
    CopiaVetor(vetor1, vetor7);
    CopiaVetor(vetor2, vetor8);
    CopiaVetor(vetor3, vetor9);
    
    CopiaVetor(vetor7, vetor4);
    CopiaVetor(vetor8, vetor5);
    CopiaVetor(vetor9, vetor6);
    
    CopiaVetor(vetor4, vetoraux1);
    CopiaVetor(vetor5, vetoraux2);
    CopiaVetor(vetor6, vetoraux3);
    
    CopiaVetores(vetor10, vetor12, vetor11);
    
}

void AtualizaPyraminx_s() {
    
    if (fator_rotac_frente_A == 120 || fator_rotac_frente_A == 240){
        CopiaVetores(corT8, corT12, corT4);
        if (fator_rotac_frente_A == 240)
            CopiaVetores(corT8, corT12, corT4);
        fator_rotac_frente_A = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_w() {
    
    if (fator_rotac_cima_A == 120 || fator_rotac_cima_A == 240){
        CopiaVetores(corT1, corT16, corT10);
        if (fator_rotac_cima_A == 240)
            CopiaVetores(corT1, corT16, corT10);
        fator_rotac_cima_A = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_a() {
    
    if (fator_rotac_esquerda_A == 120 || fator_rotac_esquerda_A == 240){
        CopiaVetores(corT2, corT5, corT13);
        if (fator_rotac_esquerda_A == 240)
            CopiaVetores(corT2, corT5, corT13);
        fator_rotac_esquerda_A = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_d() {
    
    if (fator_rotac_direita_A == 120 || fator_rotac_direita_A == 240){
        CopiaVetores(corT9, corT14, corT6);
        if (fator_rotac_direita_A == 240)
            CopiaVetores(corT9, corT14, corT6);
        fator_rotac_direita_A = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_g() {
    
    if (fator_rotac_frente_B == 120 || fator_rotac_frente_B == 240){
        CopiaSequenciaVetores(corT2, corT3, corT1, corT10, corT11, corT9, corT6, corT7, corT5, corT13, corT16, corT14);
        if (fator_rotac_frente_B == 240)
            CopiaSequenciaVetores(corT2, corT3, corT1, corT10, corT11, corT9, corT6, corT7, corT5, corT13, corT16, corT14);
        fator_rotac_frente_B = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_t() {
    
    if (fator_rotac_cima_B == 120 || fator_rotac_cima_B == 240){
        CopiaSequenciaVetores(corT2, corT3, corT4, corT12, corT11, corT9, corT14, corT15, corT13, corT5, corT8, corT6);
        if (fator_rotac_cima_B == 240)
            CopiaSequenciaVetores(corT2, corT3, corT4, corT12, corT11, corT9, corT14, corT15, corT13, corT5, corT8, corT6);
        fator_rotac_cima_B = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_f() {
    
    if (fator_rotac_esquerda_B == 120 || fator_rotac_esquerda_B == 240){
        CopiaSequenciaVetores(corT6, corT7, corT8, corT4, corT3, corT1, corT16, corT15, corT14, corT9, corT12, corT10);
        if (fator_rotac_esquerda_B == 240)
            CopiaSequenciaVetores(corT6, corT7, corT8, corT4, corT3, corT1, corT16, corT15, corT14, corT9, corT12, corT10);
        fator_rotac_esquerda_B = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx_h() {
    
    if (fator_rotac_direita_B == 120 || fator_rotac_direita_B == 240){
        CopiaSequenciaVetores(corT10, corT11, corT12, corT8, corT7, corT5, corT13, corT15, corT16, corT1, corT4, corT2);
        if(fator_rotac_direita_B == 240)
            CopiaSequenciaVetores(corT10, corT11, corT12, corT8, corT7, corT5, corT13, corT15, corT16, corT1, corT4, corT2);
        fator_rotac_direita_B = 0;
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RotacaoTotal();
        Pyraminx();
    }
    
}

void AtualizaPyraminx(){
    AtualizaPyraminx_s();
    AtualizaPyraminx_w();
    AtualizaPyraminx_a();
    AtualizaPyraminx_d();
    AtualizaPyraminx_g();
    AtualizaPyraminx_t();
    AtualizaPyraminx_f();
    AtualizaPyraminx_h();
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
    
    // Local da camera
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
    
    // Limpa a janela de visualização com a cor
    // de fundo especificada
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Inicializa o valor das cores de cada triangulo equilatero
    InicializaCoresTriangulos();
    
}

void Desenha(){
    
    // Desenha e Atualiza o Pyraminx inicial com base no valor da rotacao inicial (CONFIG_INICIAL)
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    RotacaoTotal();
    Pyraminx();
    AtualizaPyraminx();
    
    //   Função principal do programa inteiro
    //
    // Trata cada caso de rotação separadamente de acordo com o comando do usuario.
    //
    
    if (caso == 's' || caso == 'S')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação tetraedro da frente. Comandos: (S, s)
        RotacaoFrente_A();
        PyraFrente();
        glPopMatrix();
        glPushMatrix();
        RestoCentro();
        PyraCima();
        PyraEsq();
        PyraDir();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_s();
    }
    
    if (caso == 'w' || caso == 'W')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação tetraedro de cima. Comandos: (W, w)
        RotacaoCima_A();
        PyraCima();
        glPopMatrix();
        glPushMatrix();
        RestoCentro();
        PyraFrente();
        PyraEsq();
        PyraDir();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_w();
    }
    
    if (caso == 'a' || caso == 'A')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação tetraedro da esquerda. Comandos: (A, a)
        RotacaoEsquerda_A();
        PyraEsq();
        glPopMatrix();
        glPushMatrix();
        RestoCentro();
        PyraFrente();
        PyraCima();
        PyraDir();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_a();
    }
    
    if (caso == 'd' || caso == 'D')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação tetraedro da direita. Comandos: (D, d)
        RotacaoDireita_A();
        PyraDir();
        glPopMatrix();
        glPushMatrix();
        RestoCentro();
        PyraFrente();
        PyraCima();
        PyraEsq();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_d();
    }
    
    if (caso == 'g' || caso == 'G')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação da base do tetraedro da frente. Comandos: (D, d)
        RotacaoFrente_B();
        RestoCentro();
        PyraCima();
        PyraEsq();
        PyraDir();
        glPopMatrix();
        glPushMatrix();
        PyraFrente();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_g();
    }
    
    if (caso == 't' || caso == 'T')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação da base do tetraedro de cima. Comandos: (T, t)
        RotacaoCima_B();
        RestoCentro();
        PyraFrente();
        PyraEsq();
        PyraDir();
        glPopMatrix();
        glPushMatrix();
        PyraCima();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_t();
    }
    
    if (caso == 'f' || caso == 'F')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação da base do tetraedro da esquerda. Comandos: (F, f)
        RotacaoEsquerda_B();
        RestoCentro();
        PyraCima();
        PyraFrente();
        PyraDir();
        glPopMatrix();
        glPushMatrix();
        PyraEsq();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_f();
    }
    
    if (caso == 'h' || caso == 'H')
    {
        glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glPushMatrix();
        // Rotaçao total por Barra de Espaço
        RotacaoTotal();
        glPushMatrix();
        // Rotação da base do tetraedro da direita. Comandos: (H, h)
        RotacaoDireita_B();
        RestoCentro();
        PyraCima();
        PyraFrente();
        PyraEsq();
        glPopMatrix();
        glPushMatrix();
        PyraDir();
        glPopMatrix();
        glPopMatrix();
        
        AtualizaPyraminx_h();
    }
    
    // Mostra as Coordenadas
    glLoadIdentity();
    MostraCoordenadas();
    
    // Executa os comandos OpenGL para renderização
    glFlush();
}






// Feito por: Victor Cordeiro Costa
// Contato: victorcorcos@gmail.com
