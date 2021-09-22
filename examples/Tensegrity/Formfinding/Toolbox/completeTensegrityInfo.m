% Defines some of the fields of the tensegrity structure
% that can be defined automatically from the user input
%
% This is used to reduce the user input to a minimum.
% This is only used when solving the form-finding analyzing
% the transposed rigidity matrix (i.e, when the position of
% the nodes are know).
%
% Inputs
%     T: The partially defined tensegrity structure
% Outputs
%     T: The updated tensegrity structure.
%
function T=completeTensegrityInfo(T)
 
  % If the name is already given -> this function has
  % been used before.
  if ~isfield(T,'name')
    I=dbstack();
    T.name=I(end).name(7:end);
    
    % Default pretension is 1
    if ~isfield(T,'pretension')
      T.pretension=1;
    end
    
    % Number of bars
    T.nBars=size(T.bars,2);
    
    % Number of points
    T.nPoints=2*T.nBars;
    
    % Number of strings
    T.nStrings=size(T.strings,2);
    
    if isfield(T,'p')
      % length of bars
      T.lengthBar=zeros(1,T.nBars);
      for i=1:T.nBars
        a=T.bars{i}(1);
        b=T.bars{i}(2);
        T.lengthBar(i)=norm(T.p(ndx(a))-T.p(ndx(b)));
      end
      
      % length of the strings
      T.lengthString=zeros(1,T.nStrings);
      for i=1:T.nStrings
        a=T.strings{i}(1);
        b=T.strings{i}(2);
        T.lengthString(i)=norm(T.p(ndx(a))-T.p(ndx(b)));
      end
    end
  end