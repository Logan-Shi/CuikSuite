#ifndef FILENAMEH
#define FILENAMEH

/** 
   \file filename.h

   \brief  Definition of the Tfilename type and the associated functions.

   Functions to deal with file names.

   The main files used in the CuikSuite have the following extensions (the base name is the same for all
   of them and given by the problem name, i.e., for the FourBars problems we can have 
   FourBars.world, FourBars.param, FourBars.joints, etc.):

      - <b>.world</b>  Used for files describing mechanisms (links + joints) plus
        obstacles. Plannint tools directly operate on the world files but to use the position analysis
	tools we first generate equation files from world files using
	\ref cuikequations.c "cuikequations". The type of equations obtained depend on the
	\ref CT_REPRESENTATION "representation" used. The most common
	representations are \ref REP_LINKS "LINKS" 
	(described <a href="http://www.iri.upc.edu/people/porta/Docs/tro09.pdf">here</a>) and
	\ref REP_JOINTS "JOINTS" (similar to the widely-used 
        <a href="http://en.wikipedia.org/wiki/Denavit%E2%80%93Hartenberg_parameters">DH</a> formulation).
	The first one is redundant (it uses more variables than degrees of freedom)
	and the second is not.
      - <b>.param</b> File with the parameters. The default set of parameters
        is in share/CuikSuite/default.param \ref parameters.h "Here" you can find
	a description of the parameters. 
      - <b>.joints</b> Initial and final configuration for path/motion planning. Also the
        initial point when defining an altas.
        This is used for non-redundant (e.g., \ref CT_REPRESENTATION "REPRESENTATION" = JOINTS) formulation.
        We can generate .joints files from .links using \ref cuiklinks2joints.c "cuiklinks2joints".
	The inverse is obtained using \ref cuikjoints2links.c "cuikjoints2links".
	Joint values can be obtained interactively using \ref cuikmove.c "cuikmove"
	or the \ref cuikexplore.c "cuikexplore".
      - <b>.links</b> Initial and final configuration for path/motion planning. Also the
        initial point when defining an altas. This
        is used if the mechanisms is modelled using a redundant formulations
	(e.g., \ref CT_REPRESENTATION "REPRESENTATION" = LINKS). We typically do not
	use this file, but the equivalent <b>.joint</b> file.
      - <b>.cuik</b> Files including variables and equations. The solution set
        of a cuik file can be obtained using \ref cuik.c "cuik". This will produce
	a .sol file. 
      - <b>_simp.cuik</b> Files including variables and equations for simplified
        systems. Simplified systems are obtained from .cuik systems using
	\ref cuiksimplify.c "cuiksimplify". The simplification mainly removes
        variables assigned to constant values and variables linearly related to other
        variables. We typically don't use simplified systems since the cuik applications
	automatically simplify the problem (i.e., the simplification is done silently on the
	background).
      - <b>.sol</b> Solution file resulting from \ref cuik.c "cuik". These files include
        the solution set of a given system of equations in the form of boxes.
	Solution files can be represented graphicall using \ref cuikplot3d.c "cuikplot3d"
      - <b>_path.sol</b> Solution of a path planning process. It includes a sequence of
        configurations connecting the start and goal configurations defined in the corresponding
	<b>.joints</b> or <b>.links</b> files.
      - <b>_traj.sol</b> Solution of a motion plannig process.  It includes a sequence of
        states, actions, and exectuion time for each action connecting the start and goal configurations defined in the corresponding
	<b>.joints</b> or <b>.links</b> files.
      - <b>.atlas</b> File including an atlas describing a manifold.
        An atlas can be represented graphicaly using \ref cuikplotatlas.c "cuikplotatlas"
      - <b>.rrt</b> File with an RRT derived during path planning.
        An atlas can be represented graphicaly using \ref cuikplotrrt.c "cuikplotrrt"
      - <b>.arrt</b> File with the AtlasRRT information. Basically the information to
        coordinate a RRT and an Atlas. 
      - <b>.gcl</b> Files with 3D geometry to be displayed with 
        <a href="http://www.geomview.org">Geomview</a>. This files are
	obtained using, for instance, \ref cuikplot3d.c "cuikplot3d",
	\ref cuikplotatlas.c "cuikplotatlas",
	or \ref cuikplotrrt.c "cuikplotrrt".
      - <b>.pdb</b> Typical extension of files prividing molecular information
        (Protein Daba Bank file format).
      - <b>.atom</b> User provided atom 3d positions. If available, these positions
        are used to overide those in the pdb files which are given with low
	accuracy.
      - <b>.tens</b> Tensegrity structures.
      .

   \sa filename.c Tfilename 
*/

