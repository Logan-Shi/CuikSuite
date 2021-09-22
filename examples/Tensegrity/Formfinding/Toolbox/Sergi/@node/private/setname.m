function node=setname(node,name)
% changes the name of a node
% this function changes the name of a node outside a tensegrity structure. 
%
% node=setname(node,name) returns a modified version of the node 
% object with the new node name
%
% The node object must be initialized before calling this functions and the
% node name must be a string with a valid node name.
%
% See also node,tensegrity


if isa(node,'node')
    if ischar(name)
        node.name=name;
    else
        error('node - Invalid node name');
    end
else
    error('node - Invalid node structure');
end
