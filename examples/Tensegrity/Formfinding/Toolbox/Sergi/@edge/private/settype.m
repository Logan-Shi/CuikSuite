function edge=settype(edge,type)
% changes the type of an edge
% this function changes the type of an edge outside a tensegrity structure.
% To change the type of an edge included in a tensegrity structure, use the
% funciton changeedgetype() of the tensegrity class, because in this case
% it is also necessary to update the number of cables and struts, as well
% as to check the class of the new tensegrity structure.
%
% edge=settype(edge,type) returns a modified version of the edge object
% with the new type, either cable or strut.
%
% The edge object must be initialized before calling this functions and the
% type must be a string equal to either 'cable' or 'strut'.
%
% See also edge,tensegrity,changeedgetype

if isa(edge,'edge')
    if ischar(type)
        if strcmp(type,'cable')
            edge.type='cable';
        else
             if strcmp(type,'strut')
                 edge.type='strut';
             else
                 error('edge - Invalid edge type');
             end
        end
    else
        error('edge - The type value must be a string');
    end
else
    error('edge - Invalid edge structure');
end