/************************************************************************************/
/** \brief File extension for equation files.

    File extension for equation files.
*/
#define CUIK_EXT              "cuik"

/** \brief Default file extension for bio-info files. 

    Default extension for bio-info files (files including information about
    molecules). 
    The system is interfaced with OpenBabel and, thus, we can manipulate many different
    types of bio-info files. The particular type to read/write is deduced from the
    file extension. If not given, though, 'pdb' is used.
*/
#define PDB_EXT               "pdb"

/** \brief File extension for atom coordinates files. 

    File extension for files giving atom 3D coordinates. This files are used, if 
    available, to overide the atom position form pdb files, that are typically
    given with low accuracy.
*/
#define ATOM_EXT              "atoms"

/** \brief File extension for atom rigid groups. 

    File extension for files giving rigid groups of atoms.
*/
#define RGROUPS_EXT            "rgroups"

/** \brief File extension for geomview OFF files. 

    File extension for geomview OFF files. They include a description 3D
    geometry in the form of vertices and faces.
*/
#define OFF_EXT               "off"

/** \brief File extension for slam files. 

    File extension for slam files. They include a description of
    the trajectory of a robot in 2D and the landmarks it observes.

    Not used yet.
*/
#define SLAM_EXT              "slam"

/** \brief File extension for CAD files. 

    File extension for CAD files. They include geometric constraints.

    Not used yet.
*/
#define CAD_EXT               "cad"

/** \brief File extension for URDFs. 

    File extension for URDFs: universal robot description files.
*/
#define URDF_EXT              "urdf"

/** \brief File extension for SDFs. 

    File extension for SDFs: Gazebo input files.
*/
#define SDF_EXT               "sdf"

/** \brief File extension for parameter files.

    File extension for parameter files. 
*/
#define PARAM_EXT             "param"

/** \brief File extension for solution files.

    File extension for solution files. 
*/
#define SOL_EXT               "sol"

/** \brief File extension for solution files with dummies.

    File extension for solution files including dummy variables.
*/
#define SOL_WITH_DUMMIES_EXT  "dsol"

/** \brief File extension for the mechanism axes.

    File extension for mechanism axes.
*/
#define AXES_EXT               "axes"

/** \brief File extension for arrays of costs.

    File extension for sets of costs. Used to colorize atlas.
*/
#define COST_EXT               "cost"

/** \brief File extension for arrays of energy.

    File extension for sets of energy.
*/
#define ENERGY_EXT             "energy"

/** \brief File extension for problem files. 

    File extension for problem files. 
*/
#define WORLD_EXT             "world"

/** \brief File extension for 3D plot files. 

    File extension for 3D plot files. 
*/
#define PLOT3D_EXT            "gcl"

/** \brief File extension for 2D plot files. 

    File extension for 2D plot files. 
*/
#define PLOT2D_EXT            "fig"

/** \brief File extension for files with samples represented by the link poses.

    File extension for files including samples represented
    giving poses for the links.
*/
#define LINKS_EXT             "links"

/** \brief File extension for files with samples represented by the joint values.

    File extension for files including samples represented
    giving values for the degrees of freedom.
*/
#define JOINTS_EXT            "joints"

/** \brief File extension for files storing the interval solver state. 

    File extension for files storing the interval solver state.
*/
#define STATE_EXT             "state"

/** \brief File extension for files storing atlas. 

    File extension for files storing atlas on manifolds.
*/
#define ATLAS_EXT             "atlas"

/** \brief File extension for files atlas graph information. 

    File extension for files storing neighbouring relation 
    between the charts in an antals.
*/
#define ATLAS_GRAPH_EXT       "agraph"

