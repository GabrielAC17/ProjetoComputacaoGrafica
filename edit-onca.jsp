<html>
<<<<<<< HEAD
<head>
<title>Associaï¿½ï¿½o 3D</title>
=======
    <head>
<title>Associação 3D</title>
>>>>>>> refs/heads/BranchRicardoGiovanni
<meta http-equiv="content-type" content="text/html; charset=ISO-8859-1">
    
<script
			  src="https://code.jquery.com/jquery-3.4.1.js"
			  integrity="sha256-WpOohJOqMqqyKL9FccASB9O0KwACQJpFTUBLTYOVvVU="
			  crossorigin="anonymous"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js" type="text/javascript"></script>
<script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.11.4/jquery-ui.min.js" type="text/javascript"></script>
		

<script type="text/javascript" src="lib/glMatrix-0.9.5.min.js"></script>
<script type="text/javascript" src="lib/webgl-utils.js"></script>

<script type="text/javascript" src="js/events.js"></script>
<script type="text/javascript" src="js/mesh.js"></script>
<script type="text/javascript" src="js/selection.js"></script>
<script type="text/javascript" src="js/edit.js"></script>

<link rel="stylesheet" type="text/css" href="css/edit.css">

<script id="shader-fs" type="x-shader/x-fragment">
#ifdef GL_ES
precision highp float;
#endif

uniform int textureoff;
uniform int lighting;

uniform int offscreen;
uniform int fragOut;
uniform vec3 pMin;
uniform vec3 pMax;
uniform vec3 pCenter;
uniform float rad;
uniform int show;

varying vec3 vNormal;

varying vec2 vTextureCoord;
uniform sampler2D uSampler;

varying vec4 eyeVert;               // fragment in eye coordinates
varying vec3 eyeDir;                // direction of viewing ray in eye coordinates

uniform mat4 uMVMatrixInverse;

// packing floats into rgba
float shift_right (float v, float amt) { 
    v = floor(v) + 0.5; 
    return floor(v / exp2(amt)); 
}
float shift_left (float v, float amt) { 
    return floor(v * exp2(amt) + 0.5); 
}
float mask_last (float v, float bits) { 
    return mod(v, shift_left(1.0, bits)); 
}
float extract_bits (float num, float from, float to) { 
    from = floor(from + 0.5); to = floor(to + 0.5); 
    return mask_last(shift_right(num, from), to - from); 
}
vec4 encode_float (float val) { 
    if (val == 0.0) return vec4(0, 0, 0, 0); 
    float sign = val > 0.0 ? 0.0 : 1.0; 
    val = abs(val); 
    float exponent = floor(log2(val)); 
    float biased_exponent = exponent + 127.0; 
    float fraction = ((val / exp2(exponent)) - 1.0) * 8388608.0; 
    float t = biased_exponent / 2.0; 
    float last_bit_of_biased_exponent = fract(t) * 2.0; 
    float remaining_bits_of_biased_exponent = floor(t); 
    float byte4 = extract_bits(fraction, 0.0, 8.0) / 255.0; 
    float byte3 = extract_bits(fraction, 8.0, 16.0) / 255.0; 
    float byte2 = (last_bit_of_biased_exponent * 128.0 + extract_bits(fraction, 16.0, 23.0)) / 255.0; 
    float byte1 = (sign * 128.0 + remaining_bits_of_biased_exponent) / 255.0; 
    return vec4(byte4, byte3, byte2, byte1); 
}

void main(void) {

vec4 color;
vec4 aux;
vec4 fragColor;
vec3 ambientLight;
vec3 normal;

color = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));

vec3 point = vec3(uMVMatrixInverse*vec4(eyeVert.xyz,eyeVert.w));

