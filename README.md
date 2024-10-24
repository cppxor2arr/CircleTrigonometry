# Circle trigonometry visualization with SFML

Rewritten code for this [video](https://www.youtube.com/watch?v=RG-zH1W8Bec) (I couldn't find the old code).

## How to build and run

If this doesn't work because dependencies are missing try reading this:  
https://www.sfml-dev.org/tutorials/2.6/start-cmake.php

1. Go into this directory (*CircleTrigonometry*)
2. Run `cmake -B build -DCMAKE_BUILD_TYPE=Release`
3. Go into the *build* directory
4. Run `make` or `ninja` (after this the compiled *circle_trigonometry* binary should be in the *bin* directory)
5. Copy the font file into this directory (`cp ../AnonymousPro-Regular.ttf .`)
6. Run the *circle_trigonometry* binary in the *bin* directory (`./bin/circle_trigonometry`)
