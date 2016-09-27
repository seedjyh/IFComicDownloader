function unsuan(s,sk) 
{
	sw="hhmanhua.net|huhumh.com|hhmanhua.cc|huhudm.com";
	su = location.hostname.toLowerCase();
	b=false;
	for(i=0;i<sw.split("|").length;i++) {
	    if(su.indexOf(sw.split("|")[i])>-1) {
	        b=true;
	        break;
        }
    }
    if(!b)return "";
	k=sk.substring(0,sk.length-1);
	f=sk.substring(sk.length-1);
	for(i=0;i<k.length;i++) {
	    eval("s=s.replace(/"+ k.substring(i,i+1) +"/g,'"+ i +"')");
	}
    ss = s.split(f);
	s="";
	for(i=0;i<ss.length;i++) {
	    s+=String.fromCharCode(ss[i]);
    }
    return s;
}

var s1='http://www.1hanhan.com/comic/';
var s2='http://www.hhcool.com/comic/';

var ServerList=new Array(16);
ServerList[0]="http://104.237.56.99:9393/dm01/";
ServerList[1]="http://104.237.56.98:9393/dm02/";
ServerList[2]="http://104.237.56.98:9393/dm03/";
ServerList[3]="http://104.237.56.99:9393/dm04/";
ServerList[4]="http://104.237.56.98:9393/dm05/";
ServerList[5]="http://104.237.56.99:9393/dm06/";
ServerList[6]="http://104.237.56.98:9393/dm07/";
ServerList[7]="http://104.237.56.99:9393/dm08/";
ServerList[8]="http://104.237.56.98:9393/dm09/";
ServerList[9]="http://104.237.56.98:9393/dm10/";
ServerList[10]="http://104.237.56.99:9393/dm11/";
ServerList[11]="http://104.237.56.99:9393/dm12/";
ServerList[12]="http://104.237.56.99:9393/dm13/";
ServerList[13]="http://8.8.8.8:99/dm14/";
ServerList[14]="http://104.237.56.99:9393/dm15/";
ServerList[15]="http://104.237.56.99:9393/dm16/";

var page = 1;
var server = 1;
var pagea=Request("v")
var servera=Request("s")
if (pagea!="")
{
   page=pagea;
}
if (servera!="")
{
   server=servera;
}


var picurl="";
var picurl1="";

var cuImg;
PicListUrl=unsuan(PicListUrl,"tazsicoewrn");
var arrPicListUrl = PicListUrl.split('|');
var datas = arrPicListUrl.length;

for(i=0;i<datas;i++)
{
    if(i+1 ==page)
    {
        picurl = arrPicListUrl[i];
        if(i+1 < datas)
            picurl1 = arrPicListUrl[i+1];
    }
}


function Request(strName)
{
	var strHref = window.document.location.href;
	var intPos = strHref.indexOf("?");
	var strRight = strHref.substr(intPos + 1);

	var arrTmp = strRight.split("*");
	for(var i = 0; i < arrTmp.length; i++)
	{
		var arrTemp = arrTmp[i].split("=");

		if(arrTemp[0].toUpperCase() == strName.toUpperCase()) return arrTemp[1];
	}
	return "";
}

function showpic(v)
{	
	var nl = '?v='+v+"*s="+server;
	//alert (nl);
	window.location = nl;
}

function lomPic()
{
	document.getElementById("ComicPic").src = ServerList[server-1]+picurl;
 
}

function ch_sel(v)
{
    try
    {
	    document.all.select1.value = v;
	    document.all.select2.value = v;
	}
	catch(err)
	{
	   document.getElementsByName("select1")[0].value  = v;
	   document.getElementsByName("select2")[0].value  = v;
	}
	
	
    var BaseUrl="http://www.hhmanhua.com";
    
	//ComicPic.src=ServerList[server-1]+picurl;
    //ComicPic1.src=ServerList[server-1]+picurl1;
	document.getElementById("ComicPic1").src = ServerList[server-1]+picurl1;
	
    cuImg = document.getElementById("ComicPic");
	cuImg.style.cursor = "hand";
    //var evt = window.event;
    cuImg.onmousedown = function(evt){drag(evt);};
    

}

function get_sel(v)
{
    
	if (v == 0)
	{
		//document.write
		var i,outstr = "";
		for (i=1;i<=datas;i++)
		{
			outstr += "<option value='"+ i +"'>第"+ i +"页</option>";
		}
		document.write(outstr);
	}
	else
	{
		if ((v > 0) && (v < datas+1))
		{
			page = v;
			showpic(v);
			ch_sel(v);
		}
	}
}

