// This file is released under the 3-clause BSD license. See COPYING-BSD.


mode(-1)
lines(0)

toolbox_title = "FOSSEE_Image_Processing_Toolbox";

Build_64Bits = %t;


path_builder = get_absolute_file_path('builder_gateway_cpp.sce');
Names = [	
//            "raw_dctmtx", "dctmtx";
//            "raw_multithresh", "multithresh";
//            "raw_applycform", "opencv_applycform";
            "raw_arrowedline", "opencv_arrowedline";
            "raw_blur", "opencv_blur";
            "raw_boundingRect", "opencv_boundingRect";
////            "raw_bwconvhull", "opencv_bwconvhull";
////            "raw_bwdistgeodesic", "opencv_bwdistgeodesic";
////            "raw_bwlookup", "opencv_bwlookup";
////            "raw_canny", "opencv_canny";
//           "raw_circle", "opencv_circle";
////            "raw_clipline", "opencv_clipline";
////            "raw_convexhull", "opencv_convexhull";
////            "raw_convmtx2", "opencv_convmtx2";
////            "raw_copymakeborder", "opencv_copymakeborder";
////            "raw_corner", "opencv_corner";
////            "raw_cornerEigenValsAndVecs", "opencv_cornerEigenValsAndVecs";
////            "raw_cornerHarris", "opencv_cornerHarris";
////            "raw_cornerMinEigenVal", "opencv_cornerMinEigenVal";
//        "raw_cvtColor", "opencv_cvtColor";
////            "raw_demosaic", "opencv_demosaic";
//            "raw_dilate", "opencv_dilate";
////            "raw_ellipse", "opencv_ellipse";
////            "raw_ellipse2poly", "opencv_ellipse2poly";
//            
////            "raw_fftshift", "opencv_fftshift";
////            "raw_fillconvexpoly", "opencv_fillconvexpoly";
////            "raw_filter2D", "opencv_filter2D";
////            "raw_findContours", "opencv_findContours";
////            "raw_fsamp2", "opencv_fsamp2";

////            "raw_gabor", "opencv_gabor";
////            "raw_gaussianblur", "opencv_gaussianblur";
////            "raw_getStructuringElement", "opencv_getStructuringElement";
////            "getTextSize", "opencv_getTextSize";
////            "raw_getgaussiankernel", "opencv_getgaussiankernel";
////            "raw_getrectsubpix", "opencv_getrectsubpix";
////            "raw_getrotationmatrix2D", "opencv_getrotationmatrix2D";
////            "raw_goodfeaturestotrack", "opencv_goodfeaturestotrack";

////            "raw_houghcircles", "opencv_houghcircles";
////            "raw_houghlines", "opencv_houghlines";
////            "raw_houghlinesp", "opencv_houghlinesp";
////            "raw_ifftshift", "opencv_ifftshift";
////            "raw_im2double", "opencv_im2double";
////            "raw_imabsdiff", "opencv_imabsdiff";
////            "raw_imadd", "opencv_imadd";
////            "raw_imattributes", "opencv_imattributes";
////            "raw_imboxfilt3", "opencv_imboxfilt3";
////            "raw_imcomplement", "opencv_imcomplement";
////            "raw_imcontour", "opencv_imcontour";
////            "raw_imcontrast", "opencv_imcontrast";
//            "raw_imcrop", "opencv_imcrop";
////            "raw_imdivide", "opencv_imdivide";
////            "raw_imextendedmax", "opencv_imextendedmax";
////            "raw_imextendedmin", "opencv_imextendedmin";
////            "raw_imfill", "opencv_imfill";
////            "raw_imfindcircles", "opencv_imfindcircles";
////            "raw_imfuse", "opencv_imfuse";
////            "raw_imgaborfilt", "opencv_imgaborfilt";
////            "raw_imgaussfilt3", "opencv_imgaussfilt3";
////            "raw_imguidedfilter", "opencv_imguidedfilter";
////            "raw_imhmax", "opencv_imhmax";
////            "raw_imhmin", "opencv_imhmin";
////            "raw_imimposemin", "opencv_imimposemin";
////            "raw_imlincomb", "opencv_imlincomb";
////            "raw_immultiply", "opencv_immultiply";
//            "raw_impixel", "opencv_impixel";
////            "raw_impyramid", "opencv_impyramid";
           "raw_imread", "opencv_imread";
////            "raw_imrect", "opencv_imrect";
//            "raw_imresize", "opencv_imresize";
//            "raw_imsharpen", "opencv_imsharpen";
////            "raw_imshowpair", "opencv_imshowpair";
////            "raw_imsubtract", "opencv_imsubtract";
////            "raw_imwarp", "opencv_imwarp";
//            "raw_imwrite", "opencv_imwrite";
////            "raw_ind2gray", "opencv_ind2gray";
////            "raw_ind2rgb", "opencv_ind2rgb";
////            "raw_lab2double", "opencv_lab2double";
////            "raw_lab2rgb", "opencv_lab2rgb";
////            "raw_lab2uint16", "opencv_lab2uint16";
////            "raw_lab2uint8", "opencv_lab2uint8";
////            "raw_lab2xyz", "opencv_lab2xyz";
////            "raw_laplacian", "opencv_laplacian";
////            "raw_line", "opencv_line";
//              

//           "raw_medianblur", "opencv_medianblur";
////            "raw_montage", "opencv_montage";
////            "raw_morphologyEx", "opencv_morphologyEx";
////            "raw_ntsc2rgb", "opencv_ntsc2rgb";
////            "raw_puttext", "opencv_puttext";
////            "raw_pyrDown", "opencv_pyrDown";
////            "raw_pyrUp", "opencv_pyrUp";
////            "raw_rectangle", "opencv_rectangle";
////            "raw_regionfill", "opencv_regionfill";
////            "raw_rgb2lab", "opencv_rgb2lab";
////            "raw_rgb2ntsc", "opencv_rgb2ntsc";
            "raw_rgb2xyz", "opencv_rgb2xyz";
////            "raw_roifill", "opencv_roifill";
////            "raw_roipoly", "opencv_roipoly";
////            "raw_scharr", "opencv_scharr";
////            "raw_sepFilter2D", "opencv_sepFilter2D";
////           "raw_sobel", "opencv_sobel";
////            "raw_ssim", "opencv_ssim";
////            "raw_threshold", "opencv_threshold";
////            "raw_undistort", "opencv_undistort";
////            "raw_viscircles", "opencv_viscircles";
////            "raw_watershed", "opencv_watershed";
////            "raw_whitepoint", "opencv_whitepoint";
////            "raw_wiener2", "opencv_wiener2";
////            "raw_xyz2double", "opencv_xyz2double";
////            "raw_xyz2lab", "opencv_xyz2lab";
////            "raw_xyz2rgb", "opencv_xyz2rgb";
////            "raw_xyz2uint16", "opencv_xyz2uint16";
//                "raw_iminpaint.cpp", "opencv_iminpaint";
//                "raw_roiFreeHand.cpp","opencv_roiFreeHand.cpp"

//			"raw_deconvlucy", "opencv_deconvlucy";
////			"imhistmatch", "opencv_imhistmatch";
////			"graycoprops", "opencv_graycoprops";
////			"graydiffweight", "opencv_graydiffweight";
////			"decorrstretch", "opencv_decorrstretch";
////			"adaptf", "opencv_adapthisteq";
////			"affine2d", "opencv_affine2d";


////			"approxpolyDP","approxpolyDP";
////			"arclenght","arclenght";
////			"bilateralfilter","bilateralfilter";
////			"borderInterpolate","borderInterpolate";
////			"boxfilter","boxfilter";
////			"contourarea","contourarea";
////			"boxfilter","boxfilter";
//			"raw_fitellipse","opencv_fitellipse";
////			"getkerneltype","getkerneltype";
////			"histeq","histeq";
//			"raw_imrotate","opencv_imrotate";
////			"mean1","mean1";
////			"minAreaRect","minAreaRect";
////			"minimumenclosingcirlce","minimumenclosingcirlce";
////			"pyrMeanShiftFiltering","pyrMeanShiftFiltering";
//			"raw_rgb2gray","opencv_rgb2gray";
////			"warpaffine","warpaffine";
//	                "raw_detectMinEigenFeatures","opencv_detectMinEigenFeatures";
//                       "raw_correctMatches","opencv_correctMatches";
//			"raw_findHomography","opencv_findHomography";
//			"raw_matMulDeriv","opencv_matMulDeriv";
//                        "raw_imageSet","opencv_imageSet";
//			"raw_bagOfFeatures","opencv_bagOfFeatures";
//                        "raw_trainImageCategoryClassifier","opencv_trainImageCategoryClassifier";
//                        "raw_trainSVMClassifier","opencv_trainSVMClassifier";
//			"raw_predictSVM","opencv_predictSVM";
//			"raw_trainSVMSGDClassifier","opencv_trainSVMSGDClassifier";
//                        "raw_predictSVMSGD","opencv_predictSVMSGD";
//                        "raw_getParamsSVM","opencv_getParamsSVM";
//			"raw_getParamsSVMSGD","opencv_getParamsSVMSGD";
//			"raw_trainBoostClassifier","opencv_trainBoostClassifier";
//			"raw_predictBoost","opencv_predictBoost";
//                        "raw_trainEMClassifier","opencv_trainEMClassifier";
//			"raw_CascadeObjectDetector","opencv_CascadeObjectDetector";
//			"ocv_detectBRISKFeatures","opencv_detectBRISKFeatures";
//			"raw_detectMSERFeatures","opencv_detectMSERFeatures";
//                        "raw_extractFeatures","opencv_extractFeatures";
//			"raw_detectSURFFeatures","opencv_detectSURFFeatures"
//    			"raw_drawMatch","opencv_drawMatch";
//                        "raw_matchFeatures","opencv_matchFeatures";
//			"ocv_detectFASTFeatures","opencv_detectFASTFeatures";
//			"ocv_detectHarrisFeatures","opencv_detectHarrisFeatures";
//			"raw_peopleDetector","opencv_peopleDetector";
//			"raw_rectangle","opencv_rectangle";
//			"raw_detectKAZEFeatures","opencv_detectKAZEFeatures";
//                       "raw_detectGFTTFeatures","opencv_detectGFTTFeatures";
//			"raw_estimateFundamentalMat","opencv_estimateFundamentalMat";
//			"raw_undistortPoints","opencv_undistortPoints";
//			"raw_rectifyStereoImages","opencv_rectifyStereoImages";
//			"raw_estimateNewCameraMatrix", "opencv_estimateNewCameraMatrix";
//			"raw_stereoCalibrate","opencv_stereoCalibrate";
//			"raw_detectCheckerboardCorner","opencv_detectCheckerboardCorner";
//			"raw_genCheckerboardPoints","opencv_genCheckerboardPoints";
//			"raw_undistortImage","opencv_undistortImage";
//			"raw_disparity","opencv_disparity";
//                        "raw_indexImages","opencv_indexImages";
//			"raw_lab2double","opencv_lab2double";
//                        "raw_fitellipse","opencv_fitellipse";
//			"raw_graycoprops","opencv_graycoprops";
//			"raw_integralKernel","opencv_integralKernel";
//			"raw_pcread","PCL_pcread";
			

			
		];

