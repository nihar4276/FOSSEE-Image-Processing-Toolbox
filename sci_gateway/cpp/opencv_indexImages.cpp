/****************************************************************************************
* Author: Umang Agrawal                                                                 *
* Code:   indexImages.cpp                                                               *
* Function Call:   indexImage = indexImages( Image_Set, Bag, Optional Arguments)        *
*          Optional Argument:   Name                  Value                             *
*                              Verbose             Bool(1 or 0)                         *
*                        SaveFeatureLocations      Bool(1 or 0)                         *
****************************************************************************************/
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"


using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

extern "C"
{
	#include "api_scilab.h"
	#include "Scierror.h"
	#include "BOOL.h"
	#include <localization.h>
	#include "sciprint.h"
	#include "../common.h"

  bool response(const KeyPoint& p1, const KeyPoint& p2) {
      return p1.response > p2.response;
  }

	int opencv_indexImages(char *fname, unsigned long fname_len)
  {
    SciErr sciErr;

    int *piAddr = NULL;
    int *piAddr1 = NULL;
    int *piAddr2 = NULL;
    int *piAddr3 = NULL;
    int *piAddr4 = NULL;
    int *piChild = NULL;
    int *piGrandChild = NULL;
    int iRows, iCols;
    int *piLen = NULL;
    char **pstData = NULL;
    char *objectType = "invertedImageIndex";
    char **description = NULL;
    char ***location = NULL;
    int *count = NULL;
    int descriptionCount;
    char **arg = NULL;
    char **filePath = NULL;

    int inp_params = 0;
    char *bagOfFeaturesLocation = NULL;
    double *upright_bag = NULL;
    double *strength_bag = NULL;
    double *vocab_size_bag = NULL;
    int count_ver = 0, count_save = 0;
    double save = 1;
    double verbose = 1;
    int upright = 1;
    int vocab_size = 500;
    double strength = 0.8;

    vector<int> key_size_vector;
    double *wordFrequency = NULL;
    double ***ImageWords = NULL;
    int indx;

    Mat image;
    Mat dictionary;
    Mat featuresUnclustered;
    Mat feature_des;
    Mat des_matched;
    Mat hist;
    vector<KeyPoint> keypoints;
    vector<KeyPoint> valid_key;
    vector< vector<int> > clusterID;
    int key_size;
    int v_key_size;

    CheckInputArgument(pvApiCtx, 1, 6);						//Check on Number of Input Arguments
		CheckOutputArgument(pvApiCtx, 1, 1);						//Check on Number of Output Arguments

    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    if(!isListType(pvApiCtx, piAddr1))
    {
        Scierror(999, "Error: Invalid first argument. List Expected.\n");
        return 0;
    }
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 1, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
    {
      printError(&sciErr, 0);
      return 0;
    }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 1, &iRows, &iCols, piLen, NULL);
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
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 1, &iRows, &iCols, piLen, pstData);
    if(sciErr.iErr)
    {
      printError(&sciErr, 0);
      return 0;
    }

    if(!(strcmp(pstData[0],"imageSet")==0))
    {
        Scierror(999, "Error: The input argument 1 is not of type imageSet.\n");
        return 0;
    }

    // Extracting Description attribute of input argument
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 2, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
    {
      printError(&sciErr, 0);
      return 0;
    }
    if( iRows!= 1 )
    {
      Scierror(999,"Expecting an image Set with single type of Images.\n");
      return 0;
    }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 2, &iRows, &iCols, piLen, NULL);
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
    sciErr = getMatrixOfStringInList(pvApiCtx, piAddr1, 2, &iRows, &iCols, piLen, description);
    if(sciErr.iErr)
    {
      printError(&sciErr, 0);
      return 0;
    }
    descriptionCount = iRows;

    // Extracting Count attribute of input argument
    sciErr = getMatrixOfInteger32InList(pvApiCtx, piAddr1, 3, &iRows, &iCols, &count);
    if(sciErr.iErr)
    {
      printError(&sciErr, 0);
      return 0;
    }
    if( iRows!= 1 )
    {
      Scierror(999,"Expecting an image Set with single type of Images.\n");
      return 0;
    }
    location = (char***) malloc(sizeof(char**) * descriptionCount);
    sciErr = getListItemAddress(pvApiCtx, piAddr1, 4, &piChild);
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

