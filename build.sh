clang -o denvlate -I/usr/local/include -L/usr/local/lib -I./include ./src/env_reader.c ./src/processor.c ./src/template.c ./src/main.c -std=c11 -pedantic