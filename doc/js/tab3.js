// JavaScript Document

$(document).ready(function() {
		
		//On Click
		$("#submenu_lab li").click(function() {
						
				$("#submenu_lab li").css("background-color", "#ccc" );
				$("#submenu_lab li").css("color", "#000" );
				$("#submenu_lab li").removeClass("selected_submenu_lab" );
				var $this = $(this);		
				
				var element = $this.attr("id") ; //Get number of element clicked	
					
				$this.css("background-color", "#c80000");
			    $this.css("color", "#fff");
				$this.addClass("selected_submenu_lab");		
				
				switch(element){
					case 'f1':
						document.getElementById('text_box_lab').innerHTML = '<h3 > Presentation </h3> <p>  The Institute hosts 6 laboratories that provide hands on support to the various research activities. Four of these laboratories are devoted to build and test human centered robotics systems of all kind, including indoor challenging robotics applications, novel parallel mechanisms, and outdoor mobile robotic systems. The other two laboratories help the research activities in automatic control for energy management and fuel cells research. Complementary services also include a mechatronics workshop. </p> ';	
						document.getElementById('lab_pic').innerHTML = '<img src="images/techtransf/facilities/mosaic.png"/> ';	
						break;
					case 'f2':
						document.getElementById('text_box_lab').innerHTML = '<h3 > Perception and Manipulation Laboratory </h3> <p>  The Perception and Manipulation Laboratory is equipped with 2 workcells: one with 2 standard manipulators and an XY positioner, and the other with 2 WAM arms in a reconfigurable arrangement. Additionally, researchers can find a 3 fingered hand, a Delta haptic interface, force sensors, several conventional cameras, and high speed, high resolution, and 3D cameras. Laboratory service offers quick experimental setup, several standardized software tools, and expertise in robot control and perception algorithms. It also hosts the Humanoid Lab initiative, with 15 small humanoid robots. </p> ';	
						document.getElementById('lab_pic').innerHTML = '<img src="images/techtransf/facilities/labo_perc1.jpg"/> ';	
						break;
					case 'f3':
						document.getElementById('text_box_lab').innerHTML = '<h3 > Kinematics and Robot Design Laboratory </h3> </div> <p>  The Kinematics and Robot Design Laboratory was created thanks to the financial support of the VALTEC program, co-financed with FEDER funds, of the Autonomous Goverment of Catalonia. It was initially created to validate the practical interest of our parallel robot designs, but it has rapidly derived into an active lab where the prototypes designed by the researches of the Group of Kinematics and Robot Design are implemented as proofs of concept. </p>';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_kinematics.jpg"/> ';	
						break;									
					case 'f4':
						document.getElementById('text_box_lab').innerHTML = '<h3 > Mobile Robotics Lab </h3> <p>  The Mobile Robotics Laboratory is an experimental area primarily devoted to hands-on research with mobile robot devices. The lab includes 3 Pioneer platforms, 2 service robots for urban robotics research based on Segway platforms, and a 4-wheel rough outdoor mobile robot, a six-legged LAURON-III walking robot, and a vast number of sensors and cameras. </p> ';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_mobile.jpg"/> ';							
						break;					
					case 'f5':
						document.getElementById('text_box_lab').innerHTML = '<h3 > Barcelona Robot Laboratory </h3><p>  The Barcelona Robot Lab encompasses an outdoor pedestrian area of 10.000 sq m., and is provided with 21 fixed cameras, a set of heterogeneous robots, full coverage of wifi and mica devices, and partial gps coverage. The area has moderate vegetation and intense cast shadows, making computer vision algorithms more than challenging. </p> ';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_bcn.jpg"/> ';							
						break;					
					case 'f6':		
					document.getElementById('text_box_lab').innerHTML = '<h3 > Fuel Cell Control Laboratory</h3> <p> The objective of the Laboratory is the validation and testing of control strategies of fuel cell based energy conversion systems. The facilities are equipped with a supervisor system which monitors necessary safety conditions. Each of the five fuel cell test stations is equipped with the necessary sensors and actuators to be able to operate in a safe and automated way, as well as to modify the working conditions that affect a fuel cell (humidity, temperature, flow, etc.). </p> ';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_control.jpg"/> ';							
						break;		
					case 'f7':		
					document.getElementById('text_box_lab').innerHTML = '<h3 > Water-cycle Control Systems Laboratory </h3> <p> The aim of this laboratory is to test and validate modelling and control developments for dynamic systems associated to the water cycle. Hence, it provides platforms of pressure, flow and level processes, over which it is possible to implement real-time advanced control strategies. This laboratory is also open to offer services to other teams in the research community </p> ';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_water.jpg"/> ';	
						break;		
					case 'f8':		
					document.getElementById('text_box_lab').innerHTML = '<h3 > Mechatronics Workshop </h3>  <p>  The Workshop provides support in the design, construction, and maintenance of electric, electronic, and mechanical devices and prototypes for the research projects carried out at IRI. Current rapid prototyping equipment at the Workshop includes CNC machines and a 3D plastic printer. </p>  ';	
						document.getElementById('lab_pic').innerHTML = ' <img src="images/techtransf/facilities/labo_workshop.jpg"/> ';	
						break;							
				}
				return false; //Prevent browser jump to link anchor*/
		
		});
		//On Hover
	 	$("#submenu_lab li").hover(
			function() {									  
				var $this = $(this);		
				$this.css("background-color", "#aaa" );
			 	$this.css("color", "#fff" );
							
				$(".selected_submenu_lab").css("background-color", "#c80000" ); 
				$(".selected_submenu_lab").css("color", "#fff" ); 
		   },
		   function() {	
				var $this = $(this);
				$this.css("background-color", "#ccc" );
				$this.css("color", "#000" );	
				
				$(".selected_submenu_lab").css("background-color", "#c80000" ); 
				$(".selected_submenu_lab").css("color", "#fff" ); 
											
			}			
		);	  
	
	
	
	});