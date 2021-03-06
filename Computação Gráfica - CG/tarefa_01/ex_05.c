#include <stdbool.h>
#include <GL/glut.h>
#include <GL/gl.h>

float point_init[] = {0, 0};
float point_end[] = {1, 0};
float INIT_POSITION_X = 450;
float INIT_POSITION_Y = 125;
float SIZE_WINDOW_WIDTH = 800;
float SIZE_WINDOW_HEIGHT = 800;

float RED = 0.0;
float GREEN = 0.0;
float BLUE = 1.0;

float PONTOS_T_X[] = {0.0, 0.0, 0.0};
float PONTOS_T_Y[] = {0.0, 0.0, 0.0};
float COLOR[] = {0.0, 0.0, 1.0};
bool INIT = true;
bool RETA = true;
int COUNT = 0;

void desenha(){
  if(RETA == true){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(COLOR[0], COLOR[1], COLOR[2]);
    glBegin(GL_LINES);
    glVertex2f(point_init[0], point_init[1]);
    glVertex2f(point_end[0], point_end[1]);
    glEnd();
    glFlush();
    glutPostRedisplay();
  }
  else if (COUNT == 3) {
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
     {
      glVertex2f(PONTOS_T_X[0],PONTOS_T_Y[0]);
      glVertex2f(PONTOS_T_X[1], PONTOS_T_Y[1]);
      glVertex2f(PONTOS_T_X[2], PONTOS_T_Y[2]);
    }
    glEnd();
    glFlush();
    glutPostRedisplay();
    COUNT = 0;
  }
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

  if(RETA){
    if(INIT == true) {
      point_init[0] = result_x;
      point_init[1] = result_y;
      INIT = false;
    } else {
      point_end[0] = result_x;
      point_end[1] = result_y;
      INIT = true;
    }
  }
  else if (COUNT < 3) {
    PONTOS_T_X[COUNT] = result_x;
    PONTOS_T_Y[COUNT] = result_y;
    COUNT++;
  }
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
        getPosition(x, y);
      break;
  }
  glutPostRedisplay();
}

void Keyboard (unsigned char key, int x, int y){
  switch(key){
    case 'r':
    case 'R':
      RETA = true;
      glClearColor(0, 0, 0, 0); //Preto
      glClear(GL_COLOR_BUFFER_BIT);
      break;
    case 't':
    case 'T':
      RETA = false;
      glClearColor(0, 0, 0, 0); //Preto
      glClear(GL_COLOR_BUFFER_BIT);
      break;
    case '0':
      COLOR[0] = 0.961;
      COLOR[1] = 0.961;
      COLOR[2] = 0.961;
      break;
    case '1':
      COLOR[0] = 0.502;
      COLOR[1] = 0.0;
      COLOR[2] = 0.0;
      break;
    case '2':
      COLOR[0] = 0.098;
      COLOR[1] = 0.098;
      COLOR[2] = 0.439;
      break;
    case '3':
      COLOR[0] = 0.498;
      COLOR[1] = 1.0;
      COLOR[2] = 0.831;
      break;
    case '4':
      COLOR[0] = 0.0;
      COLOR[1] = 0.392;
      COLOR[2] = 0.0;
      break;
    case '5':
      COLOR[0] = 0.282;
      COLOR[1] = 0.239;
      COLOR[2] = 0.545;
      break;
    case '6':
      COLOR[0] = 1.0;
      COLOR[1] = 0.0;
      COLOR[2] = 1.0;
      break;
    case '7':
      COLOR[0] = 1.0;
      COLOR[1] = 1.0;
      COLOR[2] = 0.0;
      break;
    case '8':
      COLOR[0] = 1.0;
      COLOR[1] = 0.0;
      COLOR[2] = 0.0;
      break;
    case '9':
      COLOR[0] = 0.0;
      COLOR[1] = 0.0;
      COLOR[2] = 0.0;
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
  glutKeyboardFunc(Keyboard);
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);
  glutMainLoop ();
  return 0;
}