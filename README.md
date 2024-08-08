# lvgl_demo

## Build and run the docker environment
```
docker build --build-arg DUID=$(id -u) --build-arg DGID=$(id -g) --build-arg DUSR=$(whoami) -f lvgl_demo.dockeronment -t lvgl_demo . 
docker run --rm -it -v $(pwd):$(pwd) --workdir $(pwd) lvgl_demo
```

## Create lvgl library
```
cd littlevgl-8/lvgl/build
rm -rf *
cmake ../
make
```
When the compilation process finish you should get: `[100%] Linking C static library lib/liblvgl.a`

## Compile demo application
```
#Change to demo directory (lvgl_repo_home_dir/demo_lvgl/)
cd ../../../demo_lvgl/
make
```

## Copy and run app executable to powerwatch
```
#Copy the app executable to PowerWatch using ssh
scp lvgl_demo pw@xx.xx.xx.xx:/tmp

#Inside of Powerwatch run the app
/tmp/lvgl_demo
```
