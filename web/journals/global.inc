<?
#########################################################
# $Id$
# global.inc
# global vars for use in the site
# functions for use in the site



##########################################################
#################  FUNCTION LIST #########################
# here are some functions for the site.  they do different
# things but are mostly here because functions are a
# little easier to deal with than includes because of
# the centralization.  sometimes the files global.inc
# becomes bloated in size, but it has to be pretty big to
# notice.
# austin
##########################################################

###################################
# conn() - database connection,
# returns error if db is down.
# austin, Mon Jul 23, 2001  9:50 PM

Function conn()

{       
        
        $conn=@mysql_connect("localhost", "swinney", "XXXXXXXX");
        @mysql_select_db("swindev");
 
        if ( $conn == false)

        {       
                
                echo "<font size=6 color=red><b>We are moving to Saturn5.com<br>";
                echo "<br>thanks for your patience.</b></font></body></html>";
                exit;

        }


}



###################################
# dice() - This generates a
# number using a set of dice,
# like 1d6, or 5d2
# austin, Mon Jul 23, 2001  9:50 PM

Function dice( $number, $value )

{       
        
        $total = 0;


        for ( $i = 0 ; $i < $number ; $i++ ) {
                
                srand((double)microtime()*1000000);
                $total += rand(1, $value);

        }
        
        return $total;

}




###################################
# check_web() - evaluates $web
# this thing dont work yet.
# austin, Mon Jul 23, 2001  9:50 PM  

function check_web($web,$username) 

{

	if ($web != "") 

	{

		$username="<a href='".$web."'> ".stripslashes($username)."</a>";
	}


	if ($web == "") 

	{


		echo "$username ";
	}

}
?>