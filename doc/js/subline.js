function subline_hide_all_blocks()
{
    $('#subline_presentation').hide();
    $('#subline_areas').hide();
    $('#subline_projects').hide();
    $('#subline_staff').hide();
    $('#subline_publications').hide();
    $('#subline_techtransfer').hide();
    $('#subline_facilities').hide();
    $('#subline_back_button').hide();
}

function enable_menu_option(name)
{
    $('.subline_menu_option').removeClass('selected');
    $('.subline_show_' + name).addClass('selected');
    if (name != 'presentation')
        $('#subline_back_button').show();
}

/* The function will display the page element and add the proper
 * anchor to track where inside the subline it is (if not specified otherwise 
 */
function show_only_element(name, add_anchor_to_url) 
{
    subline_hide_all_blocks();
    $('#subline_' + name).show();
    enable_menu_option(name);

    // By default, add_anchor to url is enable
    add_anchor_to_url = typeof add_anchor_to_url !== 'undefined' ? add_anchor_to_url : true;
    if (add_anchor_to_url)
        window.location.hash = name;
}

$().ready(function() {

    $('.subline_show_presentation').click(function() {
        show_only_element('presentation');
        return false;
    });

    $('.subline_show_areas').click(function() {
        show_only_element('areas');
        return false;
    });

    $('.subline_show_specific_area').click(function() {
        show_only_element('areas', false);
    });

    $('.subline_show_projects').click(function() {
        show_only_element('projects');
        return false;
    });

    $('.subline_show_staff').click(function() {
        show_only_element('staff');
        return false;
    });

    $('.subline_show_publications').click(function() {
        show_only_element('publications');
        return false;
    });

    $('.subline_show_techtransfer').click(function() {
        show_only_element('techtransfer');
        return false;
    });

    $('.subline_show_facilities').click(function() {
        show_only_element('facilities');
        return false;
    });
});
