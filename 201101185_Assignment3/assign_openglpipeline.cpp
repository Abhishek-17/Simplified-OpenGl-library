/*
Abhishek kumar
201101185*/
#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#include<cmath>
#include "sgl.h"

void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void drawTriangle2();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f;
float cx=0,cz=0;

 /* float a[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}},b[4][4]={{2,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
   multiply(a,b);
   update(model->m);//copy  the new model matrix to the model
   answer->m[0][0]=-1;
   print(answer->m);
   print(model->m);*/
int main(int argc, char **argv) {



	sglModLoadIdentity();
	sglViewLoadIdentity();
	sglViewportLoadIdentity();
	sglProjectionLoadIdentity();
	view->next=NULL;
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;
    //ww=w,hh=h;
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("CSE251_sampleCode");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);
	glutMainLoop();
	return 0;
}


// Function to draw objects on the screen
void drawScene() {

     sglModLoadIdentity();
    sglViewLoadIdentity();
	//sglViewportLoadIdentity();
	//sglProjectionLoadIdentity();
    //float angle=45.0,aspect=1.0*ww / (float)hh,znear=1.0,zfar=200.0;
   // f=1.0/tan(DEG2RAD(angle));
    //float top=znear*tan(DEG2RAD(angle*1.0/2));
  //sglProjFrustum(-aspect*top,aspect*top,-top,top,znear,zfar);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sglModPushMatrix();
    sglModTranslate(0.0f, 0.0f, -5.0f);
    // Draw Triangle
    sglLookAt(-cx,0,13-cz,0,0,0,0,1,0);
    //drawTriangle2();
    sglModTranslate(tri_x, tri_y, 0.0f);

    sglModRotate(theta, 0.0f, 0.0f, 1.0f);
    sglModScale(0.5f, 0.5f, 0.5f);
    drawTriangle();
   // sglModPopMatrix();/**/
     sglShow() ;
    sglModPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {

    // Handle ball collisions with box
    if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;

    // Update position of ball
    ball_x += ball_velx;
    ball_y += ball_vely;

    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {

   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

    //glColor3f(1,0,0);
    sglBegin(SGL_TRIANGLES);
    sglColour(0.0f, 0.0f, 1.0f);
    sglVertex(0.0f, 1.0f, 0.0f);
    sglColour(0.0f, 1.0f, 0.0f);
    sglVertex(-1.0f, -1.0f, 0.0f);
    sglColour(1.0f, 0.0f, 0.0f);
    sglVertex(1.0f, -1.0f, 0.0f);
    sglEnd();

}
void drawTriangle2(){
    sglBegin(SGL_TRIANGLES);
    sglColour(0.0f, 0.0f, 1.0f);
    sglVertex(3.0f, 0.0f, -14.0f);
    sglColour(0.0f, 1.0f, 0.0f);
    sglVertex(2.0f, -1.0f, -11.0f);
    sglColour(1.0f, 0.0f, 0.0f);
    sglVertex(4.0f, -1.0f, -11.0f);
    sglEnd();

}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring

    sglClear(0.0f, 0.0f, 0.0f);
}

// Function called when the window is resized
void handleResize(int w, int h) {

  //  glViewport(0,0,w,h);
//sglViewport(0, 0, ww, hh);
    sglViewport(0, 0, w, h);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //
    float angle=45.0,aspect=1.0*w / (float)h,znear=0.1,zfar=200.0;
   // f=1.0/tan(DEG2RAD(angle));
   float top=znear*tan(DEG2RAD(angle*1.0/2));
   sglProjFrustum(-aspect*top,aspect*top,-top,top,znear,zfar);
 //  sglProjOrtho(-aspect*top,aspect*top,-top,top,znear,zfar);
 // sglProjOrtho(-w/2,w/2,-h/2,h/2,-1,1);
   ww=w,hh=h;
  /* f=1.0;
    float m[4][4]={
    {f*1.0/aspect,0,0,0},{0,f,0,0},{0,0,1.0*(zfar+znear)/(znear-zfar),(2.0*zfar*znear)/(znear-zfar)},
   {0,0,-1,0}
    };

    oned(m);
    glLoadMatrixf(array);
   // gluPerspective(50.0f, (double)w / (double)h, 0.1, 2000.0f);
    //gluPerspective(45.0f, (float)w / (float)h, 0.1, 200.0f);
    sglProjFrustum(,znear,zfar)
    glMatrixMode(GL_MODELVIEW);
    //sglModLoadIdentity();*/

}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    else if(key=='w'||key=='W')cz+=0.1;
    else if(key=='s'||key=='S')cz-=0.1;
    else if(key=='a'||key=='A')cx-=0.1;
    else if(key=='d'||key=='D')cx+=0.1;
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
   // curangle=theta;
   // printf("theta=%f cos=%f sin=%f\n",theta,cos(DEG2RAD(theta)), sin(DEG2RAD(theta)));
}
