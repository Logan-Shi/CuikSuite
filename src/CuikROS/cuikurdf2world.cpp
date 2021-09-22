extern "C" {
  #include "cuiksystem.h"
  #include "parameters.h"

  #include "defines.h"
  #include "error.h"
  #include "filename.h"
  #include "htransform.h"
  #include "polyhedron.h"
  #include "color.h"
  #include "link.h"
  #include "world.h"
  #include "joint.h"
}

#include <stdlib.h>
#include <math.h>
#include <tinyxml2.h>
#include <strings.h>
#include <string>
#include <unordered_map>

using namespace tinyxml2;

/** \file cuikurdf2world.cpp

    \brief Main body of the \ref cuikurdf2world.cpp "cuikurdf2world" application.
    
    <center>
    \dot
    digraph applications {
      size="7,15"
      node [shape=record, style=filled, fontname=Helvetica, fontsize=12];

      cuikurdf2world    [label="cuikurdf2world"  color="#99ff99" shape=ellipse];
      
      URDF   [label="URDF"    color="#ff9999" ];
      world  [label="world"   color="#ff9999" ];

      URDF -> cuikurdf2world;
      cuikurdf2world -> world;
    }
    \enddot
    </center>

    Main body of the \ref cuikurdf2world.cpp "cuikurdf2world" application. This application reads
    URDFs (universal robot description files) and generates a world file from them. In this
    way we can take advantage of all the URDF defined by the ROS community.

    Note that to keed the number of dependencies low, we do not use the ROS utilities to parse
    the URDF files but we directly pase them using a XML parsing tool (the tinyxml2 library).
    This means that future modifications/extensions on the URDF format might not be
    captured by this tool (altough it can be easily adapted).

    Only the links and joints in the URDFs are considered (no dynamical parameters, etc).

    This is coded in cpp to use the tinyxml library.

    \todo Integrate the urdf2world into ROS to use all the ROS tools. However, this means
          that the application would require a full ROS installation.
*/

/**
    \brief Correct the angles given in the URDF.

    Angles in the URDF are typically given with low precision. This
    function tries to correct these angles (basically set the angle
    to PI when the given angle is very close to PI and similar 
    corrections).

    \param a The input angle.

    \return The corrected angle.
*/
double correctAngle(double a);

/**
   \brief Determines the transform for a node.

   Determines the homogeneous transform from the origin/rpy
   attributes of a node.

   \param t The transform to define.
   \param err true if an error has to be raised if the origin or the
              rpy fields are missing.
   \param element The element to process.
*/
void GetTransform(THTransform *t,bool err,XMLElement *element);

/**
    \brief Finds the first element with a particular label in the list of child nodes.

    Finds the first element with a particular label in the list of child nodes.
    We loop over the children of the node searching for an element with
    the given label.

    \param label The label of the element to search.
    \param child The node for the element. This is used for subsequent searches (see \ref FindNextElement).
    \param node The parent node.

    \return A pointer to the element or NULL if the element is not found.
*/
XMLElement *FindFirstElement(char *label,XMLNode **child,XMLNode *node);

/** 
    \brief Continues a search over the set of child nodes.

    Continues the search started with \ref FindFirstElement or
    with a previous call to FindNextElement.

    \param label The label from the element to search.
    \param child The child node where the start the search.

    \return A pointer to the element or NULL if the element is not found.
*/
XMLElement *FindNextElement(char *label,XMLNode **child);


/***********************************************************************************/

double correctAngle(double a)
{
  double b=a;

  PI2PI(b);

  if (fabs(b+M_PI)<0.001)
    b=-M_PI;
  else
    { 
      if (fabs(b-M_PI)<0.001)
	b=+M_PI;
      else
	{	  
	  if (fabs(b+M_PI_2)<0.001)
	    b=-M_PI_2;
	  else
	    { 
	      if (fabs(b-M_PI_2)<0.001)
		b=+M_PI_2;
	    }
	}
    }
  return(b);
}

