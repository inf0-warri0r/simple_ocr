/*
* Author :Tharindra Galahena
* Project:simple ocr using neural networks
* Date   :11/09/2012
* License:
* 
*     Copyright 2012 Tharindra Galahena
*
* This program is free software: you can redistribute it and/or modify it under the terms of 
* the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version. This program is distributed
* in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with This program. 
* If not, see http://www.gnu.org/licenses/.
*
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glui.h>
#include <fstream>

#include "som.h"

#define MAX  120
#define NMAX   8

using namespace std;

som *s;

char text[2];
char grid[MAX][MAX];
char normal_grid[NMAX][NMAX];

int  lst  = 0;
bool draw = false;

int  min_x = MAX;
int  min_y = MAX;
int  max_x = 0;
int  max_y = 0;
int  train = 0;

float min_draw_x = -8.0;
float min_draw_y = -8.0;
float max_draw_x =  8.0;
float max_draw_y =  8.0;

float width  = 16.0;
float height = 16.0; 

float leaning_rate = 0.1;
float num_chars    = 26;
float max_error    = 0.0000001;
float iterations   = 1000000;

int  main_window;
GLUI_EditText *edittext;
GLUI_Listbox* lis;

void cell(float x1, float x2, float y1, float y2){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	
	glVertex3f(x1, y1, 0.0);
	glVertex3f(x2, y1, 0.0);
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x1, y2, 0.0);

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();

	glTranslatef(0.0, 0.0, -22.0);
	
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			if(grid[i][j] == '1')
				cell(min_draw_x + (width  /MAX) * j,
					min_draw_y + (width  /MAX) * (j + 1),
					max_draw_x - (height /MAX) * i,
					max_draw_y - (height /MAX) * (i - 1));
		}
	}
	
	glutSwapBuffers();
}
void clear_grid(int a){
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			grid[i][j] = '0';
		}
	}
	edittext -> set_text("");
	glutPostRedisplay();
}
void clear_normal_grid(){
	for(int i = 0; i < NMAX; i++){
		for(int j = 0; j < NMAX; j++){
			normal_grid[i][j] = '0';
		}
	}
}
void draw_normal_grid(){
	for(int i = 0; i < NMAX; i++){
		for(int j = 0; j < NMAX; j++){
			cout << " " << normal_grid[i][j];
		}
		cout << endl;
	}
}
void set_draw_range(){
	min_x = MAX;
	min_y = MAX;
	max_x = 0;
	max_y = 0;
	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			if(grid[i][j] == '1'){
				if(i <= min_y){
					min_y = i;
				}
				if(i >= max_y){
					max_y = i;
				}
				if(j <= min_x){
					min_x = j;
				}
				if(j >= max_x){
					max_x = j;
				}
			}
		}
	}
	if(max_x - min_x < NMAX){
		max_x += 4;
		min_x -= 4;
	}
	if(max_y - min_y < NMAX){
		max_y += 4;
		min_y -= 4;
	}
}
void normalize(){
	clear_normal_grid();
	set_draw_range();
	
	int xb = (max_x - min_x) / 8; 
	int yb = (max_y - min_y) / 8; 

	for(int i = min_y; i < max_y; i++){
		for(int j = min_x; j < max_x; j++){
			int y = (i - min_y) / yb;
			int x = (j - min_x) / xb;
			if(x > NMAX - 1) x = NMAX - 1;
			if(y > NMAX - 1) y = NMAX - 1;
			if(grid[i][j] == '1') normal_grid[y][x] = '1';
		}
	}
	draw_normal_grid();
}

void set_normal_grid(float *in){
	int n = 0;
	for(int i = 0; i < NMAX; i++){
		for(int j = 0; j < NMAX; j++){
			if(normal_grid[i][j] == '1')
				in[n] = 1.0;
			else
				in[n] = 0.0;
			n++;
		}
	}
}
void tr(char c){
	float in[NMAX * NMAX];
	set_normal_grid(in);
	int index = s -> learn(in, c);
	bool b = false;
	int i;
	float error;
	for(i = 0; i < iterations && !b; i++){	
		error = s -> train(index);
		if(error < max_error) b = true;
	}
}
void find(){
	draw_normal_grid();
	float in[NMAX * NMAX];
	set_normal_grid(in);
	char ch[2];
	ch[0] = s -> find(in);
	ch[1] = '\0';
	cout << s -> find(in) << endl;
	edittext -> set_text(ch);
}
void keyboard(unsigned char key, int x, int y){
	if(key == 27) {		
		exit(0);
	}else if((char)key == 's'){
		if(!draw) draw = true;
		else draw = false;
	}
}
void init(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);
}
void Reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluPerspective(45.0, (float)w/(float)h, 0.1, 200.0);
}

void mouse( int x, int y){
	if(draw){
		int gy = MAX - ((max_draw_y - y/45.0f) * MAX ) / height - MAX/2;
		int gx = ((x/45.0f - max_draw_x) * MAX ) / width + MAX/2;
		cout << gy << " " << gx << endl;
		if(gx >= 0 && gx < MAX){
			if(gy >= 0 && gy < MAX)
				grid[gy][gx] = '1'; 
		}
	}
	glutPostRedisplay();
}
void callback(int a){
	edittext -> get_text();
	normalize();
	if(lst == 0) lis -> delete_item(0);
	if(train){
		if(strcmp(text, "") != 0){
			tr(text[0]);
			char ch[2];
			ch[0] = text[0];
			ch[1] = '\0';
			lis -> add_item(lst++, ch);
			edittext -> set_text("Done");
		}
	}else{
		edittext -> set_text("");
		find();
	}
}
void load(int a){
	if(!s -> load()){
		edittext -> set_text("Error");
		return;
	}
	edittext -> set_text("loaded");
	char *map = s -> get_map();
	if(lst == 0) lis -> delete_item(0);
	for(int i = 0; i < lst; i++) lis -> delete_item(i);
	lst = 0;
	for(int i = 0; i < 26; i++){
		if(map[i] != '_'){
			char ch[2];
			ch[0] = map[i];
			ch[1] = '\0';
			lis -> add_item(lst, ch);
			lst++;
		}
	}
}
void record(int a){
	s -> record();
	edittext -> set_text("saved");
}
int main(int argc, char** argv){
	
	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(500,0);
	main_window = glutCreateWindow("inf0_warri0r - ocr");
	
	GLUI *glui = GLUI_Master.create_glui("inf0_warri0r - ocr");
	
	GLUI_Panel *pan = glui->add_panel("");
	GLUI_Panel *panels = glui->add_panel_to_panel(pan, "");
	glui->add_checkbox_to_panel(panels, "Training mode", &train);
	int li;
	glui->add_column_to_panel(pan, true);
	GLUI_Panel *panel0 = glui->add_panel_to_panel(pan, "");
	
	lis = glui -> add_listbox_to_panel(panel0, "List : ", &li);
	lis -> add_item(0, "");
	lst = 0;
	glui->add_column_to_panel(pan, true);
	GLUI_Panel *panel1 = glui->add_panel_to_panel(pan, "");
	edittext = glui->add_edittext_to_panel(panel1, "Char : ", GLUI_EDITTEXT_TEXT, text);
	glui->add_column_to_panel(panel1, false);
	edittext -> set_w(30);
	GLUI_Panel *panel = glui->add_panel("");
	
	glui->add_button_to_panel(panel, "train/find", 0, callback);
	glui->add_column_to_panel(panel, false);
	glui->add_button_to_panel(panel, "load", 0, load);
	glui->add_column_to_panel(panel, false);
	glui->add_button_to_panel(panel, "save", 0, record);
	glui->add_column_to_panel(panel, false);
	glui->add_button_to_panel(panel, "clear", 0, clear_grid);
	glui->set_main_gfx_window(main_window);
	GLUI_Master.set_glutReshapeFunc( Reshape );
	
	clear_grid(1);
	clear_normal_grid();
	s = new som(NMAX * NMAX, num_chars, leaning_rate);
	s -> init();
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutPassiveMotionFunc(mouse);
	glutMainLoop();
	return 0;
}
