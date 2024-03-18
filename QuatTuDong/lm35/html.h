const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <title>Remote</title>
  <
</head>
<body>
  <div>Nhiệt độ: <span class="nhietdo">0</span> độ C<br></div>
  <script>
    setInterval( funtion() { // thực hiện hàm getnhietdo mỗi 1s một lần
      getnhietdo();
    }, 1000);

    function getnhietdo() {
      var xhttp= new XMLHttpRequest();
      xhttp.onreadystatechange= function() {
        if( this.readyState== 4 && this.status== 200) {
          document.getElementById( "nhietdo").innerHTML= this.responseText;
        }
      };
      xhttp.open( "GET", "docnhietdo", true);
      xhttp.send();
    }
  </script>
</body>
</html>
)=====";
