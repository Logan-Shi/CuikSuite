function edge=setorigin(edge,origin_node)
% changes the origin node of an edge
% this function changes the origin node of an edge outside a tensegrity 
% structure. To change the origin node of an edge included in a tensegrity 
% structure, use the function addincidentedge of the node class, because in
% this case it is also necessary to change the list of incident edges of
% the node.
%
% edge=setorigin(edge,origin_node) returns a modified version of the edge 
% object with the new origin node name.
%
% The edge object must be initialized before calling this functions and the
% node name must be a string with a valid node name.
%
% See also edge,tensegrity,addincidentedge

if isa(edge,'edge')
    if ischar(origin_node)
        edge.origin=origin_node;
    else
        error('edge - Invalid origin node name');
    end
else
    error('edge - Invalid edge structure');
end