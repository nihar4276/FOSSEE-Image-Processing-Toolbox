//Author-Nihar Rao
function[point] = pcread(inputPath)

 [lhs rhs]=argn(0);
	
        if lhs>1
         error(msprintf(" Too many output arguments"));
    	elseif rhs>1 
        error(msprintf(" Too many input arguments,maximum number of arguments is 1\n"));
    	elseif rhs<1
        error(msprintf("the function needs atleast 1 arguments"));
    	end 

	[location count width height rgb xlimit ylimit zlimit dense intensity Normal]=raw_pcread(inputPath);



point=struct('dataType','PointCloud','Width',width,'Height',height,'is_dense',dense,'Location',location,'Count',count,'Color',rgb,'XLimits',xlimit,'YLimits',ylimit,'ZLimits',zlimit,'Intensity',intensity,'Normal',Normal);
    






endfunction
