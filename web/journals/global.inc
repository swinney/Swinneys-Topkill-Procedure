<?
  // global.inc
  //  functions for use in the site


  // Connect to the database

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

// who do you like?

$USERS = "
username='austin' OR 
username='s5' OR 
username='le' OR 
username='egg' OR
username='bmg'
";
?>










