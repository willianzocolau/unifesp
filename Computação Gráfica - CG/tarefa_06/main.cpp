#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "vector3f.h"

void drawObject(){
  float matrix[16];
  int i,j;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(2.0,3.0,2.0);
  glRotatef(45,1,0,0);
  glRotatef(45,0,1,0);

  glBegin(GL_LINE_LOOP);
  //P1:
  glVertex3f(0.5,0.5,0.5);
  //P2:
  glVertex3f(0.5,0.5,-0.5);
  glVertex3f(0.5,-0.5,-0.5);
  glVertex3f(0.5,-0.5,0.5);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glVertex3f(-0.5,0.5,0.5);
  glVertex3f(-0.5,0.5,-0.5);
  glVertex3f(-0.5,-0.5,-0.5);
  glVertex3f(-0.5,-0.5,0.5);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(0.5,0.5,0.5);
  glVertex3f(-0.5,0.5,0.5);
  glVertex3f(0.5,0.5,-0.5);
  glVertex3f(-0.5,0.5,-0.5);
  glVertex3f(0.5,-0.5,-0.5);
  glVertex3f(-0.5,-0.5,-0.5);
  glVertex3f(0.5,-0.5,0.5);
  glVertex3f(-0.5,-0.5,0.5);
  glEnd();

  glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
  printf("\n\nTransformacao inicial= \n");
  glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ",matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");


  glPopMatrix();
}

void init(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -10, 10);
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT);     //desenha o fundo (limpa a janela)

  vector3f p1(0.5,0.5,0.5);
  vector3f p2(0.5,0.5,-0.5);
  vector3f v = p2 - p1;
  vector3f u = v.normalize2();
  float d = sqrt(u.y * u.y + u.z * u.z);
  float cos_a = u.z / d;
  float sen_a = u.y / d;
  float cos_b = d;
  float sen_b = -u.x;


  float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
  float matrix_r1[16] = {1,0,0,0,   0,cos_a,sen_a,0,    0,-sen_a,cos_a,0,    0,0,0,1};
  float matrix_r2[16] = {cos_b,0,-sen_b,0,   0,1,0,0,    sen_b,0,cos_b,0,    0,0,0,1};
  int i,j;

  glMatrixMode(GL_MODELVIEW);

  glLoadMatrixf(matrix);
  glTranslatef(-p1.x,-p1.y,-p1.z);
  glLoadMatrixf(matrix_r1); //glRotatef(45,0,0,1);
  glLoadMatrixf(matrix_r2); //glRotatef(45,0,0,1);
  glScalef(2.0,1.0,1.0);

  printf("\n\nM = \n");
  glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ",matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");


  glColor3f(1.0f, 0.0f, 0.0f);
  drawObject();
  glFlush();
}

int main(int argc, char *argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(400,400);
  glutCreateWindow("Viewing 2D");
  glutDisplayFunc(displayFunc);
  init();
  glutMainLoop();
  return 0;
}