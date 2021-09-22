function [node,edge]=removeincidentedge(node,edge)
% removes an edge from the list of incident edges
% this function removes an edge from the internal incident edge list of the
% node. This function also eliminates the reference to the origin or end
% node from the edge object.
%
% [node,edge]=removeincidentedge(node,edge) return the modified version of
% both the node and edge objects with the updated information.
%
% Both the node and the edge objects must be initialized before calling
% this funciton.
%
% See also edge,node
 
if isa(node,'node')
    if isa(edge,'edge')
        if node.num_edges>1
            num=0;
            try
                for i=1:1:node.num_edges
                    if ~strcmp(node.inc_edges(i).name,edge.name)
                        num=num+1;                    
                        tmp_edges(num).name=node.inc_edges(i).name;
                    end
                end
            catch
                rethrow(lasterror);
            end
        else
            tmp_edges=[];
        end    
        if num<node.num_edges
            node.num_edges=node.num_edges-1;
            node.inc_edges=tmp_edges;
        end
        % elimnate the reference of the node from the edge object
        if strcmp(edge.origin,node.name)
            edge.origin='none';
        else
            edge.end='none';
        end
    else
        error('node - Invalid edge structure');
    end
else
    error('node - Invalid node structure');
end
