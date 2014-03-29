
function addCaptions() {
  var images = $(".clarity-book img");
  jQuery.each(images, function(i)  {
    if((images[i].alt).length > 0) 
    {
      var div_img = $(document.createElement("div")).addClass("ui segment");
      $(images[i]).wrap(div_img);
      var div_label = $(document.createElement("div")).addClass("ui ribbon teal top attached label");
      div_label.append(images[i].alt);
      $(div_label).insertBefore(images[i]);
    }
  })
};

// Need to check if we have already been loaded
seen = 0;

$(document).ready(function()
{ 
  if (seen == 0)
  { 
    // not loaded before - so do the restyling once (need to moodle book print)
    $(".clarity-book img").addClass ("ui image");
    $(".clarity-book pre").addClass ("ui stacked segment");
    addCaptions();
    seen = 1;
  }

  $('.tab-menu.menu .item').tab();
});