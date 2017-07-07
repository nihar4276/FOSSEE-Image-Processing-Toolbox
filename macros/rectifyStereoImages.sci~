function [out]=rectifyStereoImages(input_image1,cameramatrix1,Distortion_coff1,input_image2,cameramatrix2,Distortioncoff2,Translationvector,Rotationvector)
// Rectify the pair of image taken by stereo camera
//
// Calling Sequence
// [left_image,right_image] = rectifyStereoImages  (input_image1,cameramatrix1,Distortion_coff1,input_image2,cameramatrix2,Distortioncoff2,Translationvector,Rotationvector)
// left_image = rectified input_image1
// right_image = rectified input_image2
//
// Parameters
//
// input_image1 : First Stereo image on which rectification has to be performed
// Cameramatrix1 : An input matrix of 3*3
// Distortion_coff1 : A vector of size 4 ,5 or 8
// input_image2 : Second Stereo image on which rectification has to be performed
// Cameramatrix2 : An input matrix of 3*3
// Distortion_coff2 : A vector of size 4 ,5 or 8
// Translationvector : A vector of size 3
// Rotationvector : An input matrix of 3*3
// left_image : rectified input_image1
// right_image : rectfied input_image2
//
// Description
// This function first undistorted and then rectified the both image1 and image2.It uses  camera parameters,respective rotation,translation of both camera.
//
// Examples
// a = imread('lena.jpeg')
// cameramatrix1 = [1 0 1;0 1 1;0 0 1];
// Distortion_coff1 = [200 200 400 300];
// b = imread('lena.jpeg')
// cameramatrix2 = [2 0 1;0 1 1;0 0 1];
// Distortion_coff2 = [205 240 410 370];
// Translationvector = [1 2 3];
// Rotationvector = [0 0 2;1 4 5;6 7 8];
// [left_image,right_image] = rectifyStereoImages(a,cameramatrix1,Distortion_coff1,b,cameramatrix2,Distortioncoff2,Translationvector,Rotationvector);
// imshow(left_image);
// imshow(right_image);
//
// Authors.
//
//Diwakar Bhardwaj

         input_image3=mattolist(input_image1);
          input_image4=mattolist(input_image2);
       [left_image right_image]=rectifyStereoImages(input_image3,cameramatrix1,Distortion_coff1,input_image4,cameramatrix2,Distortioncoff2,Translationvector,Rotationvector);

           dimension1=size(left_image)
         for i = 1:dimension1
              left_out(:,:,i)=left_image(i);
         end

          dimension2=size(right_image)
         for j = 1:dimension2
              right_out(:,:,j)=right_image(j);
         end
     

         out=struct("left_rectifyimage",left_out,"right_rectifyimage",right_out);

endfunction;*
