function [int,file]=readfieldint(file,field)
% reads an integer value from the file associated to the object
% this function reads an integer value following the field identifier from 
% the file associated ot the object.
%
% [int,file]=readfieldint(file,field) return a modified version of the
% file object passed as argument after reading the real value from the
% file, as well as the integer following the field identifier text.
%
% field must be a string with a text which would be put before the desired
% string ('' can be used if no tag is required). The file object must be
% initialized before calling this function.
% 
% See also file, readfield

if isa(file,'file')
    try
        [field_out,file]=readfield(file,field);
        int=uint32(str2num(field_out));
    catch
        rethrow(lasterror);
    end
else
    error('file - Invalid file structure');
end