void GetTransform(THTransform *t,bool err,XMLElement *element)
{
  double x,y,z,a,b,c;
  THTransform r;
  char *tp;

  /* Get the translation parametres */
  tp=(char *)element->Attribute("xyz");
  if (tp)
    {
      sscanf(tp,"%lf %lf %lf",&x,&y,&z);
      HTransformTxyz(x,y,z,t);
    }
  else
    {
      if (err)
	Error("Origin without xyz attribute");
      else
	 HTransformIdentity(t);
    }

  /* get the rotation parameters */
  tp=(char *)element->Attribute("rpy");
  if (tp)
    {
      sscanf(tp,"%lf %lf %lf",&a,&b,&c);
      a=correctAngle(a);b=correctAngle(b);c=correctAngle(c);
      HTransformYawPitchRoll(c,b,a,&r);
      HTransformProduct(t,&r,t);
    }
  else
    {
      if (err)
	Error("Origin without rpy attribute");
    }
}

XMLElement *FindFirstElement(char *label,XMLNode **child,XMLNode *node)
{
  XMLElement *element;
  bool found=false;
  
  *child=node->FirstChild();
  while((!found)&&(*child)) 
    {
      element=(*child)->ToElement();
      found=((element)&&(strcasecmp(element->Value(),label)==0));
      if (!found)
	*child=(*child)->NextSibling();
    }
  if (found)
    return(element);
  else
    return(NULL);
}

XMLElement *FindNextElement(char *label,XMLNode **child)
{
  XMLElement *element;
  bool found=false;
  
  *child=(*child)->NextSibling();
  while((!found)&&(*child)) 
    {
      element=(*child)->ToElement();
      found=((element)&&(strcasecmp(element->Value(),label)==0));
      if (!found)
	*child=(*child)->NextSibling();
    }
  if (found)
    return(element);
  else
    return(NULL);
}

/***********************************************************************************/

