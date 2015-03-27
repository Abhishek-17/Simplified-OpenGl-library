/*
Abhishek kumar
201101185*/
#define	index(r,c)	 (c*4+r)
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define SGL_TRIANGLES 1

typedef struct matrix{
    float m[4][4];
    struct matrix * next;
}matrix;

typedef struct point{
    float x,y,z;
   // struct point* next;
}point;

typedef struct Scene{
    float m[1][4];
    int colorfl;
    point color;
    struct Scene* next;
}Scene;


matrix *model=(matrix*)malloc(sizeof(matrix)),*projection=(matrix*)malloc(sizeof(matrix)),*view=(matrix*)malloc(sizeof(matrix)),*viewport=(matrix*)malloc(sizeof(matrix)),*answer=(matrix*)malloc(sizeof(matrix));
Scene *scene=NULL,*last=NULL;
float curangle,ww,hh;
float array[16],array2d[4][4];
int fl=0,cc=0;
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
//sds
void multiply2(float first[1][4],float second [4][4]){
   //return;
    int i,k;
    float sum=0,ans[1][4];
    for ( i = 0 ; i < 4 ; i++ )
    {
     // for ( j = 0 ; j < 4; j++ )
     // {

        for ( k = 0 ; k < 4 ; k++ )
        {
          sum = sum + second[i][k]*first[0][k];
        }

        ans[0][i] = sum;
        sum = 0;
     // }
    }
    for(i=0;i<4;i++)first[0][i]=ans[0][i];


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
  /*  multiply(model->m,view->m);
    oned(answer->m);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(array);*/
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
  /* multiply(model->m,view->m);
    oned(answer->m);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(array);*/

}
void sglModTranslate(float tx,float ty,float tz){
        float temp[4][4]={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        update(model->m,answer->m);//copy  the new model matrix to the model
       /* multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/

}

void sglViewTranslate(float tx,float ty,float tz){
        float temp[4][4]={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
        multiply(temp,view->m);//stores the ans in answer matrix
        update(view->m,answer->m);//copy  the new model matrix to the model
     /*   multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/


}

void sglModScale(float sx,float sy,float sz){
        float temp[4][4]={{sx,0,0,0},{0,sy,0,0},{0,0,sz,0},{0,0,0,1}};
        multiply(temp,model->m);//stores the ans in answer matrix
        update(model->m,answer->m);//copy  the new model matrix to the modelddddddd
      /*  multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/


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
        /*matrix * temp=model,*m=model;
        while(temp){
            m=temp->next;
            free(temp);
            temp=m;
        }

        m=(matrix*)malloc(sizeof(matrix));
        m->next=NULL;*/
        if(!model)model=(matrix*)malloc(sizeof(matrix));
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)model->m[i][j]=(i==j);

        //model=m;
       /* multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/


}
void sglViewLoadIdentity(){


        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)view->m[i][j]=(i==j);

       /* multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/
}

void sglViewportLoadIdentity(){


        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)viewport->m[i][j]=(i==j);
}

void sglProjectionLoadIdentity(){


        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++)projection->m[i][j]=(i==j);
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
      /*  multiply(model->m,view->m);
        oned(answer->m);
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(array);*/

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
    update(projection->m,m);
     //print(projection->m);
   /* glMatrixMode(GL_PROJECTION);
    oned(m);
    glLoadMatrixf(array);*/
}

void sglProjOrtho(float left,float right,float bottom,float top,float near,float far){
    float a,b,c,d,e,f;
    a=(2.0)/(right-left);
    b=-(right+left)*1.0/(right-left);
    c=2.0/(top-bottom);
    d=-(top+bottom)*1.0/(top-bottom);
    e=-2.0/(far-near);
    f=-1.0*(far+near)/(far-near);
    float m[4][4]={{a,0,0,b},{0,c,0,d},{0,0,e,f},{0,0,0,1}};
    update(projection->m,m);
    /*glMatrixMode(GL_PROJECTION);
    oned(m);
    glLoadMatrixf(array);*/

}

