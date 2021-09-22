function new_penalty=TenUpdatePenalty(old_penalty)
% updates the penalty value
% this function is used to update the value of the penalty coefficient in
% each optimization iteration. The name of this function is used as a
% function handle to the function to be executed, which make it possible to
% change the cost function update function without modifying the main
% optimization code.
%
% The template for other penalty update functions is:
% 
%           new_value=<function name>(old_value);
%
% new_penalty=TenUpdatePenalty(old_penalty) returns the updated value for
% the penalty coefficient.
% 
% See also tenopt
new_penalty=old_penalty*2;

            