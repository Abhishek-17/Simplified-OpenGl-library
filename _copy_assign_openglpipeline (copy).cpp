#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#include<cmath>
#define	index(r,c)	 (c*4+r)
#define	rindex(r,c)	 (r*4+c)
#define coss cos(curangle)
#define sinn sin(curangle)
typedef struct matrix{
    float m[4][4];
    struct matrix * next;
}matrix;
matrix *model=(matrix*)malloc(sizeof(matrix)),*projection,*view,*viewport,*answer=(matrix*)malloc(sizeof(matrix));

float curangle;
void multiply(float second[4][4],float first[4][4]){
    int i,j,k;
    float sum=0;
    for ( i = 0 ; i < 4 ; i++ )
    {
      for ( j = 0 ; j < 4 ; j++ )
      {

        for ( k = 0 ; k < 4 ; k++ )
        {
          sum = sum + first[i][k]*second[k][j];
        }

        answer->m[i][j] = sum;
        sum = 0;
      }
    }


}
void update(float m[4][4],float answer[4][4]){
    int i,j;
    for(i=0;i<4;i++)for(j=0;j<4;j++)m[i][j]=answer[i][j];
}
void sglModRotate(float angle, float axisx, float axisy, float axisz){
    if(!axisx&&!axisy&&!axisz)return;
    float t=sqrt(pow(axisx,2)+pow(axisy,2)+pow(axisz,2));
    float x=axisx*1.0/t,y=axisy*1.0/t,z=axisz*1.0/t,m[16];
    curangle=angle;
  //  glMatrixMode(GL_MODELVIEW);
    float temp[4][4]={{x*x*(1-coss)+coss,x*y*(1-coss)-z*sinn,x*z*(1-coss)+y*sinn,0},
                   {y*x*(1-coss)+z*sinn,y*y*(1-coss)+coss,y*z*(1-coss)-x*sinn,0},
                   {x*z*(1-coss)-y*sinn,y*z*(1-coss)+x*sinn,z*z*(1-coss)+coss,0},
                    {0,0,0,1},
                    };
    multiply(temp,model->m);//stores the ans in answer matrix
    answer->next=model->next;
   update(model->m,answer->m);//copy  the new model matrix to the model
    int i,j;
    for(i=0;i<4;i++)for(j=0;j<4;j++)m[index(i,j)]=model->m[i][j];
    //glLoadMatrixf(m);
}

void sglModTranslate(float tx,float ty,float tz){
        float temp[4][4]={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        answer->next=model->next;
        update(model->m,anser->m);//copy  the new model matrix to the model

}

void sglModScale(float sx,float sy,float sz){
        float temp[4][4]={{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        answer->next=model->next;
        update(model->m,answer->m);//copy  the new model matrix to the model
}

void sglModPushMatrix(){
        matrix *temp=(matrix*)malloc(sizeof(matrix));
        update(temp->m,answer->m);
        temp->next=model;
        model=temp;


}
void sglModPopMatrix(){
        if(!model)return;
        matrix *t=model->next;
        free(model);
        model=t;
}

void print(float m[4][4]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++)printf("%f ",m[i][j]);
        printf("\n");
    }

}
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
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
int main(){

 /* float a[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}},b[4][4]={{2,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
   multiply(a,b);
   update(model->m);//copy  the new model matrix to the model
   answer->m[0][0]=-1;
   print(answer->m);
   print(model->m);*/
   int main(int argc, char **argv) {

	h = (node *)malloc(sizeof(node));
	h->next=NULL;
	model = (node *)malloc(sizeof(node));
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w * 2 / 3;
	int windowHeight = h * 2 / 3;

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

}
// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    sglModLoadIdentity();
//	glLoadIdentity();
    glPushMatrix();

    // Draw Box
    sglModTranslate(0.0f, 0.0f, -5.0f);
 //   glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBox(box_len);

    // Draw Ball
    glPushMatrix();
    sglModTranslate(ball_x, ball_y, 0.0f);
//    glTranslatef(ball_x, ball_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();

    // Draw Triangle
    glPushMatrix();
    glTranslatef(tri_x, tri_y, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawTriangle();
    glPopMatrix();

    glPopMatrix();
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

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
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
}
