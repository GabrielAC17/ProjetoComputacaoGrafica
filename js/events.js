var mvMatrix = mat4.create();
var mvMatrixStack = [];
var pMatrix = mat4.create();
var mvMatrixInverse = mat4.create();
var normalMatrix = mat3.create();

function mvPushMatrix() {
var copy = mat4.create();
mat4.set(mvMatrix, copy);
mvMatrixStack.push(copy);
}

function mvPopMatrix() {
if (mvMatrixStack.length == 0) {
	throw "Invalid popMatrix!";
}
mvMatrix = mvMatrixStack.pop();
}

function setMatrixUniforms() {
gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);

mat4.inverse(mvMatrix, mvMatrixInverse);
gl.uniformMatrix4fv(shaderProgram.mvMatrixInverseUniform, false, mvMatrixInverse);

mat4.toInverseMat3(mvMatrix, normalMatrix);
mat3.transpose(normalMatrix);
gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, normalMatrix);
}

var rot = {x: 0.0, y: 0.0, z: 0.0, s: 1.0};
var dest = {x: 0.0, y: 0.0, z: 0.0, s: 1.0};
var rotMatrix = new glMatrixArrayType(16);

function dotProduct(q1,q2) {
return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.s*q2.s;
}

function length(q) {
return Math.sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.s*q.s);
}

/* slerp */
function interpolation(t) {

var dot = dotProduct(rot,dest);

if (dot < 0) {
	dot = -dot;
	dest.x = dest.x*(-1);
	dest.y = dest.y*(-1);
	dest.z = dest.z*(-1);
}

if (dot <= 0.99) {

	var theta, st, sut, sout, coeff1, coeff2;
	//t=t/2.0;

	theta = Math.acos(dot);

	if (theta<0.0) {
		theta=-theta;
		console.log("theta");
	}
		
	st = Math.sin(theta);
	sut = Math.sin(t*theta);
	sout = Math.sin((1-t)*theta);
	coeff1 = sout/st;
	coeff2 = sut/st;

	rot.x = coeff1*rot.x + coeff2*dest.x;
	rot.y = coeff1*rot.y + coeff2*dest.y;
	rot.z = coeff1*rot.z + coeff2*dest.z;
	rot.s = coeff1*rot.s + coeff2*dest.s;

	var len = length(rot);
	if ( !((len < 1.0e-10) || isNaN(rot.x) || isNaN(rot.y) || isNaN(rot.z) || isNaN(rot.s)) ) {
		len = 1.0 / len;
		rot.x = rot.x * len;
		rot.y = rot.y * len;
		rot.z = rot.z * len;
		rot.s = rot.s * len;
	}
}
else {
	lerp(t);
}

}

function lerp(t) {
	
//((q1 + t*(q2-q1)).normalize());
rot.x =	rot.x + t*(dest.x - rot.x);
rot.y =	rot.y + t*(dest.y - rot.y);
rot.z =	rot.z + t*(dest.z - rot.z);
rot.s =	rot.s + t*(dest.s - rot.s);

var len = length(rot);
if ( !((len < 1.0e-10) || isNaN(rot.x) || isNaN(rot.y) || isNaN(rot.z) || isNaN(rot.s)) ) {
	len = 1.0 / len;
	rot.x = rot.x * len;
	rot.y = rot.y * len;
	rot.z = rot.z * len;
	rot.s = rot.s * len;
}

}

function preRotateX(angle) {

var sinAngle, cosAngle, x, y, z, w;

angle   *= 0.5;
cosAngle = Math.cos(angle);
sinAngle = Math.sin(angle);
w = cosAngle*rot.s - sinAngle*rot.x;
x = cosAngle*rot.x + sinAngle*rot.s;
y = cosAngle*rot.y - sinAngle*rot.z;
z = cosAngle*rot.z + sinAngle*rot.y;
rot.s = w;
rot.x = x;
rot.y = y;
rot.z = z;
//alert("rot: x = " + rot.x + " y = " + rot.y + " z = " + rot.z + " s = " + rot.s);
}

function preRotateY(angle) {

var sinAngle, cosAngle, x, y, z, w;

angle   *= 0.5;
cosAngle = Math.cos(angle);
sinAngle = Math.sin(angle);
w = cosAngle*rot.s - sinAngle*rot.y;
x = cosAngle*rot.x + sinAngle*rot.z;
y = cosAngle*rot.y + sinAngle*rot.s;
z = cosAngle*rot.z - sinAngle*rot.x;
rot.s = w;
rot.x = x;
rot.y = y;
rot.z = z;
//alert("rot: x = " + rot.x + " y = " + rot.y + " z = " + rot.z + " s = " + rot.s);
}

function glMatrix() {

var wx, wy, wz, xx, xy, xz, yy, yz, zz;

wx = rot.s * rot.x * 2.0;
wy = rot.s * rot.y * 2.0;
wz = rot.s * rot.z * 2.0;
xx = rot.x * rot.x * 2.0;
xy = rot.x * rot.y * 2.0;
xz = rot.x * rot.z * 2.0;
yy = rot.y * rot.y * 2.0;
yz = rot.y * rot.z * 2.0;
zz = rot.z * rot.z * 2.0;
rotMatrix[0]  = 1.0 - (yy + zz);
rotMatrix[1]  = xy + wz;
rotMatrix[2]  = xz - wy;
rotMatrix[3]  = 0.0;
rotMatrix[4]  = xy - wz;
rotMatrix[5]  = 1.0 - (xx + zz);
rotMatrix[6]  = yz + wx;
rotMatrix[7]  = 0.0;
rotMatrix[8]  = xz + wy;
rotMatrix[9]  = yz - wx;
rotMatrix[10] = 1.0 - (xx + yy);
rotMatrix[11] = 0.0;
rotMatrix[12] = 0.0;
rotMatrix[13] = 0.0;
rotMatrix[14] = 0.0;
rotMatrix[15] = 1.0;

}

