<?
////////////////////////////////
// $Id$
// converting binary form
require_once('./global.inc');
if (isset($num)) {
  $bin=bin($bit,$num);
  echo "<P><TT>base10: $num</TT><BR>\n";
  echo    "<TT>binary: $bin</TT></P>\n";
}
?>


<FORM NAME="bin_converter" ACTION="<? echo $PHP_SELF; ?>" METHOD="POST">
<TABLE><TR><TD>
<INPUT TYPE="radio" NAME="bit" VALUE=8>8 bit
</TD><TD>
<INPUT TYPE="radio" NAME="bit" VALUE=16>16 bit
</TD><TD>
<INPUT TYPE="radio" NAME="bit" VALUE=24>24 bit
</TD><TD>
<INPUT TYPE="radio" NAME="bit" VALUE=32>32 bit
</TD><TD>
<INPUT TYPE="radio" NAME="bit" VALUE=64>64 bit
</TD></TR>
</TABLE>
<INPUT TYPE="TEXT" NAME=num COLS=30>
<INPUT TYPE="SUBMIT" NAME="submit" VALUE="convert">
</FORM>
