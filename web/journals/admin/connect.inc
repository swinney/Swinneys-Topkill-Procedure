<?
  // Connect to the database

  $conn = @mysql_connect("sql.dreamhost.com", "aswinney", "XXXXXXXX");
  if ( $conn == false) {
    echo "<font size=6 color=white><b>ERROR, yo!  Textocal IS DOWN!  browse the <a href='http://swinney.org/journalx/'>archives</a> and we'll be back.</b></font></body></html>";
    mail("Textocal is Down!!!!", "Textocal DB IS DOWN!!!", " db@swinney.org");
    exit;
  }
  $DB = "textocal";

?>