#include "bioworld.h"

#include "babel.h"
#include "link.h"
#include "joint.h"
#include "polyhedron.h"
#include "filename.h"
#include "algebra.h"
#include "chart.h"
#include "samples.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

/** 
    \file bioworld.c

    \brief Implementation of the bridge between mechanical and biological information.

    Implementation of the bridge between world structures and
    biological information.

    \sa bioworld.h
*/

/****************************************************************************/

/** 
    \brief Read the list of residues to be considered flexible.

    Attempts to read a list of residues whose internal degrees of freedom
    are to be considered flexible. If the file with the list is not
    available, the degrees of freedom are deduced from the bond type:
    double bonds are rigid and single bonds define rotations
    
    This is intented to be used to model loops in proteins where only
    a small part of the protein must move.

    Note that only the backbone rotations between the N-Calpha and 
    Calpha-C atoms are considered. Lateral chains are fixed.

    \param fname The problem name used to define the namd of the file
                 with the residues
    \param nr Output. The number of residues readed. O if none.
    \param ch Output. The chain including the residues (all are in the same chain).
    \param r Output. The array with the residues. NULL if none is read.
*/
void ReadResidueList(char *fname,unsigned int *nr,char *ch,unsigned int **r);

/** 
    \brief Read the list of rigids and hinges of a molecule.

    Attempts to read a list of rigids and hinges of a molecule.
    This was implemented to test the examples provided by
    Adnan Sljoka.

    The list of rigids is just a list of all atoms in the molecule
    with the associated rigid. RigidID 0 is used for atoms not
    assigned to any rigid. The un-assigned atoms not involved
    in the hinges (see below) are not modelled.

    The hinges is a list of pairs of atoms defining rotation
    joints. These joints can correspond to actual bonds between
    atoms or to hydrogen bonds (not explicit). 

    Typically we will have two rigid bodies and several
    chains connecting them. The chains are composed by
    revolute joints only. In the chains, we use the normal policy of
    considering fixed all the bonds not included in the list
    of bonds defining the hinge.
    Thus, several small rigids might appear in the chains.

    Note that the read fails if the rigids or the hinges can
    not be fully read.

    This function can only be used after calling \ref GetMoleculeBasicInfo and
    after setting the atom positions.

    \param fname The problem name used to define the namd of the file
                 with the residues
    \param r Output. The ridid for each atom. NULL if the read fails.
    \param nh Output. Number of flexible bonds in the hinges
              0 if the read fails.
    \param h1 Output. Indexes of the first atom defining the bonds in
              the hinges. NULL if the read fails.
    \param h2 Output. Indexes of the second atom defining the bonds in
              the hinges. NULL if the read fails.
    \param added TRUE if we had to add an artificial bond in between
                 atoms h1[] and h2[] in order to define the joint.
		 These artifial bonds are needed in \ref InitWorldFromMolecule
		 but are latter removed.
    \param bw The BioWorld to update.
*/
void ReadRigidsAndHinges(char *fname,unsigned int **r,
			 unsigned int *nh,unsigned int **h1,unsigned int **h2,boolean **added,
			 TBioWorld *bw);

/** 
    \brief Collects the basic information about the molecule.

    Collects the basic information about the molecule such as the
    number of atoms, the number of bonds per atoms, the total number
    of bonds,...

    This is part of the BioWorld initialization.

    \param bw The BioWorld to update.
*/
void GetMoleculeBasicInfo(TBioWorld *bw);

/** 
    \brief Initializes the atom positions in a BioWorld.

    Initializes the atom positions in a BioWorld using an external file of 
    atoms or, if the file is not available, from the molecular information.

    This is part of the BioWorld initialization.

    \param fname Name for the file with the atom positions.
    \param pos Array where to store the atom positions.
    \param bw The partially initalized BioWorld.
*/
void GetAtomPositions(char *fname,double *pos,TBioWorld *bw);

/** 
    \brief Determines the rigid groups of atoms and the connections between them.

    Determines the rigid groups of atoms (links) and the connections between 
    them (joints).

    This function can only be used after calling \ref GetMoleculeBasicInfo and
    after setting the atom positions.

    \param bw The BioWorld to initialize.	
*/
void DetectLinksAndJoints(TBioWorld *bw);

/** 
    \brief Determines the rigid groups of atoms and the connections between them.

    Determines the rigid groups of atoms (links) and the connections between 
    them (joints) for proteins by fixing all the degrees of freedom but
    those for a list of residues. The residue information is read
    from file using \ref ReadResidueList.

    This function can only be used after calling \ref GetMoleculeBasicInfo and
    after setting the atom positions.

    \param nr The number of residues.
    \param ch The chain including the flexible residues.
    \param rID The identifiers of the residues to free.
    \param bw The BioWorld to initialize.	
*/
void DetectLinksAndJointsFromResidues(unsigned int nr,char ch,unsigned int *rID,TBioWorld *bw);

/** 
    \brief Determines the rigid groups of atoms and the connections between them.

    Determines the rigid groups of atoms (links) and the connections between 
    them (joints) for proteins taking into account the provide
    rigid/hinge information. This information is read from file using
    \ref ReadRigidsAndHinges.

    This function can only be used after calling \ref GetMoleculeBasicInfo and
    after setting the atom positions.

    \param rg The rigid for each atom (0 if the atom is not assigned to rigid).
    \param nh Number of bonds defining the hinges.
    \param h1 The first atom in the bonds defining the hinges.
    \param h2 The second atom in the bonds defining the hinges.
    \param bw The BioWorld to initialize.
*/
void DetectLinksAndJointsFromRigidsAndHinges(unsigned int *rg,
					     unsigned int nh,unsigned int *h1,unsigned int *h2,
					     TBioWorld *bw);

/** 
    \brief Generates a transform from a gobal frame to a local frame for each link.

    Generates a transform from a gobal frame to a local frame for each
    link.  The global frame is attached to the first link (i.e., its
    transform is the identity).

    The local frame attachd to each link (link=rigid group of atoms)
    is defined from the first atom in the link with at least two
    bonds. The first bond defines the X axis, the plane including the
    two bonds defines the X-Y plane and Z is just a vector orthogonal
    to this plane.

    By defining these local frames, we can readily obtain the
    configuration for a given conformation from the position of the
    atoms, irrespectively of the frame where these positions are
    defined.

    Note that this function does not requires a fully defined BioWorld
    since it only uses the list of atoms for each link (i.e., the
    world is not used).

    \param p The set of parameters.
    \param atoms Array with the position of the atoms.
    \param t Output array with the "local to global" transform for 
             each link. The space for this array mus t be 
	     allocated/released externally.
    \param bw The bioworld with the link information.
*/
void Atoms2Transforms(Tparameters *p,double *atoms,THTransform *t,
		      TBioWorld *bw);

/** 
    \brief Defines a world from molecular information.

    Defines a mechanical structure (a world) from molecular information.

    \param p The set of parameters.
    \param conformation Conformation given by the atom positions.
    \param maxAtomsLink Links with more atoms than this limit are
                        represented in wireframe. This is faster
			for visualization but it does not allow
			to detect collisions with the link.
			This is to be used only for visualization.
			Use NO_UINT for no limit (all in facy).
    \param bw The bioworld to initialize.
*/
void InitWorldFromMolecule(Tparameters *p,double **conformation,
			   unsigned int maxAtomsLink,TBioWorld *bw);

/********************************************************************/
/********************************************************************/

void ReadResidueList(char *fname,unsigned int *nr,char *ch,unsigned int **r)
{
  Tfilename fres;
  FILE *f;
  int out;
  unsigned int i,m,v;

  CreateFileName(NULL,fname,NULL,RES_EXT,&fres);
  f=fopen(GetFileFullName(&fres),"r");
  if (!f)
    {
      (*nr)=0;
      (*r)=NULL;
    }
  else
    {
      fprintf(stderr,"Reading residues from             : %s\n",GetFileFullName(&fres));
      /* first read the chain */
      fscanf(f,"%c",ch);
      if ((*ch>='a')&&(*ch<='z')) 
	*ch+=('A'-'a'); /* to upper */
      if ((*ch<'A')||(*ch>'Z'))
	Error("Wrong chain in the residue file");
      /* now the residue identifieres */
      (*nr)=0;
      m=10;
      NEW(*r,m,unsigned int);
      do {
	out=fscanf(f,"%u",&v);
	if (out==1)
	  {
	    (*r)[*nr]=v;
	    (*nr)++;
	    if (*nr==m)
	      { MEM_DUP(*r,m,unsigned int); }
	  }
      } while ((out==1)&&(out!=EOF));
      fclose(f);
      fprintf(stderr,"  Residues                        : %c",*ch);
      for(i=0;i<*nr;i++)
	fprintf(stderr," %u",(*r)[i]);
      fprintf(stderr,"\n");
    }
  DeleteFileName(&fres);
}

