/*Authors-Nihar Rao
		  Shreyash Sharma

*/

#include <numeric>
#include <iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include <sciprint.h>
#include<string.h>
#include<sys/stat.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/point_cloud.h>
#include <pcl/common/projection_matrix.h>
#include <pcl/point_types.h>
#include <pcl/exceptions.h>
#include <pcl/common/common.h>
#include <pcl/features/integral_image_normal.h>




using namespace std;
extern "C"
{
	 #include "api_scilab.h"
    #include "Scierror.h"
    #include "BOOL.h"
    #include <localization.h>
    #include "sciprint.h"
    


bool files_exist_check( char *name) {
        struct stat buffer;   
        return (stat (name, &buffer) == 0); 
     }  

 int PCL_pcread(char *fname, unsigned long fname_len)
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
    double *points;
    double *rgbValues,*intensityValues;
    int n;
    int width,height;
    int il,z;
    double num;
    double *xLimit;
    double *yLimit;
    double *zLimit;
    double *normalVectors;
    bool isDense;
    pcl::PointXYZRGB minLimit,maxLimit;
    


    //Checking number of input and output arguments (enviromnet variable, min arguments, max arguments)
    CheckInputArgument(pvApiCtx, 1, 1);
    CheckOutputArgument(pvApiCtx, 11, 11);

  
    
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
    //check if file exists
    if(!files_exist_check(pstData[0]))
        {
            
            Scierror(999, "Error: the input  file not found!.Please enter correct path!\n");
            return 0;
        }

     //get string version of file

        string inputFile(pstData[0]);

    /*Processing*/

         
         n=inputFile.length();

         

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB> ());        
        //checking ending 
        if(inputFile.substr(n-3,n-1)=="pcd")
        {

        	

  			if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (pstData[0], *cloud) == -1) // load the file
  			{
    			cout<<"\n ERROR: couldn't load file\n"<<endl;
    			return -1;
  			}



        }
        else if(inputFile.substr(n-3,n-1)=="ply")
        {
        	if (pcl::io::loadPLYFile<pcl::PointXYZRGB>  (pstData[0], *cloud) < 0)  
     		{
     			cout<<"\n ERROR: couldn't load file\n"<<endl;
      			return -1;
    		}


    	}
    	else
    	{

    		cout<<"\n ERROR: the input file should be either a ply or a pcd file!\n"<<endl;
      		return -1;



    	}


    try
      {

        //Assign cloud params
        height=cloud->height;
      	width=cloud->width;
        num=cloud->points.size();
        isDense=cloud->is_dense;

        //Allocate memory for cloud processing
        points=(double *)malloc(sizeof(double)*height*width*3);
        normalVectors=(double *)malloc(sizeof(double)*height*width*3);
        rgbValues=(double *)malloc(sizeof(double)*height*width*3);
        intensityValues=(double *)malloc(sizeof(double)*height*width);
        xLimit=(double *)malloc(sizeof(double)*1*2);
        yLimit=(double *)malloc(sizeof(double)*1*2);
        zLimit=(double *)malloc(sizeof(double)*1*2);

         
         il=0;
        
        pcl::PointCloud<pcl::PointXYZRGB>::iterator it;
        


        //storing values
         for ( it = cloud->points.begin(); it!=cloud->points.end(); ++it) { 
			points[il]=(*it).x;
			points[(height * width) + il]=(*it).y;
			points[(2 * height * width) + il]=(*it).z;

			//RGB
			rgbValues[il]=(*it).r;
			rgbValues[(height * width) + il]=(*it).g;
			rgbValues[(2 * height * width) + il]=(*it).b;
			//intensity
			intensityValues[il]=0.2989 *(*it).r + 0.5870 * (*it).g + 0.1140 * (*it).b;
			
			il++; 
			      	


         }


         
            //////get Limits
            getMinMax3D(*cloud,minLimit,maxLimit);

            //Allocate limits for returning to scilab

            xLimit[0]=minLimit.x;
            xLimit[1]=maxLimit.x;

            yLimit[0]=minLimit.y;
            yLimit[1]=maxLimit.y;

            zLimit[0]=minLimit.z;
            zLimit[1]=maxLimit.z;

            ///Normal computation


      pcl::PointCloud<pcl::PointNormal>::Ptr normals (new pcl::PointCloud<pcl::PointNormal>);
        pcl::IntegralImageNormalEstimation<pcl::PointXYZRGB, pcl::PointNormal> ne;
        ne.setNormalEstimationMethod (ne.AVERAGE_3D_GRADIENT);
        ne.setMaxDepthChangeFactor(0.02f);
        ne.setNormalSmoothingSize(10.0f);
        ne.setInputCloud(cloud);
        //ne.setRadiusSearch (0.03);
        ne.compute(*normals);
       

        //convert cloud to double *
        
	
        pcl::PointCloud<pcl::PointNormal>::iterator ir;
        il=0;
       for ( ir = normals->points.begin(); ir!=normals->points.end(); ++ir) { 
			normalVectors[il]=(*ir).x;
			normalVectors[(height * width) + il]=(*ir).y;
			normalVectors[(2 * height * width) + il]=(*ir).z;

			il++;


		}

      }
      catch(exception& e)
      {
      	Scierror(999,e.what());
      	return 0;


      }   
        





     //Write Output to Scilab



     sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 1,height*width, 3, points);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 2, 1, 1,&num );
        if(sciErr.iErr)
        {
            printError(&sciErr, 0);
            return 0;
        } 
    intErr = createScalarInteger32(pvApiCtx, nbInputArgument(pvApiCtx) + 3,width);
        if(intErr)
        {
            Scierror(999,"Error creating matrix");
            return 0;
        } 
    intErr = createScalarInteger32(pvApiCtx, nbInputArgument(pvApiCtx) + 4,height);
        if(intErr)
        {
            Scierror(999,"Error creating matrix");
            return 0;
        } 
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 5,height*width, 3, rgbValues);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 6,1,2,xLimit);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 7,1,2,yLimit);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 8,1,2,zLimit);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }

    //processing bool for output(is_dense)
    int final;
    if(isDense)
    	final=1;
    else
    	final=0;

    intErr=createScalarBoolean(pvApiCtx, nbInputArgument(pvApiCtx) + 9,final );
    if(intErr)
    {
    	Scierror(999,"error creating booleean output ");
    	return 0;


    }
     sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 10,width,height,intensityValues);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }
    sciErr = createMatrixOfDouble(pvApiCtx, nbInputArgument(pvApiCtx) + 11,height*width, 3, normalVectors);
    if(sciErr.iErr){
      printError(&sciErr, 0);
      return 0;
    }


    for(int i=1;i<=11;i++)
    AssignOutputVariable(pvApiCtx, i) = nbInputArgument(pvApiCtx) + i;

    
    //Returning the Output Variables as arguments to the Scilab environment
    ReturnArguments(pvApiCtx);

 	return 0;
 }




}	


