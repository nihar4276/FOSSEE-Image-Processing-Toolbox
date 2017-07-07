// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author:  Nihar Rao
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function [out]=imresize(image,alpha,beta)
// This function is used to resize the image
//
// Calling Sequence
//
// newImage=imresize(inputImage,alpha,beta);
//
// Parameters
//
// newImage: the new resized image
// inputImage: the image which should be resized.
// alpha: new number of rows.
// beta: new number of columns.
//
// Description
//
// This function is used to resize the image
//
// Examples
//
// z=imread("lena.jpeg",0);
// zz=imresize(z,35,12);
// imshow(zz)
   	image1=mattolist(image);
         a=raw_imresize(image1,alpha,beta);
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
endfunction;
