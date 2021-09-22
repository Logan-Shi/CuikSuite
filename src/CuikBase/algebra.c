#include "algebra.h"

/** \file algebra.c

    Definition of the lineal algebra routines used in the CuikSuite.

    Simple 2D/3D operations are defined in \ref geom.c

    Basic vector/matrix operations are defined in \ref basic_algebra.c

    Here we define high level linear algebra routines. These are the
    only routines if we ever change the support linear algebra library
    (right now GSL is used).
*/

#include <math.h>
#include <string.h>

#if __APPLE__
  /** 
     \brief Interface to the dgpadm function in EXPOKIT

     Description taken directly from EXPOKIT:

     Computes exp(t*H), the matrix exponential of a general matrix in
     full, using the irreducible rational Pade approximation to the 
     exponential function exp(x) = r(x) = (+/-)( I + 2*(q(x)/p(x)) ),
     combined with scaling-and-squaring.
     
     \param ideg The degre of the diagonal Pade to be used. 
                 A value of 6 is generally satisfactory.
     \param m The size of the matrix H.
     \param t The time.
     \param H The matrix (in column major order!)
     \param ldh The leading size of H (distance between elements in the same row).
     \param wsp Workspace. This must be of size at least 4*m*m+ideg+1.
     \param lwsp The size of wsp.
     \param ipiv Workspace of size m. (index permutation?).
     \param iexph Index in wsp where the result is stored,
                  i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1)
		  Note that fortran buffers are indexed from 1 (have to substract one).
     \param ns Number of scaling-squaring used.
     \param iflag Information flag (0 = no problem).
  */
  extern void dgpadm(int *ideg,int *m,double *t,double *H,int *ldh,double *wsp,int *lwsp,int *ipiv,int *iexph,int *ns,int *iflag);

  /** 
     \brief Interface to the dgchbv function in EXPOKIT
     
     Description taken directly from EXPOKIT:

     dgchbv computes y = exp(t*H)*y using the partial fraction
     expansion of the uniform rational Chebyshev approximation
     to exp(-x) of type (14,14). H is a General matrix.
     About 14-digit accuracy is expected if the matrix H is negative
     definite. The algorithm may behave poorly otherwise. 

     \param m The size of the matrix H.
     \param t The time.
     \param H The matrix (in column major order!)
     \param ldh The leading size of H (distance between elements in the same row).
     \param y The vector. Overwritten in the output.
     \param wsp Workspace. This is of size 2*m*(m+2). The '2*' is because it strores
                complex numbers and not just doubles.
     \param iwsp Workspace of size m. (index permutation?)
     \param iflag Information flag (0 = no problem).
  */
  extern void dgchbv(int *m,double *t,double *H,int *ldh,double *y,double *wsp,int *iwsp,int *iflag);
#else
/** 
   \brief Interface to the dgpadm function in EXPOKIT

   Description taken directly from EXPOKIT:

   Computes exp(t*H), the matrix exponential of a general matrix in
   full, using the irreducible rational Pade approximation to the 
   exponential function exp(x) = r(x) = (+/-)( I + 2*(q(x)/p(x)) ),
   combined with scaling-and-squaring.

   \param ideg The degre of the diagonal Pade to be used. 
              A value of 6 is generally satisfactory.
   \param m The size of the matrix H.
   \param t The time.
   \param H The matrix (in column major order!)
   \param ldh The leading size of H (distance between elements in the same row).
   \param wsp Workspace. This must be of size at least 4*m*m+ideg+1.
   \param lwsp The size of wsp.
   \param ipiv Workspace of size m. (index permutation?).
   \param iexph Index in wsp where the result is stored,
                i.e., exp(tH) is located at wsp(iexph ... iexph+m*m-1)
		Note that fortran buffers are indexed from 1 (have to substract one).
   \param ns Number of scaling-squaring used.
   \param iflag Information flag (0 = no problem).
*/
extern void dgpadm_(int *ideg,int *m,double *t,double *H,int *ldh,double *wsp,int *lwsp,int *ipiv,int *iexph,int *ns,int *iflag);

/** 
   \brief Interface to the dgchbv function in EXPOKIT
   
   Description taken directly from EXPOKIT:

   dgchbv computes y = exp(t*H)*y using the partial fraction
   expansion of the uniform rational Chebyshev approximation
   to exp(-x) of type (14,14). H is a General matrix.
   About 14-digit accuracy is expected if the matrix H is negative
   definite. The algorithm may behave poorly otherwise. 


   \param m The size of the matrix H.
   \param t The time.
   \param H The matrix (in column major order!)
   \param ldh The leading size of H (distance between elements in the same row).
   \param y The vector. Overwritten in the output.
   \param wsp Workspace. This is of size 2*m*(m+2). The '2*' is because it strores
              complex numbers and not just doubles.
   \param iwsp Workspace of size m. (index permutation?)
   \param iflag Information flag (0 = no problem).
*/
extern void dgchbv_(int *m,double *t,double *H,int *ldh,double *y,double *wsp,int *iwsp,int *iflag);
#endif


/* A generic header that must be re-implemented for each linear algebra package.  */

/** 
   \brief Analyzes the kernel of a matrix.

   Analyzes the kernel of a matrix and extract different information, as
   requested by the caller. This function for many purposes

   \param nr Number of rows of the matrix (no transposed).
   \param nc Number of columns of the matrix (no transposed).
   \param mT The TRANSPOSED matrix stored as a vector.
   \param dof Expected dimension of the kernel. Can be zero if the getRank is TRUE.
   \param epsilon Values below epsilon are taken as zero.
   \param computeRank If the rank has to be computed from the kernel analysis. Otherwise
                      the information provided by 'dof' is taken as good.
   \param checkRank TRUE if an error has to be triggered if the rank is different from
                    the expected one. This only has effect if computeRank is FALSE.
   \param getT TRUE if we have to return a basis of the kernel.
   \param getBase TRUE if we have to return a basis of the input matrix (selected rows).
   \param singular TRUE if the matrix is singular (has more null eigen values than
                   the expected ones). Output.
   \param rank Rank of the input matrix. Computed in this function if computeRank
               is TRUE. Otherwise it is just deduced relying on the 'dof' parameter.
   \param IR The set of independent rows as a boolean vector with as many entries as
             rows in the input matrix and TRUE for the independent rows. The space
	     for this vector is allocated here but must be deallocated externally.
	     If the matrix is singular this contains the most likely basis of the
	     matrix (up to the numerical accuracy). Caution must be taken to use
	     this output in this case. This is only allocated if getBase is TRUE.
   \param T The output kernel. This is a (nc x dof) matrix (stored as a vector).
            The space for this matrix is allocated in this function but must be
	    de-allocated externally. Only allocated if getT is TRUE.

   \return 0 if all the operations are correct, 1 if the kernel is larger than
           expected, 2 if it is smaller than expected, 3 if there is an error
	   in the QR decomposition.
*/
unsigned int AnalyzeKernel(unsigned int nr,unsigned int nc,double *mT,
			   unsigned int dof,double epsilon,
			   boolean computeRank,boolean checkRank,boolean getT,boolean getBase,
			   boolean *singular,unsigned int *rank,boolean **IR,double **T);


/** 
   \brief Generates an orthonormal basis of the column space of a matrix.

   Orthonormalizes the columns of a matrix via QR decomposition.

   This is an alternative to \ref OrthonormalizeColumns which is probably
   faster and numerically more stable.

   \param epsilon Numerical accuracy.  Values below epsilon are taken as zero.
   \param nr Number of rows of the matrix to analyze.
   \param nc Number of columns of the matrxi to analyze.
   \param A The matrix whose columns space is analyzed. Please, note that this matrix
            is modified inside the function and that at the output it can not be
	    easily interpreted any more.
   \param IC Boolean array identifying the independent columns in A.
             Allocated internally.
   \param nrT Number of rows of the orthonormal basis. It is \e nr in all the cases.
   \param ncT Number of columsn of the orthonormal basis. It can be lower than \e nc.
              This is the number of TRUE values in \e IC.
   \param T The computed orthonormal basis allocated internally and stored as a vector.
*/
unsigned int BasisColumnSpace(double epsilon,unsigned int nr,unsigned int nc,double *A,
			      boolean **IC,
			      unsigned int *nrT,unsigned int *ncT,double **T);


/* BEGIN GSL IMPLEMENTATION */

#if _GSL

