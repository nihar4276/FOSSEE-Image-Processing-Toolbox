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

function [out]=erode(input_image ,kernel,anchorX,anchorY,iterations)
// This function Erodes an image by using a specific structuring element.
//
// Calling Sequence
//
// z=imread("lena.jpeg");
// ero=erode(inputImage,kernel,anchorX,anchorY,iterations);
//
// Parameters
//
// z: input image which should be eroded.
// ero: the output eroded image
// kernel: structuring element used for erosion
// anchorX: x coordinate of Anchor.
// anchorY: y coordinate of Anchor.
// Anchor: position of the anchor within the element.
// Iterations: number of times erosion is applied.
//
// Description
//
// This function Erodes an image by using a specific structuring element.
//
// Examples
//
// z=imread("lena.jpeg");
// ero=erode(z,[6 4],1,1,4);


input_image1=mattolist(input_image);
         a=raw_erode(input_image1 ,kernel,anchorX,anchorY,iterations);
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
     
endfunction;
