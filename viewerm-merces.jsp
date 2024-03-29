<html>
<head>
<title>Apresentação Multimídia</title>
    <meta http-equiv="content-type" content="text/html; charset=UTF-8" />

<script type="text/javascript" src="lib/glMatrix-0.9.5.min.js"></script>
<script type="text/javascript" src="lib/webgl-utils.js"></script>

<script type="text/javascript" src="js/events.js"></script>
<script type="text/javascript" src="js/mesh.js"></script>
<script type="text/javascript" src="js/presentation.js"></script>

<link rel="stylesheet" type="text/css" href="css/viewerm.css">
<link rel="stylesheet" type="text/css" href="css/newstyle.css">


<script id="shader-fs" type="x-shader/x-fragment">
#ifdef GL_ES
precision highp float;
#endif

uniform int textureoff;
uniform int lighting;

uniform int offscreen;
uniform vec3 pMin;
uniform vec3 pMax;
uniform int show;

varying vec3 vNormal;
varying float DEPTH;

varying vec4 vColor;

varying vec4 eyeVert;               // fragment in eye coordinates
varying vec3 eyeDir;                // direction of viewing ray in eye coordinates

uniform mat4 uMVMatrixInverse;

// depth color
uniform int depth;
uniform float far;

void main(void) {

vec4 color;
vec4 aux;
vec4 fragColor;
vec3 ambientLight;
vec3 normal;

color = vColor;

vec3 point = vec3(uMVMatrixInverse*vec4(eyeVert.xyz,eyeVert.w));

if (offscreen == 0) {

	ambientLight = vec3(1.0,1.0,1.0);
	
    /*if (lighting == 1) {ambientLight = vec3(1.0,1.0,1.0);}
    else               {ambientLight = vec3(0.5,0.5,0.5);}*/
    
    if ( (show == 1) && (point.x >= pMin.x && point.x <= pMax.x)  && (point.y >= pMin.y && point.y <= pMax.y) && (point.z >= pMin.z && point.z <= pMax.z) ) {
		aux =  vec4(1.0, 1.0, 1.0, 0.5); /*vec4(color.r, color.g, color.b, 0.5);*/
    }
    else {
		if (textureoff == 1) {aux = vec4(1.0, 1.0, 1.0, 1.0);}
		else 				 {aux = color;}
	}

    normal = normalize(vNormal);
    fragColor = aux * vec4(normal.z, normal.z, normal.z, 1.0);

	if (depth == 1) {
		vec4 nearColor = vec4(1.0, 1.0, 1.0, 1.0);
		vec4 farColor = vec4(0.0, 0.0, 0.0, 1.0);
		float near = 0.0;

		gl_FragColor = mix(nearColor, farColor, smoothstep(near, far, gl_FragCoord.z / gl_FragCoord.w));
    } 
	else {
		gl_FragColor = vec4(fragColor.rgb * ambientLight, fragColor.a);
	}

}
else {
    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}

}

</script>

<script id="shader-vs" type="x-shader/x-vertex">
attribute vec3 aVertexPosition;

attribute vec3 aVertexNormal;
varying vec3 vNormal;

varying float DEPTH;

attribute vec4 aVertexColor;
varying vec4 vColor;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat3 uNMatrix;

// texture mapping
varying vec4 eyeVert;
varying vec3 eyeDir;

void main(void) {

vNormal = uNMatrix * aVertexNormal;

vColor = aVertexColor;

// texture mapping
eyeVert = uMVMatrix * vec4(aVertexPosition, 1.0);
eyeDir  = normalize(eyeVert.xyz);

gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);

DEPTH = gl_Position.z / 500.0 ;
}
</script>

<script type="text/javascript">

/* ---------------------------------- Multimedia Presentation ---------------------------------- */

var path;

/* ---------------------------------- mesh ---------------------------------- */

var mesh = {
	type: 0,
	src: {model:"", color:"", cell:""},
	mapping: null,
	view:{x:0, y:0, z:0, s:0}
};

function initMesh() {
	
mesh.type = 0;
mesh.src.model =  "object/merces/merces_ss-n.m2.m3";

mesh.view.x = 0;
mesh.view.y = 0;
mesh.view.z = 0;
mesh.view.s = 1;

rot.x = mesh.view.x;
rot.y = mesh.view.y;
rot.z = mesh.view.z;
rot.s = mesh.view.s;

path = 'object/merces/data/';

}

