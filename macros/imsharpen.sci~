function[dstMat] = imsharpen(SrcImg)
	
	srcMat = mattolist(SrcImg)
//    [rows cols channels]=size(SrcImg);
//	imgList=list();
//	for i=1:channels
//		imgList(i)=SrcImg(:,:,i);
//	end
//	disp(imgList(i))
//	out = opencv_imsharpen(imgList)
	out = opencv_imsharpen(srcMat)
	[rows cols channel] = size(out)
	
	for i = 1: channel
		dstMat(:,:,i) = out(i)
	end
	
endfunction
