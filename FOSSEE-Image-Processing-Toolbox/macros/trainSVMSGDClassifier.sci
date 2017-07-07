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

function [classifier]=trainSVMSGDSGDClassifier(imgSet,bag,classifierName,varargin)
// This function is used to train an image classifier using the SVMSGD(Stochastic Gradient Descent SVM) Model.
//
// Calling Sequence
// imgSet = imageSet(directory,'recursive');
// 'or'
// imgSet = imageSet(image);
// bag = bagOfFeatures(imgSet);
// classifier = trainSVMSGDClassifier(imgSets, bag);`
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass')
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass')
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize)
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize,marginReg)
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize,marginReg,marginType)
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize,marginReg,marginType,optimalParams)
// classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize,marginReg,marginType,optimalParams,stepDecreasingPower)
//classifier = trainSVMSGDClassifier(imgSets, bag,'nameclass',initialStepSize,marginReg,marginType,optimalParams,stepDecreasingPower,svmsgdType)
//
// Parameters
// classifier: Image category classifier location
// BagofFeaturesLocation : location of the xml or yml file.
// Description : features obtained after training.
// imgSets: Input imageSet to train the classifier on
// bag: The bagOfFeatures of the imageSet provided
// image: The set of images used for creating the imageset used for training
// nameclass: Name of the classifier one wants for their trained model .xml or .yml file
// initialStepSize:Parameter initialStepSize of a SVMSGD optimization problem that should be used to train the model.
// marginReg: Parameter marginRegularization of a SVMSGD optimization problem that should be used to train the model
// marginType: Parameter marginType of a SVMSGD optimization problem that should be used to train the model.it should be either 0 or 1.
// optimalParams: sets optimal parameters values for chosen SVM SGD model.
// stepDecreasingPower: Parameter stepDecreasingPower of a SVMSGD optimization problem that should be used to train the model.
// svmsgdType: Algorithm type of SVMSGD that should be used to train the model.it should be either 0 or 1.
//
//
//  Description
//  This function is used to train an image classifier using the SVMSGD(Stochastic Gradient Descent SVM) Model.
//
// Examples
// //get imageset from 'images2' folder
// image=imageSet('images2','recursive');
// //get bag of features
// x=bagOfFeatures(image);
// //train thew model and name the saved .yml file as "pbrr" using the given parameters
// r=trainSVMSGDClassifier(image,x,"pbrr",0,0,0,1,0,1);
// //read image to get prediction from the above trained data
// z=imread("fish.jpg");
// //finally predict the class using SVMSGD's prediction function for the input image
// resp=predict(r,z,"SVMSGD");
//
// //get imageset from 'images2' folder
// image=imageSet('images2','recursive');
// //get bag of features
// x=bagOfFeatures(image);
// //train the model and name the saved .yml file as "pbrr"
// r=trainSVMSGDClassifier(image,x,"pbrr");
// //read image to get prediction from the above trained data
// z=imread("fish.jpg");
// //finally predict the class using SVMSGD's prediction function for the input image
// resp=predict(r,z,"SVMSGD");

    //convert to list
    bag_list = bagStructToList(bag);
	imgSets_list = imageSetToList(imgSet);
    [lhs rhs]=argn(0);
    
    if lhs>1
         error(msprintf(" Too many output arguments"));
    elseif rhs>9
        error(msprintf(" Too many input arguments,maximum number of arguments is 9"));
    elseif rhs<3
        error(msprintf("the function needs atleast 3 arguments"));
    end
    if rhs==3
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list, bag_list,classifierName);
    elseif rhs==4
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1));
    elseif rhs==5
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2));
    elseif rhs==6
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3));
    elseif rhs==7
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4));
    elseif rhs==8
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5));
    elseif rhs==9
        temp=raw_trainSVMSGDSGDClassifier(imgSets_list,bag_list,classifierName,varargin(1),varargin(2),varargin(3),varargin(4),varargin(5),varargin(6));                    
    end
    classifier = struct("ClassifierLocation", temp(2), "BagofFeaturesLocation", temp(3), "Description", temp(4));

endfunction
