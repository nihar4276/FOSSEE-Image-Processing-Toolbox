// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Umang Agarwal & Sridhar Reddy
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in
function [regions]=detectMSERFeatures(image,varargin)
// This function is used to detect MSER features
//
// Calling Sequence
//   list_pixels = detectMSERFeatures(image, Name, Value... )
//   [list_pixels Count Location Axes Orientation] = detectMSERFeatures(image, Name, Value... )
//
// Parameters
//  Image: Input Image, should be a 2-D grayscale. The Input Image should be real
//  ThresholdDelta [Optional Input Argument]: Step Size between intensity to be checked for measurement of stability. Values: Percentage numeric value. Default: 2.0
//  RegionAreaRange [Optional Input Argument]: Size of the region in Pixels specified as [minArea maxArea]. Default Value: [30 14000]
//  ROI [Optional Input Argument]: Specify a rectangular region of operation. Format [ x y width height ]. Default: [1 1 size(Image,2) size(Image,1)]
//  MaxAreaVariation [Optional Input Argument]: Maximum Area Variation between external regions at varying thresholds for determination of stability. Values in range of (0,1]. Default 0.25
//  list_pixels: Array of point coordinates for detected regions
//  Location: A M-by-2 Matrix of [x y] coordinates of centroid of the ellipsoidal fit to the region
//  Count: Count of the number of stable regions detected
//  Axes: A M-by-2 Matrix of [majorAxis minorAxis] values for each ellipsoidal fit to the detected regions
//  Orientation: A M-by-1 Vector containing the angle of orientation of the ellipsoidal fit in the range of [-pi/2 +pi/2] radians
//
// Description
//  This function is used to detect the MSER regions, and also the corresponding ellipsoidal fit to the detected regions.
//
// Examples
//   image = imread('sample.jpg');
//   [regions] = detectMSERFeatures(image);
//
// With Optional Arguments:
//   [regions location axes] = detectMSERFeatures(image, "ThresholdDelta", 10.0)
//


    [lhs rhs]=argn(0);
    if rhs>9
        error(msprintf(" Too many input arguments"));
    elseif modulo(rhs-1,2)<>0
       error(msprintf("Either Argument Name or its Value missing"));
    end
    imageList=mattolist(image);
    select rhs-1
        case 0 then
            [pixelIdxList count location axes orientation]=raw_detectMSERFeatures(imageList);
        case 2 then
            [pixelIdxList count location axes orientation]=raw_detectMSERFeatures(imageList,varargin(1),varargin(2));
        case 4 then
            [pixelIdxList count location axes orientation]=raw_detectMSERFeatures(imageList,varargin(1),varargin(2),varargin(3),varargin(4));
        case 6 then
            [pixelIdxList count location axes orientation]=raw_detectMSERFeatures(imageList,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6));
        case 8 then
            [pixelIdxList count location axes orientation]=raw_detectMSERFeatures(imageList,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6),varargin(7),varargin(8));
    end
    //for i=1:size(pixelIdxList)
      //  regions(i)=struct('Count',1,'Location',location(i,:),'Axes',axes(i,:),'Orientation',orientation(i,:),'PixelIdxList',pixelIdxList(i));
    //end
    regions=struct('Type','MSERObject','Count',count,'Location',location,'Axes',axes,'Orientation',orientation,'PixelIdxList',pixelIdxList),
endfunction
