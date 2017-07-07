/***************************************************
Author : Nihar Rao
***************************************************/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/types_c.h"
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


int opencv_stereoCalibrate(char *fname, unsigned long fname_len)
  {
    //variables
    
    int i,j,k,n,m;
    int iRows=0,iCols=0;
    int *piAddr=NULL;
    double *pdblReal = NULL;
    double x,y,rms;
    int p;


    SciErr sciErr;
    vector<std::vector<Point2d> >imagepoints1(1),imagepoints2(1);
    vector<std::vector<Point3d> >objectPoints(1);
    
    

    Mat cameraMatrix1;
    Mat cameraMatrix2;
    Mat distCoeffsActual1,distCoeffsActual2;
    Mat rotationMatrix;
    Mat translationVector;
    int num;

  ////////parsing input
    
     n=*getNbInputArgument(pvApiCtx);
   //first
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    //stores 
    
    //objectPoints = (CvPoint3D64f*)cvAlloc( iRows *1* sizeof(CvPoint3D64f));
    for(i = 0; i < iRows; ++i)
            objectPoints[0].push_back(Point3d(double(pdblReal[(0 * iRows) + i]), double(pdblReal[(1 * iRows) + i]),0.0));


int pointCount=iRows;
    //2nd Input
    
       
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if(!isListType(pvApiCtx, piAddr))
        {
            
            Scierror(999,"\nthe imagepoints1 Argument must be a list of points \n");
            return 0;
        }
    sciErr = getListItemNumber(pvApiCtx, piAddr, &num);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        
        return 0;
    }
    imagepoints1.resize(num);

    //get items from list
    
    for(int i=1;i<=num;i++)
    {
      
      sciErr=getMatrixOfDoubleInList(pvApiCtx, piAddr,i,&iRows, &iCols, &pdblReal);
      
      if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
        
      for(j = 0; j < iRows; ++j)
            imagepoints1[i-1].push_back( Point2d(double(pdblReal[(0 * iRows) + j]), double(pdblReal[(1 * iRows) + j])));
        


    }

    //3rd input
    sciprint("\n");
    sciErr = getVarAddressFromPosition(pvApiCtx, 3, &piAddr);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    if(!isListType(pvApiCtx, piAddr))
        {
            
            Scierror(999,"\nthe imagepoints2 Argument must be a list of points \n");
            return 0;
        }
    sciErr = getListItemNumber(pvApiCtx, piAddr, &num);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        
        return 0;
    }
    imagepoints2.resize(num);
    //get items from list

    for(int i=1;i<=num;i++)
    {
      sciErr=getMatrixOfDoubleInList(pvApiCtx, piAddr,i,&iRows, &iCols, &pdblReal);
      if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

      for(j = 0; j < iRows; ++j)
            imagepoints2[i-1].push_back( Point2d(double(pdblReal[(0 * iRows) + j]), double(pdblReal[(1 * iRows) + j])));


    }

    ///Getting optional arguments

  for(i=4;i<=n;i++)
  {
      sciErr = getVarAddressFromPosition(pvApiCtx,i,&piAddr);
      if (sciErr.iErr)
     {
        printError(&sciErr, 0);
        return 0;
     }

     if(!isDoubleType(pvApiCtx, piAddr))
     {

        Scierror(999,"\nthe input should be of type double\n");
        return 0;


     }
      if(i==4 || i==6)
      {
        sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
        if(sciErr.iErr)
        {
        printError(&sciErr,0);
        return 0;
        }

         Mat C(3,3,CV_8U,&pdblReal);
         if(i==4)
         C.copyTo(cameraMatrix1);
         else
         C.copyTo(cameraMatrix2); 
      }

      if(i==5 || i==7)
      {
         sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows, &iCols, &pdblReal);
          if(sciErr.iErr)
          {
          printError(&sciErr,0);
          return 0;
          }
        if(iRows== 1)
              p = iCols;
          else if (iCols == 1)
              p = iRows;
          else{
              Scierror(1,"Distortion Points matrix  must be a 4 X 1 or 1 X 4 matrix");
              return 0;
          }
          if(p==4);
          else{
              Scierror(1," N must be 4");
              return 0;
          }
          Mat A(1,p,CV_8U,&pdblReal);
          if(i==5)
          A.copyTo(distCoeffsActual1);
          else
          A.copyTo(distCoeffsActual2);

      }

  }
    
    
   
    try
    {
         Size imageSize (600,960);
         
       rms = fisheye::stereoCalibrate(objectPoints,imagepoints1,imagepoints2,
                  cameraMatrix1, distCoeffsActual1,
                  cameraMatrix2, distCoeffsActual2,
                  imageSize, rotationMatrix, translationVector,fisheye::CALIB_FIX_SKEW | fisheye::CALIB_RECOMPUTE_EXTRINSIC | fisheye::CALIB_FIX_K4, 
                  TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, DBL_EPSILON));
       
     }    
         catch(cv::Exception& e)
    {

      Scierror(999,e.what());
      return 0;



    }
       sciprint("Calibration done with RMS error=%f\n",rms);



       ///Return Arguments to Scilab
       
    double *pstdata1 = NULL,*pstdata2 = NULL,*pstdata3 = NULL,*pstdata4 = NULL,*pstdata5 = NULL,*pstdata6 = NULL;
    pstdata1 = (double*)malloc(sizeof(double) *3* 3);
    
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            pstdata1[(j * 3) + i]=cameraMatrix1.at<double>(i,j); 
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, 3, 3, pstdata1);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    
     pstdata2 = (double*)malloc(sizeof(double) *4*1);
    
    for(i=0;i<4;i++)
         pstdata2[i]=distCoeffsActual1.at<double>(0,i);
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, 1, 4, pstdata2);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }

    pstdata3 = (double*)malloc(sizeof(double) *3* 3);
    
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            pstdata3[(j * 3) + i]=cameraMatrix2.at<double>(i,j); 
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 3, 3, 3, pstdata3);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    pstdata4 = (double*)malloc(sizeof(double) *4*1);
    for(i=0;i<4;i++)
         pstdata4[i]=distCoeffsActual2.at<double>(0,i);
    
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 4, 1, 4, pstdata4);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    pstdata5=(double*)malloc(sizeof(double) *rotationMatrix.rows*rotationMatrix.cols);

    for(i=0;i<rotationMatrix.rows;i++)
      for(j=0;j<rotationMatrix.cols;j++)
      {

         pstdata5[(j * rotationMatrix.rows) + i]=rotationMatrix.at<double>(i,j); 

      }

    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 5, rotationMatrix.rows, rotationMatrix.cols, pstdata5);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }

     pstdata6=(double*)malloc(sizeof(double) *translationVector.rows*translationVector.cols);

    for(i=0;i<translationVector.rows;i++)
      for(j=0;j<translationVector.cols;j++)
      {

         pstdata6[(j * translationVector.rows) + i]=translationVector.at<double>(i,j); 

      }

    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 6, translationVector.rows, translationVector.cols, pstdata6);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }



    for(int i=1;i<=6;i++)
  AssignOutputVariable(pvApiCtx, i) = nbInputArgument(pvApiCtx) + i;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);
    return 0;       



    }
}
    








