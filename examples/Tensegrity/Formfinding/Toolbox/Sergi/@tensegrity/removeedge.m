function t=removeedge(t,edge_id)
% removes an edge from the tensegrity topology
% this function removes an edge from the tensegrity topology object,
% removing also all the references to the origin or end nodes, and 
% decrementing the number of edges, either cable or strut.
%
% The reference of the edge to remove may be the index inside the edge list
% or the name of the edge.
%
% t=removeedge(t,edge_id) returns the modified tensegrity object with the
% specified edge removed. The edge_id may be either the edge index inside
% the index or the edge name
%
% The tensegrity object must be initialized before calling this function,
% If the edge is not present, the function thows an error.
%
% See also tensegrity,edge

tmp_edges=edge();
if isa(t,'tensegrity')
    if isnumeric(edge_id)
        if (edge_id<1 || edge_id>t.num_edges)
            error('tensegrity - There is no such edge');
        else
            try
                % remove the references from the origin and end nodes
                for i=1:1:t.num_nodes
                    [t.nodes(i),t.edges(edge_id)]=removeincidentedge(t.nodes(i),t.edges(edge_id));
                end
                % remove the edge
                for i=1:1:t.num_edges
                    if i<edge_id
                        tmp_edges(i)=t.edges(i);
                    else
                        if i==edge_id
                            del_edge=t.edges(i);
                        else
                            tmp_edges(i-1)=t.edges(i);
                        end
                    end
                end
            catch
                rethrow(lasterror);
            end
        end
    else
        if ischar(edge_id)
            try
                % remove the references from the origin and end nodes
                for i=1:1:t.num_nodes
                    [t.nodes(i),t.edges(edge_id)]=removeincidentedge(t.nodes(i),t.edges(edge_id));
                end
                % remove the edge
                num=1;
                for i=1:1:t.num_edges
                    if strcmp(t.edges(i).name,edge_id)
                        del_edge=t.edges(i);
                    else
                        tmp_edges(num)=t.edges(i);
                        num=num+1;
                    end
                end
            catch
                rethrow(lasterror);
            end
        else
            error('tensegrity - The edge identifier must be either numeric or string');
        end
    end
    % update the number of cables and struts
    t.num_edges=t.num_edges-1;
    if strcmp(del_edge.type,'cable')
        t.num_cables=t.num_cables-1;
    else
        t.num_struts=t.num_struts-1;
    end
    t.edges=tmp_edges;
else
    error('tensegrity - Invalid tensegrity structure');    
end
