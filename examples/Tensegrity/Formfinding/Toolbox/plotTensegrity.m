% Plots a tensegriy structure.
% 
% Inputs:
%     T: The tensegrity structure to plot.
%
function plotTensegrity(T,varargin)

  clf;
  
  for i=1:T.nBars
    a=3*(T.bars{i}(1)-1);
    b=3*(T.bars{i}(2)-1);
    line([T.p(a+1) T.p(b+1)],[T.p(a+2) T.p(b+2)],[T.p(a+3) T.p(b+3)],'color','k','LineWidth',3);
  end
  
  if isfield(T,'extensionBars')
    n=size(T.extensionBars,2);
    for i=1:n
      a=3*(T.extensionBars{i}(1)-1);
      b=3*(T.extensionBars{i}(2)-1);
      line([T.p(a+1) T.p(b+1)],[T.p(a+2) T.p(b+2)],[T.p(a+3) T.p(b+3)],'color','k','LineWidth',3);
    end
  end
  
  for i=1:T.nStrings
    a=3*(T.strings{i}(1)-1);
    b=3*(T.strings{i}(2)-1);
    line([T.p(a+1) T.p(b+1)],[T.p(a+2) T.p(b+2)],[T.p(a+3) T.p(b+3)],'color','b','LineWidth',1);
  end

  axis equal;
  