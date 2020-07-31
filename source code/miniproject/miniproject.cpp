
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include "glut.h"
#include "gsrc.h"

#define PI 3.141592654
#define WIN_POSX   100
#define WIN_POSY   100
#define WIN_WIDTH  500 
#define WIN_HEIGHT 500

int    option = 1;                   // specify whether the animation is uniform, accelerating or decelerating
double exponent = 6.0;                 // control the rate of change of acceleration/decleration
double t_prev;                   // previous time elapsed
double rleg_1 = 0, rleg_2 = -90;
double leg_1 = 0, leg_2 = -90;
const float Xs = 300;
const float Ys = 300;
const float Zs = 300;

double height, theta, phi, phi1, psi;			 // rotation angles of robot, lower-and-upper arm, upper arm respectivley
GLUquadricObj *pObj1, *pObj2, *pObj3;	// quadric objects to store properties of the quadric mesh

//texture
GLuint texGround;
GLuint Wall;
GLuint ground;

void cube()//2*2*2cube
{
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glutSolidCube(2);
	glPopMatrix();
}

void draw_body(void)
{
	glPushMatrix();
	glTranslatef(0, -4, 0);
	glScalef(4, 25, 4);
	cube();
	glPopMatrix();
}

void draw_head(void)
{
	glPushMatrix();
	glScalef(5.0, 5.0, 5.0);
	cube();
	glPopMatrix();
}

void draw_upper_arm(void)	
{
	glPushMatrix();
	glScalef(15.0, 2.5, 2.5);
	cube();
	glPopMatrix();
}

void draw_lower_arm(void)	
{
	glPushMatrix();
	glScalef(15.0, 2.5, 2.5);
	cube();
	glPopMatrix();
}

void draw_upper_leg(void)	
{
	glPushMatrix();
	glScalef(2.5, 25.0, 2.5);
	cube();
	glPopMatrix();
}

void draw_lower_leg(void)	
{
	glPushMatrix();
	glScalef(2.5, 25.0, 2.5);
	cube();
	glPopMatrix();
}

