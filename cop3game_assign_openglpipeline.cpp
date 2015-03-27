#include<stdio.h>
#include<stdlib.h>
#include <GL/glut.h>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#include<cmath>
#define	index(r,c)	 (c*4+r)

//----------------------------------------------------------------------------------------------------------------------------------
/*
Abhishek kumar
201101185
*/
#include <iostream>
#include <time.h>
#define PI 3.141592653589
#define d2r(deg) (deg * PI / 180)
#define rd (dirn*1.0*acos(-1)) /180
#define lrd (ldirn*1.0*acos(-1)) /180
//-----------------------------------------------------------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct tiles{
    double x,y,z;
}tiles;
typedef struct points{
    float x,y,z;
}points;
typedef struct cameras{
    double a,b,c,d,e,f,g,h,i;
}cameras;
typedef struct controls1{
    int a,b,c,d;
}controls1;
GLUquadricObj *pp;
void initRendering();
void getPointsInWorld(double x,double y);
void ff(int x, int y);
void drawtile();
void handleResize(int w, int h);
double theta[6]={0,0,0,0,0,0};
double objx,objy,objz;
int w,h,movefl[100],fl,ct=0,p=0,vm=0,drop,spfl=1,lkey=0,flv=0,jump=0,rise=1,lct,tvt,illuminate,win; //movefl: which tile will move nd which will not ct:current tile, vm:viewing mode 0:first person 1: tower view   //drop: bot has landed on blank spot or out of boundary  spfl:flag whether motion keys are kept pressed or not  lkey: last special key tvt:tile view tile
double rs=2.0f,tw,sz=1.5,zz=2,tz[100],ts[100],v=0,vmax=.06,vmin=0,accn=0.0035,desc=0.00,f,hh=2.6,rr,rh,rot=15.0,d=2.0,lth;// ts:tile speed v:velocity a:accn f: friction rr:robot radius rh : robot height rs rotation speed of robot/humanoid
tiles tile[100],hp,color[100],colors1[5],topcolor[100],roll; //hp: humanoid position
double dirn=0.0,ldirn=0,zoom=1,zf=0.01,cx,cz,rolla=0,yaw=0;//rollangle
float dx=0,dy=0,mousex=0,mousey=0,ang;
cameras camera;
controls1 control;//controls
//dsd





