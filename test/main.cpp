/*
 Transparency is best implemented using blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) with primitives sorted from farthest to nearest. Note that this transparency calculation does not require the presence of alpha bitplanes in the frame buffer.
 
 Blend function (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) is also useful for rendering antialiased points and lines in arbitrary order.
 
 Polygon antialiasing is optimized using blend function (GL_SRC_ALPHA_SATURATE, GL_ONE) with polygons sorted from nearest to farthest. (See the glEnable, glDisable reference page and the GL_POLYGON_SMOOTH argument for information on polygon antialiasing.) Destination alpha bitplanes, which must be present for this blend function to operate correctly, store the accumulated coverage
 
 Author: GH God
 email :hardxray007@gmail.com
 
 */
#include <GLUT/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#define PI 3.14152653597689786
#define RandomFactor 2.0
#define ESCAPE 27
#define TEXTID      3

void level1(int id);
void DrawTextXY(double x,double y,double z,double scale,char *s);
int beat_flag=0;

unsigned int i;
int flag=0,f=2;
int vflag=0;
GLfloat xt=0.0,yt=0.0,zt=0.0;
GLfloat xangle=0.0,yangle=0.0,zangle=0.0;
GLfloat X[3];
GLint ListNum;            //The number of the diplay list

GLfloat OuterRadius = 2.4;    //reservoir
GLfloat InnerRadius = 2.0;
GLint NumOfVerticesStone = 6;    // reservoir shape
GLfloat StoneHeight = 0.5;
GLfloat WaterHeight = 0.45;
//1.0,0.0,0.0

int light0=1,light1=1,light2=1,light3=1,light4=1,light5=1;
int playsound=0;
// Create light components
//light0
GLfloat ambientLight[] = { 0.3,0.0,0.0, 1.0f };
GLfloat diffuseLight[] = { 0.7f, 0.2f, 0.3f, 1.0f };
GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat position[] = { -1.200183f, 0.500000f ,-2.078355f, 1.0f };
GLfloat spot_direction[]={-1.0f,-1.0f,0.0f};
GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };

//light1
GLfloat ambientLight1[] = { 0.1f, 0.3f, 0.4f, 1.0f };
GLfloat diffuseLight1[] = { 0.1f,0.3f, 0.4, 1.0f };
GLfloat specularLight1[] = { 0.5f, 0.6f, 0.7f, 1.0f };
GLfloat position1[] = { -2.400000f ,0.500000f ,0.000159f, 1.0f };
GLfloat spot_direction1[]={-1.0f,-1.0f,0.0f};

//light2
GLfloat ambientLight2[] = { 0.2f, 0.2f, 1.0f, 1.0f };
GLfloat diffuseLight2[] = { 0.0f,1.0f, 1.0, 1.0f };
GLfloat specularLight2[] = { 0.3f, 0.2f, 0.5f, 1.0f };
GLfloat position2[] = { -1.199908f, 0.500000f, 2.078514f, 1.0f };
GLfloat spot_direction2[]={-1.0f,-1.0f,0.0f};

//light3
GLfloat ambientLight3[] = { 0.2f, 0.8f, 1.0f, 1.0f };
GLfloat diffuseLight3[] = { 1.0f,0.0f, 1.0, 1.0f };
GLfloat specularLight3[] = { 0.1f, 0.4f, 0.8f, 1.0f };
GLfloat position3[] = { 1.200046f ,0.500000f ,2.078435f, 1.0f };
GLfloat spot_direction3[]={-1.0f,-1.0f,0.0f};

//light4
GLfloat ambientLight4[] = { 0.0f, 0.1f, 0.5f, 1.0f };
GLfloat diffuseLight4[] = { 0.0f,0.5f, 0.5, 1.0f };
GLfloat specularLight4[] = { 0.1f, 0.4f, 0.8f, 1.0f };
GLfloat position4[] = { 2.400000f, 0.500000f ,0.000000f, 1.0f };
GLfloat spot_direction4[]={-1.0f,-1.0f,0.0f};

//light5
GLfloat ambientLight5[] = { 0.2f, 0.0f, 0.9f, 1.0f };
GLfloat diffuseLight5[] = { 0.2f,0.2f, 0.9, 1.0f };
GLfloat specularLight5[] = { 0.1f, 0.4f, 0.8f, 1.0f };
GLfloat position5[] = { 1.199771f, 0.500000f, -2.078593f, 1.0f };
GLfloat spot_direction5[]={-1.0f,-1.0f,0.0f};

GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_ambient_color[] = {0.8f, 0.8f, 0.2f, 1.0f};
GLfloat mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat no_shininess = 0.0f;
GLfloat low_shininess = 5.0f;
GLfloat high_shininess = 100.0f;
GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

//loading bmp file for texture
GLuint grass;