//draw the robot
void drawscene(void)	
{

	//glColor3f(0.0, 0.8, 0.82);
	draw_body();
	glPushMatrix();
	glTranslatef(0.0, 50.0, 0.0);		// M_(head to base)
	//glColor3f(0.0, 0.8, 0.82);
	draw_head();
	glPopMatrix();

	//leftarm
	glPushMatrix();
	glTranslatef(10.0, 45.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper and lower arm by phi degrees
	//glColor3f(0.0, 0.8, 0.82);
	draw_lower_arm();
	glTranslatef(30.0, 0.0, 0.0);		// M_(lower arm to base)
	//glRotatef(phi, 0.0, 0.0, 1.0);
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper arm by phi degrees
	//glColor3f(0.0, 0.8, 0.82);
	draw_upper_arm();
	glPopMatrix();

	//rightarm
	glPushMatrix();
	glScalef(-1, 1, 1);
	glTranslatef(10.0, 45.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper and lower arm by phi degrees
	//glColor3f(0.0, 0.8, 0.82);
	draw_lower_arm();
	glTranslatef(30.0, 0.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper arm by phi degrees
	//glColor3f(0.0, 0.8, 0.82);
	draw_upper_arm();
	glPopMatrix();

	//legs
	glPushMatrix();
	glScalef(1, -1, 1);
	glTranslatef(-10.0, 10.0, 0.0);		//M_(leg to base)
	glRotatef(leg_1, 1.0, 0.0, 0.0);		//angle
	//glColor3f(0.0, 0.8, 0.82);
	draw_upper_leg();
	glTranslatef(0, 50, 0);
	glRotatef(leg_2, 1, 0, 0);	
	//glColor3f(0.0, 0.8, 0.82);
	draw_lower_leg();
	glPopMatrix();

	glPushMatrix();
	glScalef(1, -1, 1);
	glTranslatef(10.0, 10.0, 0.0);
	glRotatef(-rleg_1, 1.0, 0.0, 0.0);
	//glColor3f(0.0, 0.8, 0.82);
	draw_upper_leg();
	glTranslatef(0, 50, 0);
	glRotatef(-rleg_2, 1, 0, 0);				
	//glColor3f(0.0, 0.8, 0.82);
	draw_lower_leg();
	glPopMatrix();
	//glutSwapBuffers();
}

//draw the shadow
void drawshadow(void)	// Setup perspective projection and the rotation
{
	draw_body();
	glPushMatrix();
	glTranslatef(0.0, 50.0, 0.0);		// M_(head to base)
	draw_head();
	glPopMatrix();

	//leftarm
	glPushMatrix();
	glTranslatef(10.0, 45.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper and lower arm by phi degrees
	draw_lower_arm();
	glTranslatef(30.0, 0.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi1, 0.0, 0.0, 1.0);      // rotate upper arm by phi degrees
	draw_upper_arm();
	glPopMatrix();

	//rightarm
	glPushMatrix();
	//glScalef(-1, 1, 1);
	glTranslatef(10.0, 45.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi, 0.0, 0.0, 1.0);      // rotate upper and lower arm by phi degrees
	draw_lower_arm();
	glTranslatef(30.0, 0.0, 0.0);		// M_(lower arm to base)
	glRotatef(phi1, 0.0, 0.0, 1.0);      // rotate upper arm by phi degrees
	glPopMatrix();

	//legs
	glPushMatrix();
	glTranslatef(-10.0, -70.0, 0.0);		//M_(leg to base)
	glRotatef(leg_1, 1.0, 0.0, 0.0);		//angle
	draw_upper_leg();
	glTranslatef(0, -35, 0);
	glRotatef(leg_2, 1, 0, 0);	
	draw_lower_leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10.0, -70.0, 0.0);
	glRotatef(rleg_1, 1.0, 0.0, 0.0);
	draw_upper_leg();
	glTranslatef(0, -35, 0);
	glRotatef(rleg_2, 1, 0, 0);				
	draw_lower_leg();
	glPopMatrix();
	//glPopMatrix();
}

// power_of_two used to determine whether a whole is a power of 2
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// Open the file, if it fails, return
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// Read the width and height of the image in the file
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	// Calculate the number of bytes occupied by each row of pixels
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// Allocate memory based on the total number of pixels
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// Read pixel data
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// Compatible with older versions
	// If the image width and height exceed the maximum value specified by OpenGL, also zoom
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // Specifies the new size to be a square with long sides after scaling
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// Calculate the number of bytes and total bytes required for each row
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// Allocate memory
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// Pixel scaling
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// Release the original pixel data
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// Assign a new texture number
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// Bind new textures, load textures and set texture parameters
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //Restore the previous texture binding
	free(pixels);
	fclose(pFile);
	return texture_ID;
}

//Set the light source
void light(void) {

	GLfloat color1[] = { 0.9, 0.9, 0, 1.0 };
	GLfloat color2[] = { 0.8, 0.8, 0.8, 1.0 };
	glEnable(GL_LIGHTING);  // activate lighting routines
	//glLight* (lightName, lightProperty, propertyValue);
	GLfloat  lightPos[] = { Xs, Ys, Zs, 1.0 };    // point source; the last entry is 1.0
	GLfloat  lightdirection[] = { 0.0, 0.0, 0.0, 0.0 };    // light direction; the last entry is 0.0
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);  // v for vector
	glLightfv(GL_LIGHT0, GL_SPECULAR, color1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color2);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
}

//draw body and shadow
void draw_all(void) {

	
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);	//viewport is by default the display window
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, double(viewport[2]) / viewport[3], 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(200, 200, 400, 0, 0, 0, 0, 1, 0);
	glMultMatrixf(gsrc_getmo());	//get the rotation matrix from the rotation user-interface

	//  Enable Z buffer method for visibility determination. 
	//  Z buffer code starts

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Z buffer code ends 


	glClearColor(1.0, 1.0, 1.0, 0.0);	//Set display-window color to white
	glClear(GL_COLOR_BUFFER_BIT);

	Wall = load_texture("wall.bmp");
	ground = load_texture("ground.bmp");
	//glBindTexture(GL_TEXTURE_2D,Wall);
	//glEnable(GL_NORMALIZE);   // normalize normals
	glEnable(GL_TEXTURE_2D);		// texture

	// draw wall
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Wall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -135.0f, 300.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 300.0f, 300.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 300.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f,-135.0f, -100.0f);
	glEnd();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -135.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 300.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(300.0f, 300.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(300.0f, -135.0f, -100.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, ground);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -135.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, -135.0f, 300.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(300.0f, -135.0f, 300.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(300.0f, -135.0f, -100.0f);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

	GLfloat M[16]; // OpenGL is in column major format though C is in row major format

	//draw the shadow in the ground
	for (int i = 0; i < 16; i++)
	M[i] = 0;
	M[0] = M[5] = M[10] = 1;
	M[7] = -1.0 / (Zs + 134);
	glColor3f(0.0, 0.8, 0.82);
	drawscene(); // draw the objects
	glPushMatrix(); // save state
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(Xs, Ys, Zs); // Mwc←s
	glMultMatrixf(M); // perspective project
	glTranslatef(-Xs, -Ys, -Zs); // Ms←wc
	glColor3f(0, 0, 0); // set 𝑘𝑎 = 𝑘𝑑 = 𝑘𝑠 = 0 if you are using lighting model
	//drawshadow();
	drawscene(); // draw the shadows
	glPopMatrix();	// restore state

	//draw the shadow in the left wall
	for (int i = 0; i < 16; i++)
		M[i] = 0;
	M[0] = M[5] = M[10] = 1;
	M[3] = -1.0 / (Zs + 99);
	glPushMatrix(); // save state
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(Xs, Ys, Zs); // Mwc←s
	glMultMatrixf(M); // perspective project
	glTranslatef(-Xs, -Ys, -Zs); // Ms←wc
	glColor3f(0, 0, 0); // set 𝑘𝑎 = 𝑘𝑑 = 𝑘𝑠 = 0 if you are using lighting model
	//drawshadow();
	drawscene(); // draw the shadows
	glPopMatrix();	// restore state

	//draw the shadow in the right wall
	for (int i = 0; i < 16; i++)
		M[i] = 0;
	M[0] = M[5] = M[10] = 1;
	M[11] = -1.0 / (Zs+99);
	glPushMatrix(); // save state
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(Xs, Ys, Zs); // Mwc←s
	glMultMatrixf(M); // perspective project
	glTranslatef(-Xs, -Ys, -Zs); // Ms←wc
	glColor3f(0, 0, 0); // set 𝑘𝑎 = 𝑘𝑑 = 𝑘𝑠 = 0 if you are using lighting model
	//drawshadow();
	drawscene(); // draw the shadows
	glPopMatrix();	// restore state
	glutSwapBuffers();
}



//Take symbol
double	sgn(double a)
{
	if (a > 0)
		return 1.0;
	else if (a < 0)
		return -1.0;
	else
		return 0.0;
}
//(-(x-1)^6+1)*sgn[sin(PI*x/2)]
void animate(void) {
	double	t;
	double swing_angle = 30.0;                  // 90 degrees
	double swing_time = 1000.0;				 // 10000 ms

	t = glutGet(GLUT_ELAPSED_TIME) - t_prev;            // return elapsed time in ms since the last call  

	if (true)
	{
		if (option == 0)
			phi = swing_angle * t / swing_time;
		else if (option == 1)
			phi = swing_angle * (1 - pow(cos(PI * t / (2 * swing_time)), exponent));
		else
			phi = swing_angle * pow(sin(PI * t / (2 * swing_time)), exponent);
	}
	else
		phi = swing_angle;                     // stop at swing_angle

	height = 1 * phi;
	phi1 = phi;
	leg_1 = phi;
	leg_2 = phi;
	rleg_1 = phi;
	rleg_2 = phi;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                                      // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Set display mode.
	glutInitWindowPosition(WIN_POSX, WIN_POSY);                // Set display-window position at (WIN_POSX, WIN_POSY) 
																// where (0, 0) is top left corner of monitor screen
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);		           // Set display-window width and height.
	glutCreateWindow("A Running Man");							// Create display window.

	light();//Set the light
	//glutDisplayFunc(drawscene);
	glutDisplayFunc(draw_all);	//Put everything you wish to draw in drawscene.

	glutIdleFunc(animate);//Set the animation

	glEnable(GL_FOG);	//Set the fog
	GLfloat Color[4] = { 0.7, 0.7, 0.7, 1.0 };
	glFogfv(GL_FOG_COLOR, Color);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.2);
	glFogf(GL_FOG_START, 0.5);
	glFogf(GL_FOG_END, 800.0);
	//////////////////////////////////////////////////////////////////
	// Register mouse-click and mouse-move glut callback functions
	// for the rotation user-interface.
	// 
	//glutMouseFunc(gsrc_mousebutton);
	//glutMotionFunc(gsrc_mousemove);
	//
	//////////////////////////////////////////////////////////////////
	glutMainLoop();			               // Display everything and wait
	return 0;
}