function loadModel() {

var request = new XMLHttpRequest();
request.open("GET", mesh.src.model);
request.responseType = "arraybuffer";
request.onreadystatechange = function () {
	if (request.readyState == 4) {
		
		if (mesh.type == 0)
			loadColorModel(request.response);
		if (mesh.type == 1)
			loadTextureModel(request.response);
		if (mesh.type == 2) {
			loadProgressiveModel(request.response);
			loadRefinementData();
		}
		displayScreen();
		tick();
	}
};
	
request.send();
}

function loadTextureProgressive() {

colorTexture = gl.createTexture();
colorTexture.image = new Image();
colorTexture.image.onload = function () {
	initColorTexture(colorTexture);
};

cellTexture = gl.createTexture();
cellTexture.image = new Image();
cellTexture.image.onload = function () {
	initTexture(cellTexture, gl.RGB, gl.NEAREST);
};

colorTexture.image.src = mesh.src.color;
cellTexture.image.src = mesh.src.cell;
}

function loadTexture() {

colorTexture = gl.createTexture();
colorTexture.image = new Image();
colorTexture.image.onload = function () {
	initTexture(colorTexture, gl.RGBA, gl.LINEAR);
};

colorTexture.image.src = mesh.src.color;
}

/* ---------------------------------- draw scene ---------------------------------- */

function drawScene() {

gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

mat4.perspective(60.0, gl.viewportWidth/gl.viewportHeight, 1.0, 4000.0, pMatrix);
mat4.identity(mvMatrix);
mat4.translate(mvMatrix, [x, y, z]);

glMatrix();
mat4.multiply(mvMatrix, rotMatrix);

gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, vertexBuffer.itemSize, gl.FLOAT, false, 0, 0);

gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
gl.vertexAttribPointer(shaderProgram.vertexNormalAttribute, normalBuffer.itemSize, gl.FLOAT, false, 0, 0);

gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);

setMatrixUniforms();
gl.drawElements(gl.TRIANGLES, faceBuffer.numItems, gl.UNSIGNED_INT, 0);
}

/* ---------------------------------- display ---------------------------------- */
var blink = {
	status:0,
	start: 0,
	time: 300
};

var update = false;
function display() {

//off-screen rendering
gl.bindFramebuffer(gl.FRAMEBUFFER, framebuffer);
offscreen();

//on-screen rendering
gl.bindFramebuffer(gl.FRAMEBUFFER, null);

gl.clearColor(0.2, 0.2, 0.2, 1.0);

if (update) {
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);

    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);
    gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, faces, gl.STATIC_DRAW);
}

if (mesh.type == 0) {
	gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, colorBuffer.itemSize, gl.FLOAT, false, 0, 0);
}

if (mesh.type == 1) {
	
	gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);
	gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, texCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);

	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, colorTexture);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
}

if (mesh.type == 2) {

	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, colorTexture);
	gl.uniform1i(shaderProgram.color, 0);

	gl.activeTexture(gl.TEXTURE1);
	gl.bindTexture(gl.TEXTURE_2D, cellTexture);
	gl.uniform1i(shaderProgram.cell, 1);

	gl.uniform1i(shaderProgram.max_size_color_tex_x, mesh.mapping[0]);
	gl.uniform1i(shaderProgram.max_size_color_tex_y, mesh.mapping[1]);
	gl.uniform1i(shaderProgram.max_size_tex_x, mesh.mapping[2]);
	gl.uniform1i(shaderProgram.max_size_tex_y, mesh.mapping[3]);
	gl.uniform1i(shaderProgram.size_cell, mesh.mapping[4]);
	gl.uniform3f(shaderProgram.bounding_box_ccc, mesh.mapping[5], mesh.mapping[6], mesh.mapping[7]);
	gl.uniform1i(shaderProgram.numberGcells, mesh.mapping[8]);
}

gl.uniform1i(shaderProgram.textureoff, textureoff);
gl.uniform1i(shaderProgram.lighting, lighting);
gl.uniform1i(shaderProgram.offscreen, 0);
gl.uniform1i(shaderProgram.show, show);

gl.uniform1i(shaderProgram.depth, 0);
//gl.uniform1f(shaderProgram.far, document.getElementById("slider").value);

gl.uniform3f(shaderProgram.pMin, bb.min.x, bb.min.y, bb.min.z);
gl.uniform3f(shaderProgram.pMax, bb.max.x, bb.max.y, bb.max.z);

showView();
drawScene();

if (update) {update = false;}
}

/* ---------------------------------- off-screen rendering ---------------------------------- */

var show = 0;

