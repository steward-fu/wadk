.386p 
include vmm.inc 

DECLARE_VIRTUAL_DEVICE FIRSTVXD,1,0, FIRSTVXD_Control,\
     UNDEFINED_DEVICE_ID, UNDEFINED_INIT_ORDER 

Begin_control_dispatch FIRSTVXD 
End_control_dispatch FIRSTVXD 

end