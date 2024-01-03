$(document).ready(function () {
  $("#forward").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "w",
    });
    $("#forward").css("background", "AliceBlue");
    return false;
  });
  $("#backward").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "s",
    });
    $("#backward").css("background", "AliceBlue");
    return false;
  });
  $("#left").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "a",
    });
    $("#left").css("background", "AliceBlue");
    return false;
  });
  $("#right").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "d",
    });
    $("#right").css("background", "AliceBlue");
    return false;
  });
  $(".module").bind("touchend mouseup", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "b",
    });
    $(".module").css("background", "Seashell");
    return false;
  });
  $("#opengate").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "i",
    });
    $("#opengate").css("background", "AliceBlue");
    return false;
  });
  $("#closegate").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "k",
    });
    $("#closegate").css("background", "AliceBlue");
    return false;
  });
  $("#changemode").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "c",
    });
    if ($("#mode").text() == "Fast") {
      $("#mode").text("Slow");
    } else if ($("#mode").text() == "Slow") {
      $("#mode").text("Fast");
    }
    $("#changemode").css("background", "AliceBlue");
    return false;
  });
  $("#decrease_L_PWM").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "r",
    });
    $("#decrease_L_PWM").css("background", "AliceBlue");
    return false;
  });
  $("#increase_L_PWM").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "t",
    });
    $("#increase_L_PWM").css("background", "AliceBlue");
    return false;
  });
  $("#decrease_R_PWM").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "y",
    });
    $("#decrease_R_PWM").css("background", "AliceBlue");
    return false;
  });
  $("#increase_R_PWM").bind("touchstart mousedown", function () {
    $.getJSON($SCRIPT_ROOT + "/commands", {
      input: "u",
    });
    $("#increase_R_PWM").css("background", "AliceBlue");
    return false;
  });
});
