function ct_file=writetopologyfile(ct_file,ten_top)
% writes the topology filename into the constraints file
% this function writes the name of the topology file associated to the
% constraints. 
%
% ct_file=writetopologyfile(ct_file,ten_top) returns a modified version of
% the tenconst object passed as argument after writing the information into
% the file.
%
% The filename must be a string terminated by .ten and the tenconst file
% object must be initialized before calling this function.
%
% See also constfile,tenconst,writefieldstring

TopFileTxt='Topology File: ';
if isa(ct_file,'constfile')
    try
        ct_file=writefieldstring(ct_file,TopFileTxt,ten_top);
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file object');
end