/** 
   \brief Main body of the \ref cuikurdf2world.cpp "cuikurdf2world" application.

   Main body of the \ref cuikurdf2world.cpp "cuikurdf2world" application.

   Use:
       - \b cuikurdf2world \e package_path \e problem_name.urdf [\e output.world]
       .
   where
       - \e package_path path to the root of the ROS package.
       - \e problem_name.urdf the URDF file to read (relative to the package path).
       - \e output.world is the name of the world file to create. This parameter is optional.
       .
   The \e .urdf extension is optional.

   \param argc Number of elements in the command line that starts the application (i.e., the 
               \b cuikurdf2world command itself and its arguments). 
   \param arg Strings with the arguments. 

   \return EXIT_SUCCESS (0) if the execution worked out fine and EXIT_FAILURE if not. 
*/
int main(int argc, char **arg)
{   
  if (argc>2)
    {
      Tfilename furdf;
      XMLDocument urdf;
      char *fileName;
      unsigned int lPath,lName;

      lPath=strlen(arg[1]);
      if (arg[1][lPath]=='/')
	{lPath--;arg[1][lPath]=0;}
      lName=strlen(arg[2]);

      NEW(fileName,lPath+lName+2,char);
      sprintf(fileName,"%s/%s",arg[1],arg[2]);
      fileName[lPath+lName+1]=0;

      /*Read the problem from file*/
      CreateFileName(NULL,fileName,NULL,(char *)URDF_EXT,&furdf);
      fprintf(stderr,"Parsing URDF                      : %s\n",GetFileFullName(&furdf));
      
      if (urdf.LoadFile((const char*)GetFileFullName(&furdf))==XML_SUCCESS)
	{
	  XMLNode *robotNode;
	  XMLElement *robot;

	  robot=FindFirstElement((char *)"robot",&robotNode,(XMLNode *)&urdf);
	  if (!robot)
	    Error("URDF without a robot definition?");
	  else
	    {
	      unsigned int i,l1,l2;
	      char *linkName,*jointName,*jointType,*jointParent,*jointChild;
	      XMLNode *linkNode,*jointNode,*partNode,*geomNode,*materialNode,*bodyNode,*colorNode,*parentNode,*childNode,*inertiaNode;
	      XMLElement *link,*joint,*part,*origin,*geom,*material,*body,*color,*parent,*child,*axis,*limit,*dynamicInfo,*mass,*inertia;
	      THTransform t,ts,tt;
	      Tcolor c;
	      Tpolyhedron p;
	      Tlink l;
	      Tjoint j;
	      Tworld w;
	      double *z,**point,**rangePoint,*a,*ap,**iMatrix;
	      double ll,ul; /* joint limits */
	      Tinterval range;
	      bool haveBody;
	      THTransform iFrame;
	      double mss;
	      double friction,damping,velocity,effort;
	      /* materials (colors) are declared once and re-used */
	      std::unordered_map<std::string,Tcolor> materials;

	      NEW(point,4,double*);
	      for(i=0;i<4;i++)
		NEW(point[i],3,double);

	      NEW(rangePoint,4,double*);
	      for(i=0;i<2;i++)
		NEW(rangePoint[i],3,double);

	      NEW(z,3,double);
	      NEW(a,3,double);
	      NEW(ap,3,double);

	      NEW(iMatrix,3,double*);
	      for(i=0;i<3;i++)
		NEW(iMatrix[i],3,double);

	      z[0]=0;z[1]=0;z[2]=0;
	      
	      /* Init the world to define */
	      InitWorld(&w);

	      /* First process the links */
	      printf("\n  Processing links\n");
	      link=FindFirstElement((char *)"link",&linkNode,robotNode);
	      while(link)
		{
		  linkName=(char *)link->Attribute("name");
		  printf("    Processing link: %s\n",linkName);

		  dynamicInfo=FindFirstElement((char *)"inertial",&partNode,linkNode);
		  if (dynamicInfo)
		    {
		      origin=FindFirstElement((char *)"origin",&inertiaNode,dynamicInfo);
		      if (origin)
			GetTransform(&iFrame,false,origin);
		      else
			HTransformIdentity(&iFrame);

		      mass=FindFirstElement((char *)"mass",&inertiaNode,dynamicInfo);
		      if (mass)
			mss=atof(mass->Attribute("value"));
		      else
			mss=0.0;

		      inertia=FindFirstElement((char *)"inertia",&inertiaNode,dynamicInfo);
		      if (inertia)
			{
			  double ixx,ixy,ixz,iyy,iyz,izz;

			  ixx=atof(inertia->Attribute("ixx"));
			  ixy=atof(inertia->Attribute("ixy"));
			  ixz=atof(inertia->Attribute("ixz"));
			  iyy=atof(inertia->Attribute("iyy"));
			  iyz=atof(inertia->Attribute("iyz"));
			  izz=atof(inertia->Attribute("izz"));

			  iMatrix[0][0]=ixx;iMatrix[0][1]=ixy;iMatrix[0][2]=ixz;
			  iMatrix[1][0]=ixy;iMatrix[1][1]=iyy;iMatrix[1][2]=iyz;
			  iMatrix[2][0]=ixz;iMatrix[2][1]=iyz;iMatrix[2][2]=izz;
			}
		      else
			{
			  iMatrix[0][0]=0.0;iMatrix[0][1]=0.0;iMatrix[0][2]=0.0;
			  iMatrix[1][0]=0.0;iMatrix[1][1]=0.0;iMatrix[1][2]=0.0;
			  iMatrix[2][0]=0.0;iMatrix[2][1]=0.0;iMatrix[2][2]=0.0;
			}
		      
		      InitLink(linkName,mss,iMatrix,&iFrame,&l);
		    }
		  else
		    InitLink(linkName,0.0,NULL,NULL,&l);

		  for(i=0;i<2;i++)
		    {
		      if (i==0)
			part=FindFirstElement((char *)"visual",&partNode,linkNode);
		      else
			part=FindFirstElement((char *)"collision",&partNode,linkNode);
		      if (part)
			{
			  /* origin of the visual/collision: to be applied to all the bodies */
			  origin=FindFirstElement((char *)"origin",&geomNode,partNode);
			  if (origin)
			    GetTransform(&t,true,origin);
			  else
			    HTransformIdentity(&t);

			  /* Color: to be applied to all the bodies */
			  material=FindFirstElement((char *)"material",&materialNode,partNode);
			  if (material)
			    {
			      char *sc;
			      double r,g,b;
			      std::string materialName;

			      materialName=material->Attribute("name");

			      /* check if the material includes the color declaration */
			      color=FindFirstElement((char *)"color",&colorNode,materialNode);
			      if (color)
				{
				  /* a new color (re)declaration */
				  sc=(char *)color->Attribute("rgba");
				  sscanf(sc,"%lf %lf %lf",&r,&g,&b);
				  NewColor(r,g,b,&c);
				  materials[materialName]=c; /* store the color for this material
							        just in case it is used latter on */
				}
			      else
				{
				  std::unordered_map<std::string,Tcolor>::const_iterator mat;

				  /* check if we have a material previously stored */
				  mat=materials.find(materialName);
				  if (mat==materials.end())
				    NewColor(0.5,0.5,0.5,&c); /* unknown material/color -> used a default color */
				  else
				    c=mat->second; /* use the color previously defined */
				}
			    }
			  else
			    NewColor(0.5,0.5,0.5,&c); /* default color */

			  /* Define a function with the code below and search also for spheres, cylinders and boxes */
			  /* The color (c) and transform (t) should be parameters of this function */
			  geom=FindFirstElement((char *)"geometry",&geomNode,partNode);
			  while (geom)
			    {
			      bodyNode=geomNode->FirstChild();
			      while(bodyNode)
				{
				  haveBody=false;
				  body=bodyNode->ToElement();
				  if (body)
				    {
				      haveBody=true;

				      HTransformIdentity(&ts);

				      if (strcasecmp(body->Value(),(char*)"mesh")==0)
					{
					  /* We have a mesh */
					  
					  unsigned int k;
					  char *s;
					  double sx,sy,sz;
					  char *meshName,*fileMeshName;
					  Tfilename fmesh;

					  meshName=(char *)body->Attribute("filename");

					  HTransformIdentity(&ts);
					  s=(char *)body->Attribute("scale");
					  if (s)
					    {
					      sscanf(s,"%lf %lf %lf",&sx,&sy,&sz);
				      
					      HTransformSetElement(0,0,sx,&ts);
					      HTransformSetElement(1,1,sy,&ts);
					      HTransformSetElement(2,2,sz,&ts);
					    }

					  /* Define the link with the collected information */
					  lName=strlen(meshName);
					  /* skip the 'package://' part of the mesh name */
					  k=0;
					  while ((i<lName)&&((meshName[k]!=':')||(meshName[k+1]!='/')||(meshName[k+2]!='/')))
					    k++;
					  if (k<lName) k+=3;
					  lName-=k;
					  /* and replace it by the package path as given by the user */

					  NEW(fileMeshName,lPath+lName+2,char);
					  sprintf(fileMeshName,"%s/%s",arg[1],&(meshName[k]));
					  fileMeshName[lPath+lName+1]=0;
					  					  
					  CreateFileName(NULL,fileMeshName,NULL,NULL,&fmesh);
					  printf("       Reading mesh: %s\n",GetFileFullName(&fmesh));
					  InitPolyhedronFromFile(&fmesh,&c,10,(i==0?DECOR_SHAPE:HIDDEN_SHAPE),&p);
					  DeleteFileName(&fmesh);
					  free(fileMeshName);
					}
				      else
					{
					  if (strcasecmp(body->Value(),(char*)"sphere")==0)
					    {
					      char *sr;
					      double r,z[3]={0,0,0};
					      
					      sr=(char *)body->Attribute("radius");
					      sscanf(sr,"%lf",&r);

					      NewSphere(r,z,&c,10,(i==0?DECOR_SHAPE:HIDDEN_SHAPE),&p);
					    }
					  else
					    {
					      if (strcasecmp(body->Value(),(char*)"cylinder")==0)
						{
						  char *sr,*sl;
						  double r,l;
						  double p1[3]={0,0,0},p2[3]={0,0,0};
					      
						  sr=(char *)body->Attribute("radius");
						  sscanf(sr,"%lf",&r);
						  sl=(char *)body->Attribute("length");
						  sscanf(sl,"%lf",&l);
						  
						  /* z-aligned cylinder (zero centered). Note that our
						     cylinders are open.... might need to close them !!*/
						  p1[2]=-l/2;
						  p2[2]=l/2;

						  NewCylinder(r,p1,p2,&c,10,(i==0?DECOR_SHAPE:HIDDEN_SHAPE),&p);
						}
					      else
						{
						  if (strcasecmp(body->Value(),(char*)"box")==0)
						    {
						      char *ss;
						      double x,y,z;
					      
						      ss=(char *)body->Attribute("size");
						      sscanf(ss,"%lf %lf %lf",&x,&y,&z);

						      NewBox(-x/2,-y/2,-z/2,x/2,y/2,z/2,&c,(i==0?DECOR_SHAPE:HIDDEN_SHAPE),&p);
						    }
						  else
						    /* unknow geometric object */
						    haveBody=false;
						}
					    }
					}
				    }
				  if (haveBody)
				    {
				      HTransformProduct(&t,&ts,&tt);
				      TransformPolyhedron(&tt,&p);

				      AddBody2Link(&p,&l);
				      DeletePolyhedron(&p);
				    }

				  bodyNode=bodyNode->NextSibling();
				}
			      geom=FindNextElement((char *)"geometry",&partNode);
			    }
			}
		    }

		  AddLink2World(&l,FALSE,&w);
		  DeleteLink(&l);

		  link=FindNextElement((char *)"link",&linkNode);
		}
	      /* Now process the joints */
	      printf("\n  Processing joints\n");
	      joint=FindFirstElement((char *)"joint",&jointNode,robotNode);
	      while(joint)
		{
		  jointName=(char *)joint->Attribute("name");
		  jointType=(char *)joint->Attribute("type");

		  parent=FindFirstElement((char *)"parent",&parentNode,jointNode);
		  jointParent=(char *)parent->Attribute("link");

		  child=FindFirstElement((char *)"child",&childNode,jointNode);
		  jointChild=(char *)child->Attribute("link");

		  l1=GetWorldLinkID(jointParent,&w);	
		  if (l1==NO_UINT)
		    Error("Unkown parent link when defining a joint");
		  
		  l2=GetWorldLinkID(jointChild,&w);		
		  if (l2==NO_UINT)
		    Error("Unkown child when defining joint");

		  printf("    Processing joint: %s [%s] %s <-> %s\n",jointName,jointType,jointParent,jointChild);

		  /* origin if provided */
		  origin=FindFirstElement((char *)"origin",&geomNode,jointNode);
		  if (origin)
		    GetTransform(&t,true,origin);
		  else
		    HTransformIdentity(&t);

		  /* axis if provided */
		  axis=FindFirstElement((char *)"axis",&geomNode,jointNode);
		  if (axis)
		    {
		      char *ap;

		      ap=(char *)axis->Attribute("xyz");
		      sscanf(ap,"%lf %lf %lf",&(a[0]),&(a[1]),&(a[2]));
		    }
		  else
		    { a[0]=1.0;a[1]=0.0;a[2]=0.0; }

		  HTransformApply(z,point[0],&t);
		  HTransformApply(a,point[1],&t);
		  point[2][0]=point[2][1]=point[2][2]=0.0;
		  point[3][0]=a[0];point[3][1]=a[1];point[3][2]=a[2];

		  DefineNormalVector(ap,a);
		  HTransformApply(ap,rangePoint[0],&t);
		  rangePoint[1][0]=ap[0];rangePoint[1][1]=ap[1];rangePoint[1][2]=ap[2];

		  /* dynamics if provided */
		  friction=0.0;
		  damping=0.0;
		  
		  dynamicInfo=FindFirstElement((char *)"dynamics",&geomNode,jointNode);
		  if (dynamicInfo)
		    {
		      char *fr,*da;
		      
		      fr=(char *)dynamicInfo->Attribute("friction");
		      if (fr)
			friction=atof(fr);

		      da=(char *)dynamicInfo->Attribute("damping");
		      if (da)
			damping=atof(da);
		    }
		  
		  /* Limits if provided */
		  velocity=INF;
		  effort=INF;
		  
		  limit=FindFirstElement((char *)"limit",&geomNode,jointNode);
		  if (limit)
		    {
		      char *ve,*ef;
		      
		      ll=atof((char *)limit->Attribute("lower"));
		      ul=atof((char *)limit->Attribute("upper"));
		      NewInterval(ll,ul,&range);

		      ve=(char *)limit->Attribute("velocity");
		      if (ve)
			velocity=atof(ve);
		      
		      ef=(char *)limit->Attribute("effort");
		      if (ef)
			effort=atof(ef);
		    }
		  else
		    NewInterval(-INF,INF,&range);

		  /* Now define the joint */
		  if (strcasecmp(jointType,(char *)"fixed")==0)
		    NewFixJoint(GetWorldNJoints(&w),
				l1,GetWorldLink(l1,&w),
				l2,GetWorldLink(l2,&w),
				&t,&j);
		  else
		    {
		      if (strcasecmp(jointType,(char *)"revolute")==0)
			NewRevoluteJoint(GetWorldNJoints(&w),REP_JOINTS,
					 l1,GetWorldLink(l1,&w),
					 l2,GetWorldLink(l2,&w),
					 (double **)point,TRUE,TRUE,&range,(double **)rangePoint,
					 FALSE,FALSE,NULL,
					 velocity,INF,effort,1.0,friction,damping,&j);
		      else
			{
			  if (strcasecmp(jointType,(char *)"continuous")==0)
			    NewRevoluteJoint(GetWorldNJoints(&w),REP_JOINTS,
					     l1,GetWorldLink(l1,&w),
					     l2,GetWorldLink(l2,&w),
					     (double **)point,FALSE,TRUE,&range,(double **)rangePoint,
					     FALSE,FALSE,NULL,
					     velocity,INF,effort,1.0,friction,damping,&j);
			  else
			    {
			      if (strcasecmp(jointType,(char *)"prismatic")==0)
				NewPrismaticJoint(GetWorldNJoints(&w),
						  l1,GetWorldLink(l1,&w),
						  l2,GetWorldLink(l2,&w),
						  (double **)point,&range,
						  FALSE,FALSE,
						  velocity,INF,effort,1.0,friction,damping,&j);
			      else
				{
				  if  (strcasecmp(jointType,(char *)"floating")==0)
				    NewFreeJoint(GetWorldNJoints(&w),
						 l1,GetWorldLink(l1,&w),
						 l2,GetWorldLink(l2,&w),
						 velocity,INF,effort,1.0,friction,damping,&j);
				  else
				  Error("Undefined joint type");
				}
			    }
			}
		    }
		  
		  AddJoint2World(&j,&w);
		  DeleteJoint(&j);

		  DeleteInterval(&range);

		  joint=FindNextElement((char *)"joint",&jointNode);
		}
	      printf("\n");

	      /* and print the world */
	      NoCheckAllCollisions(0,0,&w);
	      PrintWorld((argc>3?arg[3]:fileName),argc,arg,&w);

	      /* Generate the ".joint" file? */
	      /* Generate the ".param" file? */

	      DeleteWorld(&w);

	      for(i=0;i<3;i++)
		free(iMatrix[i]);
	      free(iMatrix);
	      
	      for(i=0;i<4;i++)
		free(point[i]);
	      free(point);
	      
	      for(i=0;i<2;i++)
		free(rangePoint[i]);
	      free(rangePoint);

	      free(z);
	      free(a);
	      free(ap);
	    }
	  free(fileName);
	}
      else
	Error("Unable to parse the XML in the URDF file");
      
      DeleteFileName(&furdf);
    }
 else
   {
     fprintf(stderr,"  Wrong number of parameters.\n");
     fprintf(stderr,"  Use:\n");   
     fprintf(stderr,"      cuikurdf2world <package path> <problem filename>.urdf [<output>.world]\n");
     fprintf(stderr,"  where <package path> is folder with the ROS package files (relative to the current directory).\n");
     fprintf(stderr,"        <problem filename> is the URDF file to read (relative to the package)\n");
     fprintf(stderr,"        <ouput> is the optional name for the world file to create (relative to the current directory).\n");
     fprintf(stderr,"    (the '.urdf' extension is not required)\n");
   }
  return(EXIT_SUCCESS);
}

