#include <GL/glut.h>
#include <GL/gl.h>

float map_X = 0;
float map_Y = 0;
float INIT_POSITION_X = 450;
float INIT_POSITION_Y = 125;
float SIZE_WINDOW_WIDTH = 800;
float SIZE_WINDOW_HEIGHT = 800;

float RED = 0.0;
float GREEN = 0.0;
float BLUE = 1.0;

float COLOR[] = {0.0, 0.0, 1.0};

void desenha(){
  glClearColor(0, 0, 0, 0); //Preto
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(COLOR[0], COLOR[1], COLOR[2]);
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

void Keyboard (unsigned char key, int x, int y){
  switch(key){
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
  glutMainLoop ();
  return 0;
}