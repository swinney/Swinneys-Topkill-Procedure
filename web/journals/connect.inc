<?
  // Connect to the database

  $conn = @mysql_connect("localhost", "swinney", "XXXXXXXX");
//  $conn = @mysql_connect("sql.dreamhost.com", "aswinney", "XXXXXXXX");

  if ( $conn == false) {
    echo "<font size=6 color=red><b>We are moving to Saturn5.com<br><br>thanks for your patience.</b></font></body></html>";
    exit;
  }
  $DB = "swinney";

?>