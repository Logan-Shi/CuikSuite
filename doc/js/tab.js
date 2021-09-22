// JavaScript Document
$(document).ready(function() {
	
		
		//$(".menu_news a:first").addClass("active");
		var elementClicked=0;
		//On Click
		  $("#news li a").click(function() {
				  
				  $("#news li a").css("background-color", "#fff" );
				  $("#news li a").css("color", "#000" );
				  var $this = $(this);		
				  
				  elementClicked = $this.attr("rel") ; //Get number of element clicked						  
			  
				  $this.css("color", "#fff" );
				  if (elementClicked==1){
					  $("#tab_news").css("z-index",100);
					  $("#tab_twitter").css("z-index",-1);
					  $this.css("background-color", "#555");
				  }
				  if (elementClicked==2){
					  $("#tab_news").css("z-index",-1);
					  $("#tab_twitter").css("z-index",100);
					  $this.css("background-color", "#c80000");
					  }
				  if (elementClicked==3){
					  $this.css("background-color", "#555" );			
				  } 				
			});
		  
			$("#news li a").hover(function() {				  
					var $this = $(this);		
					$this.css("background-color", "#ccc");
					$this.css("color", "#000");	
					if (elementClicked==1 || elementClicked==0 ){ $("#news li #first").css("background-color", "#555" );}					
					if (elementClicked==2){ $("#news li #second").css("background-color", "#c80000" );}
					if (elementClicked==3){ $("#news li #third").css("background-color", "#555" ); }			 				
			},
		   function() {			 
					$("#news li a").css("background-color", "#fff" );
					$("#news li a").css("color", "#000" );		
					if (elementClicked==1 || elementClicked==0){ $("#news li #first").css("background-color", "#555" );
										    $("#news li #first").css("color", "#fff" );
										 }					
					if (elementClicked==2){ $("#news li #second").css("background-color", "#c80000" );}
					if (elementClicked==3){ $("#news li #third").css("background-color", "#555" );
											$("#news li #first").css("color", "#fff" );
					}								
			}			
			);
	  
	  
	  });