void ReadRigidsAndHinges(char *fname,unsigned int **r,
			 unsigned int *nh,unsigned int **h1,unsigned int **h2,boolean **added,
			 TBioWorld *bw)
{
  Tfilename fr,fh;
  FILE *f1,*f2;
  int out;
  unsigned int i,m,n,v;

  (*r)=NULL;
  (*nh)=0;
  (*h1)=NULL;
  (*h2)=NULL;
  (*added)=NULL;

  CreateFileName(NULL,fname,NULL,RIGID_EXT,&fr);
  f1=fopen(GetFileFullName(&fr),"r");
  CreateFileName(NULL,fname,NULL,HINGE_EXT,&fh);
  f2=fopen(GetFileFullName(&fh),"r");
  if ((f1)&&(f2))
    {
      fprintf(stderr,"Reading rigids from               : %s\n",GetFileFullName(&fr));
      
      NEW(*r,bw->na,unsigned int);
      /* initialy assign the atoms to no link */
      for(i=0;i<bw->na;i++)
	(*r)[i]=0;
      /* scan the list of ridig assigments */
      do {
	out=fscanf(f1,"%u",&n); //num atom (from 1)
	if (n>bw->na)
	  Error("Missmatch between the molecule and the rigid");
	if (out==1)
	  {
	    out=fscanf(f1,"%u",&v); //num rigid
	    if (out==1)
	      (*r)[n-1]=v;
	  }
      } while ((out==1)&&(out!=EOF));
      fclose(f1);

      /* ensure that links are numbered from 1 */
      n=0;
      for(i=0;i<bw->na;i++)
	{
	  if ((*r)[i]>0)
	    {
	      if ((n==0)||((*r)[i]<n))
		n=(*r)[i];
	    }
	}
      if (n==0)
	Error("Wrong rigid information in ReadRigidsAndHinges");
      if (n>1)
	{	 
	  n--;
	  /* Offset the ridig ID so that it starts at 1. */
	  for(i=0;i<bw->na;i++)
	    {
	      if ((*r)[i]>0)
		(*r)[i]-=n;
	    }
	}

      /* Reading the hinges */
      fprintf(stderr,"Reading hinges from               : %s\n",GetFileFullName(&fh));
      m=10;
      NEW(*h1,m,unsigned int);
      NEW(*h2,m,unsigned int);
      NEW(*added,m,boolean);
      do {
	out=fscanf(f2,"%u",&n); //num atom1 (from 1)
	if (out==1)
	  {
	    out=fscanf(f2,"%u",&v); //num atoms2 (from 1)
	    if (out==1)
	      {
		(*h1)[*nh]=n-1;
		(*h2)[*nh]=v-1;

		/* Some of the joints might be defined over
		   unconnected atoms (h-bonds). We add them. */
		if (!HasBond(n-1,v-1,bw->m))
		  {
		    AddBond(n-1,v-1,bw->m);
		    bw->nbAtom[n-1]++;
		    bw->nbAtom[v-1]++;
		    bw->nb+=2;
		    (*added)[*nh]=TRUE;
		  }
		else
		  (*added)[*nh]=FALSE;

		(*nh)++;

		if (*nh==m)
		  { 
		    MEM_DUP(*h1,m,unsigned int); 
		    MEM_EXPAND(*h2,m,unsigned int); 
		    MEM_EXPAND(*added,m,boolean); 
		  }
	      }
	  }
      } while ((out==1)&&(out!=EOF));
      fclose(f2);

      if ((*nh)==0)
	{
	  if ((*r)!=NULL)
	    free(*r);
	  if ((*h1)!=NULL)
	    free(*h1);
	  if ((*h2)!=NULL)
	    free(*h2);
	  (*nh)=0;
	}
    }
   DeleteFileName(&fr);
   DeleteFileName(&fh);
}

void GetMoleculeBasicInfo(TBioWorld *bw)
{
  unsigned int i,j;
  TBondIterator *it;
  boolean fix;

  bw->na=nAtoms(bw->m);
  if (bw->na==2)
    Error("Too small molecule (only 2 atoms!)");

  /* Number of bonds for each atom */
  NEW(bw->nbAtom,bw->na,unsigned int);
  for(i=0;i<bw->na;i++)
    {
      #if (_DEBUG>1)
        printf("Atom %u [%g]-> ",i,VdWRadius(i,bw->m));
      #endif
      j=GetFirstNeighbour(i,&fix,&it,bw->m);
      bw->nbAtom[i]=0;
      while(j!=NO_UINT)
	{
	  #if (_DEBUG>1)
	    if (fix)
	      printf("=%u ",j);
	    else
	      printf("-%u ",j);
	  #endif
	  bw->nbAtom[i]++;
	  j=GetNextNeighbour(i,&fix,it,bw->m);
	}
      DeleteBondIterator(it);
      bw->nb+=bw->nbAtom[i];
      bw->nba+=(bw->nbAtom[i]*(bw->nbAtom[i]-1));
      #if (_DEBUG>1)
        printf("\n");
      #endif
    }
}

void GetAtomPositions(char *fname,double *pos,TBioWorld *bw)
{
  Tfilename fatoms;
  unsigned int i,j,l;
  FILE *f;

  /* Atom positions in the pdb are given with very low accuracy
     We try to use better estimations, if available. */
  CreateFileName(NULL,fname,NULL,ATOM_EXT,&fatoms);

  f=fopen(GetFileFullName(&fatoms),"r");
  if (!f)
    GetAtomCoordinates(pos,bw->m);
  else
    {
      /* the atoms file must include the 3D position of each
         atom in the same order as listed in the pdb */
      fprintf(stderr,"Reading atom positions from       : %s\n",GetFileFullName(&fatoms));

      l=0;
      for(i=0;i<bw->na;i++)
	{
	  for(j=0;j<3;j++,l++)
	    fscanf(f,"%lf",&(pos[l]));
	}
      fclose(f);
    }
  DeleteFileName(&fatoms);

  #if (_DEBUG>2)
    for(i=0,j=0;i<bw->na;i++,j+=3)
      printf("%g %g %g\n",pos[j],pos[j+1],pos[j+2]);
  #endif
}

void DetectLinksAndJoints(TBioWorld *bw)
{
  unsigned int i,n,k,l1,r,l;
  boolean fix;
  TBondIterator *it;

  NEW(bw->linkID,bw->na,unsigned int);
  NEW(bw->linkList,bw->na,unsigned int);
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->links));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint1));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint2));
  
  for(i=0;i<bw->na;i++)
    bw->linkID[i]=NO_UINT;

  bw->cut=FALSE; /* all atoms will be used to define the world */

  n=0;      /* atoms assigned to link so far */
  k=0;      /* atom to process next */
  bw->nl=0; /* Number of links so far */
  bw->nj=0; /* Number of joints so far */
  while(n<bw->na)
    {
      /* Skip atoms already assigned and isolated atoms */
      while ((bw->linkID[k]!=NO_UINT)||(bw->nbAtom[k]<=1)) k++;

      NewVectorElement((void*)&k,&(bw->links)); /* atom 'k' starts a new link */
      bw->linkList[k]=NO_UINT; /* mark end of list */
      bw->linkID[k]=bw->nl;
      n++;      /* ane atom more already assigned */

      l1=k;     /* last atom added to the solid */
      r=l1;     /* last expanded atom in the solid */

      /* Check if the link can be extended from any of the atoms
         already in it -> discard  */
      while (r!=NO_UINT)
	{
	  /* Terminal atoms are reached by other atoms in the rigid group
	     and are not a point from where to extend the rigid. */
	  if (bw->nbAtom[r]>1)
	    {
	      l=GetFirstNeighbour(r,&fix,&it,bw->m); /* 1st neigh. for atom 'r' */
	      /* Check all neighbours for atom 'r' */
	      while(l!=NO_UINT)
		{
		  /* If not visited and the bond to the atom is double or if
		     the atom is isolated -> add to the link */
		  if ((fix)||(bw->nbAtom[l]==1))
		    {
		      if (bw->linkID[l]==NO_UINT)
			{
			  bw->linkList[l1]=l;
			  bw->linkList[l]=NO_UINT; /* end of list */ 
			  bw->linkID[l]=bw->nl;
			  n++;
			  
			  l1=l; /* we have a new last atom in the link */
			}
		    }
		  else
		    {
		      if (r<l) /* avoid defining the same joint twice */
			{
			  NewVectorElement((void*)&r,&(bw->joint1));
			  NewVectorElement((void*)&l,&(bw->joint2));
			  bw->nj++;
			}
		    }
		  /* move to next */
		  l=GetNextNeighbour(r,&fix,it,bw->m); /* Next neigh. for 'r' */
		}
	      DeleteBondIterator(it);
	    }
	  /* Go for next atom in the rigid (if any) */
	  r=bw->linkList[r];
	}
      bw->nl++; /* we have a new link */
    }
}

