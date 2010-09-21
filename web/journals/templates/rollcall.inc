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
# in two thousand.  -austin 
# Thu Jul 12, 2001 10:13 AM
# 
# mmmm...the bitches. - J. 020010921
#
# Dude, this is STILL the most major 
# shitscript of all time.  you people need to
# learn to wipe your ass when you code.
# Mon Feb  4, 2002  3:44 PM, austin.
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

writers:<br>

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->

<?

#########################################
# here is said bad ass select statement
# it gets the distinct pending_articles username
# then the count of articles by said username
# which come to think of it, might be un necessary.
# hm.  comments are good. no no, you cannot get
# the count by username organized without first
# getting the distinct.  i dont think. -austin
# Thu Jul 12, 2001 10:36 AM
#
# this is for limiting the return to only those
# that have posted in the last three months 
# where 3 months= 60 sec * 60 min * 24 hrs * 30 day * 3 mon
# aka    7776000= 60     * 60     * 24     * 30     * 3
#
# wow, all math and shit.  I'm impressed, Austin!  now I will enter
# a smaller random number, because that list is still too fucking 
# long. hm, that didn't seem to change anything.  does this code even
# work? - J. 020010921
#
# i fixed it and turned it back on :)
# - austin Fri Sep 28, 2001 10:49 AM
#

 $minus=time();
 $minus=$minus-7776000;

$query = "SELECT user.username,articles_info.user_id,MAX(articles_info.date) AS date,user_priv.others,IFNULL(user_settings.lj_user,'') as lj_user,IFNULL(user_settings.cn_user,'') cn_user FROM user,articles_info,user_priv,user_settings WHERE DATE_SUB(CURDATE(),INTERVAL 9 MONTH) <= articles_info.date AND user.user_id=articles_info.user_id AND articles_info.user_id=user_priv.user_id AND articles_info.user_id=user_settings.user_id";
//
// Apply the bozo filter
//

if ($bozo_set) {
  $query .= " AND user.user_id NOT IN $bozo_set";
}

$query .= " GROUP BY articles_info.user_id ORDER BY date DESC";

if (ERROR_REP==1) {
    echo $query;
}
echo <<<EOT
<!--
$query
-->
EOT;

$res = $db->query($query);
if (DB::isError($res)) {
    die($res->getMessage());
}

while ($row = $res->fetchRow(DB_FETCHMODE_ASSOC)) {

##########################################
# this cannot be called $username
# without interfearing with the url's
# $username.  so it will be called $user.
# austin, Thu Jul 12, 2001  1:40 PM

    if ($row[username]=="Peter") {
         $row[username]="<TT>Peter</TT>";
    }
    if ($row[others]=="n") {
        $html_rollcall .= "<a href='".URLBASE."/journals/info_user.phtml?uid=$row[user_id]'>".stripslashes($row[username])."</a>";
     } else {
        $html_rollcall .= "<a href='".URLBASE."/journals/info_user.phtml?uid=$row[user_id]'><TT>@</TT>".stripslashes($row[username])."</a>";
      }
    if (!empty($row[lj_user]) && $row[lj_user] != "NULL") {
#        $html_rollcall .= "&raquo;<a href='http://www.swinney.org/journals/lj/user_lj.phtml?uid=$row[user_id]'><B>LJ</B></A>\n";
        $html_rollcall .= "&raquo;<a href='http://www.livejournal.com/users/$row[lj_user]'><B>LJ</B></A>\n";
    }
    if (!empty($row[cn_user])) {
        $html_rollcall .= "&raquo;<a href='http://www.citynoise.org/author/$row[cn_user]'><B>CN</B></A>\n";
    }

$html_rollcall .= "<BR>\n";
}
echo $html_rollcall;
?>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

(<a href="roll_call_all.phtml">a complete list</a>)<br>
</p></td>

<!-- END PHP Dynamically Required File: rollcall.inc -->











