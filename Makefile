hserver: hserver.c
	gcc hserver.c parser.c doc_prep.c mime_chk.c response_build.c -o a.exe -lws2_32