if (offscreen == 0) {

	ambientLight = vec3(1.0,1.0,1.0);	
	
	float raioInit = (point.x - pCenter.x)*(point.x - pCenter.x) + (point.y - pCenter.y)*(point.y - pCenter.y);
	float raioFinal = raioInit / (pCenter.x + pCenter.y +  pCenter.z);	
	
	if((show == 1) && ((pCenter.x + raioFinal) >= pMin.x && (pCenter.x + raioFinal) <= pMax.x) &&((pCenter.y + raioFinal) >= pMin.y && (pCenter.y + raioFinal) <= pMax.y) && ((pCenter.z + raioFinal) >= pMin.z && (pCenter.z + raioFinal) <= pMax.z )){
		aux = vec4(1.0, 1.0, 1.0, 1.0);
	}
		
    //}
    else {
		if (textureoff == 1) {aux = vec4(1.0, 1.0, 1.0, 1.0);}
		else 				 {aux = color;}
	}

    normal = normalize(vNormal);
    fragColor = aux * vec4(normal.z, normal.z, normal.z, 1.0);

	gl_FragColor = vec4(fragColor.rgb * ambientLight, fragColor.a);
}
else {
    
    if (fragOut == 0)      {gl_FragColor = encode_float(point.x);}
    else if (fragOut == 1) {gl_FragColor = encode_float(point.y);}
    else if (fragOut == 2) {gl_FragColor = encode_float(point.z);}
    else				   {gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);}
}

}

</script>

<script id="shader-vs" type="x-shader/x-vertex">
attribute vec3 aVertexPosition;

attribute vec3 aVertexNormal;
varying vec3 vNormal;

attribute vec2 aTextureCoord;
varying vec2 vTextureCoord;

uniform mat4 uMVMatrix;
uniform mat4 uPMatrix;
uniform mat3 uNMatrix;

// texture mapping
varying vec4 eyeVert;
varying vec3 eyeDir;

void main(void) {

vNormal = uNMatrix * aVertexNormal;

vTextureCoord = aTextureCoord;

// texture mapping
eyeVert = uMVMatrix * vec4(aVertexPosition, 1.0);
eyeDir  = normalize(eyeVert.xyz);

gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
}
</script>

<script type="text/javascript">

/* ---------------------------------- mesh ---------------------------------- */

var mesh = {
	type: 0,
	src: {model:"", color:"", cell:""},
	mapping: null,
	selection: {method:0},
	view:{x:0, y:0, z:0, s:0},
	print:""
};

function initMesh() {

mesh.type = 1;
mesh.src.model = "object/onca/onca.m.m3";
mesh.src.color = "object/onca/onca.jpg";

mesh.selection.method = 1; //bb

mesh.view.x = -0.2561;
mesh.view.y = -0.6336;
mesh.view.z = -0.6598;
mesh.view.s = 0.3123;

rot.x = mesh.view.x;
rot.y = mesh.view.y;
rot.z = mesh.view.z;
rot.s = mesh.view.s;

mesh.print = "Onï¿½a Wauja";

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
		
		if (mesh.selection.method == 2)
			createAdjRoi();
			
		displayScreen();
		tick();
		//console.log(rot.x + "-" + rot.y + "-" + rot.z + "-" + rot.s);
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

if (mesh.selection.method == 2) {
	gl.bindBuffer(gl.ARRAY_BUFFER, indexBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexIndexAttribute, indexBuffer.itemSize, gl.FLOAT, false, 0, 0);
}

gl.uniform1i(shaderProgram.textureoff, textureoff);
gl.uniform1i(shaderProgram.lighting, lighting);
gl.uniform1i(shaderProgram.offscreen, 0);
gl.uniform1i(shaderProgram.show, show);

showView();
drawScene();

if (update) {update = false;}
}

/* ---------------------------------- off-screen rendering ---------------------------------- */

function round(value) {
if (value < 0.0) {
	return (value - 0.1);
}
return (value + 0.1);
}

function offscreen() {

gl.clearColor(0.0, 0.0, 0.0, 1.0); //black background
gl.uniform1i(shaderProgram.offscreen, 1);
gl.uniform1i(shaderProgram.fragOut, fragOut);

drawScene();

if (selection.status == true)
	createBB();

}

var fragOut = -1;
var groundTruth = [];
var max_float = 1.0e37;
var pMin = [];
var pMax = [];
var show = 0;

