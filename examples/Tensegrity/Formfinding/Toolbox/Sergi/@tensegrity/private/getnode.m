function node=getnode(t,node_id)
% returns the node object referenced by node_id
% this private function return the node object referenced by node_if, which
% may be either an integer with the index inside the internal list or its
% name.
%
% node=getnode(t,node_id) returns a node object with the information of the
% desired node.
%
% The tensegrity object must be initialized before calling this fucntion
% and the node_id parameter must be either an integer or a string.
%
% See also tensegrity,node

if isa(t,'tensegrity')
    if isnumeric(node_id)
        if (node_id<1 || node_id>t.num_nodes)
            error('tensegrity - There is no such node');
        else
            node=t.nodes(node_id);
        end
    else
        if ischar(node_id)
            for i=1:1:t.num_nodes
                if strcmp(t.nodes(i).name,node_id)
                    node=t.nodes(i);
                    return;
                end
            end
            error('tensegrity - No such node');
        else
            error('tensegrity - The node identifier must be a value or string');
        end
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
