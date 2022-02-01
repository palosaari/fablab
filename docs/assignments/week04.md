# 4. Computer controlled cutting

## Weekly task

This week went training with vinyl cutter and laser cutter and related design software. We started studying vinyl cutter basics and after that did same for the laser cutter. Most of the time went still learning laser cutting as that process is more complex starting from the 3D-modelling process.

## Vinyl cutting

Vinyl cutter is printer look-a-like machine that has small knife in order to cut rather thin and soft material. Typically that material is just vinyl tape which is cut to some stickers.

Used vinyl cutter was Roland CAMM-1 GS-24 and it was controlled by Windows workstation.

![](../images/week04/roland_gs24.resized.jpg)

Usually cutter is connected to computer like a printer using printer driver made for the device. So instead of printing, it will cut. Printed document needs to be converted some vector format. Line width didn't seems to have any requirement at our test, it just cuts where the line center line was. Anyhow, printer driver API is for printers and does not fit 100% well other use cases like that, so be warned there may be device vendor specific tricks which are varying from manufacturer to other and so.

As a vinyl cutting exercise I made some Pokemon Go Team Valor logo stickers. I downloaded suitable existing logo which was a red colored raster image on transparent background in .png format. Then I used Inkscape Trace Bitmap tool to "cut" border of from that logo in order to get vector image from logo borders. That vector image was then cut using vinyl cutter.


Here is original image used [Valor logo](https://www.seekpng.com/ima/u2q8u2i1t4u2q8t4/)

And vector image converted from original [Valor logo](../images/week04/pokemon_valor_logo.svg)

![](../images/week04/stickers.resized.jpg)


## Laser cutting

### Kerf

Kerf is term for "extra" material removed by the cutting process itself. On ideal case cutting process does nothing but cuts your material as desired, but on real life there is very often mechanical or some other process that removes material. That is for example saw blade or laser beam. So if your saw blade is 1mm wide it will remove that much material and it is said that 1mm kerf is removed. Same applies for laser beam too as it burns material during cutting process. Kerf should be taken into account when that small amounts of extra removed material is essential.

#### Kerf test for Acrylic 3mm

I ran test for 3mm Acrylic plate. I got two different results depending how I ordered those 10 small pieces. Laser beam cut/kerf is not constant - it is wider on top side and a little bit smaller on bottom side. Larger calculated kerf is got when every other piece is upside-down and it is about double of size compared to another. Larger kerf value, 0.136mm, seems to be more realistic in real life on that case - think why and how it does.

```
>> (100-99.45)/10
ans =  0.055000
>> (100-98.64)/10
ans =  0.13600
```

![](../images/week04/IMG_20220131_010329.resized.jpg)
![](../images/week04/IMG_20220131_010530.resized.jpg)


### Focus test

Some test were made how focus effects to cutting. +/-2mm and +/-4mm offsets were tested to plywood. Laser is usually calibrated that most of the power is on focus. Due to that, more off the material is from focus the less the power it gets. 4mm offset with used settings caused it does not cut through anymore on one test.
![](../images/week04/laser_focus.resized.jpg)


### Power, frequency, speed tests

Test made how different laser parameters effects to cut and engrave. All these 3 parameters have some relation for operation result. If you for example decrease power you can/should also decrease speed in order to succeed same thickness material cut.

Test plate shows how increased speed eventually fails cut. On test plate you can see same happens for decreased power too.

![](../images/week04/laser_test.resized.jpg)


### 3D model of simple block

I used FreeCAD to design simple brick having 4 joints, one for each side. I saw this kind of pieces on lab so I decided to go where it was easiest. First I made 2D sketch on FreeCAD. Then draw outline of part using polyline tool on sketcher. After that I added constraint for horizontal and vertical lines. Then symmetry around center point of XY-plane. Then I added equal length constraint of all similar length lines. And finally parametrized that slot width. 

![](../images/week04/FreeCAD_sketch.resized.png)


Spreadsheet is created for the kerf and material thickness parameters. It may be a bit overkill for this small design but parametric design principles were required so here it is in all flavors.

Technically, that FreeCAD spreadsheet contains formula slotwidth = thickness - kerf, which can be seen on picture. Then parameter 'slotwidth' from spreadsheet is used on sketch to define slot width for one slot. Other 3 slots on the sketch are set same size as constraint so same value propagates that way to all slots on design.

![](../images/week04/FreeCAD_parametric1.resized.png)
![](../images/week04/FreeCAD_parametric2.resized.png)

It was somehow difficult to export sketch or 3D model outlines as vector format needed for laser cutter. On ideal case you just need to save/export it some format and that's all - but it is far from that. The way I did it was I made FreeCAD TehcnicalDrawing from part and exported it as a .svg (small button on bar, hardly visible on attached picture). After that you can edit it on Inkscape, change line width to 0.02mm required by laser (if line width is too large laser refuses and does error beep). From Inkscape save drawing as a .pdf and use laser printer workstation to print it.

I still wonder if there really is better tool chain to do all these tasks a bit more automatically.
![](../images/week04/FreeCAD_techdraw.resized.png)
![](../images/week04/FreeCAD_block.resized.png)


#### Download design:

* [block.FCStd](../images/week04/block.FCStd)
* [block.stl](../images/week04/block.stl)
* [block.pdf](../images/week04/block.pdf)

### Laser cutting

Laser used was Epilog Fusion M2 40.

3D model from FreeCAD was imported to laser using following steps:

* Design workstation; Export FreeCAD Technical Drawing to vector format .svg
* Design workstation; Import .svg to Inkscape
* Design workstation; Edit line width to 0.02mm and check outlines
* Design workstation; Save as .pdf
* Laser cutter; turn on (air intake on, air outlet on, laser power on)
* Laser workstation; Open .pdf
* Laser workstation; Select printer and edit printer (laser) settings
* Laser workstation; Load correct laser settings per material used (you should not need to define your own settings as there is existing settings for most common materials)
* Laser workstation; Send printer work to laser
* Laser cutter; JOG. It is staring point of your laser print - upper left corner of document you sent to laser. There is red laser pointer showing exact point, use joystick to adjust.
* Laser cutter; FOCUS. It is distance between laser beam and material. Mechanical triangle tool is for that. Use joystick to adjust, moves bed up/down.
* Laser cutter; JOB. That's is printing document queue received by the laser machine. Select your job - it is likely the last one.
* Laser cutter; GO. Start cutting.
* Laser cutter; Wait minute or so after laser is finished before opening the lid. That's in order to get all burning products like dangerous smoke to get removed from the machine.

Unfortunately there is very many things you can do wrong. It must be very careful with safety issues when working with laser cutter. Always do the basic checks mentioned on many places near laser (air intake, air outlet) and check the material compatibility. Check where fire blanket is and make plan on your head what you will do if it starts burning before you start cutting.

Laser cut blocks in random configuration. If something useful is needed then these blocks can be reconfigured as a kettle base :-)

![](../images/week04/laser_work1.resized.jpg)

## Design files
* [pokemon_valor_logo.svg](../images/week04/pokemon_valor_logo.svg)
* [block.FCStd](../images/week04/block.FCStd)
* [block.stl](../images/week04/block.stl)
* [block.pdf](../images/week04/block.pdf)

## Summary
TOO MUCH WORK. This week was terrible amount of things. Something should be reduced. I would reduce the documentation and focus more learning.
