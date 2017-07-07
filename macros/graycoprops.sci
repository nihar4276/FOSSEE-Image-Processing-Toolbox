// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Nihar Rao 
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in
function[stats] = graycoprops(srcImg, varargin)
// This function computes the Properties of gray-level co-occurrence matrix.
//
// Calling Sequence
// z=imread("lena.jpeg"); //in grayscale or color  
// //Note: z can be a image or simply a Matrix.
// gray=graycoprops(z)   //get all 4 properties
// gray=graycoprops(z,"contrast") //compute only contrast
// gray=graycoprops(z,["contrast" "energy"]) //compute contrast and energy.the properties can be passed in any order
// gray=graycoprops(z,["contrast"  "correlation" "energy"])
// gray=graycoprops(z,["contrast"  "correlation" "energy" "homogeneity"])
//
// Parameters
//
// gray: A struct containing all the parameters
// z: A image or a matrix
// contrast: a measure of the intensity contrast between a pixel and its neighbor over the whole image.
// energy: the sum of squared elements
// homogeneity: a value that measures the closeness of the distribution of elements.
// correlation:a measure of how correlated a pixel is to its neighbor over the whole image
//
// Description
// This function computes the Properties of gray-level co-occurrence matrix.The properties being "correlation","contrast","energy" and "homogeneity".
//
//
// Examples
// //compute for a image
// z=imread("lena.jpeg",0);
// sss=graycoprops(z,["contrast"])
//
// //compute for a matrix
// glcm = [0 1 2 3;1 1 2 3;1 0 2 0;0 0 0 3]
// sss=graycoprops(glcm,["contrast" "energy" "correlation"])


	[lhs, rhs] = argn(0)
	
	srcMat = mattolist(srcImg)

	select rhs
		case 1 then
			[contrast correlation energy homo] = raw_graycoprops(srcMat);
			stats=struct('Contrast',contrast,'Correlation',correlation,'Energy',energy,'Homogeniety',homo);
		case 2 then
			[rows cols]=size(varargin(1));
			n=rows*cols;
			if n>4
			   error(msprintf("the string matrix must have maximimum of 4 entries"));
			end
			inputString=varargin(1);
			if n==1			
			[out]=raw_graycoprops(srcMat,varargin(1));
			stats=struct(inputString(1),out);
			elseif n==2
			[out out1]=raw_graycoprops(srcMat,varargin(1));
			stats=struct(inputString(1),out,inputString(2),out1);
			
			elseif n==3
			[out out1 out2]=raw_graycoprops(srcMat,varargin(1));
			stats=struct(inputString(1),out,inputString(2),out1,inputString(3),out2);
			
			elseif n==4
			[out out1 out2 out3]=raw_graycoprops(srcMat,varargin(1));
			stats=struct(inputString(1),out,inputString(2),out1,inputString(3),out2,inputString(4),out3);
							
			end
			
	
		end
	
	
	
endfunction
