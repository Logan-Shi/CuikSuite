function file=writefieldreal(file,field,real)
% writes a real value into the file associated to the object
% this function writes a real value following the field identifier to the 
% file associated to the object.
%
% file=writefieldreal(file,field,real) return a modified version of the
% file object passed as argument after writing the real value into the file.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file, writefield

if isa(file,'file')
    string=num2str(real);
    try
        file=writefield(file,field,string);
    catch
        rethrow(lasterror);
    end
else
    error('file - Invalid file structure');
end
