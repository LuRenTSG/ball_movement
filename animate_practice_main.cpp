#include <GL\glut.h>
#include <time.h>
#include <Windows.h>
#include <iostream>
#include <math.h>
#define PI 3.1415926

//variable declare
double fps = 30;
double play_rate = 1.0;
int n = 20;
double g = 9.8;



//function declare
void display(void);
void reshape(GLsizei, GLsizei);
void mytime(int);

using namespace std;



class Ball
{
public:
	double position[2];
	double speed[2];
	double acceleration[2] = { 0.0,0.0 };
	double r = 3.0;
	void move() {
		position[0] += speed[0];
		position[1] += speed[1];
	}
	
	Ball(double* pos, double* spd, double rd) {
		Ball(pos, spd);
		r = rd;
	}



	Ball(double* pos, double* spd) {
		position[0] = pos[0];
		position[1] = pos[1];
		speed[0] = spd[0];
		speed[1] = spd[1];
	}

	Ball() {
		position[0] = 0.0;
		position[1] = 0.0;
		speed[0] = 0.0;
		speed[1] = 0.0;
	}


	void speed_up() {
		speed[0] += acceleration[0];
		speed[1] += acceleration[1];
	}
	void next_state(){
		if (position[1] <= -47 || position[1]>=47) {
			speed[1] *= -1;
		}
		else if (position[0] <= -47 || position[0] >= 47) {
			speed[0] *= -1;
		}
		else {
			speed_up();
		}
		move();
	}
	void collision() {
		speed[1] *= -1;
	}
	
};


double pos[] = { 20.0,0.0 };
double spd[] = { 1.1,2.2 };
Ball ball(pos,spd);


int main(int argc, char* argv[]) {
	
	int arg1 = 1;
	char* arg2[] = { "hello","" };
	glutInit(&arg1, arg2);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("animate test");


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1/fps*1000/play_rate, mytime, 1);
	glutMainLoop();
	

	return 0;

}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	//¦bposition¦ì¸m µe¶ê
	glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			glVertex2f(ball.r * cos(2 * i * PI / n)+ball.position[0], ball.r * sin(2 * i * PI / n)+ball.position[1]);
		}
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(-100, -53);
		glVertex2f(100, -53);
		glVertex2f(100, -63);
		glVertex2f(-100, -63);
	glEnd();
	glutSwapBuffers();
}

void mytime(int t) {
	ball.next_state();
	
	glutTimerFunc(1/fps*1000/play_rate, mytime, 0);
	glutPostRedisplay();
}

void reshape(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50,50,-50,50);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}