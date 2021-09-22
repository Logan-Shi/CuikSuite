extern "C" {
  #include "cuiksystem.h"
  #include "parameters.h"

  #include "defines.h"
  #include "error.h"
  #include "basic_algebra.h"
  #include "filename.h"
  #include "htransform.h"
  #include "polyhedron.h"
  #include "color.h"
  #include "link.h"
  #include "world.h"
  #include "joint.h"
  #include "samples.h"
}

#include <stdlib.h>
#include <math.h>
#include <tinyxml2.h>
#include <strings.h>
#include <string>
#include <unordered_map>
#include <sys/stat.h>

using namespace tinyxml2;

/** \file cuikworld2sdf.cpp

    \brief Main body of the \ref cuikworld2sdf.cpp "cuikworld2sdf" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikworld2sdf    [label="cuikworld2sdf"  color="#99ff99" shape=ellipse];
      
      world  [label="world"   color="#ff9999" ];
      SDF    [label="SDF"     color="#ff9999" ];

      world -> cuikworld2sdf;
      cuikworld2sdf -> SDF;
    }
    \enddot
    </center>

    Main body of the \ref cuikworld2sdf.cpp "cuikworld2sdf" application. This application reads
    the information in a world file and generates an equivalent SDF file.

    SDF files are the input files for Gazebo. See the <a href="http://sdformat.org/">SDF format</a>
    specification for more details.

    This application is our first attempt to interface the CuikPackages with Gazebo. The
    idea is to obtain nicer mechanisms simulations, including dynamical aspects.
    Beside the generation of SDF files, we would also need to implement a cuikgazeboplayer
    (i.e., a way to command gazefo robots from the cuik outputs).

    Note that we implement a world2sdf and not a world2urdf. This is because the urdf
    is a severily liminted format which can not handle kinematic loops, the fundamental
    construction in the CuikSuite. 
    <a href="http://gazebosim.org/tutorials/?tut=ros_urdf">Here</a>
    you have a very nice argument about why to use the SDF format instead of the URDF one.

    CAUTION: This application is in development and not tested at all yet (we need to install
             Gazebo to test it properly). Up to now, links seems to be correctly exported but
	     conversion of joints is still to be tested.

    \todo Test the generation of sdf joints from cuik joints.

    \todo Implement the generation of sdf sph-sph  and sph-prs-sph joints.

    \todo Implement the cuikgazeboplayer. Probably as a trivial ROS node moving different
          degrees of freedom.
*/

/** 
    \brief Generates the sdf code for a given body.
    
    Generates the sdf code for a given body in a link (might be a static link, i.e., the world).

    \param path Path of the sdf file being generated.
    \param folder Folder where files are stored (typically, the last part of the path). 
    \param linkName Name of the link being generated (might be world).
    \param sdf The sdf document being generated.
    \param link The link element being generated. 
    \param j The identifier of the body in the link.
    \param b The body to be processed.
*/
void body2SDF(char *path,char *folder,char *linkName,XMLDocument *sdf,
	      XMLElement *link,unsigned int j,Tpolyhedron *b);


/** 
   \brief Defines the header of a joint in sdf.

   Adds the header of a joint definition in sdf.

   \param id The identifier of the joint.
   \param pName Name of the parent link.
   \param cName Name of the child link.
   \param model The sdf model being defined.
   \param sdf The sdf document being defined.

   \return The joint defined.
*/
XMLElement *jointHeader2SDF(unsigned int id,char *pName,char *cName,
			    XMLElement *model,XMLDocument *sdf);

/** 
    \brief Generates the sdf code for a given joint axis.
    
    Generates the sdf code for a given joint axis (used in revolute, prismatic, universal joints)

    \param label Name of the axis: axis or axis2.
    \param p1 First point defining the axis.
    \param p2 Second point defining the axis.
    \param parentFrame TRUE if the axis is defined in the paren frame.
    \param tp Transform giving the pose of the parent link.
    \param tc Transform giving the pose of the child link.
    \param tj Transform giving the joint location.
    \param ve Maximum velocity of the joint.
    \param ef Maximum effort of the joint.
    \param fr Friction of the joint.
    \param da Damping of the joint.
    \param limited True for joints with limits.
    \param range If the joint is limited, the corresponding range.
    \param sdf The sdf document bein generated.
    \param joint The joint element being generated.
*/
void axis2SDF(char *label,double *p1,double *p2,
	      boolean parentFrame,
	      THTransform *tp,THTransform *tc,THTransform *tj,
	      double ve,double ef,double fr,double da,
	      boolean limited,Tinterval *range,
	      XMLDocument *sdf,XMLElement *joint);

