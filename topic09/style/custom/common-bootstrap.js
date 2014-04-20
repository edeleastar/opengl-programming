
function addCaptions() {
  var images = $("img");
  jQuery.each(images, function(i)  {
    if((images[i].alt).length > 0) 
    {
      var labelHtml = '<div> <span class="label label-info">' + images[i].alt + '</span> </div>';
      var div_img = $('<div/>').html(labelHtml).contents();
      $(images[i]).wrap(div_img);
    }
  });
};

// Need to check if we have already been loaded
seen = 0;

$(document).ready(function()
{ 
  if (seen == 0)
  { 
    // not loaded before - so do the restyling once (need to moodle book print)
    $("img").addClass ("img-responsive");
    addCaptions();
    seen = 1;
  }


});