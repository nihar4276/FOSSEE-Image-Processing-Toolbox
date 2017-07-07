// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Shubheksha Jalan & Nihar Rao
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function new_image = cvtColor(image, code, varargin)
// This function is used to transform a image from one space to other like rgb to gray and vice versa.
//
// Calling Sequence
//
// inputImage=imread("lena.jpeg");
// outputImage=cvtColor(inputImage,codeString);
// outputImage=cvtColor(inputImage,codeString,dstCn);
// 
//
// Parameters
// dstCn: number of channels in the destination image; if the parameter is 0, the number of the channels is derived automatically from src and code
// codeString: A string which specifies the type of conversion.The different types are listed below.
//      "CV_BGR2GRAY": Conversion is from BGR(blue-green-red) space to GRAY.                    
//      "CV_RGB2GRAY": Conversion is from RGB(red-green-blue) space to GRAY. 
//      "CV_GRAY2BGR": Conversion is from BGR(blue-green-red) space.       
//      "CV_GRAY2RGB": Conversion is from to GRAY to RGB(blue-green-red) space.
//      "CV_BGR2XYZ" : Conversion is from BGR(blue-green-red) space to CIE XYZ.  
//      "CV_RGB2XYZ" : Conversion is from RGB(red-green-blue) space to CIE XYZ. 
//      "CV_XYZ2BGR" : Conversion is from to CIE XYZ to BGR space. 
//      "CV_XYZ2RGB" : Conversion is from to CIE XYZ to RGB(red-green-blue) space. 
//      "CV_BGR2YCrCb": Conversion is from BGR(blue-green-red) space to luma-chroma. 
//      "CV_RGB2YCrCb" :Conversion is from RGB(red-green-blue) space to luma chroma. 
//      "CV_YCrCb2BGR" :Conversion is from  luma-chroma to BGR(blue-green-red) space.
//      "CV_YCrCb2RGB" :Conversion is from  luma-chroma to RGB(red-green-blue) space.
//      "CV_BGR2HSV": Conversion is from BGR(blue-green-red) space to HSV. 
//      "CV_RGB2HSV": Conversion is from RGB space to HSV. 
//      "CV_HSV2BGR": Conversion is from to HSV to BGR(blue-green-red) space. 
//      "CV_HSV2RGB": Conversion is from to HSV to RGB(red-green-blue) space.
//      "CV_BGR2HLS": Conversion is from BGR(blue-green-red) space to HLS. 
//      "CV_RGB2HLS": Conversion is from RGB space to HSV. 
//      "CV_HLS2BGR": Conversion is from  HLS to BGR(blue-green-red) space. 
//      "CV_HLS2RGB": Conversion is from  HLS to RGB(red-green-blue) space.  
//      "CV_BGR2Lab": Conversion is from BGR(blue-green-red) space to CIE Lab. 
//      "CV_RGB2Lab": Conversion is from RGB space to CIE Lab.
//      "CV_Lab2BGR": Conversion is from  CIE Lab to BGR(blue-green-red) space. 
//      "CV_Lab2RGB": Conversion is from  CIE Lab to RGB space. 
//      "CV_BGR2Luv": Conversion is from BGR(blue-green-red) space to CIE Luv.  
//      "CV_RGB2Luv": Conversion is from RGB space to CIE Luv.
//      "CV_Luv2BGR": Conversion is from  CIE Luv to BGR(blue-green-red) space.              
//      "CV_Luv2RGB": Conversion is from  CIE Luv to RGB space.
//
// Description
//
// This function is used to transform a image from one space to other like rgb to gray and vice versa.
//
// Examples
//
// z=imread("lena.jpeg",0);
// ss=cvtColor(z,"CV_GRAY2BGR");
// imshow(ss)
 
              
	
	[ lhs, rhs ] = argn(0)
	
	image_list = mattolist(image)
	
	select rhs
		case 2 then
			
			out = raw_cvtColor(image_list, code)
		
		case 3 then
			out = raw_cvtColor(image_list, code, varargin(1))
	end
	
	sz=size(out);
	for i=1:sz
		new_image(:, :, i) = out(i)
	end

endfunction