void DetectLinksAndJointsFromResidues(unsigned int nr,char ch,unsigned int *rID,TBioWorld *bw)
{
  unsigned int i,j,k,l1,lz,r,l,ar;
  boolean fix,found,revolute,proline;
  unsigned int *nID,*caID,*cID;
  TBondIterator *it;
  double *pos;

  if ((nr==NO_UINT)||(rID==NULL))
    Error("Using DetectLinksAndJointsFromResidues with an empty list of residues");

  /* Ensure that the residues are increasing */
  for(i=1;i<nr;i++)
    {
      if (rID[i-1]>=rID[i])
	Error("The residue identifiers must be sorted (increasing)");
    }

  NEW(bw->linkID,bw->na,unsigned int);
  NEW(bw->linkList,bw->na,unsigned int);
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->links));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint1));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint2));

  for(i=0;i<bw->na;i++)
    bw->linkID[i]=NO_UINT;

  /* Only have joints in between N-Calpha and Calpha-C fore ach residue */
  /* Assume that the N C-alpha and C are the first 3 atoms for each residue 
     and look for them, storing their indices */
  NEW(nID,nr,unsigned int);
  NEW(caID,nr,unsigned int);
  NEW(cID,nr,unsigned int);
  
  for(i=0;i<nr;i++)
    {
      nID[i]=NO_UINT;
      caID[i]=NO_UINT;
      cID[i]=NO_UINT;
    }

  for(i=0;i<bw->na;i++)
    {
      ar=GetAtomResidue(i,bw->m);
      
      /* if the atom is in a residue of the correct chain */
      if ((ar!=NO_UINT)&&(GetAtomChain(i,bw->m)==ch))
	{
	  /* If this is one of the flexible residues ... */
	  j=0;
	  found=FALSE;
	  while((!found)&&(j<nr))
	    {
	      found=(ar==rID[j]);
	      if (!found) j++;
	    }

	  if (found)
	    {
	      if (nID[j]==NO_UINT)
		nID[j]=i;  /* First atom in res. */
	      else
		{
		  if (caID[j]==NO_UINT)
		    caID[j]=i; /* Second atom in res. */
		  else
		    {
		      if (cID[j]==NO_UINT)
			cID[j]=i; /* Third atom in res. */
		    }
		}
	    }
	}
    }

  /* Some checks to ensure that everything is fine */
  for(i=0;i<nr;i++)
    {
      if ((nID[i]==NO_UINT)||(caID[i]==NO_UINT)||(cID[i]==NO_UINT))
	Error("Undefined residue");
    } 

  /* Adjust the bounding box  including the loop */
  bw->cut=TRUE; /* only the atoms in a given box will be used to
		   define the world */
  pos=&(bw->pos[3*nID[0]]);
  InitBoxFromPoint(3,pos,&(bw->cutB));
  for(i=nID[0];i<=cID[nr-1];i++)
    {
      pos=&(bw->pos[3*i]);
      ExpandBox(pos,&(bw->cutB));
    }
  bw->cut=FALSE; /* Not actually using the bounding box .... FIX THIS */

  /* Now define the links and joints */

  /* Reserve link 0 for the non-mobile residues (link 0 is the ground link, the
     one the defines the global reference frame).
     Right now we just initialize it. We will add more atoms after 
     defining the mobile links. */
  lz=nID[0];                                 /* This will be fist atom in link 0 */
  NewVectorElement((void*)&lz,&(bw->links)); /* atom 'lz' starts a new link */
  bw->linkList[lz]=NO_UINT;                  /* mark end of list */
  bw->linkID[lz]=0;                          /* 'lz' is part of link 0 */
  bw->nl=1;                                  /* we have one link */

  bw->nj=0;                                  /* Number of joints so far */

  /* Now define the mobile links, two per flexible residue, except for the last one
     (it connects to link 0) */
  for(i=0;i<2*nr-1;i++)
    {
      k=i/2; /* number in the array of flexible residues */
      /* Select the atom from which to start the current rigid group of atoms */
      if ((i%2)==0)
	r=caID[k];
      else
	r=cID[k];

      /* Initialize the group with the selected atom */
      NewVectorElement((void*)&r,&(bw->links)); /* atom 'r' starts a new link */
      bw->linkList[r]=NO_UINT;                  /* mark end of list */
      bw->linkID[r]=bw->nl;

      l1=r;     /* last atom added to the solid */

      /* Add atoms to the group propagating over the atom bonds recursively. 
         Do not propatage through the rotable bonds. N-Ca-C */
      while (r!=NO_UINT)
	{
	  /* Terminal atoms are reached by other atoms in the rigid group
	     and are not a point from where to extend the rigid. 
	     Isolated atoms at the end of the loop are also considered, though */
	  if (bw->nbAtom[r]>1)
	    {
	      l=GetFirstNeighbour(r,&fix,&it,bw->m); /* 1st neigh. for atom 'r' */

	      /* Check all neighbours for atom 'r' */
	      while(l!=NO_UINT)
		{
		  /* Do not propagate via the proline loop: Skip the bond closing over the
		     N atom in the backbone */
		  if ((IsAtomInProline(r,bw->m))&&(GetAtomResidue(r,bw->m)==rID[k])&&(GetAtomResidue(l,bw->m)==rID[k]))
		    proline=(((r==nID[k])&&(GetAtomicNumber(l,bw->m)==6)&&(l!=caID[k]))||
			     ((l==nID[k])&&(GetAtomicNumber(r,bw->m)==6)&&(r!=caID[k])));
		  else
		    proline=FALSE;
	
		  if (!proline)
		    {
		      /* Propagating from a Calpha atom ->  the expansion is limited by C-Ca and
			 the Ca-C bonds in the current resiude
			 Propagating from a  C atom -> the expansion is limited by C-Ca bond
			 in the current residue and the N-Ca bond in the next one */
		      if (i%2==0) 
			revolute=(((r==caID[k])&&(l==nID[k]))||
				  ((r==caID[k])&&(l==cID[k])));
		      else
			revolute=(((r==cID[k])&&(l==caID[k]))||
				  ((r==nID[k+1])&&(l==caID[k+1])));

		      if (revolute)
			{
			  /* Actually, revolute bonds define a joint */
			  if (r==caID[k]) /* but not twice! */
			    {
			      NewVectorElement((void*)&r,&(bw->joint1));
			      NewVectorElement((void*)&l,&(bw->joint2));
			      bw->nj++;
			    }
			}
		      else
			{
			  if (bw->linkID[l]==NO_UINT) /* atom still not assigned to any link */
			    {
			      bw->linkList[l1]=l;
			      bw->linkList[l]=NO_UINT; /* end of list */ 
			      bw->linkID[l]=bw->nl;
			      
			      l1=l; /* we have a new last atom in the link */
			    }
			}
		    }
		  /* move to next bonded atom */
		  l=GetNextNeighbour(r,&fix,it,bw->m); /* Next neigh. for 'r' */
		}
	      /* Delete the iterator over bonded atoms */
	      DeleteBondIterator(it);
	    }
	  /* Go for next atom in the rigid (if any) and propagate form them */
	  r=bw->linkList[r];
	}
      bw->nl++; /* we have a new link */
    }

  /* All the non-assigned atoms must be in link 0 (even if not linked between them) */
  for(i=0;i<bw->na;i++)
    {
      if (bw->linkID[i]==NO_UINT)
	{
	  bw->linkList[lz]=i;
	  bw->linkList[i]=NO_UINT;
	  bw->linkID[i]=0; 
	  lz=i;
	}
    }

  /* Release index of key atoms */
  free(nID);
  free(caID);
  free(cID);
}

