/*
  Author-Nihar Rao
*/

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


  int opencv_matMulDeriv(char *fname, unsigned long fname_len)
  {

    SciErr sciErr;
    int intErr = 0;
    int iRows1=0,iCols1=0;//for matrix1  array
    int iRows2=0,iCols2=0;//for matrix2  array
    int *piAddrNew = NULL;
    int *piAddr1  = NULL;
    int *piAddr2  = NULL;
    double *matrix1,*matrix2;
    int i,j;

    CheckInputArgument(pvApiCtx, 2, 2);
    CheckOutputArgument(pvApiCtx, 2, 2);

    int n=*getNbInputArgument(pvApiCtx);//get number of input arguments

//for matrix1
    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr1, &iRows1, &iCols1, &matrix1);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }

   

            Mat A(iRows1,iCols1,CV_64F,&matrix1);//get Mat
            

            //for matrix2
    sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &iRows2, &iCols2, &matrix2);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }


            Mat B(iRows2,iCols2,CV_64F,&matrix2);//get Mat


    //final call
   Mat C,D;
	
	sciprint("yama");
    try{
    cv::matMulDeriv(A,B,C,D);
        }
    catch(cv::Exception& e)
    {
       sciprint("%s",e.what());


    }

	
	
       
 //return the Mat to scilab memory

    double *partial1;//[iRows1*iCols2][iRows1*iCols1];
    partial1=(double*)malloc(sizeof(double)*iRows1*iCols2*iRows1*iCols1);
    for(i=0;i<iRows1*iCols2;i++)
        for(j=0;j<iRows1*iCols1;j++)
            *(partial1 + j*iRows1*iCols2 + i) = int( C.at<uchar>(i,j));

     double *partial2;//[iRows1*iCols2][iRows2*iCols2];
     partial2=(double*)malloc(sizeof(double)*iRows1*iCols2*iRows2*iCols2);
    for(i=0;i<iRows1*iCols2;i++)
        for(j=0;j<iRows2*iCols2;j++)
            *(partial2 + j*iRows1*iCols2 + i) = int(D.at<uchar>(i,j));;

    //Creating Output Arguments
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, iRows1*iCols2, iRows1*iCols1, partial1);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, iRows1*iCols2, iRows2*iCols2, partial2);
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
