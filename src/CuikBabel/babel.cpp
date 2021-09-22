#include "babel.h"

/** \file babel.cpp

    \brief Implementation of the minimalistic Cuik-OpenBabel interface.

    Implementation of the minimalistic Cuik-OpenBabel interface.
   
    \sa babel.h
*/

extern "C" {
  #include "defines.h"
  #include "error.h"
  #include "boolean.h"
}

#include <openbabel/mol.h>
#include <openbabel/obconversion.h>
#include <openbabel/forcefield.h>
#include <openbabel/oberror.h>
#include <openbabel/elements.h>
#include <openbabel/bond.h>

#include <iostream>

using namespace OpenBabel;
using namespace std;

/** \cond */

OBERROR extern OBMessageHandler obErrorLog;

/** \endcond */


/** 
   \brief Summarizes the information relating a given molecule.

   Summarizes the information relating a given molecule including its
   structure (atoms and bonds) and the associated force field.
*/
typedef struct {
  OBMol mol;         /**< The molecule itself. */
  OBForceField *ff;  /**< The associated force field. */
} TMolInfo;

TMolecule *ReadMolecule(char *fname)
{
  TMolInfo *m;
  OBConversion conv;
  OBFormat *format;
  bool error;

  // Avoid warning messages
  OpenBabel::obErrorLog.SetOutputLevel(obError);

  // Define the molecular information
  m=new(TMolInfo);

  // Read the molecule
  error=false;
  format=conv.FormatFromExt(fname);
  if (!format)
    error=true; /* unknown file extension */
  if (!conv.SetInFormat(format))
    error=true; /*Unknown file format*/
  if (!conv.ReadFile(&(m->mol),fname))
    error=true; /*Error reading the input file*/

  m->ff=NULL;
  
  if (error)
    {
      delete m;
      m=NULL;
    }
  return((void*)m);
}

void WriteMolecule(char *fname,TMolecule *ml)
{
  OBConversion conv;
  OBFormat *format;
  TMolInfo *m;

  m=(TMolInfo *)ml;

  // Avoid warning messages
  OpenBabel::obErrorLog.SetOutputLevel(obError);

  // Write the molecule
  format=conv.FormatFromExt(fname);
  if (!format)
    Error("Unknown extension file");
  if (!conv.SetOutFormat(format))
    Error("Unknown file format");
  if (!conv.WriteFile(&(m->mol),fname))
    Error("Error writting the output file");
}

unsigned int nAtoms(TMolecule *ml)
{
  TMolInfo *m;
  
  m=(TMolInfo *)ml;

  return(m->mol.NumAtoms());
}

unsigned int GetAtomicNumber(unsigned int na,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a;
  
  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na+1);

  return(a->GetAtomicNum());
}

unsigned int GetAtomResidue(unsigned int na,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a;
  OBResidue *r;
  
  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na+1);
  r=a->GetResidue();

  if (r==NULL)
    return(NO_UINT);
  else
    return(r->GetNum());
}

char GetAtomChain(unsigned int na,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a;
  OBResidue *r;
  
  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na+1);
  r=a->GetResidue();

  if (r==NULL)
    return('-');
  else
    return(r->GetChain());
}

boolean IsAtomInProline(unsigned int na,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a;
  OBResidue *r;
  
  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na+1);
  r=a->GetResidue();
  
  if (r==NULL)
    return(FALSE);
  else
    return(r->GetName().compare("PRO")==0);
}

double VdWRadius(unsigned int na,TMolecule *ml)
{  
  TMolInfo *m;
  OBAtom *a;

  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na+1); // In babel atoms are numbered from 1

  return(OBElements::GetVdwRad(a->GetAtomicNum()));
}

boolean HasBond(unsigned int na1,unsigned int na2,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a,*n;
  OBBondIterator ait;
  boolean found;

  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na1+1); // In babel atoms are numbered from 1

  n=a->BeginNbrAtom(ait);
  found=false;
  while ((!found)&&(n!=NULL))
    {
      found=(n->GetIdx()-1==na2);
      n=a->NextNbrAtom(ait);
    }

  if (found)
    return(TRUE);
  else
    return(FALSE);
}

