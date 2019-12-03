/* ---------------------------------- model ---------------------------------- */

var uint32 = 4;
var int8 = 1;
var float32 = 4;

var vertexBuffer;
var normalBuffer;
var faceBuffer;

var colorBuffer;
var texCoordBuffer;

var numVertices;
var numFaces;

var vertices;
var normals;
var faces;

var colors;
var textureCoord;

var quantStep;
var bbMin;

var mMin = [1.0e37, 1.0e37, 1.0e37];
var mMax = [-1.0e37, -1.0e37, -1.0e37];

function loadColorModel(data) {
  var i, pt;
  var dv = new DataView(data);
  var ptDV = 0;

  numVertices = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numVertices <= 0) return;

  vertices = new Float32Array(numVertices * 3);
  normals = new Float32Array(numVertices * 3);
  colors = new Float32Array(numVertices * 3);

  for (i = 0, pt = 0; i < numVertices; i++, pt += 3) {
    vertices[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    normals[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    colors[pt] = dv.getUint8(ptDV, true) / 255;
    ptDV += int8;
    colors[pt + 1] = dv.getUint8(ptDV, true) / 255;
    ptDV += int8;
    colors[pt + 2] = dv.getUint8(ptDV, true) / 255;
    ptDV += int8;

    if (vertices[pt] < mMin[0]) mMin[0] = vertices[pt];
    if (vertices[pt] > mMax[0]) mMax[0] = vertices[pt];

    if (vertices[pt + 1] < mMin[1]) mMin[1] = vertices[pt + 1];
    if (vertices[pt + 1] > mMax[1]) mMax[1] = vertices[pt + 1];

    if (vertices[pt + 2] < mMin[2]) mMin[2] = vertices[pt + 2];
    if (vertices[pt + 2] > mMax[2]) mMax[2] = vertices[pt + 2];
  }

  numFaces = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numFaces <= 0) return;

  faces = new Uint32Array(numFaces * 3);

  for (i = 0, pt = 0; i < numFaces; i++, pt += 3) {
    faces[pt] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 1] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 2] = dv.getUint32(ptDV, true);
    ptDV += uint32;
  }

  //museu
  /*
	var numQuantBits = dv.getUint32(ptDV, true);
	ptDV += uint32;
	*/

  var extents = dv.getFloat32(ptDV, true);
  ptDV += float32;
  z = -extents;

  /*
	quantStep = extents / (1 << numQuantBits);
	z = -extents;

	bbMin = new Array(3);

	bbMin[0] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	bbMin[1] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	bbMin[2] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	*/

  vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  vertexBuffer.itemSize = 3;
  vertexBuffer.numItems = numVertices;

  normalBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);
  normalBuffer.itemSize = 3;
  normalBuffer.numItems = numVertices;

  faceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, faces, gl.STATIC_DRAW);
  faceBuffer.itemSize = 1;
  faceBuffer.numItems = numFaces * 3;

  colorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, colors, gl.STATIC_DRAW);
  colorBuffer.itemSize = 3;
  colorBuffer.numItems = numVertices;
}

function loadColorModelPLY(data) {
  var loader = new THREE.PLYLoader();
  const payload = loader.parse(data);

  numFaces = payload.indices.length / 3;
  numVertices = payload.vertices.length / 3;

  vertices = payload.vertices;

  var pMin = [1.0e37, 1.0e37, 1.0e37];
  var pMax = [-1.0e37, -1.0e37, -1.0e37];

  for (pt = 0; pt < vertices.length; pt += 3) {
    if (vertices[pt] < pMin[0]) pMin[0] = vertices[pt];
    if (vertices[pt] > pMax[0]) pMax[0] = vertices[pt];

    if (vertices[pt + 1] < pMin[1]) pMin[1] = vertices[pt + 1];
    if (vertices[pt + 1] > pMax[1]) pMax[1] = vertices[pt + 1];

    if (vertices[pt + 2] < pMin[2]) pMin[2] = vertices[pt + 2];
    if (vertices[pt + 2] > pMax[2]) pMax[2] = vertices[pt + 2];
  }

  // center the model
  var pExt = [pMax[0] - pMin[0], pMax[1] - pMin[1], pMax[2] - pMin[2]];
  extents = pExt[0];
  if (pExt[1] > extents) extents = pExt[1];
  if (pExt[2] > extents) extents = pExt[2];

  z = -(2 * extents);

  vertices = new Float32Array(payload.vertices);
  normals = new Float32Array(payload.normals);
  colors = new Float32Array(payload.colors);
  faces = new Uint32Array(payload.indices);

  vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  vertexBuffer.itemSize = 3;
  vertexBuffer.numItems = numVertices;

  normalBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);
  normalBuffer.itemSize = 3;
  normalBuffer.numItems = numVertices;

  faceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, faces, gl.STATIC_DRAW);
  faceBuffer.itemSize = 1;
  faceBuffer.numItems = numFaces * 3;

  colorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, colorBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, colors, gl.STATIC_DRAW);
  colorBuffer.itemSize = 3;
  colorBuffer.numItems = numVertices;
}

