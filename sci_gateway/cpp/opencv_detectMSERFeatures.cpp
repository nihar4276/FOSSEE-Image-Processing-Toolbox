/********************************************************************************************************************************************************************************************************
*	Author:	Umang Agrawal and nihar rao																					        *
*	Code:	detectMSERFeatures.cpp																				        *
*	Function Format:	[ list_pixels, ......] = detectMSERFeatures( image, Optional Arguments........)											        *
*					Input Arguments:	1. Image (Grayscale or RGB)													        *
*								2. ThresholdDelta	Value: 	(0:100] Expressed in Percentage										*
*								3. RegionAreaRange	Value:	[ Min_Area , Max_Area ]											*
*								4. MaxAreaVariation	Value:	Scalar Double typical range from 0.25 - 4								*
*								5. ROI			Value: 	[ x_cord , y_cord , width , height ] 									*
*																									*
*					Output Argument:	1. List Of Pixels stating the Locus of all features detected										*
*								2. Count 																*
*								3. Location: Centroid of each Locus													*
*								4. Axes: Major and Minor axis length of ellipse												*
*								5. Orientation: Tilt of the elliptical fit												*
*																									*
********************************************************************************************************************************************************************************************************/


#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

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

	int opencv_detectMSERFeatures(char *fname, unsigned long fname_len)
	{
		//Various Declarations
		//Error Variables		
		SciErr sciErr;
		int sca_read;

		//Mat containers for image
		Mat image;
		Mat cropped;

		//Address of Various Arguments
		int *piAddr = NULL;
		int *piAddr2 = NULL;
		int *piAddr3 = NULL;

		int inp_params, out_params;							//Count of Parameters
		double arg_val;									//Memory for Scalar Argument Value
		int Rows, Cols;									//Rows and Columns for Matrix Argument Value
		double *roi_arg = NULL;								//Memory for Matrix Argument Value
		int *pilen = NULL;								//For String Matrix Reading: Length of String
		char **arg = NULL;								//For String Matrix Reading: String
		int count_area = 0, count_tres = 0, count_var = 0, count_roi = 0;		//Count of all the optional Arguments
		double x = 0, y = 0, width = 0, height = 0;					//Initials of all Cropped Varaibles

		int i,j;									//Iterator

		int delta = 5, min_area = 60, max_area = 14400, max_evolution = 200, edge_blur_size = 5;		//Arguments of MSER function with default values
		double max_variation = 0.25, min_diversity = 0.2, area_threshold = 1.01, min_margin = 0.003;		//Arguments of MSER function with default values

		double *pixellist = NULL;							//Output Argument Pixellist
		int count[1] ;									//Output Argument Count
		double *location = NULL;							//Output Argument Location
		double *axes = NULL;								//Output Argument Axes
		double *orientation = NULL;							//Output Argument Orientation

		vector< vector<Point> > mser_points;						//3D vector for storing the locus of each detected feature
		vector< RotatedRect > regions;	
		vector<Rect> bboxes;						//RotatedRect vector for storing each region associated with a feature

		CheckInputArgument(pvApiCtx, 1, 9);						//Check on Number of Input Arguments
		CheckOutputArgument(pvApiCtx, 1, 5);						//Check on Number of Output Arguments

		//Read Image
		retrieveImage(image, 1);

		
		//Getting Number of Input Arguments
		inp_params = *getNbInputArgument(pvApiCtx);

		//Based on the number of Input Arguments, alter the arguments of the MSER funtion.
		for(i=2; i<=inp_params; i++)
		{
			if( inp_params == 2 || inp_params == 4 || inp_params == 6 || inp_params == 8)
			{
				Scierror(999,"Either Argument Name or its Value missing\n");
				return 0;
			}
			//Reading the Name of the Argument
			sciErr = getVarAddressFromPosition(pvApiCtx, i, &piAddr2);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			//Check for Argument type
			if( !isStringType(pvApiCtx, piAddr2))
			{
				Scierror(999, "%s: Wrong type of argument #%d. A string is expected.\n", fname, 1);
				return 0;
			}
			//Matrix of Stings
			sciErr = getMatrixOfString(pvApiCtx, piAddr2, &Rows, &Cols, NULL, NULL);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			pilen = (int*)malloc(sizeof(int) * Rows * Cols);
			//second call to retrieve the length of the string
			sciErr = getMatrixOfString(pvApiCtx, piAddr2, &Rows, &Cols, pilen, NULL);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				free(pilen);
				return 0;
			}
			arg = (char**)malloc(sizeof(char*) * Rows * Cols);
			for(int j=0;j< Rows * Cols; j++)
			{
				arg[j] = (char*)malloc(sizeof(char) * (pilen[j] + 1));
			}

			//third call to retrieve data
			sciErr = getMatrixOfString(pvApiCtx, piAddr2, &Rows, &Cols, pilen, arg);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				free(pilen);
				free(arg);
				return 0;
			}

			if(strcmp(arg[0],"ThresholdDelta") == 0)
			{
				if(count_tres == 0)
				{
					sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr3);
					if(sciErr.iErr)
					{
					printError(&sciErr, 0);
					return 0;
					}
					//Checking the type of value
					if( !isDoubleType(pvApiCtx, piAddr3))
					{
						Scierror(999,"Not a valid type of value.\n");
						return 0;
					}
					//Reading the Value of the argument
					sca_read = getScalarDouble(pvApiCtx, piAddr3, &arg_val);
					if(sca_read)
					{
						Scierror(999,"Not a valid value.\n");
						return 0;
					}
					//Check for valid range
					if(arg_val <= 0 && arg_val > 100)
					{
					Scierror(999,"Not a valid range.Should be between 0 and 100.\n");
					return 0;
					}
					delta = arg_val;
					i++;
					count_tres += 1;
				}
				else
				{
					Scierror(999,"ThresholdDelta has been specified twice.Check the Arguments\n");
					return 0;
				}
			}
			else if(strcmp(arg[0],"RegionAreaRange") == 0)
			{
				if(count_area == 0)
				{
					sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr3);
					if(sciErr.iErr)
					{
						printError(&sciErr, 0);
						return 0;
					}
					//Checking the type of argument
					if( !(isDoubleType(pvApiCtx, piAddr3) || isIntegerType(pvApiCtx, piAddr3)) )
					{
						Scierror(999,"Not a valid type of value.\n");
						return 0;					
					}
					//Reading the Value of the argument
					sciErr = getMatrixOfDouble(pvApiCtx, piAddr3, &Rows, &Cols, &roi_arg);
					if(sciErr.iErr)
					{
						printError(&sciErr, 0);
						return 0;
					}
					if( Rows*Cols != 2 )
					{
						Scierror(999,"Only 2 values are expected.Neither less nor more\n");
						return 0;
					} 
					if( roi_arg[0] >= roi_arg[1] )
					{
						Scierror(999,"Max Area should be greater than Min Area\n");
						return 0;
					}	
					//Assigning the elements of the list to their proper function				
					min_area = roi_arg[0];
					max_area = roi_arg[1];
					i++;
					count_area += 1;
				}
				else
				{
				Scierror(999,"RegionAreaRange has been specified twice.Check the Arguments\n");
                                return 0;
				}
			}
			else if(strcmp(arg[0],"MaxAreaVariation") == 0)
			{
				if(count_var == 0)
				{
					sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr3);
                                        if(sciErr.iErr)
                                        {
                                        printError(&sciErr, 0);
                                        return 0;
                                        }
                                        //Checking the type of value
                                        if( !isDoubleType(pvApiCtx, piAddr3))
                                        {
                                                Scierror(999,"Not a valid type of value.\n");
                                                return 0;
                                        }
                                        //Reading the Value of the argument
                                        sca_read = getScalarDouble(pvApiCtx, piAddr3, &arg_val);
                                        if(sca_read)
                                        {
                                                Scierror(999,"Not a valid value.\n");
                                                return 0;
                                     	}
                                        max_variation = arg_val;
                                  	i++;
					count_var += 1;
				}
				else
				{
					Scierror(999,"MaxAreaVariation has been specified twice.Check the Arguments\n");
                                        return 0;
				}
			}
			else if(strcmp(arg[0],"ROI") == 0)
			{
				if(count_roi == 0)
				{
					sciErr = getVarAddressFromPosition(pvApiCtx, i+1, &piAddr3);
					if(sciErr.iErr)
					{
						printError(&sciErr, 0);
						return 0;
					}
					//Checking the type of argument
					if( !(isDoubleType(pvApiCtx, piAddr3) || isIntegerType(pvApiCtx, piAddr3)) )
					{
						Scierror(999,"Not a valid type of value.\n");
						return 0;
					}
					//Reading the Value of the argument
					sciErr = getMatrixOfDouble(pvApiCtx, piAddr3, &Rows, &Cols, &roi_arg);
					if(sciErr.iErr)
					{
					printError(&sciErr, 0);
					return 0;
					}
					if( Rows*Cols != 4 )
					{
						Scierror(999,"Expected 4 arguments in format [x,y,width,height]\n");
						return 0;
					}
					//Assigning the elements of the list to their proper function
					x = roi_arg[0];
					y = roi_arg[1];
					width = roi_arg[2];
					height = roi_arg[3];
					if(x>=image.cols || y>=image.rows || x<0 || y<0)
   			 		{
        					sciprint("Invalid x or y value\n");
        					return 0;
    					}
    					if(width<=0 || height<=0 || x+width > image.cols || y+height > image.rows)
    					{
        					sciprint("Invalid width or height value\n");
        					return 0;
    					}
					Rect myROI(x, y, width, height);
					Mat croppedRef(image, myROI);
					croppedRef.copyTo(cropped);
					i++;						//Incrementing iterator to count for the value argument read
					count_roi += 1;					//Indicating ROI has been called once
				}
				else
				{
					Scierror(999,"ROI has been specified twice.Check the Arguments\n");
                                        return 0;
				}
			}
			else
			{
				Scierror(999,"Invalid Argument\n");
				return 0;
			}
		}
        try
        {
        	image.convertTo(image,CV_8UC3);	
		//Creating an MSER class Object with specified conditions

		 Ptr<MSER> img_ms = cv::
		 MSER::create(delta, min_area, max_area, max_variation, min_diversity, max_evolution, area_threshold, min_margin, edge_blur_size);
		
		//Checking if have to operate on original image or cropped one
		// 1st Argument: Image on which MSER features has to be detected
		// 2nd Argument: Locus of all the points detected
		// 3rd Argument: Mask of empty Mat container
		if(count_roi == 0)
			img_ms->detectRegions( image, mser_points,bboxes);
		else
			img_ms->detectRegions( cropped, mser_points,bboxes);

		// Extracting Regions from the mser_points locus and approximating them to an elliptic fit
		for(i=0; i<mser_points.size(); i++)
			regions.push_back(fitEllipse(mser_points[i]));

		//Memory Allocation for all the output parameters		
		location = (double *)malloc(sizeof(double) * mser_points.size() * 2);
		axes = (double *)malloc(sizeof(double) * mser_points.size() * 2);
		orientation = (double *)malloc(sizeof(double) * mser_points.size());

		//Output Arguments: Pixel_list, Count, Location, Axes, Orientation		
		count[0] = mser_points.size();								//Count
		for(i=0; i<mser_points.size(); i++)
		{
			location[i] = regions[i].center.x + x;						//Location X co-ordinate
			location[mser_points.size() + i] = regions[i].center.y + y;				//Location Y co-ordinate
			if( regions[i].size.width >= regions[i].size.height )
			{
				axes[i] = regions[i].size.width;					//Axis: Major Axis of Ellipse
				axes[mser_points.size() + i] = regions[i].size.height;			//Axis: Minor Axis of Ellipse
			}
			else
			{
				axes[i] = regions[i].size.height;					//Axis: Major Axis of Ellipse
				axes[mser_points.size() + i] = regions[i].size.width;			//Axis: Minor Axis of Ellipse
			}
			orientation[i] = regions[i].angle;						//Orientation
		}

		//Reading the number of output Arguments user demands
		
		//Assigning Pixel_List
		
		out_params = *getNbOutputArgument(pvApiCtx);
		if( out_params >= 1 )
		{
			sciErr = createList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, mser_points.size(), &piAddr);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			for(i = 0; i<mser_points.size(); i++)
			{
				pixellist = (double *)malloc(sizeof(double) * mser_points[i].size() * 2);
				for( j=0; j<mser_points[i].size(); j++)
				{
					pixellist[j] = mser_points[i][j].x + x;
					pixellist[mser_points[i].size() + j] = mser_points[i][j].y + y;
				}
				sciErr = createMatrixOfDoubleInList(pvApiCtx, nbInputArgument(pvApiCtx) + 1, piAddr, i+1, mser_points[i].size(), 2, pixellist);
				if(sciErr.iErr)
				{
					printError(&sciErr, 0);
					return 0;
				}
				free(pixellist);
			}
			AssignOutputVariable(pvApiCtx, 1) = nbInputArgument(pvApiCtx) + 1;
		}
		}
		catch(cv::Exception& e)
  		{
    		const char* err=e.what();
    		sciprint("\n%s\n",err);


  		}
		//Assigning Count
		if( out_params >= 2 )
		{
			sciErr = createMatrixOfInteger32(pvApiCtx, nbInputArgument(pvApiCtx) + 2, 1, 1, count);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			AssignOutputVariable(pvApiCtx, 2) = nbInputArgument(pvApiCtx) + 2;
		}
	
		//Assigning Location
		if( out_params >= 3 )
		{
			sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 3, mser_points.size(), 2, location);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			AssignOutputVariable(pvApiCtx, 3) = nbInputArgument(pvApiCtx) + 3;
		}

		//Assigning Axes
		if( out_params >= 4 )
		{
			sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 4, mser_points.size(), 2, axes);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			AssignOutputVariable(pvApiCtx, 4) = nbInputArgument(pvApiCtx) + 4;
		}

		//Assigning Orientation
		if( out_params == 5 )
		{
			sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 5, mser_points.size(), 1, orientation);
			if(sciErr.iErr)
			{
				printError(&sciErr, 0);
				return 0;
			}
			AssignOutputVariable(pvApiCtx, 5) = nbInputArgument(pvApiCtx) + 5;
		}

		//Releasing all the memory Captured
		free(location);
		free(axes);
		free(orientation);

		//Returning the Output Arguments
		ReturnArguments(pvApiCtx);
		return 0;
	}
}