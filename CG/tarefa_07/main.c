#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

float zoom_a = 0.01;
float zoom_b = 2;
float stepz_a = 0.01;
float stepz_b = 0.01;

float stepl_a = 0.5;
float stepl_b = 0.5;
float line_a = 150;
float line_b = -150;

void drawObject() {
    glBegin(GL_TRIANGLES);
    glVertex2i(50, -50);
    glVertex2i(0, 50);
    glVertex2i(-50, -50);
    glEnd();
}

void drawOutline() {
    glBegin(GL_LINE_LOOP);
    glVertex2i(-99, 99);
    glVertex2i(99, 99);
    glVertex2i(99, -99);
    glVertex2i(-99, -99);
    glEnd();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);     //desenha o fundo (limpa a janela)

    glMatrixMode(GL_PROJECTION);

    //Inferior
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(150, 0, 300, 300);
    glColor3f(0.5f, 0.5f, 0.0f);

    glPushMatrix();
    glScalef(zoom_a, zoom_a, zoom_a);
    drawObject();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutline();


    //Meio esquerdo
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 300, 300, 300);
    glColor3f(0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(line_a,1,1);
    drawObject();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutline();

    //Meio direito
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(300, 300, 300, 300);
    glColor3f(0.2f, 0.5f, 0.5f);

    glPushMatrix();
    glTranslatef(line_b,1,1);
    drawObject();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutline();


    //Superior
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(150, 600, 300, 300);
    glColor3f(0.0f, 0.0f, 1.0f);

    glPushMatrix();
    glScalef(zoom_b, zoom_b, zoom_b);
    drawObject();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawOutline();

    glFlush();
}

void timerFunc(int value) {
    zoom_a += stepz_a;
    zoom_b += stepz_b;
    line_a += stepl_a;
    line_b += stepl_b;
    if (zoom_a >= 2) stepz_a = -0.01;
    if (zoom_a <= 0.1) stepz_a = 0.01;
    if (zoom_b >= 2) stepz_b = -0.01;
    if (zoom_b <= 0.1) stepz_b = 0.01;

    if (line_a >= 150) stepl_a = -0.5;
    if (line_a <= -150) stepl_a = 0.5;
    if (line_b >= 150) stepl_b = -0.5;
    if (line_b <= -150) stepl_b = 0.5;

    glutPostRedisplay();
    glutTimerFunc(10, timerFunc, 1);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(800, 800);
    glutInitWindowSize(600, 900);
    glutCreateWindow("Viewing 2D");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(10, timerFunc, 1);
    init();
    glutMainLoop();
    return 0;
}