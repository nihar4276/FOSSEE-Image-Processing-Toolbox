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
function [rectMat]=boundingRect(points)
//this function Calculates the up-right bounding rectangle of a point set.
//
// Calling Sequence
//
// z=imread("lena.jpeg",0);
// rect=boundingRect(points);
//
// Parameters
//
// rect: the rectangle coordinates
// points: the set of 2D points. It must be N*2.
//
// Description
//
// Calculates the up-right bounding rectangle of a point set.
//
// Examples
//
// z=imread("lena.jpeg",0);
// kaze=detectKAZEFeatures(z)x
// rect=boundingRect(kaze.KeyPoints);
    rectMat=raw_boundingRect(points);
endfunction
