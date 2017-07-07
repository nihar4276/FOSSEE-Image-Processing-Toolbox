// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Sukul Bagai 
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in
function [out]=ellipse(input_image , x_coordinate_of_centre , y_coordinate_centre , first_axis, second_axis, angle, startAngle, endAngle, r_value,g_value,b_value,varargin)
// This function draws a simple or thick elliptic arc or fills an ellipse sector.
//
//
// Calling Sequence
// elli=ellipse(inputImage,xcor,ycor,firstAxis,secondAxis,angle,startAngle,endAngle,r,g,b);
// elli=ellipse(inputImage,xcor,ycor,firstAxis,secondAxis,angle,startAngle,endAngle,r,g,b,thickness);
// elli=ellipse(inputImage,xcor,ycor,firstAxis,secondAxis,angle,startAngle,endAngle,r,g,b,thickness,linetype);
// elli=ellipse(inputImage,xcor,ycor,firstAxis,secondAxis,angle,startAngle,endAngle,r,g,b,thickness,linetype,shift);
//
// Parameters
// elli: The output image with the ellipse drawn in it.
// inputImage: The input image on which the ellipse should be drawn.
// xcor: X-coordinate of the center
// ycor: Y-coordinate of the center
// firstAxis: the first axis of the ellipse.
// secondAxis: the second axis of the ellipse.
// angle: Ellipse rotation angle in degrees.
// startAngle: Starting angle of the elliptic arc in degrees.
// endAngle: 	Ending angle of the elliptic arc in degrees.
// r: red color value of the ellipse.It should be in the range 0-255.
// b: blue color value of the ellipse.It should be in the range 0-255.
// g: green color value of the ellipse.It should be in the range 0-255.
// thickness: Line thickness.
// linetype: Type of the ellipse boundary.It can be 0 or 4 or 8.
// shift: Number of fractional bits in the point coordinates.
//
// Description
//
// This function draws a simple or thick elliptic arc or fills an ellipse sector.
//
// Examples
// // read the input image on which the ellipse shpuld be drawn.
// z=imread("lena.jpeg",0);
// call the function
// elli=ellipse(z,0,0,45,45,45,0,45,255,0,0,1,0);
//  // show the image drawn on it.
// imshow(elli)


	input_image1=mattolist(input_image);
	[lhs,rhs]=argn(0);
	if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>14 
        error(msprintf(" Too many input arguments,maximum number of arguments is 14\n"));
    	elseif rhs<11
        error(msprintf("the function needs atleast 11 arguments"));
    	end 
         if rhs==11
         a=raw_ellipse(input_image1 , x_coordinate_of_centre , y_coordinate_centre , first_axis, second_axis, angle, startAngle, endAngle, r_value,g_value,b_value);
	elseif rhs==12
	 a=raw_ellipse(input_image1 , x_coordinate_of_centre , y_coordinate_centre , first_axis, second_axis, angle, startAngle, endAngle, r_value,g_value,b_value,varargin(1));
	elseif rhs==13
	 a=raw_ellipse(input_image1 , x_coordinate_of_centre , y_coordinate_centre , first_axis, second_axis, angle, startAngle, endAngle, r_value,g_value,b_value,varargin(1),varargin(2));
	elseif rhs==14
	 a=raw_ellipse(input_image1 , x_coordinate_of_centre , y_coordinate_centre , first_axis, second_axis, angle, startAngle, endAngle, r_value,g_value,b_value,varargin(1),varargin(2),varargin(3));
	end
	
	
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
     
endfunction;
