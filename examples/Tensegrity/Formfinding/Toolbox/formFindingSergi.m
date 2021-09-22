% Form-findingy method by S. Hernandez-Juan and J.M. Mirats-Tur
%
% Inputs:
%      filename: Name of the files describing the problem
%      input_paramas: Parametres of the constraints in the problem
%                     e.g., the position of the center of mass of
%                     the platform
% Outputs:
%       T: The tensegrity structure (this can be manipulated with
%          the functions in the Toolbox folder.
%    
function T=formFindingSergi(filename,input_params)
  
  % Interface to the form-finding method described in
  %      S. Hernandez-Juan and J.M. Mirats-Tur 
  %      A method to generate stable, collision free configurations for tensegrity based robots. 
  %      IEEE/RSJ International Conference on Intelligent Robots
  %      and Systems, pp. 3769-3774, 2008.
  % The actual implementation of this method is in the Sergi
  % sub-folder and it is directly provided by Sergi Hernandez-Juan
    
  % Initialize the Tensegrity collision class
  ten_col=tencol();
  [ten_col,path]=loadoptparams(ten_col,filename);
  
  % check wether the C functions exist or not
  if exist([path ten_col.const_file '.c'])==0 % constraint C file does not exist, generate it
    ten_col=generateconstraints(ten_col);
    ten_col=generateconstfile(ten_col,path,[ten_col.const_file '.c']);
  end
  if exist([path ten_col.func_file '.c'])==0 % cost function C file does not exist, generate it
    ten_col=generatefunction(ten_col);
    ten_col=generatefuncfile(ten_col,path,[ten_col.func_file '.c']);
  end
  if exist([path ten_col.grad_file '.c'])==0 % gradient C file does not exist, generate it
    ten_col=generategradient(ten_col);
    ten_col=generategradfile(ten_col,path,[ten_col.grad_file '.c']);
  end
  
  % get the tensegrity topology and constraints
  ten=ten_col.const;

  % Define the static part of the 'T' output structure from the
  % information in the input files.
  I=dbstack();
  T.name=I(end).name(7:end);
  
  T.bars=[];
  T.stiffnessBar=[];
  T.strings=[];
  T.stiffnessString=[];
  T.prismaticBars=[];
  T.ctRestString=[];
  for i=1:1:size(ten.edges,2)
    edge=ten.edges(i);
    origin_node=sscanf(edge.origin,'node%d');
    end_node=sscanf(edge.end,'node%d');
    if(strcmp(edge.type,'strut')~=0)
      if(end_node>origin_node)
        T.bars=[T.bars {[origin_node end_node]}];
      else
        T.bars=[T.bars {[end_node origin_node]}];
      end
      T.stiffnessBar=[T.stiffnessBar edge.stiffness.value];
      if(strcmp(edge.rest_length.type,'actuated')~=0)
        T.prismaticBars=[T.prismaticBars 1];
      else
        T.prismaticBars=[T.prismaticBars 0];
      end
    else
      if(end_node>origin_node)
        T.strings=[T.strings {[origin_node end_node]}];
      else
        T.strings=[T.strings {[end_node origin_node]}];  
      end
      T.stiffnessString=[T.stiffnessString edge.stiffness.value];
      if (strcmp(edge.rest_length.type,'fixed')~=0)
        T.ctRestString=[T.ctRestString true];
      else
        T.ctRestString=[T.ctRestString false];
      end
    end
  end
  
  T.equilibriumNode=[];
  for i=1:1:size(ten.nodes,2)
    node=ten.nodes(i);
    if (strcmp(node.position(1).type,'fixed')~=0) && (strcmp(node.position(2).type,'fixed')~=0) && (strcmp(node.position(3).type,'fixed')~=0)
      T.equilibriumNode=[T.equilibriumNode false];
    else
      T.equilibriumNode=[T.equilibriumNode true];
    end  
  end
  
  T.nBars=size(T.bars,2);
  T.nStrings=size(T.strings,2);
  T.nPoints=2*T.nBars;
  
  % Execute the iterative optimization process to find a solution
  done=0;
  while(done==0)
    ini=rand(1,getnumoptvar(ten_col));      
    penalty=ten_col.penalty(1);    
    param=[input_params,penalty];    
    try
      final=0;
      tic
      while final==0
        ten_col=optimize(ten_col,ini,param);
        try
          ten_col=checkconstraints(ten_col,param);
          final=1;
        catch
          param(size(param,2))=param(size(param,2))*2;
          ini=ten_col.solution
        end
      end
      if(isnan(ten_col.solution(1)))
        done=0;
      else
        ini=ten_col.solution
        ten_sol=get_solution(ten_col,param,ten_col.solution);
        done=1;
        toc        
      end
    catch
      error=lasterror;
      errordlg(error.message);
    end  
  end
  
  % Store the solution in the corresponding fields of the 'T'
  % output structure
  T.compression=[];
  T.lengthBar=[];
  T.tension=[];
  T.lengthString=[];
  for i=1:1:size(ten.edges,2)
    edge=ten_sol.edges(i);
    if(strcmp(edge.type,'strut')~=0)
      T.compression=[T.compression edge.stiffness.value*(edge.rest_length.value-edge.length.value)];
      T.lengthBar=[T.lengthBar edge.length.value];
    else
      T.tension=[T.tension edge.stiffness.value*(edge.length.value-edge.rest_length.value)];
      T.lengthString=[T.lengthString edge.length.value];
    end
  end
  
  % re-compute the rest so that they are exact
  T.restBar=T.lengthBar+T.compression./T.stiffnessBar;
  T.restString=T.lengthString-T.tension./T.stiffnessString;
  
  % do not add normalization of forces
  T.pretension=0;

  T.p=[];
  for i=1:1:size(ten.nodes,2)
    node=ten_sol.nodes(i);
    T.p=[T.p ; node.position(1).value ; node.position(2).value ; node.position(3).value];
  end
  