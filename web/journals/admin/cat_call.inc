<?
#$Id$

###################################
# rollcall.inc - who is out there?
# this is the most major shit script
# in all of swinney.org.  UNTIL TODAY
# i just figured out how to generate the
# entire thing in one select statement.
# worship me.  suck my dick.  it does not matter
# i do this all for the bitches.  word up 
# in two thousand.  -OMS 
# Thu Jul 12, 2001 10:13 AM
#
# mmmm...the bitches. - J. 020010921

?>

<!-- BEGIN PHP Dynamically Required File: rollcall.inc -->


<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
<td align="center">

<img src="img/no.gif" alt="" width="1" height="10" border="0"><br>

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td width="150" valign="top" align="right" nowrap>
<p>
<a href="roll_call_all.phtml"><img src="<? echo URLBASE ?>/journals/img/rollcall.gif" alt="Roll Call" width="65" height="13" border="0"></a><br>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

shelved as:<br>

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->
<?
$query="SELECT category FROM articles_info WHERE article_id=$article_id";
$res=mysql_query($query) or die (error_page($query));
$article_bin=mysql_result($res,0,0);
$query=<<<EOT
SELECT level1 as cat_bin,name,level1&$article_bin as sexy 
FROM categories 
WHERE name<>'' 
ORDER BY name ASC
EOT;

$res=mysql_query($query);
$i=0;
while ($d=mysql_fetch_object($res)) {
    $cat_bin=$d->cat_bin;
    $name=$d->name;
    $sexy=$d->sexy;
    $base="\n$name<INPUT TYPE='checkbox' NAME='cat[$i]' VALUE='$cat_bin' ";
    if ($sexy!=0) {
        $html = $html . $base . " CHECKED><BR>\n"; // oh you are so SEXY!!!
    } else {
        $html = $html . $base . "><BR>\n"; // oh you are NOT so sexy!!!
    }
    $i++;
}
echo $html;



?>
<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>
</p></td>

<!-- END PHP Dynamically Required File: rollcall.inc -->












