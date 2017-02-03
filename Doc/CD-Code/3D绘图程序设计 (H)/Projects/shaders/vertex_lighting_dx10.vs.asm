//
// Generated by Microsoft (R) HLSL Shader Compiler 9.22.949.2248
//
//
//   fxc c:\3DGraphicsProgramming\Projects\shaders\vertex_lighting_dx10.shader
//    /Tvs_4_0 /EVS /Zi /Fcvertex_lighting_dx10.vs.asm
//
//
// Buffer Definitions: 
//
// cbuffer Matrices
// {
//
//   row_major float4x4 viewproj_matrix;// Offset:    0 Size:    64
//   row_major float4x4 world_matrix;   // Offset:   64 Size:    64
//
// }
//
// cbuffer Lights
// {
//
//   float4 g_vGlobal_AmbientLight;     // Offset:    0 Size:    16
//   
//   struct
//   {
//       
//       float4 m_vPosition;            // Offset:   16
//       float4 m_vDirection;           // Offset:   32
//       float4 m_vAmbientColor;        // Offset:   48
//       float4 m_vDiffuseColor;        // Offset:   64
//       float4 m_vSpecularColor;       // Offset:   80
//       float4 m_vAttenuation;         // Offset:   96
//       float m_fSpotlightInnerCone;   // Offset:  112
//       float m_fSpotlightCutoffCosine;// Offset:  116
//       float m_fSpotlightExponent;    // Offset:  120
//       int m_iLightType;              // Offset:  124
//       bool m_bEnabled;               // Offset:  128
//
//   } g_Lights[3];                     // Offset:   16 Size:   372
//
// }
//
//
// Resource Bindings:
//
// Name                   Type  Format         Dim Slot Elements
// ---------------- ---------- ------- ----------- ---- --------
// Matrices            cbuffer      NA          NA    0        1
// Lights              cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name             Index   Mask Register SysValue Format   Used
// ---------------- ----- ------ -------- -------- ------ ------
// POSITION             0   xyzw        0     NONE  float   xyzw
// Normal               0   xyzw        1     NONE  float   xyz 
//
//
// Output signature:
//
// Name             Index   Mask Register SysValue Format   Used
// ---------------- ----- ------ -------- -------- ------ ------
// SV_POSITION          0   xyzw        0      POS  float   xyzw
// COLOR                0   xyzw        1     NONE  float   xyzw
//
vs_4_0
dcl_input v0.xyzw
dcl_input v1.xyz
dcl_output_siv o0.xyzw , position
dcl_output o1.xyzw
dcl_constantbuffer cb0[8], immediateIndexed
dcl_constantbuffer cb1[25], dynamicIndexed
dcl_temps 7
mul r0.xyzw, v0.yyyy, cb0[1].xyzw
mad r0.xyzw, v0.xxxx, cb0[0].xyzw, r0.xyzw
mad r0.xyzw, v0.zzzz, cb0[2].xyzw, r0.xyzw
mad o0.xyzw, v0.wwww, cb0[3].xyzw, r0.xyzw
mul r0.xyz, v0.yyyy, cb0[5].xyzx
mad r0.xyz, v0.xxxx, cb0[4].xyzx, r0.xyzx
mad r0.xyz, v0.zzzz, cb0[6].xyzx, r0.xyzx
mad r0.xyz, v0.wwww, cb0[7].xyzx, r0.xyzx
mul r1.xyz, v1.yyyy, cb0[5].xyzx
mad r1.xyz, v1.xxxx, cb0[4].xyzx, r1.xyzx
mad r1.xyz, v1.zzzz, cb0[6].xyzx, r1.xyzx
mov r2.x, l(1.000000)
mov r3.x, l(1.000000)
mov r4.xyzw, cb1[0].xyzw
mov r0.w, l(0)
loop 
  ige r1.w, r0.w, l(3)
  breakc_nz r1.w
  imul null, r1.w, r0.w, l(8)
  if_nz cb1[r1.w + 8].x
    switch cb1[r1.w + 7].w
      case l(1)
      dp3_sat r2.w, cb1[r1.w + 2].xyzx, r1.xyzx
      add r5.xyzw, r2.wwww, cb1[r1.w + 3].xyzw
      break 
      case l(2)
      add r6.xyz, -r0.xyzx, cb1[r1.w + 1].xyzx
      dp3 r2.z, r6.xyzx, r6.xyzx
      sqrt r2.y, r2.z
      div r6.xyz, r6.xyzx, r2.yyyy
      dp3_sat r2.w, r6.xyzx, r1.xyzx
      dp3 r2.y, r2.xyzx, cb1[r1.w + 6].xyzx
      div r2.y, r2.w, r2.y
      add r5.xyzw, r2.yyyy, cb1[r1.w + 3].xyzw
      break 
      case l(3)
      add r2.yzw, -r0.xxyz, cb1[r1.w + 1].xxyz
      dp3 r3.z, r2.yzwy, r2.yzwy
      sqrt r3.y, r3.z
      div r2.yzw, r2.yyzw, r3.yyyy
      dp3_sat r3.w, -cb1[r1.w + 2].xyzx, r2.yzwy
      ge r6.x, r3.w, cb1[r1.w + 7].y
      if_nz r6.x
        log r3.w, r3.w
        mul r3.w, r3.w, cb1[r1.w + 7].z
        exp r3.w, r3.w
        dp3_sat r2.y, r2.yzwy, r1.xyzx
        dp3 r2.z, r3.xyzx, cb1[r1.w + 6].xyzx
        mul r2.y, r3.w, r2.y
        div r2.y, r2.y, r2.z
        add r5.xyzw, r2.yyyy, cb1[r1.w + 3].xyzw
      else 
        mov r5.xyzw, cb1[r1.w + 3].xyzw
      endif 
      break 
      default 
      mov r5.xyzw, cb1[r1.w + 3].xyzw
      break 
    endswitch 
    mad r4.xyzw, r5.xyzw, cb1[r1.w + 4].xyzw, r4.xyzw
  endif 
  iadd r0.w, r0.w, l(1)
endloop 
mov o1.xyzw, r4.xyzw
ret 
// Approximately 65 instruction slots used
