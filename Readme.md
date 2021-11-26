## PS

- The mainly point on this project is show how level of my comprehend for fragment SHADER.

- This project has some issue I can't solve else. cause I still comprehend all of principle in OpenGL.

  The issue is that I can't switch between different SHADER to render different object thus I only can use **Macro definition** to separate them in this case.

<img src=".\mdasset\MacroDefinition.png" alt="MacroDefinition" style="zoom: 80%;" />

------



<img src=".\mdasset\RollSpace.gif" alt="RollSpace" style="zoom:25%;" />

![figure1](.\mdasset\figure1.png)





The **figure 1-1** is the resource of texture and the other images is the each channel in this texture.

Saving the shape's information to each channel as mask then I can transform them separately.

The each operations of transform is position, position, scale.  The order of those operation is rotation, scale, position else you will get incorrect result. 



------



<img src=".\mdasset\WorldMap.gif" alt="WorldMap" style="zoom:25%;" />



![figure2](.\mdasset\figure2.png)

The **figure 2-1** is the resource of texture and the other images is the each channel in this texture.

figure 2-2 to figure 2-4 is applied simple rotation in coordinate of UV.



![figure3](.\mdasset\figure3.png)

On the alpha channel. I use a texture to convert standard UV to a sphere shape then sample the texture color. 

double the x-coordinate to separate forward side and back side, then use function  *SrcAlpha \* SrcColor + OneMinusSrcAlpha \* DestColor* to blend the color between forward and back.