function loadTextureModel(data) {
  var i, pt;
  var dv = new DataView(data);
  var ptDV = 0;

  numVertices = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numVertices <= 0) return;

  vertices = new Float32Array(numVertices * 3);
  normals = new Float32Array(numVertices * 3);
  textureCoord = new Float32Array(numVertices * 2);

  var ptex;
  for (i = 0, pt = 0, ptex = 0; i < numVertices; i++, pt += 3, ptex += 2) {
    vertices[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    normals[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    textureCoord[ptex] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    textureCoord[ptex + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    if (vertices[pt] < mMin[0]) mMin[0] = vertices[pt];
    if (vertices[pt] > mMax[0]) mMax[0] = vertices[pt];

    if (vertices[pt + 1] < mMin[1]) mMin[1] = vertices[pt + 1];
    if (vertices[pt + 1] > mMax[1]) mMax[1] = vertices[pt + 1];

    if (vertices[pt + 2] < mMin[2]) mMin[2] = vertices[pt + 2];
    if (vertices[pt + 2] > mMax[2]) mMax[2] = vertices[pt + 2];
  }

  numFaces = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numFaces <= 0) return;

  faces = new Uint32Array(numFaces * 3);

  for (i = 0, pt = 0; i < numFaces; i++, pt += 3) {
    faces[pt] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 1] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 2] = dv.getUint32(ptDV, true);
    ptDV += uint32;
  }

  //museu
  /*
	var numQuantBits = dv.getUint32(ptDV, true);
	ptDV += uint32; */

  var extents = dv.getFloat32(ptDV, true);
  ptDV += float32;
  z = -extents;

  /*
	quantStep = extents / (1 << numQuantBits);

	bbMin = new Array(3);

	bbMin[0] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	bbMin[1] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	bbMin[2] = dv.getFloat32(ptDV, true);
	ptDV += float32;
	*/

  vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  vertexBuffer.itemSize = 3;
  vertexBuffer.numItems = numVertices;

  normalBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);
  normalBuffer.itemSize = 3;
  normalBuffer.numItems = numVertices;

  faceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, faces, gl.STATIC_DRAW);
  faceBuffer.itemSize = 1;
  faceBuffer.numItems = numFaces * 3;

  texCoordBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, texCoordBuffer);
  gl.bufferData(
    gl.ARRAY_BUFFER,
    new Float32Array(textureCoord),
    gl.STATIC_DRAW
  );
  texCoordBuffer.itemSize = 2;
  texCoordBuffer.numItems = numVertices;
}

