function f=file(varargin)
% the constructor for the file class
% this function is the constructor for the file class. It is used as the
% base class for all objects associated to files. It provides basic
% functions to read from and write to file strings and real and integer
% value preceeded by a tag identifier.
%
% f=file() returns a new object initialized by default.
%
% f=file(file) if file is an other file object, this function returns a 
% copy of that object
%
% f=file(filename) if filename is the name of an existing file, this 
% function returns a new object associated to the file which is openend in
% read and write mode.
%
% f=file(filename,mode) if filename is the name of an existing file, this
% function returns a new object associated to the file which is openend as 
% mode.
% 

switch nargin
    case 0
        % default constructor
        f.id=-1;% file identifier
        f.filename='none';% filename
        f.line=0;% current line
        f=class(f,'file');
    case 1
        if isa(varargin{1},'file')
            % copy constructor
            f=varargin{1};
        else
            % create a new object with a file associated
            if ischar(varargin{1})
                f.id=fopen(varargin{1},'r+');
                if f.id==-1
                    error('file - Error opening file');
                else 
                    f.filename=varargin{1};
                    f.line=0;
                    f=class(f,'file');
                end
            else
                error('file - Invalid argument type');
            end
        end
    case 2
        if ischar(varargin{1}) && ischar(varargin{2})
            % create a new object with a file associated            
            f.id=fopen(varargin{1},varargin{2});
            if f.id==-1
                error('file - Error opening file');
            else
                f.filename=varargin{1};
                f.line=0;
                f=class(f,'file');
            end
        else
            error('file - Invalid argument type');
        end
    otherwise
        error('file - Invalid number of arguments');
end