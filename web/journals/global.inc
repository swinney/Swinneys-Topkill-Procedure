<?
  // global.inc
  //  functions for use in the site


  // Connect to the database

function conn() {
mysql_connect("localhost","root","maufrais");
mysql_select_db("srtech");
}


  $conn = mysql_connect("localhost", "swinney", "XXXXXXXX");

  if ( $conn == false) {
    echo "<font size=6 color=red><b>We are moving to Saturn5.com<br><br>thanks for your patience.</b></font></body></html>";
    exit;
  }
  $DB = "swinney";

// This generates a number using a set of dice, like 1d6, or 5d2
  Function dice( $number, $value ) {
    $total = 0;
    for ( $i = 0 ; $i < $number ; $i++ ) {
      srand((double)microtime()*1000000);
      $total += rand(1, $value);
    }
    return $total;
  }

// this thing dont work yet.  i never done a fucktion 
function check_web($web,$username) {

  if ($web != "") {
    $username="<a href='".$web."'> ".stripslashes($username)."</a>";
  }

  if ($web == "") {
    echo "$username ";
  }

}
?>