# Parallel BFS
Parallel BFS algorithm implementation based on PCTL lib
## Prerequisites
You need to download and load docker image for OpenCilk:
```
wget "https://github.com/OpenCilk/opencilk-project/releases/download/opencilk%2Fv1.0/docker-opencilk-v1.0.tar.gz"
docker load < docker-opencilk-v1.0.tar.gz
```
## Run
Build and run it in docker with 4 workers:
```
docker run -it -v $(pwd):/home/parallel-bfs opencilk:v1.0 bash
cd home/parallel-bfs
./build.sh
CILK_NWORKERS=4 cmake-build-Release/parallel-bfs
```
## Results
```
Average of 5 bfs runs on cubic graph with edge = 400:
Seq bfs: 26.7513s
Par bfs: 10.2093s
Seq / par: 2.6202
```
