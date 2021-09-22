function index=getnodeindex(t,name)
% return the index of a node by name in the internal node list
% this function returns the index of a node inside the internal tensegrity
% node list by name.
% 
% index=getnodeindex(t,name) return an integer which corresponds to the
% position of the node identified by the string name. If a node with the
% specified name does not exist, the function throws an error.
%
% The tensegrity object (t) must be initialized before calling this
% function.
% 
% See also tensegrity,node

if isa(t,'tensegrity')
    if ischar(name)
        for i=1:1:t.num_nodes
            if strcmp(t.nodes(i).name,name)
                index=i;
            end
        end
    else
        error('tensegrity - The node name must be a string');
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
