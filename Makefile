all:	script.c echo.c pinfo.c fore_back.c cd.c ls.c pwd.c history.c
		gcc -w script.c ls.c cd.c fore_back.c pinfo.c pwd.c echo.c history.c