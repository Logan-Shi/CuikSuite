function t=setfilename(t,filename)
% private function to set the filename of the tensegrity topology
% this function may be used internally inside the class to modify the
% filename of the topology file associated to the structure
%
% t=setfilename(t,filename) returns the tesnegrity object updated with the
% filename of the topology file.
%
% The tensegrity object (t) must initialized before calling this function.
% filename must be a string terminated by .ten.
%
% See also tensegrity

if isa(t,'tensegrity')
    if ischar(filename)
        t.filename=filename;
    else
        error('tensegrity - Invalid filename');
    end
else
    error('tensegrity - Invalid tensegrity structure');
end