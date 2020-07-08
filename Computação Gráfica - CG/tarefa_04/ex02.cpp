#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

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

void desenha(){
  glClear(GL_COLOR_BUFFER_BIT);
  glPopMatrix();
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  glVertex2f(-1.3, 0.0);
  glVertex2f(-1.2, 0.4);
  glVertex2f(-0.6, 0.4);
  glVertex2f(0, 0.8);
  glVertex2f(1.3, 0.8);
  glVertex2f(1.8, 0.4);
  glVertex2f(2.1, 0.4);
  glVertex2f(2.4, 0);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glRotatef(r,0.0,0.0,1.0);
  DrawEllipse(0, 0.0, 0.30, 0.30, 7);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(1.5,0.0,0.0);
  glRotatef(r,0.0,0.0,1.0);
  glTranslatef(-2.0,0.0,0.0);
  DrawEllipse(2.0, 0.0, 0.30, 0.30, 7);
  glPopMatrix();
  glTranslatef(t,0.0,0.0);
  glFlush();
}
void Keyboard (unsigned char key, int x, int y){
  switch(key){
    case 'd':
    case 'D':
      t=t+0.05;
      r=r+20;
      break;
    case 'e':
    case 'E':
      t=t-0.05;
      r=r-20;
      break;
  }
  printf("%2f  %2f", t, r);
  glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
  glutInit(&argc , argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (3500 ,1500);
  glutInitWindowSize (1000 ,1000);
  glutCreateWindow ("Primeiro programa usando OpenGL");
  init();
  glutDisplayFunc (desenha);
  glutKeyboardFunc(Keyboard);
  glutMainLoop ();
  return 0;
}