var maxTumb = 4;
var roiList = [];
var numRoiList = 0;
var currentRoi = -1;

function initRoiList(roi) {

roiList[roi] = {
	title:null,
	description:null,
	view:{x:0, y:0, z:0, s:0},
	pMin:{x:0, y:0, z:0},
	pMax:{x:0, y:0, z:0},
	nameImages:[],
	numImages:0,
	nameVideo:null,
	left:0,
	right:maxTumb-1,
	sbar:'roi' + roi +'-sbar',
	winDescription:'roi' + roi + '-win-description',
	winImage:'roi'+ roi + '-win-image',
	winVideo:'roi'+ roi + '-win-video',
	mainImage:'roi' + roi + '-main-image',
	enableDescription: false,
	enableImage: false,
	enableVideo: false
};
	
}

function nl2br(s) { return s.split(/\r?\n/).join("<br>"); }

function createPresentation(xml) {
	
var xmlDoc = xml.responseXML;
var roi = xmlDoc.getElementsByTagName("roi");

var i, j;
for (i=0; i<roi.length; i++) { 
	if (roi[i].childNodes) {
		
		initRoiList(i);
			
		var id = parseInt(roi[i].getAttribute("id"));
		
		var title = roi[i].getElementsByTagName("title")[0];
		roiList[i].title = title.childNodes[0].nodeValue;
		addTitleBar(i);
		
		var description = roi[i].getElementsByTagName("description")[0];
		if (description.childNodes.length > 0) {
			roiList[i].description = nl2br(description.childNodes[0].nodeValue);
			roiList[i].enableDescription = true;
			createWinText(i);
		}
		
		var view = roi[i].getElementsByTagName("view")[0];
		roiList[i].view.x = parseFloat(view.getAttribute("x"));
		roiList[i].view.y = parseFloat(view.getAttribute("y"));
		roiList[i].view.z = parseFloat(view.getAttribute("z"));
		roiList[i].view.s = parseFloat(view.getAttribute("s"));
		
		if (id != 0) {
			var min = roi[i].getElementsByTagName("pMin")[0];
			roiList[i].pMin.x = parseFloat(min.getAttribute("x"));
			roiList[i].pMin.y = parseFloat(min.getAttribute("y"));
			roiList[i].pMin.z = parseFloat(min.getAttribute("z"));
		
			var max = roi[i].getElementsByTagName("pMax")[0];
			roiList[i].pMax.x = parseFloat(max.getAttribute("x"));
			roiList[i].pMax.y = parseFloat(max.getAttribute("y"));
			roiList[i].pMax.z = parseFloat(max.getAttribute("z"));
		}
			
		var images = roi[i].getElementsByTagName("images")[0];
		if (images.childNodes.length > 0) {
			for (j=0; j<images.childElementCount; j++) { 
				var image = images.getElementsByTagName("image")[j];
				roiList[i].nameImages[j] = image.childNodes[0].nodeValue;
			}
			roiList[i].numImages = j;
			roiList[i].enableImage = true;
			createWinImage(i);
		}
		var video = roi[i].getElementsByTagName("video")[0];
		if (video.childNodes.length > 0) {
			roiList[i].nameVideo = video.childNodes[0].nodeValue;
			roiList[i].enableVideo = true;
			createWinVideo(i);
		}
		
		numRoiList++;
	}
}

}

function loadPresentation() {

var xhr;
xhr = new XMLHttpRequest();
xhr.onreadystatechange = function() {
	if (xhr.readyState == 4 && xhr.status == 200) {
	   createPresentation(xhr);
	   displayScreen();
	}
};

xhr.open("GET", path + "file.xml", true);
xhr.send();	
}

function addTitleBar(r) {

var roi = r;
var li = document.createElement("li");

if (roi == 0) {
	li.className = 'sidebar-main';
}
li.innerHTML = roiList[roi].title;
li.id = roiList[roi].sbar;
li.onclick = function(){ displayRoi(roi); };

var titleBar = document.getElementById("sBar");
titleBar.appendChild(li);
}