function createBB() {

edition.enable = false;

//console.log(rot.x + "|" + rot.y + "|" + rot.z + "|" + rot.s);
/*
rectangle.width = 33;
rectangle.height = 34;
rectangle.start.x = 198;
rectangle.start.y = 240;
*/

var data = new Uint8Array(rectangle.width * rectangle.height * 4);
gl.readPixels(rectangle.start.x, gl.viewportHeight-(rectangle.start.y+rectangle.height-1), rectangle.width, rectangle.height, gl.RGBA, gl.UNSIGNED_BYTE, data);

/*
var width = rectangle.width;
var height = rectangle.height;
var i,j,k;

var dataP = new Uint8Array(data.buffer);

//flip vertically
for (i=0; i<height/2; i++) {
    for(j=0; j<width; j++) {
	pt = (i*width*4)+(j*4);
	pt_F = ((height-1-i)*width*4) +(j*4);
	for (k=0; k<4; k++) { 
	    temp = dataP[pt + k];
	    dataP[pt+k] = dataP[pt_F + k];
	    dataP[pt_F + k] = temp;
	}
    }
}

var canvas2d = document.getElementById("temp-canvas");
canvas2d.width = width;
canvas2d.height = height;
var context = canvas2d.getContext('2d');
var imageData = context.createImageData(width, height);
imageData.data.set(dataP);
context.putImageData(imageData, 0, 0);
*/

if (fragOut == -1) {
	
	var size = rectangle.width*rectangle.height;
	var	black = setGroundTruth(data, rectangle.width, rectangle.height);
		
	if (black != size) {
	    pMin[0] = pMin[1] = pMin[2] = max_float;
	    pMax[0] = pMax[1] = pMax[2] = -max_float;
	    fragOut++;
	}
	else {
		fragOut = -1;
		selection.status = false;
	}
}
else if ((fragOut == 0) || (fragOut == 1) || (fragOut == 2)) {

	data = new Float32Array(data.buffer);
	var size = data.length;
	
	for (var i=0, pt=0; i<size; i++, pt+=4) {
		if (groundTruth[i] == 1) {
			
			if ( (data[i] >= mMin[fragOut]) && (data[i] <= mMax[fragOut]) ) {	
				if (data[i] < pMin[fragOut])
					pMin[fragOut] = data[i];
				if (data[i] > pMax[fragOut])
					pMax[fragOut] = data[i];
			}
		}
	}
		
	fragOut++;
}
	
if (fragOut == 3) {
	
	var dist = [(pMax[0]-pMin[0])/2.0, (pMax[1]-pMin[1])/2.0, (pMax[2]-pMin[2])/2.0];
	var rad = dist[0];
	if (dist[1] > rad)
		rad = dist[1];
	if (dist[2] > rad)
		rad = dist[2];
	var pCenter = [pMin[0]+dist[0], pMin[1]+dist[1], pMin[2]+dist[2]];
	
	gl.uniform3f(shaderProgram.pCenter, pCenter[0], pCenter[1], pCenter[2]);
	gl.uniform1f(shaderProgram.rad, rad);
	/*
	gl.uniform3f(shaderProgram.pMin, round(pMin[0]), round(pMin[1]), round(pMin[2]) );
	gl.uniform3f(shaderProgram.pMax, round(pMax[0]), round(pMax[1]), round(pMax[2]) );
	*/
	gl.uniform3f(shaderProgram.pMin, pMin[0], pMin[1], pMin[2]);
	gl.uniform3f(shaderProgram.pMax, pMax[0], pMax[1], pMax[2]);
	
	if (mesh.selection.method == 2) {
		selectFace();
		createRoi();
	}
	
	fragOut = -1;
	selection.status = false;
	edition.enable = true;
	show = 1;
}
	
}