void DetectLinksAndJointsFromRigidsAndHinges(unsigned int *rg,
					     unsigned int nh,unsigned int *h1,unsigned int *h2,
					     TBioWorld *bw)
{
  unsigned int i,j,k,l1,lz,r,l,m,nl;
  boolean fix,found,stop;
  TBondIterator *it;

  if ((rg==NULL)||(nh==NO_UINT)||(nh==0)||(h1==NULL)||(h2==NULL))
    Error("Using DetectLinksAndJointsFromRigidsAndHinges with an empty list of residues");

  NEW(bw->linkID,bw->na,unsigned int);
  NEW(bw->linkList,bw->na,unsigned int);
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->links));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint1));
  InitVector(sizeof(unsigned int),CopyID,DeleteID,10,&(bw->joint2));

  for(i=0;i<bw->na;i++)
    bw->linkID[i]=NO_UINT;

  bw->cut=FALSE;

  /* Now define the links and joints */
  /* Define the given ridigs */
  /* determine the maximum id for the given rigids */
  m=0;
  for(i=0;i<bw->na;i++)
    {
      if ((rg[i]!=NO_UINT)&&(rg[i]>m)) m=rg[i];
    }
  /* for all the rigids  */
  bw->nl=0;
  for(i=1;i<=m;i++) /* rigids are num. from 1 */
    {
      found=FALSE;
      lz=0;
      while ((!found)&&(lz<bw->na))
	{
	  found=(rg[lz]==i);
	  if (!found)
	    lz++;
	}
      if (found)
	{
	  /* 'lz' is the first atom of the rigid bw->nl */
	  if (bw->linkID[lz]!=NO_UINT)
	    Error("Atom assigned to two different rigids");

	  NewVectorElement((void*)&lz,&(bw->links)); /* atom 'lz' starts a new link */
	  bw->linkList[lz]=NO_UINT;                  /* mark end of list */
	  bw->linkID[lz]=bw->nl;                     /* 'lz' is part of link 0 */
	  for(j=lz+1;j<bw->na;j++)
	    {
	      if (rg[j]==i)
		{
		  if (bw->linkID[j]!=NO_UINT)
		    Error("Atom assigned to two different rigids");
		  bw->linkList[lz]=j;
		  bw->linkList[j]=NO_UINT;
		  bw->linkID[j]=bw->nl; 
		  lz=j;
		}
	    }
	  bw->nl++;
	}
    }

  /* Now define the rigids from the joints. This must somehow connect
     the given rigids */
  nl=bw->nl;

  for(i=0;i<2*nh;i++)
    {
      k=i/2; /* number in the array of joints */
      /* Select one of the atoms at the end of a joint */
      if ((i%2)==0)
	r=h1[k];
      else
	r=h2[k];

      /* if the atom is not yet in a rigid.... */
      if (bw->linkID[r]==NO_UINT)
	{
	  /* Initialize the group with the selected atom */
	  NewVectorElement((void*)&r,&(bw->links)); /* atom 'r' starts a new link */
	  bw->linkList[r]=NO_UINT;                  /* mark end of list */
	  bw->linkID[r]=bw->nl;

	  l1=r;     /* last atom added to the solid */

	  /* Propagate from atom 'r' */
	  while (r!=NO_UINT)
	    {
	      /* Terminal atoms are reached by other atoms in the rigid group
		 and are not a point from where to extend the rigid. 
		 Isolated atoms at the end of the loop are also considered, though */
	      if (bw->nbAtom[r]>1)
		{
		  l=GetFirstNeighbour(r,&fix,&it,bw->m); /* 1st neigh. for atom 'r' */

		  /* Check all neighbours for atom 'r' */
		  while(l!=NO_UINT)
		    {
		      /* stop the expansion if we reach a solid or if (l,r) is one of the
			 given joints */
		      if (bw->linkID[l]!=NO_UINT)
			stop=TRUE;
		      else
			{
			  stop=FALSE;
			  k=0;
			  while((!stop)&&(k<nh))
			    {
			      stop=(((h1[k]==r)&&(h2[k]==l))||((h1[k]==l)&&(h2[k]==r)));
			      k++;
			    }
			}
	
		      if (!stop)
			{
			  /* atom 'l' has to be added to the link */
			  bw->linkList[l1]=l;
			  bw->linkList[l]=NO_UINT; /* end of list */ 
			  bw->linkID[l]=bw->nl;
		      
			  l1=l; /* we have a new last atom in the link */
			}
		      /* move to next bonded atom */
		      l=GetNextNeighbour(r,&fix,it,bw->m); /* Next neigh. for 'r' */
		    }
		  /* Delete the iterator over bonded atoms */
		  DeleteBondIterator(it);
		}
	      /* Go for next atom in the rigid (if any) and propagate form it */
	      r=bw->linkList[r];
	    }
	  bw->nl++; /* we have a new link */
	}
    }

  /* Try to expand the given rigids as much as possible to capture un-assigned atoms */
  for(i=0;i<nl;i++)
    {
      r=*(unsigned int*)GetVectorElement(i,&(bw->links)); /* First atom in the link */
      if (r==NO_UINT)
	Error("A link without atoms?");

      /* determine the last atom added to this link */
      j=r;
      l1=NO_UINT;
      while(j!=NO_UINT)
	{
	  l1=j;
	  j=bw->linkList[j];
	}

      /* Propagate from atom 'r' */
      while (r!=NO_UINT)
	{
	  if (bw->nbAtom[r]>1)
	    {
	      l=GetFirstNeighbour(r,&fix,&it,bw->m); /* 1st neigh. for atom 'r' */

	      /* Check all neighbours for atom 'r' */
	      while(l!=NO_UINT)
		{
		  /* if we reach a non-assigned atom 'l' */
		  if (bw->linkID[l]==NO_UINT)
		    {
		      /* atom 'l' has to be added to the link */
		      bw->linkList[l1]=l;
		      bw->linkList[l]=NO_UINT; /* end of list */ 
		      bw->linkID[l]=i;
		      
		      l1=l; /* we have a new last atom in the link */
		    }
		  /* move to next bonded atom */
		  l=GetNextNeighbour(r,&fix,it,bw->m); /* Next neigh. for 'r' */
		}
	      /* Delete the iterator over bonded atoms */
	      DeleteBondIterator(it);
	    }
	  /* Continue propagation from the just added atoms */
	  r=bw->linkList[r];
	}
    }

  /* joints are given as parameters */
  bw->nj=nh; 
  for(i=0;i<bw->nj;i++)
    {
      NewVectorElement((void*)&(h1[i]),&(bw->joint1));
      NewVectorElement((void*)&(h2[i]),&(bw->joint2));
    }
}

