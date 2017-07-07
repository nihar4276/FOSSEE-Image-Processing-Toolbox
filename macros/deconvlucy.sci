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

function [out]=deconvlucy(image1,image2,varargin)
// This function is used to Deblur image using Lucy-Richardson method 
//
// Calling Sequence
// J = deconvlucy(I1, I2);
// J = deconvlucy(I1, I2, NUMIT)
//
// Parameters
// I1: image matrix of the source image .
// I2: image matrix of the source image from last iteraion.
// NUMIT: The number if iterations specified to achieve the desired result.
// B : output image in the deconvoluted form. 
//
// Description
// J = deconvlucy(I, PSF, NUMIT) specifies the number of iterations the deconvlucy function performs. If this value is not specified, the default is 10.
//
// Examples
// i = imread("lena.jpeg",0);
// i1 = imread("lena.jpeg",0);
// rs = deconvlucy(i,i1);
// 



  	input_image1=mattolist(image1);
	input_image2=mattolist(image2);
	[lhs,rhs]=argn(0);
	if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>3 
        error(msprintf(" Too many input arguments,maximum number of arguments is 3\n"));
    	elseif rhs<2
        error(msprintf("the function needs atleast 2 arguments"));
    	end 
        if rhs==2
	a=raw_deconvlucy(input_image1,input_image2);	
	elseif rhs==3
	a=raw_deconvlucy(input_image1,input_image2,varargin(1));
	end

	dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end


endfunction
