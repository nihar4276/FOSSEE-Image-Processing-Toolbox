/***************************************************
Author : Nihar Rao
***************************************************/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
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
  
  int opencv_undistortPoints(char *fname, unsigned long fname_len)
  {
    //variables
    
    int i,j,k,n,m;
    int iRows=0,iCols=0;
    int *piAddr1  = NULL;
    int *piAddr2  = NULL;
    int *piAddr3  = NULL;
    int *piAddr4  = NULL;
    int *piAddr5  = NULL;
    
    double *pdblReal = NULL;

    SciErr sciErr;

    //function varible
    std::vector< Point2d > Src;
    std::vector< Point2d > dst;
    double cameraMatrix [3][3];
    double newCameraMatrix [3][3];
    double *distCoeffs = NULL;
    double RectificationMatrix[3][3];

    /*------------------------------------------- Checking Input Argument ----------------------------------------------------*/
    
    CheckInputArgument(pvApiCtx, 5, 5);
    CheckOutputArgument(pvApiCtx, 1, 1) ;

    /*------------------------------------- Source matrix :- First argument of the input -------------------------------------*/
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr1, &iRows, &iCols, &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    // For 1 X N single channel
    for(i = 0; i < iRows; ++i)
            Src.push_back( Point2d(pdblReal[(0 * iRows) + i], pdblReal[(1 * iRows) + i]));

    /* ------------------------------------ Camera matrix :- Second argument of the input -------------------------------------*/
        
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &iRows, &iCols, &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    Mat cameraMat(3, 3, CV_64F);
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            cameraMat.at<double>(i,j) = pdblReal[(j * 3) + i];
    
        
    /* ------------------------------------ Distortion Coefficient matrix :- Third argument of the input -------------------------------------*/
    
    sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr3, &iRows, &iCols, &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
    if(iRows== 1)
        n = iCols;
    else if (iCols == 1)
        n = iRows;
    else{
        Scierror(1,"Points matrix (arg 4) must be a 2 X N matrix");
        return 0;
    }
    if(n==4 or n==5 or n==8);
    else{
        Scierror(1," n must be 4 or 5 or 8");
        return 0;
    }
    
    

    Mat distCoeffsActual(1,n,CV_64F);
    for(i=0;i<n;i++)
        distCoeffsActual.at<double>(0,i) = pdblReal[i];


    /* ------------------------------------ Rectification matrix :- Fourth argument of the input -------------------------------------*/
    
    sciErr = getVarAddressFromPosition(pvApiCtx, 4, &piAddr4);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr4, &iRows, &iCols, &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    Mat RectMat(3, 3, CV_64F);
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            RectMat.at<double>(i,j) =pdblReal[(j*3)+i];
    

    /* ------------------------------------ New Camera matrix :- Fifth argument of the input -------------------------------------*/
  
    sciErr = getVarAddressFromPosition(pvApiCtx,5,&piAddr5);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr5, &iRows, &iCols , &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    } 

    Mat newCameraMat(3,3,CV_64F);
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            newCameraMat.at<double>(i, j) =pdblReal[(j*3)+i];  

    
    
    /* opencv function for undistortPoints */
    try
    {
    fisheye::undistortPoints(Src, dst, cameraMat, distCoeffsActual, RectMat, newCameraMat);
    }
    catch(cv::Exception& e)
    {

        sciprint("%s",e.what());


    }
    /* Writing to Scilab */
    double *pstdata = NULL;
    pstdata = (double*)malloc(sizeof(double) * dst.size() * 2);
    
    for(i = 0; i < dst.size(); i++)
    {
            pstdata[i + 0 * dst.size()] = dst[i].x;
            pstdata[i + 1 * dst.size()] = dst[i].y;
    }
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, dst.size(), 2, pstdata);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    
    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);
    return 0;

  }
/* ==================================================================== */
}