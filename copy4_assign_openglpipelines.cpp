#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#include<cmath>
#define	index(r,c)	 (c*4+r)

typedef struct matrix{
    float m[4][4];
    struct matrix * next;
}matrix;

typedef struct point{
    float x,y,z;
}point;

matrix *model=NULL,*projection,*view=(matrix*)malloc(sizeof(matrix)),*viewport=(matrix*)malloc(sizeof(matrix)),*answer=(matrix*)malloc(sizeof(matrix));
float curangle;
float array[16],array2d[4][4];
void print(float m[4][4]){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++)printf("%f ",m[i][j]);
        printf("\n");
    }
    printf("\n");

}
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
void oned(float m[4][4]){
    int i,j;

    for(i=0;i<4;i++)for(j=0;j<4;j++)array[index(i,j)]=m[i][j];
}
void twod(float m[16]){
    int i,j;

    for(i=0;i<4;i++)for(j=0;j<4;j++)array2d[i][j]=m[j*4+i];
}
void sglModRotate(float angle, float axisx, float axisy, float axisz){
    if(!axisx&&!axisy&&!axisz)return;
    float t=sqrt(pow(axisx,2)+pow(axisy,2)+pow(axisz,2));
    float x=axisx*1.0/t,y=axisy*1.0/t,z=axisz*1.0/t;
    float coss=cos(DEG2RAD(angle)),sinn=sin(DEG2RAD(angle));
    //curangle=angle;
  //  x=y=z=1;
   glMatrixMode(GL_MODELVIEW);
    float temp[4][4]={{x*x*(1-coss)+coss,x*y*(1-coss)-z*sinn,x*z*(1-coss)+y*sinn,0},
                   {y*x*(1-coss)+z*sinn,y*y*(1-coss)+coss,y*z*(1-coss)-x*sinn,0},
                   {x*z*(1-coss)-y*sinn,y*z*(1-coss)+x*sinn,z*z*(1-coss)+coss,0},
                    {0,0,0,1},
                    };

    multiply(temp,model->m);//stores the ans in answer matrix
   update(model->m,answer->m);//copy  the new model matrix to the model
   // print(temp);
    multiply(model->m,view->m);
    oned(answer->m);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(array);
}
void sglViewRotate(float angle, float axisx, float axisy, float axisz){
    if(!axisx&&!axisy&&!axisz)return;
    float t=sqrt(pow(axisx,2)+pow(axisy,2)+pow(axisz,2));
    float x=axisx*1.0/t,y=axisy*1.0/t,z=axisz*1.0/t;
    float coss=cos(DEG2RAD(angle)),sinn=sin(DEG2RAD(angle));
    //curangle=angle;
  //  x=y=z=1;
   glMatrixMode(GL_MODELVIEW);
    float temp[4][4]={{x*x*(1-coss)+coss,x*y*(1-coss)-z*sinn,x*z*(1-coss)+y*sinn,0},
                   {y*x*(1-coss)+z*sinn,y*y*(1-coss)+coss,y*z*(1-coss)-x*sinn,0},
                   {x*z*(1-coss)-y*sinn,y*z*(1-coss)+x*sinn,z*z*(1-coss)+coss,0},
                    {0,0,0,1},
                    };

    multiply(temp,view->m);//stores the ans in answer matrix
   update(view->m,answer->m);//copy  the new model matrix to the view
   // print(temp);
   multiply(model->m,view->m);
    oned(answer->m);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(array);

}
void sglModTranslate(float tx,float ty,float tz){
        float temp[4][4]={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        update(model->m,answer->m);//copy  the new model matrix to the model
        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);

}

void sglViewTranslate(float tx,float ty,float tz){
        float temp[4][4]={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
        multiply(temp,view->m);//stores the ans in answer matrix
        update(view->m,answer->m);//copy  the new model matrix to the model
        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);


}

