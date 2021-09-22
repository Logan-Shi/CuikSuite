function tc_file=writenodeconst(tc_file,nc)
% writes the constraints associated to a node into the constraints file
% this function writes the constraint information of a node, which consists
% of:
%   * the cartesian coordinates of the node
%   * the extrenal forces applied to the node, if any.
%
% tc_file=writenodeconst(tc_file,nc) returns a modified version of the
% tenconst object passed as argument after writing the information into the
% file.
%
% The node constraints must be included in a nodeconst object (nc) passed
% as argument and the tenconst file object must be initialized before
% calling this function.
% 
% see also constfile,tenconst,nodeconst,writefieldstring,writefieldint

if ~isa(nc,'nodeconst')
    error('constfile - Invalid tensegrity constraint object');
end
if ~isa(tc_file,'constfile')
    error('constfile - Invalid tensegrity constraint file object');
end
% file tag text
XTxt='x:';
YTxt='y:';
ZTxt='z:';
NumForcesTxt='Num. Ext. Forces:';
FxTxt='Fx:';
FyTxt='Fy:';
FzTxt='Fz:';
try
    % write the name of the node
    tc_file=writefieldstring(tc_file,'',nc.name);
    % write the x coordinate
    x_string=nc.position(1).type;
    if strncmp(x_string,'fixed',size('fixed',2))
        x_string=[x_string,',',num2str(nc.position(1).value)];
    end
    tc_file=writefieldstring(tc_file,XTxt,x_string);
    % write the y coordinate
    y_string=nc.position(2).type;
    if strncmp(y_string,'fixed',size('fixed',2))
        y_string=[y_string,',',num2str(nc.position(2).value)];
    end
    tc_file=writefieldstring(tc_file,YTxt,y_string);
    % write the z coordinate
    z_string=nc.position(3).type;
    if strncmp(z_string,'fixed',size('fixed',2))
        z_string=[z_string,',',num2str(nc.position(3).value)];
    end
    tc_file=writefieldstring(tc_file,ZTxt,z_string);
    % write the number of forces applied to the node
    tc_file=writefieldint(tc_file,NumForcesTxt,nc.num_forces);
    % write the information for each of the forces
    for i=1:1:nc.num_forces
        % force x coordinate
        force_string=nc.forces(i,1).type;
        if strncmp(force_string,'fixed',size('fixed',2))
            force_string=[force_string,',',num2str(nc.forces(i,1).value)];
        end
        tc_file=writefieldstring(tc_file,FxTxt,force_string);
        % force y coordinate        
        force_string=nc.forces(i,2).type;
        if strncmp(force_string,'fixed',size('fixed',2))
            force_string=[force_string,',',num2str(nc.forces(i,2).value)];
        end
        tc_file=writefieldstring(tc_file,FyTxt,force_string);
        % force z coordinate        
        force_string=nc.forces(i,3).type;
        if strncmp(force_string,'fixed',size('fixed',2))
            force_string=[force_string,',',num2str(nc.forces(i,3).value)];
        end
        tc_file=writefieldstring(tc_file,FzTxt,force_string);
    end
catch
    rethrow(lasterror);
end
