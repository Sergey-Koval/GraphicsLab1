#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>

float angleX=0.0, angleY=0.0;
float lx=0.0f,ly=0.0f,lz=-1.0f;
float x=0.0f,z=5.0f,y=1.0f;

void changeSize(int w, int h);
void drawAxis();
void Display(void);
void Keyboard(unsigned char key, int xx, int yy);
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Lab2");
	glutDisplayFunc(Display);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 1;
}

void changeSize(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void drawAxis(){
        glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    glEnd();
    
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
}
void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(  x,      y,   z,
			    x+lx,   y+ly,   z+lz,
			    0.0f,   1.0f,   0.0f);
    drawAxis();
	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0,0,j * 10.0);
			glutSolidSphere(1,20,20);
			glPopMatrix();
		}
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int xx, int yy) {
	float fraction = 0.1f;
	switch (key) {
		case 'h':
			angleX -= 0.03f;
			lx = sin(angleX);
			lz = -cos(angleX);
			break;
		case 'l':
			angleX += 0.03f;
			lx = sin(angleX);
			lz = -cos(angleX);
			break;
        case 'j':
			angleY -= 0.03f;
			ly = sin(angleY);
			lz = -cos(angleY);
			break;
        case 'k':
			angleY += 0.03f;
			ly = sin(angleY);
			lz = -cos(angleY);
			break;
		case 'w':
			x += lx * fraction;
			z += lz * fraction;
			break;
		case 's':
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
    glutPostRedisplay();
	std::cout << 
	"Pos:\t\t" << x << " ; " << y << " ; " << z
	 << std::endl <<
	 "LookDir:\t" << angleX << " ; " << angleY << std::endl << std::endl;
}