/** 
    \brief Prints a GSL vector.

    Prints a GSL vector. This is used when debugging
    the GSL-based code.

    \param f The file where to print the vector.
    \param label Name of the vector. Possibly NULL.
    \param v The vector.
*/
void PrintGSLVector(FILE *f,char *label,gsl_vector *v);

/** 
    \brief Prints a GSL permutation.

    Prints a GSL permutation. This is used when debugging
    the GSL-based code.

    \param f The file where to print the vector.
    \param label Name of the vector. Possibly NULL.
    \param p The permutation.
*/
void PrintGSLPermutation(FILE *f,char *label,gsl_permutation *p);

/** 
    \brief Prints a GSL matrix.

    Prints a GSL matrix. This is used when debugging
    the GSL-based code.

    \param f The file where to print the matrix.
    \param label Name of the matrix. Possibly NULL.
    \param M The matrix.
*/
void PrintGSLMatrix(FILE *f,char *label,gsl_matrix *M);


/******************************************************************/
/*               Private function definitions                     */

unsigned int AnalyzeKernel(unsigned int nr,unsigned int nc,double *mT,
			   unsigned int dof,double epsilon,
			   boolean computeRank,boolean checkRank,boolean getT,boolean getBase,
			   boolean *singular,unsigned int *rank,boolean **IR,double **T)
{
  unsigned int err;

  #if (_DEBUG<2)
    gsl_set_error_handler_off();
  #endif

  if (dof==nc)
    {
      /* Trivial case of a system without equations. We take this into account for completeness, but
         this function should never be used in this case. */
      *singular=FALSE;
      *rank=0;

      if ((getT)&&(nc>0))
	{
	  gsl_matrix_view vT;

	  NEW(*T,nc*dof,double);
	  vT=gsl_matrix_view_array(*T,nc,dof);
	  gsl_matrix_set_identity (&(vT.matrix));
	}
      else
	*T=NULL;

      if ((getBase)&&(nr>0))
	{
	  unsigned int i;

	  NEW(*IR,nr,boolean);
	  for(i=0;i<nr;i++)
	    (*IR)[i]=FALSE;
	}
      else
	*IR=NULL;

      err=0;
    }
  else
    {
      gsl_matrix_view At;
      gsl_vector *tau;
      gsl_permutation *p;
      int signum;
      gsl_vector *norm;

      /* Define A^T */
      At=gsl_matrix_view_array(mT,nc,nr);

      /* Extra space for the QR decomposition of At */
      tau=gsl_vector_alloc((nr<nc?nr:nc));
      p=gsl_permutation_alloc(nr);
      norm=gsl_vector_alloc(nr);

      /* Decompose the matrix, with column pivoting to get the kernel. Note that
	 the permutation is not relevant for the kernel P*A*v=0 -> A*v=0  */
      err=gsl_linalg_QRPT_decomp(&(At.matrix),tau,p,&signum,norm);

      if (err)
	{
	  *singular=TRUE;
	  *rank=NO_UINT;
	  *T=NULL;
	  *IR=NULL;
	  err=3; /* Our error code for decomposition error */
	}
      else
	{
	  unsigned int k,mrc;
	  double r;

	  /***********************************************/
	  /* At is nc x nr */
	  /* Q is nc x nc */
	  /* R is nc x nr -> R^t is nr x nc */

	  /* At=Q R P^t -> A= P R^t Q^t -> P^t A Q = R^t
	     Thus, the rows of R (columns of R^t) that are zero
	     indicate columns of Q that define part of the kernel.
	     Moreover, the norm of the rows of R indicate how far
	     is from defining a new kernel basis vector. Sinc R
	     is triangular the norm of the row is the norm from
	     the diagonal to the end of the row (nr entries) */

	  mrc=(nr<nc?nr:nc);

	  if (computeRank)
	    {
	      /* Rank = number of not-null rows of R */
	      /* The rank can not be larger than the mrc=min(nr,nc) */
	      *rank=0;
	      for(k=0;k<mrc;k++)
		{
		  /* Get the norm of row k of R from the diagonal to the end of the row */
		  r=NormWithStride(nr-k,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(k,k,nc,nr)]));
		  if (r>epsilon)
		    (*rank)++;
		}
	      if (dof==0)
		{
		  *singular=FALSE;
		  /* temporary set 'dof' form '*rank' */
		  dof=nc-*rank;
		}
	      else
		*singular=((nc-dof)!=*rank);
	    }
	  else
	    {
	      if (dof==0)
		Error("Null 'dof' parameter in AnalyzeKernel");
	      if (dof>nc)
		Error("We can not have more 'dof' than variables");

	      *rank=nc-dof;

	      /* Check if row *rank-1 of R is actually not null. */
	      r=NormWithStride(nr-(*rank-1),(ROW_MAJOR?1:nc),&(mT[RC2INDEX(*rank-1,*rank-1,nc,nr)]));
	      *singular=(r<epsilon);

	      if (checkRank)
		{
		  if (*singular)
		    err=1; //Error("Singular point (increase N_DOF? Decrease EPSILON?)");

		  /* Checking row '*rank' is actually null. */
		  r=NormWithStride(nr-*rank,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(*rank,*rank,nc,nr)]));
		  if (r>epsilon)
		    err=2; //Error("Non-null kernel vector (decrease N_DOF? Increase EPSILON?)");
		}
	    }

	  #if (_DEBUG>0)
	    if ((dof>0)&&(!computeRank)&&(getT)&&(!getBase))
	      {
		printf("  E=[ ");
		for(k=*rank;k<mrc;k++)
		  {
		    r=NormWithStride(nr-k,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(k,k,nc,nr)]));
		    printf("%.16f ",r);
		  }
		printf("];\n");
	      }
	  #endif

	  /* If requested, we define T and IR, even if the chart is singular. In this case
	     we return the most likely T and IR. */
	  if (getT)
	    {
	      unsigned int i;
	      gsl_vector_view vT;

	      /* The kernel are the last 'dof' columns of Q */
	      /* Note that P^t A q_i = 0 <-> A q_i = 0 */
	      NEW(*T,nc*dof,double);
	      for(k=*rank,i=0;k<nc;k++,i++)
		{
		  vT=gsl_vector_view_array_with_stride(&((*T)[RC2INDEX(0,i,nc,dof)]),(ROW_MAJOR?dof:1),nc);
		  gsl_vector_set_basis(&(vT.vector),k);
		  gsl_linalg_QR_Qvec(&(At.matrix),tau,&(vT.vector));
		}
	    }
	  else
	    *T=NULL;

	  if (getBase)
	    {
	      NEW(*IR,nr,boolean);
	      for(k=0;k<nr;k++)
		(*IR)[k]=FALSE;
	      for(k=0;k<*rank;k++)
		(*IR)[gsl_permutation_get(p,k)]=TRUE;
	    }
	  else
	    *IR=NULL;
	}
      gsl_vector_free(norm);
      gsl_vector_free(tau);
      gsl_permutation_free(p);
    }
  return(err);
}

unsigned int BasisColumnSpace(double epsilon,unsigned int nr,unsigned int nc,double *A,
			      boolean **IC,
			      unsigned int *nrT,unsigned int *ncT,double **T);
{
  unsigned int err;
  gsl_matrix_view mA;
  gsl_vector *tau;
  gsl_permutation *p;
  int signum;
  gsl_vector *norm;
  gsl_vector_view vT;
  unsigned int k,m;
  double r;

  /* Define matrix A */
  mA=gsl_matrix_view_array(A,nr,nc);

  /* Extra space for the QR decomposition of At */
  m=(nr<nc?nr:nc)
  tau=gsl_vector_alloc(m);
  p=gsl_permutation_alloc(nc);
  norm=gsl_vector_alloc(nc);

  /* Decompose the matrix, with column pivoting.  */
  err=gsl_linalg_QRPT_decomp(&(mA.matrix),tau,p,&signum,norm);

  if (err)
    {
      /* Cancel output information */
      *nrT=0;
      *ncT=0;
      *T=NULL;
      *IC=NULL;
    }
  else
    {
      /* Count the number of independent columms and identify them */
      NEW(*IC,nc,boolean);
      for(k=0;k<nc;k++)
	(*IC)[k]=FALSE;

      *nrT=nr;
      *ncT=0;
      for(k=0;k<m;k++)
	{
	  /* Get the norm of row k of R to the diagonal */
	  r=NormWithStride(k+1,(ROW_MAJOR?nc:1),&(A[RC2INDEX(0,k,nr,nc)]));
	  if (r>epsilon)
	    {
	      (*ncT)++;
	      (*IC)[gsl_permutation_get(p,k)]=TRUE;
	    }
	}

      /* Now reconstruct the basis */
      NEWZ(*T,(*nrT)*(*ncT),double);
      for(k=0;k<*ncT;k++)
	{
	  (*T)[RC2INDEX(k,k,*nrT,*ncT)]=1.0;
	  vT=gsl_vector_view_array_with_stride(&((*T)[RC2INDEX(0,k,*nrT,*ncT)]),(ROW_MAJOR?*ncT:1),*nrT);
	  gsl_linalg_QR_Qvec(&(mA.matrix),tau,&(vT.vector));
	}
    }

  gsl_vector_free(norm);
  gsl_vector_free(tau);
  gsl_permutation_free(p);

  return(err);
}

