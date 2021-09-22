function [func,tc_file]=readcostfunc(tc_file)
% reads the name of the M-file which generates the cost function 
% this function retrieves the name of the M-file which generates the cost
% function associated to the tensegrity from the constarint file. 
%
% [func,tc_file=writecost_func(tc_file) returns a modified version of
% the tenconst object passed as argument after reading the information from
% the file, as well as the name of the cost function as a string which must
% be converted to a function handle before using it.
%
% The tenconst file object must be initialized before calling this function.
%
% See also constfile,tenconst,readfieldstring

CostFuncTxt='Cost Func.:';
if isa(tc_file,'constfile')
    try
        [func,tc_file]=readfieldstring(tc_file,CostFuncTxt);
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file');
end

