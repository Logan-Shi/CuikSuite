function file=writefieldint(file,field,int)
% write an integer value into the file associated to the object
% this function writes an integer value following the field identifier to the 
% file associated to the object.
%
% file=writefieldint(file,field,int) return a modified version of the
% file object passed as argument after writing the real value into the file.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file, writefield

if isa(file,'file')
    string=num2str(int);
    try
        file=writefield(file,field,string);
    catch
        rethrow(lasterorr);
    end
else
    error('file - Invalid file structure');
end