Files = [
//            "dctmtx.cpp",

//            "multithresh.cpp",
//            "opencv_applycform.cpp",
//            "opencv_arrowedline.cpp",
//            "opencv_blur.cpp",
////            "opencv_boundingRect.cpp",
////            "opencv_bwconvhull.cpp",
////            "opencv_bwdistgeodesic.cpp",
////            "opencv_bwlookup.cpp",
////            "opencv_canny.cpp",
//            "opencv_circle.cpp",
////            "opencv_clipline.cpp",
////            "opencv_convexhull.cpp",
////            "opencv_convmtx2.cpp",
////            "opencv_copymakeborder.cpp",
////            "opencv_corner.cpp",
////            "opencv_cornerEigenValsAndVecs.cpp",
////            "opencv_cornerHarris.cpp",
////            "opencv_cornerMinEigenVal.cpp",
//           "opencv_cvtColor.cpp",
////            "opencv_demosaic.cpp",
//            "opencv_dilate.cpp",
//            "opencv_ellipse.cpp",
////            "opencv_ellipse2poly.cpp",
///           "opencv_erode.cpp",
////            "opencv_fftshift.cpp",
////            "opencv_fillconvexpoly.cpp",
////            "opencv_filter2D.cpp",
////            "opencv_findContours.cpp",
////            "opencv_fsamp2.cpp",

////            "opencv_gabor.cpp",
////            "opencv_gaussianblur.cpp",
////            "opencv_getStructuringElement.cpp",
////            "opencv_getTextSize.cpp",
////            "opencv_getgaussiankernel.cpp",
////            "opencv_getrectsubpix.cpp",
////            "opencv_getrotationmatrix2D.cpp",
////            "opencv_goodfeaturestotrack.cpp",

////            "opencv_houghcircles.cpp",
////            "opencv_houghlines.cpp",
////            "opencv_houghlinesp.cpp",
////            "opencv_ifftshift.cpp",
////            "opencv_im2double.cpp",
////            "opencv_imabsdiff.cpp",
////            "opencv_imadd.cpp",
////            "opencv_imattributes.cpp",
////            "opencv_imboxfilt3.cpp",
////            "opencv_imcomplement.cpp",
////            "opencv_imcontour.cpp",
////            "opencv_imcontrast.cpp",
//            "opencv_imcrop.cpp",
////            "opencv_imdivide.cpp",
////            "opencv_imextendedmax.cpp",
////            "opencv_imextendedmin.cpp",
////            "opencv_imfill.cpp",
////            "opencv_imfindcircles.cpp",
////            "opencv_imfuse.cpp",
////            "opencv_imgaborfilt.cpp",
////            "opencv_imgaussfilt3.cpp",
////            "opencv_imguidedfilter.cpp",
////            "opencv_imhmax.cpp",
////            "opencv_imhmin.cpp",
////            "opencv_imimposemin.cpp",
////            "opencv_imlincomb.cpp",
////            "opencv_immultiply.cpp",
//            "opencv_impixel.cpp",
////            "opencv_impyramid.cpp",
            "opencv_imread.cpp",
////            "opencv_imrect.cpp",
//            "opencv_imresize.cpp",
//            "opencv_imsharpen.cpp",
////            "opencv_imshowpair.cpp",
////            "opencv_imsubtract.cpp",
////            "opencv_imwarp.cpp",
//            "opencv_imwrite.cpp",
////            "opencv_ind2gray.cpp",
////            "opencv_ind2rgb.cpp",
////            "opencv_lab2double.cpp",
////            "opencv_lab2rgb.cpp",
////            "opencv_lab2uint16.cpp",
////            "opencv_lab2uint8.cpp",
////            "opencv_lab2xyz.cpp",
////            "opencv_laplacian.cpp",
////            "opencv_line.cpp",
//                "opencv_roiFreeHand.cpp",

//           "opencv_medianblur.cpp",
////            "opencv_montage.cpp",
////            "opencv_morphologyEx.cpp",
////            "opencv_ntsc2rgb.cpp",
////            "opencv_puttext.cpp",
////            "opencv_pyrDown.cpp",
////            "opencv_pyrUp.cpp",
////            "opencv_rectangle.cpp",
////            "opencv_regionfill.cpp",
////            "opencv_rgb2lab.cpp",
////            "opencv_rgb2ntsc.cpp",
           "opencv_rgb2xyz.cpp",
////            "opencv_roifill.cpp",
////            "opencv_roipoly.cpp",
////            "opencv_scharr.cpp",
////            "opencv_sepFilter2D.cpp",
////            "opencv_sobel.cpp",
////            "opencv_ssim.cpp",
////            "opencv_threshold.cpp",
////            "opencv_undistort.cpp",
////            "opencv_viscircles.cpp",
////            "opencv_watershed.cpp",
////            "opencv_whitepoint.cpp",
////            "opencv_wiener2.cpp",
////            "opencv_xyz2double.cpp",
////            "opencv_xyz2lab.cpp",
////            "opencv_xyz2rgb.cpp",
////            "opencv_xyz2uint16.cpp",


//	    	"opencv_deconvlucy.cpp",
////			"opencv_integralImage.cpp",
////			"opencv_imhistmatch.cpp",
////			"opencv_graycoprops.cpp",
////			"opencv_graydiffweight.cpp",
////			"opencv_decorrstretch.cpp",
////			"opencv_adapthisteq.cpp",
////			"opencv_affine2d.cpp",

//			"rgb2gray.cpp",
////			"warpaffine.cpp",
////			"opencv_pyrMeanShiftFiltering.cpp",
////			"opencv_minimumenclosingcirlce.cpp",
////			"opencv_minAreaRect.cpp",
////			"opencv_mean1.cpp",
//			"opencv_imrotate.cpp",
////			"opencv_getkerneltype.cpp",
//			"opencv_fitellipse.cpp",
////			"opencv_contourarea.cpp",
////			"opencv_boxfilter.cpp",
////			"opencv_borderInterpolate.cpp",
////			"opencv_bilateralfilter.cpp",
////			"opencv_arclength.cpp",
////			"opencv_approxpolyDP.cpp",
////			"opencv_histeq.cpp",
//                       "opencv_detectMinEigenFeatures.cpp",
                        "opencv_correctMatches.cpp",
                        "opencv_findHomography.cpp",
			 "opencv_matMulDeriv.cpp",
                         "opencv_imageSet.cpp",
			 "opencv_bagOfFeatures.cpp",
			"opencv_trainImageCategoryClassifier.cpp",
			"opencv_trainSVMClassifier.cpp",
                        "opencv_predictSVM.cpp",
                        "opencv_trainSVMSGDClassifier.cpp",
			"opencv_predictSVMSGD.cpp",
                        "opencv_getParamsSVM.cpp",
			"opencv_getParamsSVMSGD.cpp",
			"opencv_trainBoostClassifier.cpp",
			"opencv_predictBoost.cpp",
                         "opencv_trainEMClassifier.cpp",
                        "opencv_CascadeObjectDetector.cpp",
			"opencv_detectBRISKFeatures.cpp",
			"opencv_detectMSERFeatures.cpp",
			"opencv_extractFeatures.cpp",
			"opencv_detectSURFFeatures.cpp",
                        "opencv_drawMatch.cpp",
			"opencv_matchFeatures.cpp",
			"opencv_detectFASTFeatures.cpp",
			"opencv_detectHarrisFeatures.cpp",
			"opencv_peopleDetector.cpp",
			"opencv_rectangle.cpp",
                       "opencv_detectKAZEFeatures.cpp",
			"opencv_detectGFTTFeatures.cpp",
			"opencv_estimateFundamentalMatrix.cpp",
			"opencv_undistortPoints.cpp",
			"opencv_rectifyStereoImages.cpp",
//			"opencv_estimateNewCameraMatrix.cpp",
			"opencv_stereoCalibrate.cpp",
			 "opencv_detectCheckerboardCorner.cpp",
			"opencv_genCheckerboardPoints.cpp",
			"opencv_undistortImage.cpp",
			"opencv_disparity.cpp",
                     "opencv_indexImages.cpp",
			"opencv_lab2double.cpp",
			"opencv_fitellipse.cpp",
			"opencv_graycoprops.cpp",
			"opencv_integralKernel.cpp",
			"PCL_pcread.cpp"
			"opencv_bundleAdjustment.cpp"
                        "opencv_iminpaint.cpp"



		];
		
	//copyfile("/home/fossee/Desktop/FOSSEE_Image_Processing_Toolbox/sci_gateway/cpp/common.h",TMPDIR);
    //copyfile("/home/fossee/Desktop/FOSSEE_Image_Processing_Toolbox/sci_gateway/cpp/common.cpp",TMPDIR);
    
    //[a, opt] = getversion();
    //Version = opt(2);
    
    //if getos()=="Windows" then
