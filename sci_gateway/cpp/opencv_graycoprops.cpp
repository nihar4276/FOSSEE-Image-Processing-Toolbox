/* Author: Nihar rao & Samiran Roy

/* Usage of the function is exactly similar to matlab function */
/*
 * graycoprops
 *
 * graycoprops in scilab
 * Please refer to :
 * http://www.cse.unsw.edu.au/~icml2002/workshops/MLCV02/MLCV02-Bevk.pdf, p.3.
 */

#include <numeric>
#include <math.h>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;
extern "C" {
#include "api_scilab.h"
#include "Scierror.h"
#include "BOOL.h"
#include <localization.h>
#include "sciprint.h"
#include "../common.h"

double return_contrast(Mat image)

{
  double contrast = 0;

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      contrast = contrast + (pow((i - j), 2) * image.at<double>(i, j));
    }
  }
  return contrast;
}

double return_correlation(Mat image)

{
  double correlation = 0;

  std::vector<int> mg_rows;
  std::vector<int> mg_cols;

  // Meshgrid of row and column indices
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      mg_rows.push_back(j);
      mg_cols.push_back(i);
    }
  }

  // for (int i=0; i<rows.size();i++)
  //  sciprint("%d\n", rows[i]);

  Mat flat_image = image.reshape(1, 1);

  double mean_row = 0;
  double mean_col = 0;
  double std_row = 0;
  double std_col = 0;

  for (int i = 0; i < mg_rows.size(); i++)
    mean_row = mean_row + mg_rows[i] * flat_image.at<double>(i);

  for (int i = 0; i < mg_cols.size(); i++)
    mean_col = mean_col + mg_cols[i] * flat_image.at<double>(i);

  for (int i = 0; i < mg_rows.size(); i++)
    std_row =
        std_row + (pow(mg_rows[i] - mean_row, 2) * flat_image.at<double>(i));

  std_row = sqrt(std_row);

  for (int i = 0; i < mg_cols.size(); i++)
    std_col =
        std_col + (pow(mg_cols[i] - mean_col, 2) * flat_image.at<double>(i));

  std_col = sqrt(std_col);

  for (int i = 0; i < mg_rows.size(); i++)
    correlation =
        correlation + ((mg_rows[i] - mean_row) * (mg_cols[i] - mean_col) *
                       flat_image.at<double>(i));

  double denom = std_col * std_row;
  if (denom != 0) {
    correlation = correlation / denom;
  }

  // sciprint("\n");

  // sciprint("MR: %f",mean_row);
  // sciprint("MC: %f",mean_col);

  // sciprint("SR: %f",std_row);
  // sciprint("SC: %f",std_col);
  return correlation;
}

double return_energy(Mat image)

{
  double energy = 0;

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      energy = energy + pow(image.at<double>(i, j), 2);
    }
  }
  return energy;
}

double return_homogeneity(Mat image)

{
  double homogeneity = 0;

  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      homogeneity = homogeneity + (image.at<double>(i, j) / (1 + abs(i - j)));
    }
  }
  return homogeneity;
}

