// JavaScript Document
$().ready(function() {
		$('#accordionwrap #accordion').kwicks({
			max: 400,
			spacing: 1
		});
		
		/*$('.slideBar').live('keydown', function(e) { 
  			var keyCode = e.keyCode || e.which; 
			if (keyCode == 9) { 
					$('.description','#accordion > li').stop(true,true).fadeIn();
					$('.bgDescription','#accordion > li').stop(true,true).slideDown();
					$('.slideBar','#accordion > li').css("background-color","#fff");
					$('.slideBar','#accordion > li').css("opacity","0");
					$('.slideBar','#accordion > li').css("color","#000");	
					
					$('.description','#accordion > li').stop(true,true).fadeOut();
	            	$('.bgDescription','#accordion > li').stop(true,true).slideUp();
					$('.slideBar','#accordion > li').css("opacity","0.8");
					$('.slideBar','#accordion > li').css("color","#000");
		    } 
		});		
				*/
				
		$('#accordion > li').live('keypress', function(e) { 
  			var keyCode = e.keyCode || e.which; 
			if (keyCode == 9) { 
            	var $this = $(this);
            	$('.description',$this).stop(true,true).fadeIn();
            	$('.bgDescription',$this).stop(true,true).slideDown();
				$('.slideBar',$this).css("background-color","#fff");
				$('.slideBar',$this).css("opacity","0");
				$('.slideBar',$this).css("color","#000");			
		    } 
		});		
				
    	$('#accordion > li').hover(
	       	function () {
            	var $this = $(this);
            	$('.description',$this).stop(true,true).fadeIn();
            	$('.bgDescription',$this).stop(true,true).slideDown();
				$('.slideBar',$this).css("background-color","#fff");
				$('.slideBar',$this).css("opacity","0");
				$('.slideBar',$this).css("color","#000");			
	    	},
        	function () {
            	var $this = $(this);
            	$('.description',$this).stop(true,true).fadeOut();
            	$('.bgDescription',$this).stop(true,true).slideUp();
				$('.slideBar',$this).css("opacity","0.8");
				$('.slideBar',$this).css("color","#000");

	    	}
    	);
		
		});