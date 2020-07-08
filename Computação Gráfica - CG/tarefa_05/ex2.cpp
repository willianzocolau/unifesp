#include <GL/glut.h>

#include <math.h>

float t = 0.0;
float r = 43;
float controle = 0;
float click = -1;
float adicional_key = 0;
float parar = 0;
float maxima = 500;

void init() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-3.0, 3.0, -3.0, 3.0);
}

void DrawEllipse(float cx, float cy, float rx, float ry, float num_segments) {
  glColor3ub(255, 215, 0);
  float theta = 2 * 3.1415926 / num_segments;
  float c = cosf(theta);
  float s = sinf(theta);
  float t;

  float x = 1;
  float y = 0;

  glBegin(GL_TRIANGLE_FAN);
  for (int ii = 0; ii < num_segments; ii++) {
    glVertex2f(x * rx + cx, y * ry + cy);
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
}

void drawFilledSun() {
  DrawEllipse(-0.5, 0, 0.5, 0.25, 100);
  DrawEllipse(0.5, 0, 0.5, 0.25, 100);
  DrawEllipse(0, 0.5, 0.25, 0.5, 100);
  DrawEllipse(0, -0.5, 0.25, 0.5, 100);
  int i, x, y;
  double radius = 0.25;
  glColor3ub(139, 69, 19);
  double twicePi = 2.0 * 3.142;
  x = 0, y = 0;
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y);
  for (i = 0; i <= 10000; i++) {
    glVertex2f(
      (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
    );
  }
  glEnd();
}

void desenha() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glColor3ub(139, 69, 19);
  glBegin(GL_POLYGON);
  glVertex2f(-0.2, 0);
  glVertex2f(-0.2, -2);
  glVertex2f(0.2, -2);
  glVertex2f(0.2, 0);
  glEnd();
  glRotatef(r, 0.0, 0.0, 1.0);
  drawFilledSun();
  glPopMatrix();
  glFlush();
}

void Keyboard(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_RIGHT :
    click = -1;
    parar = 0;
    adicional_key += 1;
    break;
  case GLUT_KEY_LEFT :
    click = -1;
    parar = 0;
    adicional_key -= 1;
    break;
  }
  glutPostRedisplay();
}

void GL_Setup(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  gluPerspective(45, (float) width / height, .1, 100);
  glMatrixMode(GL_MODELVIEW);
}

void timerFunc(int value) {
   if(click == 0){
      adicional_key -= 0.02;
      parar = 0;
   } else if(click == 1 && adicional_key < 0){
      adicional_key += 0.02;
      if(adicional_key >= 0) parar = 1;
      
   }

   if(parar == 0){
      r = r + adicional_key;
   }
  glutPostRedisplay();
  glutTimerFunc(10, timerFunc, 1);
}

void mouseFunc(int button, int state, int x, int y){
     switch (button)    {
        case GLUT_LEFT_BUTTON:
           if (state == GLUT_DOWN)
            click = 0;
           break;
        case GLUT_RIGHT_BUTTON:
           if (state == GLUT_DOWN)
            click=1;
           break;
        default:
           break;
     }
}

int main(int argc, char * argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(1000, 1000);
  glutCreateWindow("Primeiro programa usando OpenGL");
  init();
  glutDisplayFunc(desenha);
  glutSpecialFunc(Keyboard);
  glutMouseFunc(mouseFunc);
  glutTimerFunc(10, timerFunc, 1);
  glutMainLoop();
  return 0;
}