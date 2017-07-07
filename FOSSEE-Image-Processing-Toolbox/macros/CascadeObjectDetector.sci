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


function [out,bbox]=CascadeObjectDetector(input_image,classifierList,varargin)
// This function is used to detect objects in an image.
//
// Calling Sequence
//
// detect=CascadeObjectDetector(inputImage,classifierList);
// detect=CascadeObjectDetector(inputImage,classifierList,scale);
// detect=CascadeObjectDetector(inputImage,classifierList,scale,minNeighbors);
// detect=CascadeObjectDetector(inputImage,classifierList,scale,minNeighbors,flags);
// detect=CascadeObjectDetector(inputImage,classifierList,scale,minNeighbors,flags,minSize);
// detect=CascadeObjectDetector(inputImage,classifierList,scale,minNeighbors,flags,minSize,maxSize);
//
// Parameters
// out: the output image with all specified detections.
// inputImage: input image on which the objects should be detected.
// classifierList: a matrix of strings containing the location of the xml files which are to be used in the detection.
// scale: Parameter specifying how much the image size is reduced at each image scale.
// minNeighbors: Parameter specifying how many neighbors each candidate rectangle should have to retain it.
// flags: the method used in detection.it should be either 1 or 4 or 2 or 8.
// min size: Minimum possible object size. Objects smaller than that are ignored.
// max size: Maximum possible object size. Objects larger than that are ignored. 
//
// Description 
//
// This function is used to detect objects in an image.
//
// Examples
// // A example detecting all faces,eyes in an image.
// //read the input image.
// z=imread("oscarSelfie.jpg");
// //increase stacksize of scilab
// stacksize('max')
// declare string martrix with the xml locations.Here the general opencv's .xml files are used.
// s=["/home/nihar/Desktop/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml" "/home/nihar/Desktop/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"];
// //call function
// //Note:-the value of scale and other optional inputs must be adjusted to get proper/desired detection.
// p=CascadeObjectDetector(z,s,1.05);
// //show the detection
//imshow(p);
//
// Detect only faces.
//
// //read the input image.
// z=imread("oscarSelfie.jpg");
// //increase stacksize of scilab
// stacksize('max')
// declare string martrix with the xml locations.Here the general opencv's .xml files are used.
// s=["/home/nihar/Desktop/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"];
// //call function
// //Note:-the value of scale and other optional inputs must be adjusted to get proper/desired detection.
// p=CascadeObjectDetector(z,s,1.05);
// //show the detection
// imshow(p);



         input_image1=mattolist(input_image);
         [lhs rhs]=argn(0);
	  if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>7
        error(msprintf(" Too many input arguments"));
    	elseif rhs<2
       	error(msprintf("Too less arguments provided!,minimum is 2!"));
    	end
       select rhs
         case 2 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList);
	 case 3 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList,varargin(1));
	 case 4 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList,varargin(1),varargin(2));
	 case 5 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList,varargin(1),varargin(2),varargin(3));
	 case 6 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList,varargin(1),varargin(2),varargin(3),varargin(4));
	 case 7 then
         [a,bbox]=raw_CascadeObjectDetector(input_image1,classifierList,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5));
      end
         dimension=size(a)
         for i = 1:dimension
              out(:,:,i)=a(i);
         end
     
endfunction;
