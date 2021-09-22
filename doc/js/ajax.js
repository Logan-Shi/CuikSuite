function publications_display(id)
{
       $('.conference_pubs').hide();
       $('.journal_pubs').hide();
       $('.other_pubs').hide();

       window.location.hash = id.substring(1);
       $(id).show();
}

function get_academic_work_type_from_submenu_id(id)
{
     if (id == 'o1')
        work_type = 'thesis'
     else if (id == 'o2')
        work_type = 'master_thesis'
     else
        work_type = 'pfc'

     return work_type;
}

/* 
 * Design to work with personal staff pages, when operating with menu 
 * - Category and subcategory are selected from menu
 */
function display_person_feature(category, subcategory)
{
    switch($.trim(category))
    {
        case 'Research projects':
            var type = 'projects'
            break;
        case 'Education':
            var type = 'education'
            break;
        case 'Publications':
            var type = 'publications'
            break;
        default:
            alert ("Unable to make the request")
            return ''
    }

    subcategory = typeof(subcategory) != 'undefined' ? subcategory : 'Recent';

    switch($.trim(subcategory))
    {
        case 'Archive':
            var prefix = 'archive'
            break
        case 'Recent':
            var prefix = 'current'
            break
        default:
            alert ("Unable to make the request")
            return ''
    }

    var user    = $('h2').attr('id');
    var feature = prefix + "_" + type;
    $('#person_blocks').load("get/" + user + "/" + feature);
    return;
}

$().ready(function() {

     $('#pub1').click(function() {
         $('.conference_pubs').show();
         $('.journal_pubs').show();
         $('.other_pubs').show();
         window.location.hash = '';
     });

     $('#pub2').click(function() {
         publications_display('.journal_pubs');
     });

     $('#pub3').click(function() {
         publications_display('.conference_pubs');
     });

     $('#pub4').click(function() {
         publications_display('.other_pubs');
     });

     /* Research project lists */

     $('#research_projects_archive').click(function() {
         $('#research_main_project_list').load("research/archive");
     })

     $('#research_projects_current').click(function() {
         $('#research_main_project_list').load("research/current");
     })

     $('#techtransfer_projects_archive').click(function() {
         $('#techtransfer_projects_list').load("techtransfer/archive");
     })

     $('#techtransfer_projects_current').click(function() {
         $('#techtransfer_projects_list').load("techtransfer/current");
     })

     /* Publication description */
     $("a.note").live("click", function(){ 
         var id_str = new String($(this).attr('id'));
         var id = id_str.substring(14);
         $('.description_note_' + id).load("/www/publications/get/" + id + "/summary");
     })

     /* Academic work description */
     $("a.note_academic").live("click", function(){ 
         var id_str = new String($(this).attr('id'));
         // id should be in form of "description_link_$wid_$type
         // Cut until second _
         var pos_first_under = id_str.indexOf('_');
         var tmp_str = id_str.substring(pos_first_under + 1); // cut substring
         var pos_second_under = tmp_str.indexOf('_');
         tmp_str = tmp_str.substring(pos_second_under + 1);
         var pos_third_under = tmp_str.indexOf('_');
         // $wid_type now in tmp_str
         // type is belong third
         var type = tmp_str.substring(pos_third_under + 1);
         // $wid is from beggining to _
         var id = tmp_str.substring(0, pos_third_under);
         $('.description_note_' + type + "_" + id).load("/www/" + type + "/get/" + id + "/description");
     })

     /* Academic works */
     $('#education_submenu li').click(function() {
         var work_type_id = $(this).attr('id')
         work_type = get_academic_work_type_from_submenu_id(work_type_id)

         $('#education_list').load(work_type + "/current")
     })

     $('#education_subsubmenu li').click(function() {
         var work_type_id = $('.selected_submenu').attr('id');
         work_type = get_academic_work_type_from_submenu_id(work_type_id);

         var id = $(this).attr('id');

         if (id == 's2')
             $('#education_list').load(work_type + "/archive");
         else
             $('#education_list').load(work_type + "/current");
     })

     /* Staff */
     $('#staff_submenu li').click(function() {
         $('.staff_list_section').hide();
         id = $(this).attr('id');
         section = id.substring(11);

         if (section == 'all')
               $('.staff_list_section').show();
         else
               $('#staff_list_' + section).show();
     })

     /* Person */
     $('#person_blocks > .block_list').hide();
     $('#person_blocks > .block_list:first-child').show();

     $('#submenuProfile li').click(function() {
         var category = $(this).text();
         display_person_feature(category);
         return
     });

     $('#subsubmenuProfile li').click(function() {
         var category = $('.selected_submenu').text();
         var subcategory = $(this).text();
         display_person_feature(category, subcategory);
         return
     });
})
