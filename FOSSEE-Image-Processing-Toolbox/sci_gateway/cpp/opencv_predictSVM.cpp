/***************************************************
Author : Nihar Rao
***************************************************/
#include <iostream>
#include<bits/stdc++.h>
#include<sys/stat.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/ml.hpp"
#include "opencv2/opencv.hpp"


using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;
using namespace cv::ml;

extern "C"
{
    #include "api_scilab.h"
    #include "Scierror.h"
    #include "BOOL.h"
    #include <localization.h>
    #include "sciprint.h"
    #include "../common.h"
    inline bool file_exists_check(const std::string& name) {
        struct stat buffer;   
        return (stat (name.c_str(), &buffer) == 0); 
     }
    int opencv_predictSVM(char *fname, unsigned long fname_len)
    {
        // Error management variables
        SciErr sciErr;

        //------Local variables------//
        int upright = 1;
        Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("FlannBased");
        Ptr<SURF> detector = SURF::create(400, 4, 2, 1, int(upright));
        Ptr<DescriptorExtractor> extractor=detector;
        Ptr<BOWImgDescriptorExtractor> bowDE=makePtr<BOWImgDescriptorExtractor>(extractor,matcher);
        //SurfFeatureDetector detector(1, 4, 2, 1, int(upright));
       // char *classifierLocation = NULL;
        Mat dictionary,features;
        double response;
        vector<KeyPoint> keyPoints;
        int dictionarySize;
        int *piAddr = NULL;
        int *piChild = NULL;
        int iRows, iCols;
        char **pstData = NULL;
        int *piLen = NULL;
        char **classifierDescription = NULL;
        int classifierDescriptionCount;
        char *bagOfFeaturesLocation = NULL;
        int descriptionCount;
        Mat input;
        //------Check number of parameters------//
        CheckInputArgument(pvApiCtx, 2, 2);
        CheckOutputArgument(pvApiCtx, 1, 1);

        //------Get input arguments------//
        retrieveImage(input,2);
        //cvtColor(input, input, cv::COLOR_RGBA2GRAY);
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        if(!isListType(pvApiCtx, piAddr))
        {
            Scierror(999, "Error: The input argument #1 is not of type classifier.\n");
            return 0;
        }

        // Extracting object type and checking if type is classifier
        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 1, &iRows, &iCols, NULL, NULL);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        piLen = (int*)malloc(sizeof(int) * iRows * iCols);

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 1, &iRows, &iCols, piLen, NULL);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        pstData = (char**)malloc(sizeof(char*) * iRows * iCols);

        for(int iter = 0 ; iter < iRows * iCols ; iter++)
        {
            pstData[iter] = (char*)malloc(sizeof(char) * (piLen[iter] + 1));//+ 1 for null termination
        }

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 1, &iRows, &iCols, piLen, pstData);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if(!(strcmp(pstData[0],"classifier")==0))
        {
            Scierror(999, "Error: The input argument #1 is not of type classifier.\n");
            return 0;
        }
        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 2, &iRows, &iCols, NULL, NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        piLen = (int*) malloc(sizeof(int) * iRows * iCols);

        sciErr = getMatrixOfStringInList(pvApiCtx,  piAddr, 2,  &iRows,  &iCols,  piLen,  NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        pstData = (char**) malloc(sizeof(char*) * iRows * iCols);
        for(int iterPstData = 0; iterPstData < iRows * iCols; iterPstData++)
        {
            pstData[iterPstData] = (char*) malloc(sizeof(char) * piLen[iterPstData] + 1);
        }

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 2, &iRows, &iCols, piLen, pstData);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if(iRows!=1 || iCols!=1)
        {
            Scierror(999, "1x1 Matrix expected for classifier argument.");
            return 0;
        }
        string classifierLocation = string(pstData[0]);
        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 3, &iRows, &iCols, NULL, NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        piLen = (int*) malloc(sizeof(int) * iRows * iCols);

        sciErr = getMatrixOfStringInList(pvApiCtx,  piAddr, 3,  &iRows,  &iCols,  piLen,  NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        pstData = (char**) malloc(sizeof(char*) * iRows * iCols);
        for(int iterPstData = 0; iterPstData < iRows * iCols; iterPstData++)
        {
            pstData[iterPstData] = (char*) malloc(sizeof(char) * piLen[iterPstData] + 1);
        }

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 3, &iRows, &iCols, piLen, pstData);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        if(iRows!=1 || iCols!=1)
        {
            Scierror(999, "1x1 Matrix expected for bagOfFeatures argument.");
            return 0;
        }
        bagOfFeaturesLocation = pstData[0];
        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 4, &iRows, &iCols, NULL, NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        piLen = (int*) malloc(sizeof(int) * iRows * iCols);

        sciErr = getMatrixOfStringInList(pvApiCtx,  piAddr, 4,  &iRows,  &iCols,  piLen,  NULL);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        classifierDescription = (char**) malloc(sizeof(char*) * iRows * iCols);
        for(int iterPstData = 0; iterPstData < iRows * iCols; iterPstData++)
        {
            classifierDescription[iterPstData] = (char*) malloc(sizeof(char) * piLen[iterPstData] + 1);
        }

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 4, &iRows, &iCols, piLen, classifierDescription);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        //------Actual processing------//
        FileStorage fs(bagOfFeaturesLocation, FileStorage::READ);
        fs["dictionary"] >> dictionary;
        fs.release();
	try{

	     input.convertTo(input,CV_8U);
        dictionarySize = dictionary.rows;

        bowDE->setVocabulary(dictionary);
        if(!file_exists_check(classifierLocation))
        {
     
            Scierror(999, "Error: the input  File not found!.Please enter correct path!\n");
            return 0;

        }
       Ptr<SVM> svm = Algorithm::load<SVM>(classifierLocation);
        if(!svm->isTrained())
        {
            Scierror(999, "Error: the model is not trained!.\n");
            return 0;




        }
        detector->detect(input, keyPoints);
        bowDE->compute(input, keyPoints, features);
         features.convertTo(features,CV_32F);
        response = svm->predict(features);
        sciprint("\ndone");
        }
        catch(cv::Exception& e)
	{
		const char* err=e.what();
		sciprint("%s",err);

	}
        //------Create output arguments------//
        sciErr = createList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, 1, &piAddr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1,piAddr,1,1,1,&classifierDescription[(int)response]);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        //------Return Arguments------//
        AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx)+1;
        ReturnArguments(pvApiCtx);
        return 0;
    }
    /* ==================================================================== */
}
