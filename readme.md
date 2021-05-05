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
![117106967-c6290a00-adbb-11eb-9c0d-34a4b076ee35](https://user-images.githubusercontent.com/52307432/117110067-929cae80-adc0-11eb-83cb-d5ccc30ede20.png)

![117107003-d80aad00-adbb-11eb-9d4c-1b53bc453d72](https://user-images.githubusercontent.com/52307432/117110212-beb82f80-adc0-11eb-8c70-e49bf1c09bd2.png)

## Create yaml file
マップはYAMLファイルの設定と、マップ本体の画像ファイルのペアで管理されます。

画像ファイルはグレーが濃いほど障害物として扱われます。
そのスレッショルドはYAMLファイルで決定します。
画像ファイルはカラーでもグレーでもどっちでもいいみたいです。

ROSメッセージとしてはoccupancyは0~100の数値（0がフリーで100が完全に壁)で表されます。また、未観測領域は-1になります。

画像ファイルのフォーマットはSDLで読み込めるものならなんでもいいです。

YAMLファイルは以下のようなかんじです。

image: testmap.png
resolution: 0.1
origin: [0.0, 0.0, 0.0]
occupied_thresh: 0.65
free_thresh: 0.196
negate: 0

image: イメージファイル（YAMLからの相対・もしくは絶対パス）
resolution: [meters/pixel]
origin: マップの左下端の座標(x,y,θ)
occupied_thresh: この数値より大きいところを障害物とみなす
free_thresh: この数値より小さいところをフリースペースとみなす
negate: 白黒反転させるかどうか

```yaml
image: output.pgm
resolution: 0.050000
origin: [-10.000000, -10.000000, 0.000000]
negate: 0
occupied_thresh: 0.65
free_thresh: 0.196
```