void PrintGSLVector(FILE *f,char *label,gsl_vector *v)
{
  unsigned int i;

  if (label!=NULL)
    fprintf(f,"%s=",label);
  fprintf(f,"[");
  for(i=0;i<v->size;i++)
    fprintf(f,"%.16f ",gsl_vector_get(v,i));
  fprintf(f,"];\n");
}

void PrintGSLPermutation(FILE *f,char *label,gsl_permutation *p)
{
  unsigned int i;

  if (label!=NULL)
    fprintf(f,"%s=",label);
  fprintf(f,"[");
  for(i=0;i<p->size;i++)
    fprintf(f,"%lu ",gsl_permutation_get(p,i));
  fprintf(f,"];\n");
}

void PrintGSLMatrix(FILE *f,char *label,gsl_matrix *M)
{
  unsigned int i,j;

  if (label!=NULL)
    fprintf(f,"%s=",label);
  fprintf(f,"[");
  for(i=0;i<M->size1;i++)
    {
      for(j=0;j<M->size2;j++)
	fprintf(f,"%.16f ",gsl_matrix_get(M,i,j));
      fprintf(f,"\n");
    }
  fprintf(f,"];\n");
}


/******************************************************************/
/*                Public function definitions                     */

int MatrixDeterminantSgn(double epsilon,unsigned int n,double *A)
{
  int s;
  gsl_matrix_view m;
  gsl_permutation *p;

  #if (_DEBUG<2)
    gsl_set_error_handler_off();
  #endif

  /* We typically use this function for relatively large matrices
     and, thus, we do not take into account the case where n<=3 */
  p=gsl_permutation_alloc(n);
  m=gsl_matrix_view_array(A,n,n);

  gsl_linalg_LU_decomp(&(m.matrix),p,&s);

  s=gsl_linalg_LU_sgndet(&(m.matrix),s);

  gsl_permutation_free(p);

  return(s);
}

double MatrixDeterminant(unsigned int n,double *A)
{
  double d;

  #if (_DEBUG<2)
    gsl_set_error_handler_off();
  #endif

  /* Observe that det(A)=det(A^t) and thus for the case 2 and 3
     it does not matter if the matrix is stored ROW or COLUMN major */
  switch(n)
    {
    case 1:
      d=A[0];
      break;
    case 2:
      d=A[0]*A[3]-A[1]*A[2];
      break;
    case 3:
      d= A[0]*A[4]*A[8]+A[2]*A[3]*A[7]+A[1]*A[5]*A[6]
	-A[2]*A[4]*A[6]-A[1]*A[3]*A[8]-A[0]*A[5]*A[7];
      break;
    default:
      {
	gsl_matrix_view m;
	gsl_permutation *p;
	int s;

	p=gsl_permutation_alloc(n);
	m=gsl_matrix_view_array(A,n,n);

	gsl_linalg_LU_decomp(&(m.matrix),p,&s);

	d=gsl_linalg_LU_det(&(m.matrix),s);

	gsl_permutation_free(p);
      }
    }
  return(d);
}

boolean InvertMatrix(unsigned int nr,double *A)
{
  gsl_matrix_view mA,mI; 
  double *inv;
  gsl_permutation *p;
  int s,status;
  boolean ok;
  
  mA=gsl_matrix_view_array(A,nr,nr);
  
  NEW(inv,nr*nr,double);
  mI=gsl_matrix_view_array(inv,nr,nr);
  p=gsl_permutation_alloc(nr);

  status=gsl_linalg_LU_decomp(&(mA.matrix),p,&s);
  if (status)
    ok=FALSE;
  else
    {
      gsl_linalg_LU_invert(&(mA.matrix),p,&(mI.matrix));

      memcpy(A,mI,nr*nr*sizeof(double));
      ok=TRUE;
    } 
  gsl_permutation_free(p);
  
  return(ok);
}


void InitNewton(unsigned int nr,unsigned int nc,TNewton *n)
{

  #if (_DEBUG<2)
    gsl_set_error_handler_off();
  #endif

  n->nr=nr;
  n->nc=nc;

  NEW(n->Ab,nr*nc,double);
  NEW(n->bb,nr,double);

  n->A=gsl_matrix_view_array(n->Ab,n->nr,n->nc);
  n->b=gsl_vector_view_array(n->bb,n->nr);

  n->w=gsl_vector_alloc(nc);

  /* V and S are initialized to zero since if nr<nc some parts
     of them are actually not used. */
  n->V=gsl_matrix_calloc(nc,nc);
  n->S=gsl_vector_calloc(nc);
  n->tmp=gsl_vector_alloc(nr<nc?nr:nc);

  if (nr<nc)
    {
      /* When doing the SVD of the transpose we actually
         re-use memory for the non-transposed case. This
         is done to safe memory but mainly to avoid copying
         matrices. */
      n->VT=gsl_matrix_submatrix(n->V,0,0,nc,nr);
      n->UT=gsl_matrix_submatrix(&(n->A.matrix),0,0,nr,nr);
      n->ST=gsl_vector_subvector(n->S,0,nr);
    }

  #if (DAMPED_NEWTON)
    n->alpha=DN_F;
  #endif
}

int NewtonStep(double nullSingularValue,double *x,double *dif,TNewton *n)
{
  int err;
  unsigned int i,j;
  double d;

  /* This is a replacement for tolerant_SV_decomp. See this function to
     understand what we do here. */
  if (n->nr<n->nc)
    {
      /* Store A^t in n->VT (which is actually a submatrix of n->V. Note that
	 the space for A will be over-write (to store U). However, only the
	 first (nr X nr) block of A is used. The rest is not touched. This
	 part can be set to zero, but it is not necessary since these
	 values are actually not used when solving. */
      for(i=0;i<n->nr;i++)
	{
	  for(j=0;j<n->nc;j++)
	    gsl_matrix_set(&(n->VT.matrix),j,i,n->Ab[RC2INDEX(i,j,n->nr,n->nc)]);
	}

      err=gsl_linalg_SV_decomp(&(n->VT.matrix),&(n->UT.matrix),&(n->ST.vector),n->tmp);

      /* There is no need to copy VT in V since they share memory and the same
	 applies for UT (shares space with U) and ST (shares space with S). */
    }
  else
    err=gsl_linalg_SV_decomp(&(n->A.matrix),n->V,n->S,n->tmp);

  /* Correct the estimation and compute the error  */
  if (!err)
    {
      /* Adjust the eigenvalues (never more than 'nc' eigenvalues) */
      for(i=0;i<n->nc;i++)
	{
	  if (gsl_vector_get(n->S,i)<nullSingularValue)
	    gsl_vector_set(n->S,i,0.0);
	}

      /* This automatically solves least-square or the least-norm depending on
         the problem size and the number of non-null eigenvalues. This
         flexibility can not be achieved with QR typically because our matrices
         are typically not full rank. */
      err=gsl_linalg_SV_solve(&(n->A.matrix),n->V,n->S,&(n->b.vector),n->w);

      if (!err)
	{
	  (*dif)=0.0;

	  for(i=0;i<n->nc;i++)
	    {
	      d=gsl_vector_get(n->w,i);
	      #if (DAMPED_NEWTON)
	        x[i]-=(n->alpha*d);
	      #else
	        x[i]-=d;
	      #endif
	      (*dif)+=(d*d);
	    }
	  (*dif)=sqrt(*dif);

          #if (DAMPED_NEWTON)
	    n->alpha+=DN_W*(DN_MF-n->alpha);
          #endif

	  /* If the error is too large assume will never converge */
	  if ((*dif)>1e10)
	    err=1;
	}
    }

  return(err);
}

