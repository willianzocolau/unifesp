#include <GL/glut.h>

GLUquadricObj *obj;

int objId = 1;
float angX = 0;
float angY = 0;
// Posição inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat ya1 = 150.0f;
GLsizei rsize = 300;

// Passo nas direções x e y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Medidas da janela
GLfloat windowWidth = 600;
GLfloat windowHeight = 600;

void init(){
     glClearColor(0.0,0.0,0.0,0.0);
     glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7,7,-7,7,-7,7);
     glPushMatrix();
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_LINE);
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
     glColor3f(0.0,0.0,1.0);

     glPopMatrix();
     glPushMatrix();

     glRotatef(90+angX,1,0,0);
     glRotatef(180+angY,0,1,0);

     switch(objId){
        case 1:
           glPushMatrix();
             glColor3f(0.0,0.0,1.0);
             glTranslatef(0,0,1.5);
             glutWireCone(3,5,500,500);
           glPopMatrix();

           glPushMatrix();
             glColor3f(1.0,1.0,1.0);
             glTranslatef(-1.1,2.2-ystep,0.5);
             glutSolidSphere(0.7, 50, 50);
           glPopMatrix();

           glPushMatrix();
             glColor3f(0.0,1.0,0.0);
             glTranslatef(-1.32,2.9-ystep,0.55);
             glutSolidSphere(0.25, 50, 50);
           glPopMatrix();

           glPushMatrix();
             glColor3f(1.0,1.0,1.0);
             glTranslatef(1.1,2.2-ystep,0.5);
             glutSolidSphere(0.7, 50, 50);
           glPopMatrix();

           glPushMatrix();
             glColor3f(0.0,1.0,0.0);
             glTranslatef(1.32,2.9-ystep,0.55);
             glutSolidSphere(0.25, 50, 50);
           glPopMatrix();

           glPushMatrix();
             glColor3f(1.0,0.0,0.0);
             glTranslatef(0,2.5-ystep,-0.5);
             glutSolidSphere(0.7, 50, 50);
           glPopMatrix();

           glPushMatrix();
             glColor3f(1.0,1.0,1.0);
             glTranslatef(0, 2.15-ystep, -2.0);
             glRotatef(50,1,0,0);
             glutSolidTorus(0.2,0.6,50,50);
           glPopMatrix();

           glColor3f(1.0,1.0,0.0);
           glutSolidSphere(3, 50, 50);
           break;
     }
     glFlush();
}

void timerFunc(int value)
{
	if(ya1 > windowHeight-rsize || ya1 < 0)
		ystep = -ystep;

	x1 += xstep;
	ya1 += ystep;

	glutPostRedisplay();
	glutTimerFunc(1,timerFunc, 1);
}

void keyboard(unsigned char key, int x, int y){
     switch (key){
        case '1' :
           objId = 1;
           break ;
        case '2' :
           objId = 2;
           break ;
        case '3' :
           objId = 3;
           break ;
        case '4' :
           objId = 4;
           break ;
        case '5' :
           objId = 5;
           break ;
        case '6' :
           objId = 6;
           break ;
        case '7' :
           objId = 7;
           break ;
        case '8' :
           objId = 8;
           break ;
        case '9' :
           objId = 9;
           break ;
        case 'a' :
           objId = 10;
           break;
        case 'b' :
           objId = 11;
           break;
        case 'c' :
           objId = 12;
           break;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void transformacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Objetos 3D - OpenGL");
     glutDisplayFunc(display);
     glutTimerFunc(10,timerFunc,1);
     glutKeyboardFunc(keyboard);
     glutSpecialFunc(transformacoes);
     init();
     glutMainLoop();
}
