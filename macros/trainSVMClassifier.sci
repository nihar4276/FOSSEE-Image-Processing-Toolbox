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
function [classifier]=trainSVMClassifier(imgSet,bag,classifierName,varargin)
// This function is used to train an image classifier using the SVM(Support Vector Machines) Model.
//
// Calling Sequence
// imgSet = imageSet(directory,'recursive');
// 'or'
// imgSet = imageSet(image);
// bag = bagOfFeatures(imgSet);
// classifier = trainSVMClassifier(imgSets, bag);
// classifier = trainSVMClassifier(imgSets, bag,'nameclass')
// classifier = trainSVMClassifier(imgSets, bag,'nameclass')
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff,degree)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff,degree,gamma)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff,degree,gamma,kernelType,Nu)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff,degree,gamma,kernelType,Nu,P)
// classifier = trainSVMClassifier(imgSets, bag,'nameclass',C,coeff,degree,gamma,kernelType,Nu,P,setType)
//
// Parameters
// classifier: Image category classifier location
// BagofFeaturesLocation : location of the xml or yml file.
// Description : features obtained after training.
// imgSets: Input imageSet to train the classifier on
// bag: The bagOfFeatures of the imageSet provided
// image: The set of images used for creating the imageset used for training
// nameclass: Name of the classifier one wants for their trained model .xml or .yml file
// C: Parameter C of a SVM optimization problem that should be used to train the model
// coef: Parameter coef0 of a kernel function that should be used to train the model
// degree: Parameter degree of a kernel function that should be used to train the model
// gamma:Parameter γ of a kernel function that should be used to train the model.
// kernelType:Type of a SVM kernel that should be used to train the model.it should be [-1,5].
// Nu:Parameter ν of a SVM optimization problem that should be used to train the model.
// P: Parameter ϵ of a SVM optimization problem that should be used to train the model.
// type: Type of a SVM formulation that should be used to train the model.it should be [100,104].
//
//  Description
//  this function is used to train an image classifier using the SVM(Support Vector Machines) Model.
//
// 
// Examples
// //get imageset from 'images2' folder
// image=imageSet('images2','recursive');
// //get bag of features
// x=bagOfFeatures(image);
// //train thew model and name the saved .yml file as "SVM"
// d=trainSVMClassifier(image,x,"SVM");
// //read image to get prediction from mthe above trained data
// z=imread("fish.jpg");
// //finally predict the class using SVM's prediction function for the input image
// resp=predict(d,z,"SVM");
//
// //get imageset from 'images2' folder
// image=imageSet('images2','recursive');
// //get bag of features
// x=bagOfFeatures(image);
// //train the model with the given parameters  and name  the saved .yml file as "SVM"
// d=trainSVMClassifier(image,x,"SVM",1.1,0.2);
// //read image to get prediction from mthe above trained data
// z=imread("fish.jpg");
// //finally predict the class for the input image
// resp=predict(d,z,"SVM");
   



	
    //convert to list
    bag_list = bagStructToList(bag);
	imgSets_list = imageSetToList(imgSet);
    [lhs rhs]=argn(0);
    
    if lhs>1
         error(msprintf(" Too many output arguments"));
    elseif rhs>11 
        error(msprintf(" Too many input arguments,maximum number of arguments is 11"));
    elseif rhs<3
        error(msprintf("the function needs atleast 3 arguments"));
    end
    if rhs==3
        temp=raw_trainSVMClassifier(imgSets_list, bag_list,classifierName);
    elseif rhs==4
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1));
    elseif rhs==5
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2));
    elseif rhs==6
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3));
    elseif rhs==7
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4));
    elseif rhs==8
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5));
    elseif rhs==9
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6));
    elseif rhs==10
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6),varargin(7));
    elseif rhs==11
        temp=raw_trainSVMClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6),varargin(7),varargin(8));                      
    end
    classifier = struct("ClassifierLocation", temp(2), "BagofFeaturesLocation", temp(3), "Description", temp(4));

endfunction