void body2SDF(char *path,char *folder,char *linkName,XMLDocument *sdf,
	      XMLElement *link,unsigned int j,Tpolyhedron *b)
{
  char buffer[1000];
  XMLElement *body;
  Tcolor color;
  unsigned int bt;
  Tfilename fbody;
  double center[3];
  
  if (GetPolyhedronStatus(b)==HIDDEN_SHAPE)
    body=sdf->NewElement("collision");
  else
    body=sdf->NewElement("visual");
  
  sprintf(buffer,"%s_%u",linkName,j);
  body->SetAttribute("name",buffer);
   
  if (GetPolyhedronStatus(b)!=HIDDEN_SHAPE)
    {
      XMLElement *transparency=sdf->NewElement("transparency");
      body->InsertEndChild(transparency);
      transparency->SetText(0);

      XMLElement *shadow=sdf->NewElement("cast_shadows");
      body->InsertEndChild(shadow);
      shadow->SetText(1);
		     
      XMLElement *material=sdf->NewElement("material");
      body->InsertEndChild(material);
		   
      XMLElement *ambient=sdf->NewElement("ambient");
      material->InsertEndChild(ambient);
		   
      GetPolyhedronColor(&color,b);
      sprintf(buffer,"%f %f %f 1",GetRed(&color),GetGreen(&color),GetBlue(&color));
      ambient->SetText(buffer);
    }
  link->InsertEndChild(body);

  XMLElement *geometry=sdf->NewElement("geometry");
  body->InsertEndChild(geometry);
	      
  bt=GetPolyhedronType(b);
  switch(bt)
    {
    case OFF:
      {
	sprintf(buffer,"x_%s_%u",linkName,j);
		    
	CreateFileName(path,buffer,NULL,(char *)"dae",&fbody);
	printf("    Saving mesh to: %s\n",GetFileFullName(&fbody));
	WriteDAEMesh(GetFileFullName(&fbody),b);
	//SavePolyhedron(GetFileFullName(&fbody),b);

	XMLElement *mesh=sdf->NewElement("mesh");
	geometry->InsertEndChild(mesh);
		    
	XMLElement *uri=sdf->NewElement("uri");
	mesh->InsertEndChild(uri);
		    
	sprintf(buffer,"model://%s/x_%s_%u.dae",folder,linkName,j);
	uri->SetText(buffer);
		    
	DeleteFileName(&fbody);
      }
      break;
    case SPHERE:
      {
	XMLElement *pose=sdf->NewElement("pose");
	body->InsertEndChild(pose);
		  
	GetPolyhedronCenter(center,b);
	sprintf(buffer,"%f %f %f 0 0 0",center[0],center[1],center[2]);
	pose->SetText(buffer);
		  
	XMLElement *sphere=sdf->NewElement("sphere");
	geometry->InsertEndChild(sphere);

	XMLElement *radius=sdf->NewElement("radius");
	sphere->InsertEndChild(radius);
	radius->SetText(GetPolyhedronRadius(b));
      }
      break;
    case CYLINDER:
      {
	double p1[3],p2[3],le;
	THTransform ta,tr;
	double r,p,y;

	GetPolyhedronDefiningPoint(0,p1,b);
	GetPolyhedronDefiningPoint(1,p2,b);
		    
	DifferenceVector(3,p2,p1,p2);
	le=Norm(3,p2); // length of the cylinder
		    
	Normalize(3,p2);
	SumVector(3,p1,p2,p2);

	/* gazebo cylinders are zero-centred along the z axis
	   We have to provide a transform to a general pose */
	HTransformTz(le/2.0,&tr);
	HTransformRy(M_PI_2,&ta);
	HTransformProduct(&ta,&tr,&tr);
	HTransformX2Vect(1,1,p1,p2,&ta);
	HTransformProduct(&ta,&tr,&tr);
		    
	XMLElement *pose=sdf->NewElement("pose");
	body->InsertEndChild(pose);
	GetYawPitchRoll(&y,&p,&r,&tr);
	sprintf(buffer,"%f %f %f %f %f %f",
		HTransformGetElement(0,3,&tr),
		HTransformGetElement(1,3,&tr),
		HTransformGetElement(2,3,&tr),
		r,p,y);
	pose->SetText(buffer);
		    
	XMLElement *cylinder=sdf->NewElement("cylinder");
	geometry->InsertEndChild(cylinder);

	XMLElement *radius=sdf->NewElement("radius");
	cylinder->InsertEndChild(radius);
	radius->SetText(GetPolyhedronRadius(b));
		    
	XMLElement *length=sdf->NewElement("length");
	cylinder->InsertEndChild(length);
	length->SetText(le);
      }
      break;
    case LINE:
    case SEGMENTS:
      Error("Lines and segments can not be converted to SDF format (yet)");
      break;
    case EMPTY_BODY:
      XMLElement *empty=sdf->NewElement("empty");
      geometry->InsertEndChild(empty);
      break;
    }
}

