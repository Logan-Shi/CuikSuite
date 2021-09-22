#include "mechanism.h"

#include <string.h>


/** \file mechanism.c
    \brief Implementaton of the function operating on Tmechanism.
    
    Implementaton of the function operating on Tmechanism.

    \sa Tmechanism, mechanism.h.
*/



void InitMechanism(Tmechanism *m)
{
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_JOINTS,&(m->joints)); 
  InitVector(sizeof(void *),CopyVoidPtr,DeleteVoidPtr,INIT_NUM_LINKS,&(m->links));  
  m->nbodies=0;
  m->allSpheres=TRUE;
  m->maxCoord=0.0;
  m->isTensegrity=FALSE;
}

unsigned int GetMechanismNLinks(Tmechanism *m)
{
  return(VectorSize(&(m->links)));
}

unsigned int GetMechanismNJoints(Tmechanism *m)
{
  return(VectorSize(&(m->joints)));
}

unsigned int GetMechanismNBodies(Tmechanism *m)
{
  return(m->nbodies);
}

boolean IsMechanismAllSpheres(Tmechanism *m)
{
  return(m->allSpheres);
}

double GetMechanismMaxCoordinate(Tmechanism *m)
{
  return(m->maxCoord);
}

unsigned int GetLinkID(char *name,Tmechanism *m)
{
  unsigned int id,nl;
  boolean found;
  Tlink *l;
  
  nl=GetMechanismNLinks(m);
  found=FALSE;
  id=0;
  while((!found)&&(id<nl))
    {
      l=GetMechanismLink(id,m);
      if ((l!=NULL)&&(strcmp(name,GetLinkName(l))==0))
	found=TRUE;
      else
	id++;
    }
  if (found)
    return(id);
  else
    return(NO_UINT);
}

signed int GetMechanismMobility(Tmechanism *m)
{
  signed int ndof,constraints;
  unsigned int i,nj;

  ndof=6*(GetMechanismNLinks(m)-1); /*Ground link is fixed !!*/

  nj=GetMechanismNJoints(m);
  constraints=0;
  for(i=0;i<nj;i++)
    constraints+=(6-GetJointDOF(GetMechanismJoint(i,m)));

  return(ndof-constraints);
}

void GetMechanismDefiningPoint(unsigned int lID,unsigned int bID,unsigned int pID,
			       double *p,Tmechanism *m)
{
  GetPolyhedronDefiningPoint(pID,p,GetLinkBody(bID,GetMechanismLink(lID,m)));
}

unsigned int AddLink2Mechanism(Tlink *l,Tmechanism *m)
{
  Tlink *li;
  unsigned int k;

  NEW(li,1,Tlink);
  CopyLink(li,l);
  k=GetMechanismNLinks(m);
  SetVectorElement(k,&li,&(m->links));

  m->maxCoord+=GetLinkMaxCoordinate(l);
  m->nbodies+=LinkNBodies(l);
  m->allSpheres=((m->allSpheres)&&(IsLinkAllSpheres(l)));
  m->isTensegrity=((m->isTensegrity)||(GetLinkType(l)==LINK_NoRot)); /* ForceModel ? */

  return(k);
}

unsigned int AddJoint2Mechanism(Tjoint *j,Tmechanism *m)
{
  Tjoint *ji;
  unsigned int k;

  NEW(ji,1,Tjoint);
  CopyJoint(ji,j);
  k=GetMechanismNJoints(m);
  SetVectorElement(k,&ji,&(m->joints));

  /* Free joints are unbounded: don't take them into account */
  if (GetJointType(j)!=FREE_JOINT)
    m->maxCoord+=GetJointMaxCoordinate(j);

  return(k);
}

