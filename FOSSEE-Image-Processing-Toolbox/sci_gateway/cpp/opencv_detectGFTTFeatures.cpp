/***************************************************
Author : Nihar Rao
***************************************************/
#include <iostream>
#include <numeric>
#include<bits/stdc++.h> 
#include <vector>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d.hpp"   
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;


extern "C"
{
    #include "api_scilab.h"
    #include "Scierror.h"
    #include "BOOL.h"
    #include <localization.h>
    #include "sciprint.h"
    #include "../common.h"

	int opencv_detectGFTTFeatures(char *fname, unsigned long fname_len)
	{	

		SciErr sciErr;
		int *piAddr = NULL;
		int *piAddrVal = NULL;
    	int argPresence[7];
    	for(int i=0;i<7;i++)
	        argPresence[i]=0;
	    int val_position;
	    int iRows = 0;
	    int iCols = 0;
	    int *piLen = NULL;
	    char ** pstData = NULL;
    	char *currentArg = NULL;
        double *ROImat = NULL;
        
        double MinContrast = 0.2;
        double MinQuality = 0.1;
        double numBits = 0;
        double numFeatures = 0;
        double *featureVector = NULL;   

//  DECLARING INPUT ARGUMENTS with their default values

		
        
        bool useHarris=false;
        int maxCorners=1000;
        double minDistance=1;
        double K = 0.04;
        double qualityLevel  = 0.01;
        int blockSize=3;
        
       



//	DECLARING OUTPUT ARGUMENTS

		vector<KeyPoint> myPoints;
		int *LocationList = NULL;
		double *LocationData = NULL;
        int feature_rows=0;
        int feature_cols=0;
        

		int size;

//	ARGUMENT CHECK

		CheckInputArgument(pvApiCtx, 1,15);
    	CheckOutputArgument(pvApiCtx,1,5);

//	RETRIEVING IMAGE

    	Mat image;
    	retrieveImage(image,1);

//  GRAYSCALE VALIDATION

   	    if(image.channels()!=1)
   	 	{
    	    Scierror(999," Feature is not meant for RGB images\n");
        	return 0;        
    	}

//	OBTAINING NUMBER OF ARGUMENTS

    	int noOfarguments = *getNbInputArgument(pvApiCtx);

//	ARGUMENT COUNT CHECK

    	if(noOfarguments%2==0)
   	 	{
    	    Scierror(999," Invalid Number Of Arguments\n");
        	return 0;        
    	}

//	MULTIPLE ARGUMENT HANDLING

        for(int i=2;i<noOfarguments;i=i+2)
            {
                sciErr = getVarAddressFromPosition(pvApiCtx,i,&piAddr);
                if (sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    return 0;
                }

                if(!isStringType(pvApiCtx, piAddr))
                {
                    Scierror(999,"Invalid Argument\n");
                    return 0;
                }

                //first call to get rows and columns 
                sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, NULL, NULL);
                if(sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    return 0;
                }
                piLen = (int*)malloc(sizeof(int) * iRows * iCols);
                
                //second call to retrieve length of each string
                sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, NULL);
                if(sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    return 0;
                }
                pstData = (char**)malloc(sizeof(char*) * iRows * iCols);
                for(int j = 0 ; j < iRows * iCols ; j++)
                {
                    pstData[j] = (char*)malloc(sizeof(char) * (piLen[j] + 1));//+ 1 for null termination
                }
                
                //third call to retrieve data
                sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, pstData);
                if(sciErr.iErr)
                {
                    printError(&sciErr, 0);
                    return 0;
                }

                currentArg = pstData[0];
                free(pstData);
                iRows=0;
                iCols=0;
                free(piLen);
                
                if(strcmp(currentArg,"minDistance")==0)
                {
                    val_position=i+1;  
                    
                    if(argPresence[0]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }

                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;   
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal))
                    {
                        Scierror(999,"Invalid Value for minDistance\n");
                        return 0;
                    }     

                    getScalarDouble(pvApiCtx, piAddrVal, &minDistance);
                            
                    
                    argPresence[0]=1;       
                }
                else if(strcmp(currentArg,"K")==0)
                {
                    val_position=i+1;           

                    if(argPresence[1]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }

                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal))
                    {
                        Scierror(999," Invalid Value for K\n");
                        return 0;
                    }     

                    getScalarDouble(pvApiCtx, piAddrVal, &K);
                    
                    argPresence[1]=1;     
                }
                else if(strcmp(currentArg,"qualityLevel")==0)
                {
                    val_position=i+1;
                    
                    
                    if(argPresence[2]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }

                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal))
                    {
                        Scierror(999," Invalid Value for MinQuality. Recommended values are between 0 and 1\n");
                        return 0;
                    }

                    getScalarDouble(pvApiCtx, piAddrVal, &qualityLevel );

          
                    argPresence[2]=1; 
                }
                else if(strcmp(currentArg,"ROI")==0)
                {
                    val_position=i+1;
                    
                    if(argPresence[3]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }
                    
                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal) || isVarComplex(pvApiCtx, piAddrVal))
                    {
                        Scierror(999,"Enter a List of 4 arguments\n");
                        return 0;
                    }

                    sciErr = getMatrixOfDouble(pvApiCtx, piAddrVal, &iRows, &iCols, &ROImat);  
                    if(sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(iRows*iCols!=4)
                    {   
                        Scierror(999,"Invalid Argument\n");
                        return 0;
                    }

                    if(ROImat[0]<0 || ROImat[1]<0 || ROImat[2]<0 || ROImat[3]<0)
                    {   
                        Scierror(999,"Arguments cannot be negative\n");
                        return 0;
                    }       

                    if(ROImat[0]>image.cols || ROImat[1]>image.rows || ROImat[0]+ROImat[2]>image.cols
                        || ROImat[1]+ROImat[3]>image.rows) 
                    {
                        Scierror(999,"Please make sure the arguments are within the image range\n");
                        return 0;
                    }

                    argPresence[3]=1;
                }
               else if(strcmp(currentArg,"maxCorners")==0)
                {
                    val_position=i+1;
                    
                    
                    if(argPresence[4]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }

                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal))
                    {
                        Scierror(999," Invalid type for maxCorners\n");
                        return 0;
                    }
                    double d=0;

                    getScalarDouble(pvApiCtx, piAddrVal, &d);
                    maxCorners=(int)d;

                    
                   
          
                    argPresence[4]=1; 
                }  
                else if(strcmp(currentArg,"useHarris")==0)
                {

                        
                    val_position=i+1;
                    
                    if(argPresence[5]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }
                    
                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    int *r=NULL;

                    sciErr = getMatrixOfBoolean(pvApiCtx, piAddrVal, &iRows, &iCols, &r);
                    if(sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }
                    
                        
                    if(r[0])
                        useHarris=true;
                    else
                        useHarris=false;
                    argPresence[5]=1;
                        
                        
                } 
                else if(strcmp(currentArg,"blockSize")==0)
                {
                    val_position=i+1;
                    
                    
                    if(argPresence[6]==1)
                    {
                        Scierror(999,"Do not enter the same parameter\n");
                        return 0;
                    }

                    sciErr = getVarAddressFromPosition(pvApiCtx,val_position,&piAddrVal);
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0);
                        return 0;
                    }

                    if(!isDoubleType(pvApiCtx, piAddrVal))
                    {
                        Scierror(999," Invalid type for blockSize\n");
                        return 0;
                    }
                    double d=0;

                    getScalarDouble(pvApiCtx, piAddrVal, &d);
                    blockSize=(int)d;

                    
                   
          
                    argPresence[6]=1; 
                }              
                else
                {
                    Scierror(999, "Error: \"%s\" Invalid input argument.\n", currentArg); 
                    return 0; 
                }

            }