void DeleteNewton(TNewton *n)
{
  free(n->Ab);
  free(n->bb);

  gsl_vector_free(n->w);

  gsl_matrix_free(n->V);
  gsl_vector_free(n->S);
  gsl_vector_free(n->tmp);
}

void InitLS(unsigned int nr,unsigned int nc,unsigned int nrh,TLinearSystem *ls)
{
  #if (_DEBUG<2)
    gsl_set_error_handler_off();
  #endif

  if (nr<nc)
    Error("The linear system must be well-constrained or over-constrained");

  ls->nr=nr;
  ls->nc=nc;
  ls->nrh=nrh;

  NEW(ls->Ab,nr*nc,double);
  NEW(ls->bb,nr*nrh,double);
  NEW(ls->xb,nc*nrh,double);

  ls->A=gsl_matrix_view_array(ls->Ab,nr,nc);

  if (nr==nc)
    ls->p=gsl_permutation_alloc(nr);
  else
    {
      /* nr>nc */
      ls->tau=gsl_vector_alloc(nr);
      ls->res=gsl_vector_alloc(nr);
      ls->work=gsl_vector_alloc(3*nr);
    }
}

int LSSolve(TLinearSystem *ls)
{
  int err;
  unsigned int i;

  if (ls->nr==ls->nc)
    {
      int s;

      /* Well constrained systems -> LU decomposition */
      err=gsl_linalg_LU_decomp(&(ls->A.matrix),ls->p,&s);
      for(i=0;((!err)&&(i<ls->nrh));i++)
	{
	  ls->b=gsl_vector_view_array_with_stride(ls->bb,ls->nrh,nr);
	  ls->x=gsl_vector_view_array_with_stride(ls->xb,ls->nrh,nc);
	  err=gsl_linalg_LU_solve(&(ls->A.matrix),ls->p,&(ls->b.vector),&(ls->x.vector));
	}
    }
  else
    {
      /* Over-constrained system -> QR decomposition and less-square solve */
      err=gsl_linalg_QR_decomp(&(ls->A.matrix),ls->tau);

      for(i=0;((!err)&&(i<ls->nrh));i++)
	{
	  ls->b=gsl_vector_view_array_with_stride(ls->bb,ls->nrh,nr);
	  ls->x=gsl_vector_view_array_with_stride(ls->xb,ls->nrh,nc);
	  err=gsl_linalg_QR_lssolve(&(ls->A.matrix),ls->tau,&(ls->b.vector),&(ls->x.vector),ls->res);
	}
    }

  return(err);
}

int LSSolveCond(double *rcond,TLinearSystem *ls)
{
  int err;
  unsigned int i;

  #if (_DEBUG>0)
    if (ls->nr!=ls->nc)
      Error("LSSolveCond is only implemented for squared matrices");
  #endif
    
  /* Use QR even if squared matrices because we need to compute rcond and its computation
     is not implemented from LU decompositions in GSL */
  err=gsl_linalg_QR_decomp(&(ls->A.matrix),ls->tau);
  if (!err)
    {
      err=gsl_linalg_QRPT_rcond(&(ls->A.matrix),rcond,ls->work);
      
      if (!err)
	{
	  for(i=0;((!err)&&(i<ls->nrh));i++)
	    {
	      ls->b=gsl_vector_view_array_with_stride(ls->bb,ls->nrh,nr);
	      ls->x=gsl_vector_view_array_with_stride(ls->xb,ls->nrh,nc);
	      err=gsl_linalg_QR_lssolve(&(ls->A.matrix),ls->tau,&(ls->b.vector),&(ls->x.vector),ls->res);
	    }
	}
      else
	err=1;
    }
      
  return(err);
}

void DeleteLS(TLinearSystem *ls)
{
  free(ls->Ab);
  free(ls->bb);
  free(ls->xb);

  if (ls->nr==ls->nc)
    gsl_permutation_free(ls->p);
  else
    {
      gsl_vector_free(ls->tau);
      gsl_vector_free(ls->res);
      gsl_vector_free(ls->work);
    }
}

#endif

/* END GSL IMPLEMENTATION */


/* BEGIN LAPACK IMPLEMENTATION */
#ifdef _LAPACK

unsigned int AnalyzeKernel(unsigned int nr,unsigned int nc,double *mT,
			   unsigned int dof,double epsilon,
			   boolean computeRank,boolean checkRank,boolean getT,boolean getBase,
			   boolean *singular,unsigned int *rank,boolean **IR,double **T)
{
  unsigned int err;

  if (dof==nc)
    {
      /* Trivial case of a system without equations. We take this into account for completeness, but
         this function should never be used in this case. */
      *singular=FALSE;
      *rank=0;

      if ((getT)&&(nc>0))
	{
	  unsigned int i;

	  NEWZ(*T,nc*dof,double);
	  for(i=0;i<nc;i++)
	    (*T)[RC2INDEX(i,i,nc,dof)]=1.0;
	}
      else
	*T=NULL;

      if ((getBase)&&(nr>0))
	{
	  unsigned int i;

	  NEW(*IR,nr,boolean);
	  for(i=0;i<nr;i++)
	    (*IR)[i]=FALSE;
	}
      else
	*IR=NULL;

      err=0;
    }
  else
    {
      int *p,lwork,info;
      double *tau,wOpt,*work;

      /* Extra space for the QR decomposition of At */
      NEW(tau,(nr<nc?nr:nc),double);
      NEWZ(p,nr,int); /* This MUST be initialized to zero! */

      /* allocate the work space. We assume that the work space for the decomposition is larger
	 than that for the unpacking. */

      /* dgeqp3(M,N,A,LDA,PVT,TAU,WORK,LWORK,INFO) */
      /* computes the QR factorization, with column pivoting */
      lwork=-1;
      #ifdef _LAPACKE
        info=(int)LAPACKE_dgeqp3_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
      	                              (lapack_int)nc,(lapack_int)nr,mT,(lapack_int)nc,
      	                              (lapack_int*)p,tau,&wOpt,(lapack_int)lwork);
      #else
        dgeqp3_((int*)&nc,(int*)&nr,mT,(int*)&nc,p,tau,&wOpt,&lwork,&info);
      #endif
      lwork=(int)wOpt;
      NEW(work,lwork,double);

      /* Decompose the matrix, with column pivoting to get the kernel. Note that
	 the permutation is not relevant for the kernel P*A*v=0 -> A*v=0  */
      #ifdef _LAPACKE
        info=(int)LAPACKE_dgeqp3_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
      	                              (lapack_int)nc,(lapack_int)nr,mT,(lapack_int)nc,
      	                              (lapack_int*)p,tau,work,(lapack_int)lwork);
      #else
        dgeqp3_((int*)&nc,(int*)&nr,mT,(int*)&nc,p,tau,work,&lwork,&info);
      #endif

      err=(info!=0);

      if (err)
	{
	  *singular=TRUE;
	  *rank=NO_UINT;
	  *T=NULL;
	  *IR=NULL;
	  err=3; /* Our error code for decomposition error */
	}
      else
	{
	  unsigned int k,mrc;
	  double r;

	  /***********************************************/
	  /* At is nc x nr */
	  /* Q is nc x nc */
	  /* R is nc x nr -> R^t is nr x nc */

	  /* At=Q R P^t -> A= P R^t Q^t -> P^t A Q = R^t
	     Thus, the rows of R (columns of R^t) that are zero
	     indicate columns of Q that define part of the kernel.
	     Moreover, the norm of the rows of R indicate how far
	     is from defining a new kernel basis vector. Sinc R
	     is triangular the norm of the row is the norm from
	     the diagonal to the end of the row (nr entries) */

	  mrc=(nr<nc?nr:nc);

	  if (computeRank)
	    {
	      /* Rank = number of not-null rows of R */
	      /* The rank can not be larger than the mrc=min(nr,nc) */
	      *rank=0;
	      for(k=0;k<mrc;k++)
		{
		  /* Get the norm of row k of R from the diagonal to the end of the row */
		  r=NormWithStride(nr-k,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(k,k,nc,nr)]));
		  if (r>epsilon)
		    (*rank)++;
		}
	      if (dof==0)
		{
		  *singular=FALSE;
		  /* temporary set 'dof' form '*rank' */
		  dof=nc-*rank;
		}
	      else
		*singular=((nc-dof)!=*rank);
	    }
	  else
	    {
	      if (dof==0)
		Error("Null 'dof' parameter in AnalyzeKernel");
	      if (dof>nc)
		Error("We can not have more 'dof' than variables");

	      *rank=nc-dof;

	      /* Check if row *rank-1 of R is actually not null. */
	      r=NormWithStride(nr-(*rank-1),(ROW_MAJOR?1:nc),&(mT[RC2INDEX(*rank-1,*rank-1,nc,nr)]));
	      *singular=(r<epsilon);

	      if (checkRank)
		{
		  if (*singular)
		    err=1; //Error("Singular point (increase N_DOF? Decrease EPSILON?)");

		  /* Checking row '*rank' is actually null. */
		  r=NormWithStride(nr-*rank,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(*rank,*rank,nc,nr)]));
		  if (r>epsilon)
		    err=2; //Error("Non-null kernel vector (decrease N_DOF? Increase EPSILON?)");
		}
	    }

	  #if (_DEBUG>0)
	    if ((dof>0)&&(!computeRank)&&(getT)&&(!getBase))
	      {
		printf("  E=[ ");
		for(k=*rank;k<mrc;k++)
		  {
		    r=NormWithStride(nr-k,(ROW_MAJOR?1:nc),&(mT[RC2INDEX(k,k,nc,nr)]));
		    printf("%.16f ",r);
		  }
		printf("];\n");
	      }
	  #endif

	  /* If requested, we define T and IR, even if the chart is singular. In this case
	     we return the most likely T and IR. */
	  if (getT)
	    {
	      unsigned int i;
	      char left='L';
	      char noTrans='N';

	      /* The kernel are the last 'dof' columns of Q */
	      /* Note that P^t A q_i = 0 <-> A q_i = 0 */
	      NEWZ(*T,nc*dof,double); /* init to zero */
	      for(k=*rank,i=0;k<nc;k++,i++)
		(*T)[RC2INDEX(k,i,nc,dof)]=1.0;
	      /* DORMQR(SIDE,TRANS,M,N,K,A,LDA,TAU,C,LDC,WORK,LWORK,INFO) */
	      /* (*T)=Q*(*T)  (with Q encoded as elementary reflectors) */
	      #ifdef _LAPACKE
	        info=(int)LAPACKE_dormqr_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),left,noTrans,
				  	      (lapack_int)nc,(lapack_int)dof,(lapack_int)(nr<nc?nr:nc),
					      mT,(lapack_int)nc,tau,*T,(lapack_int)nc,work,(lapack_int)lwork);
	      #else
	        dormqr_(&left,&noTrans,(int*)&nc,(int*)&dof,(nr<nc?(int*)&nr:(int*)&nc),mT,(int*)&nc,tau,*T,(int*)&nc,work,&lwork,&info);
	      #endif
	      err=(info!=0);
	    }
	  else
	    *T=NULL;

	  if (getBase)
	    {
	      NEW(*IR,nr,boolean);
	      for(k=0;k<nr;k++)
		(*IR)[k]=FALSE;
	      for(k=0;k<*rank;k++)
		(*IR)[p[k]-1]=TRUE; /* permutations numbered from 1 in lapack */
	    }
	  else
	    *IR=NULL;
	}
      free(work);
      free(tau);
      free(p);
    }
  return(err);
}

