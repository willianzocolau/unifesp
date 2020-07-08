#include <GL/glut.h>
#include <math.h>

float t=0.0;
float r=0.0;

void init(){
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-3.0,3.0,-3.0,3.0);
}

void DrawEllipse(float cx, float cy, float rx, float ry, float num_segments)
{
  glColor3ub(255,215,0);
  float theta = 2 * 3.1415926 / num_segments;
  float c = cosf(theta);
  float s = sinf(theta);
  float t;

  float x = 1;
  float y = 0;

  glBegin(GL_TRIANGLE_FAN);
  for(int ii = 0; ii < num_segments; ii++)
  {
    glVertex2f(x * rx + cx, y * ry + cy);
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  }
  glEnd();
}

void drawFilledSun(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  DrawEllipse(-0.5, 0, 0.5, 0.25, 100);
  DrawEllipse(0.5, 0, 0.5, 0.25, 100);
  DrawEllipse(0, 0.5, 0.25, 0.5, 100);
  DrawEllipse(0, -0.5, 0.25, 0.5, 100);
  int i, x, y;
  double radius = 0.25;
  glColor3ub(139,69,19);
  double twicePi = 2.0 * 3.142;
  x = 0, y = 0;
  glBegin(GL_TRIANGLE_FAN);
  glVertex2f(x, y);
  for (i = 0; i <= 10000; i++) {
    glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
    );
  }
  glEnd(); 
}

void desenha(){
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glPushMatrix();
  glRotatef(r,0.0,0.0,1.0);
  drawFilledSun();
  glPopMatrix();
  glFlush();
}
void Keyboard (unsigned char key, int x, int y){
  switch(key){
    case 'd':
    case 'D':
      t=t+0.25;
      r=r+20;
      break;
    case 'e':
    case 'E':
      t=t-0.25;
      r=r-20;
      break;
  }
  glutPostRedisplay();
}

void GL_Setup(int width, int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  gluPerspective(45, (float)width / height, .1, 100);
  glMatrixMode(GL_MODELVIEW);
}

int main ( int argc , char * argv [] ){
  glutInit(&argc , argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (200 ,200);
  glutInitWindowSize (1000 ,1000);
  glutCreateWindow ("Primeiro programa usando OpenGL");
  init();
  glutDisplayFunc (desenha);
  glutKeyboardFunc(Keyboard);
  glutMainLoop ();
  return 0;
}