/****************************************************************************************************
estimateFundamentalMatrix(InputArray1,InputArray2,'method','RANSAC','param1',2,'param2',0.99);

possible methods are 7POINT,8POINT,RANSAC,LMEDS
param1- It indiacates maximum distance from a point to an epipolar line in pixels
param2- It specifies a desirable level of confidence
*********************************************************	***********************************************/
#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
using namespace cv;
using namespace std;
extern "C"
{
  #include "api_scilab.h"
  #include "Scierror.h"
  #include "BOOL.h"
  #include <localization.h>
  #include <sciprint.h>
  #include "../common.h"
  
  int opencv_estimateFundamentalMat(char *fname, unsigned long fname_len)
  {
  
   SciErr sciErr;
   int intErr=0;
   int iComplex = 0;
   int iType = 0;
   int *piAddr  = NULL;
   int *piLen = NULL;
   int iRows,iCols;
   int iA1Rows=0,iA1Cols=0,iA2Rows=0,iA2Cols=0;
   int method=FM_RANSAC;
   int nbInputArguments,iter,i,j;
   char **pstData = NULL; 
   char *currentArg = NULL; 
   bool *providedArgs = NULL; 
   double* pdblReal	= NULL;
   double *iArray1=NULL,*iArray2=NULL;
   double param1=3,param2=0.99;

   vector<Point2f> point1,point2;
  
  CheckInputArgument(pvApiCtx, 2, 8);
  CheckOutputArgument(pvApiCtx, 1, 1) ;
  	
  nbInputArguments = *getNbInputArgument(pvApiCtx); 
  providedArgs = (bool*) malloc(sizeof(bool) * 3); 
  
  
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	sciErr = getVarType(pvApiCtx, piAddr, &iType);
	if(sciErr.iErr || iType != sci_matrix)
	{
		printError(&sciErr, 0);
		return 0;
	}
	//Get complexity
	iComplex = isVarComplex(pvApiCtx, piAddr);
	//Check complexity
	if(iComplex)
	{
		Scierror(999, "%s: Wrong type for input argument: A complex number is not expected.\n");
		return 0;
	}	
	
 	sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iA1Rows, &iA1Cols, &iArray1);
 	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	
	
  	sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	sciErr = getVarType(pvApiCtx, piAddr, &iType);
	if(sciErr.iErr || iType != sci_matrix)
	{
		printError(&sciErr, 0);
		return 0;
	}
	//Get complexity
	iComplex = isVarComplex(pvApiCtx, piAddr);
	//Check complexity
	if(iComplex)
	{
		Scierror(999, "%s: Wrong type for input argument: A complex number is not expected.\n");
		return 0;
	}
	
 	sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iA2Rows, &iA2Cols, &iArray2);
 	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	if(iA1Rows != iA2Rows)
    {
    	Scierror(999, "There must be the same number of points in both input arrays\n"); 
        return 0; 
    }
    
	for(i=0;i<iA1Rows;i++){
		point1.push_back(Point2f(iArray1[i],iArray1[iA1Rows+i]));
		point2.push_back(Point2f(iArray2[i],iArray2[iA2Rows+i]));
	}
	for(iter=3; iter<= nbInputArguments; iter+=2)
    {
		sciErr = getVarAddressFromPosition(pvApiCtx, iter, &piAddr); 
        if (sciErr.iErr)
        {
        	printError(&sciErr, 0); 
            return 0; 
        }
        sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, NULL, NULL); 
            if (sciErr.iErr)
            {
                printError(&sciErr, 0); 
                return 0; 
            }
            
            piLen = (int*) malloc(sizeof(int) * iRows * iCols); 
            
            sciErr = getMatrixOfString(pvApiCtx,  piAddr,  &iRows,  &iCols,  piLen,  NULL); 
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
            
            sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, pstData); 
            if (sciErr.iErr)
            {
                printError(&sciErr, 0); 
                return 0; 
            }
            
            currentArg = pstData[0]; 
            if(strcmp(currentArg, "method")==0)
            {
				//sciprint("in if\tcurrentArg:%s\n",currentArg);            
                if(iter+1<=nbInputArguments && !providedArgs[0])
                {
                    sciErr = getVarAddressFromPosition(pvApiCtx, ++iter, &piAddr); 
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0); 
                        return 0; 
                    }
                    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, NULL, NULL); 
				    if (sciErr.iErr)
				    {
				        printError(&sciErr, 0); 
				        return 0; 
				    }
				    
				    piLen = (int*) malloc(sizeof(int) * iRows * iCols); 
				    
				    sciErr = getMatrixOfString(pvApiCtx,  piAddr,  &iRows,  &iCols,  piLen,  NULL); 
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
				    
				    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, pstData); 
				    if (sciErr.iErr)
				    {
				        printError(&sciErr, 0); 
				        return 0; 
				    }
				    currentArg=pstData[0];
                    // Checking if values are in proper range. Same for all optional arguments
                    //sciprint("in if\tcurrentArg:%s\n",currentArg);
                    if(strcmp(currentArg,"7POINT")==0)
                    	 method = FM_7POINT;	  
					else if (strcmp(currentArg,"8POINT")==0)
						  method= FM_8POINT;
					else if (strcmp(currentArg,"RANSAC")==0)
						  method= FM_RANSAC;
					else if (strcmp(currentArg,"LMEDS")==0)
						  method= FM_LMEDS;
					else
					{
						sciprint("Invalid method given. RANSAC was used instead");
						method= FM_RANSAC;
					}	  
                    providedArgs[0] = 1; 
                }
                else if(providedArgs[0]) // Send an error message if an argument is provided more than once. Same for all optional arguments.
                {
                    Scierror(999, "Please provide optional arguments only once.\n"); 
                    return 0; 
                }
                else // Send an error message if name of argument is given but type is incorrect. Same for all optional arguments.
                {
                    Scierror(999, "Incorrect number of arguments provided. Please check the documentation for more information.\n"); 
                    return 0; 
                }
            }    
            else if(strcmp(currentArg, "param1")==0)
            {
                if(iter+1 <= nbInputArguments  && !providedArgs[1])
                {
                    sciErr = getVarAddressFromPosition(pvApiCtx, ++iter, &piAddr); 
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0); 
                        return 0; 
                    }
                    intErr = getScalarDouble(pvApiCtx, piAddr, &param1); 
                    if(intErr)
                    {
                        return intErr; 
                    }
                    providedArgs[1] = 1; 
                }
                else if(providedArgs[1])
                {
                    Scierror(999, "Please provide optional arguments only once.\n"); 
                    return 0; 
                }
                else
                {
                    Scierror(999, "Incorrect number of arguments provided. Please check the documentation for more information.\n"); 
                    return 0; 
                }
            }
            else if(strcmp(currentArg, "param2")==0)
            {
                if(iter+1 <= nbInputArguments  && !providedArgs[2])
                {
                    sciErr = getVarAddressFromPosition(pvApiCtx, ++iter, &piAddr); 
                    if (sciErr.iErr)
                    {
                        printError(&sciErr, 0); 
                        return 0; 
                    }
                    intErr = getScalarDouble(pvApiCtx, piAddr, &param2); 
                    if(intErr)
                    {
                        return intErr; 
                    }
                    providedArgs[2] = 1; 
                }
                else if(providedArgs[2])
                {
                    Scierror(999, "Please provide optional arguments only once.\n"); 
                    return 0; 
                }
                else
                {
                    Scierror(999, "Incorrect number of arguments provided. Please check the documentation for more information.\n"); 
                    return 0; 
                }
            }
            else
            {
                Scierror(999, "Error: \"%s\" name for input argument is not valid.\n", currentArg); 
                return 0; 
            }
	}
	
	if (method==FM_7POINT && point1.size()!=7){
		Scierror(999, "Error: For FM_7POINT method number of points in each array must be 7\n"); 
        return 0;
	}
	if (method!=FM_7POINT && point1.size()<8 ){
		Scierror(999, "Error: Number of points in each array must be greater than or equal to 8\n");
		return 0;
	}
	
	Mat fm=cv::findFundamentalMat(point1, point2, method, param1, param2);
	pdblReal = (double*) malloc(sizeof(double) * fm.rows *3); 
	for(i = 0 ; i < fm.rows ; i++)
	{
		for(j = 0 ; j < 3 ; j++)
		{
			pdblReal[i + fm.rows * j] = fm.at<double>(i,j);
		}
	}
	sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, fm.rows , 3, pdblReal);
	if(sciErr.iErr)
	{
		printError(&sciErr, 0);
		return 0;
	}
	AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    ReturnArguments(pvApiCtx);
    return 0;
  }  
}