unsigned int BasisColumnSpace(double epsilon,unsigned int nr,unsigned int nc,double *A,
			      boolean **IC,
			      unsigned int *nrT,unsigned int *ncT,double **T)
{
  unsigned int err;
  int *p,lwork,info;
  double *tau,wOpt,*work;
  unsigned int k,m;
  char left='L';
  char noTrans='N';
  double r;

  err=0;

  /* Extra space for the QR decomposition of A */
  m=(nr<nc?nr:nc);
  NEW(tau,m,double);
  NEWZ(p,nc,int); /* This MUST be initialized to zero! */

  /* allocate the work space. We assume that the work space for the decomposition is larger
     than that for the unpacking. */

  /* dgeqp3(M,N,A,LDA,PVT,TAU,WORK,LWORK,INFO) */
  /* computes the QR factorization, with column pivoting */
  lwork=-1;
  #ifdef _LAPACKE
    info=(int)LAPACKE_dgeqp3_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				  (lapack_int)nr,(lapack_int)nc,A,(lapack_int)nr,
				  (lapack_int*)p,tau,&wOpt,(lapack_int)lwork);
  #else
    dgeqp3_((int*)&nr,(int*)&nc,A,(int*)&nr,p,tau,&wOpt,&lwork,&info);
  #endif
  lwork=(int)wOpt;
  NEW(work,lwork,double);

  /* Decompose the matrix, with column pivoting.  */
  #ifdef _LAPACKE
    info=(int)LAPACKE_dgeqp3_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				  (lapack_int)nr,(lapack_int)nc,A,(lapack_int)nr,
				  (lapack_int*)p,tau,&wOpt,(lapack_int)lwork);
  #else
    dgeqp3_((int*)&nr,(int*)&nc,A,(int*)&nr,p,tau,&wOpt,&lwork,&info);
  #endif

  err=(info!=0);

  if (err)
    {
      /* Cancel output information */
      *nrT=0;
      *ncT=0;
      *T=NULL;
      *IC=NULL;
    }
  else
    {
      /* Count the number of independent columms and identify them */
      NEW(*IC,nc,boolean);
      for(k=0;k<nc;k++)
	(*IC)[k]=FALSE;

      *nrT=nr;
      *ncT=0;
      for(k=0;k<m;k++)
	{
	  /* Get the norm of row k of R to the diagonal */
	  r=NormWithStride(k+1,(ROW_MAJOR?nc:1),&(A[RC2INDEX(0,k,nr,nc)]));
	  if (r>epsilon)
	    {
	      (*ncT)++;
	      (*IC)[p[k]]=TRUE;
	    }
	}

      /* Now reconstruct the base */
      NEWZ(*T,(*nrT)*(*ncT),double);
      for(k=0;k<*ncT;k++)
	(*T)[RC2INDEX(k,k,*nrT,*ncT)]=1.0;

      /* DORMQR(SIDE,TRANS,M,N,K,A,LDA,TAU,C,LDC,WORK,LWORK,INFO) */
      /* (*T)=Q*(*T)  (with Q encoded as elementary reflectors) */
      #ifdef _LAPACKE
        info=(int)LAPACKE_dormqr_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),left,noTrans,
				      (lapack_int)(*nrT),(lapack_int)(*ncT),(lapack_int)m,
				      A,(lapack_int)nr,tau,*T,(lapack_int)*nrT,work,(lapack_int)lwork);
      #else
        dormqr_(&left,&noTrans,(int*)nrT,(int*)ncT,(int*)&m,A,(int*)&nr,tau,*T,(int*)nrT,work,&lwork,&info);
      #endif
      err=(info!=0);
    }

  free(tau);
  free(work);
  free(p);

  return(err);
}

int MatrixDeterminantSgn(double epsilon,unsigned int n,double *A)
{
  int s,info,*p;
  double v;

  NEW(p,n,int);

  /* LU decomposition */
  /* DGETRF(M,N,A,LDA,IPIV,INFO) */
  /* computes an LU factorization of a general M-by-N matrix using partial pivoting with row interchanges. */
  #ifdef _LAPACKE
    info=(int)LAPACKE_dgetrf_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
                                  (lapack_int)n,(lapack_int)n,A,(lapack_int)n,(lapack_int*)p);
  #else
    dgetrf_((int*)&n,(int*)&n,A,(int*)&n,p,&info);
  #endif

  if (info==0)
    {
      unsigned int i;

      /* Get the sign of the permutation */
      s=1;
      for(i=0;i<n;i++)
	if ((unsigned int)(p[i]-1)!=i) s=-s; /* permutations numbered from 1 in lapack */

      /* and now the sign of the diagonal of U */
      for(i=0;((s!=0)&&(i<n));i++)
	{
	  v=A[RC2INDEX(i,i,n,n)];
	  if (fabs(v)<epsilon) s=0;
	  else
	    {
	      if (v<0.0) s=-s;
	    }
	}
    }
  else
    s=0;

  free(p);

  return(s);
}