//function to load bitmap image for texture
GLuint LoadBMP(const char *fileName)
{
    FILE *file;
    unsigned char header[54],*data;
    unsigned int dataPos,size,width, height;
    file = fopen(fileName, "rb");
    fread(header, 1, 54, file);
    dataPos= *(int*)&(header[0x0A]);
    size= *(int*)&(header[0x22]);
    width= *(int*)&(header[0x12]);
    height= *(int*)&(header[0x16]);
    if (size == NULL)
        size = width * height * 3;
    if (dataPos == NULL)
        dataPos = 54;
    data = new unsigned char[size];
    fread(data, 1, size, file);
    fclose(file);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    return texture;
}

//for initialising texture
void initTexture()
{
    grass=LoadBMP("/Users/hardxray007/xcode-workspace/test/test/grass.bmp");
}

//for drawing ground texture
void drawGround(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,grass);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-OuterRadius*10.0,0.0,OuterRadius*10.0);
    glTexCoord2f(800.0f, 0.0f);
    glVertex3f(-OuterRadius*10.0,0.0,-OuterRadius*10.0);
    glTexCoord2f(800.0f, 800.0f);
    glVertex3f(OuterRadius*10.0,0.0,-OuterRadius*10.0);
    glTexCoord2f(0.0f, 800.0f);
    glVertex3f(OuterRadius*10.0,0.0,OuterRadius*10.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//function to change level of fountain with beats in sound
void level_Change_With_Beats(int r){
    int k;
    static int it=0;
    srand(time(NULL));
    k=rand()%10+1;
    printf("k is : %d\n",k);
    level1(k);
//    while(beat_flag<380){
//        printf("iter no : %d\n",it);
//        it++;
//    glutTimerFunc(1000.0, level_Change_With_Beats, 0);
//        beat_flag++;
//    }
    if(beat_flag<18){
    glutTimerFunc(1000.0, level_Change_With_Beats, 0);
        beat_flag++;
    }
}


struct SVertex
{
    GLfloat x,y,z;
};

///////////////////////////////fountain///////////////////////////////////
class CDrop
{
private:
    GLfloat time;
    SVertex ConstantSpeed;
    GLfloat AccFactor;
public:
    void SetConstantSpeed (SVertex NewSpeed);
    void SetAccFactor(GLfloat NewAccFactor);
    void SetTime(GLfloat NewTime);
    void GetNewPosition(SVertex * PositionVertex);  //increments time, gets the new position
};

void CDrop::SetConstantSpeed(SVertex NewSpeed)
{
    ConstantSpeed = NewSpeed;
}

void CDrop::SetAccFactor (GLfloat NewAccFactor)
{
    AccFactor = NewAccFactor;
}

void CDrop::SetTime(GLfloat NewTime)
{
    time = NewTime;
}

void CDrop::GetNewPosition(SVertex * PositionVertex)
{
    SVertex Position;
    time += 0.15;
    Position.x = ConstantSpeed.x * time;
    Position.y = ConstantSpeed.y * time - AccFactor * time *time;
    Position.z = ConstantSpeed.z * time;
    PositionVertex->x = Position.x;
    PositionVertex->y = Position.y + WaterHeight;
    PositionVertex->z = Position.z;
    if (Position.y < 0.0)
    {
        time = time - int(time);
        if (time > 0.0) time -= 1.0;
    }
    
}

CDrop * FountainDrops;
SVertex * FountainVertices;
GLint Steps = 4;              //a fountain has several steps, each with its own height
GLint RaysPerStep =8;
GLint DropsPerRay = 80;
GLfloat DropsComplete = Steps * RaysPerStep * DropsPerRay;
GLfloat AngleOfDeepestStep = 80;
GLfloat AccFactor = 0.011;

// Creating reservoir boundary
void CreateList(void)
{
    SVertex * Vertices = new SVertex[NumOfVerticesStone*3];  //allocate mem for the required vertices
    ListNum = glGenLists(1);
    for (GLint i = 0; i<NumOfVerticesStone; i++)
    {
        Vertices[i].x = cos(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
        Vertices[i].y = StoneHeight;  //Top
        Vertices[i].z = sin(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
    }
    for (i = 0; i<NumOfVerticesStone; i++)
    {
        Vertices[i + NumOfVerticesStone*1].x = cos(2.0 * PI / NumOfVerticesStone * i) * InnerRadius;
        Vertices[i + NumOfVerticesStone*1].y = StoneHeight;  //Top
        Vertices[i + NumOfVerticesStone*1].z = sin(2.0 * PI / NumOfVerticesStone * i) * InnerRadius;
    }
    for (i = 0; i<NumOfVerticesStone; i++)
    {
        Vertices[i + NumOfVerticesStone*2].x = cos(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
        Vertices[i + NumOfVerticesStone*2].y = 0.0;  //Bottom
        Vertices[i + NumOfVerticesStone*2].z = sin(2.0 * PI / NumOfVerticesStone * i) * OuterRadius;
    }
    
    
    glNewList(ListNum, GL_COMPILE);
    // glPushMatrix();
    glPushMatrix();
    glColor3f(0.7,0.2,0.3);
//    glPushMatrix();
    DrawTextXY(Vertices[4].x-0.2,Vertices[4].y,Vertices[4].z-0.5, 0.002, "0");
//    glPopMatrix();
    glTranslatef(Vertices[4].x,Vertices[4].y,Vertices[4].z);
//    printf("%f %f %f",Vertices[5].x,Vertices[5].y,Vertices[5].z);
//    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
//    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
    
    //light1
    glPushMatrix();
    glColor3f(0.1,0.3,0.4);
    DrawTextXY(Vertices[3].x-0.2,Vertices[3].y,Vertices[3].z-0.5, 0.002, "1");
    glTranslatef(Vertices[3].x,Vertices[3].y,Vertices[3].z);
//    printf("%f %f %f",Vertices[3].x,Vertices[3].y,Vertices[3].z);
    //    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    //    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    //    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
    
    //light2
    glPushMatrix();
    glColor3f(0,1.0,1.0);
    DrawTextXY(Vertices[2].x-0.2,Vertices[2].y,Vertices[2].z-0.5, 0.002, "2");
    glTranslatef(Vertices[2].x,Vertices[2].y,Vertices[2].z);
    //    printf("%f %f %f",Vertices[3].x,Vertices[3].y,Vertices[3].z);
    //    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    //    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    //    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
    
    //light3
    glPushMatrix();
    glColor3f(1,0.0,1.0);
    DrawTextXY(Vertices[1].x+1.2,Vertices[1].y,Vertices[1].z-0.5, 0.002, "3");
    glTranslatef(Vertices[1].x,Vertices[1].y,Vertices[1].z);
    //    printf("%f %f %f",Vertices[3].x,Vertices[3].y,Vertices[3].z);
    //    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    //    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    //    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
    
    //light4
    glPushMatrix();
    glColor3f(0,0.5,0.5);
    DrawTextXY(Vertices[0].x-0.2,Vertices[0].y,Vertices[0].z-0.5, 0.003, "4");
    glTranslatef(Vertices[0].x,Vertices[0].y,Vertices[0].z);
    //    printf("%f %f %f",Vertices[3].x,Vertices[3].y,Vertices[3].z);
    //    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    //    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    //    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
    
    //light5
    glPushMatrix();
    glColor3f(0.2,0.2,0.9);
    DrawTextXY(Vertices[5].x-0.2,Vertices[5].y,Vertices[5].z-0.5, 0.003, "5");
    glTranslatef(Vertices[5].x,Vertices[5].y,Vertices[5].z);
    //    printf("%f %f %f",Vertices[3].x,Vertices[3].y,Vertices[3].z);
    //    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    //    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //    glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
    //    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.3,20,20);
    glPopMatrix();
//    glBegin(GL_QUADS);
    //ground quad:
//    glColor3ub(0,105,0);
//    glPushMatrix();
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D,grass);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f);
//    glVertex3f(-OuterRadius*10.0,0.0,OuterRadius*10.0);
//    glTexCoord2f(800.0f, 0.0f);
//    glVertex3f(-OuterRadius*10.0,0.0,-OuterRadius*10.0);
//    glTexCoord2f(800.0f, 800.0f);
//    glVertex3f(OuterRadius*10.0,0.0,-OuterRadius*10.0);
//    glTexCoord2f(0.0f, 800.0f);
//    glVertex3f(OuterRadius*10.0,0.0,OuterRadius*10.0);
//    glEnd();
//    glDisable(GL_TEXTURE_2D);
//    glPopMatrix();
    
        //original before adding texture
//    glVertex3f(-OuterRadius*10.0,0.0,OuterRadius*10.0);
//    glVertex3f(-OuterRadius*10.0,0.0,-OuterRadius*10.0);
//    glVertex3f(OuterRadius*10.0,0.0,-OuterRadius*10.0);
//    glVertex3f(OuterRadius*10.0,0.0,OuterRadius*10.0);
//    glEnd();
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    //light0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    //light1
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
//    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    //light2
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight2);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    
    //light3
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLight3);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularLight3);
    glLightfv(GL_LIGHT3, GL_POSITION, position3);
    
    //light4
    glLightfv(GL_LIGHT4, GL_AMBIENT, ambientLight4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuseLight4);
    glLightfv(GL_LIGHT4, GL_SPECULAR, specularLight4);
    glLightfv(GL_LIGHT4, GL_POSITION, position4);
    
    //light5
    glLightfv(GL_LIGHT5, GL_AMBIENT, ambientLight5);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuseLight5);
    glLightfv(GL_LIGHT5, GL_SPECULAR, specularLight5);
    glLightfv(GL_LIGHT5, GL_POSITION, position5);
    if(light0){
        printf("light0 on\n");
        glEnable(GL_LIGHT0);
    }
    if(light1){
        printf("light1 on\n");
    glEnable(GL_LIGHT1);
    }
    if(light2){
        printf("light2 on\n");
    glEnable(GL_LIGHT2);
    }
    if(light3){
        printf("light3 on\n");
    glEnable(GL_LIGHT3);
    }
    if(light4){
        printf("light4 on\n");
    glEnable(GL_LIGHT4);
    }
    if(light5){
        printf("light5 on\n");
    glEnable(GL_LIGHT5);
    }
    printf("new list\n");
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glNormal3f(0.0f, 0.0f, 1.0f);
    
    
    // stone:
    glBegin(GL_QUADS);
    for (int j = 1; j < 3; j++)
    {
        if (j == 1) glColor3f(1.3,0.5,1.2);
        if (j == 2) glColor3f(0.4,0.2,0.1);
        for (i = 0; i<NumOfVerticesStone-1; i++)
        {
            glVertex3fv(&Vertices[i+NumOfVerticesStone*j].x);
            glVertex3fv(&Vertices[i].x);
            glVertex3fv(&Vertices[i+1].x);
            glVertex3fv(&Vertices[i+NumOfVerticesStone*j+1].x);
        }
        glVertex3fv(&Vertices[i+NumOfVerticesStone*j].x);
        glVertex3fv(&Vertices[i].x);
        glVertex3fv(&Vertices[0].x);
        glVertex3fv(&Vertices[NumOfVerticesStone*j].x);
    }
    
    glEnd();
    
    //The "water":
    glTranslatef(0.0,WaterHeight - StoneHeight, 0.0);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    GLfloat cyan[] = {0.1f, 0.0f, 0.0f, 1.f};
