function tc=addcoplanarnode(tc,index,nc)
% adds a node to a set of coplanar nodes
% this function adds a node (nc) to a set of already existing coplanar 
% nodes specified by index.
%
% tc=addcoplanarnode(tc,index,nc) returns a modified tenconst object
% with the node nc added to the set of coplanar nodes specified by 
% index.
%
% Both the tensegrtiy constraint object and the node constraint object must
% be initialized before calling this function, and index must be a positive
% integer and must not exceed the number of coplanar sets.
%
% See also tenconst,nodeconst

if isa(tc,'tenconst')
    if index<1 || index>tc.num_cop_sets
        error('tenconst - Invalid index value');
    end
    if isa(nc,'nodeconst')
        for i=1:1:tc.cop_sets(index).num_nodes
            if strcmp(tc.cop_sets(index).nodes(i).name,nc.name)
                error('tenconst - Node already present');
            end
        end
        tc.cop_sets(index).num_nodes=tc.cop_sets(index).num_nodes+1;
        tc.cop_sets(index).nodes(tc.cop_sets(index).num_nodes).name=nc.name;
    else
        error('tenconst - Invalid node constraint structure');
    end
else
    error('tenconst - Invalid tensegrity constraint file');
end