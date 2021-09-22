function nc=removeexternalforce(nc,index)
% removes an external force applied to a node
% this function removes an extrenal force applied to a node (nc),
% automatically updating the number of external forces.
%
% nc=removeexternalforce(nc,index) return a modifeid version of the
% nodeconst object without the removed external force.
% 
% The node constraint object must be initialized before calling this
% function.
%
% See also nodeconst

if isa(nc,'nodeconst')
    if index<1 || index>nc.num_forces
        error('nodeconst - Invalid index value');
    end
    tmp_forces=[tenvar(),tenvar(),tenvar()];
    for i=1:1:nc.num_forces
        if i<index
            tmp_forces(i,:)=nc.forces(i,:);
        else
            if i==index
                del_force=nc.forces(i,:);
            else
                tmp_forces(i-1,:)=nc.forces(i,:);
                tmp_forces(i-1,1).name=['Force_Fx_',num2str(i-1)];
                tmp_forces(i-1,2).name=['Force_Fy_',num2str(i-1)];
                tmp_forces(i-1,3).name=['Force_Fz_',num2str(i-1)];                
            end
        end
    end
    nc.num_forces=nc.num_forces-1;
    nc.forces=tmp_forces;
else
    error('nodeconst - Invalid node constraint structure');
end