
var roiList = new Array;
var ptRoiList = 0;

function initRoiList() {

roiList[0] = {
	li: 'root-li',
	inputTitle: 'root-title',
	inputDescription: 'root-description',
	inputImage: 'root-image',
	panel: [0,0,0],
	edit: false,
	title: mesh.print,
	view: {x:mesh.view.x, y:mesh.view.y, z:mesh.view.z, s:mesh.view.s},
	pMin: 0,
	pMax: 0,
	description: null,
	nameImages:[],
	imageList:[],
	ptImageList: 0,
	video: {status:0, file:null, name:""}
};
ptRoiList = 1;

}

function attRoiList() {
	var roilisthtml = document.getElementById('roilist');
	while (roilisthtml.firstChild) {
		roilisthtml.removeChild(roilisthtml.firstChild);
	}	
	for(var i = 0; i < roiList.length; i++) {
		var item = roiList[i];
		var listitem = document.createElement('div');
		listitem.className = "roip";
		(function(i) {
			listitem.onclick = function() {
				editMultimedia(i);		
			}
		})(i, listitem);
		var span = document.createElement('span');	
		span.innerHTML = item.title;	
		listitem.appendChild(span);
		roilisthtml.appendChild(listitem)		
	};
}

function addRoiList() {

var id = 'roi' + ptRoiList;
roiList[ptRoiList] = {
	li: id +'-li',
	inputTitle: id + '-title',
	inputDescription: id + '-description',
	inputImage: id + '-image',
	panel: [0,0,0],
	edit: false,
	title: null,
	view: {
		x:rot.x, 
		y:rot.y, 
		z:rot.z, 
		s:rot.s
	},
	pMin: {
		x:pMin[0], 
		y:pMin[1], 
		z:pMin[2]
	},
	pMax: {
		x:pMax[0], 
		y:pMax[1],
		z:pMax[2]
	},
	description: null,
	nameImages:[],
	imageList:[],
	ptImageList: 0,
	video: {status:0, file:null, name:""}
};
//ptRoiList++;

}

function salvarROI() {
	var roi = roiList[edition.current];	
	roi.title = document.getElementById("titleROI").value;	
	roi.description = document.getElementById("root-description").value;	
	//save();	
closePopup();
attRoiList();
}

function fillRoiList() {

var i, j, k;
for (i=0; i<ptRoiList; i++) {
	
	if (roiList[i] != null) {	
	
		if (i==0) {
			roiList[i].title = document.getElementById(roiList[i].li).textContent;
		}
		else {
			roiList[i].title = document.getElementById(roiList[i].inputTitle).value;
		}
		
		roiList[i].description = document.getElementById(roiList[i].inputDescription).value;
	
		k = 0;
		for (j=0; j<roiList[i].ptImageList; j++) {
			if (roiList[i].imageList[j].status == 1) {
				roiList[i].nameImages[k] = 'roi' + i + '-image' + k + '.' + (roiList[i].imageList[j].file).type.split('/').pop();
				k++;
			}
		}
		
		if (roiList[i].video.status == 1) {
			roiList[i].video.name = 'roi' + i + '-video.mp4';
		}
	}
}

}

function sendPresentation() {
		
var presentation = {index:0, roi:[]};

var pt = 0;
for (var i=0; i<ptRoiList; i++) {
	
	if (roiList[i] != null) {
		
		presentation.roi[pt] = {
		title: roiList[i].title,
		view: {
			x:'' + roiList[i].view.x, 
			y:'' + roiList[i].view.y, 
			z:'' + roiList[i].view.z, 
			s:'' + roiList[i].view.s
		},
		pMin: {
			x:'' + roiList[i].pMin.x,
			y:'' + roiList[i].pMin.y,
			z:'' + roiList[i].pMin.z
		},
		pMax: {
			x:'' + roiList[i].pMax.x,
			y:'' + roiList[i].pMax.y,
			z:'' + roiList[i].pMax.z
		},
		description: roiList[i].description,
		images:		 roiList[i].nameImages,
		video:		 roiList[i].video.name
		};
		
		pt++;
	}
}

var form = "presentation="+ JSON.stringify(presentation);

var xhr = new XMLHttpRequest();
xhr.open("post", "WriteXMLPresentation", false);
xhr.setRequestHeader("Content-type","application/x-www-form-urlencoded");
xhr.send(form);
}

function sendFiles() {
	
var form = new FormData();

var i, j;
for (i=0; i<ptRoiList; i++) {
	
	if (roiList[i] != null) {
		
		for (j=0; j<roiList[i].ptImageList; j++) {
			if (roiList[i].imageList[j].status == 1) {
				form.append("file", roiList[i].imageList[j].file);
			}
		}
	
		if (roiList[i].video.status == 1) {
			form.append("file", roiList[i].video.file);
		}
	}
}

form.encoding = "multipart/form-data";

var xhr = new XMLHttpRequest();
xhr.onload = function() {
	console.log("Upload complete.");
	window.location.href = 'listp.jsp';
};
xhr.open("post", "UploadServlet", true);
xhr.send(form);
}

