    ._____LessthannetzeroenGhetto Internet Excess and Email______.
    |  Download Now           -->       http://www.swinney.org  |
    |  Request a CDROM           -->       request@swinney.org  |
    |___________________________________________________________|
       $Id$

 Welcome to the world of Swinney.org's Code, affectionately known as

		       "Swinney.org Loves You"!


Updating Swinney.org Live Site

All of swinney.org code resides in the directory
(/sky/www/swinney.org/html/) on atari.saturn5.com.  When exporting the CVS
 module to swinney.org, use the -d option to specify that directory. With
($CVSROOT=/cvsroot/swinney.org/) run the command: 

cvs export -d /sky/www/swinney.org/html/ swinney.org

The suggested method of updating Swinney.org for one or two files is
to just copy or scp them over the previous live copy.  That suffices
for making it live.  Be certain the update works first.  This better
than exporting because other developers may have some features they
are modifying or creating that are not at 'roll-out' point yet.  

The only time exports happen of the entire site is when there are
massive layout changes, or changes in the database/structure of the
site that change files all over.  If this is the case, then all
develpment will have to be at a roll-out point or excluded from the
update.  Preference is given to bringing everything to a working
version and then bestowing a releasetag on the Site for quick
rollbacks.
