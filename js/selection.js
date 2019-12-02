/* adjacency data */
var facesByWedge;

/* region of interest */
var facesRoi;
var indexBuffer;
var indices;

function createAdjRoi() {

var i, pt;

facesByWedge = [];
facesRoi = [];

indices = new Float32Array(numVertices);

for (i=0; i<numVertices; i++) {
	indices[i] = 0;
	acesByWedge[i] = {num: 0, face: new Array()};
}

var a, b, c;
for (i=0, pt=0; i<numFaces; i++, pt+=3) {

	// create adj list
	a = faces[pt];
	b = faces[pt+1];
	c = faces[pt+2];
			
	facesByWedge[a].face[facesByWedge[a].num] = i;
	facesByWedge[b].face[facesByWedge[b].num] = i;
	facesByWedge[c].face[facesByWedge[c].num] = i;

	facesByWedge[a].num++;
	facesByWedge[b].num++;
	facesByWedge[c].num++;

	facesRoi[i] = 0;
}
		
indexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, indexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, indices, gl.STATIC_DRAW);
indexBuffer.itemSize = 1;
indexBuffer.numItems = numVertices;
}

/* ---------------------------------- 3D selection ---------------------------------- */

//ray-triangle intersection
var EPSILON = 0.000001;
var edge1 = [0,0,0];
var edge2 = [0,0,0];
var tvec = [0,0,0];
var pvec = [0,0,0];
var qvec = [0,0,0];

var ray = {x:0, y:0, face:0};

function intersect(orig, dir, tri) {

vec3.subtract(tri[1], tri[0], edge1);
vec3.subtract(tri[2], tri[0], edge2);
vec3.cross(dir, edge2, pvec);
var det = vec3.dot(edge1, pvec);

if (det < EPSILON) return 0;

vec3.subtract(orig, tri[0], tvec);
var u = vec3.dot(tvec, pvec);

if (u < 0.0 || u > det) return 0;

vec3.cross(tvec, edge1, qvec);
var v = vec3.dot(dir, qvec);

if (v < 0.0 || u + v > det) return 0;

return 1;
}

var pmvMatrixInverse = mat4.create();
var pmvMatrix = mat4.create();

function unproject(winx,winy,winz,mat) { 

var viewport = gl.getParameter(gl.VIEWPORT);

var wx = 2 * (winx - viewport[0])/viewport[2] - 1.0; 
var wy = 2 * (winy - viewport[1])/viewport[3] - 1.0; 
var wz = 2 * winz - 1;

mat4.multiply(pMatrix, mvMatrix, pmvMatrix);
mat4.inverse(pmvMatrix, pmvMatrixInverse);

var n = [wx,wy,wz,1]; 
mat4.multiplyVec4(pmvMatrixInverse, n, n);

return [n[0]/n[3],n[1]/n[3],n[2]/n[3]];
}

function project(a, b, c) { 

var viewport = gl.getParameter(gl.VIEWPORT);
var _in = [a, b, c, 1]; 
var _out = [0, 0, 0, 0];

mat4.multiplyVec4(mvMatrix, _in, _out);
mat4.multiplyVec4(pMatrix, _out, _in);

if (_in[3] == 0)
 return;

_in[0] = ((_in[0]/_in[3]) * 0.5 + 0.5) * viewport[2] + viewport[0];
_in[1] = ((_in[1]/_in[3]) * 0.5 + 0.5) * viewport[3] + viewport[1];
_in[2] = ((_in[2]/_in[3]) * 0.5 + 0.5);

console.log(_in[0] + ", " + _in[1] + ", " + _in[2]);
}

function selectFace() {

var posX = rectangle.start.x + ray.x;
var posY = gl.viewportHeight - (rectangle.start.y + ray.y);

var start = unproject(posX, posY, 0);
var end = unproject(posX, posY, 1);
var dir = [0,0,0];
vec3.subtract(end, start, dir);
vec3.normalize(dir);

var triangle = [];
var i, a, b, c;
var numInter = 0;

for (i=0; i<numFaces; i++) {
 a = faces[i*3]; b = faces[i*3+1]; c = faces[i*3+2];
 triangle[0] = [vertices[a*3], vertices[a*3+1], vertices[a*3+2]];
 triangle[1] = [vertices[b*3], vertices[b*3+1], vertices[b*3+2]];
 triangle[2] = [vertices[c*3], vertices[c*3+1], vertices[c*3+2]];
 if (intersect(start, dir, triangle) == 1) {
	ray.face = i;
	numInter++;
	console.log("v1 = " + triangle[0][0] + ", " + triangle[0][1] + ", " + triangle[0][2]);
	console.log("v2 = " + triangle[1][0] + ", " + triangle[1][1] + ", " + triangle[1][2]);
	console.log("v3 = " + triangle[2][0] + ", " + triangle[2][1] + ", " + triangle[2][2]);
 }
}

console.log("face = " + ray.face);
console.log("numInter = " + numInter);
}


