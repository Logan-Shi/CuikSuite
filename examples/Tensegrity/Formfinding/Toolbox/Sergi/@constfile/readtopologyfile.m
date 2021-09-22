function [ten_top,constfile]=readtopologyfile(constfile)
% reads the topology filename from the constraints file
% this function reads the name of the topology file associated to the
% constraints from the file. 
%
% [ten_top,ct_file=readtopologyfile(ct_file) returns a modified version of
% the tenconst object passed as argument after reading the information from
% the file and a string with the name of the topology file.
%
% The tenconst file object must be initialized before calling this function.
%
% See also constfile,tenconst,readfieldstring

TopFileTxt='Topology File: ';
if isa(constfile,'constfile')
    try
        [ten_top,constfile]=readfieldstring(constfile,TopFileTxt);
    catch
        rethrow(lasterror);
    end
else
    error('constfile - Invalid constraint file');
end