//    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cyan);
    glMaterialf(GL_FRONT, GL_SHININESS, 17);
    glBegin(GL_POLYGON);
    for (i = 0; i<NumOfVerticesStone; i++)
    {
        
        
        glVertex3fv(&Vertices[i+NumOfVerticesStone].x);
        GLint m1,n1,p1;
//        m1=rand()%255;
//        n1=rand()%255;
//        p1=rand()%255;
//
//        glColor3ub(m1,n1,p1);
        
            glColor3f(1.0,1.0,1.0);
    }
    
    glEnd();
    // glPopMatrix();
    glDisable(GL_LIGHTING);
   
    glEndList();
}

GLfloat GetRandomFloat(GLfloat range)
{
    return (GLfloat)rand() / (GLfloat)RAND_MAX * range * RandomFactor;
}
//for initalising fountain water drops
void InitFountain(void)
{
    //This function needn't be and isn't speed optimized
    FountainDrops = new CDrop [ (int)DropsComplete ];
    FountainVertices = new SVertex [ (int)DropsComplete ];
    SVertex NewSpeed;
    GLfloat DropAccFactor; //different from AccFactor because of the random change
    GLfloat TimeNeeded;
    GLfloat StepAngle; //Angle, which the ray gets out of the fountain with
    GLfloat RayAngle;    //Angle you see when you look down on the fountain
    GLint i,j,k;
    for (k = 0; k <Steps; k++)
    {
        for (j = 0; j < RaysPerStep; j++)
        {
            for (i = 0; i < DropsPerRay; i++)
            {
                DropAccFactor = AccFactor + GetRandomFloat(0.0005);
                StepAngle = AngleOfDeepestStep + (90.0-AngleOfDeepestStep)
                * GLfloat(k) / (Steps-1) + GetRandomFloat(0.2+0.8*(Steps-k-1)/(Steps-1));
                //This is the speed caused by the step:
                NewSpeed.x = cos ( StepAngle * PI / 180.0) * (0.2+0.04*k);
                NewSpeed.y = sin ( StepAngle * PI / 180.0) * (0.2+0.04*k);
                //This is the speed caused by the ray:
                
                RayAngle = (GLfloat)j / (GLfloat)RaysPerStep * 360.0;
                //for the next computations "NewSpeed.x" is the radius. Care! Dont swap the two
                //lines, because the second one changes NewSpeed.x!
                NewSpeed.z = NewSpeed.x * sin ( RayAngle * PI /180.0);
                NewSpeed.x = NewSpeed.x * cos ( RayAngle * PI /180.0);
                
                //Calculate how many steps are required, that a drop comes out and falls down again
                TimeNeeded = NewSpeed.y/ DropAccFactor;
                FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetConstantSpeed ( NewSpeed );
                FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetAccFactor (DropAccFactor);
                FountainDrops[i+j*DropsPerRay+k*DropsPerRay*RaysPerStep].SetTime(TimeNeeded * i / DropsPerRay);
            }
        }
    }
    
    
    //Tell OGL that we'll use the vertex array function
    glEnableClientState(GL_VERTEX_ARRAY);
    //Pass the data position
    glVertexPointer(    3,            //x,y,z-components
                    GL_FLOAT,    //data type of SVertex
                    0,            //the vertices are tightly packed
                    FountainVertices);
    
}

