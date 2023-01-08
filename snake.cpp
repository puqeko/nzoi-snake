#include <iostream>
#include <vector>
#include <chrono>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
// Drawing (display) routine.

const int GRID_SIZE_WIDTH = 72;
const int GRID_SIZE_HEIGHT = 50;

struct snake_section {
  int x;
  int y;
  snake_section* tail;
};

snake_section head{};
enum direction {
  LEFT,
  UP,
  RIGHT,
  DOWN
} direction;

void square_at(int x, int y);

// Initialization routine.
void setup() {
  // Set background (or clearing) color.
  //            r    g    b    a
  glClearColor(1.0, 1.0, 1.0, 0.0);
  direction = UP;
}

void update() {
  switch (direction) {
    case UP:
      head.y++; break;
    case DOWN:
      head.y--; break;
    case LEFT:
      head.x--; break;
    case RIGHT:
      head.x++; break;
  }
}

void draw() {
  // Draw a polygon with specified vertices by walking a linked list
  // starting from the snakes head.
  snake_section* cell = &head;
  while(cell != nullptr) {
    square_at(cell->x, cell->y);
    cell = cell->tail;
  }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {

  // silence unused variable warnings
  // if you do use them then remove these lines
  (void)x;
  (void)y;

  switch(key) {
    case '\27': // Press escape to exit.
      exit(0);
      break;
    case 'a':
      direction = LEFT;
      break;
    case 'w':
      direction = UP;
      break;
    case 'd':
      direction = RIGHT;
      break;
    case 's':
      direction = DOWN;
      break;

    default:
      break;
  }
}




//////////////////////////////////////////////////////////////////
////

const float SQUARE_SIZE = 15.0;

static int screen_width = 0;  // will be set to actual screensize
static int screen_height = 0;  // will be set to actual screensize

void idle() {
  static auto start = chrono::steady_clock::now();
  auto now = chrono::steady_clock::now();
  auto delta = now - start;
  const auto nano_to_sec = 1e9;
  if (delta.count() > nano_to_sec / 5) {  // 5 times per second
    start = now;
    update();
    glutPostRedisplay();
  }
}

void square_at(int x, int y) {
  glBegin(GL_POLYGON);
    glVertex3f(x * SQUARE_SIZE      , y * SQUARE_SIZE, 0.0);
    glVertex3f((x + 1) * SQUARE_SIZE, y * SQUARE_SIZE, 0.0);
    glVertex3f((x + 1) * SQUARE_SIZE, (y + 1) * SQUARE_SIZE, 0.0);
    glVertex3f(x * SQUARE_SIZE      , (y + 1) * SQUARE_SIZE, 0.0);
  glEnd();
}

void drawScene() {
  // Clear screen to background color.
  glClear(GL_COLOR_BUFFER_BIT);

  // Set foreground (or drawing) color.
  glColor3f(0.0, 0.0, 0.0);

  draw();

  // Flush created objects to the screen, i.e., force rendering.
  glFlush(); 
}

// OpenGL window reshape routine.
void resize(int w, int h) {

  // Set viewport size to be entire OpenGL window.
  screen_height = h;
  screen_width = w;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);

  // Set matrix mode to projection.
  glMatrixMode(GL_PROJECTION);

  // Clear current projection matrix to identity.
  glLoadIdentity();

  // Specify the orthographic (or perpendicular) projection, 
  // i.e., define the viewing box.
  glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

  // Set matrix mode to modelview.
  glMatrixMode(GL_MODELVIEW);

  // Clear current modelview matrix to identity.
  glLoadIdentity();
}

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) {

  // Initialize GLUT.
  glutInit(&argc, argv);

  // Set display mode as single-buffered and RGB color.
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  // Set OpenGL window size.
  glutInitWindowSize(GRID_SIZE_WIDTH*SQUARE_SIZE, GRID_SIZE_HEIGHT*SQUARE_SIZE);

  // Set position of OpenGL window upper-left corner.
  glutInitWindowPosition(100, 100);

  // Create OpenGL window with title.
  glutCreateWindow("square.cpp");

  // Initialize.
  setup();

  // Register display routine.
  glutDisplayFunc(drawScene);

  // Register reshape routine.
  glutReshapeFunc(resize);

  // Register keyboard routine.
  glutKeyboardFunc(keyInput);
  
  // Register update routine.
  glutIdleFunc(idle);

  // Begin processing.
  glutMainLoop();
  
  return 0;
}