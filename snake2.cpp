#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
// Drawing (display) routine.

const float SQUARE_SIZE = 60.0;
const float SPEED = 20.0;

static int screen_width = 0;
static int screen_height = 0;
static int x_pos = 20;
static int y_pos = 20;

void drawScene() {
  // Clear screen to background color.
  glClear(GL_COLOR_BUFFER_BIT);

  // Set foreground (or drawing) color.
  glColor3f(0.0, 0.0, 0.0);

  // Draw a polygon with specified vertices.
  glBegin(GL_POLYGON);
    glVertex3f(x_pos              , y_pos              , 0.0);
    glVertex3f(x_pos + SQUARE_SIZE, y_pos              , 0.0);
    glVertex3f(x_pos + SQUARE_SIZE, y_pos + SQUARE_SIZE, 0.0);
    glVertex3f(x_pos              , y_pos + SQUARE_SIZE, 0.0);
  glEnd();

   // Flush created objects to the screen, i.e., force rendering.
   glFlush(); 
}

// Initialization routine.
void setup() {

   // Set background (or clearing) color.
   glClearColor(1.0, 1.0, 1.0, 0.0); 
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

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
  cout << (int)key << endl;
   switch(key) {
      case 27: // Press escape to exit.
         exit(0);
         break;
      case 'a':   // left arrow
        x_pos -= SPEED;
        break;
      case 'w':   // up arrow
        y_pos += SPEED;
        break;
      case 'd':   // right arrow
        x_pos += SPEED;
        break;
      case 's':   // down arrow
        y_pos -= SPEED;
        break;

      default:
         break;
   }
   glutPostRedisplay();
}

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) {

   // Initialize GLUT.
   glutInit(&argc, argv);

   // Set display mode as single-buffered and RGB color.
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

   // Set OpenGL window size.
   glutInitWindowSize(500, 500);

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

   // Begin processing.
   glutMainLoop();
   
   return 0;
}