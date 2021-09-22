// Script for displaying the description_note
$().ready(function() {
        $("h5 a.note, h5 a.note_academic").live("click", function() {
                var note = $(this).parent().siblings(".description_note");
                var msg = 'Description';
                if ( $(this).parents().is("#publications_list") ){
                    var msg = 'Abstract';
                }

                if ( note.is(":visible") ) {
                        note.hide("slow");
                        $(this).html('<img src="/www/images/open.png" alt="pdf"/> ' + msg);
                        $(this).css("background-color","transparent");
                        $(this).css("color","#c80000");
                }else{
                        $(this).html('<img src="/www/images/close.png" alt="pdf"/>' + msg);
                        $(this).css("background-color","#555");
                        $(this).css("color","#fff");
                        note.show("slow");
                }

                return false; //Prevent browser jump to link anchor
         });
});
