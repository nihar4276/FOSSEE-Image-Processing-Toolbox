function [output] = xyz2rgb(img)
	image = mattolist(img);
	a = opencv_xyz2rgb(image);
	d = size(a);
	for i=1:d
		output(:,:,i) = a(i);
	end
endfunction
