// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Deepshika & Nihar Rao
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

function [idealPoints] = undistortPoints(observedPoints, camMat, disCoefMat, rectMat, newCamMat)
// Returns the ideal point coordinates from the observed point coordinates
//
// Calling Sequence
//   [idealPoints] = undistortPoints(observedPoints, camMat, disCoefMat, rectMat, newCamMat)
//
// Parameters
// observedPoints: 1xN or Nx1 2-channel (CV_32FC2 or CV_64FC2).
// camMat: \vecthreethree{f_x}{0}{c_x}{0}{f_y}{c_y}{0}{0}{1}
// disCoefMat: Input vector of distortion coefficients  (k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6]]) of 4, 5, or 8 elements. If the vector is NULL/empty, the zero  distortion coefficients are assumed.
// rectMat: Rectification transformation in the object space (3x3 matrix). If the matrix is empty, the identity transformation is used.
//newCamMat: New camera matrix (3x3) or new projection matrix (3x4. If the matrix is empty, the identity new camera matrix is used.
// idealPoints: ideal point coordinates matrix. If matrix newCamMat is identity or omitted, idealPoints will contain normalized point coordinates.
//
// Description
// Returns the ideal points coordinates from the observed point coordinates after undistortion and reverse perpective transformation. 
//
// Examples
// [observedPoints] = [1 2 3 4; 4 3 2 1]
// [camMat] = [450 0 231; 0 876.3 87.1; 0 0 1]
// [disCoefMat] = [3 2 0 9]
// [rectMat] = [1 0 0; 0 1 0; 0 0 1]
// [newCamMat] = []
// [idealPoints] = undistortPoints(observedPoints, camMat, disCoefMat, rectMat, newCamMat)



	output = raw_undistortPoints(observedPoints, camMat, disCoefMat, rectMat, newCamMat)
    
         idealPoints=output;
	
		
    
endfunction