XMLElement *jointHeader2SDF(unsigned int id,char *pName,char *cName,
			    XMLElement *model,XMLDocument *sdf)
{
  char buffer[100];
  
  /* Now define the joints using these virtual links */
  XMLElement *joint=sdf->NewElement("joint");
  sprintf(buffer,"joint_%u",id);
  joint->SetAttribute("name",buffer);
  model->InsertEndChild(joint);
	  
  XMLElement *parent=sdf->NewElement("parent");
  joint->InsertEndChild(parent);
  parent->SetText(pName);
		
  XMLElement *child=sdf->NewElement("child");
  joint->InsertEndChild(child);
  child->SetText(cName);
  
  return(joint);
}

void axis2SDF(char *label,double *p1,double *p2,
	      boolean parentFrame,
	      THTransform *tp,THTransform *tc,THTransform *tj,
	      double ve,double ef,double fr,double da,
	      boolean limited,Tinterval *range,
	      XMLDocument *sdf,XMLElement *joint)
{
  char buffer[1000];
  THTransform t;
  double r,p,y;
  
  DifferenceVector(3,p2,p1,p2);    
  Normalize(3,p2);

  /* tj w.r.t. tc :  tp*tj=tc*t -> t=tc^-1*tp*tj */
  XMLElement *pose=sdf->NewElement("pose");
  joint->InsertEndChild(pose);
  HTransformInverse(tc,&t);
  HTransformProduct(&t,tp,&t);
  HTransformProduct(&t,tc,&t);
  GetYawPitchRoll(&y,&p,&r,&t);
  sprintf(buffer,"%f %f %f %f %f %f",
	  HTransformGetElement(0,3,&t),
	  HTransformGetElement(1,3,&t),
	  HTransformGetElement(2,3,&t),
	  r,p,y);
  pose->SetText(buffer);
		
  XMLElement *axis=sdf->NewElement(label);
  joint->InsertEndChild(axis);

  XMLElement *xyz=sdf->NewElement("xyz");
  axis->InsertEndChild(xyz);
  sprintf(buffer,"%f %f %f",p2[0],p2[1],p2[2]);
  xyz->SetText(buffer);

  if (parentFrame)
    {
      XMLElement *pframe=sdf->NewElement("use_parent_model_frame");
      axis->InsertEndChild(pframe);
      pframe->SetText("1");
    }
  
  if ((fr>0)||(da>0)||(ve<INF)||(ve<INF)||(limited))
    {
      XMLElement *dynamics=sdf->NewElement("dynamics");
      axis->InsertEndChild(dynamics);

      if (fr>0)
	{
	  XMLElement *friction=sdf->NewElement("friction");
	  dynamics->InsertEndChild(friction);
	  friction->SetText(fr);
	}

      if (da>0)
	{
	  XMLElement *damping=sdf->NewElement("damping");
	  dynamics->InsertEndChild(damping);
	  damping->SetText(da);
	}

      if ((ve<INF)||(ve<INF)||(limited))
	{
	  XMLElement *limit=sdf->NewElement("limit");
	  axis->InsertEndChild(limit);

	  if (ve<INF)
	    {
	      XMLElement *velocity=sdf->NewElement("velocity");
	      limit->InsertEndChild(velocity);
	      velocity->SetText(ve);
	    }

	  if (ef<INF)
	    {
	      XMLElement *effort=sdf->NewElement("effort");
	      limit->InsertEndChild(effort);
	      effort->SetText(ef);
	    }
		
	  if (limited)
	    {		    
	      XMLElement *lower=sdf->NewElement("lower");
	      limit->InsertEndChild(lower);
	      lower->SetText(LowerLimit(range));
		    
	      XMLElement *upper=sdf->NewElement("upper");
	      limit->InsertEndChild(upper);
	      upper->SetText(UpperLimit(range));
	    }
	}
    }
}

