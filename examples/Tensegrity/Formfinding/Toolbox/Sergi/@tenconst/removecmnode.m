function tc=removecmnode(tc,nc)
% removes a node the a set node of the center of mass
% this function removes a node (nc) from the set of nodes used to compute the
% center of mass.
%
% tc=removecmnode(tc,nc) returns a modified tenconst object
% with the node nc removed from the set of nodes used to generate the center
% of mass.
%
% Both the tensegrtiy constraint object and the node constraint object must
% be initialized before calling this function.
%
% See also tenconst,nodeconst

if isa(tc,'tenconst')
    if isa(nc,'nodeconst')
        tmp_nodes.name=[];
        num=0;
        for i=1:1:tc.cm.num_nodes
            if ~strcmp(tc.cm.nodes(i).name,nc.name)
                num=num+1;
                tmp_nodes(num).name=tc.cm.nodes(i).name;
            end
        end
        tc.cm.num_nodes=tc.cm.num_nodes-1;
        tc.cm.nodes=tmp_nodes;
        if tc.cm.num_nodes==0
            tc.cm.position=[tenvar(),tenvar(),tenvar()];
            tc.cm.orientation=[tenvar(),tenvar(),tenvar()];            
        end
    else
        error('tenconst - Invalid node constraint structure');
    end
else
    error('tenconst - Invalid tensegrity constraint file');
end