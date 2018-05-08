# mdb
Persistent Key Value database I started making for my interactive disassembler.
Uses B+ trees internally. 
Right now it just dumps the key-value pairs into a file when exiting and rebuilds the tree when a database is opened.
However, future plans include keeping the B+ Tree in pages and using buffer manager for efficient io access.

Includes test program for that lets you 'get' and 'set' values

Example

```
>set key1 val1
key1 -> val1
>set key2 val2
key2 -> val2
>set key3 val3 
key3 -> val3
>set key4 val4
key4 -> val4
>set key5 val5
key5 -> val5
>set key6 val6
key6 -> val6
>set key7 val7
key7 -> val7
>set key8 val8
key8 -> val8
>set key9 val9
key9 -> val9
>dump
			((val1)key1)
		(key2)
			((val2)key2)
	(key3)
			((val3)key3)
		(key4)
			((val4)key4)
(key5)
			((val5)key5)
		(key6)
			((val6)key6)
	(key7)
			((val7)key7)
		(key8)
			((val8)key8)
			((val9)key9)
>quit
Serializing:
Writing to disk
```