void Atoms2Transforms(Tparameters *p,double *atoms,THTransform *t,TBioWorld *bw)
{
  unsigned int l,i,j,k;
  boolean fix;
  TBondIterator *it;
  double *p1,*p2,*p3;
  double x[3],y[3],z[3];
  boolean found;
  /*
  double c;
  double v1[3],v2[3];
  double epsilon;
  */

  for(l=0;l<bw->nl;l++)
    {
      /* first atom in the link */
      i=*(unsigned int *)GetVectorElement(l,&(bw->links));
      j=NO_UINT;
      k=NO_UINT;
      
      /* If we are in a protein try to get the pre-defined 
         reference frame */
      if (GetAtomResidue(i,bw->m)!=NO_UINT)
	{
	  /* Check if we are in the first rigid of the residue N-Ca-C */
	  /* We assume that atoms in a residue are given in order N-Ca-C */
	  found=FALSE;
	  while ((!found)&&(i!=NO_UINT))
	    {
	      found=((i>0)&&
		     (GetAtomicNumber(i,bw->m)==6)&&   /*Ca*/
		     (GetAtomicNumber(i-1,bw->m)==7)&& /*N */
		     (GetAtomicNumber(i+1,bw->m)==6)&& /*C */
		     (GetAtomResidue(i,bw->m)==GetAtomResidue(i-1,bw->m))&&
		     (GetAtomResidue(i,bw->m)==GetAtomResidue(i+1,bw->m))&&
		     (HasBond(i,i-1,bw->m))&&
		     (HasBond(i,i+1,bw->m)));
	      if (!found)
		i=bw->linkList[i];
	    }
	  if (found)
	    {
	      /* i = Ca */
	      j=i+1; /* C  */
	      k=i-1; /* N */
	    }
	  else
	    {
	      /* Check if we are in the second ridig of the residue Ca-C-N */
	      /* here Ca-C are in the same res. and num. consecutively but
	         N is in next residue and non-consecutive */
	      i=*(unsigned int *)GetVectorElement(l,&(bw->links));
	      while ((!found)&&(i!=NO_UINT))
		{
		  j=GetFirstNeighbour(i,&fix,&it,bw->m);
		  while ((!found)&&(j!=NO_UINT))
		    {
		      found=((i>0)&&
			     (GetAtomicNumber(i,bw->m)==6)&&   /*C */
			     (GetAtomicNumber(i-1,bw->m)==6)&& /*Ca*/
			     (GetAtomicNumber(j,bw->m)==7)&&   /*N */
			     (GetAtomResidue(i,bw->m)==GetAtomResidue(i-1,bw->m))&&
			     (GetAtomResidue(i,bw->m)+1==GetAtomResidue(j,bw->m))&&
			     (HasBond(i,i-1,bw->m))&&
			     (HasBond(i,j,bw->m)));
		      if (!found)
			j=GetNextNeighbour(i,&fix,it,bw->m);
		    }
		  DeleteBondIterator(it);
		  if (!found)
		    i=bw->linkList[i];
		}
	      if (found)
		{
		  /* i = Ca */
		  /* j = N */
		  k=i-1; /* C*/
		}
	    }
	}

      /* if the previous strategy did not work just pick any 3 atoms 
         in the link */
      if ((i==NO_UINT)||(j==NO_UINT)||(k==NO_UINT))
	{
	  i=*(unsigned int *)GetVectorElement(l,&(bw->links));
	  while((i!=NO_UINT)&&(bw->nbAtom[i]<2))
	    i=bw->linkList[i];

	  if (i==NO_UINT)
	    Error("A link with no valid atom to define a reference frame");

	  /* Note that 'j' and 'k' are not necessarily in the same link (=rigid
	     group of atoms) as atom 'i'. However, the bond between them define
	     a rigid angle and, thus, a fixed plane with respect to the link. */

	  /* We first try to avoid using isolated atoms as references */
	  j=GetFirstNeighbour(i,&fix,&it,bw->m);
	  if (j==NO_UINT)
	    Error("Inconsistency in BioWorld (Atoms2Transforms)");
	  while ((j!=NO_UINT)&&(bw->nbAtom[j]<2))
	    j=GetNextNeighbour(i,&fix,it,bw->m);
	  if (j!=NO_UINT)
	    {
	      k=GetNextNeighbour(i,&fix,it,bw->m);
	      while ((k!=NO_UINT)&&(bw->nbAtom[k]<2))
		k=GetNextNeighbour(i,&fix,it,bw->m);
	    }
	  DeleteBondIterator(it);

	  /* If not possible just use the first two atoms */
	  if ((j==NO_UINT)||(k==NO_UINT))
	    {
	      j=GetFirstNeighbour(i,&fix,&it,bw->m);
	      k=GetNextNeighbour(i,&fix,it,bw->m);
	      if (k==NO_UINT)
		Error("Inconsistency in BioWorld (Atoms2Transforms)");
	      DeleteBondIterator(it);
	    }
	}

      p1=&(atoms[3*i]);
      p2=&(atoms[3*j]);
      p3=&(atoms[3*k]);

      DifferenceVector(3,p2,p1,x);
      Normalize(3,x);

      DifferenceVector(3,p3,p1,y);
      Normalize(3,y);

      CrossProduct(x,y,z);
      Normalize(3,z);

      CrossProduct(z,x,y);
      Normalize(3,y); /* just for numerical accuracy */
      
      /*
      epsilon=GetParameter(CT_EPSILON,p);

      DifferenceVector(3,p2,p1,v1);
      Normalize(3,v1);

      DifferenceVector(3,p3,p1,v2);
      Normalize(3,v2);

      memcpy(x,v1,3*sizeof(double));

      c=DotProduct(v1,v2);
      if (fabs(1-fabs(c))<epsilon)
	Error("Aligned bonds");
      SumVectorScale(3,v2,-c,v1,y);
      ScaleVector(1.0/sqrt(1-c*c),3,y);

      CrossProduct(x,y,z);
      */

      HTransformFromVectors(x,y,z,p1,&(t[l]));

#if (0)
      fprintf(stderr,"Link %u: [%u %u %u]\n",l,i,j,k);
      if (l==0)
	HTransformPrint(stderr,&(t[l]));
#endif
    }
}

