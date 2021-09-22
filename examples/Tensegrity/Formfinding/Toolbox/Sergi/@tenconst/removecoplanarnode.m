function tc=removecoplanarnode(tc,index,nc)
% remove a node from a set of coplanar nodes
% this function removes a node (nc) from a set of already existing coplanar 
% nodes set specified by index.
%
% tc=removecoplanarnode(tc,index,nc) returns a modified tenconst object
% with the node nc removed from the set of coplanar nodes specified by 
% index.
%
% Both the tensegrtiy constraint object and the node constraint object must
% be initialized before calling this function, and the index must be a
% psitive integer and must not exceed the number of existing sets.
%
% See also: tenconst,nodeconst

if isa(tc,'tenconst')
    if index<1 || index>tc.num_cop_sets
        error('tenconst - Invalid index value');
    end
    if isa(nc,'nodeconst')
        tmp_nodes.name=[];
        num=0;
        for i=1:1:tc.cop_sets(index).num_nodes
            if ~strcmp(tc.cop_sets(index).nodes(i).name,nc.name)
                num=num+1;
                tmp_nodes(num).name=tc.cop_sets(index).nodes(i).name;
            end
        end
        tc.cop_sets(index).num_nodes=tc.cop_sets(index).num_nodes-1;
        tc.cop_sets(index).nodes=tmp_nodes;
    else
        error('tenconst - Invalid node constraint structure');
    end
else
    error('tenconst - Invalid tensegrity constraint file');
end