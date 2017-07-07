function[dstMat] = integralImage(srcImg, varargin)
	
	[lhs, rhs] = argn(0)
	
	srcMat = mattolist(srcImg)

	select rhs
		case 1 then
			out = opencv_integralImage(srcMat)
		case 3 then
			out = opencv_integralImage(srcMat, varargin(1))
	end
	
	channel = size(out)
	
	for i = 1: channel
		dstMat(:,:,i) = out(i)
	end
	
endfunction
