#version 430 
layout (location = 0) in vec3 aPos;

int main()
{
    gl_Position = vec4(aPos, 1.0f);
}


acc num: 10096766