#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include <math.h>
#include "globj.h"

GLobj::GLobj(QWidget *parent)
    : QGLWidget(parent)
{

}

GLobj::~GLobj()
{

}

//Initialize the GL settings
void GLobj::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glLineWidth(2.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
}

//Set up the viewport based on the screen dimensions
//Function is called implicitly by initializeGL and when screen is resized
void GLobj::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is stretched
    if(w>h)
        glViewport((w-h)/2, 0, h, h);
    else
        glViewport(0, (h-w)/2, w, w);

    //setup the projection and switch to model view for transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Paints the GL scene
void GLobj::paintGL()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    float full = 1.0;
    float radius = 0.5;
    float halfRadius = 0.25;

    //Draw a point
    glBegin(GL_POINTS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.90,-halfRadius,0.0);
    glEnd();

    //Draws line
    GLfloat vertex1[] = {-full, 0.0, 0.0};
    GLfloat vertex2[] = {-0.80, 0.0, 0.0};
    glBegin(GL_LINES);
    glColor3f (0.0, 0.0, full);
    glNormal3f(0, 0, 1);
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glEnd();

    //Draws triangle
    GLfloat vertex3[] = {-0.75, -0.75, 0.0};
    GLfloat vertex4[] = {-radius, radius, 0.0};
    GLfloat vertex5[] = {-halfRadius, -0.75, 0.0};
    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 1.0);
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);
    glVertex3fv(vertex5);
    glEnd();

    //Draws square
    glBegin(GL_QUADS);
    glColor3f (1.0, 0.0, 0.0);
    glVertex3f(-halfRadius, halfRadius,  0.0);
    glVertex3f( 0.05, halfRadius,  0.0);
    glVertex3f( 0.05,  full,  0.0);
    glVertex3f(-halfRadius,  full,  0.0);

    //Draws hex
    GLfloat v1[] = {0.05, -0.75, 0.0}; //far right point
    GLfloat v2[] = {0.0, 0.20, 0.0};
    GLfloat v3[] = {-0.15, 0.20, 0.0};
    GLfloat v4[] = {-0.2, -0.75, 0.0}; //far left point
    GLfloat v5[] = {-0.15, - 0.20, 0.0};
    GLfloat v6[] = {0.20, - 0.20, 0.0};
    glBegin(GL_POLYGON);
    glColor3f (1.0, 1.0, 1.0);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v4);
    glVertex3fv(v5);
    glVertex3fv(v6);
    glEnd();

    //Draws Cube
    GLfloat v7[] = {full, -radius, -radius};
    GLfloat v8[] = {full, radius, -radius};
    GLfloat v9[] = {radius, radius, -radius};
    GLfloat v10[] = {radius, -radius, -radius};
    GLfloat v11[] = {full, -radius, radius};
    GLfloat v12[] = {full, radius, radius};
    GLfloat v13[] = {radius, radius, radius};
    GLfloat v14[] = {radius, -radius, radius};
    //FRONT
    glBegin(GL_POLYGON);
    glColor3f (1.5, 0.0, 1.0);
    glVertex3fv(v7);
    glVertex3fv(v8);
    glVertex3fv(v9);
    glVertex3fv(v10);
    glEnd();
    //BACK
    glBegin(GL_POLYGON);
    glColor3f (0.0, 0.0, 1.0);
    glVertex3fv(v11);
    glVertex3fv(v12);
    glVertex3fv(v13);
    glVertex3fv(v14);
    glEnd();
    //LEFT
    glBegin(GL_POLYGON);
    glColor3f (1.0, 1.0, 1.0);
    glVertex3fv(v8);
    glVertex3fv(v7);
    glVertex3fv(v9);
    glVertex3fv(v10);
    glEnd();
    //RIGHT
    glBegin(GL_POLYGON);
    glColor3f (1.0, 0.0, 0.0);
    glVertex3fv(v13);
    glVertex3fv(v14);
    glVertex3fv(v12);
    glVertex3fv(v11);
    glEnd();
    //BOTTOM
    glBegin(GL_POLYGON);
    glColor3f (1.0, 1.0, 1.0);
    glVertex3fv(v13);
    glVertex3fv(v11);
    glVertex3fv(v8);
    glVertex3fv(v10);
    //TOP
    glBegin(GL_POLYGON);
    glColor3f (1.0, 1.0, 1.0);
    glVertex3fv(v12);
    glVertex3fv(v8);
    glVertex3fv(v9);
    glVertex3fv(v7);
    glEnd();

    glEnd();
    glFlush ();
}



