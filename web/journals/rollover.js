
function rollover(label,inactive,active,status)
{
	this.rollokay   = testbrowser();
	this.imagelabel   = label;
	this.statusline = status;
	this.active   = false;

	if( this.rollokay )
	{
		this.activeimage         = new Image();
		this.activeimage.src     = active;
		this.inactiveimage       = new Image();
		this.inactiveimage.src   = inactive;
	}
	
	this.mouseOver = activerollover;
	this.mouseOut  = inactiverollover;
}

function activerollover()
{
	if ( this.rollokay && !this.isSelected )
	{
		document.images[this.imagelabel].src = this.activeimage.src;
	}
	this.active = true
	window.status = this.statusline;
}

function inactiverollover()
	{
		if ( this.rollokay )
		{
			if( !this.isSelected ) {document.images[this.imagelabel].src = this.inactiveimage.src;}
		}
		this.active = false
		window.status = '';
	}

function testbrowser()
{
	if (navigator.appName == "Microsoft Internet Explorer")
	{
		if(parseInt(navigator.appVersion) >= 4)
		{
			return( 1 );
    } 
    else 
    {
			return( 0 );
		}
	} 
	else if (navigator.appName == "Netscape") 
	{
		if(parseInt(navigator.appVersion) >= 3) 
		{
			return( 1 );
		} 
		else 
		{
			return( 0 );
		}
	}
}

NS = IE = false;

if ((navigator.appName == "Microsoft Internet Explorer") && (navigator.userAgent.indexOf("Mac")==-1))
IE = true;
else
NS = true;