//	third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
//	lib_base_dir = third_dir + filesep() + 'windows' + filesep() + 'lib' + filesep() + Version + filesep();
//	inc_base_dir = third_dir + filesep() + 'windows' + filesep() + 'include' + filesep() + 'coin';
//    C_Flags=['-D__USE_DEPRECATED_STACK_FUNCTIONS__ -w -I '+path_builder+' '+ '-I '+inc_base_dir+' ']
//    Linker_Flag  = [lib_base_dir+"libClp.lib "+lib_base_dir+"libCgl.lib "+lib_base_dir+"libOsi.lib "+lib_base_dir+"libOsiClp.lib "+lib_base_dir+"libCoinUtils.lib "+lib_base_dir+"libSymphony.lib "+lib_base_dir+"IpOptFSS.lib "+lib_base_dir+"IpOpt-vc10.lib "]

//else
	//third_dir = path_builder+'..'+filesep()+'..'+filesep()+'thirdparty';
	//lib_base_dir = third_dir + filesep() + 'linux' + filesep() + 'lib' + filesep() + Version + filesep();
	//inc_base_dir = third_dir + filesep() + 'linux' + filesep() + 'include' + filesep() + 'opencv';
	//incl_base_dir = third_dir + filesep() + 'linux' + filesep() + 'include' + filesep() + 'opencv2';
    