function createWinText(r) {
	
var roi = r;

var win = document.createElement("div");
win.className = 'drag-window-text';
win.id = roiList[roi].winDescription;
win.style.left = window.innerWidth-400-5; // window width
win.style.top = 270+10; // window height

var bar = document.createElement("div");
bar.className = 'title-bar';
bar.onmousedown = function () { initDrag(win); return false;}

var title = document.createElement("h1");
title.innerHTML = roiList[roi].title;
bar.appendChild(title);

var close = document.createElement("div");
close.className = 'close-button';
close.onclick = function () { win.style.display = 'none';}
bar.appendChild(close);

var text = document.createElement("div");
text.className = 'content';
text.innerHTML = roiList[roi].description;

win.appendChild(bar);
win.appendChild(text);

document.body.appendChild(win);
}

function capture(src){
var canvas2D = document.createElement("canvas");
var video = document.createElement("video");
video.src = src;
canvas2D.getContext('2d').drawImage(video, 0, 0, video.videoWidth, video.videoHeight);
return canvas2D.toDataURL();
}

function createWinVideo(r) {
	
var roi = r;

var win = document.createElement("div");
win.className = 'drag-window-video';
win.id = roiList[roi].winVideo;
win.style.left = window.innerWidth-400-5 +60;
win.style.top = 270+10 +55;

var bar = document.createElement("div");
bar.className = 'title-bar';
bar.onmousedown = function () { initDrag(win); return false;}

var title = document.createElement("h1");
title.innerHTML = roiList[roi].title;
bar.appendChild(title);

var close = document.createElement("div");
close.className = 'close-button';
close.onclick = function () { win.style.display = 'none';}
bar.appendChild(close);

win.appendChild(bar);

var content = document.createElement("div");
content.className = 'content';

var mainVideo = document.createElement("div");
mainVideo.className = 'main-video';

var video = document.createElement("video");
video.controls = true;
video.src = path + roiList[roi].nameVideo;

mainVideo.appendChild(video);
content.appendChild(mainVideo);

win.appendChild(content);
document.body.appendChild(win);
}
	
function createWinImage(r) {
	
var roi = r;

var win = document.createElement("div");
win.className = 'drag-window-image';
win.id = roiList[roi].winImage;
win.style.left = window.innerWidth-400-5; // window width
win.style.top = 5;

var bar = document.createElement("div");
bar.className = 'title-bar';
bar.onmousedown = function () { initDrag(win); return false;}

var title = document.createElement("h1");
title.innerHTML = roiList[roi].title;
bar.appendChild(title);

var close = document.createElement("div");
close.className = 'close-button';
close.onclick = function () { win.style.display = 'none';}
bar.appendChild(close);

win.appendChild(bar);

var content = document.createElement("div");
content.className = 'content';

var img = document.createElement("div");
img.className = 'main-image';
img.id = roiList[roi].mainImage;
img.style.backgroundImage = 'url('+ path + roiList[roi].nameImages[0] + ')';
content.appendChild(img);

var table = document.createElement("table");
var row = table.insertRow(0);

/*carousel*/
var pt = 0;
var cell = row.insertCell(pt);
var left = document.createElement("div");
left.className = 'left-button';
left.style.float = 'left';
left.onclick = function(){ moveLeft(roi); };

if (roiList[roi].numImages <= 4)
	left.style.visibility = 'hidden';

cell.appendChild(left);
pt++;

for (var i=0; i<roiList[roi].numImages; i++, pt++) {
	
	var cell = row.insertCell(pt);
	var tumb = document.createElement("div");
	tumb.className = 'tumb-image';
	tumb.id = 'roi' + roi + '-tumb' + i;
	tumb.style.backgroundImage = 'url(' + path + roiList[roi].nameImages[i] + ')';
	tumb.onclick = function(){ displayImage(this, roi); };
	
	if (i >= maxTumb)
		tumb.style.display = 'none'; 
	
	cell.appendChild(tumb);
}

var cell = row.insertCell(pt);
var right = document.createElement("div");
right.className = 'right-button';
right.style.float = 'right';
right.onclick = function(){ moveRight(roi); };

if (roiList[roi].numImages <= 4)
	right.style.visibility = 'hidden';

cell.appendChild(right);

content.appendChild(table);

win.appendChild(content);
document.body.appendChild(win);
}

function displayImage(tumb, roi) {
var img = document.getElementById(roiList[roi].mainImage);
var url = tumb.style.backgroundImage;
img.style.backgroundImage = url;
}

function moveLeft(roi) {

if (roiList[roi].left >= 1) {
	var id = 'roi' + roi + '-tumb';
	document.getElementById(id+roiList[roi].right).style.display = 'none';
	roiList[roi].right = roiList[roi].right - 1;
	roiList[roi].left = roiList[roi].left - 1;
	document.getElementById(id+roiList[roi].left).style.display = 'block';
}
	
}

