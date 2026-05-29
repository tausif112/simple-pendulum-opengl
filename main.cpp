#include <GL/glut.h>
#include <math.h>

float angle = 45;     // starting position (A)
int direction = -1;

float cx = 320, cy = 420;   // fixed suspension point
float length = 200;         // string length
float bobRadius = 20;

// draw circle using line loop with radius
void drawCircle(float x, float y, float r)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.1416 / 180;
        float dx = r * cos(theta);
        float dy = r * sin(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float bx = cx + length * sin(angle * 3.1416 / 180);
    float by = cy - length * cos(angle * 3.1416 / 180);

    // fixed point as circle
    float fixedRadius = 6;
    drawCircle(cx, cy, fixedRadius);

    // thick horizontal line above the fixed point (flush, longer)
    glLineWidth(1);  // thicker line
    glBegin(GL_LINES);
    glVertex2f(cx - 10, cy + fixedRadius); // left end
    glVertex2f(cx + 100, cy + fixedRadius); // right end
    glEnd();
    glLineWidth(1); // reset line width

    // string
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(bx, by);
    glEnd();

    // bob (circle)
    drawCircle(bx, by, bobRadius);

    glFlush();
}

void update(int value)
{
    angle += direction;

    if(angle > 45 || angle < -45)
        direction = -direction;

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

void init()
{
    glClearColor(1,1,1,1);    // white background
    glColor3f(0,0,0);         // black drawing color

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,640,0,480);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Simple Pendulum");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);

    glutMainLoop();
}

