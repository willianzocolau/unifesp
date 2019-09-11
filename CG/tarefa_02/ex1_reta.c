#include <GL/glut.h>

int size = 800, height = 800;
int click = 0;
int coordenada_x, coordenada_y, coordenada_x_f, coordenada_y_f;
void mouse(int var1, int condition, int x, int y);
void display();
void coordenadas();

int main(int argc, char ** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(size, height);
  glutCreateWindow("Atividade 2 - Exercício 1");
  glutDisplayFunc(display);
  coordenadas();
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
}

void printPixel(int x, int y) {
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
  glFlush();
}

void display() {
  glClearColor(1, 1, 1, 1.0);
  glColor3f(0.2, 0.3, 0.3);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
}

void algoritmo(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int x, y;
  if (dx >= dy) {
    int d = 2 * dy - dx;
    int ds = 2 * dy;
    int dt = 2 * (dy - dx);
    if (x0 < x1) {
      x = x0;
      y = y0;
    } else {
      x = x1;
      y = y1;
      x1 = x0;
      y1 = y0;
    }
    printPixel(x, y);
    while (x < x1) {
      if (d < 0)
        d += ds;
      else {
        if (y < y1) {
          y++;
          d += dt;
        } else {
          y--;
          d += dt;
        }
      }
      x++;
      printPixel(x, y);
    }
  } else {
    int d = 2 * dx - dy;
    int ds = 2 * dx;
    int dt = 2 * (dx - dy);
    if (y0 < y1) {
      x = x0;
      y = y0;
    } else {
      x = x1;
      y = y1;
      y1 = y0;
      x1 = x0;
    }
    printPixel(x, y);
    while (y < y1) {
      if (d < 0)
        d += ds;
      else {
        if (x > x1) {
          x--;
          d += dt;
        } else {
          x++;
          d += dt;
        }
      }
      y++;
      printPixel(x, y);
    }
  }
}

void mouse(int var1, int condition, int x, int y) {
  if (var1 == GLUT_LEFT_BUTTON && condition == GLUT_DOWN) {
    switch (click) {
      case 0:
        coordenada_x = x;
        coordenada_y = (height - y);
        click = 1;
        break;
      case 1:
        coordenada_x_f = x;
        coordenada_y_f = (height - y);
        algoritmo(coordenada_x, coordenada_y, coordenada_x_f, coordenada_y_f);
        click = 0;
        break;
    }
  }
}

void coordenadas() {
  glViewport(0, 0, size, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLdouble) size, 0.0, (GLdouble) height);
  glMatrixMode(GL_MODELVIEW);
}