// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Sukul Bagai & Nihar Rao
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function[dstMat] = imread(matA,varargin)
// This function is used to Read/Load an image from the disk
//
//  
//
// Calling Sequence
// image=imread("image_path");
// image=imread("image_path",options)
//
// Parameters
// image_path: a String which contains the path of the image that is to be read.
// options: an Integer, containing the option for user to specify. See below for details.	
// 0 :  convert image to the single channel grayscale image.
// 1 :  convert image to the 3 channel BGR color image.
// 2 :  load 16-bit/32-bit image when the input image has the corresponding depth, otherwise convert it to 8-bit.
// 4 :  the image is read in any possible color format.
// 8 :  use the gdal driver for loading the image.
// 16 :	convert image to the single channel grayscale image and the image size reduced 1/2.
// 17 : convert image to the 3 channel BGR color image and the image size reduced 1/2.
// 32 : convert image to the single channel grayscale image and the image size reduced 1/4.
// 33 : convert image to the 3 channel BGR color image and the image size reduced 1/4.
// 64 : convert image to the single channel grayscale image and the image size reduced 1/8.
// 65 : convert image to the 3 channel BGR color image and the image size reduced 1/8.
// 128 : do not rotate the image according to EXIF's orientation flag.
//
//  Description
//  This function is used to Read/Load an image from the disk	
//
// 
// Examples
// Read a image as it is(Unchanged).
// //Calling imread
// image=imread("test.jpg");
//
// Read image as grayscale
// //Calling imread
// image=imread("test.jpg",0);

       [lhs rhs]=argn(0);
	
        if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>2 
        error(msprintf(" Too many input arguments,maximum number of arguments is 2\n"));
    	elseif rhs<1
        error(msprintf("the function needs atleast 1 arguments"));
    	end       
	if rhs==1
        out = raw_imread(matA);
        else
        out=raw_imread(matA,varargin(1));
        end


	channel = size(out)
	
	for i = 1: channel
		dstMat(:,:,i) = (out(i))
	end
	
endfunction
