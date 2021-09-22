function [string,file]=readfieldstring(file,field)
% reads a string from the file associated to the object
% this function reads the string following the field identifier from the file
% associated ot the object.
%
% [string,file]=readfieldstring(file,field) return a modified version of the
% file object passed as argument after reading the string from the file, as
% well as the string following the field identifier text.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file, readfield

if isa(file,'file')
    try
        [string,file]=readfield(file,field);
    catch
        rethrow(lasterror);
    end
else
    error('file - Invalid file structure');
end