int opencv_graycoprops(char *fname, unsigned long fname_len) {
  SciErr sciErr;
  int intErr = 0;

  int *piAddr1 = NULL;
  int *piLen = NULL;
  int i,j;
  int argPresence[4]={0};

  int error;
  int iRows,iCols;
  // String holding the second argument
  int iRet = 0;
  char **pstData = NULL;
  vector<Mat> rgb;
  double s;

  // Checking input argument
  CheckInputArgument(pvApiCtx, 1, 2);
  CheckOutputArgument(pvApiCtx, 1, 4);

  //get number of input arguments
  int n=*getNbInputArgument(pvApiCtx);
  // Get input image
  Mat image;
  retrieveImage(image, 1);

  // converting image to float

  image.convertTo(image, CV_64FC1, 1, 0);
  //if only one input argument
 if(n==1)
 {
       if (image.channels() == 1) {
    // Normalizing image
    
    double s = cv::sum(image)[0];
    image = image / s;

          
      double contrast = return_contrast(image);
      intErr =
          createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1, contrast);
      if (intErr) return intErr;

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
      // Returning the Output Variables as arguments to the Scilab environment
      
      
    

    
      double correlation = return_correlation(image);

      intErr = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2,
                                  correlation);
      if (intErr) return intErr;

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 2) = nbInputArgument(pvApiCtx) + 2;
      // Returning the Output Variables as arguments to the Scilab environment
  
     
      double energy = return_energy(image);

      intErr =
          createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 3, energy);
      if (intErr) return intErr;

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 3) = nbInputArgument(pvApiCtx) + 3;
    

      double homogeneity = return_homogeneity(image);

      intErr = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 4,
                                  homogeneity);
      if (intErr) return intErr;

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 4) = nbInputArgument(pvApiCtx) + 4;
      // Returning the Output Variables as arguments to the Scilab environment
      ReturnArguments(pvApiCtx);
      return 0;
  }

  else if (image.channels() == 3) {
    
      
      split(image, rgb);

      double *contrast = (double *)malloc(sizeof(double) * 3);
      

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        contrast[2-i] = return_contrast(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+1, 1, 3,
                                    contrast);

      free(contrast);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx)+1;
      // Returning the Output Variables as arguments to the Scilab environment
      
    
      
      split(image, rgb);

      double *correlation = (double *)malloc(sizeof(double) * 3);
     

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        correlation[2-i] = return_correlation(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+2, 1, 3,
                                    correlation);

      free(correlation);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 2) = nbInputArgument(pvApiCtx)+2;
      // Returning the Output Variables as arguments to the Scilab environment
      
      
    

           split(image, rgb);

      double *energy = (double *)malloc(sizeof(double) * 3);
     

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        energy[2-i] = return_energy(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+3, 1, 3,
                                    energy);

      free(energy);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 3) = nbInputArgument(pvApiCtx)+3;
     

    
            split(image, rgb);

      double *homogeneity = (double *)malloc(sizeof(double) * 3);
      
      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        homogeneity[2-i] = return_homogeneity(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+4, 1, 3,
                                    homogeneity);

      free(homogeneity);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      // Assigning the list as the Output Variable
      AssignOutputVariable(pvApiCtx, 4) = nbInputArgument(pvApiCtx)+4;
      // Returning the Output Variables as arguments to the Scilab environment
      ReturnArguments(pvApiCtx);
      return 0;
    
        
  } else {
    sciprint("Invalid number of channels in the image(must be 1 or 3)\n");
    return 0;
  }



 }

 //2 input arguments

 else
 {

  if (image.channels() == 1) {
    // Normalizing image
    
     s = cv::sum(image)[0];
    image = image / s;

    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr1);

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    pstData= (char**)malloc(sizeof(char*) * iRows * iCols);
    for(i = 0 ; i < iRows * iCols ; i++)
    {
        pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
    }
    //third call to retrieve data
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen,pstData);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    //iterate througt the matrix

 for(j=0;j<iRows * iCols;j++)
  {

    
    if (strcmp(pstData[j], "contrast") == 0) {
      if(argPresence[0])
      {
        Scierror(999,"\n contrast argument already present. pass it only one time!");
        return 0;

      }
      argPresence[0]=1;
      double contrast = return_contrast(image);
      intErr =
          createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + j+1, contrast);
      if (intErr) return intErr;

     
    }

    else if (strcmp(pstData[j], "correlation") == 0) {

      if(argPresence[1])
      {
        Scierror(999,"\n correlation argument already present. pass it only one time!");
        return 0;

      }
      argPresence[1]=1;

      double correlation = return_correlation(image);

      intErr = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + j+1,
                                  correlation);
      if (intErr) return intErr;

    } else if (strcmp(pstData[j], "energy") == 0) {
      if(argPresence[2])
      {
        Scierror(999,"\n energy argument already present. pass it only one time!\n");
        return 0;

      }
      argPresence[2]=1;
      double energy = return_energy(image);

      intErr =
          createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + (j+1), energy);
      if (intErr) return intErr;

    
    }

    else if (strcmp(pstData[j], "homogeneity") == 0) {
      if(argPresence[3])
      {
        Scierror(999,"\n homogeneity argument already present. pass it only one time!");
        return 0;

      }
      argPresence[3]=1;
      double homogeneity = return_homogeneity(image);

      intErr = createScalarDouble(pvApiCtx, nbInputArgument(pvApiCtx) + (j+1),
                                  homogeneity);
      if (intErr) return intErr;

      
    }

    else {
      sciprint("\n Error: Unknown Parameter Name: %s\n", pstData[j]);
       return 0;
    }
  }
  //Assigning output variables
  for(i=0;i<iRows*iCols;i++)
  {
    AssignOutputVariable(pvApiCtx, i+1) = nbInputArgument(pvApiCtx)+i+1;
      


  }
  // Returning the Output Variables as arguments to the Scilab environment
      ReturnArguments(pvApiCtx);
      return 0;

 }

  else if (image.channels() == 3) {
    sciErr = getVarAddressFromPosition(pvApiCtx, 2, &piAddr1);

    if (sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }

    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, NULL, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    piLen = (int*)malloc(sizeof(int) * iRows * iCols);
    //second call to retrieve length of each string
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen, NULL);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    pstData= (char**)malloc(sizeof(char*) * iRows * iCols);
    for(i = 0 ; i < iRows * iCols ; i++)
    {
        pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
    }
    //third call to retrieve data
    sciErr = getMatrixOfString(pvApiCtx, piAddr1, &iRows, &iCols, piLen,pstData);
    if(sciErr.iErr)
    {
        printError(&sciErr, 0);
        return 0;
    }
    //iterate througt the matrix

 for(j=0;j<iRows * iCols;j++)
  {
    if (strcmp(pstData[j], "contrast") == 0) {
     if(argPresence[0])
      {
        Scierror(999,"\n contrast argument already present. pass it only one time!");
        return 0;

      }
      argPresence[0]=1;
      
      split(image, rgb);

      double *contrast = (double *)malloc(sizeof(double) * 3);
      

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        contrast[2-i] = return_contrast(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+j+1, 1, 3,
                                    contrast);

      free(contrast);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

    }

  else if (strcmp(pstData[j], "correlation") == 0) {

      if(argPresence[1])
      {
        Scierror(999,"\n correlation argument already present. pass it only one time!");
        return 0;

      }
      argPresence[1]=1;
      
      split(image, rgb);

      double *correlation = (double *)malloc(sizeof(double) * 3);
     

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        correlation[2-i] = return_correlation(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+j+1, 1, 3,
                                    correlation);

      free(correlation);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      
    }

    else if (strcmp(pstData[j], "energy") == 0) {

      if(argPresence[2])
      {
        Scierror(999,"\n energy argument already present. pass it only one time!");
        return 0;

      }
      argPresence[2]=1;
      
      split(image, rgb);

      double *energy = (double *)malloc(sizeof(double) * 3);
      

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        energy[2-i] = return_energy(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+j+1, 1, 3,
                                    energy);

      free(energy);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }
    }


    else if (strcmp(pstData[j], "homogeneity") == 0) {

      if(argPresence[3])
      {
        Scierror(999,"\n contrast argument already present. pass it only one time!");
        return 0;

      }
      argPresence[3]=1;
     
      split(image, rgb);

      double *homogeneity = (double *)malloc(sizeof(double) * 3);
      

      for (int i = 0; i < 3; i++) {
        s = cv::sum(rgb[i])[0];
        rgb[i] = rgb[i] / s;
        homogeneity[2-i] = return_homogeneity(rgb[i]);
      }

      sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx)+j+1, 1, 3,
                                    homogeneity);

      free(homogeneity);

      if (sciErr.iErr) {
        printError(&sciErr, 0);
        return 0;
      }

      
    }
        else {
      sciprint("\nUnknown Parameter Name: %s\n", pstData[j]);
       return 0;
    }

  }
  //Assigning output variables
  for(i=0;i<iRows*iCols;i++)
  {
    AssignOutputVariable(pvApiCtx, i+1) = nbInputArgument(pvApiCtx)+i+1;
      


  }
   // Returning the Output Variables as arguments to the Scilab environment
      ReturnArguments(pvApiCtx);
      return 0;

  } else {
    sciprint("Invalid number of channels in the image(must be 1 or 3)\n");
    return 0;
  }

 }
  
}
/* ==================================================================== */
}

