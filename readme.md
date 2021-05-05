# **Map Merge Tool**

## Instructions to Run:
```bash
$ cd build/
$ cmake ..
$ make
```

./DisplayImage inputfile1 inputfile2 outputfile

```bash
$ ./DisplayImage figure/map2.1.pgm figure/map2.2.pgm result/output.pgm
```

To do stop, please ctrl+C

```bash
rotation: -0.0277336
translation (x,y): 0.11894, -0.956272
matrix: [1.001368923533066, -0.0004847044592732864, 0.1189402785106077;
 0.0004847044592732864, 1.001368923533066, -0.9562716407693578]
imwrite_('debug.pgm'): can't write data: OpenCV(4.1.1) /home/nvidia/host/build_opencv/nv_opencv/modules/imgcodecs/src/grfmt_pxm.cpp:427: error: (-5:Bad argument) Portable bitmap(.pgm) expects gray image in function 'write'

rotation: -0.0277336
translation (x,y): 0.11894, -0.956272
matrix: [1.001368923533066, -0.0004847044592732864, 0.1189402785106077;
 0.0004847044592732864, 1.001368923533066, -0.9562716407693578]
imwrite_('debug.pgm'): can't write data: OpenCV(4.1.1) /home/nvidia/host/build_opencv/nv_opencv/modules/imgcodecs/src/grfmt_pxm.cpp:427: error: (-5:Bad argument) Portable bitmap(.pgm) expects gray image in function 'write'

^C
```
## Result
![Screenshot from 2021-05-05 16-00-53](https://user-images.githubusercontent.com/52307432/117106967-c6290a00-adbb-11eb-9c0d-34a4b076ee35.png)