void updatetile(){
    if(hp.x<tile[0].x||hp.x>tile[9].x+2*sz||hp.z<tile[99].z-2*sz||hp.z>tile[0].z){drop=1;return;}
    int x,z;
    x=(hp.x-tile[0].x)/(2*sz);
    z=(-hp.z+tile[0].z)/(2*sz);
    ct=(10*z+x);
    if(!movefl[ct]&&!jump){drop=1;}//bot landed at wrong place .. will fall now.. :(
    ang=(hp.z-tile[0].z)*2;
    if(ct==99){//won
        win=1;
        exit(0);
      //  if((hp.y<tile[99].y+zz*1.9)&&rise2){hp.y+=0.05,accn=0.007;}else{if(rise2&&hp.y<tile[ct].y)drop=1,rise=1,jump=0,accn=0.0035;else rise=0;if(hp.y>tile[ct].y&&!rise)hp.y-=0.05;if(hp.y<=tile[ct].y&&!rise)hp.y=tile[ct].y,rise=1,jump=0,accn=0.0035;}}

    }

}
void updatecamera(){
    if(drop&&(vm!=1)){camera=(cameras){hp.x,hp.y+hh,hp.z,tile[ct].x,tile[ct].y,tile[ct].z,1.0,0.0,0.0};return;}
    if(vm==0){//first person
        camera=(cameras){hp.x,hp.y+hh,hp.z,hp.x+2*d*cos(rd),tile[ct].y,hp.z-2*d*sin(rd),0.0,1.0,0.0};
    }
    else if(vm==2){//third person
        camera=(cameras){hp.x-d*cos(rd)*2,hp.y+hh*2,hp.z+d*sin(rd)*2,hp.x+d*cos(rd)*2,tile[ct].y,hp.z-d*sin(rd)*2,0.0,1.0,0.0};
    }
    else if(vm==1){//tower mode
      //  fl=1;
        camera=(cameras){tile[5].x,tile[0].y+25,tile[5].z+15,tile[5].x,tile[0].y,tile[5].z-10*sz,0,1,0};
    }
    else if(vm==3){//tile view

            camera=(cameras){tile[tvt].x,tile[tvt].y+hh,tile[tvt].z,hp.x,hp.y+hh/2,hp.z,0,1,0};
    }

    else if(vm==4){//helicopter view
      //  return;

             camera=(cameras){tile[5].x+cx,(tile[0].y+25)*zoom,(tile[5].z+15)*zoom+cz,tile[5].x,tile[0].y+yaw,tile[5].z-10*sz,roll.x,roll.y,0};

    }

}
void handleKeypress2(int key, int x, int y) {

    //printf("vm=%d dirn=%lf ct=%d \n",vm,dirn,ct);
   // modifykeys(key);

    if(drop)return;
    //spfl=0;
    tiles temp=hp;
    if(vm!=1&&vm!=4){

        if((key==GLUT_KEY_RIGHT||key==GLUT_KEY_LEFT)&&v){desc=0.0005;}
        // else{lkey=key;}
         if((lkey==GLUT_KEY_UP&&key==GLUT_KEY_DOWN)||!lkey){if(v){desc=0.0005;return;}else {lkey=key;desc=0.0004;}}
         else if((key==GLUT_KEY_UP&&lkey==GLUT_KEY_DOWN)||!lkey){if(v){desc=0.0005;return;}else {lkey=key;desc=0.0004;}}
         else if(key==lkey)desc=0.0004;

         if(v==0){ldirn=dirn;}
          if(ldirn!=dirn&&v)return;
          //else if((lkey==GLUT_KEY_UP&&key==GLUT_KEY_DOWN)||(lkey==GLUT_KEY_DOWN&&key==GLUT_KEY_UP))
          // printf("hk==2 %lf  ldirn=%lf dirn=%lf desc=%lf lkey=%d key=%d desc=%f\n",v,ldirn,dirn,desc,lkey,key,desc);
        if(key==GLUT_KEY_UP){
                if(v<vmax)v+=accn;
                hp.x+=v*cos(rd);
                hp.z+=v*sin(rd)*-1;

                }
        else if(key==GLUT_KEY_DOWN){

                if(v<vmax)v+=accn;
                hp.x-=v*cos(rd);
                hp.z-=v*sin(rd)*-1;
        }
        else if(key==GLUT_KEY_RIGHT){
                dirn-=90;
               if(dirn>360)dirn-=360;
               else if(dirn<0)dirn+=360;
        }
        else if(key==GLUT_KEY_LEFT){
                dirn+=90;
                if(dirn>360)dirn-=360;
               else if(dirn<0)dirn+=360;
              //if(dirn==360)dirn=0.0;
        }
        else return;
    }

     else if(vm==1||vm==4){//tower mode + helicoptermode
        // printf("jump=%d ct=%d rise=%d y=%lf\n",jump,ct,rise,hp.y);
      // printf("hk==2 %lf flv=%d ldirn=%lf dirn=%lf desc=%lf key=%d lrkey=%d\n",v,flv,ldirn,dirn,desc,key,lrkey);
                if(v==0){lkey=key;ldirn=dirn;desc=0.0004;}

                if(key==GLUT_KEY_UP){if(dirn!=90)dirn=90; else { if(ldirn!=dirn&&v)return; if(v<vmax)v+=accn;hp.z+=v*sin(rd)*-1;}}
                else if(key==GLUT_KEY_DOWN){if(dirn!=270)dirn=270;else {  if(ldirn!=dirn&&v)return; if(v<vmax)v+=accn;hp.z-=v*sin(rd);}}
                else if(key==GLUT_KEY_RIGHT){if(dirn!=0)dirn=0; else {  if(ldirn!=dirn&&v)return; if(v<vmax)v+=accn;hp.x+=v*cos(rd);}}
                else if(key==GLUT_KEY_LEFT){if(dirn!=180)dirn=180; else{  if(ldirn!=dirn&&v)return; if(v<vmax)v+=accn;hp.x+=v*cos(rd);}}
            if(ldirn!=dirn)desc=0.0005;
                //else return;

     }
    int lct=ct;
     updatetile();
   if(lct!=ct&&movefl[ct]==3){//new tile is a block
        if(temp.y<tile[ct].y){v=0,hp=temp;updatetile();}

   }
     updatecamera();
        //return;
    rot*=-1;


}
void handlekeypress3(int key){
    tiles temp=hp;
        if(drop)return;
       if(vm!=4&&vm!=1){

        if(key==GLUT_KEY_UP){

                hp.x+=v*cos(lrd);
                hp.z+=v*sin(lrd)*-1;

                }
        else if(key==GLUT_KEY_DOWN){

                hp.x-=v*cos(lrd);
                hp.z-=v*sin(lrd)*-1;
        }

    }
     else if(vm==1||vm==4){
   //   printf("hk==3 %lf flv=%d ldirn=%lf dirn=%lf desc=%lf key=%d\n",v,flv,ldirn,dirn,desc,key);
                if(key==GLUT_KEY_UP){  hp.z+=v*sin(lrd)*-1;}
                else if(key==GLUT_KEY_DOWN){hp.z-=v*sin(lrd);}
                else if(key==GLUT_KEY_RIGHT){hp.x+=v*cos(lrd);}
                else if(key==GLUT_KEY_LEFT){ hp.x+=v*cos(lrd);}
                else return;

     }
      int lct=ct;
     updatetile();
   if(lct!=ct&&movefl[ct]==3){//new tile is a block
        if(temp.y<tile[ct].y){v=0,hp=temp;updatetile();}

   }

     updatecamera();
    // rot*=-1;
}

