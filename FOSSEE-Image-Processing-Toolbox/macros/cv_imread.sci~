function[dstMat] = imread(matA)

	out = opencv_imread(matA)

	channel = size(out)
	
	for i = 1: channel
		dstMat(:,:,i) = out(i)
	end
	
endfunction
