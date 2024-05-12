#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define TO_RADIAN		0.017453292519943296 

int rightbuttonpressed = 0;
int leftbuttonpressed = 0, center_selected = 0;
int shearingbuttonpressed = 0;
int reflectionbuttonpressed = 0;
float r, g, b; // Background color
float px, py, qx, qy; // Line (px, py) --> (qx, qy)
int n_object_points = 6;
float object[6][2], object_center_x, object_center_y;
float rotation_angle_in_degree;
int window_width, window_height;


void draw_axes() {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.975f, 0.025f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.975f, -0.025f);
	glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(0.025f, 0.975f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(-0.025f, 0.975f);
	glVertex2f(0.0f, 1.0f);
	glEnd();
	glLineWidth(1.0f);

	glPointSize(7.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	glPointSize(1.0f);
}
void draw_line(float px, float py, float qx, float qy) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(px, py); 
	glVertex2f(qx, qy);
	glEnd();

	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(px, py);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(qx, qy);
	glEnd();
	glPointSize(1.0f);
}

void draw_object(void) {
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 0.0f);
	for (int i = 0; i < 6; i++)
		glVertex2f(object[i][0], object[i][1]);
	glEnd();
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < 6; i++)
		glVertex2f(object[i][0], object[i][1]);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(object_center_x, object_center_y);
	glEnd();
	glPointSize(1.0f);
}

void display(void) {
	glClearColor(r, g, b, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT);

	draw_axes();
	draw_line(px, py, qx, qy);
	draw_object();
	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'r':
		r = 1.0f; g = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'g':
		g = 1.0f; r = b = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 'b':
		b = 1.0f; r = g = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case 's':
		r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case ' ':
	{
		//과제h 추가구현 선분을 기준으로 다각형의 대칭이동
		float angle = -atan((qy - py)/ (qx - px));
		float c;
		float s;
		for (int i = 0; i < n_object_points; i++) {
			object[i][0] -= px;
			object[i][1] -= py;
			
			c = cos(angle);
			s = sin(angle);
			float x = object[i][0] * c - object[i][1] * s;
			float y = object[i][0] * s + object[i][1] * c;
			object[i][0] = x;
			object[i][1] = y;
			
			object[i][1] = -object[i][1];
			
			c = cos(-angle);
			s = sin(-angle);
			x = object[i][0] * c - object[i][1] * s;
			y = object[i][0] * s + object[i][1] * c;
			object[i][0] = x;
			object[i][1] = y;

			object[i][0] += px;
			object[i][1] += py;
		}
		object_center_x = 0.0f;
		object_center_y = 0.0f;
		for (int i = 0; i < n_object_points; i++) {
			object_center_x += object[i][0];
			object_center_y += object[i][1];
		}
		object_center_x /= n_object_points;
		object_center_y /= n_object_points;
		glutPostRedisplay();
		break;
	}
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		r -= 0.1f;
		if (r < 0.0f) r = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		r += 0.1f;
		if (r > 1.0f) r = 1.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		g -= 0.1f;
		if (g < 0.0f) g = 0.0f;
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		g += 0.1f;
		if (g > 1.0f) g = 1.0f;  
		fprintf(stdout, "$$$ The new window background color is (%5.3f, %5.3f, %5.3f).\n", r, g, b);
		glutPostRedisplay();
		break;
	}
}

int prevx, prevy;
void mousepress(int button, int state, int x, int y) {
	//과제e shift와 좌클릭을 사용한 Picking
	if (button == GLUT_LEFT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_SHIFT &&state == GLUT_DOWN) {
		float tx = float(x - 375) / 250;
		float ty = -float(y - 375) / 250;
		if (px > tx - 0.03 && px<tx + 0.03 && py>ty - 0.03 && py < ty + 0.03) {
			px = tx;
			py = ty;
			leftbuttonpressed = 1;
			prevx = x;
			prevy = y;
		}
	}
	else {
		leftbuttonpressed = 0;
	}
	//과제f ALT와 우클릭을 사용한 Translation
	if (button == GLUT_RIGHT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_ALT && state == GLUT_DOWN) {
		rightbuttonpressed = 1;
		prevx = x;
		prevy = y;
	}
	else {
		rightbuttonpressed = 0;
	}
	//과제g CTRL과 우클릭을 사용한 Scaling
	if (button == GLUT_RIGHT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_CTRL && state == GLUT_DOWN) {
		center_selected = 1;
		prevx = x;
		prevy = y;
	}
	else {
		center_selected = 0;
	}
	//과제h 추가구현 shift와 우클릭을 사용한 shearing
	if (button == GLUT_RIGHT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_SHIFT && state == GLUT_DOWN) {
		shearingbuttonpressed = 1;
		prevx = x;
		prevy = y;
	}
	else {
		shearingbuttonpressed = 0;
	}

}

