NAME=ShellMsg
$(NAME).vxd:$(NAME).obj
	link -vxd -def:$(NAME).def $(NAME).obj
$(NAME).obj:$(NAME).asm
	ml -coff -c -Cx  -DMASM6 -DBLD_COFF -DIS_32 $(NAME).asm