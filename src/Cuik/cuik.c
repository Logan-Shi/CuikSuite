
#include "cuiksystem.h"
#include "parameters.h"

#include "defines.h"
#include "error.h"
#include "box_list.h"
#include "filename.h"
#include "random.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>
 
#if (_USE_MPI)
  #include <mpi.h>
  #include <unistd.h>
#endif


/** \file cuik.c
    \brief Main body of the \ref cuik.c "cuik" application.
 
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuik    [label="cuik"    color="#99ff99" shape=ellipse ];
      
      param   [label="param"   color="#ff9999"];
      kin     [label="cuik"    color="#ff9999"];
      sol     [label="sol"     color="#ff9999"];
      state   [label="state"   color="#ff9999"];

      param -> cuik
      kin -> cuik
      cuik -> sol
      cuik -> state
      state -> cuik
    }
    \enddot
    </center>

    This is the \b CuikSuite application for position analysis. 
    <br>
    <br>
    If CuikSuite is compiled with MPI=1 (see CMakeList.txt in the main CuikSuite directory)
    <b>cuik</b> will be prepared to take advantage of multi-processors systems. 
    To distribute the execution among several processors you should use the 
    <em>rmpicuik</em> script (check the scripts directory).
    <br>
    Be aware that even if you compile with MPI=1, 
    if you execute this application and not <em>rmpicuik</em>, the execution will use 
    only one processor.
    <br>
    <br>
    If a <em>.state</em> file exists for the problem at hand, <b>cuik</b> will resume
    the execution from this saved state. If you want to start from scratch, remove the
    <em>.state</em> file. State files are only present if the execution of <b>cuik</b>
    on a given problem was, for some reason, interrupted. If <b>cuik</b> terminates 
    properly it takes care of removing the state file for the problem at hand.
    <br>    
    <br>
    This application take as inputs
    - A set of equations in a <A href="../../examples/4b.cuik"><em>.cuik</em></a> file.
    The equations can be hand-coded or can be generated from abstract problem descriptions
    (i.e.,<A href="../../examples/TestPlan1/test1.world">world</a> files using
    \ref cuikequations.c "cuikequations")
    - A set of parameters in a <a href="../../examples/4b.param"><em>.param</em></a> file. 
    Those parameters overide the ones in the 
    <a href="../../share/default.param"><em>default</em></a> parameter file.
    .

    <br>
    <br>
    When <em>USE_MPI</em> is 0 and <em>DEBUG</em> is 1, the execution of 
    <b>cuik</b> generates lines like
    <br>
    - <0.0116886 1>[7]...  -> <3.19456e-06 0.5>b[4]
    .

    <br>
    Which means that <b>cuik</b> processed a box of volume 0.0116886 and size 1
    that was generated after 7 bisections and after iterating three times (this is
    the meaning of the tree dots after the "[7]") the
    <em>ReduceBox</em> procedure (see our 
    <a href="http://www-iri.upc.es/english/publiproject.php?proj=44">papers </a>
    for more details) the result
    is a box of volume 3.19456e-06 and size 0.5 that is bisected along dimension 4.<br>
    Small enough boxes (i.e., smaller that <em>SIGMA</em>) 
    are not bisected but considered solutions. In this case,
    the output line ends with and <em>s</em> or with and <em>S</em>, the later 
    corresponding to the case where the box is verified to include a solution.<br><br>
    When <em>USE_MPI</em> is 1 and the execution is launched via the <em>rmpicuik</em> 
    script the output is slightly different. We have lines like
    <br>
    - b<4.29014e+12, 2, 8>-> 31
    .

    <br>
    that mean that a box of volume 4.29014e+12 and size 2 generated after 8 bisections
    is send to processor number 31 for reduction. Then, we also have lines of the form
    <br>
    - b[16](t=1)-><1.03916e+09 2>b[2]
    .

    <br>
    which means that the main scheduler received a box back from processor 16 and that,
    after reduction, the box has volume 1.03916e+09 and size 2 and that it has been
    split along dimension 2. If, after the process of the box it result empty, the
    output line is of the form
    <br>
    - b[16](t=1)-> e
    . 

    <br>
    and solution boxes are not bisected but marked with and <em>s</em>.
    <br>
    <br>
    The output of <b>cuik</b> is a <a href="../../examples/4b.sols" >.sol</a> file. 
    If the position analysis problem at hand has isolted solutions, the output 
    of <B>cuik</B> will be a set of non-overlaping boxes, in
    general, one for each solution. If the problem has a continuous set of
    solutions, the output boxes bound this continuous set.
    See the 
    <a href="http://www-iri.upc.es/groups/gmr/cuikweb/benchmarks.html">benchmarks</a>
    for examples of both type of outputs.
    <br>
    The <em>.sol</em>  file includes the compilation flags,
    the parameters used for the <b>cuik</b> execution, a copy of
    the <em>.cuik</em> input file, and a list of solutions where each solution is of the
    form 
    <br>
    - 281 (0.000929312):{ 6  st2:[-0.901387818866,-0.87332428828] ct2:[-0.487139289629,-0.433012701892] st3:[0.87332428828,0.901387818866] ct3:[0.433012701892
    ,0.487139289629] st4:[-0.000523712590637,0.00052364116326] ct4:[-1,-0.999999862237] }
    .
    <br>
    indicanting that this is solution number 281, that the error of the center of the 
    box when  replaced in the set of equations is 0.000929312, that the box has 6 
    variables and the range for each variable. Finally, the  <em>.sol</em>  file also 
    includes a set of statistics on the  execution (execution time, number of solution
    boxes, etc.).

    <br>
    Execute the application without parameters to get a short help on how to 
    use <b>cuik</b>.

    \sa cuiksystem.h cuiksystem.c
*/

