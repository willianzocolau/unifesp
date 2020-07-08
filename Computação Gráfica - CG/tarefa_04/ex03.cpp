#include <GL/glut.h>
#include <math.h>

float braco_esq[5] = {0.0, 0.0, 0.0, -0.8, 0.8};
float braco_dir[5] = {0.0, 0.0, 0.0, 0.8, 0.0 };
float perna_esq[5] = {0.0, 0.0, 0.0, -2, -0.8};
float perna_dir[5] = {0.0, 0.0, 0.0, -0.8, -1.1 };

void init(){
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-3.0,3.0,-3.0,3.0);
}

void DrawEllipse(float cx, float cy, float rx, float ry, float num_segments)
{
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

void cabeca(){
  DrawEllipse(0, 1.35, 0.35, 0.35, 100);
}

void tronco(){
  glBegin(GL_POLYGON);
  glVertex2f(-0.3, -1);
  glVertex2f(-0.3, 1);
  glVertex2f(0.3, 1);
  glVertex2f(0.3, -1);
  glEnd();
}

void braco_e(){
  glBegin(GL_POLYGON);
  glVertex2f(-0.3, -0.5);
  glVertex2f(-0.3, 0.5);
  glVertex2f(-0.5, 0.5);
  glVertex2f(-0.5, -0.5);
  glEnd();
}

void braco_d(){
  glBegin(GL_POLYGON);
  glVertex2f(0.3, -0.5);
  glVertex2f(0.3, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glEnd();
}

void perna_e(){
  glBegin(GL_POLYGON);
  glVertex2f(-0.3, -1);
  glVertex2f(-0.3, -1.8);
  glVertex2f(0, -1.8);
  glVertex2f(0, -1);
  glEnd();
}

void perna_d(){
  glBegin(GL_POLYGON);
  glVertex2f(0.3, -1);
  glVertex2f(0.3, -1.8);
  glVertex2f(0, -1.8);
  glVertex2f(0, -1);
  glEnd();
}


void desenha(){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
  cabeca();
  tronco();

  glPushMatrix();
  glTranslatef(braco_esq[1],braco_esq[2], 0.0);
  glRotatef(braco_esq[0],0.0,0.0,1.0);
  braco_e();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(braco_dir[1],braco_dir[2], 0.0);
  glRotatef(braco_dir[0],0.0,0.0,1.0);
  braco_d();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(perna_esq[1],perna_esq[2], 0.0);
  glRotatef(perna_esq[0],0.0,0.0,1.0);
  perna_e();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(perna_dir[1],perna_dir[2], 0.0);
  glRotatef(perna_dir[0],0.0,0.0,1.0);
  perna_d();
  glPopMatrix();

  glFlush();
}

int inverte_r(int value){
  if(value == 0)
    return 90;
  else
    return  0;
}

void inverte_t(float value[]){
  if(value[1] != 0.0){
    value[1] = 0.0;
    value[2] = 0.0;
  }
  else {
    value[1] = value[3];
    value[2] = value[4];
  }
}

void Keyboard (unsigned char key, int x, int y){
  switch(key){
    case 'd':
    case 'D':
      perna_dir[0] = inverte_r(perna_dir[0]);
      inverte_t(perna_dir);
      break;
    case 's':
    case 'S':
      perna_esq[0] = inverte_r(perna_esq[0]);
      inverte_t(perna_esq);
      break;
    case 'e':
    case 'E':
      braco_dir[0] = inverte_r(braco_dir[0]);
      inverte_t(braco_dir);
      break;
    case 'w':
    case 'W':
      braco_esq[0] = inverte_r(braco_esq[0]);
      inverte_t(braco_esq);
      break;

  }
  glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
  glutInit(&argc , argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (50 ,100);
  glutInitWindowSize (600 ,600);
  glutCreateWindow ("Primeiro programa usando OpenGL");
  init();
  glutDisplayFunc (desenha);
  glutKeyboardFunc(Keyboard);
  glutMainLoop ();
  return 0;
}