#
# Author :Tharindra Galahena
# Project:simple ocr using neural networks
# Date   :11/09/2012
# License:
# 
#     Copyright 2012 Tharindra Galahena
#
# This program is free software: you can redistribute it and/or modify it under the terms of 
# the GNU General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or (at your option) any later version. This program is distributed
# in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along with This program. 
# If not, see http://www.gnu.org/licenses/.
#
#

FLAGS = -lGL -lglut -lGLU -lglui 

all:
	g++ -c som.cpp
	g++ -o ocr ocr.cpp som.o $(FLAGS)

	rm som.o