/* ------------------------ mouse ----------------------- */

function degToRad(degrees) {
return degrees * Math.PI / 180;
}

var mouseDown = false;
var lastMouseX = null;
var lastMouseY = null;
var rotationMatrix = mat4.create();
mat4.identity(rotationMatrix);

function handleMouseDown(event) {
mouseDown = true;
lastMouseX = event.clientX;
lastMouseY = event.clientY;
}

function handleMouseUp(event) {
mouseDown = false;
}

function handleMouseMove(event) {

if (!mouseDown) {
    return;
}
        
var newX = event.clientX;
var newY = event.clientY;
var deltaX = newX - lastMouseX;
var deltaY = newY - lastMouseY;

preRotateX(degToRad(deltaY*0.5));
preRotateY(degToRad(deltaX*0.5));

lastMouseX = newX;
lastMouseY = newY;
}

function handleMouseWheel(event) {

var wheelDirection = function(evt) {
if (!evt) evt = event;
    return (evt.detail<0) ? 1 : (evt.wheelDelta>0) ? 1 : -1;
};
        
if (wheelDirection(event) == 1) {
    eventZoomIn();
}
else if (wheelDirection(event) == -1) {
    eventZoomOut();
}

}

/* ------------------------ touch ----------------------- */
var drag = 0;
var lastTouchX = 0;
var lastTouchY = 0;

function startTouch(evt) {
 
var evList = evt.touches;

if (evList.length == 1) { // one finger touch
	lastTouchX = evList[0].pageX;  
	lastTouchY = evList[0].pageY;
	drag = 1;
}
else if (evList.length == 2) { // two fingers touch
	drag = 2;
}
evt.preventDefault();

}

function continueTouch(evt) {

if (drag == 1) {
	var newX = evt.touches[0].pageX;
	var newY = evt.touches[0].pageY;
	var deltaX = newX - lastTouchX;
	var deltaY = newY - lastTouchY;
	var newRotationMatrix = mat4.create();

	mat4.identity(newRotationMatrix);
	mat4.rotate(newRotationMatrix, degToRad(deltaX*0.5), [0, 1, 0]);
	mat4.rotate(newRotationMatrix, degToRad(deltaY*0.5), [1, 0, 0]);

	mat4.multiply(newRotationMatrix, rotationMatrix, rotationMatrix);

	lastTouchX = newX;
	lastTouchY = newY;
}

}

function stopTouch() {
drag = 0;
}

/* ------------------------ keys and icons ----------------------- */
var x = 0.0;
var y = 0.0;
var z = 0.0;
var textureoff = 0;
var lighting = 1;
var currentlyPressedKeys = {};

function handleKeyDown(event) {
currentlyPressedKeys[event.keyCode] = true;
}

function handleKeyUp(event) {
currentlyPressedKeys[event.keyCode] = false;
}

function handleKeys() {

if (currentlyPressedKeys[33]) {
// Page Up
eventZoomIn();
}
if (currentlyPressedKeys[34]) {
// Page Down
eventZoomOut();
}
if (currentlyPressedKeys[37]) {
// Left cursor key
eventRotLeft();	
}
if (currentlyPressedKeys[39]) {
// Right cursor key
eventRotRight();
}
if (currentlyPressedKeys[38]) {
// Up cursor key
eventRotUp();
}
if (currentlyPressedKeys[40]) {
// Down cursor key
eventRotDown();
}

if (currentlyPressedKeys[65]) {
animating = true;
}

}

function eventTexture() {
textureoff = !textureoff;
}

function eventLighting() {
lighting = !lighting;
}

function eventZoomIn() {
z = z * (1.0/1.1);
}
function eventZoomOut() {
z = z * 1.1;
}
function eventMovUp() {
y -= z * 0.05;
}
function eventMovDown() {
y += z * 0.05;
}
function eventMovLeft() {
x += z * 0.05;
}
function eventMovRight() {
x -= z * 0.05;
}

function eventRotUp() {
preRotateX(degToRad(5.0));
}

function eventRotDown() {
preRotateX(degToRad(-5.0));
}

function eventRotLeft() {
preRotateY(degToRad(5.0));
}

function eventRotRight() {
preRotateY(degToRad(-5.0));
}


var t_zoom = new Date().getTime();
var lastTime = 0;
var animating = false;

function animate() {
	
var timeNow = new Date().getTime();

if (lastTime != 0) {
    var elapsed = timeNow - lastTime;
    preRotateY(degToRad((90 * elapsed) / 2000.0));
	
    var t_zoom_now = timeNow - t_zoom;
    if (t_zoom_now > 6000 && t_zoom_now < 12000) {
	z += 1.2;
	y += z * 0.0008;
    }
    if (t_zoom_now > 18000 && t_zoom_now < 24000) {
	y -= z * 0.001;
    }
    if (t_zoom_now > 30000 && t_zoom_now < 36000) {
	y -= z * 0.0012;
    }
    if (t_zoom_now > 40000 && t_zoom_now < 46000) {
	z -= 1.2;
	y += z * 0.0008;
    }
    if (t_zoom_now > 51300) {
	animating = false;
    }
}

lastTime = timeNow;
}