void drawhumanoid(){
    //hp.y=tile[ct].y;
    sglModPushMatrix();
    if(!drop)sglModTranslate(hp.x,hp.y,hp.z);
    else sglModTranslate(hp.x,hp.y,hp.z);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    sglModRotate(-90.0f, 1.0f, 0.0f, 0.0f);
    /*  if(dirn==90.0||dirn==270.0){ //legs

            if(dirn==90.0)sglModRotate(90.0f, 0.0f, 0.0f, 1.0f);
            else sglModRotate(-90.0f, 0.0f, 0.0f, 1.0f);
      }
      if(dirn==180.0)sglModRotate(180.0f, 0.0f, 0.0f, 1.0f);
      */
      sglModRotate(dirn, 0.0f, 0.0f, 1.0f);
            sglModPushMatrix();
           // glColor3f(1.0f, 1.0f, 0.0f);
           glColor3f(1.0 , 0.498039 ,0.0);
            sglModTranslate(0,0.06,0.4);
            sglModPushMatrix();
            sglModRotate(-180, 0.0f, 1.0f, 0.0f);
            sglModRotate(rot, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic,0.03f,0.03f,0.4,50,50);
            sglModPopMatrix();
            sglModTranslate(0,-0.06*2,0);
            sglModRotate(-180, 0.0f, 1.0f, 0.0f);
            sglModRotate(-rot, 0.0f, 1.0f, 0.0f);
            glColor3f(0.5f, 0.0f, 1.0f);
           gluCylinder(quadratic,0.03f,0.03f,0.4,50,50);
            sglModPopMatrix();

    glColor3f(1.0f, 1.0f, 0.0f);
    sglModTranslate(0,0.0,0.4);
    gluCylinder(quadratic,0.3f,0.2f,0.2f,50,50);
     sglModTranslate(0,0.0,0.2);
     glColor3f(0.0f, 0.0f, 0.0f);
    gluCylinder(quadratic,0.2f,0.2f,0.4f,50,50); //body
   // glutWireSphere(GLdouble radius,GLint slices, GLint stacks);

   if(!drop) sglModTranslate(0,0.0,0.1);
   else sglModTranslate(0,0.0,0.6);
            //arms
            glColor3f(1,0,0);
            sglModPushMatrix();
            sglModTranslate(0,0.2+0.03,0);
            sglModTranslate(0,0,0.3);
            sglModPushMatrix();

            sglModRotate(-180, 0.0f, 1.0f, 0.0f);
            sglModRotate(rot, 0.0f, 1.0f, 0.0f);
           // sglModTranslate(0,0.3,0);

            gluCylinder(quadratic,0.03f,0.03f,0.3f,50,50);
            sglModPopMatrix();

            sglModTranslate(0,-0.40-0.03-0.03,0);
             sglModPushMatrix();
             //
            sglModRotate(-180, 0.0f, 1.0f, 0.0f);
            sglModRotate(-rot, 0.0f, 1.0f, 0.0f);
            gluCylinder(quadratic,0.03f,0.03f,0.3f,50,50);
             sglModPopMatrix();
            sglModPopMatrix();
             glColor3f(0.0 ,1.0 ,1.0);

    if(!drop)sglModTranslate(0,0.0,0.3);
    else sglModTranslate(0,0.0,-0.2);
    gluCylinder(quadratic,0.07f,0.07f,0.2f,50,50); //neck
    sglModTranslate(0,0.0,0.4);
    glutSolidSphere(0.2,50, 50);//head
    glColor3f(1,0,0);
    sglModPushMatrix();
    sglModTranslate(0.15,-0.04,0.03);
    glutSolidSphere(0.06,50, 50);
    sglModPopMatrix();
    sglModTranslate(0.15,0.04,0.03);
    glutSolidSphere(0.06,50, 50);
    sglModPopMatrix();
   // sglModPopMatrix();
    //glBegin(GL_LINES);
    //glVertex3f(hp.x+sz,tile[ct].y,hp.z-sz);
    //glVertex3f( hp.x+sz,tile[ct].y+1,hp.z-sz);
   // glEnd();

}
void update(int value){

    updatecamera();
    updatetile();

    if(!drop&&!jump){if((movefl[ct]==2&&hp.y<tile[ct].y&&lct!=ct)||(lct!=ct&&(movefl[lct]==2&&hp.y+0.3<tile[ct].y)))drop=1;else if(hp.y>tile[ct].y&&movefl[ct]!=2){hp.y-=0.1;if(hp.y<tile[ct].y)hp.y=tile[ct].y;}else{hp.y=tile[ct].y;}}
    lct=ct;
    glutTimerFunc(20, update, 0);
}

