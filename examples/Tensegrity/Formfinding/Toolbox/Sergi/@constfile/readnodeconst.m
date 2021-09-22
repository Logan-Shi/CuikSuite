function [tc_file,nc]=readnodeconst(tc_file,nc)
% reads the constraints associated to a node from the constraints file
% this function reads the constraint information of a node, which consists
% of:
%   * the cartesian coordinates of the node
%   * the extrenal forces applied to the node, if any.
%
% [tc_file,nc]=writenodeconst(tc_file,nc) returns a modified version of the
% tenconst object passed as argument after reading the information from the
% file, as well as a modified version of a nodeconst object with the new
% constraint information read from the file.
%
% Both the node constraint object and the tenconst file object must be 
% initialized before calling this function.
% 
% see also constfile,tenconst,nodeconst,readfieldstring,readfieldint

if ~isa(nc,'nodeconst')
    error('constfile - Invalid tensegrity constraint structure');
    return;
end
if ~isa(tc_file,'constfile')
    error('constfile - Invalid tensegrity constraint file structure');
end    
% file tag text
XTxt='x:';
YTxt='y:';
ZTxt='z:';
FxTxt='Fx:';
FyTxt='Fy:';
FzTxt='Fz:';
NumForcesTxt='Num. Ext. Forces:';
try
    % read the constraints of the x coordinate
    [x_string,tc_file]=readfieldstring(tc_file,XTxt);
    if strncmp(x_string,'fixed',size('fixed',2))
        value=x_string(size('fixed,',2)+1:size(x_string,2));
        nc.position(1)=tenvar('fixed',[nc.name,'_x'],str2num(value));
    else
        if strncmp(x_string,'passive',size('passive',2))
            nc.position(1)=tenvar('passive',[nc.name,'_x']);
        else
            if strncmp(x_string,'parameter',size('parameter',2))
                nc.position(1)=tenvar('parameter',[nc.name,'_x']);
            else
                if strncmp(x_string,'actuated',size('actuated',2))
                    nc.position(1)=tenvar('actuated',[nc.name,'_x']);
                else
                    error('constfile - Invalid file format');
                end
            end
        end
    end
    % read the constraints of the y coordinate    
    [y_string,tc_file]=readfieldstring(tc_file,YTxt);
    if strncmp(y_string,'fixed',size('fixed',2))
        value=y_string(size('fixed,',2)+1:size(y_string,2));
        nc.position(2)=tenvar('fixed',[nc.name,'_y'],str2num(value));
    else
        if strncmp(y_string,'passive',size('passive',2))
            nc.position(2)=tenvar('passive',[nc.name,'_y']);
        else
            if strncmp(y_string,'parameter',size('parameter',2))
                nc.position(2)=tenvar('parameter',[nc.name,'_y']);
            else
                if strncmp(y_string,'actuated',size('actuated',2))
                    nc.position(2)=tenvar('actuated',[nc.name,'_y']);
                else
                    error('constfile - Invalid file format');
                end
            end
        end
    end
    % read the constraints of the z coordinate    
    [z_string,tc_file]=readfieldstring(tc_file,ZTxt);
    if strncmp(z_string,'fixed',size('fixed',2))
        value=z_string(size('fixed,',2)+1:size(z_string,2));
        nc.position(3)=tenvar('fixed',[nc.name,'_z'],str2num(value));
    else
        if strncmp(z_string,'passive',size('passive',2))
            nc.position(3)=tenvar('passive',[nc.name,'_z']);
        else
            if strncmp(z_string,'parameter',size('parameter',2))
                nc.position(3)=tenvar('parameter',[nc.name,'_z']);
            else
                if strncmp(z_string,'actuated',size('actuated',2))
                    nc.position(3)=tenvar('actuated',[nc.name,'_z']);
                else
                    error('constfile - Invalid file format');
                end
            end
        end
    end
    % read the number of external forces
    [num_forces,tc_file]=readfieldint(tc_file,NumForcesTxt);
    force=tenvar();
    % read the information for each of the external forces
    for i=1:1:num_forces
        % read the constraints for the x component of the force
        [string,tc_file]=readfieldstring(tc_file,FxTxt);
        if strncmp(string,'fixed',size('fixed',2))
            values=str2num(string(size('fixed,',2):size(string,2)));
            force(1)=tenvar('fixed',[nc.name,'_Fx_',num2str(i)],values(1));
        else
            if strncmp(force_string,'parameter',size('parameter',2))
                forces(1)=tenvar('parameter',[nc.name,'_Fx_',num2str(i)]);
            else
                error('constfile - Invalid file format');
            end
        end
        % read the constraints for the x component of the force        
        [string,tc_file]=readfieldstring(tc_file,FyTxt);
        if strncmp(string,'fixed',size('fixed',2))
            values=str2num(string(size('fixed,',2):size(string,2)));
            force(2)=tenvar('fixed',[nc.name,'_Fy_',num2str(i)],values(1));
        else
            if strncmp(force_string,'parameter',size('parameter',2))
                forces(2)=tenvar('parameter',[nc.name,'_Fy_',num2str(i)]);
            else
                error('constfile - Invalid file format');
            end
        end
        % read the constraints for the x component of the force        
        [string,tc_file]=readfieldstring(tc_file,FzTxt);
        if strncmp(string,'fixed',size('fixed',2))
            values=str2num(string(size('fixed,',2):size(string,2)));
            force(3)=tenvar('fixed',[nc.name,'_Fz_',num2str(i)],values(1));
        else
            if strncmp(force_string,'parameter',size('parameter',2))
                force(3)=tenvar('parameter',[nc.name,'_Fz_',num2str(i)]);
            else
                error('constfile - Invalid file format');
            end
        end
        % add the external force to the node consstraint object
        nc=addexternalforce(nc,force);
    end
catch
    rethrow(lasterror);
end