void randcolor()
{
    GLint a,b,c;
    a=rand()%101;
    b=rand()%101;
    c=rand()%101;
    X[0]=(GLfloat)a/100.0;
    X[1]=(GLfloat)b/100.0;
    X[2]=(GLfloat)c/100.0;
    
}
//function to draw fountain
void DrawFountain(void)
{
    if(flag==0)
        glColor3f(1,1,1);
    else if(flag==1)
        glColor3fv(X);
    else if(flag==2)
        glColor3f(0.0,1.0,0.0);
    else
        glColor3f(0.0,1.0,1.0);
    for (int i = 0; i < DropsComplete; i++)
    {
        FountainDrops[i].GetNewPosition(&FountainVertices[i]);
    }
    glDrawArrays(    GL_POINTS,
                 0,
                 DropsComplete);
    glutPostRedisplay();
}

//callback function to change color of fountain
void colours(int id)
{
    
    flag=id;
    if(flag==1)
        randcolor();
    glutPostRedisplay();
}

//callback function to change flow of fountain
void flow(int id)
{
    RaysPerStep=id;
    DropsComplete = Steps * RaysPerStep * DropsPerRay;
    delete [] FountainVertices;
    delete [] FountainDrops;
    InitFountain();
    glutPostRedisplay();
}
//callback function to change level of fountain
void level(int id)
{
    Steps=id;
    DropsComplete = Steps * RaysPerStep * DropsPerRay;
    delete [] FountainVertices;
    delete [] FountainDrops;
    InitFountain();
    glutPostRedisplay();
}

