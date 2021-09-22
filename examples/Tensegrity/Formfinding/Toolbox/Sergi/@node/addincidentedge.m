function [node,edge]=addincidentedge(node,edge)
% adds an edge to the list of incident edges
% this function adds an edge to the internal incident edge list of the
% node. This function also updates the origin or end node from the edge 
% object.
%
% [node,edge]=addincidentedge(node,edge) return the modified version of
% both the node and edge objects with the updated information.
%
% Both the node and the edge objects must be initialized before calling
% this funciton.
%
% See also edge,node

global error;
if isa(node,'node')
    if isa(edge,'edge')
        if node.num_edges>0
            for i=1:1:node.num_edges
                if strcmp(node.inc_edges(i).name,edge.name)
                    error('node - Edge already included');
                end
            end
            node.inc_edges(i+1).name=edge.name;
        else
            node.inc_edges(1).name=edge.name;
        end
        node.num_edges=node.num_edges+1;
        % update the origin or end node from the edge object
        if strcmp(edge.origin,'none')
            edge.origin=node.name;
        else
            edge.end=node.name;
        end
    else
        if ischar(edge)
            node.num_edges=node.num_edges+1;
            node.inc_edges(node.num_edges).name=edge;
        else
            error('node - Invalid edge structure');
        end
    end
else
    error('node - Invalid node structure');
end
