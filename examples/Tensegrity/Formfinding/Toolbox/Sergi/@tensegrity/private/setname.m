function t=setname(t,name)
% sets the name of the tensegrity structure
% this private functions change the current name of the tensegrity 
% structure
%
% t=setname(t,name) returns a modified version of the tensegrity structure
% with the new name.
%
% The tensegrity object must be initialized before calling this function
% and the name parameter must be a string.
%
% See also tensegrity
global error;
if isa(t,'tensegrity')
    if ischar(name)
        t.name=name;
    else
        error('tensegrity - Invalid name');
    end
else
    error=('tensegrity - Invalid tensegrity structure');
end
