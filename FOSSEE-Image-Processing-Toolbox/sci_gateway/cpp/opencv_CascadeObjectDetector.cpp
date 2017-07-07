/********************************************************
Author: Nihar Rao 
*********************************************************
*/

#include <numeric>
#include "opencv2/core/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <sys/stat.h>
#include "opencv2/videoio.hpp"
#include <iostream>
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
 double readdoublec_from_scilab(int cnt)
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
   bool file_existsindirectory_check(const std::string& name) {
        struct stat buffer;   
        return (stat (name.c_str(), &buffer) == 0); 
     }
  
  int opencv_CascadeObjectDetector(char *fname, unsigned long fname_len)
 {
    SciErr sciErr;
    int intErr = 0;
    int iRows=0,iCols=0;
    int iRows1,iCols1;
    int *piAddr = NULL;
    int *piAddrNew = NULL;
    int *piAddr2  = NULL;
    int *piAddr3  = NULL;
    int *piLen = NULL;
    char **object = NULL;
    int i;
    double minX,minY,maxX,maxY;
    double *bboxes = NULL;
    double *minSize,*maxSize;
    double scale=1.05;//all optional arguments are set to their default values
    int minNeighbors=2,flags=2;
    
    CheckInputArgument(pvApiCtx, 2, 7);
    CheckOutputArgument(pvApiCtx, 1, 2) ;
    Mat image,new_image,image_gray;
    //get no. of input arguments
    int n=*getNbInputArgument(pvApiCtx);
    retrieveImage(image, 1);

    ///resize(image,image,Size(800,600),0,0,cv::INTER_AREA);

    sciErr = getVarAddressFromPosition(pvApiCtx,2, &piAddr2);

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getMatrixOfString(pvApiCtx, piAddr2, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string
    sciErr = getMatrixOfString(pvApiCtx, piAddr2, &iRows, &iCols, piLen, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    object= (char**)malloc(sizeof(char*) * iRows * iCols);
    for(i = 0 ; i < iRows * iCols ; i++)
    {
        object[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
    }
    //third call to retrieve data
    sciErr = getMatrixOfString(pvApiCtx, piAddr2, &iRows, &iCols, piLen,object);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    
   ///Reading optional arguments
    int cnt=3;
        switch(n)
        {
          case 3:
           
          scale=readdoublec_from_scilab(cnt);
          cnt++;
          break;
          case 4:
           
          scale=readdoublec_from_scilab(cnt);
          cnt++;
          minNeighbors=(int)readdoublec_from_scilab(cnt);
          cnt++;
          break;
          case 5:
           
          scale=readdoublec_from_scilab(cnt);
          cnt++;
          minNeighbors=(int)readdoublec_from_scilab(cnt);
          cnt++;
          flags=(int)readdoublec_from_scilab(cnt);
          if(flags!=2 && flags!=1 && flags!=4 && flags!=8)
            {
               Scierror(999,"Error: the flag should be {1,2,4,8}\n");
                return 0;

            }

          cnt++;
          break;
          case 6:
           
          scale=readdoublec_from_scilab(cnt);
          cnt++;
          minNeighbors=(int)readdoublec_from_scilab(cnt);
          cnt++;
          flags=(int)readdoublec_from_scilab(cnt);
          cnt++;
          if(flags!=2 && flags!=1 && flags!=4 && flags!=8)
            {
               Scierror(999,"Error: the flag should be {1,2,4,8}\n");
                return 0;

            }

           sciErr = getVarAddressFromPosition(pvApiCtx,cnt,&piAddr);
          if (sciErr.iErr)
          {
            printError(&sciErr, 0);
              return 0;
          }
          sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows1, &iCols1, &minSize);
          if(sciErr.iErr)
          {
            printError(&sciErr,0);
            return 0;
          }

        //check dimensions
        if(iCols1!=2 || iRows1!=1)
        {
          Scierror(999,"The minSize argument must have dimensions 1*2");
          return -1;
        }
          
          cnt++;


          break;
          case 7:
           
          scale=readdoublec_from_scilab(cnt);
          cnt++;
          minNeighbors=(int)readdoublec_from_scilab(cnt);
          cnt++;
          flags=(int)readdoublec_from_scilab(cnt);
          cnt++;
          if(flags!=2 && flags!=1 && flags!=4 && flags!=8)
            {
               Scierror(999,"Error: the flag should be {1,2,4,8}\n");
                return 0;

            }

          sciErr = getVarAddressFromPosition(pvApiCtx,cnt,&piAddr);
          if (sciErr.iErr)
          {
            printError(&sciErr, 0);
              return 0;
          }
          sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows1, &iCols1, &minSize);
          if(sciErr.iErr)
          {
            printError(&sciErr,0);
            return 0;
          }

        //check dimensions
        if(iCols1!=2 || iRows1!=1)
        {
          Scierror(999,"The minSize argument must have dimensions 1*2 ");
          return -1;
        }
          cnt++;

         sciErr = getVarAddressFromPosition(pvApiCtx,cnt,&piAddr);
          if (sciErr.iErr)
          {
            printError(&sciErr, 0);
              return 0;
          }
          sciErr = getMatrixOfDouble(pvApiCtx, piAddr, &iRows1, &iCols1, &maxSize);
          if(sciErr.iErr)
          {
            printError(&sciErr,0);
            return 0;
          }

        //check dimensions
        if(iCols1!=2 || iRows1!=1)
        {
          Scierror(999,"The maxSize argument must have dimensions 1*2 ");
          return -1;
        }
          
          break;

         }


    /* Actual Processing*/
   try{
    if(image.channels()==1)
    {
      image.convertTo(image,CV_8U);
      image.copyTo(image_gray);
      
      equalizeHist( image_gray, image_gray );
      


    }
    else
    {
    //Converting image from rgb to gray scale image.
    image.convertTo(image,CV_8U);
    cvtColor( image, image_gray, CV_BGR2GRAY );
    //equalizing the histrogram of gray scale image
    equalizeHist( image_gray, image_gray );
    }
    


        vector<Rect> found;
        
        //set minSize and maxSize if passed
        if(n==6)
        {
          minX=minSize[0];
          minY=minSize[1];
          
        }
        else if(n==7)
        {
          minX=minSize[0];
          minY=minSize[1];

          maxX=maxSize[0];
          maxY=maxSize[1];



        }

        
        
          int j;
          for(j=0;j<iRows * iCols;j++)
        {
          if(!file_existsindirectory_check(object[j]))
          {
     
            sciprint("Error: the input File -%s  not found!.Please enter correct path!\n",object[j]);
            return 0;

          }
            
            CascadeClassifier s;
            s.load(object[j]);
            found.clear();
            
            if(n==7)
            s.detectMultiScale( image_gray, found, scale, minNeighbors, 0|flags , Size(int(minX),int(minY)),Size(int(maxX),int(maxY)));
            else if(n==6)
            s.detectMultiScale( image_gray, found, scale, minNeighbors, 0|flags , Size(int(minX),int(minY)));
            else
            s.detectMultiScale( image_gray, found, scale, minNeighbors, 0|flags); 
            
            
            

          for( int i = 0; i < found.size(); i++ )
        {    

           Point point1( found[i].x + found[i].width, found[i].y + found[i].height );
           Point point2( found[i].x, found[i].y);
           rectangle(image,found[i],cvScalar(255,100,0),2,16,0);
           

        }

       }
   
    bboxes = (double*)malloc(sizeof(double) * (int)found.size() * 4);

    int total_boxes = (int)found.size();
    
    for(i = 0; i < found.size(); ++i)
    {
      Rect temp = found[i];

      // x coordinate
      bboxes[i + 0 * total_boxes] = temp.x;

      // y coordinate
      bboxes[i + 1 * total_boxes] = temp.y;

      // width
      bboxes[i + 2 * total_boxes] = temp.width;

      // height
      bboxes[i + 3 * total_boxes] = temp.height;
    }


   
      
          
    //sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, tbox, 4, bboxes);

    string tempstring = type2str(image.type());
    char *checker;
    checker = (char *)malloc(tempstring.size() + 1);
    memcpy(checker, tempstring.c_str(), tempstring.size() + 1);
    returnImage(checker,image,1);
    free(checker);

    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, total_boxes, 4, bboxes);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }

    }
       
       catch(cv::Exception& e)
      {
        
        Scierror(999,e.what());
        return 0;


      }

    //Assigning the list as the Output Variable
    AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
    AssignOutputVariable(pvApiCtx, 2) = nbInputArgument(pvApiCtx) + 2;
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx); 
    return 0;

  }
  

  
}
