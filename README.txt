simple OCR using neural networks
=================================

this is a simple ocr created using neural networks (self organizing maps).

compiling :
-------------

you need "glui", "opengl" and "glut" libraries to compile . install them 
by running,

sudo apt-get install freeglut3-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglui-dev

on terminal. the type make.

running:
---------

double click on the compiled file and run the application. it will open
 two windows, a control window and a window to draw characters. first 
you have to train the OCR. so you need to check the "training mode"
check box first. the move to the drawing window and draw the character.
to draw you need type 's' first. then draw using mouse (no need of clicking) 
. when you want to stop type 's' again. for example if you 
want to draw 'T' , get the mouse pointer to the correct position, type 's'
draw vertical line, then type 's' to stop drawing then get pointer to the 
place where the horizontal line should start and press 's' again and draw
the line. then press 's' again to stop. then on the control window type the 
character you draw on the text field. then click 'train/find' button. you 
can train up to 26 characters like this. to save the trained characters use 
save button. it will save it to a file called 'weights.data'. later you can
lode this file using 'load' button. (there is a 'weights.data' file in the 
folder which is trained for capital 26 letters of English language)

after loading or training the app check off the 'training mode' check box. 
then draw a character and hit 'train/find' button. the result will be shown 
on the text field if the app is trained to that character. all the 
characters that app is currently trained are shown on the list box on the 
control window. 
 

more inf0 :
-----------

http://www.inf0warri0r.blogspot.com
tcg.galahena@gmail.com 

License :
---------

	Copyright 2012 Tharindra Galahena

This program is free software: you can redistribute it and/or modify it under the terms 
of the GNU General Public License as published by the Free Software Foundation, either 
version 3 of the License, or (at your option) any later version. This program is
distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even 
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License along with This 
program. If not, see http://www.gnu.org/licenses/.
