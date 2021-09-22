function t=removenode(t,node_id)
% removes a node from the tensegrity topology
% this function removes a node from the tensegrity topology object,
% removing also all the references to the origin or end nodes of all
% incident edges, and decrementing the number of nodes.
%
% The reference of the node to remove may be the index inside the node list
% or the name of the node.
%
% t=removenode(t,node_id) returns the modified tensegrity object with the
% specified node removed. The node_id may be either the node index inside
% the index or the node name
%
% The tensegrity object must be initialized before calling this function,
% If the node is not present, the function thows an error.
%
% See also tensegrity,node

tmp_nodes=node();
if isa(t,'tensegrity')
    if isnumeric(node_id)
        if (node_id<1 || node_id>t.num_nodes)
            error('tensegrity - There is no such node');
        else
            try
                for i=1:1:t.num_nodes
                    if i<node_id
                        tmp_nodes(i)=t.nodes(i);
                    else
                        if i==node_id
                            del_node=t.nodes(i);
                        else
                            tmp_nodes(i-1)=t.nodes(i);
                        end
                    end
                end
            catch
                rethrow(lasterror);
            end
        end
    else
        if ischar(node_id)
            num=1;
            try
                for i=1:1:t.num_nodes
                    n=t.nodes(i);
                    if strcmp(t.nodes(i).name,node_id)
                        del_node=t.nodes(i);
                    else
                        tmp_nodes(num)=t.nodes(i);
                        num=num+1;
                    end
                end
            catch
                rethrow(lasterror);
            end
            if num==t.num_nodes
                error('tensegrity - There is no such node');
            end
        else
            error('tensegrity - The node identifier must be either numeric or string');
        end
    end
    t.num_nodes=t.num_nodes-1;
    t.nodes=tmp_nodes;
    % remove the references from the incident edges
    try
        for i=1:1:t.num_edges
            if strcmp(t.edges(i).origin,del_node.name)
                t.edges(i).origin='none';
            else
                if strcmp(t.edges(i).end,del_node.name)
                    t.edges(i).end='none';
                end
            end
        end
    catch
        rethrow(lasterror);
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