double MatrixDeterminant(unsigned int n,double *A)
{
  double d;

  /* Observe that det(A)=det(A^t) and thus for the case 2 and 3
     it does not matter if the matrix is stored ROW or COLUMN major */
  switch(n)
    {
    case 1:
      d=A[0];
      break;
    case 2:
      d=A[0]*A[3]-A[1]*A[2];
      break;
    case 3:
      d= A[0]*A[4]*A[8]+A[2]*A[3]*A[7]+A[1]*A[5]*A[6]
	-A[2]*A[4]*A[6]-A[1]*A[3]*A[8]-A[0]*A[5]*A[7];
      break;
    default:
      {
	int info,*p;

	NEW(p,n,int);

	/* LU decomposition */
	/* DGETRF(M,N,A,LDA,IPIV,INFO) */
	/* computes an LU factorization of a general M-by-N matrix using partial pivoting with row interchanges. */
	#ifdef _LAPACKE
          info=(int)LAPACKE_dgetrf_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
                                        (lapack_int)n,(lapack_int)n,A,(lapack_int)n,(lapack_int*)p);
        #else
	  dgetrf_((int*)&n,(int*)&n,A,(int*)&n,p,&info);
	#endif
	if (info==0)
	  {
	    unsigned int i;

	    /* Get the sign of the permutation */
	    d=1.0;
	    for(i=0;i<n;i++)
	      if ((unsigned int)(p[i]-1)!=i) d=-d; /* permutations numbered from 1 in lapack */

	    /* and now the product of the diagonal of U */
	    for(i=0;i<n;i++)
	      d*=A[RC2INDEX(i,i,n,n)];
	  }
	else
	  d=INF;

	free(p);
      }
    }
  return(d);
}

boolean InvertMatrix(unsigned int nr,double *A)
{
  int *p,lwork,info;
  double *work,wOpt;

  NEW(p,nr,int);

  #ifdef _LAPACKE
    info=(int)LAPACKE_dgetrf_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
                                  (lapack_int)nr,(lapack_int)nr,A,(lapack_int)nr,(lapack_int*)p);
    if (info==0)
      {
	lwork=-1;
	info=(int)LAPACKE_dgetri_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				      (lapack_int)nr,A,(lapack_int)nr,(lapack_int*)p,&wOpt,(lapack_int)lwork);
	lwork=(int)wOpt;
	NEW(work,lwork,double);
	info=(int)LAPACKE_dgetri_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				      (lapack_int)nr,A,(lapack_int)nr,(lapack_int*)p,work,(lapack_int)lwork);
	free(work);
      }
  #else
    dgetrf_((int*)&nr,(int*)&nr,A,(int*)&nr,p,&info);
    if (info==0)
      {
	lwork=-1;
	dgetri_((int *)&nr,A,(int*)&nr,p,&wOpt,&lwork,&info);
	lwork=(int)wOpt;
	NEW(work,lwork,double);
	dgetri_((int *)&nr,A,(int*)&nr,p,work,&lwork,&info);
	free(work);
      }
  #endif

  free(p);

  return(info==0);
}

void InitNewton(unsigned int nr,unsigned int nc,TNewton *n)
{
  int rank,one=1,info;
  double w,e=1e-6;

  n->nr=(int)nr;
  n->nc=(int)nc;

  NEW(n->Ab,nr*nc,double);
  /* b is used for input and output */
  NEW(n->bb,(nr>nc?nr:nc),double);

  NEW(n->s,(nr<nc?nr:nc),double);

  /* Request the optimal size for the work buffer */
  /* DGELSS(M,N,NRHS,A,LDA,B,LDB,S,RCOND,RANK,WORK,LWORK,INFO) */
  n->lwork=-1;
  #ifdef _LAPACKE
    info=(int)LAPACKE_dgelss_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
                                  (lapack_int)n->nr,(lapack_int)n->nc,one,n->Ab,
				  (lapack_int)n->nr,n->bb,(lapack_int)(n->nr>n->nc?n->nr:n->nc),
				  n->s,e,(lapack_int*)&rank,&w,n->lwork);
  #else
    dgelss_(&n->nr,&n->nc,&one,n->Ab,&n->nr,n->bb,(n->nr>n->nc?&n->nr:&n->nc),n->s,&e,&rank,&w,&n->lwork,&info);
  #endif

  if (info!=0)
    Error("Clapack error in InitNewton");

  n->lwork=(int)w;
  NEW(n->work,n->lwork,double);

  #if (DAMPED_NEWTON)
    n->alpha=DN_F;
  #endif
}

int NewtonStep(double nullSingularValue,double *x,double *dif,TNewton *n)
{
  int rank,info,one=1;

  /* Minimum norm solution via SVD (works even if the matrix is not full rank) */

  /* DGELSS(M,N,NRHS,A,LDA,B,LDB,S,RCOND,RANK,WORK,LWORK,INFO) */
  /* computes the minimum norm solution to a real linear least squares problem: */
  /* singular values smaller than MaxSingularValue*Rcond are treated as zero */
  /* This is a difference w.r.t the GSL implementation! */
  #ifdef _LAPACKE
    info=(int)LAPACKE_dgelss_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
                                  (lapack_int)n->nr,(lapack_int)n->nc,one,n->Ab,
				  (lapack_int)n->nr,n->bb,(lapack_int)(n->nr>n->nc?n->nr:n->nc),
				  n->s,nullSingularValue,(lapack_int*)&rank,n->work,n->lwork);
  #else
    dgelss_(&n->nr,&n->nc,&one,n->Ab,&n->nr,n->bb,(n->nr>n->nc?&n->nr:&n->nc),n->s,&nullSingularValue,&rank,n->work,&n->lwork,&info);
  #endif

  if (info==0)
    {
      #if (DAMPED_NEWTON)
        SumVectorScale(n->nc,x,-n->alpha,n->bb,x);
	n->alpha+=DN_W*(DN_MF-n->alpha);
      #else
        SubtractVector(n->nc,x,n->bb);
      #endif
      *dif=Norm(n->nc,n->bb);

      /* If the error is too large assume will never converge */
      if ((*dif)>1e10)
	info=1;
    }

  return(info!=0);
}

void DeleteNewton(TNewton *n)
{
  free(n->Ab);
  free(n->bb);

  free(n->s);

  free(n->work);
}

void InitLS(unsigned int nr,unsigned int nc,unsigned int nrh,TLinearSystem *ls)
{
  if (nr<nc)
    Error("The linear system must be well-constrained or over-constrained");

  ls->nr=(int)nr;
  ls->nc=(int)nc;
  ls->nrh=(int)nrh;

  NEW(ls->Ab,nr*nc,double);
  NEW(ls->bb,nr*nrh,double);
  ls->xb=ls->bb; /* vector re-used */

  if (nr==nc)
    {
      /* Solve via LU decomposition */
      NEW(ls->p,nr,int);
      NEW(ls->w,4*nr,double);
      NEW(ls->iw,nr,int);
    }
  else
    {
      /* Solve via QR decomposition */
      int info;
      double w;
      char noTrans='N';

      /* Request the optimal size for the work buffer */
      /* DGELS(TRANS,M,N,NRHS,A,LDA,B,LDB,WORK,LWORK,INFO) */
      /* DGELS solves overdetermined or underdetermined real linear systems */
      /* It uses QR or LQ decompositions. */
      /* It assumes the matrix to be full rank. */
      ls->lwork=-1;
      #ifdef _LAPACKE
        info=(int)LAPACKE_dgels_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),noTrans,
	                             (lapack_int)ls->nr,(lapack_int)ls->nc,ls->nrh,ls->Ab,
				     (lapack_int)ls->nr,ls->bb,(lapack_int)ls->nr,&w,ls->lwork);
      #else
        dgels_(&noTrans,&ls->nr,&ls->nc,&ls->nrh,ls->Ab,&ls->nr,ls->bb,&ls->nr,&w,&ls->lwork,&info);
      #endif

      if (info!=0)
        Error("Clapack error in InitLS");

      ls->lwork=(int)w;
      NEW(ls->work,ls->lwork,double);
    }
}