function createRoi() {

var maxFaces = numFaces;
var startFace = ray.face;
var perimeter = [];
var numPerimeter = 0;
var numFacesRoi = 0;
var curRoi = 1;
var curFace;
var i,j,w,f;

var ptIn = 0;
var ptOut = 0;

perimeter[0] = startFace;
numPerimeter++;
ptIn++;

while ( (ptIn != ptOut) && (numFacesRoi < maxFaces) ) {

 curFace = perimeter[ptOut];
 ptOut++;

 facesRoi[curFace] = curRoi;
 numFacesRoi++;

 for (i=0; i<3; i++) {

	w = faces[curFace*3+i];
		
	// set color
	colors[w*3] = 0.0; colors[w*3+1] = 1.0; colors[w*3+2] = 0.0;
	indices[w] = 1;

	for (j=0; j<facesByWedge[w].num; j++) {

	    f = facesByWedge[w].face[j];
	
	    if ( (facesRoi[f] != curRoi) && (facesRoi[f] != -1) && (addFace(f)) ) {
		if (addFace(f)) {
		perimeter[ptIn] = f;
		ptIn++;
		facesRoi[f] = -1; //in perimeter
		}
	    }
	}
 }
}

gl.bindBuffer(gl.ARRAY_BUFFER, indexBuffer);
gl.bufferData(gl.ARRAY_BUFFER, indices, gl.STATIC_DRAW);
}

function addFace(f) {

var i, w;
for (i=0; i<3; i++) {
 w = faces[f*3+i];

 if ( (vertices[w*3] >= pMin[0]   && vertices[w*3] <= pMax[0])   && 
	 (vertices[w*3+1] >= pMin[1] && vertices[w*3+1] <= pMax[1]) && 
	 (vertices[w*3+2] >= pMin[2] && vertices[w*3+2] <= pMax[2]) )
	return true;
}

return false;
}

/* ---------------------------------- 2D selection ---------------------------------- */

selection = {
	status: false,
	mode: 0,
	count:0
};

var rectangle = {
	start: {x:0, y:0}, 
	width: 0, 
	height: 0
};

function setRectangle(mouse) {
	
mouse.x = mouse.x - 570;
mouse.startX = mouse.startX - 570;

if (mouse.startX > mouse.x && mouse.startY > mouse.y) {
    rectangle.start.x = mouse.x;      rectangle.start.y = mouse.y;
}
else if (mouse.startX < mouse.x && mouse.startY > mouse.y) {
    rectangle.start.x = mouse.startX; rectangle.start.y = mouse.y;
}
else if (mouse.startX < mouse.x && mouse.startY < mouse.y) {
    rectangle.start.x = mouse.startX; rectangle.start.y = mouse.startY;
}
else if (mouse.startX > mouse.x && mouse.startY < mouse.y) {
    rectangle.start.x = mouse.x;      rectangle.start.y = mouse.startY;
}

rectangle.width  = Math.abs(mouse.startX - mouse.x) + 1;
rectangle.height = Math.abs(mouse.startY - mouse.y) + 1;
console.log("start = " + rectangle.start.x + ", " + rectangle.start.y + " width = " + rectangle.width + " height = " + rectangle.height);
}

function roiSelection() {

if (selection.count > 0) {
    var list = document.getElementById("canvas2D");
    list.removeChild(list.childNodes[0]);
    selection.count = 0;
}

selection.mode = !selection.mode;

if (selection.mode == 1) {
    document.getElementById("canvas3D").setAttribute("style" ,"z-index: 1");
    console.log("2D");
}
else {
    document.getElementById("canvas3D").setAttribute("style" ,"z-index: 2");
    console.log("3D");
    document.getElementById("select").style.backgroundImage = 'url(edit-buttons/select.png)';
}

}

function initSelection(canvas2D) {

function setMousePosition(e) {

var ev = e || window.event;
if (ev.pageX) {
	mouse.x = ev.pageX + window.pageXOffset;
	mouse.y = ev.pageY + window.pageYOffset;
}
};

var mouse = {x: 0, y: 0, startX: 0, startY: 0};
var element = null;

canvas2D.onmousemove = function (e) {
    setMousePosition(e);
    if (element !== null) {
    	element.style.width = Math.abs(mouse.x - mouse.startX) + 'px';
    	element.style.height = Math.abs(mouse.y - mouse.startY) + 'px';
    	element.style.left = (mouse.x - mouse.startX < 0) ? mouse.x-570 + 'px' : mouse.startX-570 + 'px';
    	element.style.top = (mouse.y - mouse.startY < 0) ? mouse.y + 'px' : mouse.startY + 'px';
    }
}

canvas2D.onclick = function (e) {
    if (element !== null) {
    	element = null;
    	selection.count++;
    	canvas2D.style.cursor = "default";
    	console.log("finsihed." + mouse.x + " | " + mouse.y);
    	setRectangle(mouse);
    	selection.status = true;
    } 
    else {
    	if (selection.count == 1) { 
    		canvas2D.removeChild(canvas2D.childNodes[0]);
    		selection.count = 0;
    	}

    	mouse.startX = mouse.x;
    	mouse.startY = mouse.y;
    	console.log("begun." + mouse.startX + " | " + mouse.startY);
    	element = document.createElement('div');
    	element.className = 'rectangle';
    	element.style.left = mouse.x-570 + 'px';
    	element.style.top = mouse.y + 'px';
    	canvas2D.appendChild(element);
    	canvas2D.style.cursor = "crosshair";
    }
}

}