//..............................................................................................................
    inp_params = *getNbInputArgument(pvApiCtx);
    if( inp_params>=2 )
    {
      sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr2);
      if (sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      if(!isListType(pvApiCtx, piAddr2))
      {
          Scierror(999, "Error: Invalid first argument. List Expected.\n");
          return 0;
      }
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 1, &iRows, &iCols, NULL, NULL);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      piLen = (int*)malloc(sizeof(int) * iRows * iCols);
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 1, &iRows, &iCols, piLen, NULL);
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
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 1, &iRows, &iCols, piLen, pstData);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      if(!(strcmp(pstData[0],"bagOfFeatures")==0))
      {
          Scierror(999, "Error: The input argument 2 is not of type bagOfFeatures.\n");
          return 0;
      }
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 2, &iRows, &iCols, NULL, NULL);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      piLen = (int*)malloc(sizeof(int) * iRows * iCols);
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 2, &iRows, &iCols, piLen, NULL);
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
      sciErr = getMatrixOfStringInList(pvApiCtx, piAddr2, 2, &iRows, &iCols, piLen, pstData);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      bagOfFeaturesLocation = pstData[0];
      sciErr = getMatrixOfDoubleInList(pvApiCtx, piAddr2, 3, &iRows, &iCols, &vocab_size_bag);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      sciErr = getMatrixOfDoubleInList(pvApiCtx, piAddr2, 4, &iRows, &iCols, &strength_bag);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      sciErr = getMatrixOfDoubleInList(pvApiCtx, piAddr2, 5, &iRows, &iCols, &upright_bag);
      if(sciErr.iErr)
      {
        printError(&sciErr, 0);
        return 0;
      }
      upright = int(upright_bag[0]);
      vocab_size = int(vocab_size_bag[0]);
      strength = strength_bag[0];
      FileStorage fs(bagOfFeaturesLocation, FileStorage::READ);
      fs["dictionary"] >> dictionary;
      fs.release();

