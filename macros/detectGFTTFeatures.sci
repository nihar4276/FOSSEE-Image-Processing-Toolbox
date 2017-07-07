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
function [varargout] = detectGFTTFeatures(image, varargin)	
// This function is used to detect GFTT Features in a grayscale Image.
//
// Calling Sequence
//  result = detectGFTTFeatures(Image);
//  result = detectGFTTFeatures(Image,Name,Value,....)
//
// Parameters
// result: a struct containing features and keypoints
// Image: a grayscale image whose GFTT features is to be found
// blocksize: the blocksize to be used for detecting the keypoints
// minDistance: the minimum distance between the points for feature computation
// useHarrisDetector: an option to use the HarrisDetector.default value is false.
// maxCorners: the maximum number of corners that should be used for feature computation.
// ROI or Mask : (Optional) Region Of Interest. This is taken as a vector [u v width height]. When specified, the function detects the key points within region of area width*height with u and v being the top left corner coordinates.
// Description
// This function is used to detect GFTT Features in a grayscale Image.
// Examples
//
// //read image in grayscale
// z=imread("people.jpg",0);
// image=imread("pls.jpg",0);
// stacksize('max')
// //call the function to detect features for image- z
// pls=detectGFTTFeatures(z,"minDistance",4);
// // call the function to detect features for image- image 
// pls1=detectGFTTFeatures(image);
// //match features using the features detected using the above function 
// [op ir]=matchFeatures(pls.Features,pls1.Features);
// //finally draw those matches
// final=drawMatch(z,image,pls.KeyPoints,pls1.KeyPoints,op,ir);
// imshow(final)



	image_list = mattolist(image);
	[ lhs, rhs ] = argn(0)
	if rhs > 15 then
		error(msprintf("Too many input arguments"))
	end	
	if lhs > 1 then
		error(msprintf("Too many output arguments"))
	end		

	select rhs 
		case 1 then
			[a b c d e]= raw_detectGFTTFeatures(image_list)		
		case 3 then
			[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2))
		case 5 then
			[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4))		
		case 7 then
				[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4), varargin(5), varargin(6))			
		case 9 then
			[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4), varargin(5), varargin(6), varargin(7), varargin(8))
		case 11 then
		[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4), varargin(5), varargin(6), varargin(7), varargin(8),varargin(9),varargin(10))
                case 13 then
		[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4), varargin(5), varargin(6), varargin(7), varargin(8),varargin(9),varargin(10),varargin(11),varargin(12));
		case 15 then
		[a b c d e]= raw_detectGFTTFeatures(image_list, varargin(1), varargin(2), varargin(3), varargin(4), varargin(5), varargin(6), varargin(7), varargin(8),varargin(9),varargin(10),varargin(11),varargin(12),varargin(13),varargin(14));

        end
varargout(1) = struct("Type","binaryFeatures",'Features',a,'NumBits',b,'NumFeatures',c,'KeyPoints',d,'keypointsCount',e);	
endfunction
