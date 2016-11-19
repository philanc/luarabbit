# Luarabbit

Luarabbit is a small Lua extension library including the *Rabbit* stream cipher. 

It works with Lua versions 5.1 to 5.3.

Rabbit is a very fast stream cipher (faster and much stronger than rc4). It was one of the four eSTREAM finalists in 2008. See the rabbit presentation pages at [eSTREAM](http://www.ecrypt.eu.org/stream/rabbitpf.html) and at [ECRYPT II](http://www.ecrypt.eu.org/stream/e2-rabbit.html).  Rabbit was also specified in [RFC 4503](http://www.ietf.org/rfc/rfc4503.txt)

### API

```
rabbit(str, key, iv)
	encrypt (or decrypt, as rabbit is symmetric) string str with 
	key string key and initial value string iv.
	key must be 16 bytes. iv must be 8 bytes
	return the encrypted string (same length as str)
	or nil, error msg if the key or iv lengths are not correct
	-- for more information and references on rabbit, see the comment 
	at the top of src/rabbit.c

encode(str, key, iv)
decode(str, key, iv)
	encode and decode are defined as aliases of the rabbit() 
	symmetrical function.
```

### License

luarabbit is distributed under the terms of the MIT License. 

The luarabbit library includes the rabbit implementation by Cryptico A/S 
(public domain, since 2008)

Copyright (c) 2016  Phil Leblanc 


	




