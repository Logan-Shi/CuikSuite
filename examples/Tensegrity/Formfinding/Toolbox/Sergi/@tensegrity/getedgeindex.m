function index=getedgeindex(t,name)
% return the index of an edge by name in the internal edge list
% this function returns the index of an edge inside the internal tensegrity
% edge list by name.
% 
% index=getedgeindex(t,name) return an integer which corresponds to the
% position of the edge identified by the string name. If an edge with the
% specified name does not exist, the function throws an error.
%
% The tensegrity object (t) must be initialized before calling this
% function.
% 
% See also tensegrity,edge

if isa(t,'tensegrity')
    if ischar(name)
        for i=1:1:t.num_edges
            if strcmp(t.edges(i).name,name)
                index=i;
            end
        end
    else
        error('tensegrity - The edge index must be a string');
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
