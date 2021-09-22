function [m,vc,va,contacts, object object_R,axes] = Init(fname)
%
% This function reads the files with the data needed for the determination of
% the indeces: force-closure, manipulability or both.
%
% For the moment, the contact friction model is defined here, but should be in 
% the script that determines J and G.
%

  nf = 3; % number of fingers
  vf = 3; % number of components per finger
  nc = 3; % number of contacts
  vc = 7; % numbers of components per contact [point normal length]
  va = 6; % number of components per joint [point vector]
  vl = 6; % number of variables per link [vector_u vector_v]
  
  
  % read information about the contact
  fprintf(['Reading contact information: ' fname '_with_contacts_with_eigens_center.links\n']);
    full = load([fname '_with_contacts_with_eigens_center.links']); % last columns, in the order of fingers in .world file
    
    [m,n] = size(full);
    
    contacts = full(:,n-(nc*(vc)-1):n);
    object = full(:,n-(nc*vc+nf*vf+2):n-(nc*vc+nf*vf));
    object_R = full(:,10*vl+1:10*vl+6);
  
  % read information about the axes
  fprintf(['Reading joint information: ' fname '_with_contacts_with_eigens_center.axes\n']);
    axes = load([fname '_with_contacts_with_eigens_center.axes']); %  in the order of appearance in .world file
  
  
%  % CONTACT MODELS
%  %free model
%  %Hn = zeros(6,6);
%  %frictionless model
%  %Hpwof = [ [1 0 0 ; zeros(2,3)] zeros(3,3); zeros(3,6) ];
%  %hard friction model
%  Hhf = [eye(3) zeros(3,3); zeros(3,6)];
%  %soft friction model
%  %Hsf = [eye(3) zeros(3,3); zeros(3,3) [1 0 0 ; zeros(2,3)] ];
%  %rigid model
%  %Hr = eye(6);
%  
%  % model in contact 1
%  H1 = Hhf;
%  
%  % model in contact 2
%  H2 = Hhf;
%  
%  % model in contact 3
%  H3 = Hhf;

%  % full selection matrix
%  H = blkdiag(H1,H2,H3); 