function offscreen() {

gl.clearColor(0.0, 0.0, 0.0, 1.0); //black background
gl.uniform1i(shaderProgram.offscreen, 1);

drawScene();

//picking
/*
var posX = lastMouseX;
var posY = gl.viewportHeight - lastMouseY;
var data = new Uint8Array(1 * 1 * 4);
gl.readPixels(posX, posY, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, data);
console.log(posX + " - " + posY + " # " + data[0] + " - " + data[1] + " - " + data[2] + " - " +data[3]);

if ((data[0] == 0) && (data[1] == 255) && (data[2] == 0)) {show = 1;}
else {show = 0};
*/
}

/* ---------------------------------- webGL ---------------------------------- */
var shaderProgram;
var canvas;
var gl;

function initGL(canvas) {
	
try {
	//gl = canvas.getContext("experimental-webgl");
	gl = canvas.getContext("experimental-webgl", {preserveDrawingBuffer: true});
	gl.viewportWidth = canvas.width;
	gl.viewportHeight = canvas.height;
} catch (e) {
}

if (!gl) {
    alert("Could not initialise WebGL");
}

var ext = gl.getExtension("OES_element_index_uint");
if (!ext) {
    alert("No OES_element_index_uint support");
}

var ext2 = gl.getExtension("OES_standard_derivatives");
if (!ext2) {
    alert("No OES_standard_derivatives support");
}

}

function getShader(gl, id) {

var shaderScript = document.getElementById(id);
if (!shaderScript) {
    return null;
}

var str = "";
var k = shaderScript.firstChild;
while (k) {
    if (k.nodeType == 3) {
	str += k.textContent;
    }
    k = k.nextSibling;
}

var shader;
if (shaderScript.type == "x-shader/x-fragment") {
    shader = gl.createShader(gl.FRAGMENT_SHADER);
}
else if (shaderScript.type == "x-shader/x-vertex") {
    shader = gl.createShader(gl.VERTEX_SHADER);
} 
else {
    return null;
}

gl.shaderSource(shader, str);
gl.compileShader(shader);

if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    console.log(gl.getShaderInfoLog(shader));
    return null;
}

return shader;
}

function initShaders() {

var fragmentShader = getShader(gl, "shader-fs");
var vertexShader = getShader(gl, "shader-vs");

shaderProgram = gl.createProgram();
gl.attachShader(shaderProgram, vertexShader);
gl.attachShader(shaderProgram, fragmentShader);
gl.linkProgram(shaderProgram);

if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert(gl.LINK_STATUS);
}

gl.useProgram(shaderProgram);

shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
shaderProgram.nMatrixUniform = gl.getUniformLocation(shaderProgram, "uNMatrix");
shaderProgram.mvMatrixInverseUniform = gl.getUniformLocation(shaderProgram, "uMVMatrixInverse");

shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

shaderProgram.vertexNormalAttribute = gl.getAttribLocation(shaderProgram, "aVertexNormal");
gl.enableVertexAttribArray(shaderProgram.vertexNormalAttribute);

if (mesh.type == 0) {
	shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
}

if (mesh.type == 1) {
	shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
	gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
	shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, "uSampler");
}

if (mesh.type == 2) {
	shaderProgram.color = gl.getUniformLocation(shaderProgram, "color_tiles");
	shaderProgram.cell = gl.getUniformLocation(shaderProgram, "cell_tex");
	shaderProgram.max_size_color_tex_x = gl.getUniformLocation(shaderProgram, "max_size_color_tex_x");
	shaderProgram.max_size_color_tex_y = gl.getUniformLocation(shaderProgram, "max_size_color_tex_y");
	shaderProgram.max_size_tex_x = gl.getUniformLocation(shaderProgram, "max_size_tex_x");
	shaderProgram.max_size_tex_y = gl.getUniformLocation(shaderProgram, "max_size_tex_y");
	shaderProgram.size_cell = gl.getUniformLocation(shaderProgram, "size_cell");
	shaderProgram.bounding_box_ccc = gl.getUniformLocation(shaderProgram, "bounding_box_ccc");
	shaderProgram.numberGcells = gl.getUniformLocation(shaderProgram, "numberGcells");
}

// interaction
shaderProgram.textureoff = gl.getUniformLocation(shaderProgram, "textureoff"); 
shaderProgram.lighting = gl.getUniformLocation(shaderProgram, "lighting");

// depth image
shaderProgram.depth = gl.getUniformLocation(shaderProgram, "depth");
shaderProgram.far = gl.getUniformLocation(shaderProgram, "far"); 

// selection
shaderProgram.offscreen = gl.getUniformLocation(shaderProgram, "offscreen");
shaderProgram.show = gl.getUniformLocation(shaderProgram, "show");
shaderProgram.pMin = gl.getUniformLocation(shaderProgram, "pMin");
shaderProgram.pMax = gl.getUniformLocation(shaderProgram, "pMax");

}

