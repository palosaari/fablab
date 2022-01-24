# 3. Computer Aided design

This week task was to study and evaluate different design tools - raster, vector, 2D and 3D. My personal needs are mostly 3D design so I did more testing and evaluation on that side. Selected design tools are: GIMP, Inkscape and FreeCAD.

## GIMP

Basic picture editing tool selected was simply GIMP (GNU Image Manipulation Program). I have used it earlier, it comes with Linux distribution used and it does the job. I think I don't even need it much during these courses.

![](../images/week03/gimp.png)

```console
sudo dnf install gimp
```

## Inkscape

Inkscape is a vector graphics editor I selected. It was natural choice as it was available from my OS package manager and it is rather feature rich. I am not sure how much I will need that kind of 2D vector graphic design tool still - probably for the laser cutter at least.

As a test, I quickly draw simple half wave dipole antenna around 1000 MHz (not simulated not even calculated accurate, just a concept). I wonder if it is possible to laser cut that kind of small antennas from few millimeter thick aluminum plate...

![](../images/week03/inkscape.png)

```console
sudo dnf install inkscape
```

[dipole antenna.svg](../images/week03/dipole antenna.svg)


## FreeCAD

3D design tool is one I likely need most. Here I evaluated Fusion 360 and FreeCAD. I had too much problems with Fusion 360. Firstly, Fusion 360 does not have Linux version and secondly that mess about user account. I tried it with Wine (Windows API implementation for Linux) but not very great results. It worked somehow, but feeling was a bit buggy. Also registration for Autodesk in order to get license was a bit tricky and you have to send some proofs (like picture of student id) in order to get education license. And for some reason it still started 30 days trial version of Fusion 360 even "You’re eligible for free one-year educational access to Autodesk products through the Autodesk Education Community.".

So I eventually switched to FreeCAD. My only earlier experience of 3D modeling I had was some experience modelling antennas using CST Studio. FreeCAD feels totally different which means learning curve will be rather heavy. After looking some tutorials from YouTube I was finally able to made simple design. It wasn't any part for my final project, but something useful still - it is cover plate for light switch. I need that as I have replaced manual light switches with smart ones that are controlled via home automation.

3D design made was build from 4 different blocks. All blocks were first drawn as 2D sketch and then converted to 3D model. First block was "Pad" which covers outlines of whole part. Then rest of three blocks were "Pocket" which are then removed from the Pad by boolean style operation.

![](../images/week03/freecad.png)

```console
sudo dnf install freecad
```

[ABB Cover frame Jussi Impressivo.FCStd](../images/week03/ABB Cover frame Jussi Impressivo.FCStd)

[ABB Cover frame Jussi Impressivo.stl](../images/week03/ABB Cover frame Jussi Impressivo.stl)