function savePresentation() {
closePopup();
fillRoiList();
sendPresentation();
sendFiles();

}

/* ---------------------------------- editing control ---------------------------------- */

var edition = {
	enable: false,	
	accept: false,
	current: 0,
	next: 0
};


function accept() {
	
if (selection.mode == 1)
	roiSelection();
	
if ( (edition.enable == false) || (edition.current != edition.next) )
	return;
edition.enable = false;

closeEdition(edition.current);

edition.next = ptRoiList;
addRoiList();

// title
var roi = edition.next;
var bar = document.getElementById("bar");

var li = document.createElement("li");
li.id = roiList[roi].li;
li.onclick = function(){ editMultimedia(roi); };

var input = document.createElement("input");
input.id = roiList[roi].inputTitle; 
input.type = 'text';
input.autofocus = true;
input.onchange = function(){ addEdition(); };

li.appendChild(input);
bar.appendChild(li);
    
edition.current = edition.next = roi;
    editPopup();
}

function addEdition() {
	
if (edition.current == edition.next)
	return;

ptRoiList++;
edition.current = edition.next;
var roi = edition.current;

/* text panel */
var pText = document.getElementById("panel-text");

var textarea = document.createElement("textarea");
textarea.id = roiList[roi].inputDescription;
textarea.placeholder = 'Escreva o texto aqui.';
pText.appendChild(textarea);

/* image panel */
var table = document.createElement("table");
table.id = roiList[roi].inputImage;
table.className = 'list';
table.width = "100%";
table.style.visibility = 'hidden';

var row = table.insertRow(0);
var cell = row.insertCell(0);
cell.style.width = "90%";
cell = row.insertCell(1);
cell.style.width = "10%";

/*
row = table.insertRow(1);
row.className = 'row';
cell = row.insertCell(0);
cell.className = 'cell';
cell.innerHTML = "dinamico";

cell = row.insertCell(1);
cell.className = 'cell';
var element = document.createElement("div");
element.className = 'remove';
element.onclick = function(){ deleteRow(this.parentNode.parentNode.rowIndex, pt); };
cell.appendChild(element);
*/

var list = document.getElementById("list-image");
list.appendChild(table);

var li = document.getElementById(roiList[roi].li);
var element = document.createElement("div");
element.className = 'remove-alt';
element.onclick = function(){ removeEdition(roi); };
li.appendChild(element);

editMultimedia(roi);
}

function removeEdition(roi) {

editMultimedia(0);

var bar = document.getElementById("bar");
var li = document.getElementById(roiList[roi].li);
bar.removeChild(li);

var pText = document.getElementById("panel-text");
var textarea = document.getElementById(roiList[roi].inputDescription);
pText.removeChild(textarea);

var list = document.getElementById("list-image");
var table = document.getElementById(roiList[roi].inputImage);
list.removeChild(table);

roiList[roi] = null;
}

function closeEdition(roi) {
	
var id = [document.getElementById("panel-text"), document.getElementById("panel-image"), document.getElementById("panel-video")];

for (var i=0; i<3; i++) {
	if (roiList[roi].panel[i] == 1) {
		id[i].classList.toggle('closed');
		roiList[roi].panel[i] = 0;
	}
}

//var inputDescription = document.getElementById(roiList[roi].inputDescription);
//inputDescription.setAttribute("style", "display:none;");
//var inputImage = document.getElementById(roiList[roi].inputImage);
//inputImage.setAttribute("style", "display:none;");

//var table = document.getElementById("video");
//table.style.visibility = 'hidden';

document.getElementById(roiList[roi].li).style.backgroundColor = '#777777';

roiList[roi].edit = false;

}

function openEdition(roi) {
	
/*var inputDescription = document.getElementById(roiList[roi].inputDescription);
inputDescription.setAttribute("style", "display:block;");
var inputImage = document.getElementById(roiList[roi].inputImage);
inputImage.setAttribute("style", "display:block;");

if (roiList[roi].video.status == 1) {
	var table = document.getElementById("video");
	var name = table.rows[1].cells[0];
	name.innerHTML = roiList[roi].video.file.name;
	table.style.visibility = 'visible';
}

document.getElementById("panel-text").classList.toggle('closed');
roiList[roi].panel[0] = 1;
*/
roiList[roi].edit = true;
}

var slerp = {
	status:false,
	t:0.0,
	/*dest:{x:0, y:0, z:0, s: 1}*/
};

function showView() {

if (slerp.status == false)
	return;
	
interpolation(slerp.t);
slerp.t = slerp.t + 0.01;
if (slerp.t >= 1.01) {
	slerp.status = false;
}
}

