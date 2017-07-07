// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: V Srininivas
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function [out]=demosaic(src,code,dstCn)
// This function  converts the Bayer pattern encoded image  to the truecolor image, RGB.
//
// Calling Sequence
// image=imread("lena.jpeg",0)
// dem=demosaic(image,"gbrg");
// dem=demosaic(image,"bggr");
// dem=demosaic(image,"rggb");
// dem=demosaic(image,"grbg");
//
// Parameters
//
// dem: the output image
// image: the image which should be converted.
// 
// Description
//
// This function  converts the Bayer pattern encoded image  to the truecolor image, RGB.
//
// Examples
//
// z=imread("lena.jpeg");
// dem=demosaic(z,"rggb");
// imshow(dem); 


         input_image1=mattolist(src);
         a=raw_demosaic( input_image1,code);
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
endfunction;
