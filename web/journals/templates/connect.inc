<?
  // Connect to the database
  $conn = mysql_pconnect("sql.dreamhost.com", "aswinney", "XXXXXXXX");
  if ( $conn == false ) {
    echo "<font size=6 color=red><b>ERROR!  STATS DB IS DOWN!</b></font>";
    mail("TEXTOCAL DB IS DOWN!!!!", "TEXTOCAL DB IS DOWN!!!", "db@swinney.org");
    exit;
  }
  $DB = "textocal";
?>