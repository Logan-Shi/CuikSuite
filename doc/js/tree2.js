// JavaScript Document// JavaScript Document
$().ready(function() {
	
		//On Click
		$(".submenu li").click(
			function() {				
				
				// Reset the background and font colors of all elements of the tree	
				$(".submenu li").css("background-color", "#ccc" );
				$(".submenu li").css("color", "#000" );
				$(".submenu li").removeClass("selected_submenu" );
				
				// Reset the background and font colors of all elements of the subtree	
				$(".subsubmenu li").css("background-color", "transparent" );
				$(".subsubmenu li").css("color", "#000" );
				$(".subsubmenu li").css("border-bottom","1px solid #999");

				// Set "active background and active font color" to the first element of the subtree	
				$(".subsubmenu li:first").css("color", "#c80000" );
				$(".subsubmenu li:first").css("border-bottom","1px solid #c80000");
				
				// Set "active background and active font color" to the element clicked			
				var $this = $(this);
				$this.css("background-color", "#c80000" );
			    $this.css("color", "#fff" );
				$this.css("border", "none" );				
				$this.addClass("selected_submenu");	
								
				var element = $this.attr("id") ; //Get element clicked	
				
				// Move the subtree position depending on the position of the element clicked
				switch(element){
					case 'o1':				
						$(".subsubmenu").css("margin-left", 20 );
						break;
					case 'o2':				
						$(".subsubmenu").css("margin-left", 150 );
						break;
					case 'o3':				
						$(".subsubmenu").css("margin-left", 250 );
						break;
				}
				return false; //Prevent browser jump to link anchor				
			}		

		);
	
		//On Hover
	 	$(".submenu li").hover(
			function() {									  
				var $this = $(this);		
				$this.css("background-color", "#aaa" );
			 	$this.css("color", "#fff" );
							
				$(".selected_submenu").css("background-color", "#c80000" ); 
				$(".selected_submenu").css("color", "#fff" ); 
				$(".selected_submenu").css("border", "none" );
		   },
		   function() {	
				var $this = $(this);
				$this.css("background-color", "#ccc" );
				$this.css("color", "#000" );
				
				$(".selected_submenu").css("background-color", "#c80000" ); 
				$(".selected_submenu").css("color", "#fff" ); 
				$(".selected_submenu").css("border", "none" );
											
			}			
		);	  
		
		//On Click
		$(".subsubmenu li").click(
			function() {				
				
				$(".subsubmenu li").css("color", "#000" );
				$(".subsubmenu li").css("border-bottom", "1px solid #999" );
				$(".subsubmenu li").removeClass("selected_subsubmenu" );
				
				var $this = $(this);	
						
				$this.css("background-color", "#555");
			    $this.css("color", "#fff");		
				$this.addClass("selected_subsubmenu" );		
				
				return false; //Prevent browser jump to link anchor				
			}		

		);
	
			//On Hover
	 	$(".subsubmenu li").hover(
			function() {									  
				var $this = $(this);		
				$this.css("background-color", "#aaa" );
			 	$this.css("color", "#fff" );
							
				$(".selected_subsubmenu").css("color", "#c80000" ); 
				$(".selected_subsubmenu").css("border-bottom","1px solid #c80000");
		   },
		   function() {	
				var $this = $(this);
				$this.css("background-color", "transparent" );
				$this.css("color", "#000" );
				$this.css("border-bottom", "1px solid #999" );				
				
				$(".selected_subsubmenu").css("color", "#c80000" ); 
				$(".selected_subsubmenu").css("border-bottom","1px solid #c80000");
											
			}			
		);	  
	
	
	
	});
	
	