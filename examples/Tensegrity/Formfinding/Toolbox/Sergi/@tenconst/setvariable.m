function tc=setvariable(tc,index,var)
% update the information of an internal tenconst variable
% this function allows to update the information of a single variable
% indise the tenconst object by means of its index inside the variable
% list.
%
% tc=setvariable(tc,index,var) returns a modified version of the tenconst
% object with the information for the index variable updated to val.
%
% Both the tensegrity constraint object and the variable object must be
% initialized before calling this function, and index must be a positive
% integer and must not exceed the number of available variables (both 
% internal and user).
%
% See also tenconst,tenvar

if isa(tc,'tenconst')
    if index<1 || index>tc.num_var
        error('tenconst - Invalid variable index');
    else
        if isa(var,'tenvar')
            tc.variables(index)=var;            
            % node constraints
            for i=1:1:tc.tensegrity.num_nodes
                index=index-1;
                if index==0
                    tc.tensegrity.nodes(i).position(1)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.tensegrity.nodes(i).position(2)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.tensegrity.nodes(i).position(3)=var;
                    return;
                end
                for j=1:1:tc.tensegrity.nodes(i).num_forces
                    index=index-1;
                    if index==0
                        tc.tensegrity.nodes(i).forces(j,1)=var;
                        return;
                    end
                    index=index-1;                    
                    if index==0
                        tc.tensegrity.nodes(i).forces(j,2)=var;
                        return;
                    end
                    index=index-1;                    
                    if index==0
                        tc.tensegrity.nodes(i).forces(j,3)=var;
                        return;
                    end
                end
            end
            % edge constraints            
            for i=1:1:tc.tensegrity.num_edges
                index=index-1;
                if index==0
                    tc.tensegrity.edges(i).stiffness=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.tensegrity.edges(i).rest_length=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.tensegrity.edges(i).length=var;
                    return;
                end
            end
            % center of mass constraints
            if tc.cm.num_nodes>0
                index=index-1;
                if index==0
                    tc.cm.position(1)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.cm.position(2)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.cm.position(3)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.cm.orientation(1)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.cm.orientation(2)=var;
                    return;
                end
                index=index-1;
                if index==0
                    tc.cm.orientation(3)=var;
                    return;
                end
            end
            % coplanar node sets constraints
            for i=1:1:tc.num_cop_sets
                cop_set=tc.cop_sets(i);
                index=index-1;
                if index==0
                    tc.cop_sets(i).normal(1)=var;
                end
                index=index-1;
                if index==0
                    tc.cop_sets(i).normal(2)=var;
                end
                index=index-1;
                if index==0
                    tc.cop_sets(i).normal(3)=var;
                end
                index=index-1;
                if index==0
                    tc.cop_sets(i).dist=var;
                end
            end
            
        else
            error('tenconst - Invalid variable structure');
        end
    end
else
    error('tenconst - Invalid tensegrity constraint structure');
end