function loadProgressiveModel(data) {
  var i, pt;
  var dv = new DataView(data);
  var ptDV = 0;
  var aux;

  numVertices = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numVertices <= 0) return;

  vertices = new Float32Array(numVertices * 3);
  normals = new Float32Array(numVertices * 3);

  for (i = 0, pt = 0; i < numVertices; i++, pt += 3) {
    vertices[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    vertices[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    normals[pt] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 1] = dv.getFloat32(ptDV, true);
    ptDV += float32;
    normals[pt + 2] = dv.getFloat32(ptDV, true);
    ptDV += float32;

    aux = dv.getInt8(ptDV, true);
    ptDV += int8;
    aux = dv.getInt8(ptDV, true);
    ptDV += int8;
    aux = dv.getInt8(ptDV, true);
    ptDV += int8;

    if (vertices[pt] < mMin[0]) mMin[0] = vertices[pt];
    if (vertices[pt] > mMax[0]) mMax[0] = vertices[pt];

    if (vertices[pt + 1] < mMin[1]) mMin[1] = vertices[pt + 1];
    if (vertices[pt + 1] > mMax[1]) mMax[1] = vertices[pt + 1];

    if (vertices[pt + 2] < mMin[2]) mMin[2] = vertices[pt + 2];
    if (vertices[pt + 2] > mMax[2]) mMax[2] = vertices[pt + 2];
  }

  numFaces = dv.getUint32(ptDV, true);
  ptDV += uint32;

  if (numFaces <= 0) return;

  faces = new Uint32Array(numFaces * 3);

  for (i = 0, pt = 0; i < numFaces; i++, pt += 3) {
    faces[pt] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 1] = dv.getUint32(ptDV, true);
    ptDV += uint32;
    faces[pt + 2] = dv.getUint32(ptDV, true);
    ptDV += uint32;
  }

  var numQuantBits = dv.getUint32(ptDV, true);
  ptDV += uint32;

  var extents = dv.getFloat32(ptDV, true);
  ptDV += float32;

  quantStep = extents / (1 << numQuantBits);
  z = -extents;

  bbMin = new Array(3);

  bbMin[0] = dv.getFloat32(ptDV, true);
  ptDV += float32;
  bbMin[1] = dv.getFloat32(ptDV, true);
  ptDV += float32;
  bbMin[2] = dv.getFloat32(ptDV, true);
  ptDV += float32;

  vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
  vertexBuffer.itemSize = 3;
  vertexBuffer.numItems = numVertices;

  normalBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, normals, gl.STATIC_DRAW);
  normalBuffer.itemSize = 3;
  normalBuffer.numItems = numVertices;

  faceBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, faceBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, faces, gl.STATIC_DRAW);
  faceBuffer.itemSize = 1;
  faceBuffer.numItems = numFaces * 3;
}

/* ---------------------------------- texture ---------------------------------- */
var colorTexture;
var cellTexture;

function initColorTexture(texture) {
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texImage2D(
    gl.TEXTURE_2D,
    0,
    gl.RGBA,
    gl.RGBA,
    gl.UNSIGNED_BYTE,
    texture.image
  );
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
  gl.bindTexture(gl.TEXTURE_2D, null);
}

function initTexture(texture, type, param) {
  gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texImage2D(gl.TEXTURE_2D, 0, type, type, gl.UNSIGNED_BYTE, texture.image);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, param);
  gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, param);
  gl.generateMipmap(gl.TEXTURE_2D);
  gl.bindTexture(gl.TEXTURE_2D, null);
}

/* ---------------------------------- off-screen rendering ---------------------------------- */

var texture;
var framebuffer;

function initFramebuffer() {
  var width = canvas.width;
  var height = canvas.height;

  texture = gl.createTexture();
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.texImage2D(
    gl.TEXTURE_2D,
    0,
    gl.RGB,
    width,
    height,
    0,
    gl.RGB,
    gl.UNSIGNED_BYTE,
    null
  ); //gl.RGBA

  var renderbuffer = gl.createRenderbuffer();
  gl.bindRenderbuffer(gl.RENDERBUFFER, renderbuffer);
  gl.renderbufferStorage(gl.RENDERBUFFER, gl.DEPTH_COMPONENT16, width, height);

  var framebuffer = gl.createFramebuffer();
  gl.bindFramebuffer(gl.FRAMEBUFFER, framebuffer);
  gl.framebufferTexture2D(
    gl.FRAMEBUFFER,
    gl.COLOR_ATTACHMENT0,
    gl.TEXTURE_2D,
    texture,
    0
  );
  gl.framebufferRenderbuffer(
    gl.FRAMEBUFFER,
    gl.DEPTH_ATTACHMENT,
    gl.RENDERBUFFER,
    renderbuffer
  );

  gl.bindTexture(gl.TEXTURE_2D, null);
  gl.bindRenderbuffer(gl.RENDERBUFFER, null);
  gl.bindFramebuffer(gl.FRAMEBUFFER, null);
}
