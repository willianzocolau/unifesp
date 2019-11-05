#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265

float angle = 0.0;
float step = 5.0;
float val = PI/360;

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo

    //imprime as matrized GL_PROJECTION e GL_MODELVIEW
    printf("M_ortho = \n");
    float matrix[16];
    int i,j;
    glGetFloatv(GL_PROJECTION_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");

    printf("\n\nM_wc,vc = \n");
    glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            printf("%f ",matrix[i + j * 4]);
        }
        printf("\n");
    }
    printf("\n");
}

void cube(){
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(0.5,-0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(0.5,-0.5,-0.5);
    glEnd();
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    glEnd();
    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(0.5,-0.5,-0.5);
    glEnd();
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
    glEnd();
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(sin(angle*val)+cos(angle*val),1.0,cos(angle*val)-sin(angle*val),
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)

    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(sin(angle*val)+cos(angle*val),1.0,cos(angle*val)-sin(angle*val),
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-3.0, 3.0, -3.0, 3.0, -4.0, 20.0); //define uma projeção ortogonal
    glViewport(0, 0, 500, 500);

    glPushMatrix();
    glRotatef(angle, 1,0,0);
    cube(); //desenha um cubo
    glPopMatrix();

    glFlush(); //força o desenho das primitivas
    glutSwapBuffers();
}

void timerFunc(int value)
{
    angle += step;
    glutPostRedisplay();
    glutTimerFunc(30,timerFunc, 1);
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Viewing 3D - Projecao Ortogonal");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(30,timerFunc,1);
    init();
    glutMainLoop();
    return 0;
}