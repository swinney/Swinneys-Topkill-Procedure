<?
// user login page
// user_login.inc
?>

<!-- USER LOGIN AREA -->

<FORM ACTION="process_login.phtml" METHOD="post">
<INPUT TYPE="text" NAME="username" value="<? echo "$username"; ?>" SIZE=10 MAXLENGTH=20>
<BR>
<INPUT TYPE="password" NAME="password" value="<? echo "$password"; ?>" SIZE=10 MAXLENGTH=20>
<BR>
<INPUT TYPE="submit" VALUE="that's me">
</FORM>

<!-- END USER LOGIN AREA -->