int LSSolve(TLinearSystem *ls)
{
  int info;
  char noTrans='N';

  if (ls->nr==ls->nc)
    {
      /* DGESV(N,NRHS,A,LDA,IPIV,B,LDB,INFO) */
      /* Computes the solution to a real system of linear equations */
      /* The LU decomposition with partial pivoting and row interchanges is used */
      #ifdef _LAPACKE
        info=(int)LAPACKE_dgesv_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
		                     (lapack_int)ls->nr,ls->nrh,ls->Ab,(lapack_int)ls->nr,
				     (lapack_int*)ls->p,ls->bb,(lapack_int)ls->nr);
      #else
        dgesv_(&ls->nr,&ls->nrh,ls->Ab,&ls->nr,ls->p,ls->bb,&ls->nr,&info);
      #endif
    }
  else
    /* Least square QR */
    /* DGELS(TRANS,M,N,NRHS,A,LDA,B,LDB,WORK,LWORK,INFO) */
    /* DGELS solves overdetermined or underdetermined real linear system using a QR or LQ factorization. */
    /* It is assumed that the matrix has full rank. */
    #ifdef _LAPACKE
      info=(int)LAPACKE_dgels_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),noTrans,
	                           (lapack_int)ls->nr,(lapack_int)ls->nc,ls->nrh,ls->Ab,
 	 	                   (lapack_int)ls->nr,ls->bb,(lapack_int)ls->nr,ls->work,ls->lwork);
    #else
      dgels_(&noTrans,&ls->nr,&ls->nc,&ls->nrh,ls->Ab,&ls->nr,ls->bb,&ls->nr,ls->work,&ls->lwork,&info);
    #endif

  return(info!=0);
}

int LSSolveCond(double *rcond,TLinearSystem *ls)
{ 
  int info;
  char normType='1'; /* We use 1-norm (as rcond in Matlab). Could also use 'I' */
  char noTrans='N';
  double anorm;

  #if (_DEBUG>0)
    if (ls->nr!=ls->nc)
      Error("LSSolveCond is only implemented for squared matrices");
  #endif

    //PrintMatrix(stderr,"A",ls->nr,ls->nr,ls->Ab);
    
    /* Compute the norm of the matrix before decomposing it */
  #ifdef _LAPACKE
    anorm=(int)LAPACKE_dlange_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				   normType,ls->nr,ls->nc,ls->Ab,ls->nr,ls->w);
  #else
    anorm=dlange_(&normType,&ls->nr,&ls->nc,ls->Ab,&ls->nr,ls->w);
  #endif
      
  /* LU decomposition */
  #ifdef _LAPACKE
    info=LAPACKE_dgetrf((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
			(lapack_int)ls->nr,(lapack_int)ls->nc,
			ls->Ab,(lapack_int)ls->nr,
			(lapack_int*)ls->p);
  #else
    dgetrf_(&ls->nr,&ls->nc,ls->Ab,&ls->nr,ls->p,&info);
  #endif

  if (info==0)
    {
      /* Compute the condition number */
      #ifdef _LAPACKE
        info=(int)LAPACKE_dgecon_work((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),
				      normType,(lapack_int)ls->nr,ls->Ab,(lapack_int)ls->nr,
				      anorm,rcond,ls->w,(lapack_int*)ls->iw);
      #else
	dgecon_(&normType,&ls->nr,ls->Ab,&ls->nr,&anorm,rcond,ls->w,ls->iw,&info);
      #endif
	      
      /* Check if the condition number is large enough */
      if (info==0)
	{
	  /* if so, solve the system from the LU decomposition */
          #ifdef _LAPACKE
	    info=(int)LAPACKE_dgetrs((ROW_MAJOR?LAPACK_ROW_MAJOR:LAPACK_COL_MAJOR),noTrans,
				     (lapack_int)ls->nr,(lapack_int)ls->nrh,ls->Ab,
				     (lapack_int)ls->nr,(lapack_int*)ls->p,
				     ls->bb,(lapack_int)ls->nr);
	  #else
	    dgetrs_(&noTrans,&ls->nr,&ls->nrh,ls->Ab,&ls->nr,ls->p,ls->bb,&ls->nr,&info);
	  #endif
	}
      else
	info=1;
    }
  
  return(info!=0);
}

void DeleteLS(TLinearSystem *ls)
{
  free(ls->Ab);
  free(ls->bb);

  if (ls->nr==ls->nc)
    {
      free(ls->p);
      free(ls->w);
      free(ls->iw);
    }
  else
    free(ls->work);
}


#endif

/* END LAPACK IMPLEMENTATION */


/* GENERIC IMPLEMENTATION */
/***************************************************************************/
/***************************************************************************/
/***************************************************************************/

/* Some functions are independent of the underlying linear algebra package */


unsigned int MatrixExponential(unsigned int m,double *A,double t,double *eA)
{
  int iflag;
  
  if (fabs(t)<1e-6)
    {
      IdentityMatrix(m,eA);
      iflag=0;
    }
  else
    {
      int ideg,lwsp,*ipiv,iexph,ns;
      double *wsp;
  
      #if (ROW_MAJOR)
        double sa;
	unsigned int i,j,i1,i2;

	/* Transpose the input matrix in place because expokit assumes
	   column major order */
	for(i=0;i<m;i++)
	  {
	    for(j=i+1;j<m;j++)
	      {
		i1=i*m+j;
		i2=j*m+i;
		sa=A(i1);
		A(i1)=A(i2);
		A(i2)=sa;
	      }
	  }
      #endif
 
      ideg=6;
      lwsp=4*m*m+ideg+1;
      NEW(wsp,lwsp,double);
      NEW(ipiv,m,int);

      #if __APPLE__
        dgpadm(&ideg,(int *)&m,&t,A,(int *)&m,wsp,&lwsp,ipiv,&iexph,&ns,&iflag);
      #else
        dgpadm_(&ideg,(int *)&m,&t,A,(int *)&m,wsp,&lwsp,ipiv,&iexph,&ns,&iflag);
      #endif
  
      if (iflag==0)
	memcpy(eA,&(wsp[iexph-1]),m*m*sizeof(double));
  
      free(wsp);
      free(ipiv);
  
      #if (ROW_MAJOR)
        /* Transpose the input and the output matrix in place */
        for(i=0;i<m;i++)
	  {
	    for(j=i+1;j<m;j++)
	      {
		i1=i*m+j;
		i2=j*m+i;
	    
		sa=A(i1);
		A(i1)=A(i2);
		A(i2)=sa;

		if (iflag==0)
		  {
		    sa=eA(i1);
		    eA(i1)=eA(i2);
		    eA(i2)=sa;
		  }
	      }
	  }
      #endif
    }
  
  return(iflag==0);
}

unsigned int MatrixExponentialVector(unsigned int m,double *A,double t,double *v)
{
  int iflag;
  
    /* If t is close to zero, expm(A)=eye and, thus expm(A)*v=v -> nothing to do */
  if (fabs(t)>1e-6)
    {
      int *iwsp;
      double *wsp;
  
      #if (ROW_MAJOR)
        double sa;
	unsigned int i,j,i1,i2;

	/* Transpose the input matrix in place because expokit assumes
	   column major order */
	for(i=0;i<m;i++)
	  {
	    for(j=i+1;j<m;j++)
	      {
		i1=i*m+j;
		i2=j*m+i;
		sa=A(i1);
		A(i1)=A(i2);
		A(i2)=sa;
	      }
	  }
      #endif


      NEW(wsp,2*m*(m+2),double);
      NEW(iwsp,m,int);

      #if __APPLE__
        dgchbv((int*)&m,&t,A,(int*)&m,v,wsp,iwsp,&iflag);
      #else
	dgchbv_((int*)&m,&t,A,(int*)&m,v,wsp,iwsp,&iflag);
      #endif

      free(iwsp);
      free(wsp);
  
      #if (ROW_MAJOR)
        /* Transpose the input and the output matrix in place */
        for(i=0;i<m;i++)
	  {
	    for(j=i+1;j<m;j++)
	      {
		i1=i*m+j;
		i2=j*m+i;
	    
		sa=A(i1);
		A(i1)=A(i2);
		A(i2)=sa;
	      }
	  }
      #endif
    }
  else
    iflag=0;

  return(iflag==0);
}

unsigned int FindRank(double epsilon,unsigned int nr,unsigned int nc,double *mT)
{
  boolean singular;
  boolean *IR;
  double *T;
  unsigned int rank;

  AnalyzeKernel(nr,nc,mT,0,epsilon,
		TRUE,FALSE,FALSE,FALSE, /* computeRank, checkRank, getT, getBase */
		&singular,&rank,&IR,&T);

  return(rank);
}