void level1(int id)
{
    Steps=id;
    DropsComplete = Steps * RaysPerStep * DropsPerRay;
    delete [] FountainVertices;
    delete [] FountainDrops;
    InitFountain();
    glutPostRedisplay();
}

//callback function to play music
void soundplay(int id)
{
    switch (id) {
        case 0:
            if(playsound!=1)
            {
                playsound=1;
                system("afplay -t 20 /Users/hardxray007/xcode-workspace/test/test/2.mp3&");
                glutTimerFunc(1000.0, level_Change_With_Beats, 0);
            }
            break;
        case 1:
            if(playsound==1)
            {
                playsound=0;
                beat_flag=0;
            }
//            char *cmd;
//            strcpy(cmd,"kill `ps | grep 'afplay [a-z0-9A-Z]*.mp3' | awk '{print $1}'`");
//            system(cmd);
//            playsound=0;
            break;
    }
}
//callback function to move using keyboard
void help(int id)
{
    switch (id) {
        case 1:
            vflag=11;  // near
            break;
        case 2:
            vflag=1;    // away
            break;
        case 3:
            vflag=2;    //down
            break;
        case 4:
            vflag=22;    //up
            break;
        case 5:
            vflag=3;     //top
            break;
        case 6:
            vflag=33;    //front
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

//function to enable or disable lights
void light(int id)
{
    //tick mark character code-\u2713 when lights are on menu shows entry with tick mark
    
    //cross mark character code-\u2A2F when lights are off menu shows entry with cross mark
    switch (id) {
        case 0:
            glDisable(GL_LIGHT0);
            if(light0==0){
                light0=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 0", 0);
            }
            else
            {
                light0=0;
                glutChangeToMenuEntry(id+1, "\u2A2F light 0", 0);
            }
            CreateList();
            break;
        case 1:
            glDisable(GL_LIGHT1);
            if(light1==0){
                light1=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 1", 1);
            }
            else
            {
                light1=0;
                printf("hi");
                glutChangeToMenuEntry(id+1, "\u2A2F light 1", 1);
            }
                CreateList();
            break;
        case 2:
            glDisable(GL_LIGHT2);
            if(light2==0){
                light2=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 2", 2);
            }
            else
            {
                light2=0;
                glutChangeToMenuEntry(id+1, "\u2A2F light 2", 2);
            }
                CreateList();
            break;
        case 3:
            glDisable(GL_LIGHT3);
            if(light3==0){
                light3=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 3", 3);
            }
            else{
                light3=0;
                glutChangeToMenuEntry(id+1, "\u2A2F light 3", 3);
            }
                CreateList();
            break;
        case 4:
            glDisable(GL_LIGHT4);
            if(light4==0){
                light4=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 4", 4);
            }
            else{
                light4=0;
                glutChangeToMenuEntry(id+1, "\u2A2F light 4", 4);
            }
                CreateList();
            break;
        case 5:
            glDisable(GL_LIGHT5);
            if(light5==0){
                light5=1;
                glutChangeToMenuEntry(id+1, "\u2713 light 5", 5);
            }
            else{
                light5=0;
                glutChangeToMenuEntry(id+1, "\u2A2F light 5", 5);
            }
                CreateList();
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
void CMain(int id)
{
}
//key board functions
void NormalKey(GLubyte key, GLint x, GLint y)
{
    
    if(f==0) //main page
    {
        switch ( key )
        {
            case 13:
            case '1':    f=3;    break;    //fountain
            case 'h':
            case '2':    f=1;    break;    //help
            case '3':                    //exit
            case '4':
            case 'b':    f=2;    break;
            case ESCAPE:    exit(0);
                
                glutPostRedisplay();
        }
    }
    else if(f==1)  //help page
    {
        if(key=='b'||key=='B')
            f=0;
        else
            f=3;
        glutPostRedisplay();
    }
    else if(f==2)    //cover page
    {    f=0;
    }
    else    // funtain page
    {
        switch ( key )
        {
            case ESCAPE : exit(0);    break;
                
            case 't':    case 'T':
                vflag=3;                        //top view
                glutPostRedisplay();
                break;
                
            case 'f':    case 'F':
                vflag=33;                        //front view
                glutPostRedisplay();
                break;
                
            case 'd':    case 'D':
                vflag=2;                      // Move down
                glutPostRedisplay();
                break;
                
            case 'u':    case 'U':
                vflag=22;                      // Move up
                glutPostRedisplay();
                break;
                
            case 'a':    case 'A':
                vflag=1;                      // Move away
                glutPostRedisplay();
                break;
                
            case 'n':    case 'N':
                vflag=11;                      // Move near
                glutPostRedisplay();
                break;
                
            case 'b':    case 'B':                    //back
                f=0;
                glutPostRedisplay();
                break;
                
            case 'h':    case 'H':                    //help
                f=1;
                glutPostRedisplay();
                break;
                
                
            default:
                break;
        }
    }//end of else
}

// functrion to display text
void DrawTextXY(double x,double y,double z,double scale,char *s)
{
    int i;
    
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(scale,scale,scale);
    for (i=0;i < strlen(s);i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);
    // glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
    glPopMatrix();
}
// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f, ly = 0.0f;

// XZ position of the camera
float x=0.0f, z=5.0f, y = 1.75f;

float lastX = 1024 / 2.0f;
float lastY = 768 / 2.0f;
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
float Yaw=YAW;
float Pitch=PITCH;
int valid=0;   //flag


// the key states. These variables will be zero
//when no key is being presses
//float deltaAngle = 0.0f;
//float deltaMove = 0;
//int xOrigin = -1;
void mouseMove(int x, int y) {
    
    // this will only be true when the left button is down
    //    if (xOrigin >= 0) {
    
    //        // update deltaAngle
    //        deltaAngle = (x - xOrigin) * 0.001f;
    //
    //        // update camera's direction
    //        lx = sin(angle + deltaAngle);
    //        lz = -cos(angle + deltaAngle);
    //for camera using mouse
    if (valid) {
        float xoffset = lastX - x;
        float yoffset = y-lastY;
        /* do something with dx and dy */
        xoffset *= 0.01f;
        yoffset *= 0.01f;
        
        Yaw   += xoffset;
        Pitch += yoffset;
        
        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
        glm::vec3 front,right,up;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front = glm::normalize(front);
        lx=front.x;
        ly=front.y;
        lz=front.z;
        // Also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front,glm::vec3(0.0f,1.0f,0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up    = glm::normalize(glm::cross(right, front));
    }
    lastX = x;
    lastY = y;
    
    glutPostRedisplay();
    //    }
}
void mouseButton(int button, int state, int x, int y) {
    
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        
        // when the button is released
        if (state == GLUT_UP) {
            //            angle += deltaAngle;
            //            deltaAngle = 0.0f;
            //            xOrigin = -1;
            valid=0;
        }
        else  {// state = GLUT_DOWN
            //            xOrigin = x;
            
            // for turnging lights on or of using mouse click
            std::cout<<x<<" "<<y<<std::endl;
            if(x>=326 && x<=367 && y>=545 && y<=585){
                light(0);
            }
            else if(x>=336 && x<=388 && y>=611 && y<=638){
                light(1);
            }
            else if(x>=542 && x<=601 && y>=597 && y<=656){
                light(2);
            }
            else if(x>=673 && x<=720 && y>=562 && y<=611){
                light(3);
            }
            else if(x>=604 && x<=643 && y>=531 && y<=566){
                light(4);
            }
            else if(x>=455 && x<=490 && y>=525 && y<=551){
                light(5);
            }
            //for camera
            lastX = x;
            lastY = y;
            valid=1;
        }
    }
    
}

void Display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0,0,0,1.0);
    glTranslatef(0.0,0.0,-6.0);
    glTranslatef(0.0,-1.3,0.0);
    //for camera
    gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0f,1.0f,0.0f);
    
    
    if(vflag==1)        //far
    {
        zt-=0.06;
    }
    glTranslatef(xt,yt,zt);
    
    if(vflag==11)       //near
    {
        zt+=0.06;
    }
    glTranslatef(xt,yt,zt);
    
    if(vflag==2)        //down
    {
        yt -= 0.05;
    }
    glTranslatef(xt,yt,zt);
    
    if(vflag==22)       //up
    {
        yt += 0.05;
    }
    glTranslatef(xt,yt,zt);
    
    
    if(vflag==3)       //angular
    {
        if(xangle<=80.0)
            xangle += 5.0;
    }
    
    if(vflag==33)
    {                    //angular
        if(xangle>=-5)
            xangle -= 5.0;
    }
    
    glColor3f(1.0,0.0,0.0);
    
    glRotatef(xangle,1.0,0.0,0.0);
    
    
    vflag=0;
    glRotatef(45.0,0.0,1.0,0.0);
    
    
    glPushMatrix();
    
    glCallList(ListNum);
    drawGround();
   
    
    glPopMatrix();
    
    DrawFountain();
    
    glFlush();            //Finish rendering
    glutSwapBuffers();    //Swap the buffers ->make the result of rendering visible
    
    
}