void sglModScale(float sx,float sy,float sz){
        float temp[4][4]={{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        update(model->m,answer->m);//copy  the new model matrix to the modelddddddd
        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);


}

void sglModPushMatrix(){
        matrix *temp=(matrix*)malloc(sizeof(matrix));
        update(temp->m,model->m);
        temp->next=model;
        model=temp;


}
void sglModPopMatrix(){
        if(!(model))return;
        matrix *t=model->next;
        free(model);
        model=t;
     /*   oned(model->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/
}
void sglModLoadIdentity(){
        matrix * temp=model,*m=model;
        while(temp){
            m=temp->next;
            free(temp);
            temp=m;
        }
        m=(matrix*)malloc(sizeof(matrix));
        m->next=NULL;
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)m->m[i][j]=(i==j);

        model=m;
        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);


}
void sglViewLoadIdentity(){


        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)view->m[i][j]=(i==j);

        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);
}
void sglModMatrix(float mat[16]){
     twod(mat);
     multiply(array2d,model->m);
     oned(answer->m);
     int i;
     for(i=0;i<16;i++)mat[i]=array[i];

}
void sglViewMatrix(float mat[16]){
     twod(mat);
     multiply(array2d,view->m);
     oned(answer->m);
     int i;
     for(i=0;i<16;i++)mat[i]=array[i];

}
point cross(point a,point b){
    return (point){a.y*b.z-a.z*b.y,-1*(a.x*b.z-b.x*a.z),a.x*b.y-a.y*b.x};
}
void sglLookAt(float cx,float cy,float cz,float lx,float ly,float lz,float upx,float upy,float upz){
        point F=(point){lx-cx,ly-cy,lz-cz},f,up,s,u;
        float t=sqrt(pow(F.x,2)+pow(F.y,2)+pow(F.z,2));
        if(t)f=(point){F.x/t,F.y/t,F.z/t};
        t=sqrt(pow(upx,2)+pow(upy,2)+pow(upz,2));
        if(t)up=(point){upx/t,upy/t,upz/t};
        s=cross(f,up);
        u=cross(s,f);
        float temp[4][4]={
            {s.x,s.y,s.z,0},{u.x,u.y,u.z,0},{-f.x,-f.y,-f.z,0},{0,0,0,1}
        };
        multiply(temp,view->m);
        update(view->m,answer->m);
        sglViewTranslate(-cx,-cy,-cz);
        multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);

}

void sglProjFrustum(float left,float right,float bottom,float top,float near,float far){//same as gluperspective
    float a,b,c,d,e,f;
    a=(2.0*near)/(right-left);
    b=(right+left)*1.0/(right-left);
    c=2.0*near/(top-bottom);
    d=(top+bottom)*1.0/(top-bottom);
    e=-1.0*(far+near)/(far-near);
    f=-1.0*(2*far*near)/(far-near);
    float m[4][4]={{a,0,b,0},{0,c,d,0},{0,0,e,f},{0,0,-1,0}};
    glMatrixMode(GL_PROJECTION);
    oned(m);
    glLoadMatrixf(array);
}

void sglProjOrtho(float left,float right,float bottom,float top,float near,float far){
    float a,b,c,d,e,f;
    a=(2.0)/(right-left);
    b=(right+left)*1.0/(right-left);
    c=2.0/(top-bottom);
    d=(top+bottom)*1.0/(top-bottom);
    e=-2.0/(far-near);
    f=-1.0*(far+near)/(far-near);
    float m[4][4]={{a,0,0,b},{0,c,0,d},{0,0,e,f},{0,0,0,1}};
    glMatrixMode(GL_PROJECTION);
    oned(m);
    glLoadMatrixf(array);

}

void sglViewport(float llx,float lly,float width,float height){
    float a,b,c,d;
    a=(width-llx)/2.0;
    b=(width+llx)/2.0;
    c=(height-lly)/2.0;
    d=(height+lly)/2.0;
    float m[4][4]={{a,0,0,b},{0,c,0,d},{0,0,0.5,0.5},{0,0,0,1.0}};
    oned(m);
    glMatrixMode(GL_VIEWPORT);
    glLoadMatrixf(array);
    glMatrixMode(GL_MODELVIEW);
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


 /* float a[4][4]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}},b[4][4]={{2,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
   multiply(a,b);
   update(model->m);//copy  the new model matrix to the model
   answer->m[0][0]=-1;
   print(answer->m);
   print(model->m);*/
int main(int argc, char **argv) {



	sglModLoadIdentity();
	sglViewLoadIdentity();
	view->next=NULL;
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


// Function to draw objects on the screen
void drawScene() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    sglModLoadIdentity();
//	glLoadIdentity();
    sglModPushMatrix();


    // Draw Box
    sglModTranslate(0.0f, 0.0f, -5.0f);

 // glTranslatef(0.0f, 0.0f, -5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawBox(box_len);

    // Draw Ball
    sglModPushMatrix();
    sglModTranslate(ball_x, ball_y, 0.0f);
//    glTranslatef(ball_x, ball_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    sglModPopMatrix();

    // Draw Triangle
    sglModPushMatrix();
    sglModTranslate(tri_x, tri_y, 0.0f);
    sglModRotate(theta, 0.0f, 0.0f, 1.0f);
    sglModScale(0.5f, 0.5f, 0.5f);
    drawTriangle();
    sglModPopMatrix();/**/

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



    sglViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    float angle=45.0,aspect=1.0*w / (float)h,znear=0.1,zfar=200.0;
   // f=1.0/tan(DEG2RAD(angle));
   float top=znear*tan(DEG2RAD(angle*1.0/2));
   sglProjFrustum(-aspect*top,aspect*top,-top,top,znear,zfar);
   //sglProjOrtho(-aspect*top,aspect*top,-top,top,znear,zfar);
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