void InitWorldFromMolecule(Tparameters *p,double **conformation,
			   unsigned int maxAtomsLink,TBioWorld *bw)
{
  unsigned int rep,i,j,m,n;
  double *x,*y,*z;
  boolean fix,simple;
  Tpolyhedron sphere,cylinder,segments;  
  Tlink link;
  Tjoint joint;
  unsigned int k,l,nal;
  Tcolor defaultColor,carbon,sulphur,hydrogen,black,oxygen,nitrogen,red,green,blue,*atomColor;
  char name[100];
  double **jointPoint;
  double vdwRatio; /* ratio of Van der Waals radius used */
  double radius,*atomPos,endPoint[3];
  TBondIterator *it;
  THTransform *l2g;

  for(i=0;i<bw->na;i++)
    {
      if (bw->linkID[i]==NO_UINT)
	Error("Unassigned atom to link in InitWorldFromMolecule (this atom can not be correctly moved)");
    }

  /* Get the transform to global coordinates for each link. */
  NEW(l2g,bw->nl,THTransform);
  Atoms2Transforms(p,bw->pos,l2g,bw);

  /* Compute the global2local (inverse of local2global) */
  NEW(bw->g2l,bw->nl,THTransform);
  for(i=0;i<bw->nl;i++)
    HTransformInverse(&(l2g[i]),&(bw->g2l[i]));

  /* Use the transforms to compute the local coordinates of each atom */
  NEW(bw->localPos,bw->na*3,double);
  for(i=0,l=0;i<bw->na;i++,l+=3)
    {
      if (bw->linkID[i]!=NO_UINT) /* Only for actually used atoms */
	HTransformApply(&(bw->pos[l]),&(bw->localPos[l]),&(bw->g2l[bw->linkID[i]]));
    }

  /*Generate an empty world*/
  InitWorld(&(bw->w)); 

  /* Add the links to the world */
  NewColor(0.75,0.75,0.75,&defaultColor);
  NewColor(0.25,0.25,0.25,&carbon);
  NewColor(0.6,0.6,0.2,&sulphur);
  NewColor(1,1,1,&hydrogen);
  NewColor(1,0,0,&oxygen);
  NewColor(0,0,1,&nitrogen);
  NewColor(1,0,0,&red);
  NewColor(0,1,0,&green);
  NewColor(0,0,1,&blue);
  NewColor(0,0,0,&black);
  vdwRatio=GetParameter(CT_VDW_RATIO,p);

  for(i=0;i<bw->nl;i++)
    {
      /* Initialize the link */
      sprintf(name,"link_%u",i);
      InitLink(name,0.0,NULL,NULL,&link);

      /* Define a sphere for each atom in the link */
      /* Count the num. atoms in the link.  */
      k=*(unsigned int *)GetVectorElement(i,&(bw->links));
      nal=0; /* number atoms link */
      while (k!=NO_UINT)
	{
	  nal++;
	  k=bw->linkList[k];
	}
      /* If we have many atoms we use a simple representation */
      simple=((maxAtomsLink!=NO_UINT)&&(nal>=maxAtomsLink));

      if (simple)
	{
	  n=0;
	  m=100;
	  NEW(x,m,double);
	  NEW(y,m,double);
	  NEW(z,m,double);
	}

      /* first atom in the link */
      k=*(unsigned int *)GetVectorElement(i,&(bw->links));      
      do{
	/* Only consider atoms in a range +/-10 atoms around the cut
	   box, if any. */
	if ((!bw->cut)||(PointInBox(NULL,3,&(bw->pos[3*k]),GetBoxDiagonal(NULL,&(bw->cutB))/2,&(bw->cutB))))
	  {
	    atomPos=&(bw->localPos[3*k]);

	    radius=vdwRatio*VdWRadius(k,bw->m);

	    switch(GetAtomicNumber(k,bw->m))
	      {
	      case 1:
		atomColor=&hydrogen;
		break;
	      case 6:
		atomColor=&carbon;
		break;
	      case 7:
		atomColor=&nitrogen;
		break;
	      case 8:
		atomColor=&oxygen;
		break;
	      case 16:
		atomColor=&sulphur;
		break;
	      default:
		atomColor=&defaultColor;
	      }
	    if (simple)
	      NewSphere(radius,atomPos,atomColor,0,HIDDEN_SHAPE,&sphere);
	    else
	      NewSphere(radius,atomPos,atomColor,0,NORMAL_SHAPE,&sphere);
	    AddBody2Link(&sphere,&link);
	    DeletePolyhedron(&sphere);

	    /* A cylinder/line for each pair of bonded atoms.  */
	    j=GetFirstNeighbour(k,&fix,&it,bw->m);
	    while(j!=NO_UINT)
	      {	    
		if (simple)
		  {
		    if ((k<j)||(bw->linkID[j]!=bw->linkID[k]))
		      {
			/* the end point might be in another link and we
			   need its coordinates in this link */
			HTransformApply(&(bw->pos[3*j]),endPoint,&(bw->g2l[i]));
		    
			if (n>=m-1)
			  {
			    MEM_DUP(x,m,double);
			    MEM_EXPAND(y,m,double);
			    MEM_EXPAND(z,m,double);
			  }
			x[n]=atomPos[0];
			y[n]=atomPos[1];
			z[n]=atomPos[2];
			n++;
			x[n]=endPoint[0];
			y[n]=endPoint[1];
			z[n]=endPoint[2];
			n++;
		      }
		  }
		else
		  {
		    /* the end point might be in another link and we
		       need its coordinates in this link */
		    HTransformApply(&(bw->pos[3*j]),endPoint,&(bw->g2l[i]));
		    DifferenceVector(3,endPoint,atomPos,endPoint);
		    SumVectorScale(3,atomPos,0.5,endPoint,endPoint);

		    NewCylinder(0.15,atomPos,endPoint,atomColor,0,DECOR_SHAPE,&cylinder);
		    AddBody2Link(&cylinder,&link);
		    DeletePolyhedron(&cylinder);
		  }
		j=GetNextNeighbour(k,&fix,it,bw->m);
	      }
	    DeleteBondIterator(it);
	  }

	/* Go for next atom */
	k=bw->linkList[k];
      } while(k!=NO_UINT);
      
      if (simple)
	{
	  switch(i%4)
	    {
	    case 0:
	      NewSegments(n,x,y,z,&blue,&segments);
	      break;
	    case 1:
	      NewSegments(n,x,y,z,&green,&segments);
	      break;
	    case 2:
	      NewSegments(n,x,y,z,&red,&segments);
	      break;
	    case 3:
	      NewSegments(n,x,y,z,&black,&segments);
	      break;
	    }
	  AddBody2Link(&segments,&link);
	  DeletePolyhedron(&segments);
	  free(x);
	  free(y);
	  free(z);
	}

      AddLink2World(&link,FALSE,&(bw->w));
      DeleteLink(&link);
    }
  DeleteColor(&defaultColor);
  DeleteColor(&carbon);
  DeleteColor(&hydrogen);
  DeleteColor(&sulphur);
  DeleteColor(&black);

  /* Add the joints to the world */
  NEW(jointPoint,4,double*);
  for(i=0;i<4;i++)
    NEW(jointPoint[i],3,double);

  rep=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  for(i=0;i<bw->nj;i++)
    {
      k=*(unsigned int *)GetVectorElement(i,&(bw->joint1));
      l=*(unsigned int *)GetVectorElement(i,&(bw->joint2));

      HTransformApply(&(bw->pos[3*k]),jointPoint[0],
		      &(bw->g2l[bw->linkID[k]]));
      HTransformApply(&(bw->pos[3*l]),jointPoint[1],
		      &(bw->g2l[bw->linkID[k]]));

      HTransformApply(&(bw->pos[3*k]),jointPoint[2],
		      &(bw->g2l[bw->linkID[l]]));
      HTransformApply(&(bw->pos[3*l]),jointPoint[3],
		      &(bw->g2l[bw->linkID[l]]));

      NewRevoluteJoint(i,rep,
		       bw->linkID[k],GetWorldLink(bw->linkID[k],&(bw->w)),
		       bw->linkID[l],GetWorldLink(bw->linkID[l],&(bw->w)),
		       jointPoint,FALSE,FALSE,NULL,NULL,FALSE,0,NULL,
		       INF,INF,INF,1.0,0.0,0.0,
		       &joint);

      AddJoint2World(&joint,&(bw->w));
      DeleteJoint(&joint);
    }

  /* Release temporal information used in the world definition. */
  for(i=0;i<4;i++)
    free(jointPoint[i]);
  free(jointPoint);

  /* Post-process the world */
  if (bw->nl>0)
    {
      /* Check all collisions (between atoms in different rigids/links) */
      CheckAllCollisions(0,0,&(bw->w));
      /* Generate the kinematic equations */
      GenerateWorldEquations(p,NULL,NULL,&(bw->w)); /* NULL,NULL -> no user-provided equations */
    }

  /* Now that the mechanism is alraedy defined, the local2global 
     transforms can be used to deduce the conformation in
     internal coordinates*/
  GetSolutionPointFromLinkTransforms(p,l2g,NULL,conformation,&(bw->w));

  /* Release the local 2 global transforms */
  for(i=0;i<bw->nl;i++)
    HTransformDelete(&(l2g[i]));
  free(l2g);
}

/********************************************************************/
/********************************************************************/

boolean InitBioWorld(Tparameters *p,char *filename,unsigned int maxAtomsLink,
		     double **conformation,TBioWorld *bw)
{
  
  unsigned int nr,*r;
  char ch;
  double *c;
  unsigned int nh,*h1,*h2;
  boolean *added;

  /* Read the molecule */      
  bw->m=ReadMolecule(filename);
  if (bw->m!=NULL)
    {
      fprintf(stderr,"Reading bio-info from             : %s\n",filename);

      /* Collect information about the molecule and eventually 
	 print debug information about it  */
      GetMoleculeBasicInfo(bw);

      /* Atom positions */
      NEW(bw->pos,3*bw->na,double);
      GetAtomPositions(filename,bw->pos,bw);
      SetAtomCoordinates(bw->pos,bw->m);

      /* Detect the links and joints
	 links=rigid groups of atoms
	 joints=revolute joints along single bonds
      */
      ReadRigidsAndHinges(filename,&r,&nh,&h1,&h2,&added,bw);
      if ((r!=NULL)&&(h1!=NULL)&&(h1!=NULL)&&(added!=NULL))
	DetectLinksAndJointsFromRigidsAndHinges(r,nh,h1,h2,bw);
      else
	{
	  ReadResidueList(filename,&nr,&ch,&r);
	  if (r!=NULL)
	    {
	      DetectLinksAndJointsFromResidues(nr,ch,r,bw);
	      free(r);
	    }
	  else
	    DetectLinksAndJoints(bw);
	}

      /* Define the world from the molecular information defined so far */
      InitWorldFromMolecule(p,conformation,maxAtomsLink,bw);

      //AdjustBioWorldGeometry(p,bw);

      /* Set the atom positions in accordance to the new reference frames 
	 just defined */
      BioWordConformationFromAtomPositions(p,bw->pos,&c,bw);
      BioWordSetAtomPositionsFromConformation(p,FALSE,c,bw);
      free(c);

      if ((r!=NULL)&&(h1!=NULL)&&(h1!=NULL)&&(added!=NULL))
	{
	  unsigned int i;
       
	  /* Remove the artificially created bonds, if any. */
	  for (i=0;i<nh;i++)
	    {
	      if (added[i])
		{
		  RemoveBond(h1[i],h2[i],bw->m);
		  bw->nbAtom[h1[i]]--;
		  bw->nbAtom[h2[i]]--;
		  bw->nb-=2;
		}
	    }
	  free(r);
	  free(h1);
	  free(h2);
	  free(added);
	}
      return(TRUE);
    }
  else
    return(FALSE);
}

