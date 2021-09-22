function edge=getedge(t,edge_id)
% returns the edge object referenced by node_id
% this private function return the edge object referenced by edge_if, which
% may be either an integer with the index inside the internal list or its
% name.
%
% edge=getedge(t,edge_id) returns an edge object with the information of the
% desired edge.
%
% The tensegrity object must be initialized before calling this fucntion
% and the node_id parameter must be either an integer or a string.
%
% See also tensegrity,edge

if isa(t,'tensegrity')
    if isnumeric(edge_id)
        if (edge_id<1 || edge_id>t.num_edges)
            error('tensegrity - There is no such edge');
        else
            edge=t.edges(edge_id);
        end
    else
        if ischar(edge_id)
            for i=1:1:t.num_edges
                if strcmp(t.edges(i).name,edge_id)
                    edge=t.edges(i);
                    return;
                end
            end
        else
            error('tensegrity - The edge index must be an integer');
        end
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