function setGroundTruth(data, width, height) {

var n0, n1, n2, n3, n4, n5, n6, n7;

var i, j, pt;
var pt_g = 0;
var b = 0;
var middle = (width*height)*0.5;

for (i=0; i<height; i++) {
    for(j=0; j<width; j++) {
    
	pt = (i*width*4)+(j*4);
	groundTruth[pt_g] = 1;

	if ( (data[pt] == 0) && (data[pt+1] == 0) && (data[pt+2] == 0) ) {
	    groundTruth[pt_g] = 0;
	    b++;
	}
	else if ( i == 0 || i == height-1 || j == 0 || j == width-1) {
	    groundTruth[pt_g] = 0;
	    b++;
	}
	else {
	    // neighbors
	    n0 = ((i-1)*width*4) + ((j-1)*4); // [i-1, j-1]
	    n1 = ((i-1)*width*4) + ((j)*4);   // [i-1, j]
	    n2 = ((i-1)*width*4) + ((j+1)*4); // [i-1, j+1]
		
	    n3 = (i*width*4) + ((j-1)*4); // [i, j-1]
	    n4 = (i*width*4) + ((j+1)*4); // [i, j+1]
		
	    n5 = ((i+1)*width*4) + ((j-1)*4); // [i+1, j-1]
	    n6 = ((i+1)*width*4) + ((j)*4);   // [i+1, j]
	    n7 = ((i+1)*width*4) + ((j+1)*4); // [i+1, j+1]

	    // black neighbor
	    if ( ((data[n0] == 0) && (data[n0+1] == 0) && (data[n0+2] == 0)) || ((data[n1] == 0) && (data[n1+1] == 0) && (data[n1+2] == 0)) ||
		 ((data[n2] == 0) && (data[n2+1] == 0) && (data[n2+2] == 0)) || ((data[n3] == 0) && (data[n3+1] == 0) && (data[n3+2] == 0)) ||
		 ((data[n4] == 0) && (data[n4+1] == 0) && (data[n4+2] == 0)) || ((data[n5] == 0) && (data[n5+1] == 0) && (data[n5+2] == 0)) ||
		 ((data[n6] == 0) && (data[n6+1] == 0) && (data[n6+2] == 0)) || ((data[n7] == 0) && (data[n7+1] == 0) && (data[n7+2] == 0)) ) {
			groundTruth[pt_g] = 0;
			b++;
	    }
	    else if (pt_g < middle) {
			ray.x = j;
			ray.y = i;
	    }
	}
	
	pt_g++;
    }
}

return b;
}


/* ----------------------------- save presentation --------------------------- */
function save() {

if (confirm("Salvar ?") == true) {
	savePresentation();
}
}

/* ---------------------------------- webGL ---------------------------------- */
var shaderProgram;
var canvas;
var gl;
var extd = null;