void handleKeypress1(unsigned char key, int x, int y) {
    //int k;double dd,m,a,l,r;
    if (key == 27) {
        exit (0);
    }

    /*
         90.0
    180.0       0.0
         270.0
    */

    if(key=='j'||key=='J'){
        if(drop)return;
        jump=1;
        lth=tile[ct].y;
    }
    if(key=='i'||key=='I'){
        if(illuminate)illuminate=0;
        else if(!illuminate)illuminate=1;
       // printf("sdfs %d\n",illuminate);
    }
     if(key==86||key==118){//V or v : toggle view mode
       // if(v==4)sglModPopMatrix();
        vm=(vm+1)%5;//vm=1 tower mode

       if(vm==4){roll.x=0;roll.y=1;roll.z=0;}
       else if(vm==0||vm==2||vm==3)desc=0.0004;
        if(vm!=2&&vm!=0){int i; i=(dirn/90.0); dirn=i*90.0;}
        updatecamera();
     //   printf("%d\n",vm);
    }
    //else if(key==97)
       // printf("%f\n",hp.z-2*sz);
   // if(drop)return;
    //else if(key=='p'||key=='P'){
        //printf("%lf %f %lf\n",objx,objy,objz);
   // }
   else if(key==82||key==114)//r or R rotate camera right in vm=0 first person mode
        {
           if(vm!=1&&vm!=4) {dirn+=rs*-1;
                    if(dirn>360)dirn-=360;
               else if(dirn<0)dirn+=360;}
             //  printf("%f %f %f\n",hp.x,hp.y,hp.z);
            else if(vm==4){
                rolla-=2;
                roll.y=cos(d2r(rolla));
                roll.x=sin(d2r(rolla));
            }
        }
    else if(key==76||key==108)//l or L
    {
        if(vm!=1&&vm!=4){dirn+=rs;
                if(dirn>360)dirn-=360;
               else if(dirn<0)dirn+=360;
        }
        else if(vm==4){
            rolla+=2;
            roll.y=cos(d2r(rolla));
            roll.x=sin(d2r(rolla));
        }
    }
    else if((key==83||key==115)&&drop){//s or S : respawn
        hp=tile[0];
        hp.x+=sz,hp.z-=sz;
        ct=0;
        drop=0;
        dirn=0.0;
        v=0;

    }
     else if(key=='w'||key=='W'){
            if(vm==3){if(tvt<90)tvt+=10;}//vm=3 tile mode
            else if(vm==4){//move helicopter camera
                cz-=zf*30;
            }
        }
    else if(key=='s'||key=='S'){
            if(vm==3){if(tvt>9)tvt-=10;}
            else if(vm==4){
                cz+=zf*30;
            }
        }
    else if(key=='a'||key=='A'){
            if(vm==3){if(tvt%10)tvt-=1;}
            else if(vm==4){
                cx-=zf*50;
            }
        }
    else if(key=='d'||key=='D'){
           if(vm==3){if((tvt+1)%10)tvt+=1;}
           else if(vm==4){
                cx+=zf*50;
            }
        }
    else if(key=='<'||key==','){
        if(vm==4)
        yaw=yaw-0.8;
    }
     else if(key=='>'||key=='.'){
        if(vm==4)
        yaw=yaw+0.8;
    }


}
void mouse(int button, int state, int x, int y)
{
   // Wheel reports as button 3(scroll up) and button 4(scroll down)

   if(button==3){//zoom in/up
        zoom-=zf;
   }
   else if(button==4){//zoom out/down
        zoom+=zf;
   }
 //  else{  // normal button event
 //      printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
 //  }
}
void spot(double a, double b, double c, double d, double e, double f){
    /*
    a, b and c -- x, y and z co-ordinates for light position
    d, e and f -- x, y and z co-ordinates for spot light position
    */
    GLfloat mat_specular[] = { 0.3, 1.0, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { a,b,c, 1.0 };
    GLfloat spotDir[] = { d,e,f };
    glClearColor (0.5, 0.5, 0.5, 0.0);
    glShadeModel (GL_SMOOTH);
    glLightfv(GL_LIGHT0,GL_SPECULAR,mat_specular);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    // Definig spotlight attributes
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,95.0);
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,2.0);
    glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
   // return 0;
}
void drawspotlight(){
  //  int i;

    sglModTranslate(tile[99].x+3*sz,tile[0].y-2*sz,tile[99].z-3*sz);
    sglModRotate(ang,0,1,0);
    glPushAttrib(GL_ENABLE_BIT);
    glLineWidth(2.5);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0, 11.2, 0);

    glEnd();

   glColor3f(1,0,0);
   sglModTranslate(-sz*.1,12,sz*.5);

    sglModRotate(45,0,1,0);
     sglModRotate(135,0,0,1);
          glColor3f(1,1,0);
    glBegin(GL_QUADS);

        glVertex3f( -sz, 0,0); //top face
        glVertex3f(-sz,0,-sz);
        glVertex3f(sz,0,-sz);
        glVertex3f(sz,0,0); //if(

    glEnd();

    glPopAttrib();

}

