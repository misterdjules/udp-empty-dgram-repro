# How to reproduce the issue

First, make sure you initialized the libuv submodule:

```
$ git submodule update --init
```

Then, build libuv:
```
$ cd libuv && sh ./autogen.sh && ./configure && make -j 8 && cd -
```

Now build the binary that reproduces the issue:
```
make
```

Finally, run the binary:
```
$ ./repro
```

On a Linux system, it should send and receive the datagram properly
```
$ ./repro
on_send callback called!
Recv from 127.0.0.1
$
```

but on MacOS X, the datagram is never received:
```
$ ./repro
on_send callback called!
```

and the process just hangs indefinitely.
