function t=setdimension(t,dimension)
% sets the dimension of the work space of the tensegrity structure
% this private functions change the current dimension of the work space of
% the tensegrity. The allowd values are 2 and 3.
%
% t=setdimension(t,dimension) returns a modified version of the tensegrity 
% structure with the new dimension.
%
% The tensegrity object must be initialized before calling this function
% and the dimension parameter must be an integer equal to either 2 or 3.
%
% See also tensegrity

if isa(t,'tensegrity')
    if (~isnumeric(dimension))
        error('tensegrity - The dimension value must be an integer');
    else
        if (dimension<1 || dimension>3)
            error('tensegrity - Invalid dimension value');
        else
            t.dimension=dimension;
        end
    end
else
    error('tensegrity - Invalid tensegrity structure');    
end