function initGL(canvas) {
	
try {
    gl = canvas.getContext("experimental-webgl");
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

extd = gl.getExtension("WEBGL_draw_buffers");

if (!extd) {
	alert("No WEBGL_draw_buffers support");
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

// selection
shaderProgram.offscreen = gl.getUniformLocation(shaderProgram, "offscreen");
shaderProgram.fragOut = gl.getUniformLocation(shaderProgram, "fragOut");
shaderProgram.show = gl.getUniformLocation(shaderProgram, "show");
shaderProgram.pMin = gl.getUniformLocation(shaderProgram, "pMin");
shaderProgram.pMax = gl.getUniformLocation(shaderProgram, "pMax");

shaderProgram.pCenter = gl.getUniformLocation(shaderProgram, "pCenter");
shaderProgram.rad = gl.getUniformLocation(shaderProgram, "rad");

if (mesh.selection.method == 2) {
	shaderProgram.vertexIndexAttribute = gl.getAttribLocation(shaderProgram, "aVertexIndex");
	gl.enableVertexAttribArray(shaderProgram.vertexIndexAttribute);
}

}

function webGLStart() {

canvas = document.getElementById("canvas3D");
initGL(canvas);
initFramebuffer();
initShaders();

loadModel();

loadTexture();

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

var width = window.innerWidth;// - (60+160+350); //570
var height = window.innerHeight;

var canvas = document.getElementById("canvas3D");
canvas.width = width;
canvas.height = height;

document.getElementById("canvas2D").style.width = width;
document.getElementById("canvas2D").style.height = height;

}

window.onload = function() {
	initMesh();
    initRoiList();
    initSelection(document.getElementById('canvas2D'));
    adjustCanvas();
    webGLStart();
};

window.onresize = function() {
    adjustCanvas();
};
</script>
    </head>
    <body>
        <!-- http://preloaders.net/en/circular -->
        <div id="divLoading" class="loading"></div>
        <div id="divScreen" style="display: none">
            <div class="title" style="display: flex;">
                <h1>Onça Wuaja</h1>
            </div>
            <div class="toolbar">
                <div class="button" id="select" onclick="roiSelection();" style="background-image:url(edit-buttons/select.png);"       onmousedown="this.style.backgroundImage='url(edit-buttons/select-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/select-over.png)'"></div>
                <div class="button" onclick="accept();"       style="background-image:url(edit-buttons/accept.png);" onmouseover="this.style.backgroundImage='url(edit-buttons/accept-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/accept.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/accept-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/accept-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/zoom-in.png);"    onclick="eventZoomIn();"   onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-in.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-in-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/zoom-out.png);"   onclick="eventZoomOut();"  onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-out.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-out-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/texture.png);"    onclick="eventTexture();"  onmouseover="this.style.backgroundImage='url(edit-buttons/texture-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/texture.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/texture-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/texture-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/turn-left.png);"  onclick="eventRotLeft();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'"       onmouseout="this.style.backgroundImage='url(edit-buttons/turn-left.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-left-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/turn-right.png);" onclick="eventRotRight();" onmouseover="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-right.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-right-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/turn-up.png);"    onclick="eventRotUp();"    onmouseover="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-up.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-up-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'"></div>
                <div class="button" style="background-image:url(edit-buttons/turn-down.png);"  onclick="eventRotDown();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-down.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-down-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'"></div>
            </div>
            <div id="divCanvas">
                <canvas id="canvas3D"></canvas>
                <div id="canvas2D"></div>
            </div>
	    <div id="roilist">
		<div class="roip" onclick="editMultimedia(0);"><span>Onça Wuaja</span></div>
            </div>
	    <div id="salveAll">
		<div class="roip" onclick="save()"><span>Salvar</span></div>
	    </div>
            <div id="popup">
		<div style="position: relative; width: 100%; height: 35px; line-height: 35px; padding: 0px 12px; color: white; background-color: black;margin-bottom: 5px" id="handle-header">		
			<font style="z-index: 999">Região de Interesse</font>
			<div style="position: absolute; top: 0; left: 0; width: 100%; height: 100%; z-index: 1000"></div>
		</div>
		<input id="titleROI" type="text" placeholder="Digite um título..." style="margin: 6px 12px; width: calc(100% - 24px);" />
		<hr style="border: none; border-bottom: dashed 1px gray; width: calc(100% - 24px);" />
                <div class="tab" style="padding: 0px 12px;">
                    <button class="tablinks" onclick="openTab(event, 'Texto')">Texto</button>
                    <button class="tablinks" onclick="openTab(event, 'Imagem')">Imagem</button>
                    <button class="tablinks" onclick="openTab(event, 'Video')">Video</button>
                </div>
                <div class="tab" style="height: 300px">
                    <div id="Texto" class="tabcontent">
                        <h3>Texto</h3>
			<textarea id="root-description" placeholder="Escreva o texto aqui." rows="13"
				style="margin:0!important;"></textarea>
                    </div>
                    <div id="Imagem" class="tabcontent">
                        <h3>Imagem</h3>
			<div class="file-upload">
                        	<span>Upload</span>
                        	<input type="file" class="upload" multiple onchange="handleFiles(this.files)" accept=".png, .jpg, .jpeg"/>
                        </div>
                        <div class="list-wrap" id="list-image">
                        	<table class="list" id="root-image">
					<tr>
						<td width="90%"></td>
						<td width="10%"></td>
                                        </tr>
				</table>
			</div>
                    </div>
                    <div id="Video" class="tabcontent">
                        <h3>Video</h3>
<form id="form">
                                    <div class="file-upload">
                                        <span>Upload</span>  
                                            <input type="file" class="upload" onchange="handleVideo(this.files)" accept=".mp4"/>
                                    </div>
                                </form>
                                <div class="list-wrap" id="list-video">
                                    <table class="list" id="video">
                                        <tr>
                                            <td width="90%"></td>
                                            <td width="10%"></td>
                                        </tr>
                                        <tr class="row">
                                            <td class="cell">exemplo</td>
                                            <td class="cell"><div class="remove" onclick="removeVideo();"></div></td></tr>
                                    </table>  
                                </div>
                    </div>
                </div>
		<hr style="border: none; border-bottom: dashed 1px gray; width: calc(100% - 24px);" />
                <div class="tab" style="padding: 6px 12px;">
                    <button style="width: 25%; border: solid 1px black;" onclick="closePopup()">Fechar</button>
			<button style="width: 25%; border: solid 1px black;margin-left: 10px;" onclick="salvarROI();">Salvar</button>	
                </div>
            </div>
        </div>

        <div id="divScreen2" style="display: none;"> <!--divScreen-->            
            <table>
                <tr>
                    <td width="160px">
                        <ul class="sidebar" id="bar">
                            <li class="sidebar-main" id="root-li" onclick="editMultimedia(0);">Onça Wuaja</li>
                        </ul>
                    </td>
                    <td width="350px">
                        <div class="multimedia-wrap">
                            <div class="panel-wrap" onclick="displayPanel(0);">
                                <h1>+ Texto</h1>
                            </div>
                            <div class="panel-inner closed" id="panel-text">
                                <textarea id="root-description" placeholder="Escreva o texto aqui."></textarea>
                            </div>
                            <div class="panel-wrap" onclick="displayPanel(1);">
                                <h1>+ Imagem</h1>
                            </div>
                            <div class="panel-inner closed" id="panel-image">
                                <div class="file-upload">
                                    <span>Upload</span>
                                    <input type="file" class="upload" multiple onchange="handleFiles(this.files)" accept=".png, .jpg, .jpeg"/>
                                </div>
                                <div class="list-wrap" id="list-image">
                                    <table class="list" id="root-image">
                                        <tr>
                                            <td width="90%"></td>
                                            <td width="10%"></td>
                                        </tr>
                                    </table>
                                </div>
                            </div>

                            <div class="panel-wrap" onclick="displayPanel(2);">
                                <h1>+ Video</h1>
                            </div>
                            <div class="panel-inner closed" id="panel-video">
                                <form id="form">
                                    <div class="file-upload">
                                        <span>Upload</span>  
                                            <input type="file" class="upload" onchange="handleVideo(this.files)" accept=".mp4"/>
                                    </div>
                                </form>
                                <div class="list-wrap" id="list-video">
                                    <table class="list" id="video">
                                        <tr>
                                            <td width="90%"></td>
                                            <td width="10%"></td>
                                        </tr>
                                        <tr class="row">
                                            <td class="cell">exemplo</td>
                                            <td class="cell"><div class="remove" onclick="removeVideo();"></div></td></tr>
                                    </table>  
                                </div>
                            </div>
                            <div class="save" onclick="save();">
                                <span>Salvar</span>
                            </div> 
                        </div>
                    </td>
                    <td width="60px">
                        
                    </td>
                    <td>
                        <div id="divCanvas">
                            <canvas id="canvas3D"></canvas>
                            <div id="canvas2D"></div>
                        </div>
                    </td>
                </tr>
            </table>
            <div id="preview" class="preview-image"></div>
            <canvas id="canvas-2d" style="z-index:1000; background-color:white;"></canvas>
        </div>

<<<<<<< HEAD
</head>
<body>

<!-- http://preloaders.net/en/circular -->
<div id="divLoading" class="loading"></div>

<div id="divScreen" style="display: none;"> <!--divScreen-->

  <table>
  <tr>
  <td width="160px">
  <ul class="sidebar" id="bar">
    <li class="sidebar-main" id="root-li" onclick="editMultimedia(0);">Onï¿½a Wuaja</li>
  </ul>
  </td>
  
  	

  <td width="350px">
  <div class="multimedia-wrap">
  
    <div class="panel-wrap" onclick="displayPanel(0);"><h1>+ Texto</h1></div>
    <div class="panel-inner closed" id="panel-text">
      <textarea id="root-description" placeholder="Escreva o texto aqui."></textarea>
    </div>
    
    <div class="panel-wrap" onclick="displayPanel(1);"><h1>+ Imagem</h1></div>
    <div class="panel-inner closed" id="panel-image">
      <div class="file-upload">
        <span>Upload</span>
        <input type="file" class="upload" multiple onchange="handleFiles(this.files)" accept=".png, .jpg, .jpeg"/>
      </div>
      <div class="list-wrap" id="list-image">
        <table class="list" id="root-image">
        <tr><td width="90%"></td><td width="10%"></td></tr>
        <!--  
        <tr class="row">
        <td class="cell">exemplo</td>
        <td class="cell"><div class="remove"></div></td></tr> -->
        </table>
      </div>
    </div>
    
    <div class="panel-wrap" onclick="displayPanel(2);"><h1>+ Video</h1></div>
    <div class="panel-inner closed" id="panel-video">
      <form id="form">
      <div class="file-upload">
        <span>Upload</span>  
        <input type="file" class="upload" onchange="handleVideo(this.files)" accept=".mp4"/>
      </div>
      </form>
      <div class="list-wrap" id="list-video">
        <table class="list" id="video">
        <tr><td width="90%"></td><td width="10%"></td></tr>
        
        <tr class="row">
        <td class="cell">exemplo</td>
        <td class="cell"><div class="remove" onclick="removeVideo();"></div></td></tr>
        </table>  
      </div>
    </div>
    
    <!-- <div id="preview" class="preview-image"></div> -->
    <div class="save" onclick="save();"><span>Salvar</span></div> 
  
  </div>
  </td>
  
  <td width="60px">
  <div class="toolbar">

	<div class="button" id="toggle_roi" onclick="toggleRoi();" style="width:50px; height:50px; margin:5px; background-image:url(edit-buttons/remove.png);"  onmouseup="this.style.backgroundImage='url(edit-buttons/remove3.png)'"><!-- onmouseout="this.style.backgroundImage='url(edit-buttons/select.png)'" onmouseover="this.style.backgroundImage='url(edit-buttons/select-over.png)'"--></div>
    <div class="button" id="select" onclick="roiSelection();" style="width:50px; height:50px; margin:5px; background-image:url(edit-buttons/select.png);" onmousedown="this.style.backgroundImage='url(edit-buttons/select.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/select-over.png)'"><!-- onmouseout="this.style.backgroundImage='url(edit-buttons/select.png)'" onmouseover="this.style.backgroundImage='url(edit-buttons/select-over.png)'"--></div>
    <div class="button" onclick="accept();"       style="margin:8px; background-image:url(edit-buttons/accept.png);" onmouseover="this.style.backgroundImage='url(edit-buttons/accept-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/accept.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/accept-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/accept-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/zoom-in.png);"    onclick="eventZoomIn();"   onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-in.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-in-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-in-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/zoom-out.png);"   onclick="eventZoomOut();"  onmouseover="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/zoom-out.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/zoom-out-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/zoom-out-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/texture.png);"    onclick="eventTexture();"  onmouseover="this.style.backgroundImage='url(edit-buttons/texture-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/texture.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/texture-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/texture-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/turn-left.png);"  onclick="eventRotLeft();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-left.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-left-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-left-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/turn-right.png);" onclick="eventRotRight();" onmouseover="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-right.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-right-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-right-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/turn-up.png);"    onclick="eventRotUp();"    onmouseover="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-up.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-up-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-up-over.png)'"></div>
    <div class="button" style="background-image:url(edit-buttons/turn-down.png);"  onclick="eventRotDown();"  onmouseover="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'" onmouseout="this.style.backgroundImage='url(edit-buttons/turn-down.png)'" onmousedown="this.style.backgroundImage='url(edit-buttons/turn-down-down.png)'" onmouseup="this.style.backgroundImage='url(edit-buttons/turn-down-over.png)'"></div>
    
  </div>
  </td>
  
  <td>
  <div id="divCanvas">
    <canvas id="canvas3D"></canvas>
    <div id="canvas2D"></div>
    <!-- <canvas id="temp-canvas"></dasdasdasdasdasd> -->
  </div>
  </td>
  
  </tr>
  </table>
  <div id="preview" class="preview-image"></div>
  <canvas id="canvas-2d" style="z-index:1000; background-color:white;"></canvas>