void AddBond(unsigned int na1,unsigned int na2,TMolecule *ml)
{
  TMolInfo *m;

  m=(TMolInfo *)ml;

  m->mol.AddBond(na1+1,na2+1,1);
}

void RemoveBond(unsigned int na1,unsigned int na2,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a;
  OBBond *b;
  OBBondIterator bit;
  boolean found;

  m=(TMolInfo *)ml;

  a=m->mol.GetAtom(na1+1); // In babel atoms are numbered from 1

  b=a->BeginBond(bit);
  found=false;
  while ((!found)&&(b!=NULL))
    {
      found=(((b->GetBeginAtomIdx()-1==na1)&&(b->GetEndAtomIdx()-1==na2))||
	     ((b->GetBeginAtomIdx()-1==na2)&&(b->GetEndAtomIdx()-1==na1)));
      if (!found)
	b=a->NextBond(bit);
    }

  if (found)
    m->mol.DeleteBond(b);
}

unsigned int GetFirstNeighbour(unsigned int na,boolean *fix,TBondIterator **it,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a,*n;
  OBBondIterator *ait;
  
  m=(TMolInfo *)ml;

  ait=new OBBondIterator;

  a=m->mol.GetAtom(na+1); // In babel atoms are numbered from 1
  n=a->BeginNbrAtom(*ait);
  *it=(void *)ait;

  if (n==NULL)
    {
      *fix=FALSE;
      return(NO_UINT);
    }
  else
    {
      /* double bonds fix the rotation */
      *fix=((*(*ait))->IsDoubleBondGeometry());
      return(n->GetIdx()-1); // In babel atoms are numbered from 1
    }
}

unsigned int GetNextNeighbour(unsigned int na,boolean *fix,TBondIterator *it,TMolecule *ml)
{
  TMolInfo *m;
  OBAtom *a,*n;
  OBBondIterator *ait;
  
  m=(TMolInfo *)ml;
  ait=(OBBondIterator *)it;

  a=m->mol.GetAtom(na+1); // In babel atoms are numbered from 1
  n=a->NextNbrAtom(*ait);

  if (n==NULL)
    {
      *fix=FALSE;
      return(NO_UINT);
    }
  else
    {
      /* double bonds fix the rotation */
      /* hidrogens can rotate but since there is nothing else attached to them
         the rotation has no effect (due to the symmetry of hydrogens represented
	 as balls) */
      *fix=((*(*ait))->IsDoubleBondGeometry());
      return(n->GetIdx()-1); // In babel atoms are numbered from 1
    }
}

void DeleteBondIterator(TBondIterator *it)
{
  OBBondIterator *ait;

  ait=(OBBondIterator *)it;

  delete ait;
}

void GetAtomCoordinates(double *pos,TMolecule *ml)
{ 
  TMolInfo *m;
  double *p;
  OBAtomIterator i;

  m=(TMolInfo *)ml;

  p=pos;
  for(i=m->mol.BeginAtoms();i!=m->mol.EndAtoms();++i)
    {
      *p=(*i)->x();p++;
      *p=(*i)->y();p++;
      *p=(*i)->z();p++;
    }
}

void SetAtomCoordinates(double *pos,TMolecule *ml)
{ 
  TMolInfo *m;
  
  m=(TMolInfo *)ml;

  m->mol.SetCoordinates(pos);
}

double ComputeEnergy(TMolecule *ml)
{
  TMolInfo *m;
  
  m=(TMolInfo *)ml;

  if (m->ff==NULL)
    {
      m->ff=OBForceField::FindType("MMFF94");
 
      if (!m->ff->Setup(m->mol))
	Error("Could not setup forcefield.");
    }

  m->ff->SetCoordinates(m->mol);

  return(m->ff->Energy(false));
}

void DeleteMolecule(TMolecule *ml)
{
  TMolInfo *m;
  
  m=(TMolInfo *)ml;

  delete m;
}
