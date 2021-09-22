function t=addnode(t,n)
% adds a node to the tensegrity structure
% this function adds a previously initialized node in the internal node
% list. The total number of nodes is automatically updated.
%
% t=addnode(t,n) return a modified version of the tensegrity object (t)
% with the node (n) added.
%
% Both the tensegrity object and the node object must be initialized before
% calling this function.
%
% See also tensegrity,node

if isa(t,'tensegrity')
    if isa(n,'node')
        for i=1:1:t.num_nodes
            if strcmp(t.nodes(i).name,n.name)==1
                error('tensegrity - Node already present');
            end
        end
        t.num_nodes=t.num_nodes+1;
        if t.num_nodes==1
            t.nodes=n;
        else
            t.nodes(t.num_nodes)=n;
        end
    else
        error('tensegrity - Invalid node structure');
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