unsigned int AddBody2Mechanism(unsigned int lID,Tpolyhedron *b,Tmechanism *m)
{
  Tlink *lk;

  lk=GetMechanismLink(lID,m);
  if (lk==NULL)
    Error("Unkown link in AddBody2Mechanism");

  
  m->maxCoord-=GetLinkMaxCoordinate(lk);
  AddBody2Link(b,lk);

  m->maxCoord+=GetLinkMaxCoordinate(lk);
  m->nbodies++;
  m->allSpheres=((m->allSpheres)&&(IsLinkAllSpheres(lk)));
  
  return(m->nbodies);
}

Tlink *GetMechanismLink(unsigned int i,Tmechanism *m)
{
  Tlink **l;

  l=(Tlink **)GetVectorElement(i,&(m->links));
  if (l==NULL)
    return(NULL);
  else
    return(*l);
}

unsigned int GetMechanismLinkID(char *ln,Tmechanism *m)
{
  unsigned int i,nl;
  Tlink **l;
  boolean found;

  nl=VectorSize(&(m->links));
  found=FALSE;
  i=0;
  while((!found)&&(i<nl))
    {
      l=(Tlink **)GetVectorElement(i,&(m->links));
      
      if ((l!=NULL)&&(strcmp(ln,GetLinkName(*l))==0))
	found=TRUE;
      else
	i++;
    }
    
  if (found)
    return(i);
  else
    return(NO_UINT);
}

Tjoint *GetMechanismJoint(unsigned int i,Tmechanism *m)
{
  Tjoint **j;

  j=(Tjoint **)GetVectorElement(i,&(m->joints));
  if (j==NULL)
    return(NULL);
  else
    return(*j);
}

boolean AllRevolute(Tmechanism *m)
{
  unsigned int nj,i;
  boolean all;
  
  nj=GetMechanismNJoints(m);
  all=TRUE;
  i=0;
  while((all)&&(i<nj))
    {
      all=(GetJointType(GetMechanismJoint(i,m))==REV_JOINT);
      i++;
    }
  return(all);
}

void PlotMechanism(Tplot3d *pt,double axesLength,Tmechanism *m)
{
  unsigned int i;
  unsigned int n;
  Tlink *l;

  n=GetMechanismNLinks(m);  
  if (n>0) Start3dBlock(pt);
  for(i=0;i<n;i++)
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	PlotLink(pt,axesLength,l);
    } 

  if (n>0) Close3dBlock(pt);
}

void RegenerateMechanismSolution(Tparameters *p,TCuikSystem *cs,
				 double *sol,Tmechanism *m)
{ 
  unsigned int i;
  unsigned int n;
  Tlink *l;
  Tjoint *j;

  n=GetMechanismNLinks(m); 
  for(i=0;i<n;i++)
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	RegenerateLinkSolution(p,cs,sol,IsGroundLink(i),l);
    }

  n=GetMechanismNJoints(m); 
  for(i=0;i<n;i++)
    {
      j=GetMechanismJoint(i,m);
      if (j!=NULL)
	RegenerateJointSolution(p,cs,sol,j);
    }
}

void RegenerateMechanismBox(Tparameters *p,TCuikSystem *cs,Tbox *b,Tmechanism *m)
{
  unsigned int i;
  unsigned int n;
  Tlink *l;
  Tjoint *j;
  unsigned int r;

  r=(unsigned int)(GetParameter(CT_REPRESENTATION,p));

  /* for DOF representations -> nothing to regenerate */
  if (r!=REP_JOINTS)
    {
      n=GetMechanismNLinks(m);
      for(i=0;i<n;i++)
	{
	  l=GetMechanismLink(i,m);
	  if (l!=NULL)
	    RegenerateLinkBox(p,cs,b,IsGroundLink(i),l);
	}

      n=GetMechanismNJoints(m); 
      for(i=0;i<n;i++)
	{
	  j=GetMechanismJoint(i,m);
	  if (j!=NULL)
	    RegenerateJointBox(p,cs,b,j);
	}
    }
}