//    C_Flags=["-D__USE_DEPRECATED_STACK_FUNCTIONS__ -w -fpermissive -I"+path_builder+"-I"+inc_base_dir+" "+"-I"+incl_base_dir+" -Wl,-rpath= "+lib_base_dir+" "+"-L"+lib_base_dir+"libopencv_core"+" "+"-L"+lib_base_dir+"libopencv_highgui"+" "+"-L"+lib_base_dir+"libopencv_imgproc" ]

//    export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:"+lib_base_dir
//    unix_s("export LD_LIBRARY_PATH="+lib_base_dir);
    
//    C_Flags=["-I"+inc_base_dir+" "+"-I"+incl_base_dir];
//    Linker_Flag = ["-L"+lib_base_dir+"libopencv_core"+" "+"-L"+lib_base_dir+"libopencv_highgui"+" "+"-L"+lib_base_dir+"libopencv_imgproc" ];
    
//    Linker_Flag = ["-L/home/fossee/Desktop/FOSSEE_Image_Processing_Toolbox/thirdparty/linux/lib/x64 -lopencv_core -L/home/fossee/Desktop/FOSSEE_Image_Processing_Toolbox/thirdparty/linux/lib/x64 -lopencv_imgproc -L/home/fossee/Desktop/FOSSEE_Image_Processing_Toolbox/thirdparty/linux/lib/x64 -lopencv_highgui" ]
    

