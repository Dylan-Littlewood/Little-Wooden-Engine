// Basic UI Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform vec2 u_Screen;
uniform vec2 u_Offset;
uniform vec2 u_Size;
uniform vec4 u_BorderRadius;

out vec2 v_Position;
out vec4 v_BorderRadius;

float Map(float pixel, vec2 input, vec2 output)
{
	return output.x + ((output.y - output.x) / (input.y - input.x)) * (pixel - input.x);
}
vec2 RectRoot(vec2 pixelCoord, vec2 rectSize)
{
	return vec2(Map(pixelCoord.x,vec2(-1.0,1.0),vec2(0.0,rectSize.x)),Map(pixelCoord.y,vec2(-1.0,1.0),vec2(0.0,rectSize.y)));
}
vec2 Remap(vec2 pixels, vec2 screenSize)
{
	return vec2(Map(pixels.x,vec2(0.0,screenSize.x),vec2(-1.0,1.0)),Map(pixels.y,vec2(0.0,screenSize.y),vec2(1.0,-1.0)));
}
vec4 CheckBorders(vec4 brIn, vec2 size)
{
	float ratioA = brIn.x + brIn.y <= size.x ? 1.0 : size.x/(brIn.x + brIn.y);
	float ratioB = brIn.z + brIn.w <= size.x ? 1.0 : size.x/(brIn.z + brIn.w);
	float ratioC = brIn.x + brIn.w <= size.y ? 1.0 : size.y/(brIn.x + brIn.w);
	float ratioD = brIn.y + brIn.z <= size.y ? 1.0 : size.y/(brIn.y + brIn.z);

	float ratio = min(ratioA,min(ratioB,min(ratioC,ratioD)));
	return brIn.x * brIn.y * brIn.z * brIn.w < 0.0 ? vec4(0.0) : vec4(brIn.x * ratio, brIn.y * ratio, brIn.z * ratio, brIn.w * ratio);
}

void main()
{
	v_BorderRadius = CheckBorders(u_BorderRadius, u_Size);
	v_Position = RectRoot(a_Position.xy,u_Size);
	gl_Position = mat4(1.0) * vec4(Remap(v_Position + u_Offset,u_Screen),0.0, 1.0);
}	

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_Position;
in vec4 v_BorderRadius;

uniform vec2 u_Size;
uniform vec4 u_Color;


void main(){

	vec2 TLr = vec2(v_BorderRadius.x);
	vec2 TRr = vec2(u_Size.x,0.0) + vec2(-v_BorderRadius.y,v_BorderRadius.y);
	vec2 BRr = u_Size - vec2(v_BorderRadius.z);
	vec2 BLr = vec2(0.0,u_Size.y) + vec2(v_BorderRadius.w,-v_BorderRadius.w);

	float opacity = 1.0;
		opacity *= v_BorderRadius.x == 0.0 ? 1.0 : clamp(v_BorderRadius.x-distance(clamp(v_Position,vec2(0.0),TLr),TLr),0.0,1.0);
		opacity *= v_BorderRadius.y == 0.0 ? 1.0 : clamp(v_BorderRadius.y-distance(clamp(v_Position,vec2(TRr.x,0.0),vec2(u_Size.x,TRr.y)),TRr),0.0,1.0);
		opacity *= v_BorderRadius.z == 0.0 ? 1.0 : clamp(v_BorderRadius.z-distance(clamp(v_Position,BRr,u_Size),BRr),0.0,1.0);
		opacity *= v_BorderRadius.w == 0.0 ? 1.0 : clamp(v_BorderRadius.w-distance(clamp(v_Position,vec2(0.0,BLr.y),vec2(BLr.x,u_Size.y)),BLr),0.0,1.0);

	vec3 col = vec3(1.0);

	color = u_Color * vec4(1.0,1.0,1.0,opacity);
}
