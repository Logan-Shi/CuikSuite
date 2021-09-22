function [line,file]=readline(file)
% reads a line of text from a file
% this function reads a full line of text from the file associated to the 
% file object.
% 
% [line,file]=readline(file) return the line of text read from the file as
% a string and the modified version of the file object passed as argument
% after reading the line from the file.
% 
% See also file

if isa(file,'file')
    line=fgetl(file.id);
    file.line=file.line+1;
    while line(1)=='#'
        line=fgetl(file.id);
        file.line=file.line+1;
    end
else
    error('file - Invalid file structure');
end