//	DEFAULT ARGUMENTS

            if(argPresence[3]==0)
            {
                ROImat=(double *)malloc(sizeof(double)*1*4);
                ROImat[0]=0;
                ROImat[1]=0;
                ROImat[2]=image.cols;
                ROImat[3]=image.rows;       
            }

//	CREATING REGION OF INTEREST    

            Rect masker(ROImat[0], ROImat[1], ROImat[2], ROImat[3]);
            
            Mat mask(image.size(), CV_8UC1, Scalar::all(0));
            mask(masker).setTo(Scalar::all(255));
//KAZE processing
            Mat descriptor;
        Ptr<GFTTDetector> myobject = cv::GFTTDetector::create(maxCorners,qualityLevel,minDistance,blockSize,useHarris,K);
        try     
        {
            image.convertTo(image, CV_8U);
            myobject->detect(image,myPoints,mask);
            Ptr<FREAK> obj=FREAK::create( true, true, 22.0f, 4 ,std::vector< int >());
            obj->compute(image, myPoints ,descriptor);
            numBits = descriptor.size[1];
            numFeatures = descriptor.size[0];

            featureVector = (double*)malloc(sizeof(double)*descriptor.size[0]*descriptor.size[1]);
            for( int i=0; i<descriptor.size[0]; i++)
                for( int j=0; j<descriptor.size[1]; j++)
                {
                    *(featureVector + j*descriptor.size[0] + i) = int( descriptor.at<uchar>(i,j));
                }
                feature_rows = descriptor.size[0];
                feature_cols = descriptor.size[1];    
        }
        catch(cv::Exception &e)
        {
            const char *err = e.what();
            sciprint("%s", err);
            return 0;
        }
        


        size = myPoints.size();


//	LOCATION   ---->
    
    LocationData = (double *)malloc(sizeof(double) * size * 2);
    for(int i = 0; i < size; i++)
    {
        LocationData[i] = myPoints[i].pt.x;
        LocationData[i + size] = myPoints[i].pt.y;
    }
     

//Creating Output Arguments
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, feature_rows, feature_cols, featureVector);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, 1, 1, &numBits);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
    
        sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 3, 1, 1, &numFeatures);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }     
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 4, size, 2, LocationData);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
        

    createScalarInteger32(pvApiCtx,nbInputArgument(pvApiCtx) + 5, size);
    
//	ASSIGNING   ---->

    for(int i=1;i<=5;i++)
    {
 		AssignOutputVariable(pvApiCtx, i) = nbInputArgument(pvApiCtx) + i;   	
    }

    ReturnArguments(pvApiCtx);
	}
    

}