void mousemove(int x, int y) {
	float dx = (x - prevx) / 250.0f;
	float dy = -(y - prevy) / 250.0f;
	prevx = x;
	prevy = y;
	//과제e shift와 좌클릭을 사용한 Picking
	if (leftbuttonpressed && glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		px += dx;
		py += dy;
		glutPostRedisplay();
	}
	//과제f ALT와 우클릭을 사용한 Translation
	if (rightbuttonpressed && glutGetModifiers() == GLUT_ACTIVE_ALT) {
		for (int i = 0; i < n_object_points; i++) {
			object[i][0] += dx;
			object[i][1] += dy;
		}
		object_center_x = 0.0f;
		object_center_y = 0.0f;
		for (int i = 0; i < n_object_points; i++) {
			object_center_x += object[i][0];
			object_center_y += object[i][1];
		}
		object_center_x /= n_object_points;
		object_center_y /= n_object_points;
		glutPostRedisplay();
	}
	//과제g CTRL과 우클릭을 사용한 Scaling
	if (center_selected && glutGetModifiers() == GLUT_ACTIVE_CTRL){
		for (int i = 0; i < n_object_points; i++) {
			float cx = object_center_x - object[i][0];
			float cy = object_center_y - object[i][1];
			object[i][0] = object_center_x - cx * (1.0f+dx);
			object[i][1] = object_center_y - cy * (1.0f+dx);
		}

		glutPostRedisplay();
	}

	//과제h 추가구현 shift와 우클릭을 사용한 shearing
	//축은 무게중심 좌표의 x축을 기준으로 하였다.
	if (shearingbuttonpressed && glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		for (int i = 0; i < n_object_points; i++) {
			object[i][0] -= object_center_x;
			object[i][1] -= object_center_y;
			object[i][0] = object[i][0] + dx*object[i][1];
			object[i][1] = object[i][1];
			object[i][0] += object_center_x;
			object[i][1] += object_center_y;
		}
		object_center_x = 0.0f;
		object_center_y = 0.0f;
		for (int i = 0; i < n_object_points; i++) {
			object_center_x += object[i][0];
			object_center_y += object[i][1];
		}
		object_center_x /= n_object_points;
		object_center_y /= n_object_points;
		glutPostRedisplay();
	}
}
//과제d 마우스 휠을 사용한 Rotation
void mouseWheel(int button, int dir, int x, int y) {
	if (dir > 0) {
		rotation_angle_in_degree = 1.0f;
	}
	else {
		rotation_angle_in_degree = -1.0f;
	}
	float angle_in_radian = rotation_angle_in_degree * TO_RADIAN;
	float c = cos(angle_in_radian);
	float s = sin(angle_in_radian);

	qx -= px;
	qy -= py;

	qx = qx * c - qy * s;
	qy = qx * s + qy * c;
	qx += px;
	qy += py;

	glutPostRedisplay();
}

	
void reshape(int width, int height) {
	// DO NOT MODIFY THIS FUNCTION!!!
	window_width = width, window_height = height;
	glViewport(0.0f, 0.0f, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-window_width / 500.0f, window_width / 500.0f,  -window_height / 500.0f, window_height / 500.0f, -1.0f, 1.0f);

	glutPostRedisplay();
}


void close(void) {
	fprintf(stdout, "\n^^^ The control is at the close callback function now.\n\n");
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mousepress);
	glutMotionFunc(mousemove);
	glutReshapeFunc(reshape);
 	glutCloseFunc(close);
	glutMouseWheelFunc(mouseWheel);
}

void initialize_renderer(void) {
	register_callbacks();
	r = 250.0f / 255.0f, g = 128.0f / 255.0f, b = 114.0f / 255.0f; // Background color = Salmon
	px = -0.70f, py = -0.50f, qx = 0.0f, qy = -1.0f;
	rotation_angle_in_degree = 1.0f; // 1 degree
	
	float sq_cx = 0.55f, sq_cy = -0.45f, sq_side = 0.25f;
	object[0][0] = sq_cx + 0.5*sq_side;
	object[0][1] = sq_cy + 0.5*sq_side;
	object[1][0] = sq_cx + 0.2 * sq_side;
	object[1][1] = sq_cy + 1.5 * sq_side;
	object[2][0] = sq_cx - 0.5*sq_side;
	object[2][1] = sq_cy + 0.5*sq_side;
	object[3][0] = sq_cx - 1.5*sq_side;
	object[3][1] = sq_cy - 0.2*sq_side;
	object[4][0] = sq_cx - 0.2 * sq_side;
	object[4][1] = sq_cy - 1.5 * sq_side;
	object[5][0] = sq_cx + 1.4*sq_side;
	object[5][1] = sq_cy - 0.3*sq_side;
	object_center_x = object_center_y = 0.0f;
	for (int i = 0; i < n_object_points; i++) {
		object_center_x += object[i][0];
		object_center_y += object[i][1];
	}
	object_center_x /= n_object_points;
	object_center_y /= n_object_points;
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = TRUE;
	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char *program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 4
void main(int argc, char *argv[]) {
	char program_name[64] = "Sogang CSE4170 Simple 2D Transformations";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'r', 'g', 'b', 's', 'q'",
		"    - Special keys used: LEFT, RIGHT, UP, DOWN",
		"    - Mouse used: SHIFT/L-click and move, ALT/R-click and move, CTRL/R-click and move",
		"    - Wheel used: up and down scroll"
		"    - Other operations: window size change"
	};

	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // <-- Be sure to use this profile for this example code!
 //	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(750, 750);
	glutInitWindowPosition(500, 200);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

   // glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_EXIT); // default
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutMainLoop();
	fprintf(stdout, "^^^ The control is at the end of main function now.\n\n");
}