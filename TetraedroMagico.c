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

#define VELOCIDADE 15      // Natural: 5
#define INITIAL_CONFIG 0   // Rotacoes iniciais

// Para deixar a tela cheia
int telacheia=0;

// Valor da Rotacao do objeto inteiro
float fator_rotac_total=0;

// Valor da Rotacao das Minipiramides
float fator_rotac_frente_A=INITIAL_CONFIG, fator_rotac_cima_A=INITIAL_CONFIG, fator_rotac_direita_A=-INITIAL_CONFIG, fator_rotac_esquerda_A=INITIAL_CONFIG;

// Valor da Rotacao das Bases das Minipiramides
float fator_rotac_frente_B=-INITIAL_CONFIG, fator_rotac_cima_B=INITIAL_CONFIG, fator_rotac_direita_B=INITIAL_CONFIG, fator_rotac_esquerda_B=INITIAL_CONFIG;

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

// Cores das faces
GLfloat corCimaEsquerda[3] = { 1.0f, 0.0f, 0.0f };   // Vermelho
GLfloat corCimaDireita[3]  = { 0.0f, 0.0f, 1.0f };   // Azul
GLfloat corBaixo[3]        = { 0.0f, 1.0f, 0.0f };   // Verde
GLfloat corTras[3]         = { 1.0f, 1.0f, 0.0f };   // Amarelo
GLfloat corInterna[3]      = { 0.0f, 0.0f, 0.0f };   // Preto

// Triangulos Equilateros externos (De acordo com a figura localizada na pasta)
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

// Triangulos Equilateros internos
void TEsq();
void TDir();
void TCima();
void TFrente();

// Tetraedros. Formado pelos triangulos equilateros.
void Tetraedro();
void TetraFrente();
void TetraEsq();
void TetraDir();
void TetraCima();
void RestoCentro();

// Piramide base3.
void MiniPiramideFrente();
void BasePiramideFrente();
void MiniPiramideEsquerda();
void BasePiramideEsquerda();
void MiniPiramideDireita();
void BasePiramideDireita();
void MiniPiramideCima();
void BasePiramideCima();

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

// Mostra coordenadas
void MostraCoordenadas();

// Mostra o menu
void Menu();

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
    glutCreateWindow("Tetraedro Magico");
    
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

void Menu();

void Keyboard (unsigned char key, int x, int y){
    
    switch (key)
    {
        case 's':
            fator_rotac_frente_A += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'S':
            fator_rotac_frente_A -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'a':
            fator_rotac_esquerda_A += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'A':
            fator_rotac_esquerda_A -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'd':
            fator_rotac_direita_A += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'D':
            fator_rotac_direita_A -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'w':
            fator_rotac_cima_A += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'W':
            fator_rotac_cima_A -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'g':
            fator_rotac_frente_B += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'G':
            fator_rotac_frente_B -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'f':
            fator_rotac_esquerda_B += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'F':
            fator_rotac_esquerda_B -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'h':
            fator_rotac_direita_B += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'H':
            fator_rotac_direita_B -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 't':
            fator_rotac_cima_B += VELOCIDADE;
            glutPostRedisplay();
            break;
        case 'T':
            fator_rotac_cima_B -= VELOCIDADE;
            glutPostRedisplay();
            break;
        case 32: // Barra de espaco
            fator_rotac_total += VELOCIDADE+5;
            glutPostRedisplay();
            break;
        case 'p':
            if (telacheia == 0)
            {
                glutFullScreen();
                telacheia = 1;
            }
            else
            {
                glutReshapeWindow(600, 600);
                glutPositionWindow(300, 150);
                telacheia = 0;
            }
            break;
        case 27:
            exit(0);
            break;
        default:
            printf ("   Special key %c == %d\n", key, key);
    }
    printf("Frente: %f \n Cima: %f \n Direita: %f \n Esquerda:  %f \n", fator_rotac_frente_A, fator_rotac_cima_A, fator_rotac_direita_A, fator_rotac_esquerda_A);
}

void T1(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertB);
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void T2(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertH);
    glVertex3fv(vertF);
    glVertex3fv(vertC);
    
    glEnd();
    
}

void T3(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void T4(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaEsquerda);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T5(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertC);
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T6(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertI);
    glVertex3fv(vertG);
    glVertex3fv(vertD);
    
    glEnd();
    
}

void T7(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T8(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corBaixo);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T9(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertD);
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T10(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertJ);
    glVertex3fv(vertE);
    glVertex3fv(vertB);
    
    glEnd();
    
}