function editMultimedia(roi) {
// roi was not accepted yet
if (edition.current != edition.next) /*&& (edition.next == roi)*/
	return;

console.log(roiList);
console.log(roi);

// move to view
if (slerp.status == false) {
	slerp.t = 0.0;
	dest.x = roiList[roi].view.x;
	dest.y = roiList[roi].view.y;
	dest.z = roiList[roi].view.z;
	dest.s = roiList[roi].view.s;
	slerp.status = true;
}


document.getElementById(roiList[roi].li).style.backgroundColor = '#2a88e0';
	
// roi already open	
if (roiList[roi].edit == true)
	return;

// close current
if (roiList[edition.current].edit == true)
	closeEdition(edition.current);

// open roi
openEdition(roi);

//roi is the current now
edition.current = edition.next = roi;
editPopup();
}

function displayPanel(p) {
	
var roi = edition.current;

if ( (roiList[roi].edit == false) || (roiList[roi].panel[p] == 1) )
    return;

var id = [document.getElementById("panel-text"), document.getElementById("panel-image"), document.getElementById("panel-video")];

for (var i=0; i<3; i++) {
	if (roiList[roi].panel[i] == 1) {
		id[i].classList.toggle('closed');
		roiList[roi].panel[i] = 0;
    }
}

id[p].classList.toggle('closed');
roiList[roi].panel[p] = 1;

}

function editPopup(roi) {
    document.getElementById("popup").style.top = '50%';
    document.getElementById("popup").style.left = '50%';
    document.getElementById("popup").style.transform = 'translate(-50%, -50%)';
    document.getElementById("popup").style.display = 'block';
    var first = document.getElementsByClassName("tablinks")[0];
    first.click();
	
var roi = roiList[edition.current];
	document.getElementById("titleROI").value = roi.title;	
	document.getElementById("root-description").value = roi.description;
}
function closePopup() {
    document.getElementById("popup").style.display = 'none';
closeEdition(edition.current);
}
function openTab(evt, cityName) {
    var i, tabcontent, tablinks;
    tabcontent = document.getElementsByClassName("tabcontent");
    for (i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablinks");
    for (i = 0; i < tablinks.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    document.getElementById(cityName).style.display = "block";
    evt.currentTarget.className += " active";
}

/* ---------------------------------- Multimedia Video ---------------------------------- */

function handleVideo(files) {

var roi = edition.current;

roiList[roi].video.file = files[0];
roiList[roi].video.status = 1;

// show video name
var table = document.getElementById("video");
var name = table.rows[1].cells[0];
name.innerHTML = files[0].name;
table.style.visibility = 'visible';
document.getElementById("form").reset();
}

function removeVideo() {
	
var roi = edition.current;

roiList[roi].video.file = null;
roiList[roi].video.status = 0;
var table = document.getElementById("video");
table.style.visibility = 'hidden';
document.getElementById("form").reset();
}

/* ---------------------------------- Multimedia Image ---------------------------------- */

var shown = -1;

function handleFiles(files) {

var roi = edition.current;
var numFiles = files.length;

for (var i=0; i<numFiles; i++) {	
    addRow(files[i].name);
    //console.log((files[i].type).split('/').pop());
    roiList[roi].imageList[roiList[roi].ptImageList] = {file:files[i], status:1};
    roiList[roi].ptImageList++;
}

}

function deleteRow(row, pt) {

var roi = edition.current;
var table = document.getElementById(roiList[roi].inputImage);

table.deleteRow(row);
roiList[roi].imageList[pt].status = 0;
document.getElementById("preview").style.visibility = 'hidden';

var rowCount = table.rows.length;
if (rowCount <= 8) {
	document.getElementById("panel-image").style.overflowY = "hidden";
}

if (rowCount == 1) {
	table.style.visibility = 'hidden';
}


}

function addRow(name) {

var roi = edition.current;
var table = document.getElementById(roiList[roi].inputImage);
table.style.visibility = 'visible';

var rowCount = table.rows.length;

if (rowCount > 8) {
	document.getElementById("panel-image").style.overflowY = "scroll";
}

var row = table.insertRow(rowCount);
row.className = 'row';

var pt = roiList[roi].ptImageList;

row.onmouseover = function(){ showPreview(pt); };
row.onmouseout = function(){ clearPreview(); };

var cell = row.insertCell(0);
cell.className = 'cell';
cell.innerHTML = name;
 
cell = row.insertCell(1);
cell.className = 'cell';
var element = document.createElement("div");
element.className = 'remove';
element.onclick = function(){ deleteRow(this.parentNode.parentNode.rowIndex, pt); };
cell.appendChild(element);

if (rowCount >= 3)
document.getElementById("list-image").scrollTop += 50;
}

function showPreview(pt) {

var roi = edition.current;
var img = document.getElementById("preview");  

img.style.visibility = 'visible';
if (pt == shown)
    return;
          
img.file = roiList[roi].imageList[pt].file;
var reader = new FileReader();
reader.onload = (function(aImg) { return function(e) { aImg.style.backgroundImage = 'url(' + e.target.result + ')'; }; })(img);
reader.readAsDataURL(roiList[roi].imageList[pt].file);
shown = pt;
} 

function clearPreview() {
document.getElementById("preview").style.visibility = 'hidden';
}
