/*
* Author :Tharindra Galahena
* Project:simple ocr using neural networks
* Date   :11/09/2012
* icense:
* 
*     Copyright 2012 Tharindra Galahena
*
* This program is free software: you can redistribute it and/or modify it under the terms 
* of the GNU General Public License as published by the Free Software Foundation, either 
* version 3 of the License, or (at your option) any later version. This program is distributed
* in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
* Public License for more details.
*
* You should have received a copy of the GNU General Public License along with This program. 
* If not, see http://www.gnu.org/licenses/.
*
*/

#ifndef SOM_H_
#define SOM_H_

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

typedef struct node{
	int num_inputs;
	float *weights;
	float *inputs;
	float *errors;
	float output;
} node;

typedef struct layer{
	int num_nodes;
	node *chr;
} layer;

class som{
	private:
		int num_inputs;
		int num_outputs;
		int num_weights;
		float leaning_rate;
		float *inputs;
		float *outputs;
		float **weights;
		char *map;
		
	public:
		som();
		som(int in, int out, float lrate);		
		void init();	
		int get_num_weights(); 				
		float **get_weights();  				
		float convert(float input);		
		int learn(float *in, char ch);
		float train(int index);
		char find(float *in);
		void print_map();
		void record();
		bool load();
		char *get_map();
};

#endif