function moveRight(roi) {

if (roiList[roi].right < roiList[roi].numImages-1) {
	var id = 'roi' + roi + '-tumb'
	document.getElementById(id+roiList[roi].left).style.display = 'none';
	roiList[roi].left = roiList[roi].left + 1;
	roiList[roi].right = roiList[roi].right + 1;
	document.getElementById(id+roiList[roi].right).style.display = 'block';
}
	
}

function closeRoi(roi) {

if (roiList[roi].enableDescription)
	document.getElementById(roiList[roi].winDescription).style.display = 'none';
			
if (roiList[roi].enableImage)
	document.getElementById(roiList[roi].winImage).style.display = 'none';
	
if (roiList[roi].enableVideo)
	document.getElementById(roiList[roi].winVideo).style.display = 'none';
		
document.getElementById(roiList[roi].sbar).style.backgroundColor = '#2a88e0';
}

function openRoi(roi) {

if (roiList[roi].enableDescription)
	document.getElementById(roiList[roi].winDescription).style.display = 'block';
	
if (roiList[roi].enableImage)
	document.getElementById(roiList[roi].winImage).style.display = 'block';
	
if (roiList[roi].enableVideo)
	document.getElementById(roiList[roi].winVideo).style.display = 'block';
		
document.getElementById(roiList[roi].sbar).style.backgroundColor = '#333333';
}

function displayRoi(roi){

if (currentRoi >= 0) {
	closeRoi(currentRoi);
}
openRoi(roi);
currentRoi = roi;

//move to view
if (slerp.status == false) {
	slerp.t = 0.0;
	dest.x = roiList[roi].view.x;
	dest.y = roiList[roi].view.y;
	dest.z = roiList[roi].view.z;
	dest.s = roiList[roi].view.s;
	slerp.status = true;
}

//show colored roi
show = 0;
if (roi > 0) {
	bb.min.x = round(roiList[roi].pMin.x);
	bb.min.y = round(roiList[roi].pMin.y);
	bb.min.z = round(roiList[roi].pMin.z);
	
	bb.max.x = round(roiList[roi].pMax.x);
	bb.max.y = round(roiList[roi].pMax.y);
	bb.max.z = round(roiList[roi].pMax.z);
	
	show = 1;
	blink.start = new Date().getTime();
	blink.status = 1;
}
}

var slerp = {
	status:false,
	t:0.0,
	/*dest:{x:0, y:0, z:0, s: 1}*/
};

function showView() {

if (blink.status == 1) {
	var now =  new Date().getTime();
	var elapsed = now - blink.start;
	if (elapsed > 300 && elapsed < 600)
		show = 0;
	else if (elapsed > 600 && elapsed < 900)
		show = 1;
	else if (elapsed > 900 && elapsed < 1200)
		show = 0;
	else if (elapsed > 1200 && elapsed < 1500)
		show = 1;
	else if (elapsed > 1500) {
		show = 0;
		blink.status = 0;
	}
	
}

if (slerp.status == false)
	return;
		
interpolation(slerp.t);
slerp.t = slerp.t + 0.01;
if (slerp.t >= 1.01) {
	slerp.status = false;
}
}

var bb = {
	max:{x:0, y:0, z:0}, 
	min:{x:0, y:0, z:0}
};

function round(value) {
if (value < 0.0) {return (value - 0.1);}
	return (value + 0.1);
}

/* ---------------------------------- Draggwable window ---------------------------------- */
var dragw = {
	selected: null,
	offsetX: 0,
	offsetY: 0,
	startX: 0,
	startY: 0
};

function initDrag(elem) {
dragw.selected = elem;
dragw.startX = window.event.clientX;
dragw.startY = window.event.clientY;
dragw.offsetX = dragw.selected.offsetLeft;
dragw.offsetY = dragw.selected.offsetTop;
}

function moveWindow(e) {

if (dragw.selected !== null) {
	dragw.selected.style.left = (dragw.offsetX + e.clientX - dragw.startX) + 'px'; 
	dragw.selected.style.top =  (dragw.offsetY + e.clientY - dragw.startY) + 'px';
}
}

function releaseWindow() {
dragw.selected = null;
}

document.onmousemove = moveWindow;
document.onmouseup = releaseWindow;
