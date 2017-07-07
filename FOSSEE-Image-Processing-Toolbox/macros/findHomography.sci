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
function [homography_matrix]= findHomography(points1,points2,varargin)
// This Function Finds a perspective transformation between two planes.
//
// Calling Sequence
// homographyMatrix=findHomography(points1,points2);
// homographyMatrix=findHomography(points1,points2,method);
// homographyMatrix=findHomography(points1,points2,method,threshold);
//
// Parameters
// homographyMatrix: perspective transformation H between the source and the destination planes
// points1: Coordinates of the points in the original plane
// points2: Coordinates of the points in the target plane
// method: Method used to computed a homography matrix. 
// Here are the different options for method
// 0 - a regular method using all the points
// 4 - RANSAC-based robust method
// 8 - Least-Median robust method
// 16 - PROSAC-based robust method
// threshold: Maximum allowed reprojection error to treat a point pair as an inlier.
// Note: the number of points should be same in the points1 and points2
// Description
// The function finds and returns the perspective transformation H between the source and the destination planes
//
//Examples
//
// read first image
// z=imread("lena.jpeg",0);
// get points from first image
// yo=detectGFTTFeatures(z);
// read second image
// image=imread("lena2.jpg",0);
// yo1=detectGFTTFeatures(image);
// // call function with same number of points in both(first arg has 594 so passig 594 points from second arg)
// lou=findHomography(yo.KeyPoints,yo1.KeyPoints(1:594,:));




	
    [lhs rhs]=argn(0);
    if lhs>1
         error(msprintf(" Too many output arguments"));
    elseif rhs>4
        error(msprintf(" Too many input arguments,maximum number of arguments is 4"));
    elseif rhs<2
        error(msprintf("the function needs atleast 2 arguments"));
    end
    
    if rhs==2  then
        homography_matrix=raw_findHomography(points1,points2);
    elseif rhs==3
        homography_matrix=raw_findHomography(points1,points2,varargin(1));
     elseif rhs==4
        homography_matrix=raw_findHomography(points1,points2,varargin(1),varargin(2));   
    end
    
    
    
endfunction