//display menu
void menu1()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0,0,0,0.0);
    
    glTranslatef(0.0,0.0,-6.0);
    glTranslatef(0.0,-1.3,0.0);
    
    glColor3f(1.00,0.20,0.10);
    glLoadName(TEXTID);
    
    DrawTextXY(-2.7,3.5,0.0,0.003,"     FOUNTAIN ");
    
    glColor3f(0.6,0.8,0.7);
    DrawTextXY(-1.25,2.4,0.0,0.0014,"    MENU ");
    
    glColor3f(1.0,0.8,0.4);
    DrawTextXY(-1.25,2.1,0.0,0.001,"     1 : PROCEED ");
    DrawTextXY(-1.25,1.9,0.0,0.001,"     2 : HELP ");
    DrawTextXY(-1.25,1.7,0.0,0.001,"     3 : EXIT ");
    DrawTextXY(-1.25,1.5,0.0,0.001,"     4 : BACK");
    
    glFlush();            //Finish rendering
    glutSwapBuffers();
    
}

void menu2()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0,0,0,1.0);
    
    glTranslatef(0.0,0.0,-6.0);
    glTranslatef(0.0,-1.3,0.0);
    
    glColor3f(0.6,0.8,0.7);
    DrawTextXY(-2.7,3.5,0.0,0.003,"       HELP ");
    glColor3f(1.0,0.8,0.4);
    DrawTextXY(-1.75,2.4,0.0,0.0014,"  Keyboard Controls : ");
    glColor3f(0.9,0.8,0.9);
    DrawTextXY(-1.25,2.1,0.0,0.001,"  Move Near  ->  N ");
    DrawTextXY(-1.25,1.9,0.0,0.001,"  Move Away  ->  A ");
    DrawTextXY(-1.25,1.5,0.0,0.001,"  Move Up    ->  U ");
    DrawTextXY(-1.25,1.3,0.0,0.001,"  Move Down  ->  D ");
    DrawTextXY(-1.25,0.9,0.0,0.001,"  Top View   ->  T ");
    DrawTextXY(-1.25,0.7,0.0,0.001,"  Front View ->  F ");
    DrawTextXY(-1.25,0.3,0.0,0.001,"  Open HELP  ->  H ");
    DrawTextXY(-1.25,0.1,0.0,0.001,"  Open MENU  ->  B ");
    
    
    glColor3f(0.9,0.9,0.8);
    DrawTextXY(1,-0.4,0.0,0.001,"  Press any KEY ... ");
    glFlush();            //Finish rendering
    glutSwapBuffers();
    
}

