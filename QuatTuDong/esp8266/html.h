const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Remote</title>
</head>
<body>
  <div>
    Nhiệt độ: <span id= "nhietdos">0</span>C<br>
  </div>

  <script>
    setInterval(function() { 
      getnhietdo();
    }, 1000);

    function getnhietdo() {
      var xhttp= new XMLHttpRequest();
      xhttp.onreadystatechange= function() {
        if( this.readyState== 4 && this.status== 200) {
          document.getElementById( "nhietdos").innerHTML= this.responseText;
        }
      };
      xhttp.open( "Get", "docnhietdo", true);
      xhttp.send();
    }
  </script>
  
</body>
</html>
)=====";
