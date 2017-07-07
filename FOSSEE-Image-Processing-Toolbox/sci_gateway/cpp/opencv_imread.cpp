/***************************************************
Authors : Sukul Bagai and Nihar Rao
***************************************************/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include<sys/stat.h>
using namespace cv;
using namespace std;
extern "C"
{
    #include "api_scilab.h"
    #include "Scierror.h"
    #include "BOOL.h"
    #include <localization.h>
    #include "sciprint.h"
    #include "../common.h"
    #include "../common.cpp"

 bool file_exists_check( char *name) {
        struct stat buffer;   
        return (stat (name, &buffer) == 0); 
     }    

int opencv_imread(char *fname, unsigned long fname_len)
{
    
    SciErr sciErr;
    int iLen        = 0;
    //variable info
    int iRows       = 0;
    int iCols       = 0;
    int piRows      = 0;
    int piCols      = 0;  
    int *piAddr = NULL;      
    int *piLen      = NULL;
    char **pstData  = NULL;
    int **pstData1  = NULL;
    int i,j,k=0;
    int intErr;
    double val;
    Mat img;


    //Checking number of input and output arguments (enviromnet variable, min arguments, max arguments)
    CheckInputArgument(pvApiCtx, 1, 2);
    CheckOutputArgument(pvApiCtx, 1, 1) ;
    
    //get number of input arguments
    int n=*getNbInputArgument(pvApiCtx);
    
    // get Address of inputs
    sciErr = getVarAddressFromPosition(pvApiCtx, 1, &piAddr);

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }


    //Now, we will retrieve the string from the input parameter. For this, we will require 3 calls
    //first call to retrieve dimensions
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
    for(i = 0 ; i < iRows * iCols ; i++)
    {
        pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
    }
    //third call to retrieve data
    sciErr = getMatrixOfString(pvApiCtx, piAddr, &iRows, &iCols, piLen, pstData);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    //read 2nd argument if user has passed 2 arguments
    if(n==2)
    {
    sciErr = getVarAddressFromPosition(pvApiCtx,2,&piAddr);
        if (sciErr.iErr)
        {
        printError(&sciErr, 0);
        return 0;
        }
         intErr = getScalarDouble(pvApiCtx, piAddr ,&val);
       if(intErr)
       {
           Scierror(999,"Error: there was an error while reading the second argument \n");
           return 0;

       }
     }
       int d=(int)val;
       
     if(!file_exists_check(pstData[0]))
        {
            
            Scierror(999, "Error: the input  image not found!.Please enter correct path!\n");
            return 0;
        }

        

     try{

       

    if(n==2)
     {
       switch(d)
       {

        case -1:
        img = imread(pstData[0],CV_LOAD_IMAGE_UNCHANGED);
        break;
        case 0:
        img = imread(pstData[0],CV_LOAD_IMAGE_GRAYSCALE);
        break;
        case 1:
        img = imread(pstData[0],CV_LOAD_IMAGE_COLOR);
        break;
        case 2:
        img = imread(pstData[0],2);
        break;
        case 4:
        img = imread(pstData[0],4);
        break;
        case 8:
        img = imread(pstData[0],8);
        break;
        case 16:
        img = imread(pstData[0],16);
        break;
        case 17:
        img = imread(pstData[0],16);
        break;
        case 32:
        img = imread(pstData[0],32);
        break;
        case 33:
        img = imread(pstData[0],33);
        break;
        case 64:
        img = imread(pstData[0],64);
        break;
        case 65:
        img = imread(pstData[0],65);
        break;
        case 128:
        img = imread(pstData[0],128);
        break;

       }
     
    }
    //one argument
    else
    {
        
        img = imread(pstData[0],CV_LOAD_IMAGE_UNCHANGED);
    }
  }
    catch(cv::Exception& e)
    {
        
        const char* err=e.what();
        Scierror(999,err);

    }

    
    //wrong argument check
    if(n==2 && img.empty())
    {
        Scierror(999,"Error: the second argument is invalid or the image path is wrong!! \n");
           return 0;


    }


    
    string tempstring = type2str(img.type());
    char *checker;
    checker = (char *)malloc(tempstring.size() + 1);
    memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
    returnImage(checker,img,1);
    free(checker);

    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx); 
    return 0;
}
/* ==================================================================== */
}