points map(points a){
    points t;
    multiply(model->m,view->m);

    t.x=(answer->m[0][0]*a.x+answer->m[0][1]*a.y+answer->m[0][2]*a.z);
    t.y=(answer->m[1][0]*a.x+answer->m[1][1]*a.y+answer->m[1][2]*a.z);
    t.z=(answer->m[2][0]*a.x+answer->m[2][1]*a.y+answer->m[2][2]*a.z);
    return t;

}
void drawScene() {
   // printf("jump=%d \n",jump);
   sglModLoadIdentity();
	sglViewLoadIdentity();
	view->next=NULL;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    sglModLoadIdentity();
  // sglModTranslate(-4.8, -2.5,-20);
    //sglModTranslate(0.0f, 0.0f,-0.1);

    if(drop&&hp.y>-10000)hp.y-=0.05;
    //flv=1;
    if(v>vmin){v-=desc;if(v<0)v=0;handlekeypress3(lkey);}
    if(jump){if((hp.y<lth+zz*1.9)&&rise){hp.y+=0.05,accn=0.007;}else{if(rise&&hp.y<tile[ct].y)drop=1,rise=1,jump=0,accn=0.0035;else rise=0;if(hp.y>tile[ct].y&&!rise)hp.y-=0.05;if(hp.y<=tile[ct].y&&!rise)hp.y=tile[ct].y,rise=1,jump=0,accn=0.0035;}}

    sglLookAt(camera.a,camera.b,camera.c,camera.d,camera.e,camera.f,camera.g,camera.h,camera.i);
    drawtile();

        points source,robo;
     if(illuminate)source=(points){tile[99].x+3*sz,tile[0].y+10,tile[99].z-2*sz},robo={hp.x+3*sz,hp.y+hh,hp.z-6*sz};
    else source=(points){tile[99].x+3*sz,tile[0].y+10,tile[99].z-2*sz},robo={tile[0].x,2*hh,hp.z+6*sz};
    source=map(source);robo=map(robo);
    spot(robo.x,robo.y,robo.z,source.x,source.y,source.z);
    sglModPushMatrix();
    drawspotlight();
    sglModPopMatrix();

    drawhumanoid();

    glutSwapBuffers();
}

