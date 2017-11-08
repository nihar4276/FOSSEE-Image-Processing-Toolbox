/* Author -Nihar Rao  */

#include <numeric>
#include<bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgproc/imgproc.hpp"
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



  int opencv_findHomography(char *fname, unsigned long fname_len)
  {
    SciErr sciErr;
    int intErr = 0;
    int *piAddrNew = NULL;
    int *piAddr1  = NULL;
    int *piAddr2  = NULL;
    int *piAddr3  = NULL;
    int *piAddr4  = NULL;
    int *piAddr5  = NULL;
    int iRows1=0,iCols1=0;//for points1  array
    int iRows2=0,iCols2=0;//for points2  array
    int method=0;
    int i,j;
    double ransacReprojThreshold=3;
    int n=*getNbInputArgument(pvApiCtx);//get number of input arguments
    double *points1,*points2;
    vector<Point2f> Point1,Point2;
    double r;
    CheckInputArgument(pvApiCtx, 2, 4);
    CheckOutputArgument(pvApiCtx, 1, 1);


    //for points1
    sciErr = getVarAddressFromPosition(pvApiCtx,1,&piAddr1);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr1, &iRows1, &iCols1, &points1);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }
    if(iCols1!=2)
    {
        Scierror(999,"\n Error: the number of columns in points matrix should be 2 which are x and y coordinate \n");
        return 0;

    }

       
            //for points2
    sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr2);
    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    sciErr = getMatrixOfDouble(pvApiCtx, piAddr2, &iRows2, &iCols2, &points2);
    if(sciErr.iErr)
    {
        printError(&sciErr,0);
        return 0;
    }
    if(iCols2!=2)
    {
        Scierror(999,"\n Error: the number of columns in points matrix should be 2  which are x and y coordinate \n");
        return 0;

    }
      if(iRows1!=iRows2 || iCols2!=iCols1)
      {
         Scierror(999,"\n Error: the number of points in sourch and destination must be same! \n");
        return 0;



      }
   

            
     


    //get optional arguments(A user can pass 4 or 3 or 2 arguments,minimum is 2)
    int flag=0;

    switch(n)
    {

        case 3:
        flag=3;
        //for method
        
        sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        
        intErr= getScalarDouble(pvApiCtx, piAddr3, &r);
        if(intErr)
        return intErr;
        method=(int)r;
        if(method!=16 && method!=8 && method!=4 && method!=0 )
        {

            Scierror(999,"method Argument must be either {0,4,8,16}");
            return 0;
        }
        break;

        case 4:

        flag=4;
       //for method
        sciErr = getVarAddressFromPosition(pvApiCtx,3,&piAddr3);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        
        intErr= getScalarDouble(pvApiCtx, piAddr3, &r);
        if(intErr)
        return intErr;
        method=(int)r;
        if(method!=16 && method!=8 && method!=4 && method!=0 )
        {

            Scierror(999,"method Argument must be either {0,4,8,16}");
            return 0;
        }

        
        sciErr = getVarAddressFromPosition(pvApiCtx,4,&piAddr4);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
        intErr = getScalarDouble(pvApiCtx, piAddr4 ,&ransacReprojThreshold);
        if(intErr)
        return intErr;
        break;
    }
      //  convert to vector
     
    for(i=0;i<iRows1;i++){

        Point1.push_back(Point2f(points1[i],points1[iRows1+i]));
        
        
    }
     

    for(i=0;i<iRows2;i++){

        
        Point2.push_back(Point2f(points2[i],points2[iRows2+i]));
        
    }
     
     
       Mat fun;
       try
       {
     if(flag==0)
        fun=cv::findHomography(Point1,Point2);
     else if(flag==3)
     {

        fun=cv::findHomography(Point1,Point2,method);
    }
     else if(flag==4)
        fun=cv::findHomography(Point1,Point2,method,ransacReprojThreshold);
        }
        catch(cv::Exception& e)
        {

            sciprint("%s",e.what());

        }
//Returning matrix
         
        double *new1;
    new1 = (double*) malloc(sizeof(double) * fun.cols*fun.rows); 
    for(i = 0 ; i < fun.rows ; i++)
    {
        for(j = 0 ; j < fun.cols ; j++)
        {
            new1[i + fun.rows * j] = fun.at<double>(i,j);
        }
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, fun.rows,fun.cols, new1);
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        }

         //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);
    return 0;
  }

}
