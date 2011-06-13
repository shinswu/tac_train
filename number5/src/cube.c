#include <stdio.h>
#include <stdlib.h>
#ifdef Darwin
# include <glut.h>
#else
# include <GL/glut.h>
#endif /* Darwin */

GLfloat light_ambient[] = {0.2f, 0.6f, 1.0f, 10.0f};
GLfloat light_diffuse[] = {1.0f, 0.0f, 0.0f, 0.5f};
GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

/* Normals for the 6 faces of a cube. */
static GLfloat _nn[6][3] = {{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
                            {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}};
/* Vertex indices for the 6 faces of a cube. */
static GLint _faces[6][4] = {{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
                     {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}};
/* Vertices array */
static GLfloat _vv[8][3];
static unsigned int _timer_period = 1000/30;       /* gives us roughly 30 fps */

static void _timer_func(int value);
static void _disp_nxt_frame();

void drawBox(void)
{
  int i;

  for (i = 0; i < 6; i++) {
    glBegin(GL_QUADS);
    glNormal3fv(&_nn[i][0]);
    glVertex3fv(&_vv[_faces[i][0]][0]);
    glVertex3fv(&_vv[_faces[i][1]][0]);
    glVertex3fv(&_vv[_faces[i][2]][0]);
    glVertex3fv(&_vv[_faces[i][3]][0]);
    glEnd();
  }
}

void display(void)
{
  static y_camera = 0;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  drawBox();
  glutSwapBuffers();
}

void init(void)
{
  /* Setup cube vertex data. */
  _vv[0][0] = _vv[1][0] = _vv[2][0] = _vv[3][0] = -1;
  _vv[4][0] = _vv[5][0] = _vv[6][0] = _vv[7][0] = 1;
  _vv[0][1] = _vv[1][1] = _vv[4][1] = _vv[5][1] = -1;
  _vv[2][1] = _vv[3][1] = _vv[6][1] = _vv[7][1] = 1;
  _vv[0][2] = _vv[3][2] = _vv[4][2] = _vv[7][2] = 1;
  _vv[1][2] = _vv[2][2] = _vv[5][2] = _vv[6][2] = -1;

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40.0,         /* field of view in degree */ 
                  1.0,         /* aspect ratio */ 
                  1.0, 10.0);  /* Z near and far */ 
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,      /* eye is at (0,0,5) */
            0.0, 0.0, 0.0,      /* center is at (0,0,0) */
            0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* put cube position at an asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("red 3D lighted cube");
  glutDisplayFunc(display);
  init();
  glutTimerFunc(_timer_period, _timer_func, 0);
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}


static void _timer_func(int value)
{
  glutTimerFunc(_timer_period, _timer_func, 0);
  _disp_nxt_frame();
}

static void _disp_nxt_frame()
{
  float Xcamera = 0.25;
  float Ycamera = 0.0;
  float Zcamera = 0.0;
  
  glRotated(0.25, 0.0, 0.0, 1.0);
  glutPostRedisplay();
}