/** \brief File extension for files storing rrt's. 

    File extension for files storing rrts on manifolds.
*/
#define RRT_EXT               "rrt"

/** \brief File extension for files storing AtlasRTT's. 

    File extension for files storing AtlasRRTs. These files
    store the information linking the RRT and the Atlas
*/
#define ATLAS_RRT_EXT         "arrt"

/** \brief File extension for files storing residue indentifiers. 

    File extension for files storing the identifiers of the residues
    to be considered flexible in a given protein. 
    If this file does not exits the degrees of freedom are deduced from
    the bond type (double bonds are fixed and single bonds allow for rotations).
*/
#define RES_EXT               "res"

/** \brief File extension for files storing rigid part of molecules. 

    File extension for files storing the rigid parts of a given molecule
    The files include a list of atoms together with the identifier of the
    rigid including them, if any. Atoms in no rigid are assigned to 0.
*/
#define RIGID_EXT             "rigids"

/** \brief File extension for files storing the hinges of a molecule. 

    File extension for files storing the hinges connecting the
    rigid parts of a given molecules. The hinges are a set of
    rotation between given pairs of atoms.
*/
#define HINGE_EXT             "hinges"

/** \brief File extension for files describing tensegrities. 

    File extension for files describing tensegrity structures.
*/
#define TENSEGRITY_EXT        "tens"

/** \brief File extension for files including forces. 

    File extension for files including foces. They are typically
    generated with the \ref cuikworldforces.c "cuikworldforces" 
    application, processing a solution set (i.e., a solution 
    path of a planning process).
*/
#define FORCES_EXT            "forces"


/************************************************************************************/

/** 
   \brief Data structure to hold the information about the name of a file.

   Data structure to hold the information about the name of a file.
   
   \sa filename.h filename.c
 */
typedef struct {
  char *path;      /**< The path of the file. */
  char *name;      /**< The name of the file. */
  char *ext;       /**< The extension of the file. */
  char *baseName;  /**< The path plus the name. */
  char *fullName;  /**< The path plus the name plus the extension. */
} Tfilename;

/** 
   \brief Constructor

   Generates a Tfilename structure.

   \param path The path. If not given we get it from the system and is
               the path from of the directory from where the application is exeucted.
   \param name The name of the file. If the given name includes part of a path, it is
               removed from the name and added to the path data field.
   \param suffix A suffix to add to the name. Possibly NULL.
   \param ext The extension for the file.
   \param fn The filename structure to create.
*/
void CreateFileName(char *path,char *name,char *suffix,char *ext,Tfilename *fn);

/** 
   \brief Gets the file full name (paht+name+extension).

   Gets the file full name (path+name+extension).

   \param fn The filename structure.

   \return Returns the full name for the file.
*/
char *GetFileFullName(Tfilename *fn);

/** 
   \brief Gets the file path.

   Gets the file path.

   \param fn The filename structure.

   \return Returns the path for the file.
*/
char *GetFilePath(Tfilename *fn);

/** 
   \brief Gets the file base name (paht+name) .

   Gets the file base name (paht+name).

   \param fn The filename structure.

   \return Returns the base name (path+name) for the file.
*/
char *GetFileBaseName(Tfilename *fn);

/** 
   \brief Gets the file name.

   Gets the file name.

   \param fn The filename structure.

   \return Returns the name for the file.
*/
char *GetFileName(Tfilename *fn);

/** 
   \brief Gets the file extension.

   Gets the file extension.

   \param fn The filename structure.

   \return Returns the extension for the file.
*/
char *GetFileExtension(Tfilename *fn);

/** 
    \brief Creates a link to a given filename.

    Creates a link to a given filename with a given extension.

    \param fn1 File to link.
    \param ext Extension of the files.
    \param fn2 File name of the link.
*/
void LinkFileNameWithExtension(char *fn1,char *ext,Tfilename *fn2);


/** 
   \brief Destructor.

   Deleltes the Tfilename structure.

   \param fn The filename structure to delete.
*/
void DeleteFileName(Tfilename *fn);

#endif
