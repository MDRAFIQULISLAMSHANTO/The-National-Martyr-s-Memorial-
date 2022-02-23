/*
Things to add in animation::>

1) Morning, Day and Night smooth transition -> slowly changing glClearColor values back and forth according to glutTimerFunction
2) sun will move from left to right, when sun disappears moon come into play. No cloud in night mode
3) When it is morning and day mode the people will come animated from right into the screen. and while they are into the screen music will be played in loop.
4) There should be a fade in fade out effect in music when the people with banner comes in and go out.
5) Extra lighting and shading (according to morning, day and night view-mode)
6) Birds (Optional)




*/





#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include<windows.h>



//for banner
char text[] = "                        16th    December";
char text2[] = "                       Happy   Victory Day";


unsigned char viewMode = 'd';


//Background skyColor
GLclampf skyColorRed = 0.133;
GLclampf skyColorGreen = 0.585;
GLclampf skyColorBlue = 0.899;

//Cloud color
GLfloat cloudRed=1;
GLfloat cloudGreen=1;
GLfloat cloudBlue=1;


void Sprint( float x, float y, char *st)
{
    int l,i;
    l=strlen( st );
    glColor3f(0.0,1.0,0.0);
    glRasterPos2f( x, y);
    for( i=0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);

    }
}

GLfloat sunRayRotate = 0;

GLfloat sunpositionY=0.8;



void drawSunRays(GLdouble radius,GLfloat x,GLfloat y)
{

    glColor3ub(180, 64.7, 10);

    glPushMatrix(); //glPushMatrix copies the top matrix and pushes it onto the stack, while glPopMatrix pops the top matrix off the stack
    //glTranslatef(.1,.1,0);

    glTranslatef(x,y,0);
    glRotatef(sunRayRotate,0,0,-0.3);//i=how many degree you want to rotate around an axis

    glLineWidth(5);
    glBegin(GL_LINES);

    glVertex2f(0.0f, 0.0f);
    glVertex2f( radius+0.02f, radius);

    glVertex2f( 0.0f, 0.0f);
    glVertex2f( radius+0.04f, radius-0.03f);

    glVertex2f( 0.0f, 0.0f);
    glVertex2f( radius+0.04f, radius-0.06f);



    glEnd();



    glPopMatrix();


    sunRayRotate+=0.1f;

}

void drawFilledSun(GLfloat x, GLfloat y, GLdouble radius)
{

    //glColor3ub(253, 184, 19);
    //rgb(250,226,1)
    glColor3ub(250,226,1);
    double twicePi = 2.0 * 3.142;
    drawSunRays(radius,x,y);
    glLoadIdentity();
    glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
    glVertex2f(x, y); // center of circle
    for (int i = 0; i <= 10000; i++)
    {
        glVertex2f (
            (x + (radius * cos(i * twicePi / 20))), (y + (radius * sin(i * twicePi / 20)))
        );
    }
    glEnd(); //END
}

void dayToNightAutoTrans()
{
    if(skyColorRed == 0.07 && skyColorGreen == 0.09 && skyColorBlue == 0.38){
            viewMode = 't';
        }

    if(viewMode=='d')
    {
        skyColorRed-= 0.001;
        skyColorGreen-=0.001;
        skyColorBlue-=0.001;

        cloudRed -= 0.001;
        cloudGreen -= 0.001;
        cloudBlue -= 0.001;

        glClearColor(skyColorRed, skyColorGreen, skyColorBlue,0.0);
        glutPostRedisplay();
        if(skyColorBlue<=0 && skyColorRed<=0 && skyColorGreen<=0)
        {
            viewMode = 'n';
        }
    }
    else
    {


        if(skyColorBlue<=0.899)
        {
            skyColorBlue += 0.001;
            if(skyColorGreen<=0.585)
            {
                skyColorGreen+=0.001;
                if(skyColorRed<=0.133)
                {
                    skyColorRed+=0.001;


                    cloudRed += 0.001;
                    cloudGreen += 0.001;
                    cloudBlue += 0.001;
                }
            }
        }
        else
        {

            viewMode='d';

        }

        glClearColor(skyColorRed, skyColorGreen, skyColorBlue,0.0);
        glutPostRedisplay();
    }
}
float cloudSpeed=100;

