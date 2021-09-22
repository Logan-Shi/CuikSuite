function edge=setname(edge,name)
% changes the name of an edge
% this function changes the name of an edge outside a tensegrity 
% structure. 
%
% edge=setname(edge,name) returns a modified version of the edge 
% object with the new edge name
%
% The edge object must be initialized before calling this functions and the
% node name must be a string with a valid node name.
%
% See also edge,tensegrity

if isa(edge,'edge')
    if ischar(name)
        edge.name=name;
    else
        error('edge - Invalid edge name');
    end
else
    error('edge - Invalid edge structure');
end