void GetMechanismDOFsFromTransforms(Tparameters *p,THTransform *tl,TLinkConf *def,
				    double *dof,Tmechanism *m)
{
  Tjoint *j;
  Tlink *l;
  unsigned int i,nj,k;
  unsigned int l1,l2;
  THTransform t;
  
  k=0;
  if (def!=NULL)
    {
      Tlink *l;
      unsigned int nl;

      nl=GetMechanismNLinks(m);  
      for(i=0;i<nl;i++)
	{
	  l=GetMechanismLink(i,m);
	  if ((l!=NULL)&&(NumLinkDOF(l)>0))
	    {
	      GenerateDOFFromLinkConf(&(def[i]),&(dof[k]),l);
	      k+=NumLinkDOF(l);
	    }
	}
    }
  
  nj=GetMechanismNJoints(m);  
  for(i=0;i<nj;i++)
    {
      j=GetMechanismJoint(i,m);
      if (j!=NULL)
	{
	  l1=JointFromID(j);
	  l2=JointToID(j);
	  l=JointFrom(j);
	  /* If necessary traverse the previous deformation link
	     (remove the deformation dof from the transforms to use
	     to get the DOF)  */
	  if (IsVariableLengthLink(l))
	    {
	      GetLinkTransformFromConf(&(def[l1]),&t,l);
	      HTransformProduct(&(tl[l1]),&t,&t);
	      GetJointDOFValues(p,&t,&(tl[l2]),&(dof[k]),j);
	      HTransformDelete(&t);
	    }
	  else
	    GetJointDOFValues(p,&(tl[l1]),&(tl[l2]),&(dof[k]),j);
	  k+=GetJointDOF(j);
	}
    }
}

void MechanismPrintAtoms(FILE *f,THTransform *tl,Tmechanism *m)
{
  unsigned int i,n;
  Tlink *l;

  n=GetMechanismNLinks(m);
  for(i=0;i<n;i++) 
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	LinkPrintAtoms(f,&(tl[i]),l);
    }
  fprintf(f,"\n");
}

void MechanismStoreRigidAtoms(FILE *f,THTransform *tl,Tmechanism *m)
{
  unsigned int i,n,nr,na;
  Tlink *l;

  n=GetMechanismNLinks(m);

  /* number of rigid = number of links with balls */
  nr=0;
  for(i=0;i<n;i++) 
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	{
	  if (LinkNAtoms(l)>0)
	    nr++;
	}
    }
  fprintf(f,"%u\n",nr);

  /* now store  */
  for(i=0;i<n;i++) 
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	{
	  na=LinkNAtoms(l);
	  if (na>0)
	    {
	      fprintf(f,"%u %u\n",na,IsGroundLink(i)); 
	      LinkStoreAtoms(f,&(tl[i]),l);
	    }
	}
    }
  fprintf(f,"\n");
}

void MoveMechanismFromTransforms(Tparameters *pr,Tplot3d *pt,
				 THTransform *tl,TLinkConf *def,
				 Tmechanism *m)
{
  unsigned int i;
  unsigned int n;
  Tlink *l;

  n=GetMechanismNLinks(m);
  if (n>0) Start3dBlock(pt);
  for(i=1;i<n;i++) /*Ground link (ID==0) does not move*/
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	MoveLinkFromTransform(pt,&(tl[i]),&(def[i]),l);
    }

  if (n>0) Close3dBlock(pt);
}