function webGLStart() {

canvas = document.getElementById("canvas3D");
initGL(canvas);
initFramebuffer();
initShaders();

loadModel();

gl.enable(gl.DEPTH_TEST);

document.onkeydown = handleKeyDown;
document.onkeyup = handleKeyUp;
        
canvas.onmousedown = handleMouseDown;
canvas.onmouseup = handleMouseUp;
canvas.onmousemove = handleMouseMove;

if (canvas.addEventListener) {
    canvas.addEventListener('touchstart', startTouch, false);
    canvas.addEventListener('touchmove', continueTouch, false);
    canvas.addEventListener('touchend', stopTouch, false);
}

canvas.addEventListener('contextmenu', function(e) {
    if (e.button === 2) {
	e.preventDefault();
	return false;
    }
}, false);
		
//tick();
}

function tick() {
requestAnimFrame(tick);
handleKeys();
display();

}

/* ---------------------------------- Screen ---------------------------------- */

function displayScreen() {
document.getElementById("divLoading").setAttribute("style" ,"display: none");
document.getElementById("divScreen").setAttribute("style" ,"display: block");
}

function adjustCanvas() {

var canvas = document.getElementById("canvas3D");
var width = 160;
var height = 0;
			
canvas.width = window.innerWidth - width;
canvas.height = window.innerHeight - height;
canvas.style.width = window.innerWidth - width;
canvas.style.height = window.innerHeight - height;

}

window.onload = function() {
	adjustCanvas();
	initMesh();
	loadPresentation();
	webGLStart();
};

window.onresize = function() {
    adjustCanvas();
};

// slider
function showValue() {
	document.getElementById("slider-value").innerText = document.getElementById("slider").value;
}
function download() {

var image = canvas.toDataURL("image/png").replace("image/png", "image/octet-stream");
window.open(image, 'image.png');
}
</script>

</head>
<body>
<!-- http://preloaders.net/en/circular -->
<div id="divLoading" class="loading"></div>

<div id="divScreen" style="display: none;">
	<div class="sidenav">

	
  <table style="width:100%;">
  <tr>
  <td width="160px"><ul class="sidebar" id="sBar"></ul></td>
  <td>
    <div id="divCanvas">
    <canvas id="canvas3D"></canvas>
    </div>
  </td>
  </tr>
  </table>
  
  <div class="toolbar">
    <div class="options"><h1>&#9776; Options</h1></div>
    <table>
    <tr>
    <td width="160px"><div class="options-back"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/zoom-in.png);"    onclick="eventZoomIn();"   onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-in.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-in-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/zoom-out.png);"   onclick="eventZoomOut();"  onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-out.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-out-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/texture.png);"    onclick="eventTexture();"  onmouseover="this.style.backgroundImage='url(edit-buttons/texture-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/texture.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/texture-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/texture-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/turn-left.png);"  onclick="eventRotLeft();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-left.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-left-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'"></div></td>  
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/turn-right.png);" onclick="eventRotRight();" onmouseover="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-right.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-right-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/turn-up.png);"    onclick="eventRotUp();"    onmouseover="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-up.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-up-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/turn-down.png);"  onclick="eventRotDown();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-down.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-down-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/left.png);"       onclick="eventMovLeft();"  onmouseover="this.style.backgroundImage='url(edit-buttons/left-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/left.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/left-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/left-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/right.png);"      onclick="eventMovRight();" onmouseover="this.style.backgroundImage='url(edit-buttons/right-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/right.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/right-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/right-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/up.png);"         onclick="eventMovUp();"    onmouseover="this.style.backgroundImage='url(edit-buttons/up-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/up.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/up-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/up-over.png)'"></div></td>
    <td style="padding-left:10px;"><div class="button" style="background-image:url(edit-buttons/down.png);"       onclick="eventMovDown();"  onmouseover="this.style.backgroundImage='url(edit-buttons/down-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/down.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/down-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/down-over.png)'"></div></td>
    </tr>
    </table>
  </div>
</div>
  <!--
  <div style="background-color:#1abc9c; position:fixed; bottom:0px; right: 0px; z-index:1004; padding:10px; color:#fff; font-size: 16px; font-weight: normal;">
    <div> Far: <span id="slider-value">value</span></div>
    <input id="slider" type="range" min="0" max="4000" value="0" step="50" onchange="showValue()"/>
	<div style="border:2px solid white; border-radius: 25px; margin:auto; height:20px; width:20px; cursor:pointer; background-image:url(edit-buttons/down.png); background-size: 80%; background-position: 50% 50%; background-repeat: no-repeat;" onclick="download();"></div>
  </div>
  -->
</div>

</body>
</html>