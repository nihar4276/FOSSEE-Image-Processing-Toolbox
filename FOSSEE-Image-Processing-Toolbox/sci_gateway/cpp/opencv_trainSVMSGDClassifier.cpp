/***************************************************
Author : Nihar Rao
***************************************************/
#include <iostream>
#include<bits/stdc++.h>
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

    double readdoubles_from_scilab(int cnt)
    {

            SciErr sciErr;
           int *piAddr=NULL;
           double val=0;
         int  intErr;

        sciErr = getVarAddressFromPosition(pvApiCtx,cnt,&piAddr);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
         intErr = getScalarDouble(pvApiCtx, piAddr ,&val);

        if(isDoubleType(pvApiCtx, piAddr))
        return val;
        else
        {
          Scierror(999,"Error: the input argument is not of type double");
          return 0;


        }


    }



    int opencv_trainSVMSGDClassifier(char *fname, unsigned long fname_len)
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
        char *fileName = NULL;
        Mat dictionary,inp,features;
        vector<KeyPoint> keyPoints;


        int *piAddr = NULL;
        int *piChild = NULL;
        int iRows, iCols;
        char **pstData = NULL;
        int *piLen = NULL;
        int *count = NULL;
        char **description = NULL;
        char ***location = NULL;
        char *bagOfFeaturesLocation = NULL;
        int descriptionCount;
        char *classifierLocation = "classifier.yml";
        char *objectType = "classifier";
        int intErr = 0;
	char* stringData = NULL;
        char* classifierName;
        int iRet;

        double initStepSize=0.2,marginreg=0,optimalParam=0,stepDecreasingPower=0.1;//all model paramenter set to their default values
        int marginType=0,svmsgdType=0;
        

        //------Check number of parameters------//
        CheckInputArgument(pvApiCtx, 3,9);
        CheckOutputArgument(pvApiCtx, 1, 1);

        //------Get input arguments------//
        int n=*getNbInputArgument(pvApiCtx);
        sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        if(!isListType(pvApiCtx, piAddr))
        {
            Scierror(999, "Error: The input argument #1 is not of type imageSet.\n");
            return 0;
        }

        // Extracting object type and checking if type is imageSet
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

        if(!(strcmp(pstData[0],"imageSet")==0))
        {
            Scierror(999, "Error: The input argument #1 is not of type imageSet.\n");
            return 0;
        }

        // Extracting Description attribute of input argument
        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 2, &iRows, &iCols, NULL, NULL);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        piLen = (int*)malloc(sizeof(int) * iRows * iCols);

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 2, &iRows, &iCols, piLen, NULL);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        description = (char**)malloc(sizeof(char*) * iRows * iCols);

        for(int iter = 0 ; iter < iRows * iCols ; iter++)
        {
            description[iter] = (char*)malloc(sizeof(char) * (piLen[iter] + 1));//+ 1 for null termination
        }

        sciErr = getMatrixOfStringInList(pvApiCtx, piAddr, 2, &iRows, &iCols, piLen, description);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        descriptionCount = iRows;	
             
        // Extracting Count attribute of input argument
        sciErr = getMatrixOfInteger32InList(pvApiCtx, piAddr, 3, &iRows, &iCols, &count);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

        location = (char***) malloc(sizeof(char**) * descriptionCount);
        sciErr = getListItemAddress(pvApiCtx, piAddr, 4, &piChild);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        for(int iter = 1; iter<=descriptionCount; iter++)
        {
            sciErr = getMatrixOfStringInList(pvApiCtx, piChild, iter, &iRows, &iCols, NULL, NULL);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }

            piLen = (int*)malloc(sizeof(int) * iRows * iCols);

            sciErr = getMatrixOfStringInList(pvApiCtx, piChild, iter, &iRows, &iCols, piLen, NULL);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }

            location[iter-1] = (char**)malloc(sizeof(char*) * iRows * iCols);

            for(int colIter = 0 ; colIter < iRows * iCols ; colIter++)
            {
                location[iter-1][colIter] = (char*)malloc(sizeof(char) * (piLen[colIter] + 1));//+ 1 for null termination
            }

            sciErr = getMatrixOfStringInList(pvApiCtx, piChild, iter, &iRows, &iCols, piLen, location[iter-1]);
            if(sciErr.iErr)
            {
                printError(&sciErr, 0);
                return 0;
            }
        }
        // Second argument
        sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr);
        if (sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        if(!isListType(pvApiCtx, piAddr))
        {
            Scierror(999, "Error: The input argument #2 is not of type bagOfFeatures.\n");
            return 0;
        }

        // Extracting object type and checking if type is bagOfFeatures
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

        if(!(strcmp(pstData[0],"bagOfFeatures")==0))
        {
            Scierror(999, "Error: The input argument #2 is not of type bagOfFeatures.\n");
            return 0;
        }
        // Extracting name of next argument takes three calls to getMatrixOfString
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
            Scierror(999, "1x1 Matrix expected for bagOfFeatures argument.");
            return 0;
        }
        // Handling 3rd argument.
		sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddr);
		if(sciErr.iErr)
		{
			printError(&sciErr, 0);
			return 0;
		}
        if(isStringType(pvApiCtx, piAddr))
        {
    		if(isScalar(pvApiCtx, piAddr))
            {
                char* stringData = NULL;

                iRet = getAllocatedSingleString(pvApiCtx, piAddr, &stringData);
                if(!iRet)
                {
                    classifierName = stringData;
                }
                else
                {
                    Scierror(999, "Error: Could not assign input arg #3 to local var.\n");
                    return 0;
                }
            }
           	else
    	    {
    		    Scierror(999, "Error: The input argument #3 is not scalar type.\n");
        		return 0;
    	    }
        }
        else 
        {
            Scierror(999, "Error: The input argument #3 is not a string.\n");
            return 0;
        }
        bagOfFeaturesLocation = pstData[0];
        classifierLocation = classifierName;
        strcat(classifierLocation, ".yml");
        //------Actual processing------//
        FileStorage fs(bagOfFeaturesLocation, FileStorage::READ);
        fs["dictionary"] >> dictionary;
        fs.release();
        if(dictionary.rows==0 || dictionary.cols==0)
        {
            sciprint("Error: The provided file for bagOfFeatures may be invalid.\n");
        }
        sciprint("Training an image category classifier for %d categories.\n",descriptionCount);
        sciprint("-------------------------------------------------------\n\n");
        for(int i=0;i<descriptionCount;i++)
        {
            sciprint("# Category %d: %s\n",i+1,description[i]);
        }
        sciprint("\n");
        int dictionarySize = dictionary.rows;
        Mat labels(0, 1, CV_32SC1);
        Mat trainingData(0, dictionarySize, CV_32FC1);
        bowDE->setVocabulary(dictionary);
        for(int i=0; i<descriptionCount;i++)
        {
            sciprint("# Encoding features for Category %d ...",i+1);
            for(int j=0; j<count[i]; j++)
            {
                features.release();
                keyPoints.clear();
                fileName = location[i][j];
                inp = imread(fileName,0);
                detector->detect(inp,keyPoints);
                bowDE->compute(inp,keyPoints,features);
                trainingData.push_back(features);
                labels.push_back((int)i);
            }
            sciprint("done.\n");
        }
        int cnt=4;
        switch(n-1)
        {
        case 3:
             
            initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
        break;
        case 4:
             
            initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
            marginreg=readdoubles_from_scilab(cnt);
            cnt++;
        break;
        case 5:
             
            initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
            marginreg=readdoubles_from_scilab(cnt);
            cnt++;
            marginType=(int)readdoubles_from_scilab(cnt);//default type of scalar is double in scilab.so typecasting is needed
            if(marginType>1 || marginType<0)
            {
               Scierror(999,"Error: the marginType should be either 0 or 1");
                return 0;

            }
            cnt++;
        break;
       case 6:
             
            initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
            marginreg=readdoubles_from_scilab(cnt);
            cnt++;
            marginType=(int)readdoubles_from_scilab(cnt);//default type of scalar is double in scilab.so typecasting is needed
            if(marginType>1 || marginType<0)
            {
               Scierror(999,"Error: the marginType should be either 0 or 1");
                return 0;

            }
            cnt++;
            optimalParam=readdoubles_from_scilab(cnt);
            cnt++;
        break;
        case 7:
             
            initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
            marginreg=readdoubles_from_scilab(cnt);
            cnt++;
            marginType=(int)readdoubles_from_scilab(cnt);//default type of scalar is double in scilab.so typecasting is needed
            if(marginType>1 || marginType<0)
            {
               Scierror(999,"Error: the marginType should be either 0 or 1");
                return 0;

            }
            cnt++;
            optimalParam=readdoubles_from_scilab(cnt);
            cnt++;
            stepDecreasingPower=readdoubles_from_scilab(cnt);
            cnt++;
        break;
        case 8:

	    initStepSize=readdoubles_from_scilab(cnt);
            cnt++;
            marginreg=readdoubles_from_scilab(cnt);
            cnt++;
            marginType=(int)readdoubles_from_scilab(cnt);//default type of scalar is double in scilab.so typecasting is needed
            if(marginType>1 || marginType<0)
            {
               Scierror(999,"Error: the marginType should be either 0 or 1");
                return 0;

            }
            cnt++;
            optimalParam=readdoubles_from_scilab(cnt);
            cnt++;
            stepDecreasingPower=readdoubles_from_scilab(cnt);
            cnt++;
            svmsgdType=(int)readdoubles_from_scilab(cnt);//default type of scalar is double in scilab.so typecasting is needed
            if(svmsgdType>1 || svmsgdType<0)
            {
               Scierror(999,"Error: the marginType should be either 0 or 1");
                return 0;

            }

        break;


        }
        sciprint("\n# Training the category classifier...");




        try{

        cv::Ptr<SVMSGD> svmsgd = SVMSGD::create();
        svmsgd->setInitialStepSize(initStepSize);
        svmsgd->setMarginRegularization(marginreg);
        svmsgd->setMarginType(marginType);
        svmsgd->setOptimalParameters(svmsgdType,marginType);
        svmsgd->setStepDecreasingPower(stepDecreasingPower);
        svmsgd->setSvmsgdType(svmsgdType);
        svmsgd->setTermCriteria(cvTermCriteria(CV_TERMCRIT_ITER,100,0.000001));
        svmsgd->train( trainingData , ml::ROW_SAMPLE , labels );
        transpose(trainingData,trainingData);
        if(!svmsgd->isTrained())
            {
             Scierror(999,"\nthere was an error while training the model,please try again!\n");
                return 0;

            }
        if(svmsgd->isTrained())
        svmsgd->save(classifierLocation);
         sciprint("\ndone");

        }
         catch(cv::Exception& e)
	{
		const char* err=e.what();
		sciprint("%s",err);

	}










        //------Create output arguments------//
        sciErr = createList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, 4, &piAddr);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piAddr, 1, 1, 1, &objectType);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piAddr, 2, 1, 1, &classifierLocation);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piAddr, 3, 1, 1, &bagOfFeaturesLocation);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piAddr, 4, descriptionCount, 1, description);
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

