function to=generatefuncfile(to,filename)
% creates and compiles the optimization function c file
% this funcitons creates a c file with the optimization function and 
% compiles it in order to be used to rapidly evaluate the cost function in
% the optimization process
%
% to=generatefuncfile(to,filename) creates and compiles the c file
% corresponding to the optimization function. The name of the c file is stored
% internally to the object.
%
% The tensegrity optimization object must be initialized before calling
% this function and the filename must be a string terminate by *.c.
%
% See also: tenopt

file=fopen(filename,'w');
fprintf(file,'#include "mex.h"\n');
fprintf(file,'#include "math.h"\n\n');
fprintf(file,'void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[])\n{\n');
tc=to.const;
% crear les variables d'entrada
num_par=0;
num_opt=0;
old_par=sym('0');
new_par=sym('0');
for i=1:1:tc.num_var
    if strcmp(tc.variables(i).type,'parameter')
        num_par=num_par+1;
        old_par(num_par)=tc.variables(i).var;
        fprintf(file,'\tdouble p%d;\n',num_par);        
        new_par(num_par)=sym(['p',num2str(num_par)]);
    else
        if ~strcmp(tc.variables(i).type,'fixed')
            num_opt=num_opt+1;
            old_opt(num_opt)=tc.variables(i).var;
            fprintf(file,'\tdouble v%d;\n',num_opt);        
            new_opt(num_opt)=sym(['v',num2str(num_opt)]);
        end
    end
end
fprintf(file,'\tdouble *Variables;\n');
fprintf(file,'\tdouble *Parameters;\n');
fprintf(file,'\tdouble *Output;\n');
fprintf(file,'\tdouble t0;\n');
fprintf(file,'\tint num_var,num_param;\n');
% substituir les noves variables 
new_func=subs(to.function,[old_par,old_opt],[new_par,new_opt]);
% convertir les restriccions a codi C
const=ccode(new_func);
i=1;
text=['MapleGenVar',num2str(i)];
ocurrences=strfind(const,text);
fprintf(file,'\tdouble MapleGenVar%d;\n',i);
while size(ocurrences,1)~=0
    i=i+1;
    text=['MapleGenVar',num2str(i)];
    ocurrences=strfind(const,text);
    fprintf(file,'\tdouble MapleGenVar%d;\n',i);    
end
% comprovar els paràmetres d'entrada
fprintf(file,'\t/* check for the proper number of arguments */\n\tif(nrhs != 2)\n\t\tmexErrMsgTxt("Two inputs are required.");\n\tif(nlhs != 1)\n\t\tmexErrMsgTxt("One output required.");\n');
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
% retornar el valor de l'avaluació
fprintf(file,'\tplhs[0]=mxCreateDoubleMatrix(1,1,mxREAL);\n');
fprintf(file,'\tOutput=mxGetPr(plhs[0]);\n');
% escriure el codi de c
fprintf(file,'%s\n',const);
fprintf(file,'\tOutput[0]=t0;\n');
fprintf(file,'return;\n}\n');
% generar el fitxer mex
fclose(file);
to.func_file=strtok(filename,'.');
compile=['mex ',filename];
eval(compile);
