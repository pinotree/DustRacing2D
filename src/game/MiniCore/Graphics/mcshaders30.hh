// This file belongs to the "MiniCore" game engine.
// Copyright (C) 2013 Jussi Lind <jussi.lind@iki.fi>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA.
//

#ifndef MCSHADERS30_HH
#define MCSHADERS30_HH

static const char * MCDefaultVsh =
"#version 130\n"
"in      vec3  inVertex;\n"
"in      vec3  inNormal;\n"
"in      vec2  inTexCoord;\n"
"in      vec4  inColor;\n"
"uniform vec4  scale;\n"
"uniform vec4  color;\n"
"uniform mat4  vp;\n"
"uniform mat4  model;\n"
"uniform float fade;\n"
"uniform vec4  dd;\n"
"uniform vec4  dc;\n"
"uniform vec4  ac;\n"
"out     vec2  texCoord0;\n"
"out     vec4  vColor;\n"
""
"void main()\n"
"{"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
""
"    mat4 normalRot = mat4(mat3(model));\n"
"    float di = dot(dd, normalRot * vec4(-inNormal, 1)) * dc.a;\n"
"    vColor = inColor * color * (\n"
"        vec4(ac.rgb, 1.0) * ac.a +\n"
"        vec4(dc.rgb, 1.0) * di) * vec4(fade, fade, fade, 1.0);\n"
""
"    texCoord0 = inTexCoord;\n"
"}\n";

static const char * MCDefaultVshSpecular =
"#version 130\n"
""
"attribute vec3  inVertex;\n"
"attribute vec3  inNormal;\n"
"attribute vec2  inTexCoord;\n"
"attribute vec4  inColor;\n"
"uniform   vec4  scale;\n"
"uniform   vec4  color;\n"
"uniform   mat4  vp;\n"
"uniform   mat4  v;\n"
"uniform   mat4  model;\n"
"uniform   float fade;\n"
"uniform   vec4  dd;\n"
"uniform   vec4  dc;\n"
"uniform   vec4  sd;\n"
"uniform   vec4  sc;\n"
"uniform   vec4  ac;\n"
"uniform   float sCoeff;\n"
"varying   vec2  texCoord0;\n"
"varying   vec4  vColor;\n"
""
"void main()\n"
"{"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
""
"    mat4 normalRot = mat4(mat3(model));\n"
"    float di = dot(dd, normalRot * vec4(-inNormal, 1)) * dc.a;\n"
""
"    vec3 vNormalEye = (v * model * vec4(inNormal, 1)).xyz;\n"
"    vec3 vVertexEye = (v * model * vec4(inVertex, 1) * scale).xyz;\n"
""
"    vec3 eye = vec3(0, 0, 1);\n"
"    vec3 pos = vVertexEye;\n"
"    vec3 V   = normalize(eye - pos);\n"
"    vec3 L   = normalize(eye);\n"
"    vec3 N   = normalize(-vNormalEye);\n"
""
"    float si = 0.0;\n"
"    if (dot(N, L) > 0.0)\n"
"    {\n"
"        vec3 R = (N * dot(N, L) * 2.0) - L;\n"
"        si = max(0.0, pow(dot(R, V), sCoeff));\n"
"    }\n"
""
"    vColor = (inColor * color * (\n"
"        vec4(ac.rgb, 1.0) * ac.a +\n"
"        vec4(dc.rgb, 1.0) * di) + vec4(sc.xyz, 1.0) * si) * vec4(fade, fade, fade, 1.0);\n"
""
"    texCoord0 = inTexCoord;\n"
"}\n";

static const char * MCDefaultFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"in      vec2      texCoord0;\n"
"in      vec4      vColor;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 texColor = texture2D(tex0, texCoord0);\n"
"    if (texColor.a < 0.1)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        fragColor = vColor * texColor;\n"
"    }\n"
"}\n";

static const char * MCDefaultShadowVsh =
"#version 130\n"
""
"in      vec3 inVertex;\n"
"in      vec3 inNormal;\n"
"in      vec2 inTexCoord;\n"
"in      vec4 inColor;\n"
"uniform vec4 scale;\n"
"uniform vec4 color;\n"
"uniform mat4 vp;\n"
"uniform mat4 model;\n"
"out     vec2 texCoord0;\n"
"out     vec4 vColor;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
"    vColor      = inColor * color;\n"
"    texCoord0   = inTexCoord;\n"
"}\n";

static const char * MCDefaultShadowFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"in      vec2      texCoord0;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 color = texture2D(tex0, texCoord0);\n"
"    if (color.a < 0.1)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        fragColor = vec4(0.0, 0.0, 0.0, 0.6);\n"
"    }\n"
"}\n";

static const char * MCDefaultParticleFsh =
"#version 130\n"
""
"in  vec4 vColor;\n"
"out vec4 fragColor;\n"
""
"void main(void)\n"
"{\n"
"    fragColor = vColor;\n"
"}\n";

static const char * MCDefaultPointParticleVsh =
"#version 130\n"
""
"in      vec3  inVertex;\n"
"in      vec3  inNormal;\n"
"in      vec4  inColor;\n"
"uniform mat4  vp;\n"
"uniform float fade;\n"
"uniform float pointSize;\n"
"out     mat2  rotationMatrix;\n"
"out     vec4  vColor;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * vec4(inVertex, 1);\n"
"    gl_PointSize = pointSize * inVertex.z;\n"
"    vColor = inColor * fade;\n"
"    // Rotation matrix to rotate a point sprite (sin and cos delivered as normals)\n"
"    rotationMatrix = mat2(inNormal.x, inNormal.y, -inNormal.y, inNormal.x);\n"
"}\n";

static const char * MCDefaultPointParticleFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"in      vec4      vColor;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    fragColor = texture2D(tex0, gl_PointCoord) * vColor;\n"
"}\n";

static const char * MCDefaultPointParticleRotateFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"in      vec4      vColor;\n"
"in      mat2      rotationMatrix;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 texColor = texture2D(tex0, rotationMatrix * gl_PointCoord) * vColor;\n"
"    fragColor = texColor;\n"
"}\n";

static const char * MCDefaulTextVsh =
"#version 130\n"
""
"in      vec3  inVertex;\n"
"in      vec3  inNormal;\n"
"in      vec2  inTexCoord;\n"
"in      vec4  inColor;\n"
"uniform vec4  scale;\n"
"uniform vec4  color;\n"
"uniform mat4  vp;\n"
"uniform mat4  model;\n"
"uniform float fade;\n"
"out     vec2  texCoord0;\n"
"out     vec4  vColor;\n"
""
"void main()\n"
"{\n"
"    gl_Position = vp * model * (vec4(inVertex, 1) * scale);\n"
"    vColor      = inColor * color * fade;\n"
"    texCoord0   = inTexCoord;\n"
"}\n";

static const char * MCDefaultTextShadowFsh =
"#version 130\n"
""
"uniform sampler2D tex0;\n"
"in      vec2      texCoord0;\n"
"out     vec4      fragColor;\n"
""
"void main(void)\n"
"{\n"
"    vec4 color = texture2D(tex0, texCoord0);\n"
"    if (color.a < 0.1)\n"
"    {\n"
"        discard;\n"
"    }\n"
"    else\n"
"    {\n"
"        fragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
"    }\n"
"}\n";

#endif // MCSHADERS30_HH