//tools_path  = path_builder + "../../thirdparty/linux/";
//unix_s("export LD_LIBRARY_PATH="+tools_path+"lib/"+Version+filesep()+" ");
//C_Flags=["-w -fpermissive -I"+tools_path+"include/opencv -I"+tools_path+"include/opencv2 -Wl,-rpath="+tools_path+"lib/"+Version+filesep()+" "]

//Linker_Flag = ["-L"+tools_path+"lib/"+Version+"-lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core "]

//end

//tbx_build_gateway(toolbox_title,Names,Files,get_absolute_file_path("builder_gateway_cpp.sce"), [], Linker_Flag, C_Flags,"g++");

//clear toolbox_title Names Files Linker_Flag C_Flags;

function builder_gw_cpp()
    WITHOUT_AUTO_PUTLHSVAR = %t;
    copyfile(path_builder+"/common.h",TMPDIR);
    copyfile(path_builder+"/common.cpp",TMPDIR);
    tbx_build_gateway("skeleton_imageprocessing", ..
    Names, ..
    Files, ..
    get_absolute_file_path("builder_gateway_cpp.sce"),[],["-L/usr/local/lib -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dpm -lopencv_fuzzy -lopencv_hdf -lopencv_line_descriptor -lopencv_optflow -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_rgbd -lopencv_viz -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_plot -lopencv_dnn -lopencv_xfeatures2d -lopencv_shape -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core -lpcl_common -lpcl_features -lpcl_filters -lpcl_io -lpcl_kdtree -lpcl_keypoints -lpcl_octree -lpcl_outofcore -lpcl_people -lpcl_recognition -lpcl_registration -lpcl_sample_consensus -lpcl_search -lpcl_segmentation -lpcl_surface -lpcl_tracking"],["-I/usr/include/scilab -I/usr/local/include/opencv -I/usr/local/include/opencv2 -I/usr/local/include/pcl-1.8 -I/usr/include/eigen3 "],"g++");
endfunction

builder_gw_cpp();
clear builder_gw_cpp; // remove builder_gw_cpp on stack
 
