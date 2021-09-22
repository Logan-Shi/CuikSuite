function tc=addcmnode(tc,nc)
% adds a node to the set of nodes of the center of mass
% this function adds a new node (nc) to the set nodes used to compute the
% center of mass.
%
% tc=addcmnode(tc,nc) returns a modified tenconst object with the node nc
% added to the set of node used to generate the center of mass
%
% Both the tensegrtiy constraint object and the node constraint object must
% be initialized before calling this function.
%
% See also tenconst,nodeconst

if isa(tc,'tenconst')
    if isa(nc,'nodeconst')
        for i=1:1:tc.cm.num_nodes
            if strcmp(tc.cm.nodes(i).name,nc.name)
                error('tenconst - Node already present');
            end
        end
        tc.cm.num_nodes=tc.cm.num_nodes+1;
        tc.cm.nodes(tc.cm.num_nodes).name=nc.name;
        if tc.cm.num_nodes==1
            tc.cm.position=[tenvar('passive','x_cm'),tenvar('passive','y_cm'),tenvar('passive','z_cm')];
            tc.cm.orientation=[tenvar('passive','rx_cm'),tenvar('passive','ry_cm'),tenvar('passive','rz_cm')];            
        end
    else
        error('tenconst - Invalid node constraint structure');
    end    
else
    error('tenconst - Invalid tensegrity constraint structure');
end