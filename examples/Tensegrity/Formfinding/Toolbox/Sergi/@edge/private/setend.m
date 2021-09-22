function edge=setend(edge,end_node)
% changes the end node of an edge
% this function changes the end node of an edge outside a tensegrity 
% structure. To change the end node of an edge included in a tensegrity 
% structure, use the function removeincidentedge of the node class, because
% in this case it is also necessary to change the list of incident edges of
% the node.
%
% edge=setend(edge,end_node) returns a modified version of the edge 
% object with the new end node name.
%
% The edge object must be initialized before calling this functions and the
% node name must be a string with a valid node name.
%
% See also edge,tensegrity,addincidentedge

if isa(edge,'edge')
    if ischar(end_node)
        edge.end=end_node;
    else
        error('edge - Invalid end node name');
    end
else
    error('edge - Invalid edge structure');
end