//................................................................................................................
      for( int i=3; i<=inp_params; i++)
      {
        if( inp_params%2 != 0)
        {
          Scierror(999,"Either Argument Name or its Value missing\n");
          return 0;
        }
        sciErr = getVarAddressFromPosition(pvApiCtx, i, &piAddr3);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          return 0;
        }
        //Check for Argument type
        if( !isStringType(pvApiCtx, piAddr3))
        {
          Scierror(999, "%s: Wrong type of argument for Name of Optional Argument. A string is expected.\n", fname);
          return 0;
        }
        //Matrix of Stings
        sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, NULL, NULL);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          return 0;
        }
        piLen = (int*)malloc(sizeof(int) * iRows * iCols);
        //second call to retrieve the length of the string
        sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, piLen, NULL);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          free(piLen);
          return 0;
        }
        arg = (char**)malloc(sizeof(char*) * iRows * iCols);
        for(int j=0;j< iRows * iCols; j++)
        {
          arg[j] = (char*)malloc(sizeof(char) * (piLen[j] + 1));
        }

        //third call to retrieve data
        sciErr = getMatrixOfString(pvApiCtx, piAddr3, &iRows, &iCols, piLen, arg);
        if(sciErr.iErr)
        {
          printError(&sciErr, 0);
          free(piLen);
          free(arg);
          return 0;
        }

        if(strcmp(arg[0],"Verbose") == 0)
        {
          if( count_ver != 0)
  				{
  					Scierror(999,"Verbose has been called twice.\n");
  					return 0;
  				}
          free(arg);
  				free(piLen);
          sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr4);
          if(sciErr.iErr)
          {
            printError(&sciErr, 0);
            return 0;
          }
          if( !(isDoubleType(pvApiCtx, piAddr4)||isIntegerType(pvApiCtx, piAddr4)))
          {
            Scierror(999,"Not a valid type of value for Verbose.\n");
            return 0;
          }
          //Reading the Value of the argument
          if(getScalarDouble(pvApiCtx, piAddr4, &verbose))
          {
            Scierror(999,"Not a valid type of value for Verbose.\n");
            return 0;
          }
          if( !(verbose == 1|| verbose == 0) )
          {
            Scierror(999,"Enter a valid value for Verbose (Either 0 or 1)\n");
            return 0;
          }
  				i++;
          count_ver += 1;
          }
        else if(strcmp(arg[0],"SaveFeatureLocations") == 0)
        {
          if( count_save != 0)
  				{
  					Scierror(999,"SaveFeatureLoactions has been called twice.\n");
  					return 0;
  				}
          free(arg);
  				free(piLen);
          sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr4);
          if(sciErr.iErr)
          {
            printError(&sciErr, 0);
            return 0;
          }
          if( !(isDoubleType(pvApiCtx, piAddr4)||isIntegerType(pvApiCtx, piAddr4)))
          {
            Scierror(999,"Not a valid type of value for SaveFeatureLoactions.\n");
            return 0;
          }
          //Reading the Value of the argument
          if(getScalarDouble(pvApiCtx, piAddr4, &save))
          {
            Scierror(999,"Not a valid type of value for SaveFeatureLoactions.\n");
            return 0;
          }
          if( !(save == 1|| save == 0) )
          {
            Scierror(999,"Enter a valid value for SaveFeatureLoactions (Either 0 or 1)\n");
            return 0;
          }
  				i++;
          count_save += 1;
        }
        else
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
          Scierror(999,"Invalid Argument Name\n");
          return 0;
        }
      }
    }

    if(int(verbose))
    {
      sciprint("Creating an Inverted image Index Using Bag-Of-Features.\n");
      sciprint("--------------------------------------------------------\n");
    }

    if( inp_params == 1)
    {
      bagOfFeaturesLocation = "Bag-Of-Features.yml";
      Ptr<SURF> detector = SURF::create( 400, 4, 2, 1, int(upright) );
        Ptr<SURF> extractor = SURF::create(400, 4, 2, 1, int(upright));

  		if(int(verbose))
  		{
  			sciprint("Creating Bag-Of-Features from %d image sets.\n\n",descriptionCount);
  			for(int i=0; i<descriptionCount; i++)
  				sciprint("Image set %d: %s\n",i+1,description[i]);
  			sciprint("\nExtracting SURF Features from each image set.\n\n");
  		}

  		for( int i=0; i<descriptionCount; i++)
  		{
  			if(int(verbose))
  				sciprint("Extracting features from %d images in image set %d",count[i],i+1);
  			key_size = 0;
        v_key_size = 0;
  			for( int j=0; j<count[i]; j++)
  			{
                                                                                                                                                                                                                          				if(int(verbose))
  					sciprint(".");
  				keypoints.clear();
          valid_key.clear();
  				image = imread(location[i][j],1);
  				detector->detect(image, keypoints);
          sort(keypoints.begin(), keypoints.end(), response);
  				for( int k=0; k<(keypoints.size()*strength); k++)
  				{
  					valid_key.push_back(keypoints[k]);
  				}
  				extractor->compute(image, valid_key, feature_des);
  				featuresUnclustered.push_back(feature_des);
  				key_size += keypoints.size();
          v_key_size += valid_key.size();
  			}
  			if(int(verbose))
  			{
  				sciprint("done. Extracted %d features.\n",key_size);
  				sciprint("Keeping %f percent of the strongest features.\n",(strength)*100);
  				sciprint("Net Extracted features : %d\n\n",v_key_size);
  			}
  		}

  		vocab_size = featuresUnclustered.rows;
  		TermCriteria tc(CV_TERMCRIT_ITER, 100, 0.001);
  	  int retries = 3;
  		BOWKMeansTrainer bowTrainer(int(vocab_size), tc, retries, KMEANS_PP_CENTERS);

  		if(int(verbose))
  		{
  			sciprint("Using K-Means Clustering to create a %d word visual vocabulary.\n",int(vocab_size));
  			sciprint("Number of Features : %d\n",featuresUnclustered.rows);
  			sciprint("Number of Clusters : %d\n\n",int(vocab_size));
  		}

  		dictionary = bowTrainer.cluster(featuresUnclustered);

  		if(int(verbose))
  			sciprint("Finished creating Bag-Of-Features\n");

  		FileStorage fs(bagOfFeaturesLocation, FileStorage::WRITE);
  	  fs<<"dictionary"<<dictionary;
  	  fs.release();
    }

    filePath = (char**)malloc(sizeof(char*)*1*1);
    filePath[0] = (char*)malloc(sizeof(char)*20*1);
    strcpy(filePath[0],bagOfFeaturesLocation);

    if(int(verbose))
    {
      sciprint("Encoding 1 Image Set using Bag-Of-Features.\n");
      sciprint("--------------------------------------------\n");
    }

    if(int(verbose))
    {
      sciprint("\nImage set 1: %s\n\n",description[0]);
      sciprint("Encoding %d images from image set 1",count[0]);
    }
    try
    {
    ImageWords = (double***)malloc(sizeof(double**)*count[0]*1);
    wordFrequency = (double*)malloc(sizeof(double)*vocab_size);
    for( int j=0; j<vocab_size; j++)
    {
      wordFrequency[j] = 0;
    }

    Ptr<SURF> detector = SURF::create( 400, 4, 2, 1, int(upright) );
        Ptr<SURF> extractor = SURF::create(400, 4, 2, 1, int(upright));
    for( int i=0; i<count[0]; i++)
    {
      if(int(verbose))
        sciprint(".");
      valid_key.clear();
      keypoints.clear();
      feature_des.release();
      image = imread(location[0][i],1);
      detector->detect(image, keypoints);
      extractor->compute(image, keypoints,feature_des);

      key_size_vector.push_back(keypoints.size());
      ImageWords[i] = (double**)malloc(sizeof(double*)*4*1);
      ImageWords[i][0] = (double*)malloc(sizeof(double)*keypoints.size()*1);
      ImageWords[i][1] = (double*)malloc(sizeof(double)*keypoints.size()*2);
      ImageWords[i][2] = (double*)malloc(sizeof(double)*1);
      ImageWords[i][3] = (double*)malloc(sizeof(double)*1);

      ImageWords[i][2][0] = vocab_size;
      ImageWords[i][3][0] = keypoints.size();

      for( int j=0; j<keypoints.size(); j++)
      {
        ImageWords[i][1][j] = keypoints[j].pt.x;
        ImageWords[i][1][keypoints.size() + j] = keypoints[j].pt.y;
      }
      for( int j=0; j<clusterID.size(); j++)
      {
        wordFrequency[j] = wordFrequency[j]+clusterID[j].size();
        for( int k=0; k<clusterID[j].size(); k++)
        {
            indx = clusterID[j][k];
            ImageWords[i][0][indx] = j;
        }
      }
    }
    if(int(verbose))
    {
      sciprint("done.\n\n");
      sciprint("Finished encoding images.\nFinished creating the image index\n");
    }
  }
  catch(cv::Exception& e)
  {

    sciprint("%s",e.what());
    return 0;

  }

    sciErr = createList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, 4+int(save), &piAddr);
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
    sciErr = createListInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piAddr, 2, count[0], &piChild);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    for( int i=0; i<count[0]; i++)
    {
      sciErr = createListInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piChild, i+1, 4, &piGrandChild);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piGrandChild, 1, key_size_vector[i], 1, ImageWords[i][0]);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piGrandChild, 2, key_size_vector[i], 2, ImageWords[i][1]);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piGrandChild, 3, 1, 1, ImageWords[i][2]);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piGrandChild, 4, 1, 1, ImageWords[i][3]);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
    }
    sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piAddr, 3, vocab_size, 1, wordFrequency);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piAddr, 4, 1, 1, filePath);
		if(sciErr.iErr)
		{
			printError(&sciErr, 0);
			return 0;
		}
    if(int(save) == 1)
    {
      sciErr = createListInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piAddr, 5, descriptionCount, &piChild);
      if(sciErr.iErr)
      {
          printError(&sciErr, 0);
          return 0;
      }
      for(int i=0;i<descriptionCount;i++)
      {
          sciErr = createMatrixOfStringInList(pvApiCtx, nbInputArgument(pvApiCtx)+1, piChild, i+1, 1, count[i], location[i]);
          if(sciErr.iErr)
          {
              printError(&sciErr, 0);
              return 0;
          }
      }
    }
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx)+1;
    ReturnArguments(pvApiCtx);
    return 0;
  }
}
