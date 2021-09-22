#ifndef BIOWORLDH
#define BIOWORLDH

#include "parameters.h"
#include "world.h"
#include "babel.h"
#include "vector.h"
#include "htransform.h"
#include "box.h"

/** 
    \file bioworld.h

    \brief A bridge between world structures and biological information.

    A bridge between world structures and biological information.

    \sa bioworld.c
*/

/** 
    \brief Structure with the molecular and the mechanical information.

    Structure with the molecular and the mechanical information.
    
    \sa bioworld.h bioworld.c
*/
typedef struct {
  Tworld w;               /**< The world structure. */ 
  TMolecule *m;           /**< The biological information. */
  unsigned int na;        /**< Number of atoms */
  unsigned int nb;        /**< Total number of bonds */
  unsigned int nba;       /**< (Over estimation of the) Total number of bond angles */
  double *localPos;       /**< Positions of the atoms in local coordinates of each link. */ 
  double *pos;            /**< Current positions of the atoms in global coordinates. */ 
  unsigned int *nbAtom;   /**< Number of bonds for each atom. */
  unsigned int nl;        /**< Number of links. */
  Tvector links;          /**< List of the first atom in each link. */
  unsigned int *linkID;   /**< Link identifier for each atom*/

  unsigned int nj;        /**< Number of joints. */
  Tvector joint1;         /**< List of the first atom in each joint. */
  Tvector joint2;         /**< List of the second atom in each joint. */

  unsigned int *linkList; /**< Linked list of the atoms in each link. */

  THTransform *g2l;       /**< Transform giving positions/vectors in the link 
			     local reference frames from position/vectors in 
			     the global frame. */
  boolean cut;            /**< TRUE if the world only includes  the atoms in a
			     given box. */
  Tbox cutB;              /**< The cut box, if any. */
} TBioWorld;

/** 
    \brief Initializes a world form a biomolecule.

    Initializes a world structure from biological information.

    \param p The set of parameters.
    \param filename The name for the file with the biological
                    information. All formats available in babel 
		    can be used.
    \param maxAtomsLink Links with more atoms than this limit are
                        represented in wireframe. This is faster
			for visualization but it does not allow
			to detect collisions with the link.
			This is to be used only for visualization.
			Use NO_UINT for no limit (all in facy).
    \param conformation Configuration of the molecule (space 
           allocated internally).
    \param bw The BioWorld to initialize.

    \return TRUE if the BioWorld could be initialized.
*/
boolean InitBioWorld(Tparameters *p,char *filename,unsigned int maxAtomsLink,
		     double **conformation,
		     TBioWorld *bw);

/** 
    \brief Enforces all bond lengths and angles to be the same.

    Enforces all bond lengths and angles to be the same for each pair
    or triplet of atoms of different type.

    We set up a set of constraints and finds a point that holds
    them form the current conformation using a local procedure.
    The new point is used to change the atom positions in the 
    given bioworld.

    \param p The set of parameters.
    \param bw The BioWorld to initialize.
*/
void AdjustBioWorldGeometry(Tparameters *p,TBioWorld *bw);

/** 
    \brief Returns a pointer to the world generated from the bio-information.

    Returns a pointer to the world generated from the bio-information.

    This function is provided for convenience but
    caution must be taken not to modify this internal structure.

    \param bw The BioWorld to query.

    \return A pointer to the internal world structure.
*/
Tworld *BioWorldWorld(TBioWorld *bw);

/** 
    \brief Number of atoms in the molecule.

    Number of atoms in the molecule.

    \param bw The BioWorld to query.

    \return The number of atoms in the molecule.
*/
unsigned int BioWorldNAtoms(TBioWorld *bw);

/** 
    \brief Number of variables used to represent a conformation.

    Number of variables used to represent a conformation. 
    This changes for different representations (see \ref CT_REPRESENTATION)
    In any case this function returns the number of system varibles
    used to represent a  conformation. This is the number
    of variables appearing in the output files. Internally, though, a
    different number of variables migth be used (resulting from the 
    simplification and dummification of the equations, if applied).

    \param bw The BioWorld to query.

    \return The number of variables representing a conformation.
*/ 
unsigned int BioWorldConformationSize(TBioWorld *bw);

/** 
    \brief Computes the position of the atoms.

    Computes the position of the atoms in a molecule from the 
    conformation encoded in the \e conformation
    vector. The contents of this vector changes according to the
    representation used for the equations (see \ref
    CT_REPRESENTATION).

    \param p The set of parameters.
    \param simp TRUE if the sample is given in the simplified system.
    \param conformation The configuration.
    \param pos Array where to store the new positions (3 entries per atom).
    \param bw The BioWorld information.
*/

