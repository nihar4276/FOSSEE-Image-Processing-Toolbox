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
function [DA,DB]= matMulDeriv(A,B)
// this function Computes partial derivatives of the matrix product for each multiplied matrix 
//
// Calling Sequence
// [da db]=matMulDeriv(A,B);
//
//  Parameters
//  A First multiplied matrix.
//  B Second multiplied matrix.
// da First output derivative matrix d(A*B)/dA of size (A.rows * B.cols)x(A.rows * A.cols) and same type as A.
// db Second output derivative matrix d(A*B)/dB of size (A.rows * B.cols)x(B.rows * B.cols) and same type as A.
//
// Description
// this function Computes partial derivatives of the matrix product for each multiplied matrix 
// Examples
//
// Declare mattrices
//a=[1 2 ;3 4];
//b=[1 2 ;3 4];
// //call function
//[da db]=matMulDeriv(a,b);
// //view output
//da
//db
    [lhs rhs]=argn(0);
    
    if lhs>2
         error(msprintf(" Too many output arguments,maximum number of output arguments is 2"));
    elseif rhs>2
        error(msprintf(" Too many input arguments,maximum number of arguments is 2`"));
    elseif rhs<2
        error(msprintf("the function needs atleast 2 arguments"));
    end
    
    [DA,DB]=raw_matMulDeriv(A,B);
    
    
endfunction
