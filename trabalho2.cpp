#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Variáveis globais
float maePosX = 0.0f, maePosZ = 0.0f, maeAngle = 0.0f;
bool temPeixe = false;
float filhoteEnergia = 60.0f;
float tempoJogo = 0.0f;
int peixeX = 0, peixeZ = 2;
bool buraco[10][10] = {false};
bool andandoFrente = false;
bool andandoTras = false;
bool virandoEsquerda = false;
bool virandoDireita = false;
int eixoX=0;
int eixoZ=0;

void desenharPeixe(float, float);


// Inicialização
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.6f, 0.85f, 1.0f, 1.0f);

    GLfloat light0_pos[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light0_amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light0_diff[] = { 0.8, 0.8, 0.8, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

    GLfloat light1_pos[] = { -1.0, 1.0, -1.0, 0.0 };
    GLfloat light1_diff[] = { 0.6, 0.6, 0.6, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

    srand(time(NULL));
}

// Desenha pinguim
void desenharPinguim(float x, float z, bool filhote) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    if (!filhote) glRotatef(maeAngle, 0, 1, 0);

    float scale = filhote ? 0.7f : 1.0f;
    glTranslatef(0.0f, 1.4f * scale, 0.0f); // Alinhamento dos pés com Y=0

    glColor3f(0.1f, 0.1f, 0.1f); // Corpo
    glPushMatrix();
    glScalef(1.0f * scale, 1.6f * scale, 0.7f * scale);
    glutSolidSphere(1.0, 40, 40);
    glPopMatrix();

    glColor3f(0.95f, 0.95f, 0.95f); // Barriga
    glPushMatrix();
    glTranslatef(0.0f, -0.2f * scale, 0.65f * scale);
    glScalef(0.7f * scale, 0.9f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 40, 40);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f); // Cabeça
    glPushMatrix();
    glTranslatef(0.0f, 1.3f * scale, 0.0f);
    glScalef(0.8f * scale, 0.8f * scale, 0.7f * scale);
    glutSolidSphere(0.6 * scale, 40, 40);
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.0f); // Bico
    glPushMatrix();
    glTranslatef(0.0f, 1.2f * scale, 0.5f * scale);
    glScalef(1.0f * scale, 1.0f * scale, 1.5f * scale);
    glutSolidCone(0.12 * scale, 0.3 * scale, 20, 20);
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f); // Olhos brancos
    glPushMatrix();
    glTranslatef(-0.18f * scale, 1.35f * scale, 0.45f * scale);
    glScalef(0.1f * scale, 0.1f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.18f * scale, 1.35f * scale, 0.45f * scale);
    glScalef(0.1f * scale, 0.1f * scale, 0.1f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f); // Pupilas
    glPushMatrix();
    glTranslatef(-0.18f * scale, 1.35f * scale, 0.5f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.18f * scale, 1.35f * scale, 0.5f * scale);
    glScalef(0.04f * scale, 0.04f * scale, 0.04f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glColor3f(0.1f, 0.1f, 0.1f); // Asas
    glPushMatrix();
    glTranslatef(-0.9f * scale, 0.1f * scale + (filhote ? 0 : sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 0.1 * scale), 0.0f);
    glRotatef(30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.9f * scale, 0.1f * scale + (filhote ? 0 : sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 0.1 * scale), 0.0f);
    glRotatef(-30, 0, 0, 1);
    glScalef(0.25f * scale, 1.0f * scale, 0.15f * scale);
    glutSolidSphere(1.0, 30, 30);
    glPopMatrix();

    glColor3f(1.0f, 0.7f, 0.0f); // Patas
    glPushMatrix();
    glTranslatef(-0.35f * scale, -1.4f * scale, 0.2f * scale);
    glScalef(0.5f * scale, 0.15f * scale, 0.4f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.35f * scale, -1.4f * scale, 0.2f * scale);
    glScalef(0.5f * scale, 0.15f * scale, 0.4f * scale);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    if (temPeixe && !filhote) {
        glPushMatrix();
        glTranslatef(-1.0f, 1.7f * scale, 2.2f * scale);
        glRotatef(90,0,1,0);
        desenharPeixe(1,1);
        glPopMatrix();
    }
    glPopMatrix();
}

