// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Abhilasha Sancheti & Nihar Rao
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in
function [out]=circle(input_image , x_coordinate_of_centre , y_coordinate_centre , radius, r_value,g_value,b_value,varargin)
// This function circle draws a simple or filled circle on an image with a given center and radius.
//
// Calling Sequence
// cir=circle(inputImage,xcor,ycor,radius,r,g,b);
// cir=circle(inputImage,xcor,ycor,radius,r,g,b,thickness);
// cir=circle(inputImage,xcor,ycor,radius,r,g,b,thickness,linetype);
// cir=circle(inputImage,xcor,ycor,radius,r,g,b,thickness,linetype,shift);
//
// Parameters
// cir: The output image with the circle drawn in it.
// inputImage: The input image on which the circle should be drawn.
// xcor: X-coordinate of the center
// ycor: Y-coordinate of the center
// r: red color value of the circle.It should be in the range 0-255.
// b: blue color value of the circle.It should be in the range 0-255.
// g: green color value of the circle.It should be in the range 0-255.
// thickness: Line thickness.
// linetype: Type of the circle boundary.It can be 0 or 4 or 8.
// shift: Number of fractional bits in the point coordinates.
//
// Description
// This function circle draws a simple or filled circle on an image with a given center and radius.
//
//
// Examples
//
// //read the input image 
// z=imread("lena.jpeg");
// //call the function
// cir=circle(z,100,100,15,255,0,0,1,8,0);
// finally show the circle drawn
// imshow(cir)

           
	input_image1=mattolist(input_image);
	[lhs,rhs]=argn(0);
	if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>10 
        error(msprintf(" Too many input arguments,maximum number of arguments is 10\n"));
    	elseif rhs<7
        error(msprintf("the function needs atleast 11 arguments"));
    	end 
	if rhs==7
         a=raw_circle(input_image1 , x_coordinate_of_centre , y_coordinate_centre , radius, r_value,g_value,b_value);
	elseif rhs==8
	 a=raw_circle(input_image1 , x_coordinate_of_centre , y_coordinate_centre , radius, r_value,g_value,b_value,varargin(1));
	elseif rhs==9
	 a=raw_circle(input_image1 , x_coordinate_of_centre , y_coordinate_centre , radius, r_value,g_value,b_value,varargin(1),varargin(2));
	elseif rhs==10
	a=raw_circle(input_image1 , x_coordinate_of_centre , y_coordinate_centre , radius, r_value,g_value,b_value,varargin(1),varargin(2),varargin(3));
	end
         dimension=size(a);
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
     
endfunction;