void AdjustBioWorldGeometry(Tparameters *p,TBioWorld *bw)
{
  TCuikSystem c;
  Tvariable var;
  Tequation eq,eq2;
  Tmonomial m,m2;
  double *s;
  char *vname;
  unsigned int i,j,l,n,nv,k;
  boolean fix;
  Tinterval range;
  unsigned int vID[3],vID2[3],lID;
  unsigned int an1,an2,an3;
  TBondIterator *it,*it2;
  double v1[3],v2[3];
  double sgn;
 
  InitCuikSystem(&c);

  nv=bw->na+bw->nb+bw->nba;
  NEW(s,nv,double);
  k=0;

  /* x,y,z for each atom */
  NEW(vname,100,char);
  InitMonomial(&m);
  InitMonomial(&m2);
  
  for(i=0;i<bw->na;i++)
    {
      for(j=0;j<3;j++)
	{
	  /* The ct value from the bio-info (initial approx.
	     to the solution) */
	  s[k]=bw->pos[k];

	  /* x,y,z position for each atom */
	  sprintf(vname,"p_%u_%s",i,(j==0?"x":(j==1?"y":"z")));

	  /* add the new variable to the system */
	  NewVariable(SYSTEM_VAR,vname,&var);
	  //NewInterval(s[k]-0.1,s[k]+0.1,&range);
	  NewInterval(-20,20,&range);
	  SetVariableInterval(&range,&var);
	  lID=AddVariable2CS(&var,&c);
	  DeleteVariable(&var);

	  /* fix first atom */
	  if (i==0)
	    {
	      InitEquation(&eq);
	      SetEquationType(SYSTEM_EQ,&eq);
	      SetEquationCmp(EQU,&eq);
	      //SetEquationValue(s[k],&eq);
	      SetEquationValue(0,&eq);
	      
	      AddVariable2Monomial(NFUN,lID,1,&m);
	      AddMonomial(&m,&eq);
	      ResetMonomial(&m);

	      AddEquation2CS(p,&eq,&c);
	      DeleteEquation(&eq);
	    }
	  k++;
	}
    }  
 
  /* vector for each pair of bonded atoms */
  for(i=0;i<bw->na;i++)
    {
      l=GetFirstNeighbour(i,&fix,&it,bw->m);
      while(l!=NO_UINT)
	{
	  if (l>i)
	    {
	      for(j=0;j<3;j++)
		{
		  /* The ct value from the atom positions */
		  s[k]=bw->pos[3*l+j]-bw->pos[3*i+j];

		  /* v_i_l = p_l-p_i */
		  sprintf(vname,"v_%u_%u_%s",i,l,(j==0?"x":(j==1?"y":"z")));

		  /* Add the new variable v_i_l to the system */
		  NewVariable(DUMMY_VAR,vname,&var);
		  //NewInterval(s[k]-0.2,s[k]+0.2,&range);
		  NewInterval(-20,20,&range);
		  SetVariableInterval(&range,&var);
		  vID[j]=AddVariable2CS(&var,&c);
		  DeleteVariable(&var);

		  /* Initialize the equation */
		  InitEquation(&eq);
		  SetEquationType(DUMMY_EQ,&eq);
		  SetEquationCmp(EQU,&eq);
		  SetEquationValue(0,&eq);

		  /* p_l */
		  AddVariable2Monomial(NFUN,3*l+j,1,&m);
		  AddMonomial(&m,&eq);
		  ResetMonomial(&m);

		  /* -p_i */
		  AddCt2Monomial(-1.0,&m);
		  AddVariable2Monomial(NFUN,3*i+j,1,&m);
		  AddMonomial(&m,&eq);
		  ResetMonomial(&m);

		  /* -v_i_l */
		  AddCt2Monomial(-1.0,&m);
		  AddVariable2Monomial(NFUN,vID[j],1,&m);
		  AddMonomial(&m,&eq);
		  ResetMonomial(&m);
		  
		  AddEquation2CS(p,&eq,&c);
		  DeleteEquation(&eq);

		  k++;
		}

	      /* The norm of v_i_l must the the same for all bonds
	         of this type (type given by the atom types) */
	      GenerateNormEquation(vID[0],vID[1],vID[2],0.0,&eq);

	      an1=GetAtomicNumber(i,bw->m);
	      an2=GetAtomicNumber(l,bw->m);
	      if (an1<an2)
		sprintf(vname,"bl_%u_%u",an1,an2);
	      else
		sprintf(vname,"bl_%u_%u",an2,an1);
	      lID=GetCSVariableID(vname,&c);
	      if (lID==NO_UINT)
		{
		  /* and define the initial estimation from the atom pos */
		  s[k]=Distance(3,&(bw->pos[3*i]),&(bw->pos[3*l]));
		  s[k]*=s[k];

		  /* First bond of this type found -> add the new variable */
		  NewVariable(DUMMY_VAR,vname,&var);
		  //NewInterval(s[k]-0.1,s[k]+0.1,&range);
		  NewInterval(-400,400,&range);
		  SetVariableInterval(&range,&var);
		  lID=AddVariable2CS(&var,&c);
		  DeleteVariable(&var);

		  InitEquation(&eq2);
		  SetEquationType(SYSTEM_EQ,&eq2);
		  SetEquationCmp(EQU,&eq2);
		  SetEquationValue(s[k],&eq2);
		  
		  AddVariable2Monomial(NFUN,lID,1,&m2);
		  AddMonomial(&m2,&eq2);
		  ResetMonomial(&m2);
		  
		  AddEquation2CS(p,&eq2,&c);
		  DeleteEquation(&eq2);

		  k++;
		}

	      AddCt2Monomial(-1.0,&m);
	      AddVariable2Monomial(NFUN,lID,1,&m);
	      AddMonomial(&m,&eq);
	      ResetMonomial(&m);
	      
	      AddEquation2CS(p,&eq,&c);
	      DeleteEquation(&eq);
	    }
	  l=GetNextNeighbour(i,&fix,it,bw->m);
	}
      DeleteBondIterator(it);
    }

  /* angle between for each triplet of bonded atoms.
     In particular we look for all angles with vertex at atom 'i'
     (avoiding repetitions). */
  for(i=0;i<bw->na;i++)
    {
      l=GetFirstNeighbour(i,&fix,&it,bw->m);
       while(l!=NO_UINT)
	 {
	   n=GetFirstNeighbour(i,&fix,&it2,bw->m);
	   while(n!=NO_UINT)
	     {
	       if (l>n)
		 {
		   /* Equation v1*v2'-n1*n2*cos(alpha)=0 */
		   an1=GetAtomicNumber(i,bw->m);
		   an2=GetAtomicNumber(l,bw->m);
		   an3=GetAtomicNumber(n,bw->m);

		   /* v1*v2 */
		   sgn=1.0;
		   for(j=0;j<3;j++)
		     {
		       if (l>i)
			 sprintf(vname,"v_%u_%u_%s",i,l,(j==0?"x":(j==1?"y":"z")));
		       else
			 {
			   sprintf(vname,"v_%u_%u_%s",l,i,(j==0?"x":(j==1?"y":"z")));
			   if (j==0) sgn*=-1.0;
			 }
		       vID[j]=GetCSVariableID(vname,&c);
		       if (vID[j]==NO_UINT)
			 Error("Unknow atom difference when fixing an angle bond");
		       
		       if (n>i)
			 sprintf(vname,"v_%u_%u_%s",i,n,(j==0?"x":(j==1?"y":"z")));
		       else
			 {
			   sprintf(vname,"v_%u_%u_%s",n,i,(j==0?"x":(j==1?"y":"z")));
			   if (j==0) sgn*=-1.0;
			 }
		       vID2[j]=GetCSVariableID(vname,&c);
		       if (vID2[j]==NO_UINT)
			 Error("Unknow atom difference when fixing an angle bond");
		     }
		   
		   /* This initializes the equation */
		   GenerateDotProductEquation(vID[0],vID[1],vID[2],
					      vID2[0],vID2[1],vID2[2],
					      NO_UINT,0,&eq);		 

		   if ((an1<an2)&&(an1<an3))
		     {
		       /* an1 smaller */
		       if (an2<an3)
			 sprintf(vname,"ba_%u_%u_%u",an1,an2,an3);
		       else
			 sprintf(vname,"ba_%u_%u_%u",an1,an3,an2);
		     }
		   else
		     {
		       /* an2 smaller */
		       if ((an2<an1)&&(an2<an3))
			 {
			   if (an1<an3)
			     sprintf(vname,"ba_%u_%u_%u",an2,an1,an3);
			   else
			     sprintf(vname,"ba_%u_%u_%u",an2,an3,an1);
			 }
		       else
			 {
			   /* an3 smaller */
			   if (an1<an2)
			     sprintf(vname,"ba_%u_%u_%u",an3,an1,an2);
			   else
			     sprintf(vname,"ba_%u_%u_%u",an3,an2,an1);
			 }
		     }

		   lID=GetCSVariableID(vname,&c);
		   if (lID==NO_UINT)
		     {
		       /* and define the initial estimation from the current atom positions */
		       DifferenceVector(3,&(bw->pos[3*l]),&(bw->pos[3*i]),v1);
		       DifferenceVector(3,&(bw->pos[3*n]),&(bw->pos[3*i]),v2);
		       s[k]=DotProduct(v1,v2);

		       /* First angle of this type found */
		       NewVariable(SYSTEM_VAR,vname,&var);
		       //NewInterval(s[k]-0.1,s[k]+0.1,&range);
		       NewInterval(-1,1,&range);
		       SetVariableInterval(&range,&var);
		       lID=AddVariable2CS(&var,&c);
		       DeleteVariable(&var);

		       InitEquation(&eq2);
		       SetEquationType(DUMMY_EQ,&eq2);
		       SetEquationCmp(EQU,&eq2);
		       SetEquationValue(s[k],&eq2);
		       
		       AddVariable2Monomial(NFUN,lID,1,&m2);
		       AddMonomial(&m2,&eq2);
		       ResetMonomial(&m2);
		       
		       AddEquation2CS(p,&eq2,&c);
		       DeleteEquation(&eq2);

		       k++;
		     }

		   AddCt2Monomial(-sgn,&m);
		   AddVariable2Monomial(NFUN,lID,1,&m);
		   AddMonomial(&m,&eq);
		   ResetMonomial(&m);
		      
		   AddEquation2CS(p,&eq,&c);
		   DeleteEquation(&eq);
		 }
	       n=GetNextNeighbour(i,&fix,it2,bw->m);
	     }
	   DeleteBondIterator(it2);
	   l=GetNextNeighbour(i,&fix,it,bw->m);
	 }
       DeleteBondIterator(it);
    }
  DeleteMonomial(&m);
  
  /* Print Cuiksystem?? */
  {
    FILE *fout;
    Tbox b;
    char **varNames;
    boolean *systemVars;

    fout=fopen("geometry.cuik","w");
    if (!fout)
      Error("Could not open the file to store the geometry equations.");
    PrintCuikSystem(p,fout,&c);
    fclose(fout);

    InitBoxFromPoint(k,s,&b);
    fout=fopen("geometry.sol","w");
    if (!fout)
      Error("Could not open the file to store the initial approx.");
    NEW(varNames,k,char*);
    GetCSVariableNames(varNames,&c);
    GetCSSystemVars(&systemVars,&c);
    PrintBoxSubset(fout,systemVars,varNames,&b);
    free(varNames);
    free(systemVars);
    fclose(fout);
    DeleteBox(&b);
  }
  /* CuikNewton on Cuiksystem? */

  free(s);
  free(vname);
  DeleteCuikSystem(&c);
}

