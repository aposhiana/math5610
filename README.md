## MATH 5610:  Computational Linear Algebra

#### How to use this library

If you have a gcc compatible compiler, run `./build_run.sh` to build and execute the tests for this project.

You can also run the project inside a Docker container using the Ubuntu base Docker image from the Dockerfile in the root directory of this repository. Look at getting Docker [here](https://docs.docker.com/install/). Then `cd` into the root directory of the cloned repository. You can then build the image with the following command:
```
docker build -t cppdev .
```

You can then run the container, mount the repository at the `/app` directory of the container, and enter a shell in the container with the command below. Note that the `--rm` flag will cause you to automatically stop the container once you type `exit` to exit the container shell.
```
docker run -it --rm --mount type=bind,src="$(pwd)",dst=/app cppdev /bin/bash
```
You can then run `./build_run.sh` inside the container. To debug using valgrind after building, `cd` into the build directory and run the following: 
```
valgrind --leak-check=yes ./LinAlgTester
```

#### Software manual
The software manual is the technical documentation for this project. It includes detailed descriptions of all routines with examples.

[See the software manual](software_manual/README.md).

#### Homework
My homeworks are included in this repository as markdown files. The homeowork tasks contain short descriptions and links to the relevent files produced and software manual entries.

[See homework](homework/README.md).
