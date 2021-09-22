function tc=setcostfunction(tc,func_name)
% sets the cost function to be used in the optimization process
% this function sets the cost function handle of the tenconst object by
% means of the name of the *.m file associated. The filename is internally
% converted to a function handle and stored as a class attribute.
%
% tc=setcostfunction(tc,func_name) returns a modified version of the
% tenconst object with the new handle to the cost function.
%
% The tensegrtiy constriaint object must be initialized before calling this
% function, and func_name must be a string with an existing *.m file. The
% template for the cost function file is as follows:
%
%   cost_func=<function name>(tenconst object);
%
% See also tenconst

if isa(tc,'tensegrity')
    if ischar(func_name)
        tc.cost_func_h=str2func(func_name);
    else
        error('tenconst - Invalid function name');
    end
else
    error('tenconst - Invalid tensegrityt constraint file');
end