function tc=removecoplanarset(tc,index)
% removes a coplanar set from the constraints
% this function removes a set of coplanar nodes from the internal
% list of coplanar sets. index is the position of the desired set to be
% remved inside the internal list.
%
% tc=removecoplanarset(tc,index) return a modified version of the tenconst
% object without the coplanar node set to be removed.
%
% The tensegrtiy constraint object must be initialized before calling this
% function, and index must be a positive integer and must not exceed the
% number of existing sets.
%
% See also: tenconst

if isa(tc,'tenconst')
    if index<1 || index>tc.num_cop_sets
        error('tenconst - Invalid index value');
    end
    tmp_cop_sets.name=[];
    tmp_cop_sets.num_nodes=0;
    tmp_cop_sets.nodes.name=[];
    tmp_cop_sets.normal=[tenvar(),tenvar(),tenvar()];
    tmp_cop_sets.dist=tenvar();
    for i=1:1:tc.num_cop_sets
        if i<index
            tmp_cop_sets(i).name=tc.cop_sets(i).name;
            tmp_cop_sets(i).num_nodes=tc.cop_sets(i).num_nodes;
            tmp_cop_sets(i).nodes(:).name=tc.cop_sets(i).nodes(:).name;
            tmp_cop_sets(i).normal=tc.cop_sets(i).normal;
            tmp_cop_sets(i).dist=tc.cop_sets(i).dist;
        else
            if i>index
                tmp_cop_sets(i-1).name=tc.cop_sets(i).name;
                tmp_cop_sets(i-1).num_nodes=tc.cop_sets(i).num_nodes;
                tmp_cop_sets(i-1).nodes(:).name=tc.cop_sets(i).nodes(:).name;
                tmp_cop_sets(i-1).normal=tc.cop_sets(i).normal;
                tmp_cop_sets(i-1).normal(1).name=['Normal_x_',num2str(i-1)];
                tmp_cop_sets(i-1).normal(2).name=['Normal_y_',num2str(i-1)];
                tmp_cop_sets(i-1).normal(3).name=['Normal_z_',num2str(i-1)];                
                tmp_cop_sets(i-1).dist=tc.cop_sets(i).dist;
                tmp_cop_sets(i-1).dist.name=['Dist_',num2str(i-1)];
            end
        end
    end
    tc.cop_sets=tmp_cop_sets;
    tc.num_cop_sets=tc.num_cop_sets-1;
else
    error('tenconst - Invalid node constraint structure');
end