Tworld *BioWorldWorld(TBioWorld *bw)
{
  return(&(bw->w));
}

unsigned int BioWorldNAtoms(TBioWorld *bw)
{
  return(bw->na);
}

unsigned int BioWorldConformationSize(TBioWorld *bw)
{
  return(GetWorldNumSystemVariables(&(bw->w)));
}

void BioWordGetAtomPositionsFromConformation(Tparameters *p,boolean simp,double *conformation,
					     double *pos,TBioWorld *bw)
{
  THTransform *tl,*t;
  TLinkConf *def;
  unsigned int i,k;
  
  /* Compute the position of the atoms form the conformation */
  GetLinkTransformsFromSolutionPoint(p,simp,conformation,&tl,&def,&(bw->w));
  
  /* for all links */
  for(i=0;i<bw->nl;i++) 
    {
      /* Transform for this link */
      t=&(tl[i]);
      /* apply it for all atoms in this link */
      k=*(unsigned int *)GetVectorElement(i,&(bw->links));
      do{
	/* move the atom */
	HTransformApply(&(bw->localPos[3*k]),&(pos[3*k]),t);

	/* go for next atom in this link */
	k=bw->linkList[k];

      } while(k!=NO_UINT);
    }

  DeleteLinkTransforms(tl,def,&(bw->w));
}

void BioWordSetAtomPositionsFromConformation(Tparameters *p,boolean simp,double *conformation,
					     TBioWorld *bw)
{
  BioWordGetAtomPositionsFromConformation(p,simp,conformation,bw->pos,bw);

  SetAtomCoordinates(bw->pos,bw->m);
}

double BioWorldRMSE(double *pos,TBioWorld *bw)
{
  double e;
  unsigned int i,n,k;

  e=0.0;
  n=0;
  for(i=0,k=0;i<bw->na;i++,k+=3)
    {
      /* atoms in link 0 do not move. When modelling protein loops
         link 0 can be quite large. */
      if (bw->linkID[i]!=0)
	{
	  e+=Distance(3,&(pos[k]),&(bw->pos[k]));
	  n++;
	}
    }

  return(sqrt(e/n));
}


unsigned int BioWordConformationFromAtomPositions(Tparameters *p,double *atoms,
						  double **conformation,TBioWorld *bw)
{
  THTransform *l2g;
  unsigned int i,nv;
  
  /* Get the transform to global coordinates for each link. */
  NEW(l2g,bw->nl,THTransform);
  Atoms2Transforms(p,atoms,l2g,bw);

  nv=GetSolutionPointFromLinkTransforms(p,l2g,NULL,conformation,&(bw->w));

  /* Release the local-2-global transforms */
  for(i=0;i<bw->nl;i++)
    HTransformDelete(&(l2g[i]));
  free(l2g);

  return(nv);
}

double BioWorldEnergy(Tparameters *p,boolean simp,double *conformation,void *bw)
{
 
  BioWordSetAtomPositionsFromConformation(p,simp,conformation,(TBioWorld *)bw);
  
  /* And compute the energy */
  return(ComputeEnergy(((TBioWorld *)bw)->m));
}

void SaveBioWorldBioInfo(Tparameters *p,char *fname,boolean simp,double *conformation,TBioWorld *bw)
{
  BioWordSetAtomPositionsFromConformation(p,simp,conformation,bw);

  /* and save in bio-format*/
  WriteMolecule(fname,bw->m);
}

void PrintBioWorld(Tparameters *p,char *fname,int argc,char **arg,TBioWorld *bw)
{
  PrintWorld(fname,argc,arg,&(bw->w));
}

void DeleteBioWorld(TBioWorld *bw)
{
  unsigned int i;

  DeleteWorld(&(bw->w));
  DeleteMolecule(bw->m);

  free(bw->localPos);
  free(bw->pos);

  free(bw->nbAtom);

  for(i=0;i<bw->nl;i++)
    HTransformDelete(&(bw->g2l[i]));
  free(bw->g2l);

  free(bw->linkList);
  DeleteVector((void *)&(bw->links));
  DeleteVector((void *)&(bw->joint1));
  DeleteVector((void *)&(bw->joint2));
  free(bw->linkID);

  if (bw->cut)
    DeleteBox(&(bw->cutB));
}

