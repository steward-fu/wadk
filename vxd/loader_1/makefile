NAME=vxdloader
$(NAME).exe: $(NAME).obj
        Link   /SUBSYSTEM:WINDOWS /LIBPATH:c:\masm\lib $(NAME).obj
$(NAME).obj: $(NAME).asm
        ml /c /coff /Cp  $(NAME).asm
