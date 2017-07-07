// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Tess Zacharias
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function [output] = lab2double(pstData)
// This function used to convert a matrix of L*a*b to double.
//
// Calling Sequence
//
// doub=lab2double(matrix);
//
// Parameters
//
// doub: The output matrix with double values.
// matrix: the input matrix with Lab values.
//
// Description
//
// This function used to convert a matrix of L*a*b to double.
//
// Examples
// a=[1 0 1];
// doub=lab2double(a);
//
// z=imread("lena.jpeg");
// cvt=cvtColor(z,"CV_RGB2Lab");
// doub=lab2double(cvt);

	pstData=mattolist(pstData);
	a = raw_lab2double(pstData);
	d = size(a);
	for i=1:d
		output(:,:,i) = a(i);
	end
endfunction
