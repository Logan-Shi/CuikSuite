function tc_file=writecost_func(tc_file,func)
% writes the name of the M-file which generates the cost function 
% this function stores the name of the M-file which generates the cost
% function associated to the tensegrity into the constarint file. 
%
% tc_file=writecost_func(tc_file,func) returns a modified version of
% the tenconst object passed as argument after writing the information into
% the file.
%
% The cost function M-file name must not include the .m termination and 
% the tenconst file object must be initialized before calling this function.
%
% See also constfile,tenconst,writefieldstring

% file tag text
TopFileTxt='Cost Func.:';
if isa(tc_file,'constfile')
    try
        tc_file=writefieldstring(tc_file,TopFileTxt,func);
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file');
end
