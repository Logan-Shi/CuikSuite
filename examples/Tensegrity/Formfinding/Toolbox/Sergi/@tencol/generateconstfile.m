function to=generateconstfile(to,path,filename)
% creates and compiles the constraint equations c file
% this funcitons creates a c file with the constraint equations and 
% compiles it in order to be used to rapidly check for constraint violations
% in the optimization process
%
% to=generateconstfile(to,filename) creates and compiles the c file
% corresponding to the constraint equations. The name of the c file is stored
% internally to the object.
%
% The tensegrity optimization object must be initialized before calling
% this function and the filename must be a string terminate by *.c.
%
% See also: tenopt

path='Toolbox/Sergi/';

c_filename=[path,filename];

file=fopen(c_filename,'w');
fprintf(file,'#include "mex.h"\n\n');
fprintf(file,'#include "math.h"\n\n');
fprintf(file,'void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])\n{\n');
tc=to.tenopt.const;
% crear les variables d'entrada
num_par=0;
num_opt=0;
old_par=sym('0');
new_par=sym('0');
tmp_env=tenenv();
[tmp_env,num_var,variables]=getvariables(to.tenopt.const);
for i=1:1:num_var
    if strcmp(variables(i).type,'parameter')
        num_par=num_par+1;
        old_par(num_par)=variables(i).var;
        fprintf(file,'\tdouble p%d;\n',num_par);        
        new_par(num_par)=sym(['p',num2str(num_par)]);
    else
        if ~strcmp(variables(i).type,'fixed')
            num_opt=num_opt+1;
            old_opt(num_opt)=variables(i).var;
            fprintf(file,'\tdouble v%d;\n',num_opt);        
            new_opt(num_opt)=sym(['v',num2str(num_opt)]);
        end
    end
end
fprintf(file,'\tdouble *Variables;\n');% vector de variables del problema
fprintf(file,'\tdouble *Parameters;\n');% vector de par??metres
fprintf(file,'\tdouble *new_const;\n');% vector de resultats
fprintf(file,'\tint num_var,num_param;\n');
% substituir les noves variables 
const=[];
if(to.tenopt.num_eq>0)
  const=[const;to.tenopt.eq_const.'];
end
if(to.tenopt.num_ineq>0)
  const=[const;to.tenopt.ineq_const.'];
end
if(to.num_env_eq>0)
  const=[const;to.env_eq_const.'];
end
if(to.num_env_ineq>0)
  const=[const;to.env_ineq_const.'];
end
new_const=subs(const,[old_par,old_opt],[new_par,new_opt]);
num_const=to.tenopt.num_eq+to.tenopt.num_ineq+to.num_env_eq+to.num_env_ineq;
% convertir les restriccions a codi C
code=ccode(new_const);
i=1;
text=['MapleGenVar',num2str(i)];
ocurrences=strfind(code,text);
fprintf(file,'\tdouble MapleGenVar%d;\n',i);
while size(ocurrences,1)~=0
    i=i+1;
    text=['MapleGenVar',num2str(i)];
    ocurrences=strfind(code,text);
    fprintf(file,'\tdouble MapleGenVar%d;\n',i);    
end
% eliminar la segona redirecci?? del resultat [i][0] -> [i]
for i=0:1:size(const,1)-1
    text1=['[',num2str(i),'][0]'];
    text2=['[',num2str(i),']'];
    code=strrep(code,text1,text2);
end
% comprovar els par??metres d'entrada
fprintf(file,'\t/* check for the proper number of arguments */\n\tif(nrhs != 2)\n\t\tmexErrMsgTxt("Two inputs are required.");\n\tif(nlhs != 1)\n\t\tmexErrMsgTxt("One output is required.");\n');
fprintf(file,'\t/* check that both inputs are row vectors*/\n\tif(mxGetM(prhs[0])!= 1 || mxGetM(prhs[1])!= 1)\n\t\tmexErrMsgTxt("The inputs must be row vectors.");\n');
fprintf(file,'\t/* get the length of each input vector */\n\tnum_var=mxGetN(prhs[0]);\n\tnum_param=mxGetN(prhs[1]);\n');
fprintf(file,'\t/* get pointers to the real and imaginary parts of the inputs */\n\tVariables=mxGetPr(prhs[0]);\n\tParameters=mxGetPr(prhs[1]);\n');
% assignar les variables d'entrada
for i=1:1:num_opt
    fprintf(file,'\tv%d=Variables[%d];\n',i,i-1);
end
% assignar les variables de control
for i=1:1:num_par
    fprintf(file,'\tp%d=Parameters[%d];\n',i,i-1);
end
% retornar el valor de l'avaluaci??
fprintf(file,'\tplhs[0]=mxCreateDoubleMatrix(%d,1,mxREAL);\n',num_const);
fprintf(file,'\tnew_const=mxGetPr(plhs[0]);\n');
% escriure el codi de c
fprintf(file,'%s\n',code);
fprintf(file,'return;\n}\n');
% generar el fitxer mex
fclose(file);
to.tenopt.const_file=strtok(filename,'.');
compile=['mex -Dchar16_t=uint16_T -outdir ',path,' ',c_filename];
eval(compile);