void desenharPeixe(float x, float z) {
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f); // Olhos brancos
        glPushMatrix();
            glTranslatef(x+0.2, -0.42f, z+0.15);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(1.0, 20, 20);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(x+0.2, -0.42f, z-0.15);
            glScalef(0.1, 0.1, 0.1);
            glutSolidSphere(1.0, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(x, -0.5f, z);
            glScalef(0.5f, 0.3f, 0.2f);
            glColor3f(1.0f, 0.0f, 0.0f);
            glutSolidSphere(1.0, 20, 20);
        glPopMatrix();
            glColor3f(1.0f, 0.45f, 0.0f);
            glPushMatrix();
                glTranslatef(x-0.65, -0.5f, z);
                glRotatef(90, 0, 1, 0);
                glScalef(1,2,1);
                glutSolidCone(0.1, 0.2, 20, 20);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void desenharBuraco(float x, float z) {
    glColor3f(0.0f, 0.0f, 0.5451f);
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glScalef(0.7f, 0.1f, 0.7f);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
}

void desenharGelo() {
    glColor3f(0.9f, 0.9f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(10.0f, 0.1f, 10.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenharSkybox() {
    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
    for (int i = -1; i <= 1; i += 2)
        for (int j = -1; j <= 1; j += 2) {
            glVertex3f(i * 10, -10, j * 10); glVertex3f(i * 10, 10, j * 10);
        }
    glEnd();
    glEnable(GL_LIGHTING);
}

void desenharCenario() {
    static float anguloSol = 0.0f;
    anguloSol += 0.005f;
    if (anguloSol > 2 * M_PI) anguloSol -= 2 * M_PI;

    glDisable(GL_LIGHTING);

    glColor3f(0.0f, 0.2f, 0.5f);
    glBegin(GL_QUADS);
    for (float x = -50; x < 50; x += 50) {
        for (float z = -50; z < 50; z += 50) {
            glVertex3f(x, -10.0f, z);
            glVertex3f(x + 50, -10.0f, z);
            glVertex3f(x + 50, 0.0f, z);
            glVertex3f(x, 0.0f, z);
        }
    }
    glEnd();

    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glVertex3f(50.0f, 0.0f, -50.0f);
    glVertex3f(50.0f, 50.0f, -50.0f);
    glVertex3f(-50.0f, 50.0f, -50.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(10.0f * cos(anguloSol), 30.0f, 10.0f * sin(anguloSol));
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(2.0, 40, 40);
    glPopMatrix();

    float nuvens[3][3] = {
        { -15.0f, 40.0f, -20.0f },
        { 10.0f, 42.0f, 0.0f },
        { 20.0f, 38.0f, 15.0f }
    };
    for (int i = 0; i < 3; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        glPushMatrix();
        glTranslatef(nuvens[i][0], nuvens[i][1], nuvens[i][2]);
        glutSolidSphere(2.0, 20, 20);
        glTranslatef(2.0, 0.0, 0.0);
        glutSolidSphere(1.5, 20, 20);
        glTranslatef(-4.0, 0.0, 0.0);
        glutSolidSphere(1.5, 20, 20);
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
}

void jogo(){
    //desenharCenario();
   //desenharSkybox();
    desenharGelo();
    glPushMatrix();
        
        for (int i = -5; i < 5; i++){
            for (int j = -5; j < 5; j++){
                if (buraco[i + 5][j + 5]) {
                    desenharBuraco(i, j);
                }
            }
        }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(peixeX, 0.85, peixeZ);
       // glRotatef(90,0,1,0);
        desenharPeixe(peixeX, peixeZ);
    glPopMatrix();

    desenharPinguim(0.0f, 0.0f, true);
    desenharPinguim(maePosX, maePosZ, false);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
     glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    //gluLookAt(0.0, 5.0, 10.0, maePosX, 0.5, maePosZ, 0.0, 1.0, 0.0); // acompanha a pinguim mãe
    gluLookAt(0.0, 5, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // camera fix
    jogo();

 

    

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

bool podeMover(float novoX, float novoZ) {
    int i = (int)(novoX + 5); // converter para índice matriz
    int j = (int)(novoZ + 5);
    if(i < 0 || i >= 10 || j < 0 || j >= 10) return false;
    return !buraco[i][j];
}

void keyboardSpecial(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            andandoFrente = true;
            break;
        case GLUT_KEY_DOWN:
            andandoTras = true;
            break;
        case GLUT_KEY_LEFT:
            virandoEsquerda = true;
            break;
        case GLUT_KEY_RIGHT:
            virandoDireita = true;
            break;
    }
}

void keyboardSpecialUp(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            andandoFrente = false;
            //eixoX =0;
 
            break;
        case GLUT_KEY_DOWN:
            andandoTras = false;
         
            //eixoX=0;
            break;
        case GLUT_KEY_LEFT:
            virandoEsquerda = false;
    
            break;
        case GLUT_KEY_RIGHT:
            virandoDireita = false;
     
            break;
    }
}
void update(int value) {
    tempoJogo += 0.016f;
    filhoteEnergia -= 0.016f;

    // Movimento contínuo da pinguim mãe
float velocidade = 0.08f;
float rotacaoVel = 2.5f;

if (virandoEsquerda) maeAngle -= rotacaoVel;
if (virandoDireita) maeAngle += rotacaoVel;

float rad = maeAngle * M_PI / 180.0f;
if (andandoFrente) {
    maePosX += velocidade * sin(rad);
    maePosZ += velocidade * cos(rad);
}
if (andandoTras) {
    maePosX -= velocidade * sin(rad);
    maePosZ -= velocidade * cos(rad);
}
    if (filhoteEnergia <= 0 || tempoJogo >= 300) exit(0);

    if (rand() % 100 < 1) {
        peixeX = (rand() % 10 - 5) * 0.5f;
        peixeZ = (rand() % 10 - 5) * 0.5f;
    }

    if (rand() % 100 < 1) {
        int i = rand() % 10;
        int j = rand() % 10;
        buraco[i][j] = true;
    }

    float dx = peixeX - maePosX;
    float dz = peixeZ - maePosZ;
    if (!temPeixe && dx*dx + dz*dz < 0.5f) {
        temPeixe = true;
        peixeX = peixeZ = 0;
    }

    dx = 0.0f - maePosX;
    dz = 0.0f - maePosZ;
    if (temPeixe && dx*dx + dz*dz < 0.5f) {
        temPeixe = false;
        filhoteEnergia = 60.0f;
    }

    glutTimerFunc(16, update, 0);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Jogo do Pinguim 3D");
    glutFullScreen();

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialUpFunc(keyboardSpecialUp);
    glutSpecialFunc(keyboardSpecial);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