/** 
   \brief Main body of the \b cuik application.

   Main body of the \b cuik application.

   Use:
      - \b cuik \e problem_name.cuik
      .
   where
      - \e problem_name contains the kinematic equations
      .

   The \e .cuik extension is optional.
   
   \param argc Number of elements in the command line that starts the application (i.e., the
               \b cuik command itself and its arguments).
   \param arg Strings with the arguments.
   
   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not.
*/
int main(int argc, char **arg)
{
  signed int np=1,p=0;     /* The default mode is to run in one processor */

  FILE *f_out;             /* File where the solutions are printed as they 
			      are found */

  FILE *f_state;           /* File from where we try to recover the execution
			      state of cuik (this is used to continue execution
			      after a crash) */

  #if (!_QUIET)
    FILE *f_in;            /* Used to read-and-print the equation input 
			      file in the output file */
  #endif

  Tfilename fcuik;
  Tfilename fparam;
  Tfilename fsols;
  Tfilename fstate;

  TCuikSystem cuiksystem;  /* The set of variables and equations */
  Tparameters parameters;  /* Parameters used in the Cuik process */

  boolean restart;         /* Restart from a state file */
  unsigned int ri;

  #if (_USE_MPI)
    unsigned int i;
    unsigned int fileflag_in;
    MPI_Status status;
    char name[MPI_MAX_PROCESSOR_NAME+1];
    signed int len;

    MPI_Init(&argc,&arg);

    /* Set up a new Error handler */
    //MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

    MPI_Comm_rank(MPI_COMM_WORLD,&p);  /*number of this process*/
    MPI_Comm_size(MPI_COMM_WORLD,&np); /*total number of processes*/
  #endif

  if (argc>1)
    {
      ri=(unsigned int)time(NULL);
      //ri=1465223267;
      randomSet(ri);
      
      /*Init parameters*/
      CreateFileName(NULL,arg[1],NULL,PARAM_EXT,&fparam);
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);

      /*Read the problem from file*/
      CreateFileName(NULL,arg[1],NULL,CUIK_EXT,&fcuik);
      InitCuikSystemFromFile(&parameters,GetFileFullName(&fcuik),&cuiksystem);

      #if (_USE_MPI)
        /* Update the cuiksystem for all the processors (in complex files this can
	   take a while and its better to do it before starting to process boxes */
        VerifyCuikSystem(&parameters,&cuiksystem);
      #endif

      /*Check if a state file is available*/
      if (p==0)
	{
	  CreateFileName(NULL,arg[1],NULL,STATE_EXT,&fstate);
	  f_state=fopen(GetFileFullName(&fstate),"rb");
	  if (f_state)
	    {
	      restart=TRUE;
	      fclose(f_state);
	    }
	  else
	    restart=FALSE;
	}
      else
	restart=FALSE;
      

      /*Check if we can create the output file*/
      f_out=stdout; /* the default is stdout for all processes. 
		       Only process 0 has special output file */
      if (p==0)
	{
	  CreateFileName(NULL,arg[1],NULL,SOL_EXT,&fsols);
	  if (restart)
	    f_out=fopen(GetFileFullName(&fsols),"a"); /*append data to an already existing file*/
	  else
	    f_out=fopen(GetFileFullName(&fsols),"w"); /*start a brand new output file*/

	  if (!f_out)
	    Error("Could not open main output file");
	}

      #if (!_QUIET)
        /*While the rest of processors read the parameter file, the 
	  first processors stores data about the problem to be solved 
	  next in the output file*/
        if (p==0)
	  {
	    if (restart)
	      {
		fprintf(f_out,"\n==========================================================================\n");
		fprintf(f_out,"RESTARTING CUIK FROM A PREVIOUS EXECUTION STATE\n");
		fprintf(f_out,"WE ASSUME THAT THE .cuik FILE AND THE .param FILE HAVE NOT CHANGED");
		fprintf(f_out,"\n==========================================================================\n\n");
		fflush(f_out);
	      }
	    else
	      {
		fprintf(f_out,"\n==========================================================================\n");
		fprintf(f_out,"Random seed: %u",ri);
		fprintf(f_out,"\n==========================================================================\n");
		PrintParameters(f_out,&parameters);
	    
		/*Print the description of the problem to be solved*/
		fprintf(f_out,"\n==========================================================================\n");
		fprintf(f_out,"Equations from file: %s\n",GetFileFullName(&fcuik));
		f_in=fopen(GetFileFullName(&fcuik),"r");
		if (!f_in)
		  Error("Error opening input file");
		else
		  {
		    int c;

		    do { c=fgetc(f_in); if (c!=EOF) fprintf(f_out,"%c",c); } while(c!=EOF);
		    fclose(f_in);
		    fprintf(f_out,"\n"); 
		  }
	 
		fprintf(f_out,"\n==========================================================================\n");
		PrintCuikSystemWithSimplification(&parameters,f_out,&cuiksystem);
		fprintf(f_out,"\n==========================================================================\n");
	      }
	    fflush(f_out);
	  }
      #endif

      /* The main processors takes care of writing the solutions as they are 
	 found by the slaves */
      if ((p==0)&&(!restart))
	{ 
	  fprintf(f_out,"Cuik executed in %u processors\n",np);
	  fprintf(f_out,"SOLUTIONS (to input file %s):\n\n",GetFileFullName(&fcuik)); 
	  fflush(f_out);
	}

      if (np<3) /*single cpu execution -> Do not use parallel cuik*/
	{
	  if (p==0)
	    SolveCuikSystem(&parameters,restart,GetFileFullName(&fstate),
			    NULL,f_out,NULL,&cuiksystem); 
	}
      #if (_USE_MPI)
      else
	{
	  MPI_Get_processor_name(name,&len);

	  /*Execution on several cpu: one is the master and the rest are slaves*/
	  /*First we wait all the slaves to be ready. We do not want to send out boxes
	    if the slaves are not ready to receive them.*/
	  if (p==0)
	    {
	      fprintf(stdout,"Main scheduler running on %s\n",name);
	      fprintf(stdout,"Waiting all processes to read the param/cuik files\n"); 
	      fflush(stdout);
	      
	      for(i=1;i<(unsigned int)np;i++)
		{
		  while ((MPI_Recv(&fileflag_in,1,MPI_UNSIGNED,i,50+i,MPI_COMM_WORLD,&status)!=MPI_SUCCESS)&&
			 (fileflag_in!=i));
		  fprintf(stdout,"Ping from process %u received\n",i);
		  fflush(stdout);
		}

	      fprintf(stdout,"Starting scheduler\n");
	      fflush(stdout); 

	      MPI_SolveCuikSystem(&parameters,restart,GetFileFullName(&fstate),NULL,f_out,&cuiksystem); /* one master */
	    }
	  else
	    {
	      fprintf(stdout,"Starting sub-proces on processor %d running on %s\n",p,name);
	      fflush(stdout); 
	      /* Send a signal to the scheduler process (process number 0) indicating
		 that sub-process 'p' is ready to process boxes */
	      MPI_Ssend(&p,1,MPI_UNSIGNED,0,50+p,MPI_COMM_WORLD);

	      MPI_TreatBox(&parameters,&cuiksystem); /* and np-1 slaves */

	      printf("Killing sub-process %u\n",p);
	      fflush(stdout);
	    }
	}
      #endif

      if (p==0) 
	{
	  fprintf(f_out,"END OF THE SOLUTION FILE\n\n");
	  fclose(f_out);
	}

      /*Delete  the parameters and the equations*/
      DeleteParameters(&parameters);
      DeleteCuikSystem(&cuiksystem);
      
      DeleteFileName(&fcuik);
      DeleteFileName(&fparam);

      if (p==0)
	{
	  DeleteFileName(&fsols);
 
	  /*Remove the last state file generated*/
	  remove(GetFileFullName(&fstate));
	  DeleteFileName(&fstate);
	}
    }
  else
    {
      if (p==0) /* Only one error message */
	{
	  fprintf(stderr,"  Wrong number of parameters.\n");
	  fprintf(stderr,"  Use:\n");   
	  fprintf(stderr,"      cuik <problem file name>.cuik \n");
	  fprintf(stderr,"  where <problem file name> contains the kinematic equations\n");
	  fprintf(stderr,"    (the '.cuik' extension is not required)\n");
	}
    }

  #if (_USE_MPI)
    MPI_Finalize();
  #endif

  return(EXIT_SUCCESS);
}