void PrintMechanism(FILE *f,char *path,char *prefix,Tmechanism *m)
{
  unsigned int i,n;
  Tlink *l;
  Tjoint *j;
  Tlink *l1,*l2;
  double *p1,*p2;

  if (m->isTensegrity)
    Error("Tensegrity mechanisms can not be printed (not implemented yet)");


  NEW(p1,3,double);
  NEW(p2,3,double);
  
  n=GetMechanismNLinks(m);
  if (n>0)
    fprintf(f,"[LINKS]\n\n");
  for(i=0;i<n;i++)
    { 
      l=GetMechanismLink(i,m);
      if ((l!=NULL)&&(GetLinkType(l)!=LINK_Connect))
	PrintLink(f,path,prefix,NULL,NULL,l);
    }

  n=GetMechanismNJoints(m);
  if (n>0)
    fprintf(f,"[JOINTS]\n\n");
  i=0;
  while (i<n)
    {
      j=GetMechanismJoint(i,m);
      if (j!=NULL)
	{
	  unsigned int t;
	  Tpolyhedron *b;
	  
	  t=GetJointType(j);
	  switch(t)
	    {
	    case REV_LOW_JOINT:
	    case REV_UP_JOINT:
	      Error("Tensegrity mechanisms can not be printed (not implemented yet)");
	      break;
	    case SPH_SPH_LOW_JOINT:
	      {
		Tjoint *j2;
		Tlink *l3;
		unsigned int bs;
		Tcolor c;
		Tinterval *l;
		boolean prs;

		j2=GetMechanismJoint(i+1,m);

		l1=JointFrom(j);
		l2=JointTo(j);
		l3=JointTo(j2);

		/* fixed of prismatic leg */
		if (GetLinkType(l2)!=LINK_AxisX)
		  Error("Inconsistent composite joint");
			
		l=GetLinkLength(l2);
		    
		prs=(IntervalSize(l)>ZERO);
		b=GetLinkBody(1,l2); /* The cylinder (skip sphere) */
		GetPolyhedronColor(&c,b);
		bs=GetPolyhedronStatus(b);
		GetJointPoint(0,0,p1,j);
		GetJointPoint(1,0,p2,j2);

		if (prs)
		  fprintf(f,"  sph_prs_sph %s :",GetLinkName(l2));
		else
		  fprintf(f,"  sph_sph %s :",GetLinkName(l2));
		fprintf(f," %s (%.16f,%.16f,%.16f)",GetLinkName(l1),p1[0],p1[1],p1[2]);
		fprintf(f," %s (%.16f,%.16f,%.16f)",GetLinkName(l3),p2[0],p2[1],p2[2]);
		if (prs)
		  { fprintf(f," length ");PrintInterval(f,l); }
		else
		  fprintf(f," length %.16f",IntervalCenter(l));
		fprintf(f," radius %.16f ",GetPolyhedronRadius(b));
		fprintf(f," color (");PrintColor(f,&c);
		if (bs!=NORMAL_SHAPE)
		  fprintf(f,") %s\n",(bs==HIDDEN_SHAPE?"hidden":"decoration"));
		else
		  fprintf(f,")\n");
			
		DeleteColor(&c);

		i+=2; /* skip the sph_sph_upper joint */
	      }
	      break;
	    default:
	      PrintJoint(f,j);
	      i++;
	    }
	}
    }

  /* The connection links are printed like joints since they involve two links */
  for(i=0;i<n;i++)
    { 
      l=GetMechanismLink(i,m);
      if ((l!=NULL)&&(GetLinkType(l)==LINK_Connect))
	{
	  l1=GetMechanismLink(GetConnectLinkFrom(l),m);
	  l2=GetMechanismLink(GetConnectLinkTo(l),m);
	  PrintLink(f,path,prefix,GetLinkName(l1),GetLinkName(l2),l);
	}
    }
     
   free(p2);
   free(p1);
}

void DeleteMechanism(Tmechanism *m)
{

  unsigned int i;
  unsigned int n;
  Tlink *l;
  Tjoint *j;

  n=GetMechanismNLinks(m);
  for(i=0;i<n;i++)
    {
      l=GetMechanismLink(i,m);
      if (l!=NULL)
	{
	  DeleteLink(l);
	  free(l);
	} 
    }

  n=GetMechanismNJoints(m);
  for(i=0;i<n;i++)
    {
      j=GetMechanismJoint(i,m);
      if (j!=NULL)
	{
	  DeleteJoint(j);
	  free(j);
	}
    }

  DeleteVector(&(m->links)); 
  DeleteVector(&(m->joints)); 
}
