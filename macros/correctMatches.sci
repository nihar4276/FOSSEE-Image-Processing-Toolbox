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

function [newPoints1, newPoints2] = correctMatches(F, points1, points2)
// This function Refines coordinates of corresponding points 
//
// Calling Sequence
// [newPoints1, newPoints2] = correctMatches(F, points1, points2)
//   
// Parameters
// F – 3x3 fundamental matrix.
// points1 – 2xN array containing the first set of points.
// points2 – 2xN array containing the second set of points.
// newPoints1 – The optimized points1.
// newPoints2 – The optimized points2.
//
// Description
// The function implements the Optimal Triangulation Method (see Multiple View Geometry for details). For each given point correspondence points1[i] <-> points2[i], and a fundamental matrix F, it computes the corrected correspondences newPoints1[i] <-> newPoints2[i] that minimize the geometric error  d(points1[i], newPoints1[i])^2 + d(points2[i],newPoints2[i])^2 (where  d(a,b) is the geometric distance between points  a and  b ) subject to the epipolar constraint  newPoints2^T * F * newPoints1 = 0 .
//
// Examples
// //read first image
// I=imread("oscarSelfie.jpg",0);
// //increase stack size of scilab
// stacksize('max')
// // get points from first image
// cornerPoints1=detectMSERFeatures(I);
// //read second image
// I2=imread("oscarSelfie.jpg",0);
// //get points for 2nd image
// cornerPoints2=detectMSERFeatures(I2);
// fundamentalMat=estimateFundamentalMat(cornerPoints1.Location,cornerPoints2.Location);
// [new1 new2]=correctMatches(fundamentalMat,cornerPoints2.Location,cornerPoints1.Location);
   [lhs rhs]=argn(0);
    
    if lhs>2
         error(msprintf(" Too many output arguments,maximum number of output arguments is 2"));
    elseif rhs>3
        error(msprintf(" Too many input arguments,maximum number of arguments is 3`"));
    elseif rhs<3
        error(msprintf("the function needs atleast 3 arguments"));     
    end
    
    [newPoints1, newPoints2]=raw_correctMatches(F, points1, points2);

    
    
endfunction
