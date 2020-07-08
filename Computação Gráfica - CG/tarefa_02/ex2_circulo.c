#include <GL/glut.h>

int processado = 0;
int click = 0;
int size = 800, height = 800;
int x_centro = size / 2, y_centro = height / 2; //inicialização

void display();
void show();
void mouse(int var1, int condition, int x, int y);

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(size, height);
  glutCreateWindow("Atividade 2 - Exercício 2");
  display();
  glutMouseFunc(mouse);
  glutDisplayFunc(show);
  glutMainLoop();
}

void plot_point(int x, int y) {
  if(processado == 1){
    glBegin(GL_POINTS);
    glVertex2i(x_centro + x, y_centro + y);
    glVertex2i(x_centro + x, y_centro - y);
    glVertex2i(x_centro + y, y_centro + x);
    glVertex2i(x_centro + y, y_centro - x);
    glVertex2i(x_centro - x, y_centro - y);
    glVertex2i(x_centro - y, y_centro - x);
    glVertex2i(x_centro - x, y_centro + y);
    glVertex2i(x_centro - y, y_centro + x);
    glEnd();
  }
}

void algoritmo(int r) {
  processado = 1;
  int x = 0, y = r;
  float pk = (5.0 / 4.0) - r;
  plot_point(x, y);
  int k;

  while (x < y) {
    x = x + 1;
    if (pk < 0)
      pk = pk + 2 * x + 1;
    else {
      y = y - 1;
      pk = pk + 2 * (x - y) + 1;
    }
    plot_point(x, y);
  }
  glFlush();
  processado = 0;
}

void show() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void display() {
  glClearColor(1.0, 1.0, 1.0, 0);
  glColor3f(0.0, 0.0, 0.0);
  gluOrtho2D(0, size, 0, height);
  glClear(GL_COLOR_BUFFER_BIT);
}

void mouse(int var1, int condition, int x, int y) {
  if (var1 == GLUT_LEFT_BUTTON && condition == GLUT_DOWN) {
    switch (click) {
      case 0:
        x_centro = x;
        click = 1;
        break;
      case 1:
        glClear(GL_COLOR_BUFFER_BIT);
        algoritmo(y);
        click = 0;
        break;
    }
  }
}
