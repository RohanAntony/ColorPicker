#include <stdio.h>
#include <GL/glut.h>

float RED=0.0,GREEN=0.0,BLUE=0.0;
int redPosition=-200,greenPosition=-200,bluePosition=-200;
int redOffset = 0,greenOffset = 0,blueOffset = 0;

void init();
void display();
void drawRedScale(int,int,int);
void drawGreenScale(int,int,int);
void drawBlueScale(int,int,int);
void drawSelect(int,int,int,float,float,float);
void drawColorBoard(int,int,int,int,float,float,float);
void keyPressed(unsigned char,int,int);

int main(int argc,char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(1300,700);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Color Picker");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyPressed);
  glutMainLoop();
  return 0;
}

void init(){
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(-650,650,-350,350);
}

void drawRedScale(int x,int y,int width){
  glBegin(GL_LINES);
  for(int i=0;i<400;i++){
    glColor3f(i/400.0,0,0);
    glVertex2i(x,y+i);
    glVertex2i(x+width,y+i);
  }
  glEnd();
}

void drawGreenScale(int x,int y,int width){
  glBegin(GL_LINES);
  for(int i=0;i<400;i++){
    glColor3f(0,i/400.0,0);
    glVertex2i(x,y+i);
    glVertex2i(x+width,y+i);
  }
  glEnd();
}

void drawBlueScale(int x,int y,int width){
  glBegin(GL_LINES);
  for(int i=0;i<400;i++){
    glColor3f(0,0,i/400.0);
    glVertex2i(x,y+i);
    glVertex2i(x+width,y+i);
  }
  glEnd();
}

void drawSelect(int x,int y,int width,float r,float g,float b){
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);
  glVertex2i(x+width+1,y);
  glVertex2i(x+width+40,y-25);
  glVertex2i(x+width+40,y+25);
  glEnd();
}

void drawColorBoard(int x,int y,int width,int height,float r,float g,float b){

  glBegin(GL_QUADS);
  //black background;
  glColor3f(0,0,0);
  glVertex2i(x-40,y-40);
  glVertex2i(x+width/2,y-40);
  glVertex2i(x+width/2,y+height+40);
  glVertex2i(x-40,y+height+40);

  //white background
  glColor3f(1.0,1.0,1.0);
  glVertex2i(x+width/2+1,y-40);
  glVertex2i(x+width+40,y-40);
  glVertex2i(x+width+40,y+height+40);
  glVertex2i(x+width/2+1,y+height+40);

  //main color part
  glColor3f(r,g,b);
  glVertex2i(x,y);
  glVertex2i(x+width,y);
  glVertex2i(x+width,y+height);
  glVertex2i(x,y+height);
  glEnd();
}

void display(){
  glClearColor(RED,GREEN,BLUE,1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  drawRedScale(-500,-200,120);
  drawGreenScale(-300,-200,120);
  drawBlueScale(-100,-200,120);

  RED = redOffset/400.0;
  GREEN = greenOffset/400.0;
  BLUE = blueOffset/400.0;

  drawSelect(-500,redPosition+redOffset,120,0.2+RED,0,0);
  drawSelect(-300,greenPosition+greenOffset,120,0,0.2+GREEN,0);
  drawSelect(-100,bluePosition+blueOffset,120,0,0,0.2+BLUE);

  drawColorBoard(200,-100,300,200,RED,GREEN,BLUE);

  glEnd();
  glFlush();
}

void keyPressed(unsigned char key,int x,int y){
  if(key == 'Q' || key == 'q'){
    if(redOffset < 400)
      redOffset++;
    printf("red offset:%d\n",redOffset);
  }else if(key == 'W' || key == 'w'){
    if(greenOffset < 400)
      greenOffset++;
    printf("green offset:%d\n",greenOffset);
  }else if(key == 'E' || key == 'e'){
    if(blueOffset < 400)
      blueOffset++;
    printf("blue offset:%d\n",blueOffset);
  }else if(key == 'A' || key == 'a'){
    if(redOffset > 0)
      redOffset--;
    printf("red offset:%d\n",redOffset);
  }else if(key == 'S' || key == 's'){
    if(greenOffset > 0)
      greenOffset--;
    printf("green offset:%d\n",greenOffset);
  }else if(key == 'D' || key == 'd'){
    if(blueOffset > 0)
      blueOffset--;
    printf("blue offset:%d\n",blueOffset);
  }else if(key == 'F' || key == 'f'){
    printf("R:%f,G:%f,B:%f\n",RED,GREEN,BLUE);
  }

  {
    glutPostRedisplay();
  }
}
