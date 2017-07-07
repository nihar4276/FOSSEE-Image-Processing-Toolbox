function [imageIndex]=indexImages(imgSet,varargin)
// This function creates image search index
//
// Calling Sequence
//  imageIndex = indexImages(imgSet, bagOfFeatures, Name, Value... );
//
// Parameters
//  imgSet: Collection of images with their location and labels
//  bagOfFeatures: Bag of Visual Words
//  Verbose [Optional Input Argument]: Enable Progress display to Screen
//  SaveFeatureLocations [Optional Input Argument]: A boolean value indicating whether feature locations has to be saved or not. Values: [True(default)|False]
//  imageIndex: Search Index Object containing the mapping of visual vocabulary to each image in the image set
//
// Description
//  Creates a search Index Object that has been mapped to visual words that can be used for retrieve Images
//
// Examples
//    imgSet = imageSet(directory,'recursive');
//    [trainingSet testSet] = partition(imgSet,[0.8]);
//    bag = bagOfFeatures(trainingSet);
//    imageindex = indexImages(trainingSet, bag);
//
// With Optional Arguments:
//    imageindex = indexImages(trainingSet, bag, "Verbose", 1);
//
// Authors
//  Umang Agrawal
//  Rohit Suri
//  Sridhar Reddy

    [lhs rhs]=argn(0);
    if rhs>6
        error(msprintf(" Too many input arguments"));
    end
    imageSetList=imageSetStructToList(imageSet);
    if modulo(lhs,2)==0
   		bagList=bagStructToList(varargin(1));
    select rhs
        case 1 then
            [imageIndexList]=opencv_indexImages(imgSetList);
        case 2 then
            [imageIndexList]=opencv_indexImages(imgSetList,bagList);
        case 3 then
            [imageIndexList]=opencv_indexImages(imgSetList,varargin(1),varargin(2));
        case 4 then
            [imageIndexList]=opencv_indexImages(imgSetList,bagList,varargin(2),varargin(3));
        case 5 then
            [imageIndexList]=opencv_indexImages(imgSetList,varargin(1),varargin(2),varargin(3),varargin(4));
        case 6 then
            [imageIndexList]=opencv_indexImages(imgSetList,bagList,varargin(2),varargin(3),varargin(4),varargin(5));
    end

endfunction