function prevpage()
{
	page--;
	if (page <1)
	{
		alert('前面还有吗？我都不知道！');
		page = 1;
	}
	else
	{
		//alert(page);
		ch_sel(page);
		showpic(page);
	}
}

function nextpage()
{
	page++;
	//alert (page);
	if (page > datas )
	{
		alert('最后一页了!PS告诉你更多的朋友，本站提供免费在线漫画!\n\n新推出高速服务器 www.huhumh.com 更快更爽的看漫画');
               //var url = "/jsc/huhu.html";
x=500;
y=333;
window.showModalDialog(url,null,"dialogHeight:"+y+"px;dialogWidth:"+x+"px;scroll:no;status:no;help:no;resizable:yes");

		page = datas-1;
	}
	else
	{
		//alert(page);
		ch_sel(page);
		showpic(page);
	}
}

 
function nocontextmenu() 
{
 event.cancelBubble = true
 event.returnValue = false;
 
 return false;
}
 
function norightclick(e) 
{
 if (window.Event) 
 {
  if (e.which == 2 || e.which == 3)
   return false;
 }
 else
  if (event.button == 2 || event.button == 3)
  {
   event.cancelBubble = true
   event.returnValue = false;
   return false;
  }
 
}



function drag(evt) 
{
	evt = evt || window.event;
	if (document.all && evt.button != 1) {
		return false;
	}
		
	oX = 2 * document.documentElement.scrollLeft;
	cX = document.documentElement.scrollLeft - evt.screenX;
	oY = 2 * document.documentElement.scrollTop;
	cY = document.documentElement.scrollTop - evt.screenY;	
	if (cuImg.addEventListener) {
		cuImg.addEventListener("mousemove", moveHandler, true);
		cuImg.addEventListener("mouseup", upHandler, true);
	} else if (cuImg.attachEvent) {
		cuImg.setCapture( );
		cuImg.attachEvent("onmousemove", moveHandler);
		cuImg.attachEvent("onmouseup", upHandler);
		cuImg.attachEvent("onlosecapture", upHandler);
	} else {
		var oldmovehandler = cuImg.onmousemove;
		var olduphandler = cuImg.onmouseup;
		cuImg.onmousemove = moveHandler;
		cuImg.onmouseup = upHandler;
	}	
	if (evt.stopPropagation) evt.stopPropagation( );
	else evt.cancelBubble = true;	
	if (evt.preventDefault) evt.preventDefault( );
	else evt.returnValue = false;	
	if (evt.stopPropagation) evt.stopPropagation( );
	else evt.cancelBubble = true;	
	cuImg.style.cursor = "move";	
	function moveHandler(evt) {
		mX = evt.screenX + cX;
		mY = evt.screenY + cY;
		window.scrollTo(oX - mX, oY - mY);		
		if (evt.stopPropagation) evt.stopPropagation( );
		else evt.cancelBubble = true;
	}	
	function upHandler(evt) {
		cuImg.style.cursor = "pointer";		
		if (cuImg.removeEventListener) {
			cuImg.removeEventListener("mouseup", upHandler, true);

			cuImg.removeEventListener("mousemove", moveHandler, true);
		} else if (cuImg.detachEvent) {
			cuImg.detachEvent("onlosecapture", upHandler);
			cuImg.detachEvent("onmouseup", upHandler);
			cuImg.detachEvent("onmousemove", moveHandler);
			cuImg.releaseCapture( );
		} else {
			cuImg.onmouseup = olduphandler;
			cuImg.onmousemove = oldmovehandler;
		}
		if (evt.stopPropagation) evt.stopPropagation( );
		else evt.cancelBubble = true;
	}
}

function engage99()
{
	chgCursor(2);
	status99 = 1;
	oX99 = 2 * document.body.scrollLeft;
	cX99 = document.body.scrollLeft - window.event.screenX;
	oY99 = 2 * document.body.scrollTop;
	cY99 = document.body.scrollTop - window.event.screenY;		
	return false;
}

function release99()
{
	chgCursor(1);
	status99 = 0;
	return false;
}

function chgCursor(url)
{
	switch (url)
	{
		case 1: 
		{ 
			document.getElementById("comicpic").style.cursor = handICON;
			break;
		}
		case 2:
		{
			document.getElementById("comicpic").style.cursor = movICON;
			break;
		}
		default :
		{
			document.getElementById("comicpic").style.cursor = handICON;
			break;
		}
	}
}


document.oncontextmenu=new Function('event.returnValue=false;');
document.onselectstart=new Function('event.returnValue=false;');
