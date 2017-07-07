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

function [params]=stereoCalibrate(objectpoints,imagepoints1,imagepoints2,varargin)
// this function Performs stereo calibration for the fisheye model.
//
// Calling Sequence
//
// stereo=stereoCalibrate(objectpoints,imagepoints1,imagepoints2);
// stereo=stereoCalibrate(objectpoints,imagepoints1,imagepoints2,cameraMatrix1,distCoeffs1,cameraMatrix2,distCoeffs2);
//
// Parameters
// stereo: a Struct containing all the camera Params
// objectpoints: a  2d set of actual object points.
// imagepoints1: a list of imagepoints of image1.
// imagepoints2: a list of imagepoints of image2.
// cameraMatrix1: camera matrix of first camera.
// distCoeffs1: distortion coefficients of first camera.it should be 4*1 or 1*4.
// cameraMatrix2: camera matrix of second camera.
// distCoeffs2: distortion coefficients of second camera.it should be 4*1 or 1*4.
//
// Description
//
// this function Performs stereo calibration for the fisheye model.
//
// Examples
// // A example to show calibration, using the traditional chessboard/checkerboard example.
//
// //generate checkerboardpoints for calibration
// yo=genCheckerboardPoints([7 10],8);
// //read first image
// z=imread("left1.jpg",0);
// //read second image
// image=imread("right1.jpg",0);
// //detect checkerboardpoints for image 1
// ii=detectCheckerboardCorner(z,[7 10]);
// //detect checkerboardpoints for image 2
// ii2=detectCheckerboardCorner(image,[7 10]);
// //convert imagepoints to list
// ii=list(ii);
// ii2=list(ii2);
// // call function
// final=stereoCalibrate(yo,ii,ii2);
// // show the struct 
// final
// // use the above calibration further
// uu = undistortImage(image,final.cameraMatrix2);
// imshow(uu);
//
// 
// //generate checkerboardpoints for calibration
// yo=genCheckerboardPoints([7 10],8);
// //read first image
// z=imread("left1.jpg",0);
// //read second image
// image=imread("right1.jpg",0);
// //detect checkerboardpoints for image 1
// ii=detectCheckerboardCorner(z,[7 10]);
// //detect checkerboardpoints for image 2
// ii2=detectCheckerboardCorner(image,[7 10]);
// //convert imagepoints to list
// ii=list(ii);
// ii2=list(ii2);
// // call function
// final=stereoCalibrate(yo,ii,ii2);
// // show the struct 
// final
// // use the above calibration further
// uu = undistortImage(image,final.cameraMatrix2,'distCoeffs',final.distortionCoefficients2);
// imshow(uu);

 

     [lhs rhs]=argn(0);
  
     	if lhs>1
         error(msprintf(" Too many [a b c d e f]put arguments\n"));
    	elseif rhs>7
        error(msprintf(" Too many input arguments,maximum number of arguments is 7\n"));
    	elseif rhs<3
        error(msprintf("the function needs atleast 3 arguments\n"));
    	end 

	if rhs==3
        [a b c d e f] =raw_stereoCalibrate(objectpoints,imagepoints1,imagepoints2);
        elseif rhs==4
        [a b c d e f]=raw_stereoCalibrate(objectpoints,imagepoints1,imagepoints2,varargin(1));
        elseif rhs==5
        [a b c d e f]=raw_stereoCalibrate(objectpoints,imagepoints1,imagepoints2,varargin(1),varargin(2));
	elseif rhs==6
        [a b c d e f]=raw_stereoCalibrate(objectpoints,imagepoints1,imagepoints2,varargin(1),varargin(2),varargin(3));
        elseif rhs==7
        [a b c d e f]=raw_stereoCalibrate(objectpoints,imagepoints1,imagepoints2,varargin(1),varargin(2),varargin(3),varargin(4));
        end
       
       

        params=struct('cameraMarix1',a,'distortionCoefficients1',b,'cameraMatrix2',c,'distortionCoefficients2',d,'rotationMatrix',e,'TranslationVector',f);
endfunction