void sglViewport(float llx,float lly,float width,float height){
    float a,b,c,d;
    a=(width-llx)/2.0;
    b=(width+llx)/2.0;
    c=(height-lly)/2.0;
    d=(height+lly)/2.0;
    float m[4][4]={{a,0,0,b},{0,c,0,d},{0,0,0.5,0.5},{0,0,0,1.0}};
    update(viewport->m,m);
   /* oned(m);
    glMatrixMode(GL_VIEWPORT);
    glLoadMatrixf(array);
    glMatrixMode(GL_MODELVIEW);*/
}

void sglVertex(float x,float y,float z){
    if(!fl)return;//sglbegin was not called
    if(!scene){scene=(Scene*)malloc(sizeof(Scene));
            scene->m[0][0]=x,scene->m[0][1]=y,scene->m[0][2]=z,scene->m[0][3]=1.0,scene->next=NULL;
             multiply2(scene->m,model->m);
       //   if(!i)printf("2: %f %f %f %f\n",scene->m[0][0],scene->m[0][1],scene->m[0][2],scene->m[0][3]);
            multiply2(scene->m,view->m);
            multiply2(scene->m,projection->m);
            //multiply2(scene->m,viewport->m);
            scene->colorfl=0;
            last=scene;
            cc++;
            return;
    }
    else{
        Scene * temp=(Scene*)malloc(sizeof(Scene));
            temp->m[0][0]=x,temp->m[0][1]=y,temp->m[0][2]=z,temp->m[0][3]=1.0,temp->next=NULL;
            multiply2(temp->m,model->m);
       //   if(!i)printf("2: %f %f %f %f\n",scene->m[0][0],scene->m[0][1],scene->m[0][2],scene->m[0][3]);
            multiply2(temp->m,view->m);
            multiply2(temp->m,projection->m);
          //  multiply2(temp->m,viewport->m);
            temp->colorfl=0;
            last->next=temp;
            cc++;
            last=temp;
    }


}
void sglShow(){
    Scene * temp;

  //  int i=0;
    //print(model->m);
    FILE * pFile;
    pFile = fopen ("PLY_201101185.ply","w");
   if (pFile!=NULL)
   {
     glBegin(GL_TRIANGLES);

    while(scene){
        //printf("%d\n",i++);

      //if(!i)printf("1: %f %f %f %f\n",scene->m[0][0],scene->m[0][1],scene->m[0][2],scene->m[0][3]);
        temp=scene->next;
    /*    multiply2(scene->m,model->m);
       //   if(!i)printf("2: %f %f %f %f\n",scene->m[0][0],scene->m[0][1],scene->m[0][2],scene->m[0][3]);
        multiply2(scene->m,view->m);
        multiply2(scene->m,projection->m);
        multiply2(scene->m,viewport->m);*/
        //if(scene->m[0][3]==0)scene->m[0][3]=1;
        glVertex3f(1.0*scene->m[0][0]/scene->m[0][3],1.0*scene->m[0][1]/scene->m[0][3],1.0*scene->m[0][2]/scene->m[0][3]);
        fprintf(pFile,"%f %f %f %f\n",scene->m[0][0],scene->m[0][1],scene->m[0][2],scene->m[0][3]);
        if(scene->colorfl)glColor3f(scene->color.x,scene->color.y,scene->color.z);

        //  i++;
        free(scene);
        scene=temp;

    }
    last=NULL;
    glEnd();
    fclose (pFile);
    cc=0;
   }

}


void sglBegin(int n){
    if(n!=1)return;
    fl=1;

}
void sglEnd(){
    fl=0;

}

void sglColour(float r,float g,float b){
    if(last==NULL){glColor3f(r,g,b);return;}
    last->colorfl=1;
    last->color=(point){r,g,b};

}
void sglClear(float r,float g,float b){
    glClearColor(r, g, b, 1.0f);   // Setting a background color
}
