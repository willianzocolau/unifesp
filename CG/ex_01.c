#include <GL/glut.h>
#include <GL/gl.h>

float map_X = 0;
float map_Y = 0;
float INIT_POSITION_X = 450;
float INIT_POSITION_Y = 125;

float SIZE_WINDOW_WIDTH = 800;
float SIZE_WINDOW_HEIGHT = 800;

void desenha(){
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,1.0);
  glPointSize(40.0f);
  glBegin(GL_POINTS);
  glVertex2f(map_X, map_Y);
  glEnd();
  glFlush();
}

void getPosition(float x, float y){
  float result_x = (x / (SIZE_WINDOW_WIDTH / 2.0));
  float result_y = (y / (SIZE_WINDOW_WIDTH / 2.0));

  if(result_x < 1.0)
    result_x = (1 - result_x) * (-1.0);
  else if(result_x >= 1.0)
    result_x = result_x - 1.0;

  if(result_y >= 1.0)
    result_y = (1 - result_y);
  else if(result_y < 1.0)
    result_y = 1.0 - result_y;

  map_X = result_x;
  map_Y = result_y;
}

void MouseInt (int botao, int estado, int x, int y){
  switch(botao){
    case GLUT_LEFT_BUTTON:
      if(estado == GLUT_DOWN){
        getPosition(x, y);
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if(estado == GLUT_DOWN)

      break;
  }
  glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
  glutInit(&argc , argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition (INIT_POSITION_X ,INIT_POSITION_Y);
  glutInitWindowSize (SIZE_WINDOW_WIDTH ,SIZE_WINDOW_HEIGHT);
  glutCreateWindow ("Primeiro programa usando OpenGL");
  glutDisplayFunc (desenha);
  glutMouseFunc(MouseInt);
  glutMainLoop ();
  return 0;
}