</div> 


</body>
=======
<script type="text/javascript">
dragElement(document.getElementById("popup"));

function dragElement(elmnt) {
  var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
  if (document.getElementById("handle-header")) {
    // if present, the header is where you move the DIV from:
    document.getElementById("handle-header").onmousedown = dragMouseDown;
  } else {
    // otherwise, move the DIV from anywhere inside the DIV:
    elmnt.onmousedown = dragMouseDown;
  }

  function dragMouseDown(e) {
    e = e || window.event;
    e.preventDefault();
    // get the mouse cursor position at startup:
    pos3 = e.clientX;
    pos4 = e.clientY;
    document.onmouseup = closeDragElement;
    // call a function whenever the cursor moves:
    document.onmousemove = elementDrag;
  }

  function elementDrag(e) {
    e = e || window.event;
    e.preventDefault();
    // calculate the new cursor position:
    pos1 = pos3 - e.clientX;
    pos2 = pos4 - e.clientY;
    pos3 = e.clientX;
    pos4 = e.clientY;
    // set the element's new position:
    elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
    elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
  }

  function closeDragElement() {
    // stop moving when mouse button is released:
    document.onmouseup = null;
    document.onmousemove = null;
  }
}

</script>
    </body>
>>>>>>> refs/heads/BranchRicardoGiovanni
</html>
