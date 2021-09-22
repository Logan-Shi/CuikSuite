function tc=addcoplanarset(tc)
% adds a coplanar set to the constraints
% this function adds a default set of coplanar nodes to the internal list of 
% coplanar sets. The information about the new coplanar set can be
% modified by adding node with the addcoplanarnode function.
%
% tc=addcoplanarset(tc) return a modified version of the tenconst
% object with the new coplanar node set.
%
% The tensegrtiy constraint object must be initialized before calling this
% function.
%
% See also tenocnst

if isa(tc,'tenconst')
    tc.num_cop_sets=tc.num_cop_sets+1;
    tc.cop_sets(tc.num_cop_sets).name=['set_',num2str(tc.num_cop_sets)];
    tc.cop_sets(tc.num_cop_sets).num_nodes=0;
    tc.cop_sets(tc.num_cop_sets).nodes.name=[];
    tc.cop_sets(tc.num_cop_sets).normal=[tenvar('passive',['Normal_x_',num2str(tc.num_cop_sets)]),tenvar('passive',['Normal_y_',num2str(tc.num_cop_sets)]),tenvar('passive',['Normal_z_',num2str(tc.num_cop_sets)])];
    tc.cop_sets(tc.num_cop_sets).dist=tenvar('passive',['Dist_',num2str(tc.num_cop_sets)]);
else
    error('tenconst - Invalid tensegrity constraint structure');
end