int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv); //- It allows OpenGLUT to initialize internal structures. - It allows OpenGLUT to process command-line arguments to control the initial window position, etc.
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    srand ( time(NULL) );
    w = glutGet(GLUT_SCREEN_WIDTH); //  glutGet retrieves simple GLUT state represented by integers.
    h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w ;
    int windowHeight = h ;
  // if(fll==0) printf("%d %d\n",w,h),fll++;
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    int i,k;
    double z=90.56,x=90.0;
    //printf("%f",z%x);
    fl=1;
    colors1[0]=(tiles){0.043478, 0.500000 ,0.500000};
    colors1[1]=(tiles){0.035714, 0.028571, 0.066667};
    colors1[2]=(tiles){0,1,1};
    colors1[3]=(tiles){1.000000 ,0.022727 ,0.019231};
    colors1[4]=(tiles){1,1,0};
   // for(i=0;i<100;i++){movefl[i]=rand()%10;if(movefl[i]>1)movefl[i]=0;j=pow(-1,(rand()%2+1));if(j<0)tile[i]=j*zz*0.2;else tz[i]=j*zz; ts[i]=j*0.009;}
    for(i=0;i<100;i++)
        {
            color[i]=colors1[rand()%5];
          //  printf("%d %lf %lf %lf\n",i,color[i].x,color[i].y,color[i].z);
            movefl[i]=rand()%6;
            if(movefl[i]>1)movefl[i]=1; //1:not moving 2: moving 0: no tile
            else if(movefl[i]==1)movefl[i]=2;
            k=pow(-1,(rand()%2+1));
            if(i==0)movefl[i]=1;//movefl[i]=1;
            if(movefl[i]==2){if(k<0)tile[i].y=k*-zz*0.2;else tile[i].y=2*zz; }
            else tile[i].y=zz;
            if(movefl[i]==1)if((rand()%7)>4){movefl[i]=3;tile[i].y=(zz*3.0/((rand()%3)+1));if(tile[i].y==z)tile[i].y+=k;}//having blocks
            ts[i]=k*0.01*(rand()%2+1);
            topcolor[i]=(tiles){1.0/(rand()%3+1),1.0/(rand()%3+1),1.0/((rand()%3)+1)};
        }
    movefl[99]=rand()%2?1:2;
    i=0;
    for(z=23.0*sz;z>=3.0*sz;z-=2*sz){
       // printf("%f\n",z);
        for(x=-7*sz;x<13*sz;x+=2*sz){
            tile[i].x=x,tile[i].z=z;
            i++;
        }
    }
    hp=tile[0];
    hp.x+=sz;
    hp.z-=sz;
   // camera=(cameras){0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0};

   // camera=(cameras){tile[5].x,tile[0].y+10,tile[5].z+6,tile[5].x,tile[0].y,tile[5].z-5,0,1,0};
    glutCreateWindow("~CRAZY WALKER~");  // Setup the window
    initRendering();
     //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1); // Sets the Keyboard callback for the current window. ascii
   glutSpecialFunc(handleKeypress2);//when keyboard function or directional keys are pressed
   //glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
   glutTimerFunc(20, update, 0);
  // glutSpecialUpFunc(speedcheck);
  //glutPassiveMotionFunc(ff);
  glutMouseFunc(mouse);
  glutMotionFunc(ff);
    glutMainLoop();
    return 0;
}
void initRendering() {
    glEnable(GL_DEPTH_COMPONENT);
    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor( 0.498039 ,0, 1.0, 1.0f);   // Setting a background color
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
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
void drawblock(int i){
     //  sglModTranslate(.x,tile[i].y,tile[i].z);
        double bottom=1,x=tile[i].x,y=tile[i].y,z=tile[i].z;

        bottom+=y;
        glBegin(GL_QUADS);
      /*  glVertex3f( x, y,z); //top face
        glVertex3f(x+2*sz,y, z);
        glVertex3f(x+2*sz, y,z-2*sz);
        glVertex3f( x, y,z-2*sz);*/
 glColor3f(color[i].x,color[i].y,color[i].z);
        glVertex3f( x, bottom,z);//top face
        glVertex3f(x+2*sz,bottom, z);
        glVertex3f(x+2*sz, bottom,z-2*sz);
        glVertex3f( x, bottom,z-2*sz);
        glColor3f(0,1,1);
        glVertex3f( x+2*sz, y,z); //rzght szde
        glVertex3f(x+2*sz,y, z-2*sz);
        glVertex3f(x+2*sz, bottom,z-2*sz);
        glVertex3f( x+2*sz,bottom,z);
        glVertex3f( x, y,z);//left
        glVertex3f(x,y, z-2*sz);
        glVertex3f(x, bottom,z-2*sz);
        glVertex3f( x, bottom,z);
        glColor3f(1,1,0);
        glVertex3f( x, y,z);//front
        glVertex3f(x+2*sz,y, z);
        glVertex3f(x+2*sz, bottom,z);
        glVertex3f( x, bottom,z);
        glVertex3f( x, y,z-2*sz);//back
        glVertex3f(x+2*sz,y, z-2*sz);
        glVertex3f(x+2*sz,bottom,z-2*sz);
        glVertex3f( x, bottom,z-2*sz);



    glEnd();


}

void drawtile(){
    //printf("%f %f\n",zz,sz);
      if(vm==4){sglModRotate(-dx*1.0/20,0,1,0);
        //sglModRotate(-dy*1.0/8,1,0,0);
      }
    int i;
    p=0;
    double y,z,x,bottom;
    for(i=0;i<100;i++){ //

   //     printf("%d\n",i);
         p=!p;
         if(i%10==0)p=!p;
         if(!movefl[i])continue;
        //  printf("%f %d\n",i,p);
        if(p)glColor3f(0.658824 , 0.658824 , 0.658824);
        else glColor3f(1.0f,1.0f,1.0f);
        if(movefl[i]==2){ // a moving tile
        //  if(ct==1)sglLookAt( sz*(x-1), 2*(i-1)*sz, (i-1)*sz, 10.0*sz, 13.0*sz, -2, 0.0, 0.0, 1.0 );
          //  glColor3f(color[i].x,color[i].y,color[i].z);
          glColor3f(0.0f,1.0f,0.0f);

            if(tile[i].y>=zz*3||tile[i].y<=-zz*0.2)ts[i]*=-1;
            tile[i].y+=ts[i];
            y=tile[i].y;
            }
            else if(movefl[i]==3)y=tile[i].y,glColor3f(topcolor[i].x,topcolor[i].y,topcolor[i].z);
        else y=zz;
       // y=zz;
        x=tile[i].x;
        z=tile[i].z;

  //  if(ct==1)sglLookAt( x, 3*sz+0.1, i+2.5, x+5.0*sz, y, i-5*sz, 0.0, 1.0, 0.0 );
        glBegin(GL_QUADS);
        glVertex3f( x, y,z); //top face
        glVertex3f(x+2*sz,y, z);
        glVertex3f(x+2*sz, y,z-2*sz);
        glVertex3f( x, y,z-2*sz); //if(movefl[i]==2)continue;
        //continue;
        if(!p)glColor3f(0.658824 , 0.658824 , 0.658824);
        else glColor3f(1.0f,1.0f,1.0f);
        bottom=-zz*0.2;
            if(movefl[i]==2||movefl[i]==3) {   //glColor3f(1.000000 ,0.022727 ,0.019231);
                 glColor3f(color[i].x,color[i].y,color[i].z);
                 if(movefl[i]==2)bottom=y-zz*0.33;
                            }

            else { bottom=y-zz*0.33;}
        //bottom=y-zz*0.33;
        glVertex3f( x, bottom,z);//bottom face
        glVertex3f(x+2*sz,bottom, z);
        glVertex3f(x+2*sz, bottom,z-2*sz);
        glVertex3f( x, bottom,z-2*sz);
        glVertex3f( x+2*sz, y,z); //rzght szde
        glVertex3f(x+2*sz,y, z-2*sz);
        glVertex3f(x+2*sz, bottom,z-2*sz);
        glVertex3f( x+2*sz,bottom,z);
        glVertex3f( x, y,z);//left
        glVertex3f(x,y, z-2*sz);
        glVertex3f(x, bottom,z-2*sz);
        glVertex3f( x, bottom,z);
        glVertex3f( x, y,z);//front
        glVertex3f(x+2*sz,y, z);
        glVertex3f(x+2*sz, bottom,z);
        glVertex3f( x, bottom,z);
        glVertex3f( x, y,z-2*sz);//back
        glVertex3f(x+2*sz,y, z-2*sz);
        glVertex3f(x+2*sz,bottom,z-2*sz);
        glVertex3f( x, bottom,z-2*sz);
          glEnd();
   // if(movefl[i]==3){drawblock(i);}
    }


}
void ff(int x, int y){
    float nx=mousex-x,ny=mousey-y;
    mousex=x,mousey=y;
    dx+=nx,dy+=ny;
   // getPointsInWorld(x,y);
    //printf("%d %d\n",x,y);
    //printf("%f %f\n",dx,dy);

}


