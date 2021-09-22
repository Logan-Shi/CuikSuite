function [cm_const,tc_file]=readcmconstraints(tc_file)
% reads the constraints associated to the center of mass
% this function reads the constraints associated to the center of mass of 
% the structure, which consist of:
%   * the position in the euclidean space 
%   * the orientation
% 
% [cm_const,tc_file]=readcmconstraints(tc_file) returns a modified version 
% of the tenconst object passed as argument after reading the information 
% from the file, as well as a structure with the constraint information
% about the center of mass of the structure
%
% The tenconst file object must be initialized before calling this function.
%
% See also constfile,tenconst,readfieldstring,readfieldint

if isa(tc_file,'constfile')
    % file tag txt
    CMNumNodesTxt='Num. CM Nodes:';
    CMNodesTxt='CM Nodes:';
    CMxTxt='xcm:';
    CMyTxt='ycm:';
    CMzTxt='zcm:';
    CMrxTxt='rxcm:';
    CMryTxt='rycm:';
    CMrzTxt='rzcm:';    
    try
        % read the number of nodes
        [cm_const.num_nodes,tc_file]=readfieldint(tc_file,CMNumNodesTxt);
        if cm_const.num_nodes>0
            % read the name of the nodes
            [nodes,tc_file]=readfieldstring(tc_file,CMNodesTxt);
            for i=1:1:cm_const.num_nodes
                [cm_const.nodes(i).name,nodes]=strtok(nodes,',');
            end
            cm_const.position=tenvar();
            % read the constraints for the x position
            [string,tc_file]=readfieldstring(tc_file,CMxTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.position(1)=tenvar('parameter','x_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.position(1)=tenvar('fixed','x_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.position(1)=tenvar('passive','x_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
            % read the constraints for the y position            
            [string,tc_file]=readfieldstring(tc_file,CMyTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.position(2)=tenvar('parameter','y_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.position(2)=tenvar('fixed','y_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.position(2)=tenvar('passive','y_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
            % read the constraints for the x position            
            [string,tc_file]=readfieldstring(tc_file,CMzTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.position(3)=tenvar('parameter','z_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.position(3)=tenvar('fixed','z_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.position(3)=tenvar('passive','z_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
            cm_const.orientation=tenvar();        
            % read the constraints for the rotation about x
            [string,tc_file]=readfieldstring(tc_file,CMrxTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.orientation(1)=tenvar('parameter','rx_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.orientation(1)=tenvar('fixed','rx_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.orientation(1)=tenvar('passive','rx_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
            % read the constraints for the rotation about y            
            [string,tc_file]=readfieldstring(tc_file,CMryTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.orientation(2)=tenvar('parameter','ry_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.orientation(2)=tenvar('fixed','ry_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.orientation(2)=tenvar('passive','ry_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
            % read the constraints for the rotation about z            
            [string,tc_file]=readfieldstring(tc_file,CMrzTxt);
            if strncmp(string,'parameter',size('parameter',2))
                cm_const.orientation(3)=tenvar('parameter','rz_cm');
            else 
                if strncmp(string,'fixed',size('fixed',2))
                    value=str2num(string(size('fixed,',2)+1:size(string,2)));
                    cm_const.orientation(3)=tenvar('fixed','rz_cm',value);                
                else
                    if strncmp(string,'passive',size('passive',2))
                        cm_const.orientation(3)=tenvar('passive','rz_cm');                
                    else
                        error('constfile - Invalid type for variable center of mass');
                    end
                end
            end
        else
            cm_const.nodes.name=[];
            cm_const.position=[tenvar(),tenvar(),tenvar()];
            cm_const.orientation=[tenvar(),tenvar(),tenvar()];
        end
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file structure');
end