void cover()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glClearColor(0,0,0,0.0);
    
    glTranslatef(0.0,0.0,-6.0);
    glTranslatef(0.0,-1.3,0.0);
    
    glColor3f(1.00,0.20,0.10);
    glLoadName(TEXTID);
    
    DrawTextXY(-1.7,3.5,0.0,0.001,"   GRAPHICAL IMPLEMENTATION OF  ");
    
    glColor3f(0.6,0.8,0.7);
    DrawTextXY(-1.75,3,0.0,0.0014,"    FLOWING FOUNTAIN ");
    
    glColor3f(0.7,0.6,0.1);
    DrawTextXY(-3.25,1.5,0.0,0.0007,"     Submitted by :- ");
    
    glColor3f(1.0,0.5,0.0);
    DrawTextXY(-2.5,1.2,0.0,0.001,"     First Name ");
    DrawTextXY(1,1.2,0.0,0.001,"        Second Name ");
    glColor3f(0.7,0.8,0.6);
    DrawTextXY(-2.5,0.95,0.0,0.001,"     Kunal Sikri ");
    DrawTextXY(1,0.95,0.0,0.001,"        Priyanka Meena ");
    
    glColor3f(0.7,0.6,0.1);
    DrawTextXY(-1.25,0,0.0,0.0007,"     Under the guidance of : ");
    glColor3f(1.0,0.8,0.4);
    DrawTextXY(-1.25,-.2,0.0,0.001,"     Dr.Somnath");
