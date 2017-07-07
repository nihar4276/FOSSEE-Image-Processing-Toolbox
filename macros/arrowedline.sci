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

function[dstImg] = arrowedline(srcImg, x1, y1, x2, y2, R, G, B, varargin)
// This Function Draws a arrow segment pointing from the first point to the second one.
//
// Calling Sequence
//
// z=imread("lena.jpeg");
// arrow=arrowedline(z,x1,y1,x2,y2,R,G,B);
// arrow=arrowedline(z,x1,y1,x2,y2,R,G,B,thickness);
// arrow=arrowedline(z,x1,y1,x2,y2,R,G,B,thickness,linetype);
// arrow=arrowedline(z,x1,y1,x2,y2,R,G,B,thickness,linetype,shift);
//
// Parameters
//
// z: input image on which the arrowd line should be drawn.
// arrow: the output image with the arrowed line drawn on it.
// x1: x coordinate of first point
// y1: y coordinate of first point
// x2: x coordinate of second point
// R: red color value of the circle.It should be in the range 0-255.
// G: blue color value of the circle.It should be in the range 0-255.
// B: green color value of the circle.It should be in the range 0-255.
// thickness: Line thickness.
// linetype: Type of the circle boundary.It can be 0 or 4 or 8.
// shift: Number of fractional bits in the point coordinates.
//
// Description
// This Function Draws a arrow segment pointing from the first point to the second one.
//
// Examples
//
// z=imread("lena.jpeg");
// arrow=arrowedline(z,200,200,150,10,255,255,0,13);
// imshow(arrow)




	[lhs, rhs] = argn(0)
	
	srcMat = mattolist(srcImg)

	select rhs
		case 8 then
			out = raw_arrowedline(srcMat, x1, y1, x2, y2, R, G, B)
		case 9 then
			out = raw_arrowedline(srcMat, x1, y1, x2, y2, R, G, B,varargin(1))
		case 10 then
			out = raw_arrowedline(srcMat, x1, y1, x2, y2, R, G, B, varargin(1),varargin(2))
		case 11 then
			out = raw_arrowedline(srcMat, x1, y1, x2, y2, R, G, B, varargin(1),varargin(2), varargin(3))
		case 12 then
			out = raw_arrowedline(srcMat, x1, y1, x2, y2, R, G, B, varargin(1),varargin(2), varargin(3), varargin(4))
	end
	
	channels = size(out)
	
	for i = 1:channels
		dstImg(:,:,i) = out(i)
	end
endfunction
