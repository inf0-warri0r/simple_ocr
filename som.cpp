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

#include "som.h"

som :: som(){
}
som :: som(int in, int out, float lrate){
	num_inputs = in;
	num_outputs = out;
	num_weights = in * out;
	leaning_rate = lrate;
	weights = (float **)malloc(sizeof(float *) * num_outputs);
	inputs  = (float  *)malloc(sizeof(float  ) *  num_inputs);
	outputs = (float  *)malloc(sizeof(float  ) * num_outputs);
	for(int i = 0; i < num_outputs; i++){
		weights[i] = (float *)malloc(sizeof(float) * num_inputs);
	}
	map = (char *)malloc(num_outputs);
	for(int i = 0; i < num_outputs; i++){
		map[i] = '_';
	}
}
void som :: init(){
	for(int i = 0; i < num_outputs; i++){
		for(int j = 0; j < num_inputs; j++){
			weights[i][j] = (float)rand() / (float)RAND_MAX - 0.5;
		}
	}
}
void som :: print_map(){
	for(int i = 0; i < num_outputs; i++){
		cout << map[i] << " ";
	}
	cout << endl;
}
char* som :: get_map(){
		return map;
}
int som :: get_num_weights(){
	return num_weights;
}

float** som :: get_weights(){
	return weights;
}
int som :: learn(float *in, char ch){
	for(int j = 0; j < num_inputs; j++){
		inputs[j] = ((in[j] > 0) ? 1 : -1);
	}
	float max = -10000;
	int index;
	for(int i = 0; i < num_outputs; i++){
		outputs[i] = 0;
		for(int j = 0; j < num_inputs; j++){
			outputs[i] += weights[i][j] * inputs[j]  / num_inputs; 
		}
		outputs[i] /= num_inputs;
		if(outputs[i] > max){
			index = i;
			max = outputs[i];
		}
		if(outputs[i] < 0){
			outputs[i] = 0;
		}else if(outputs[i] > 1){
			outputs[i] = 1;
		}
	}
	while(map[index] != '_') index = (index + 1) % num_outputs; 	
	cout << index << endl;
	map[index] = ch;
	return index;
}
char som :: find(float *in){
	for(int j = 0; j < num_inputs; j++){
		inputs[j] = ((in[j] > 0) ? 1 : -1);
	}
	float max = -10000;
	int index;
	for(int i = 0; i < num_outputs; i++){
		outputs[i] = 0;
		for(int j = 0; j < num_inputs; j++){
			outputs[i] += weights[i][j] * inputs[j] / num_inputs; 
		}
		//outputs[i] /= num_inputs;
		if(outputs[i] > max){
			index = i;
			max = outputs[i];
		}
		if(outputs[i] < 0){
			outputs[i] = 0;
		}else if(outputs[i] > 1){
			outputs[i] = 1;
		}
	}
	//while(map[index] != '_') index = (index + 1) % num_outputs; 	
	return map[index];
}
float som :: train(int index){
	float be = 0;
	for(int i = 0; i < num_inputs; i++){
		float e = inputs[i] - weights[index][i];
		if(e > be) be = e;
		weights[index][i] += leaning_rate * e;
	}
	return be;
}
void som :: record(){
	FILE *fp = fopen("weights.data", "w");
	for(int i = 0; i < num_outputs; i++){
		for(int j = 0; j < num_inputs; j++){	
			fprintf(fp, "%f \n", weights[i][j]);
		}
	}
	for(int i = 0; i < num_outputs; i++){
		fprintf(fp, "%c \n", map[i]);
	}
	fclose(fp);
}
bool som :: load(){
	FILE *fp = fopen("weights.data", "r");
	if(fp == NULL) return false;
	for(int i = 0; i < num_outputs; i++){
		for(int j = 0; j < num_inputs; j++){	
			fscanf(fp, "%f \n", &weights[i][j]);
		}
	}
	for(int i = 0; i < num_outputs; i++){
		fscanf(fp, "%c \n", &map[i]);
	}
	fclose(fp);
	return true;
}
float som::convert(float input){
	return ( 1.0 / ( 1.0 + (float)exp(-input)));
}