void BioWordGetAtomPositionsFromConformation(Tparameters *p,boolean simp,double *conformation,
					     double *pos,TBioWorld *bw);

/** 
    \brief Changes the position of the atoms.

    Changes the position of the atoms in a molecule. The new position
    is computed from the conformation encoded in the \e conformation
    vector. The contents of this vector changes according to the
    representation used for the equations (see \ref
    CT_REPRESENTATION).

    \param p The set of parameters.
    \param simp TRUE if the sample is given in the simplified system.
    \param conformation The configuration.
    \param bw The BioWorld information.
*/
void BioWordSetAtomPositionsFromConformation(Tparameters *p,boolean simp,
					     double *conformation,TBioWorld *bw);

/** 
    \brief Computes the RMSE.

    Computes the 
    <a href="http://en.wikipedia.org/wiki/Root_mean_square_deviation_(bioinformatics)">Root Mean Square Error</a>
    (RMSE) between the current the atom positions
    stored int he BioWorld structure and the atom position corresponding
    to another conformation. These atom postiions can be computed form
    conformations using \ref BioWordGetAtomPositionsFromConformation.

    If the flexibility of the molecule is reduced to only few residues
    only those are considered for the error.
    
    \param pos The atom positions for the new conformation.
    \param bw The BioWorld to be used as a reference.

    \return The RMSE.
*/
double BioWorldRMSE(double *pos,TBioWorld *bw);

/** 
    \brief Produces the internal coordinates from the atom positions.

    Generates a conformation (internal coordinates) from the atom positions).
    The exact form of the internal coordinates depend on the \ref CT_REPRESENTATION
    value in the file of parameters. If DOF is used, the conformation is
    represented in the tradional internal coordinates in molecular modeling
    (dihedral angles). Other representations are not typical in bio-engineering
    but in Robotics.

    \param p The set of parameters.
    \param atoms The 3d positions of the atoms.
    \param conformation The output conformation. Space is allocated internally.
    \param bw The BioWorld to query.

    \return The size of the conformation.
*/
unsigned int BioWordConformationFromAtomPositions(Tparameters *p,double *atoms,
						  double **conformation,TBioWorld *bw);

/** 
    \brief Computes the energy of a given configuration.

    Computes the energy of a given configuraion. This is used to
    implement T-RRT like algorithms on biomolecules.  The signature of
    this function is generic for all cost function (see \ref
    EvaluateCSCost).

    \param p The set of parameters.
    \param simp TRUE if the conformation is given in the simplified system.
    \param conformation Array giving the conformation.
    \param bw The BioWorld information.
*/
double BioWorldEnergy(Tparameters *p,boolean simp,double *conformation,void *bw);

/** 
    \brief Stores the BioWorld information in a molecular format (eg. pdb).

    Changes the atom positions and stores the resulting conformation into a
    molecular format.

    \param p The set of parameters.
    \param fname The name for the output file. The format of the file is infered
                 from the extension of the filename. All the formats available
		 in OpenBabel can be used.
    \param simp TRUE if the conformation is given in the simplified system.
    \param conformation Array giving the conformation.
    \param bw The BioWorld information store.
*/
void SaveBioWorldBioInfo(Tparameters *p,char *fname,boolean simp,double *conformation,
			 TBioWorld *bw);

/** 
    \brief Prints the BioWorld information into a file.

    Store the world information (stored into the BioWorld structure) 
    into a file so that it can be read as

    Moreover we generate a conformation deduced from the atom positions. This can be
    given it is already available to the caller (for instance as an output of 
    \ref InitBioWorld).

    The world and the conformation file can be used to generate the atlas or to plan.

    \param p The set of parameters.
    \param fname Name of the file where to store the information (different
                 extensions are used for the world and the sample files).
    \param argc Number of strings to be added to the world file header as comments.
    \param arg Strings to be added to the world file as comments. Right now, this is used
              to store in the command line used to create it.
    \param bw The BioWorld with the information to save.
*/
void PrintBioWorld(Tparameters *p,char *fname,int argc,char **arg,TBioWorld *bw);

/** 
    \brief Destructor.

    Releases the memory allocated in a BioWorld structure.
    
    \param bw The BioWorld information.
*/
void DeleteBioWorld(TBioWorld *bw);

#endif