unsigned int FindKernel(unsigned int nr,unsigned int nc,double *mT,
			unsigned int dof,boolean check,double epsilon,double **T)
{
  unsigned int err;
  boolean singular;
  boolean *IR;
  unsigned int rank;

  err=AnalyzeKernel(nr,nc,mT,dof,epsilon,
		    FALSE,check,TRUE,FALSE, /* computeRank, checkRank, getT, getBase */
		    &singular,&rank,&IR,T);
  return(err);
}

unsigned int FindKernelAndRank(unsigned int nr,unsigned int nc,double *mT,
			       unsigned int *rank,double epsilon,double **T)
{
  unsigned int err;
  boolean singular;
  boolean *IR;

  err=AnalyzeKernel(nr,nc,mT,0,epsilon,     /* ndof=0, not given */
		    TRUE,FALSE,TRUE,FALSE, /* computeRank, checkRank, getT, getBase */
		    &singular,rank,&IR,T);
  return(err);
}

unsigned int FindKernelAndIndependentRows(unsigned int nr,unsigned int nc,double *mT,
					  unsigned int dof,double epsilon,boolean *singular,
					  boolean **IR,double **T)
{
  unsigned int err;
  unsigned int rank;

  err=AnalyzeKernel(nr,nc,mT,dof,epsilon,
		    FALSE,TRUE,TRUE,TRUE, /* computeRank, checkRank, getT, getBase */
		    singular,&rank,IR,T);

  return(err);
}

unsigned int FindIndependentRows(unsigned int nr,unsigned int nc,double *mT,
				 unsigned int dof,double epsilon,boolean *singular,
				 boolean **IR)
{
  unsigned int err;
  unsigned int rank;
  double *T;

  err=AnalyzeKernel(nr,nc,mT,dof,epsilon,
		    FALSE,TRUE,FALSE,TRUE, /* computeRank, checkRank, getT, getBase */
		    singular,&rank,IR,&T);

  return(err);
}

inline double *GetNewtonMatrixBuffer(TNewton *n)
{
  return(n->Ab);
}

inline double *GetNewtonRHBuffer(TNewton *n)
{
  return(n->bb);
}

inline void NewtonSetMatrix(unsigned int i,unsigned int j,double v,TNewton *n)
{
  n->Ab[RC2INDEX(i,j,n->nr,n->nc)]=v;
}

inline void NewtonSetRH(unsigned int i,double v,TNewton *n)
{
  n->bb[i]=v;
}

inline double *GetLSMatrixBuffer(TLinearSystem *ls)
{
  return(ls->Ab);
}

inline double *GetLSRHBuffer(TLinearSystem *ls)
{
  return(ls->bb);
}

inline double *GetLSSolutionBuffer(TLinearSystem *ls)
{
  return(ls->xb);
}

inline void LSSetMatrix(unsigned int i,unsigned int j,double v,TLinearSystem *ls)
{
  ls->Ab[RC2INDEX(i,j,ls->nr,ls->nc)]=v;
}

inline void LSSetRH(unsigned int i,unsigned int j,double v,TLinearSystem *ls)
{
  ls->bb[RC2INDEX(i,j,ls->nr,ls->nrh)]=v;
}

void InitBroyden(unsigned int nr,unsigned int nc,TBroyden *b)
{
  if (nc!=nr)
    Error("Broyden method is only defined for well-constrained systems");

  InitLS(nc,nc,1,&(b->ls));

  b->it=0;

  b->n=nr; /* == nc */

  NEW(b->resp,b->n,double); /* previous residue (previous rhs of Newton) */
  NEW(b->r,b->n,double);  /* Difference in residue current-previous.*/
  NEW(b->p,b->n,double);  /* p */

  b->An=GetLSMatrixBuffer(&(b->ls));
  b->bn=GetLSRHBuffer(&(b->ls));
  b->s=GetLSSolutionBuffer(&(b->ls));

  NEW(b->B,b->n*b->n,double);
  NEW(b->res,b->n,double);
}

inline void ResetBroyden(TBroyden *b)
{
  b->it=0;
}

inline double *GetBroydenMatrixBuffer(TBroyden *b)
{
  if (b->it>0)
    Error("Can not access Broyden matrix buffer once the Broyden iteration is started (after calling BroydenStep)");
  return(b->B);
}

inline double *GetBroydenRHBuffer(TBroyden *b)
{
  return(b->res);
}

int BroydenStep(double epsilon,unsigned int *tp,
		double *x,TBroyden *b)
{
  int info;
  unsigned int i;
  #if (_DEBUG>6)
    char *label;
    NEW(label,100,char);
  #endif

  /*
    For a system with approximated Jacobian S and
    residue y0, Broyden method can be summarized as:

    d = -S\y0; <- Evaluated in this function
    x = x0+d;

    y = feval(f,x,varargin{:}); <- Evaluated externally

    S = S+((y-y0)-S*d)*d'/(d'*d); <- Evaluated in BroydenUpdateJacobian
    tmp = sqrt((x-x0)'*(x-x0));
    err = tmp-eps1*(1+abs(x));
    ferr = sqrt(y'*y);
    x0 = x;
    y0 = y;
    r(i+1)=norm(y);
    if r(i+1)<tol;break;end
   */
    
  /* We need to copy B into the Newton's buffer An because An is
     overwrite at every call to BroydenStep. */
  memcpy(b->An,b->B,sizeof(double)*b->n*b->n);
  memcpy(b->bn,b->res,sizeof(double)*b->n);
      
  #if (_DEBUG>6)
  {
    fprintf(stderr,"            Broyden iteration: %u\n",b->it);
    sprintf(label,"               B_%u",b->it);PrintMatrix(stderr,label,b->n,b->n,b->B);
    sprintf(label,"               r_%u",b->it);PrintVector(stderr,label,b->n,b->res);
    fprintf(stderr,"              |r_%u|=%.14f\n",b->it,Norm(b->n,b->res));
  }
  #endif

  info=LSSolve(&(b->ls));
  
  if (info==0)
    {	
      /* x=x-s */
      for(i=0;i<b->n;i++)
	{
	  x[i]-=b->s[i];
	  if ((tp!=NULL)&&(tp[i]==TOPOLOGY_S))
	    PI2PI(x[i]);
	}
      
      #if (_DEBUG>6)
	sprintf(label,"               s_%u",b->it);PrintVector(stderr,label,b->n,b->s);
	sprintf(label,"               x_%u",b->it);PrintVector(stderr,label,b->n,x);
      #endif
    }

  /* Save the residue before re-computing it */
  memcpy(b->resp,b->res,sizeof(double)*b->n);
  
  b->it++;
  
  #if (_DEBUG>6)
    free(label);
  #endif
    
  return(info);
}

void BroydenUpdateJacobian(double epsilon,TBroyden *b)
{
  double dif;
  
  /* Update the Jacobian matrix 

     Note that in our case b->s is actuall -delta_x as defined in
     the textbooks. This introduces some sign changes

      S = S+((res-resp)-S*(-s))*(-s)'/((-s)'*(-s)); <- Evaluated in BroydenUpdateJacobian
      S = S-(r+S*s)*s'/(s'*s);
      S = S-(r+p)*s'/(s'*s);
      S = S-p*s'/(s'*s);

   */

  /* Wikipedia (et al) version */
  dif=GeneralDotProduct(b->n,b->s,b->s);
  DifferenceVector(b->n,b->res,b->resp,b->r);
  MatrixVectorProduct(b->n,b->n,b->B,b->s,b->p); 
  AccumulateVector(b->n,b->r,b->p);
  RankOneUpdate(-1.0/dif,b->n,b->p,b->n,b->s,b->B);
      
  /*
    fprintf(stderr,"    dif: %.19f \n",dif);
    fprintf(stderr,"    t:%.19f\n",Norm(b->n,b->r));
    PrintVector(stderr,"    s",b->n,b->s);
    PrintVector(stderr,"    res",b->n,b->res);
    PrintVector(stderr,"    resp",b->n,b->resp);
    PrintVector(stderr,"    r",b->n,b->r);
    PrintVector(stderr,"    p",b->n,b->p);
    PrintMatrix(stderr,"    B",b->n,b->n,b->B);
  */
}

void DeleteBroyden(TBroyden *b)
{
  DeleteLS(&(b->ls));

  free(b->B);
  free(b->res);
  free(b->resp);
  free(b->r);
  free(b->p);
}
