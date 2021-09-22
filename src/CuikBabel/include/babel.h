#ifndef BABELH
#define BABELH

#include "boolean.h"

/** 
   \file babel.h

   \brief Minimalistic Cuik-OpenBabel interface.

   Definition of the minimalistic Cuik-OpenBabel interface.

   \sa babel.cpp
*/

#ifdef __cplusplus
extern "C" {
#endif


  /** 
      \brief Iterator over the neighbours of a given atom.

      Iterator over the neighbours of a given atom.
  */
  typedef void TBondIterator;

  /** 
     \brief The molecule handler type.

     This is a dummy type used to hold a reference to the molecule information.
   */
  typedef void TMolecule;

  /** 
     \brief Reads the molecule information from a file.

     Initializes the molecule information from a file.

     This function also sets up the force field to be used for energy computations.
     For small molecules (less than 100 atoms) we use the MMFF94 force field. For
     larger ones we use the Generalized Amber Force Field (GAFF). The idea is that
     larger molecules correspond to proteins where the GAFF is more accurate.

     \param fname Name of the file from where to read the molecule information.
                  The format of the file is deduced from the extension.
		  All the formats available to OpenBabel can be used.
     
     \return The molecule handler.
  */
  TMolecule *ReadMolecule(char *fname);

  /** 
      \brief Writes the molecule information to a file.

      Stores the molecule information into a file (eg. a pdb).

      \param fname The name fo the file where to store the information.
                   The format of the file is deduced from the extension.
	 	   All the formats available to OpenBabel can be used.
      \param m The molecule to save.
  */
  void WriteMolecule(char *fname,TMolecule *m);

  /** 
     \brief Number of atoms in a molecule.
     
     Number of atoms in a molecule.
     
     \param ml The molecule to query.
     
     \return The number of atoms in a molecule.
  */
  unsigned int nAtoms(TMolecule *ml);

  /** 
      \brief Returns the atomic number of a given atom.

      Returns the atomic number of a given atom.

      \param na The atom whose atomic number is queried.
      \param ml The molecule to query.
      
      \return The atomic number of the atom.
  */
  unsigned int GetAtomicNumber(unsigned int na,TMolecule *ml);

  /** 
      \brief Returns the residue of a given atom.

      Returns the number of the residue including the given atom.

      \param na The atom whose residue is queried.
      \param ml The molecule to query.
      
      \return The number of the residue including the atom or NO_UINT if
              the atom is not in a residue.
  */
  unsigned int GetAtomResidue(unsigned int na,TMolecule *ml);

  /** 
      \brief Returns a char identifying the chain of the atom.

      Returns a char identifying the chain of the atom (A B C...).
      Only works for atoms in residues.
      
      \param na The atom whose chain is queried.
      \param ml The molecule to query.
      
      \return The chain or '-' if the atom is not in a residue.
  */
  char GetAtomChain(unsigned int na,TMolecule *ml);

  /** 
      \brief Identifies atoms in proline residues.

      Identifies atoms in proline residues.
      
      \param na The atom to query.
      \param ml The molecule to query.
      
      \return TRUE if the atom is in a proline.
  */
  boolean IsAtomInProline(unsigned int na,TMolecule *ml);
  
  /** 
      \brief Returns the Van der Waals radius for a given atom.

      Returns the Van der Waals radius for a given atom.

      This is used for representation purposes.

      The returned value is the standard VdW radius, that can be different
      from the VdW parameters used in the force field. Thus, this parameter
      can be adjusted (scaled down) if you want use this radius to radpidly
      discard high-energy conformations.

      \param na The atom whose neighbours are to be queried.
      \param ml The molecule to query.
      
      \return The Van der Waals radius.
  */
  double VdWRadius(unsigned int na,TMolecule *ml);

  /** 
      \brief Determines is a given bond exists.

      Determines if a bond between a given pair of atoms exists.
      
      \param na1 The index of the first atom  (num. from 0).
      \param na2 The index of the second atom (num. from 0).
      \param ml The molecule to query.

      \return TRUE if the bond exits.
  */
  boolean HasBond(unsigned int na1,unsigned int na2,TMolecule *ml);

  /** 
      \brief Adds a bond between two atoms.

      Adds a simple bond between the two given atoms.
      If the bond already exists it is re-added (probably OpenBabel
      takes care of removing duplicates). To ensure no
      duplicates are introduced use \ref HasBond before adding it.

      \param na1 The index of the first atom to bond (num. from 0).
      \param na2 The index of the second atom to bond (num. from 0).
      \param ml The molecule to modify.
  */
  void AddBond(unsigned int na1,unsigned int na2,TMolecule *ml);

  /** 
      \brief Removes a bond between two atoms.

      Removes a bond between the two given atoms.
      No check is done on whether the bond actually exists.

      \param na1 The index of the first atom to bond (num. from 0).
      \param na2 The index of the second atom to bond (num. from 0).
      \param ml The molecule to modify.
  */
  void RemoveBond(unsigned int na1,unsigned int na2,TMolecule *ml);

  /** 
     \brief Gets the identifier of the first neighbour for a given atom in a molecule.
     
     Gets the identifier of the first neighbour of a given atom
     in the molecule. 
     
     \param na The atom whose neighbours are to be queried.
     \param fix TRUE if the bond is fixed (it does not allow any rotation).
     \param it Iterator over the bonds of this atoms. To be used in subsequent calls
               to \ref GetNextNeighbour.
     \param ml The molecule to query.
     
     \return The identifier of the first neighbour of the given atom.
  */
  unsigned int GetFirstNeighbour(unsigned int na,boolean *fix,TBondIterator **it,TMolecule *ml);

  /** 
     \brief Gets the identifier of the next neighbour for a given atom in a molecule.
     
     Gets the identifier of the next neighbour of a given atom
     in the molecule.

     \param na The atom whose neighbours are to be queried.
     \param fix TRUE if the bond is fixed (it does not allow any rotation).
     \param it Iterator over the bonds of this atoms created in \ref GetNextNeighbour.
               Note that if the atom identifier (\e na) is not the same as that used 
	       when calling  \ref GetNextNeighbour the behavior is undefined.
     \param ml The molecule to query.
     
     \return The identifier of the next neighbour of the given atom. NO_UINT if there
             are no more neighbours.
  */
  unsigned int GetNextNeighbour(unsigned int na,boolean *fix,TBondIterator *it,TMolecule *ml);

  /** 
      \brief Deletes the bond iterator defined in \ref GetFirstNeighbour.

      Deletes the iterator defined in \ref GetFirstNeighbour.

      \param it The bond iterator to delete.
  */
  void DeleteBondIterator(TBondIterator *it);

  /** 
     \brief Gets the positions of the atoms in the molecule.
     
     Gets the 3D positions of the atoms in the molecule.

     The space for the buffer must be allocated externally before
     using this function.
     
     This is typically used only once, after reading the molecule from
     file to have access to the "default" atom positions.
     After this we typically call \ref SetAtomCoordinates so that the
     molecule and our system share the same vector of atom position.
     
     \param pos Buffer where to store the positions (size 3*num_atoms)
     \param  ml The molecule to query.
  */
  void GetAtomCoordinates(double *pos,TMolecule *ml);

  /** 
     \brief Sets the positions of the atoms in the molecule.
     
     Sets the 3D positions of the atoms in the molecule.

     Note that this only need to be done once. The molecule store a
     pointer to the given array of positions that can be latter
     on modified externally.
     
     \param pos Buffer from where to get the positions (size 3*num_atoms)
     \param  ml The molecule to query.
  */
  void SetAtomCoordinates(double *pos,TMolecule *ml);

  /** 
     \brief Computes the potential energy of a molecule.
     
     Computes the potential energy of a molecule according the
     the MMFF94 force field.

     The different conformations are defined by directly editing the
     vector of 3D positions of atoms given to the molecule using
     \ref SetAtomCoordinates.
     
     \param ml The molecule to query.

     \return The energy value.
  */
  double ComputeEnergy(TMolecule *ml);

  /** 
     \brief Destructor.

     Molecule information destructor.

     \param ml The molecule to delete.
  */
  void DeleteMolecule(TMolecule *ml);

#ifdef __cplusplus
}
#endif

#endif
