#include <GL/glut.h>
#include <math.h>

float t=0.0;
float r=0.0;

void init(){
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(-3.0,3.0,-3.0,3.0);
}

void drawFilledSun(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  int i, x, y;
  double radius = 0.50;
  glColor3ub(255, 0, 0);
  double twicePi = 2.0 * 3.142;
//  glBegin(GL_POLYGON);
//    glVertex2f(-0.5, 0);
//    glVertex2f(-0.5, 0.5);
//    glVertex2f(-1, 0.5);
//    glVertex2f(-1, 0);
//  glEnd();
  x = 0, y = 0;
  glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
  glVertex2f(x, y); // center of circle
  for (i = 0; i <= 10000; i++)   {
    glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
    );
  }
  glEnd(); //END
  x = -1, y = 0.5;
  glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
  glVertex2f(x, y); // center of circle
  for (i = 0; i <= 10000; i++)   {
    glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
    );
  }
  glEnd(); //END
}

void desenha(){
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glTranslatef(t,0.0,0.0);
  glPushMatrix();
  //glRotatef(r,0.0,0.0,1.0);
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
  glutInitWindowPosition (50 ,100);
  glutInitWindowSize (600 ,600);
  glutCreateWindow ("Primeiro programa usando OpenGL");
  init();
  glutDisplayFunc (desenha);
  glutKeyboardFunc(Keyboard);
  //GL_Setup(600, 600);
  glutMainLoop ();
  return 0;
}