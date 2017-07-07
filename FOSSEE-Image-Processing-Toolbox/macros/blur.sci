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

function [out]=blur(input_image ,ksize_width,ksize_height,anchorX,anchorY)
// This function is used to blur an image using the normalized box filter. 
//
// Calling Sequence
// B = blur(input_image ,ksize_width,ksize_height,anchorX,anchorY);
//
// Parameters
// A: image matrix of the source image.
// ksize_width : Defines the width of the kernel to be used in pixels.
// ksize_width : Defines the height of the kernel to be used in pixels.
// anchorX :  Indicates where the x coordinate of the anchor point (the pixel evaluated) is located with respect to the neighborhood. If there is a negative value, then the center of the kernel is considered the anchor point.
// anchorY :  Indicates where the y coordinate of the anchor point (the pixel evaluated) is located with respect to the neighborhood. If there is a negative value, then the center of the kernel is considered the anchor point.
// B : output image with the applied blur fucntion. 
//
// Description
// The function smoothes an image using the kernel specified with its dimesnsions.
//
// Examples
// i = imread('right1.jpg',0);
// i2 =blur(i,5,5,1,1)
// imshow(i2);
//

         input_image1=mattolist(input_image);
         a=raw_blur(input_image1, ksize_width,ksize_height,anchorX,anchorY);
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
     
endfunction;
