/*****************************************************************************
		FILE : submit.cpp (Assignment 1)
		NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID:   161710237
		Student Name: Liu Lingyun
		Student Chinese Name: ¡ı¡Ë‘∆
		email: daoyunmaihua@163.com
*****************************************************************************/
#include <cstdio>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>
#include <string>


/*******************************************************************************
Declarations of functions
********************************************************************************/

void init(int *argc, char **argv);
void display();
void reshape(int width, int height);
void keyboard_func(unsigned char key, int x, int y);
void idle_func();
void register_callback_functions();
void draw_walls();
void adjust_by_human();
/*******************************************************************************/


/*******************************************************************************
Implementations of functions
********************************************************************************/

/*
*/
struct Settings{
	bool need_adjust;
	float width;
	float height;
	float depth;
	void out() {
		using namespace std;
		cout << "room width = " << width << ";" << endl;
		cout << "room height = " << height << ";" << endl;
		cout << "room depth = " << depth << ";" << endl;
	}
	Settings() {
		need_adjust = true;
		width = 20;
		height = 20;
		depth = 20;
	}
	void init() {
		using namespace std;
		out();
		cout << "input new width,height,depth" << endl;
		cin >> width >> height >> depth;
	}
}My;

int main(int argc, char **argv)
{
	init(&argc, argv);
	register_callback_functions();
	glutMainLoop();
}

void init(int *argc, char **argv)
{
	/*Initialization of GLUT Library */
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	// 2d
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

GLfloat light_pos0[] = { 0, 25, -10, 1 };
GLfloat light_dir0[] = { 0, -1, 0 };
GLfloat light_cutoff0 = 45;
GLfloat light_amb0[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_dif0[] = { 0.4, 0.4, 0.4, 1.0 };
GLfloat light_spc0[] = { 1.0, 1.0, 1.0, 1.0 };

void adjust_by_human() {
	std::string ans;
	My.need_adjust = false;
	while (My.need_adjust) {
		My.init();
		display();
		//My.need_adjust = false;
		std::cout << "Is this Ok" << std::endl;
		std::cin >> ans;
		if (ans == "yes") {
			My.need_adjust = false;
			My.out();
			return;
		}
	}
	display();
}

void display()
{
	// TODO
	/*int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	*/
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_walls();

	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height)
{
	// Keep the visible area width to height ratio 1
	// and make it centered
	int new_size = min(width, height);
	int left_margin = (width - new_size) / 2;
	int bottom_margin = (height - new_size) / 2;

	glViewport(left_margin, bottom_margin, (GLsizei)new_size, (GLsizei)new_size);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, 1.0, 1.0, 100.0);
	gluLookAt(0.0, 0.0, 20, 
				0.0, 0.0, 0.0, 
					0.0, 1.0, 0.0);
}

void keyboard_func(unsigned char key, int x, int y)
{
}

void idle_func()
{
}


void register_callback_functions()
{
	glutReshapeFunc(reshape);
	glutDisplayFunc(adjust_by_human);
	glutKeyboardFunc(keyboard_func);
	glutIdleFunc(idle_func);
}

void draw_walls() {
	using namespace std;
	GLfloat x = My.width / 2;
	GLfloat y = My.height / 2;
	GLfloat z = My.depth / 2;
	GLfloat points[8][3] = {
		-x, -y, z,
		x, -y, z,
		x, -y, -z,
		-x, -y, -z,
		-x, y, z,
		x, y, z,
		x, y, -z,
		-x, y, -z,
	};
	GLfloat colors[5][3] = {
		1.0, 1.0, 0.0, // bottom
		0.0, 0.6, 0.43, // left
		0.7, 0.2, 0.6, // top
		0.0, 0.6, 0.43, // right
		0.3, 0.3, 0.3 // back
	};
	int point_sequences[5][4] = {
		0, 1, 2, 3, // bottom
		0, 3, 7, 4, // left
		4, 5, 6, 7, // top
		5, 1, 2, 6, // right
		2, 6, 7, 3 // back
	};
	string names[] = {
		"bottom",
		"left",
		"top",
		"right",
		"back"
	};
	GLfloat *p,*c;
	for (int i = 0; i < 5; ++i) {
		cout << "________________________" << endl;
		cout << names[i] << endl;

		c = colors[i];
		glColor3f(c[0], c[1], c[2]);
		glBegin(GL_QUADS);
		for (int j = 0; j < 4; ++j) {
			p = points[point_sequences[i][j]];
			glVertex3f(p[0], p[1], p[2]);

			cout << p[0] << "\t" << p[1] << "\t" << p[2] << endl;
		}
		glEnd();
		cout << "*************************" << endl;
	}
}

/*******************************************************************************/