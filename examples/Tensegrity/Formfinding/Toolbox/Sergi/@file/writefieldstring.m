function file=writefieldstring(file,field,string)
% writes a string into the file associated to the object
% this function writes the string following the field identifier to the file
% associated to the object.
%
% file=writefieldstring(file,field,string) return a modified version of the
% file object passed as argument after writing the string into the file.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file, writefield

if isa(file,'file')
    try
        file=writefield(file,field,string);
    catch
        rethrow(lasterror);
    end
else
    error('file - Invalid file structure');
end
