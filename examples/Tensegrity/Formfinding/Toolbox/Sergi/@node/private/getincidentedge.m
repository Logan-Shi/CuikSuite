function inc_edge=getincidentedge(node,index)
% return the incident edge at the index position
% this function return the name of the incident edge at the index position
% inside the internal list of incident edges.
%
% inc_edge=getincidentedge(node,index) return the name of the incident egde
% at the index position.
%
% The node object must be initialized before calling this function and
% index must be positive and do not exceed the number of incident edges,
% otherwise an error is thrown.
%
% See also node, edge

if isa(node,'node')
    if index<1 || index>node.num_edges
        error('node - Invalid index value');  
    else
        inc_edge=node.inc_edges(index).name;
    end
else
    error('node - Invalid node structure');  
end