GLfloat peopleNtext = 0;
void update(int value)
{


//day -> night auto transition
    dayToNightAutoTrans();
//cloud movement management

    if(cloudSpeed<-150)
    {
        cloudSpeed=100;
    }

    //sun and moon positioning

    if(sunpositionY<-0.8 && viewMode=='t' || viewMode=='n'){
        sunpositionY = 1.1;
    }
    if(viewMode=='d'){
            if(peopleNtext>=0){
        peopleNtext-=1;
            }
    }

    glutTimerFunc(10, update, 0);
}


void myInit (void)
{
    glClearColor(skyColorRed, skyColorGreen, skyColorBlue,0.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0.0, 400.0, -70, 380.0);

}

GLfloat cloudAnimSpeed = 0.3;
void danimateCloud()
{
//Cloud 1

    glPushMatrix();




    glTranslatef(50+cloudSpeed, 300, 0);

    glBegin(GL_POLYGON);

    glColor3f(cloudRed, cloudGreen, cloudBlue);

    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(35+cloudSpeed, 280, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=25;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(55+cloudSpeed, 280, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(40+cloudSpeed, 260, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();




//cloud 2
    glPushMatrix();
    glTranslatef(350+cloudSpeed, 100, 0);
    glPushMatrix();
    glTranslatef(-150+cloudSpeed, 180, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-140+cloudSpeed, 160, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-120+cloudSpeed, 180, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-135+cloudSpeed, 200, 0);

    glBegin(GL_POLYGON);
    glColor3f(cloudRed, cloudGreen, cloudBlue);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=20;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();


    glPopMatrix();
    glPopMatrix();

    cloudSpeed-=cloudAnimSpeed;

}


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    drawFilledSun(0,sunpositionY,0.1);
    glPopMatrix();
    if(sunpositionY > 0.5 && sunpositionY < 1){
        sunpositionY-=0.001;
    }
    else{
    sunpositionY-=0.002;
    }




    //ground 1st
    glColor3f(0.7, 0.3, 0.2) ;
    glBegin(GL_QUADS);
    glVertex2i (0, 30);
    glVertex2i (0, 15);
    glVertex2i (400, 15);
    glVertex2i (400, 30);
    glEnd();

    //ground 2nd

    glColor3f(0.5, 0.3, 0.2) ;
    glBegin(GL_QUADS);
    glVertex2i (0, 15);
    glVertex2i (0, -50);
    glVertex2i (400, -50);
    glVertex2i (400, 15);
    glEnd();


    //ground 3rd
    glColor3f(0.4, 0.3, 0.2) ;
    glBegin(GL_QUADS);
    glVertex2i (0, -50);
    glVertex2i (0, -70);
    glVertex2i (400, -70);
    glVertex2i (400, -50);
    glEnd();



    //trin 1 main
    glColor3ub(29, 130, 32) ;
    glBegin(GL_QUADS);
    glVertex2i (0, 130);
    glVertex2i (0, 30);
    glVertex2i (400, 30);
    glVertex2i (400, 130);
    glEnd();






    // Hill


    glPushMatrix();
       //sun in the back


    glTranslatef(30, 120, 0);

    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);

    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=55;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(80, 140, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();



    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(100, 140, 0);



    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();



    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(120, 140, 0);


    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(180, 120, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=55;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();



    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(270, 110, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=55;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(270, 145, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(290, 140, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(310, 140, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(360, 120, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(29, 130, 32);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=55;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    //Tree 1
    glPushMatrix();
    glTranslatef(-28, 23, 0);


    glPushMatrix();
    glTranslatef(50, 170, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(60, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(40, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glColor3ub(120, 32, 12);
    glBegin(GL_QUADS);
    glVertex2i(48, 130);
    glVertex2i(47, 40);
    glVertex2i(52, 40);
    glVertex2i(51, 130);
    glEnd();


    glPopMatrix();


//Tree 2


    glPushMatrix();
    glTranslatef(320, 43, 0);


    glPushMatrix();
    glTranslatef(50, 170, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(60, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(40, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glColor3ub(120, 32, 12);
    glBegin(GL_QUADS);
    glVertex2i(48, 130);
    glVertex2i(47, 40);
    glVertex2i(52, 40);
    glVertex2i(51, 130);
    glEnd();


    glPopMatrix();

//Tree 3
    glPushMatrix();
    glTranslatef(0, 37, 0);


    glPushMatrix();
    glTranslatef(50, 170, 0);


    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(60, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(40, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glColor3ub(120, 32, 12);
    glBegin(GL_QUADS);
    glVertex2i(48, 130);
    glVertex2i(47, 67);
    glVertex2i(52, 67);
    glVertex2i(51, 130);
    glEnd();

    glPopMatrix();


//Tree 4
    glPushMatrix();
    glTranslatef(35, 13, 0);


    glPushMatrix();
    glTranslatef(50, 170, 0);


    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();



    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(60, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();



    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(40, 150, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glColor3ub(120, 32, 12);
    glBegin(GL_QUADS);
    glVertex2i(48, 130);
    glVertex2i(47, 40);
    glVertex2i(52, 40);
    glVertex2i(51, 130);
    glEnd();


    glPopMatrix();


// Tree 5
    glPushMatrix();
    glTranslatef(290, 4, 0);

    glPushMatrix();
    glTranslatef(50, 170, 0);



    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);



    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(60, 150, 0);


    glPushMatrix();

    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(40, 150, 0);

    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3ub(12, 120, 41);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=15;
        float x = r * cos(A);
        float y = r * sin(A)*1.5;
        glVertex2f(x,y );
    }
    glEnd();


    glPopMatrix();
    glPopMatrix();


    glColor3ub(120, 32, 12);
    glBegin(GL_QUADS);
    glVertex2i(48, 130);
    glVertex2i(47, 70);
    glVertex2i(52, 70);
    glVertex2i(51, 130);
    glEnd();


    glPopMatrix();



//clouds here
    danimateCloud();


//trin 1


    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(40, 30);
    glVertex2i (180, 62);

    glVertex2i (180, 62);
    glVertex2i (320, 30);

    glVertex2i (320, 30);
    glVertex2i (40, 30);

    glEnd();



//trin 1 main
    glColor3f(0.6, 0.6, 0.6) ;
    glBegin(GL_POLYGON);

    glVertex2i(43, 30);
    glVertex2i (317, 30);

    glVertex2i (317, 30);
    glVertex2i (180, 60);

    glVertex2i (180, 60);
    glVertex2i (43, 30);

    glEnd();



//trn2
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(60, 30);
    glVertex2i (180, 102);

    glVertex2i (180, 102);
    glVertex2i (300, 30);

    glVertex2i (300, 30);
    glVertex2i (60, 30);
    glEnd();


//trn2 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(62, 30);
    glVertex2i (180, 100);

    glVertex2i (180, 100);
    glVertex2i (298, 30);

    glVertex2i (298, 30);
    glVertex2i (62, 30);

    glEnd();


//trn3
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(80, 30);
    glVertex2i (180, 152);

    glVertex2i (180, 152);
    glVertex2i (280, 30);

    glVertex2i (280, 30);
    glVertex2i (80, 30);

    glEnd();



//trn3 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(81, 30);
    glVertex2i (180, 150);

    glVertex2i (180, 150);
    glVertex2i (279, 30);

    glVertex2i (279, 30);
    glVertex2i (81, 30);

    glEnd();



//trn 4
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(100, 30);
    glVertex2i (180, 202);

    glVertex2i (180, 202);
    glVertex2i (260, 30);

    glVertex2i (260, 30);
    glVertex2i (100, 30);

    glEnd();



//trn4 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(101, 30);
    glVertex2i (180, 200);

    glVertex2i (180, 200);
    glVertex2i (259, 30);

    glVertex2i (259, 30);
    glVertex2i (101, 30);

    glEnd();



//trn 5

    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(120, 30);
    glVertex2i (180, 252);

    glVertex2i (180, 252);
    glVertex2i (240, 30);

    glVertex2i (240, 30);
    glVertex2i (120, 30);

    glEnd();



//trn5 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(121, 30);
    glVertex2i (180, 250);

    glVertex2i (180, 250);
    glVertex2i (239, 30);

    glVertex2i (239, 30);
    glVertex2i (121, 30);

    glEnd();



//trn 6
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(140, 30);
    glVertex2i (180, 302);

    glVertex2i (180, 302);
    glVertex2i (220, 30);

    glVertex2i (220, 30);
    glVertex2i (140, 30);

    glEnd();



//trn6 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(141, 30);
    glVertex2i (180, 300);

    glVertex2i (180, 300);
    glVertex2i (219, 30);

    glVertex2i (219, 30);
    glVertex2i (141, 30);

    glEnd();



//trn 7
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(160, 30);
    glVertex2i (180, 351);

    glVertex2i (180, 351);
    glVertex2i (200, 30);

    glVertex2i (200, 30);
    glVertex2i (160, 30);

    glEnd();




//trn7 main
    glColor3f(0.4, 0.4, 0.4) ;
    glBegin(GL_POLYGON);

    glVertex2i(161, 30);
    glVertex2i (180, 350);

    glVertex2i (180, 350);
    glVertex2i (199, 30);

    glVertex2i (199, 30);
    glVertex2i (161, 30);

    glEnd();




//middle line.
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(167, 145);
    glVertex2i (167, 148);

    glVertex2i (167, 148);
    glVertex2i (193, 148);

    glVertex2i (193, 148);
    glVertex2i (193, 145);

    glVertex2i (193, 145);
    glVertex2i (167, 145);

    glEnd();




//under train main
    glColor3f(0.3, 0.3, 0.3) ;
    glBegin(GL_POLYGON);

    glVertex2i(168, 145);
    glVertex2i (180, 91);

    glVertex2i (180, 91);
    glVertex2i (192, 145);

    glVertex2i (192, 145);
    glVertex2i(168, 145);


    glEnd();




//upper train main
    glColor3f(0.3, 0.3, 0.3)  ;
    glBegin(GL_POLYGON);

    glVertex2i(168, 148);
    glVertex2i (180, 197);

    glVertex2i (180, 197);
    glVertex2i (192, 148);

    glVertex2i (192, 148);
    glVertex2i(168, 148);

    glEnd();




//low train
    glColor3f(1.0, 1.0, 1.0) ;
    glBegin(GL_POLYGON);

    glVertex2i(160, 30);
    glVertex2i (180, 44);

    glVertex2i (180, 44);
    glVertex2i (200, 30);

    glVertex2i (200, 30);
    glVertex2i(160, 30);

    glEnd();



//low train main
    glColor3f(0.7, 0.3, 0.2) ;
    glBegin(GL_POLYGON);

    glVertex2i(162, 30);
    glVertex2i (180, 42);

    glVertex2i (180, 42);
    glVertex2i (198, 30);

    glVertex2i (198, 30);
    glVertex2i(162, 30);


    glEnd();



//Middle line top to bottom
    glColor3f(1.0, 1.0, 1.0) ; ;
    glBegin(GL_LINES);

    glVertex2i (180, 44);
    glVertex2i (180, 91);

    glVertex2i (180, 197);
    glVertex2i (180, 350);

    glEnd();





// Figure 1
    glPushMatrix();

    glPushMatrix();
    glTranslatef(310+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y );
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);


//dress

    glColor3f(1.0, 0.0, 1.0);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);


//ear


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);

    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();


    glPopMatrix();


// Figure 2
    glPushMatrix();
    glTranslatef(330+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y );
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();



    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();

    glPopMatrix();


// Figure 3
    glPushMatrix();
    glTranslatef(350+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y);
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);

    glColor3f(1.0, 0.1, 0.0);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();

    glPopMatrix();




// Figure 4

    glPushMatrix();
    glTranslatef(370+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y );
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);

    glColor3f(1.1, 1.1, 1.1);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();

    glPopMatrix();


// Figure 5

    glPushMatrix();
    glTranslatef(290+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y );
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);

    glColor3f(1.0, 1.0, 0.0);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();

    glPopMatrix();


// Figure 6

    glPushMatrix();
    glTranslatef(270+peopleNtext, 33, 0);

    glBegin(GL_POLYGON);
    glColor3ub(225, 227, 104);


    for(int i=0; i<200; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float r=4;
        float x = r * cos(A);
        float y = r * sin(A)*3;
        glVertex2f(x,y );
    }
    glEnd();


    glBegin(GL_QUADS);
    glColor3ub(209, 30, 17);
    glVertex2i (-1, -10);
    glVertex2i (-2, -16);
    glVertex2i (2, -16);
    glVertex2i (1, -10);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2i (-6, -16);
    glVertex2i (-8, -22);
    glVertex2i (8, -22);
    glVertex2i (6, -16);

    glVertex2i (-4, -22);
    glVertex2i (-5, -32);
    glVertex2i (5, -32);
    glVertex2i (4, -22);

    glColor3ub(23, 18, 3);
    glVertex2i (-3, -33);
    glVertex2i (-3, -80);
    glVertex2i (-1, -80);
    glVertex2i (-1, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-1, -80);
    glVertex2i (-2, -83);
    glVertex2i (-4, -83);
    glVertex2i (-3, -80);

    glColor3ub(23, 18, 3);
    glVertex2i (1, -33);
    glVertex2i (1, -80);
    glVertex2i (3, -80);
    glVertex2i (3, -33);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (1, -80);
    glVertex2i (2, -83);
    glVertex2i (4, -83);
    glVertex2i (3, -80);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.0, 0.7, 0.0);
    glVertex2i (-4, 7);
    glVertex2i (-4, 0);
    glVertex2i (4, 0);
    glVertex2i (4, 7);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-2, 13);
    glVertex2i (-4, 7);
    glVertex2i (4, 7);
    glVertex2i (2, 13);

    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i (-4, 0);
    glVertex2i (-4, -5);
    glVertex2i (-3, -5);
    glVertex2i (-3, 0);

    glVertex2i (4, 0);
    glVertex2i (4, -5);
    glVertex2i (3, -5);
    glVertex2i (3, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);


    for(int i=0; i<50; i++)
    {
        float pi=3.1416;
        float A=(i*2*pi)/50;
        float r=1.2;
        float x = r * cos(A);
        float y = r * sin(A)*2;
        glVertex2f(x,y+3 );
    }
    glEnd();

    glPopMatrix();


// Text
    glColor3ub(222, 13, 0);
    glBegin(GL_QUADS);
    glVertex2i(260+peopleNtext, -40);
    glVertex2i(260+peopleNtext, 10);
    glVertex2i(380+peopleNtext, 10);
    glVertex2i(380+peopleNtext, -40);
    glEnd();


    glPushMatrix();
    glTranslatef(30+peopleNtext, 180, 0);
    Sprint(240,-190,text);
    Sprint(240,-210,text2);
    glPopMatrix();

glPopMatrix();

if(viewMode=='t' || viewMode == 'n'){
    if(peopleNtext<=200){

    peopleNtext+=1;
    }
}

//flag stand

    glPushMatrix();
    glTranslatef(-180, -60, 0);

    glColor3f(0.2, 0.4, 0.4) ; ;
    glBegin(GL_POLYGON);

    glVertex2i(370, 0);
    glVertex2i (372, 0);

    glVertex2i (372, 0);
    glVertex2i (372, 310);

    glVertex2i (372, 300);
    glVertex2i (370, 305);

    glVertex2i (370, 310);
    glVertex2i (370, 0);

    glEnd();


//flag
    glColor3f(0.0, 0.6, 0.0) ; ;
    glBegin(GL_QUADS);
    glVertex2i (340, 300);
    glVertex2i (340, 260);
    glVertex2i (370, 260);
    glVertex2i (370, 300);



    glEnd();


    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);

    float angle;
    for(int i=0; i<360; i++)
    {
        angle = i * 3.1416/180;
        glVertex2f(355+cos(angle)*5, 280+sin(angle)*12);
    }

    glEnd();

    glPopMatrix();

    glFlush();

}

// declare keyboard, mouse and special key function::>
void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        //mouse clicked left
    cloudAnimSpeed+=0.1;
    }
    if (button == GLUT_RIGHT_BUTTON)
    {
        //mouse clicked right
        cloudAnimSpeed-=0.1;
    }
    glutPostRedisplay();

}



void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        //pressed a
            PlaySound("ek-sagor-rokter-18865.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);


        break;
    case 's':
        //pressed s
            PlaySound(NULL, NULL, SND_ASYNC|SND_FILENAME);

        break;
    }
    glutPostRedisplay();

}

void arrowInput(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        //left arrow pressed
        peopleNtext-=1;

        break;
    case GLUT_KEY_RIGHT:
        //right arrow pressed
        peopleNtext+=1;

        break;
    }
    glutPostRedisplay();
}



int main (int argc, char **argv)
{

    glutInit (&argc, argv);
    glutInitWindowSize (1920, 1080);
    glutCreateWindow ("National Memorial");

    //Display, keyboard and mouse function
    glutDisplayFunc (myDisplay);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(arrowInput);
    glutMouseFunc(handleMouse);

    glutTimerFunc(25,update,0);

    myInit();
    glutMainLoop();


    return 0;
}
