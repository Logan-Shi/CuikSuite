function tc_file=writeedgeconst(tc_file,ec)
% write the constraints associated to an edge into the constraints file
% this function writes the constraint information of an edge, which consists
% of:
%   * the stiffness constant
%   * the rest length
%
% tc_file=writeedgeconst(tc_file,ec) returns a modified version of the
% tenconst object passed as argument after writing the information into the
% file.
%
% The edge constraints must be included in a edgeconst object (ec) passed
% as argument and the tenconst file object must be initialized before
% calling this function.
% 
% see also constfile,tenconst,edgeconst,writefieldstring

if ~isa(ec,'edgeconst')
    error('constfile - Invalid tensegrity constraint structure');
end
if ~isa(tc_file,'constfile')
    error('constfile - Invalid tensegrity constraint file structure');
end    
% file tag text
KTxt='k:';
RestLengthTxt='d0:';
try
    tc_file=writefieldstring(tc_file,'',ec.name);
    % write the stiffness constant
    string=ec.stiffness.type;
    if strncmp(string,'fixed',size('fixed',2))
        string=[string,',',num2str(ec.stiffness.value)];
    end
    tc_file=writefieldstring(tc_file,KTxt,string);
	% write the rest length
    string=ec.rest_length.type;
    if strncmp(string,'fixed',size('fixed',2))
        string=[string,',',num2str(ec.rest_length.value(1))];
    else
        % if the rest length is not fixed, it must be bounded
        if strncmp(string,'actuated',size('actuated',2)) || strncmp(string,'passive',size('passive',2))
            string=[string,',(',num2str(ec.rest_length.value(1)),',',num2str(ec.rest_length.value(2)),')'];
        end
    end
    tc_file=writefieldstring(tc_file,RestLengthTxt,string);
catch
    rethrow(lasterror);
end