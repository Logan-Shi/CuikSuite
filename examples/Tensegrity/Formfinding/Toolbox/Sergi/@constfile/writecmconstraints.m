function tc_file=writecmconstraints(tc_file,cm_const)
% writes the constraints associated to the center of mass
% this function writes the constraints associated to the center of mass of 
% the structure, which consist of:
%   * the position in the euclidean space 
%   * the orientation
% 
% tc_file=writecmconstraints(tc_file,cm_const) returns a modified version 
% of the tenconst object passed as argument after writing the information 
% into the file.
%
% cm_const must be a structure with all the information associated to the
% constraints of the center of mass of the structure, and the tenconst file
% object must be initialized before calling this function.
%
% See also constfile,tenconst,writefieldstring,writefieldint

if isa(tc_file,'constfile')
    % file tag text
    CMNumNodesTxt='Num. CM Nodes:';
    CMNodesTxt='CM Nodes:';
    CMxTxt='xcm:';
    CMyTxt='ycm:';
    CMzTxt='zcm:';
    CMrxTxt='rxcm:';
    CMryTxt='rycm:';
    CMrzTxt='rzcm:';    
    try
        % write the number of nodes associated to the center of mass
        tc_file=writefieldint(tc_file,CMNumNodesTxt,cm_const.num_nodes);
        if cm_const.num_nodes>0
            nodes='';
            for i=1:1:cm_const.num_nodes
                nodes=[nodes,cm_const.nodes(i).name];
                if i<cm_const.num_nodes
                    nodes=[nodes,','];
                end
            end
            % write the name of the nodes associated to teh center of mass
            tc_file=writefieldstring(tc_file,CMNodesTxt,nodes);
            % write the x coordinate
            string=cm_const.position(1).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.position(1).value)];
            end
            tc_file=writefieldstring(tc_file,CMxTxt,string);
            % write the y coordinate        
            string=cm_const.position(2).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.position(2).value)];
            end
            tc_file=writefieldstring(tc_file,CMyTxt,string);
            % write the z coordinate            
            string=cm_const.position(3).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.position(3).value)];
            end
            tc_file=writefieldstring(tc_file,CMzTxt,string);
            % write the rotation about x
            string=cm_const.orientation(1).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.orientation(1).value)];
            end
            tc_file=writefieldstring(tc_file,CMrxTxt,string);
            % write the rotation about y            
            string=cm_const.orientation(2).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.orientation(2).value)];
            end
            tc_file=writefieldstring(tc_file,CMryTxt,string);
            % write the rotation about z            
            string=cm_const.orientation(3).type;
            if strncmp(string,'fixed',size('fixed',2))
                string=[string,',',num2str(cm_const.orientation(3).value)];
            end
            tc_file=writefieldstring(tc_file,CMrzTxt,string);
        end
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file structure');
end