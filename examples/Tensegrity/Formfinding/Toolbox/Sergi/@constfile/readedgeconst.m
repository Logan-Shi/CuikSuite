function [tc_file,ec]=readedgeconst(tc_file,ec)
% reads the constraints associated to an edge from the constraints file
% this function reads the constraint information of an edge, which consists
% of:
%   * the stiffness constant 
%   * the rest length.
%
% [tc_file,ec]=readedgeconst(tc_file,ec) returns a modified version of the
% tenconst object passed as argument after reading the information from the
% file, as well as the modified version of a edgeconst object with the new
% information read from the file.
%
% Both the edge constraint object (ec) and the tenconst file object must be
% nitialized before calling this function.
% 
% see also constfile,tenconst,edgeconst,readfieldstring

if ~isa(ec,'edgeconst')
    error('constfile - Invalid tensegrity constraint structure');
end
if ~isa(tc_file,'constfile')
    error('constfile - Invalid tensegrity constraint file structure');
end    
% file tag txt
KTxt='k:';
RestLengthTxt='d0:';
try
    % read the stiffnedd constant
    [stiffness_string,tc_file]=readfieldstring(tc_file,KTxt);
    if strncmp(stiffness_string,'fixed',size('fixed',2))
        value=str2num(stiffness_string(size('fixed,',2)+1:size(stiffness_string,2)));
        ec.stiffness=tenvar('fixed',[ec.name,'_k'],value);
    else
        if strncmp(stiffness_string,'passive',size('passive',2))
            ec.stiffness=tenvar('passive',[ec.name,'_k']);
        else
            if strncmp(stiffness_string,'parameter',size('parameter',2))
                ec.stiffness=tenvar('parameter',[ec.name,'_k']);
            else
                error('constfile - Invalid variable type');
            end
        end
    end
    % read the rest length
    [restlength_string,tc_file]=readfieldstring(tc_file,RestLengthTxt);
    if strncmp(restlength_string,'fixed',size('fixed',2))
        value=str2num(restlength_string(size('fixed,',2)+1:size(restlength_string,2)));
        ec.rest_length=tenvar('fixed',[ec.name,'_d0'],value);
    else
        if strncmp(restlength_string,'passive',size('passive',2))
            values=sscanf(restlength_string,'passive,(%f,%f)');
            ec.rest_length=tenvar('passive',[ec.name,'_d0'],values);
        else
            if strncmp(restlength_string,'parameter',size('parameter',2))
                ec.rest_length=tenvar('parameter',[ec.name,'_d0']);
            else
                if strncmp(restlength_string,'actuated',size('actuated',2))
                    values=sscanf(restlength_string,'actuated,(%f,%f)');
                    ec.rest_length=tenvar('actuated',[ec.name,'_d0'],values);
                else
                    error('constfile - Invalid variable type');
                end
            end
        end
    end
    % create an internal length variable
    ec.length=tenvar('passive',[ec.name,'_d']);
catch
    rethrow(lasterror);
end