/***********************************************************************************/

/** 
   \brief Main body of the \ref cuikworld2sdf.cpp "cuikworld2sdf" application.

   Main body of the \ref cuikworld2sdf.cpp "cuikworld2sdf" application.

   Use:
       - \b cuikworld2sdf \e world_filename.world folder [\e sdf_filename.sdf]
       .
   where
       - \e world_filename Name of the world file to translate.
       - \e folder Folder where to store the generated sdf and related files.
       - \e sdf_filename.sdf Name of the SDF file to generate. If not given, the
                             world filename with extension .sdf is used.
       .
   The \e .world and \e .sdf extensions are optional.

   The idea is to generate all the files in a given folder that can be moved/linked
   to/from the gazebo model directory (typically .gazebo/models).


   Example of use:
     - bin/cuikworld2sdf examples/Jaco/jaco sdf
     .

   Then open the sdf/jaco.sdf in gazebo.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikworld2sdf command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{   
  if (argc>2)
    {
      Tfilename fparam;
      Tfilename fsdf;
      Tfilename ffolder;
      Tparameters parameters;
      Tworld world;
      XMLDocument sdf;
      unsigned int i,nl,j,nb,nj,jt,no,sl,k;
      double ms,**iMatrix;
      THTransform *iFrame;
      Tlink *l;
      Tjoint *jo;
      Tpolyhedron *b;
      double r,p,y;
      char buffer[1000];
      char *outputName,*fName;
      double *configuration;
      THTransform *tl;
      TLinkConf *def;
      
      printf("\n\n------------ Warning: This application is development (alpha version). Use at your own risk. ----------------\n\n");

      
      /* Reading the parameters */
      CreateFileName(NULL,arg[1],NULL,(char *)PARAM_EXT,&fparam);
      fprintf(stderr,"Reading parameter file            : %s\n",GetFileFullName(&fparam));
      InitParametersFromFile(GetFileFullName(&fparam),&parameters);
      
      /*Read the world file*/
      InitWorldFromFile(&parameters,TRUE,TRUE,arg[1],&world);
      
      /* Read the configuration. The conversion to sdf is only possible if you have
         a valid configuration for the mechanisms. Moreover, it is implicitly assumed
         that this valid configuration defines the zero of the joints, which is not
         always possible. In a complex mechanisms with many kinematic loops, 0 for
	 all joinst might not be a valid solution. Of course, the zeros can be offset
         so that (0...0) is a solution, but this is ofteh very difficult. Again, people
         defining formats think only in the trivial cases :( 
	 We get a valid configuration which might not be zero.  This however might 
	 produce incorrect joint limits. */
      ReadOneSample(&parameters,arg[1],GetWorldNumSystemVariables(&world),&configuration);
      GetLinkTransformsFromSolutionPoint(&parameters,FALSE,configuration,&tl,&def,&world);
      
      /* Creating the sdf file */
      if (argc>3)
	fName=arg[3];
      else
	fName=GetFileName(&fparam);

      /* ensure that the given folder exists */
      CreateFileName(NULL,arg[2],NULL,NULL,&ffolder);
      mkdir(GetFileFullName(&ffolder),0777);
      DeleteFileName(&ffolder);

      NEW(outputName,strlen(arg[2])+strlen(fName)+10,char);
      sprintf(outputName,"%s/%s",arg[2],fName);
      
      CreateFileName(NULL,outputName,NULL,(char *)SDF_EXT,&fsdf);
      fprintf(stderr,"Creating the SDF file             : %s\n",GetFileFullName(&fsdf));
      
      XMLDeclaration* declaration=sdf.NewDeclaration("xml version=\"1.0\"");
      sdf.InsertEndChild(declaration);
      
      XMLElement *root=sdf.NewElement("sdf");
      sdf.InsertEndChild(root);
      
      root->SetAttribute("version","1.5");

      XMLElement *worldSDF=sdf.NewElement("world");
      worldSDF->SetAttribute("name",GetFileName(&fsdf));
      root->InsertEndChild(worldSDF);
      
      XMLElement *model=sdf.NewElement("model");
      worldSDF->InsertEndChild(model);
      model->SetAttribute("name",GetFileName(&fsdf));

      nl=GetWorldNLinks(&world);
      for(i=0;i<nl;i++)
	{
	  l=GetWorldLink(i,&world);
	  printf("  Processing link: %s\n",GetLinkName(l));
 
	  if ((GetLinkType(l)==LINK_DeformX)||(GetLinkType(l)==LINK_NoRot))
	    Error("Tensegrity structures can not be handled yet");

	  if (GetLinkType(l)==LINK_PrismaticX)
	    sl=2; /* prismatic links can be divied in two sublinks */
	  else
	    sl=1;

	  for(k=0;k<sl;k++)
	    {
	      XMLElement *link=sdf.NewElement("link");
	      model->InsertEndChild(link);

	      if (k==0)
		link->SetAttribute("name",GetLinkName(l));
	      else
		{
		  sprintf(buffer,"%s_up",GetLinkName(l));
		  link->SetAttribute("name",buffer);
		}
	  
	      XMLElement *kinematic=sdf.NewElement("kinematic");
	      link->InsertEndChild(kinematic);
	      kinematic->SetText(1);

	      XMLElement *pose=sdf.NewElement("pose");
	      link->InsertEndChild(pose);
	      GetYawPitchRoll(&y,&p,&r,&(tl[i]));
	      sprintf(buffer,"%f %f %f %f %f %f",
		      HTransformGetElement(0,3,&(tl[i])),
		      HTransformGetElement(1,3,&(tl[i])),
		      HTransformGetElement(2,3,&(tl[i])),
		      r,p,y);
	      pose->SetText(buffer);
	      
	      ms=GetLinkMass(l);
	      if (ms>0.0)
		{
		  XMLElement *inertial=sdf.NewElement("inertial");
		  link->InsertEndChild(inertial);

		  XMLElement *mass=sdf.NewElement("mass");
		  inertial->InsertEndChild(mass);
		  mass->SetText(ms);

		  iFrame=GetLinkInertialFrame(l);
		  XMLElement *pose=sdf.NewElement("pose");
		  inertial->InsertEndChild(pose);
		  GetYawPitchRoll(&y,&p,&r,iFrame);
		  sprintf(buffer,"%f %f %f %f %f %f",
			  HTransformGetElement(0,3,iFrame),
			  HTransformGetElement(1,3,iFrame),
			  HTransformGetElement(2,3,iFrame),
			  r,p,y);
		  pose->SetText(buffer);

		  iMatrix=GetLinkInertiaMatrix(l);
		  XMLElement *inertia=sdf.NewElement("inertia");
		  inertial->InsertEndChild(inertia);
		  inertia->SetAttribute("ixx",iMatrix[0][0]);
		  inertia->SetAttribute("ixy",iMatrix[0][1]);
		  inertia->SetAttribute("ixz",iMatrix[0][2]);
		  inertia->SetAttribute("iyy",iMatrix[1][1]);
		  inertia->SetAttribute("iyz",iMatrix[1][2]);
		  inertia->SetAttribute("izz",iMatrix[2][2]);
		}

	      nb=LinkNBodies(l);	  
	      for(j=(k==0?0:nb/2);j<((sl==1)||(k==1)?nb:nb/2);j++)
		{	  
		  b=GetLinkBody(j,l);
		  body2SDF(GetFilePath(&fsdf),arg[2],GetLinkName(l),&sdf,link,j,b); 
		}
	    }
	}

      /* Now process the joints */

      /* Joints are always in the 0,0,0 pose in the parent link
	 and aligned with axis Z. This forces us to define one
	 virtual link for each joint (i.e., to explicitly define
	 the joint frame). */
      
      nj=GetWorldNJoints(&world);
      for(i=0;i<nj;i++)
	{
	  char *parentName;
	  
	  jo=GetWorldJoint(i,&world);
	  jt=GetJointType(jo);
	  
	  printf("  Processing joint: %u\n",i);

	  if ((jt==SPH_SPH_UP_JOINT)&&
	      (GetLinkType(JointFrom(jo))==LINK_PrismaticX))
	    {
	      sprintf(buffer,"%s_up",GetLinkName(JointFrom(jo)));
	      parentName=buffer;
	    }
	  else
	    parentName=GetLinkName(JointFrom(jo));

	  XMLElement *joint=jointHeader2SDF(i,parentName,GetLinkName(JointTo(jo)),
					    model,&sdf);
	  
	  switch(jt)
	    {
	    case FREE_JOINT:
	      /* nothing to translate */
	      break;
	    case FIX_JOINT:
	      /* fixed at the current configuration */
	      joint->SetAttribute("type","fixed");
	      break;
	    case REV_JOINT:
	      {
		double p1[3],p2[3];
	  
		joint->SetAttribute("type","revolute");
		
		GetJointPoint(0,0,p1,jo);
		GetJointPoint(0,1,p2,jo);

		axis2SDF((char *)"axis",p1,p2,TRUE,
			 &(tl[JointFromID(jo)]),&(tl[JointToID(jo)]),GetJointFrame(jo),
			 GetJointVelocity(jo),
			 GetJointEffort(jo),
			 GetJointFriction(jo),
			 GetJointDamping(jo),
			 LimitedJoint(jo),GetJointRange(jo),
			 &sdf,joint);
	      }
	      break;
	    case PRS_JOINT:
	      {
		double p1[3],p2[3];
		
		joint->SetAttribute("type","prismatic");
		
		GetJointPoint(0,0,p1,jo);
		GetJointPoint(0,1,p2,jo);
		
		axis2SDF((char *)"axis",p1,p2,TRUE,
			 &(tl[JointFromID(jo)]),&(tl[JointToID(jo)]),GetJointFrame(jo),
			 GetJointVelocity(jo),
			 GetJointEffort(jo),
			 GetJointFriction(jo),
			 GetJointDamping(jo),
			 LimitedJoint(jo),GetJointRange(jo),
			 &sdf,joint);
	      }
	      break;
	    case UNV_JOINT:
	      {
		double p1[3],p2[3];
	  
		joint->SetAttribute("type","universal");
		
		GetJointPoint(0,0,p1,jo);
		GetJointPoint(0,1,p2,jo);
		axis2SDF((char *)"axis",p1,p2,TRUE,
			 &(tl[JointFromID(jo)]),&(tl[JointToID(jo)]),GetJointFrame(jo),
			 GetJointVelocity(jo),
			 GetJointEffort(jo),
			 GetJointFriction(jo),
			 GetJointDamping(jo),
			 LimitedJoint(jo),GetJointRange(jo),
			 &sdf,joint);

		GetJointPoint(1,0,p1,jo);
		GetJointPoint(1,1,p2,jo);
		axis2SDF((char *)"axis2",p1,p2,FALSE,
			 &(tl[JointFromID(jo)]),&(tl[JointToID(jo)]),GetJointFrame(jo),
			 GetJointVelocity(jo),
			 GetJointEffort(jo),
			 GetJointFriction(jo),
			 GetJointDamping(jo),
			 LimitedJoint(jo),GetJointSecondRange(jo),
			 &sdf,joint);
	      }
	      break;
	    case SPH_JOINT:
	    case SPH_SPH_LOW_JOINT:
	    case SPH_SPH_UP_JOINT:
	      {
		double p1[3];
		double p2[3]={1,0,0};
		
		joint->SetAttribute("type","ball");
		
		GetJointPoint(0,0,p1,jo);
		HTransformApplyRot(p2,p2,GetJointFrame(jo));
		SumVector(3,p1,p2,p2);    
		axis2SDF((char *)"axis",p1,p2,TRUE,
			 &(tl[JointFromID(jo)]),&(tl[JointToID(jo)]),GetJointFrame(jo),
			 GetJointVelocity(jo),
			 GetJointEffort(jo),
			 GetJointFriction(jo),
			 GetJointDamping(jo),
			 (jt==SPH_JOINT?LimitedJoint(jo):FALSE),GetJointRange(jo),
			 &sdf,joint);
	      }
	      break;
	      /* add SPH_SPH, SPH_PRS_PSH */
	    default:
	      Error("Conversion of this type of joint to SDF is not implemented yet");
	    }
	    
	  if ((jt==SPH_SPH_LOW_JOINT)&&
	      (GetLinkType(JointFrom(jo))==LINK_PrismaticX))
	    {
	      /*define the prismatic joint between child and child_up*/
	      double p1[3]={0,0,0},p2[3]={0,0,0};
	      THTransform tc;

	      p1[0]=GetLinkConfExtension(&(def[JointToID(jo)]));
	      p2[0]=p1[0]+1;

	      sprintf(buffer,"%s_up",GetLinkName(JointTo(jo)));
	      joint=jointHeader2SDF(i,GetLinkName(JointTo(jo)),buffer,
				    model,&sdf);
	      
	      joint->SetAttribute("type","prismatic");

	      HTransformCopy(&tc,&(tl[JointToID(jo)]));
	      HTransformAcumTrans(p1[0],0,0,&tc);
		
	      axis2SDF((char *)"axis",p1,p2,TRUE,
		       &(tl[JointToID(jo)]),&tc,&tc,
		       GetJointVelocity(jo),
		       GetJointEffort(jo),
		       GetJointFriction(jo),
		       GetJointDamping(jo),
		       LimitedJoint(jo),GetJointRange(jo),
		       &sdf,joint);
	    }
	}
      
      /* Now the obstacles */
      no=GetWorldNObstacles(&world);
      if (no>0)
	{
	  XMLElement *environment=sdf.NewElement("environment");
	  root->InsertEndChild(environment);
	  sprintf(buffer,"%s_environment",GetFileName(&fsdf));
	  environment->SetAttribute("name",buffer);
	  environment->SetAttribute("static","true");
      
	  for(i=0;i<no;i++)
	    {
	      /* the obstacle link */
	      XMLElement *obstacleLink=sdf.NewElement("link");
	      environment->InsertEndChild(obstacleLink);
	      obstacleLink->SetAttribute("name",GetWorldObstacleName(i,&world));

	      /* the associated geometry */
	      Tpolyhedron *obs=GetWorldObstacle(i,&world); 
	      body2SDF(GetFilePath(&fsdf),arg[2],GetWorldObstacleName(i,&world),&sdf,obstacleLink,0,obs); 
	    }
	}
      
      /* Finally save the file */
      sdf.SaveFile(GetFileFullName(&fsdf));  
      
      /* And realease memeory */
      free(configuration);
      DeleteLinkTransforms(tl,def,&world);

      free(outputName);

      DeleteWorld(&world);
      DeleteParameters(&parameters);
      
      DeleteFileName(&fsdf);
      DeleteFileName(&fparam);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikworld2sdf <world filename> folder [<sdf filename>]\n");
     fprintf(stderr,"  where <world filename> is file with the world description\n");
     fprintf(stderr,"        <folder> folder where to store the generated sdf and related files.\n");
     fprintf(stderr,"        <sdf filename> is the sdf file to generate\n");
     fprintf(stderr,"                       If not give the world file name is used with sdf extension.\n");
   }
  return(EXIT_SUCCESS);
}

