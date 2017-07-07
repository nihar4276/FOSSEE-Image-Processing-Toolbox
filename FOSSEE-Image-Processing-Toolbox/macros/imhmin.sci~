unction[dstMat] = imfill(srcImg, H-min)
	
	[lhs, rhs] = argn(0)
	
	srcMat = mattolist(srcImg)

	out = opencv_imfill(srcMat, H-min)
	
	channel = size(out)
	
	for i = 1: channel
		dstMat(:,:,i) = out(i)
	end
	
endfunction
