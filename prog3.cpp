#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <tuple>

GLuint objects;


void display(void) {
  // position of light
  static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 };
  // position of eye
  static double ex = 0.0, ez = 0.0;
  // direction of eye
  static double r = 0.0;

  // clear window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // init modelview matrix
  glLoadIdentity();

  // eye position
  glRotated(r, 0.0, 1.0, 0.0);
  glTranslated(ex, 0.0, ez);

  // light position
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

  // write scene
  glCallList(objects);

  glFlush();
}

void resize(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
  if (key == '\033' || key == 'q') {
    exit(0);
  }
}

void scene(void) {
  static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
  static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
  static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
  static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
  static GLfloat ground[][4] = {
    { 0.6, 0.6, 0.6, 1.0 },
    { 0.3, 0.3, 0.3, 1.0 }
  };

  int i, j;

  objects = glGenLists(1);
  glNewList(objects, GL_COMPILE);

  // red box
  glPushMatrix();
  glTranslated(0.0, 0.0, -3.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(1.0);
  glPopMatrix();

  // green box
  glPushMatrix();
  glTranslated(0.0, 0.0, 3.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glutSolidCube(1.0);
  glPopMatrix();

  // blue box
  glPushMatrix();
  glTranslated(-3.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
  glutSolidCube(1.0);
  glPopMatrix();

  // yellow box
  glPushMatrix();
  glTranslated(3.0, 0.0, 0.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
  glutSolidCube(1.0);
  glPopMatrix();

  // base
  glBegin(GL_QUADS);
  glNormal3d(0.0, 1.0, 0.0);
  int base_size = 20; // defolt = 5
  for (j = -base_size; j < base_size; ++j) {
    for (i = -base_size; i < base_size; ++i) {
      glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
      glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
      glVertex3d((GLdouble)i, -0.5, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j + 1));
      glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
    }
  }
  glEnd();

  glEndList();
}

// x正方向 : 右側
// z正方向 : 前側
// jr はy軸正方向からの角度(degree)

void motion(int x, int y) {
  static bool wrap = false;

  if (!wrap) {
    int ww = glutGet(GLUT_WINDOW_WIDTH);
    int wh = glutGet(GLUT_WINDOW_WIDTH);

    int dx = x - ww / 2;
    int dy = y - wh / 2;
    wrap = true;
    glutWarpPointer(ww / 2, wh /2);
  }
  else {
    wrap = false;
  }
}


void init(void) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  scene();
  init();
  glutMainLoop();
  return 0;
}
