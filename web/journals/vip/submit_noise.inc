<?
/* $Id$
 * noise filter
 */

if (!$authenticated_user_id) {
  $error_msg .= "<P>you dont have an authenticated_user_id.</P>";
} else {
    if ($SUBMIT) {
      $limit_chars = $set_limit_chars;
      $query = <<<EOT
           UPDATE user_settings 
              SET noise_filter=$set_limit_chars 
            WHERE user_id=$authenticated_user_id
EOT;
      $res = $db->query($query);
      if (DB::isError($res)) {
	die($res->getMessage());
      }
    }
}
#unset($limit_chars);
function get_limit_chars() {
  global $db;
  global $authenticated_user_id;
  global $set_limit_chars;
  if (!$authenticated_user_id) {
    $error_msg .= "<P>you dont have an authenticated_user_id.</P>";
  } else {
    $query = "SELECT * FROM user_settings WHERE user_id=$authenticated_user_id";
    $row = $db->getRow($query);
    if (!$authenticated_user_id==$row[0]) {
      $query = "INSERT INTO user_settings (user_id,noise_filter) VALUES ($authenticated_user_id,0)";
      $res=$db->query($query);
      if (DB::isError($res)) {
	die($res->getMessages());
      }
      $row[1]=0;
    }
    unset($row);
  }    
  return $row[1];
}

$html .=<<<EOT
<P><B>$title</B></P>
<P>The noise filter is for <B>comments</B>: ridding your swinney 
experience of those pesky one liner, or those 
pesky two sentencers, or gosh darn it, those 
people who post only three paragraphs!  the nerve.  
</P><P>
You <B>do not</B> want to see posts with <B>less characters than</B>:
</P>
EOT;

if (session_is_registered("limit_chars") && $limit_chars!=0) {
  // debug
} else {
  session_register("limit_chars");
  $limit_chars=get_limit_chars();
}



$html_form .= <<<EOT
<FORM NAME="noise_filter" METHOD=POST ACTION="$PHP_SELF">
EOT;

$set_val = array (
		  "0"=>"i love you, you bastard",
		  "100"=>"omit needless words",
		  "200"=>"i am picky, but i commune with the people",
		  "300"=>"this is the average comment",
		  "400"=>"i am a princess",
		  "500"=>"i believe in free speech used wisely",
		  "1000"=>"this better be important",
		  "2000"=>"i love words",
		  "3000"=>"long live the bard!",
		  "1000000"=>"it will be a cold day in hell when i mix with you people",
		  );

foreach ($set_val as $key=>$val) {
  $html_form .= "<INPUT TYPE=RADIO NAME=set_limit_chars VALUE=$key"; 
  if ($key==$limit_chars) {
    $html_form .= " CHECKED";
  }
  $html_form .="> ($key) <i>$val</i><BR>\n";
}

$html_form .=<<<EOT
<INPUT TYPE=SUBMIT NAME=SUBMIT VALUE="Set your noise filter">
</FORM>
EOT;

echo $html;
echo $html_form;
?>

