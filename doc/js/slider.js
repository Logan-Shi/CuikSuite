// JavaScript Document
$(document).ready(function() {
	
		//Show the paging and activate its first link
		$(".paging").show();
		
		//Get size of the image, how many images there are, then determin the size of the image reel.
		var imageWidth = $(".window").width();
		var imageSum = $(".image_reel img").size();
		var imageReelWidth = imageWidth * imageSum;

		// Get random number to choose which banner will be showed
		//var num = Math.floor(Math.random()*imageSum);
		var num = imageSum-1;
        
		// Select the "circle" of the banner chosen
		$(".paging a").eq(num).addClass("active");
			
		//$(".paging a:first").addClass("active");
								
		//Adjust the image reel to its new size
		$(".image_reel").css({'width' : imageReelWidth});
		
		//Paging  and Slider Function
		rotate = function(){
			var triggerID = $active.attr("rel") - 1; //Get number of times to slide
			var image_reelPosition = triggerID * imageWidth; //Determines the distance the image reel needs to slide
		
			$(".paging a").removeClass('active'); //Remove all active class
			$active.addClass('active'); //Add active class (the $active is declared in the rotateSwitch function)
		
			//Slider Animation
			$(".image_reel").animate({
				left: -image_reelPosition
			}, 500 );
		
		}; 
		
		// Call the function to show the banner randomly chosen:
		$active = $(".paging a").eq(num);
		rotate(); 
		
		//On Click
		$(".paging a").click(function() {
			$active = $(this); //Activate the clicked paging
			rotate(); //Trigger rotation immediately
			return false; //Prevent browser jump to link anchor
		});
	
	});
