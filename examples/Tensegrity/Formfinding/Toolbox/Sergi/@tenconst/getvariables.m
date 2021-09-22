function [tc,num,vars]=getvariables(tc)
% returns the number and the list of the internal and user variables
% this function checks the object for all present variables and generates a
% vector with them, returning both the number and the list of internal
% variables. It also updates the internal list of variables and its number.
%
% [tc,num,vars]=getvariables(tc) returns a modified version of a tenconst
% object together with the number and the list of internal variables.
%
% The tensegrity constraint object must be initialized before calling this
% function.
%
% See also tenconst,tenvar

if ~isa(tc,'tenconst')
    error('tenconst - Invalid tensegrity constraint structure');
end
tc.num_var=0;
tc.variables=tenvar();
% variables of the nodes
for i=1:1:tc.tensegrity.num_nodes
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.nodes(i).position(1);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.nodes(i).position(2);    
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.nodes(i).position(3);    
    for j=1:1:tc.tensegrity.nodes(i).num_forces
        tc.num_var=tc.num_var+1;
        tc.variables(tc.num_var)=tc.tensegrity.nodes(i).forces(j,1);    
        tc.num_var=tc.num_var+1;
        tc.variables(tc.num_var)=tc.tensegrity.nodes(i).forces(j,2);    
        tc.num_var=tc.num_var+1;
        tc.variables(tc.num_var)=tc.tensegrity.nodes(i).forces(j,3);    
    end
end
% variables of the edges
for i=1:1:tc.tensegrity.num_edges
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.edges(i).stiffness;
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.edges(i).rest_length;
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.tensegrity.edges(i).length;
end
% variables of the center of mass
if tc.cm.num_nodes>0
    cm_const=tc.cm;
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.position(1);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.position(2);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.position(3);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.orientation(1);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.orientation(2);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cm_const.orientation(3);
end
% variables of the coplanar sets
for i=1:1:tc.num_cop_sets
    cop_set=tc.cop_sets(i);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cop_set.normal(1);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cop_set.normal(2);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cop_set.normal(3);
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=cop_set.dist;
end
% user variables
for i=1:1:tc.num_user_var
    tc.num_var=tc.num_var+1;
    tc.variables(tc.num_var)=tc.user_variables(i);
end
% return the number and list of variables
num=tc.num_var;
vars=tc.variables;