//    DrawTextXY(-1,-.5,0.0,0.0007,"     Designation ");
    DrawTextXY(-1,-.7,0.0,0.001,"       IIT Indore");
    glColor3f(0.3,0.3,0.3);
    DrawTextXY(-1,-1,0.0,0.0008,"     Press any key... ");
    
    glFlush();            //Finish rendering
    glutSwapBuffers();
}

void Dis()
{
    
    if(f==0)
        menu1();
    else if(f==1)
        menu2();
    else if(f==2)
        cover();
    else
        Display();
}

void Reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(50.0,(GLdouble)x/(GLdouble)y,0.10,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
    //Adjust point size to window size
    glPointSize(GLfloat(x)/600.0);
}
int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Flowing Fountain");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,100,1.0);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glLineWidth(2.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    initTexture();//for loading texture
    InitFountain();//for creation of waterdrops
    CreateList();            //for creation of boundary of fountain
    glutDisplayFunc(Dis);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(NormalKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    
    //add the menu and submenus
    //color submenu creation
    int sub_menu=glutCreateMenu(colours);
    glutAddMenuEntry("RANDOM",1);
    glutAddMenuEntry("GREEN",2);
    glutAddMenuEntry("BLUE",3);
    
    // flow sub menu creation
    int sub_menu2=glutCreateMenu(flow);
    glutAddMenuEntry("LOW",8);
    glutAddMenuEntry("MEDIUM",20);
    glutAddMenuEntry("HIGH",40);
    
    //level sub menu creation
    int sub_menu3=glutCreateMenu(level);
    glutAddMenuEntry("4 LEVELS",4);
    glutAddMenuEntry("5 LEVELS",5);
    glutAddMenuEntry("6 LEVELS",6);
    
    //keyboard help sub menu creation
    int sub_menu4=glutCreateMenu(help);
    glutAddMenuEntry("KEYBOARD CONTROLS:",0);
    glutAddMenuEntry("Move Near:  n",1);
    glutAddMenuEntry("Move Away:  a",2);
    glutAddMenuEntry("Move Down:  d",3);
    glutAddMenuEntry("Move Up:    u",4);
    glutAddMenuEntry("Move top:    t",5);
    glutAddMenuEntry("Move front:    f",6);
    
    //light submenu creation
    int sub_menu5=glutCreateMenu(light);
    glutAddMenuEntry("\u2713 light0", 0);
    glutAddMenuEntry("\u2713 light1", 1);
    glutAddMenuEntry("\u2713 light2", 2);
    glutAddMenuEntry("\u2713 light3", 3);
    glutAddMenuEntry("\u2713 light4", 4);
    glutAddMenuEntry("\u2713 light5", 5);
    
    //for playing music sub menu creation
    int sub_menu6=glutCreateMenu(soundplay);
    glutAddMenuEntry("Play", 0);
    glutAddMenuEntry("Reset flag", 1);
    
    //creation of main menu and adding all sub menus in it
    glutCreateMenu(CMain);
    glutAddSubMenu("Colors",sub_menu);
    glutAddSubMenu("Flow",sub_menu2);
    glutAddSubMenu("Level",sub_menu3);
    glutAddSubMenu("Help",sub_menu4);
    glutAddSubMenu("Lights", sub_menu5);
    glutAddSubMenu("Sound Play", sub_menu6);
    
    //attaching submenu to mouse click
    glutAttachMenu(GLUT_RIGHT_BUTTON);//attached to right click
    
    glutIdleFunc(Dis); //sets the global idle callback
//    system("afplay /Users/hardxray007/xcode-workspace/test/test/1.mp3");
    glutMainLoop();
    return 0;
}



