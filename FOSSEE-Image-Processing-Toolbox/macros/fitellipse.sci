// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author:  Nihar Rao &  Priyanka Gandhi  
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in
function [out]=fitellipse(InputArraypoints)
// The function calculates the ellipse that fits (in a least-squares sense) a set of 2D points best of all.
//
// Calling Sequence
//
// felli=fitellipse(points);
//
// Parameters
// felli: a struct containing all the details about the ellipse Params.
// points: Input 2D point set
//
// Description
//
// The function calculates the ellipse that fits (in a least-squares sense) a set of 2D points best of all.
//
// Examples
//
// // read image
// z=imread("lena.jpeg",0);
// //get points using KAZE detector or the points can also be hardcoded.
// pio=detectKAZEFeatures(z);
// // call function
// sss=fitellipse(pio.KeyPoints)

           [t1 t2 t3 t4 t5]= raw_fitellipse(InputArraypoints);
           out=struct("size1",t1,"size2",t2,"center1",t3,"center2",t4,"angle",t3);
endfunction;
