#include <openbabel/obconversion.h>
#include <openbabel/mol.h>
#include <openbabel/forcefield.h>
#include <openbabel/oberror.h>

#include <iostream>

using namespace OpenBabel;
using namespace std;

/** \cond */
OBERROR extern OBMessageHandler obErrorLog;
/** \endcond */

/** \file energy.cpp

    \brief Main body of the cuikbabelenergy application.

    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikbabelenergy  [label="cuikbabelenergy"    color="#99ff99" shape=ellipse ];
      
      pdb     [label="pdb"   color="#ff9999"];

      pdb -> cuikbabelenergy
    }
    \enddot
    </center>

    Main body of the cuikbabelenergy application. This application computes
    the potential energy of a molecular conformation stored in a pdb file.

    This is just an exemple of how to access molecular information via OpenBabel. However
    this should not be used in general but \ref cuikenergy.c "cuikenergy" which computes energy from
    configurations.

    \todo Remove this from the repository.
*/

/**  
   \brief Main body of the cuikbabelenergy application.

   Main body of the cuikbabelenergy application.

   Use:
       - \b cuikbabelenergy \e problem_name.pdb
       .
   where
       - \e problem_name contains the molecular information.
       .
   The extension (e.g., \e .pdb ) is COMPULSATORY. All the extensions managed by OpenBabel can be used.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikbabelenergy command itself and its arguments). 
   \param argv Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **argv)
{
  OBConversion conv;
  OBMol mol;
  OBForceField *ff;

  // Avoid warning messages
  OpenBabel::obErrorLog.SetOutputLevel(obError);

  if (argc < 2) 
    {
      cout << "Usage: " << argv[0] << " <filename>" << endl;
      return 1;
    }

  // Read the file.
  conv.SetInFormat(conv.FormatFromExt(argv[1]));
  conv.ReadFile(&mol,argv[1]);

  // Get the forcefield.
  ff=OBForceField::FindType("MMFF94");

  // Setup the forcefield.
  if (!ff->Setup(mol)) 
    {
      cout << "Could not setup forcefield." << endl;
      return 1;
    }

  // Print the enegy and unit.
  cout << ff->Energy() << " " << ff->GetUnit() << endl;

  return 0;
}