void T11(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T12(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corCimaDireita);
    glVertex3fv(vertG);
    glVertex3fv(vertE);
    glVertex3fv(vertA);
    
    glEnd();
    
}

void T13(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);
    glVertex3fv(vertC);
    glVertex3fv(vertH);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void T14(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);
    glVertex3fv(vertI);
    glVertex3fv(vertJ);
    glVertex3fv(vertD);
    
    glEnd();
    
}

void T15(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);
    glVertex3fv(vertH);
    glVertex3fv(vertI);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void T16(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corTras);
    glVertex3fv(vertB);
    glVertex3fv(vertH);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void TEsq(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corInterna);
    glVertex3fv(vertH);
    glVertex3fv(vertF);
    glVertex3fv(vertI);
    
    glEnd();
    
}

void TDir(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corInterna);
    glVertex3fv(vertI);
    glVertex3fv(vertG);
    glVertex3fv(vertJ);
    
    glEnd();
    
}

void TCima(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corInterna);
    glVertex3fv(vertJ);
    glVertex3fv(vertE);
    glVertex3fv(vertH);
    
    glEnd();
    
}

void TFrente(){
    
    glBegin(GL_TRIANGLES);
    
    glColor3fv(corInterna);
    glVertex3fv(vertE);
    glVertex3fv(vertF);
    glVertex3fv(vertG);
    
    glEnd();
    
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

void TetraFrente(){
    
    T4();
    T8();
    T12();
    TFrente();
    
}

void TetraEsq(){
    
    T2();
    T5();
    T13();
    TEsq();
    
}

void TetraDir(){
    
    T6();
    T9();
    T14();
    TDir();
    
}

void TetraCima(){
    
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


void MiniPiramideFrente(){
    
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

void BasePiramideFrente(){
    
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
    glVertex3fv(vertH);
    glVertex3fv(vertI);
    glVertex3fv(vertF);
    
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

void MiniPiramideCima(){
    
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

void BasePiramideCima(){
    
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
    BasePiramideFrente();
    glLoadIdentity();
    
    // Rotaciona
    RotacaoTotal();
    RotacaoFrente_A();
    
    // Desenha piramide do topo
    MiniPiramideFrente();
    glLoadIdentity();
    
}

void TesteRotacaoCima(){
    
    // Rotaciona
    RotacaoTotal();
    RotacaoCima_B();
    
    // Desenha base da piramide traseira
    BasePiramideCima();
    glLoadIdentity();
    
    // Rotaciona
    RotacaoTotal();
    RotacaoCima_A();
    
    // Desenha piramide traseira
    MiniPiramideCima();
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
    
    // Fazer os glPush e glPop aqui.
    
    
    
    glPushMatrix();
     // Rotaçao total por Barra de Espaço
     RotacaoTotal();
     glPushMatrix();
      // Comandos: (S, s)
      RotacaoFrente_A();
      TetraFrente();
     glPopMatrix();
     glPushMatrix();
      // Comandos: (G, g)
      RotacaoFrente_B();
      RestoCentro();
      glPushMatrix();
       // Comandos: (W, w)
       RotacaoCima_A();
       TetraCima();
      glPopMatrix();
      glPushMatrix();
       // Comandos: (A, a)
       RotacaoEsquerda_A();
       TetraEsq();
      glPopMatrix();
      glPushMatrix();
       // Comandos: (D, d)
       RotacaoDireita_A();
       TetraDir();
      glPopMatrix();
     glPopMatrix();
    glPopMatrix();
    
    
    
    
    
    // Mostra as Coordenadas
    glLoadIdentity();
    MostraCoordenadas();
    
    // Executa os comandos OpenGL para renderização
    glFlush();
}

 
    // Rotações Feitas:
    //
    // Total
    // Minipiramide da frente
    // Base da Minipiramide da frente
    // Minipiramide da esquerda
    //
    // Como fazer as outras rotaçoes? Principalmente a Base da Minipiramide da esquerda?
    //
    // O problema é que é preciso utilizar de triangulos já escritos!
    // Neste caso T4(), T8() e T12() precisariam para a Base da Minipiramide da esquerda! E não pode desenhá-los de novo.
    //



/*
 
 Exemplo de glPush e glPop
 
 glPushMatrix();
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 1.0, 0.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
     glScalef (2.0, 0.4, 1.0);
     glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
     glScalef (2.0, 0.4, 1.0);
     glutWireCube (1.0);
   glPopMatrix();
 glPopMatrix();
 
 
 */









