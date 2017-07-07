//Author:- Nihar Rao




#include <numeric>
#include<bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <math.h>
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



int opencv_correctMatches(char *fname, unsigned long fname_len)
{

	    SciErr sciErr;
	    int intErr = 0;
	    int iRows=0,iCols=0;//for fundamental matrix
	    int iRows1=0,iCols1=0;//for points1  array
	    int iRows2=0,iCols2=0;//for points2  array
	    int *piAddrNew = NULL;
	    int *piAddr1  = NULL;
	    int *piAddr2  = NULL;
	    int *piAddr3  = NULL;
	    double *points1,*points2,*fundamental_matrix;
		int i,j;
        double *new1,*new2;
        CheckInputArgument(pvApiCtx, 3,3);
        CheckOutputArgument(pvApiCtx, 2, 2);
        int n=*getNbInputArgument(pvApiCtx);//get number of input arguments
        vector<Point2f> Point1,Point2;

    //for fundamental matrix
    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr1, &iRows, &iCols, &fundamental_matrix);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }
     Mat F(3, 3, CV_32FC1, &fundamental_matrix);

    if(iRows!=3 || iCols!=3)
    {

          Scierror(999, "%s: The entered Fundamental matrix must have dimensions 3*3.\n", fname, 1);
          return 0;


    }
     

    //for points1
    sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &iRows1, &iCols1, &points1);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }

    

            //for points2
    sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr3, &iRows2, &iCols2, &points2);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }
    if(iCols1 != iCols2)
    {
        Scierror(999, "There must be the same number of points in both input arrays(points)\n"); 
        return 0; 
    }

    for(i=0;i<iRows1;i++){

        Point1.push_back(Point2f(points1[i],points1[iRows1+i]));
        Point2.push_back(Point2f(points2[i],points2[iRows2+i]));
        
    }




  

    Mat C,D;
    try{
    cv::correctMatches(F,Point1,Point2,C,D);
     }
     catch(cv::Exception& e)
	{
		const char* err=e.what();
		sciprint("%s",err);
		
	}
    
    new1 = (double*) malloc(sizeof(double) * C.cols *2); 
    for(i = 0 ; i < C.cols ; i++)
    {
        for(j = 0 ; j < 2 ; j++)
        {
            new1[i + C.cols * j] = C.at<double>(i,j);
        }
    }
    


    new2 = (double*) malloc(sizeof(double) * C.cols *2); //both C and D have same dimensions
    for(i = 0 ; i < C.cols ; i++)
    {

        for(j = 0 ; j < 2 ; j++)
        {
            new2[i + C.cols * j] = D.at<double>(i,j);
            
        }
    }
    //Creating Output Arguments
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, C.cols, 2, new1);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, C.cols,2, new2);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    AssignOutputVariable(pvApiCtx, 2) = nbInputArgument(pvApiCtx) + 2;
    ReturnArguments(pvApiCtx);
    return 0;

















}
}
